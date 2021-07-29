#include "coroutine.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

#if __APPLE__ && __MACH__
#include <sys/ucontext.h>
#else

#include <ucontext.h>

#endif

#define STACK_SIZE (1024*1024)
#define DEFAULT_COROUTINE 16

struct coroutine;

struct schedule {
    char stack[STACK_SIZE]; //栈大小
    ucontext_t main;
    int nco;
    int cap;
    int running;
    struct coroutine **co;  //协程列表
};

struct coroutine {
    coroutine_func func;    //协程方法
    void *ud;
    ucontext_t ctx;
    struct schedule *sch;
    ptrdiff_t cap;
    ptrdiff_t size;
    int status;
    char *stack;         //栈大小
};

static struct coroutine *_co_new(struct schedule *S, coroutine_func func, void *ud) {
    struct coroutine *co = malloc(sizeof(*co));
    co->func = func;
    co->ud = ud;
    co->sch = S;
    co->cap = 0;
    co->size = 0;
    co->status = COROUTINE_READY;
    co->stack = NULL;
    return co;
}

static void _co_delete(struct coroutine *co) {
    free(co->stack);
    free(co);
}

struct schedule *coroutine_open(void) {
    struct schedule *s = malloc(sizeof(*s));
    s->nco = 0;
    s->cap = DEFAULT_COROUTINE;
    s->running = -1;
    s->co = malloc(sizeof(struct coroutine *) * s->cap);
    memset(s->co, 0, sizeof(struct coroutine *) * s->cap);
    return s;
}

void coroutine_close(struct schedule *s) {
    int i;
    for (i = 0; i < s->cap; i++) {
        struct coroutine *co = s->co[i];
        if (co) {
            _co_delete(co);
        }
    }
    free(s->co);
    s->co = NULL;
    free(s);
}

int coroutine_new(struct schedule *s, coroutine_func func, void *ud) {
    struct coroutine *co = _co_new(s, func, ud);
    if (s->nco >= s->cap) {
        //扩容
        int id = s->cap;
        s->co = realloc(s->co, s->cap * 2 * sizeof(struct coroutine *));
        memset(s->co + s->cap, 0, sizeof(struct coroutine *) * s->cap);
        s->co[s->cap] = co;
        s->cap *= 2;
        ++s->nco;
        return id;
    } else {
        int i;
        for (i = 0; i < s->cap; i++) {
            int id = (i + s->nco) % s->cap;
            if (s->co[id] == NULL) {
                s->co[id] = co;
                ++s->nco;
                return id;
            }
        }
    }
    assert(0);
    return -1;
}

static void mainfunc(uint32_t low32, uint32_t hi32) {
    //合并指针
    uintptr_t ptr = (uintptr_t) low32 | ((uintptr_t) hi32 << 32);
    struct schedule *s = (struct schedule *) ptr;
    int id = s->running;
    struct coroutine *c = s->co[id];
    c->func(s, c->ud);
    _co_delete(c);
    s->co[id] = NULL;
    --s->nco;
    s->running = -1;
}

void coroutine_resume(struct schedule *S, int id) {
    assert(S->running == -1);
    assert(id >= 0 && id < S->cap);
    struct coroutine *C = S->co[id];
    if (C == NULL)
        return;
    int status = C->status;
    switch (status) {
        case COROUTINE_READY:
            //获取当前上下文
            getcontext(&C->ctx);
            C->ctx.uc_stack.ss_sp = S->stack;
            C->ctx.uc_stack.ss_size = STACK_SIZE;
            C->ctx.uc_link = &S->main;      //执行完当前，后继是main
            S->running = id;
            C->status = COROUTINE_RUNNING;
            uintptr_t ptr = (uintptr_t) S;
            //把指针64拆成2个32位传进参数。为什么这么搞？？？
            makecontext(&C->ctx, (void (*)(void)) mainfunc, 2, (uint32_t) ptr, (uint32_t) (ptr >> 32));
            //挂起main，开始当前协程
            swapcontext(&S->main, &C->ctx);
            break;
        case COROUTINE_SUSPEND:
            memcpy(S->stack + STACK_SIZE - C->size, C->stack, C->size);
            S->running = id;
            C->status = COROUTINE_RUNNING;
            //挂起main，开始当前协程
            swapcontext(&S->main, &C->ctx);
            break;
        default:
            assert(0);
    }
}

static void _save_stack(struct coroutine *c, char *top) {
    char dummy = 0;
    assert(top - &dummy <= STACK_SIZE);
    if (c->cap < top - &dummy) {
        free(c->stack);
        c->cap = top - &dummy;
        c->stack = malloc(c->cap);
    }
    c->size = top - &dummy;
    memcpy(c->stack, &dummy, c->size);
}

void coroutine_yield(struct schedule *S) {
    int id = S->running;
    assert(id >= 0);
    struct coroutine *C = S->co[id];
    assert((char *) &C > S->stack);
    _save_stack(C, S->stack + STACK_SIZE);
    C->status = COROUTINE_SUSPEND;
    S->running = -1;
    //当前协程挂起，开始main
    swapcontext(&C->ctx, &S->main);
}

int coroutine_status(struct schedule *S, int id) {
    assert(id >= 0 && id < S->cap);
    if (S->co[id] == NULL) {
        return COROUTINE_DEAD;
    }
    return S->co[id]->status;
}

int coroutine_running(struct schedule *S) {
    return S->running;
}


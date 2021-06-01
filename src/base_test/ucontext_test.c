/**
ucontext族函数详解
https://langzi989.github.io/2017/10/06/ucontext%E5%87%BD%E6%95%B0%E8%AF%A6%E8%A7%A3/
https://blog.csdn.net/dragon101788/article/details/80311346

#include <ucontext.h>
typedef struct ucontext_t {
  struct ucontext_t* uc_link;
  sigset_t uc_sigmask;
  stack_t uc_stack;
  mcontext_t uc_mcontext;
  ...
};
类成员解释:

uc_link:为当前context执行结束之后要执行的下一个context，若uc_link为空，执行完当前context之后退出程序。
uc_sigmask : 执行当前上下文过程中需要屏蔽的信号列表，即信号掩码
uc_stack : 为当前context运行的栈信息。
uc_mcontext : 保存具体的程序执行上下文，如PC值，堆栈指针以及寄存器值等信息。它的实现依赖于底层，是平台硬件相关的。此实现不透明。

#include <ucontext.h>
void makecontext(ucontext_t* ucp, void (*func)(), int argc, ...);
int swapcontext(ucontext_t* olducp, ucontext_t* newucp);
int getcontext(ucontext_t* ucp);
int setcontext(const ucontext_t* ucp);

makecontext:初始化一个ucontext_t,func参数指明了该context的入口函数，argc为入口参数的个数，每个参数的类型必须是int类型。
 另外在makecontext之前，一般需要显示的初始化栈信息以及信号掩码集同时也需要初始化uc_link，以便程序退出上下文后继续执行。

swapcontext:原子操作，该函数的工作是保存当前上下文并将上下文切换到新的上下文运行。
getcontext:将当前的执行上下文保存在ucp中，以便后续恢复上下文
setcontext : 将当前程序切换到新的context,在执行正确的情况下该函数直接切换到新的执行状态，不会返回。

注意:setcontext执行成功不返回，getcontext执行成功返回0，若执行失败都返回-1。若uc_link为NULL,执行完新的上下文之后程序结束。

 */

#include <ucontext.h>
#include <unistd.h>

void newContextFun() {
    printf("this is the new context \n");
}

int main() {
    char stack[10*1204];

    //get current context
    ucontext_t curContext;
    getcontext(&curContext);        //将当前的执行上下文保存在ucp中，以便后续恢复上下文

    //modify the current context
    ucontext_t newContext = curContext;
    newContext.uc_stack.ss_sp = stack;
    newContext.uc_stack.ss_size = sizeof(stack);
    newContext.uc_stack.ss_flags = 0;
    newContext.uc_link = &curContext;

    //register the new context
    makecontext(&newContext, (void(*)(void))newContextFun, 0);
    swapcontext(&curContext, &newContext);  //原子操作，该函数的工作是保存当前上下文并将上下文切换到新的上下文运行。

    printf("main\n");
    return 0;
}
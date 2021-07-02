#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>
#include <stdatomic.h>

#include <pthread.h>

#ifdef __STDC_NO_ATOMICS__ // since gcc 4.9
#error "Do not support C11 atomic"
#endif

// 为了避免CPU直接死等，
// 这里定义了常用处理器架构的释放当前线程的暗示指令操作
#if defined(__x86__) || defined(__x86_64__) || defined(__i386__)
#define CPU_PAUSE()     asm("pause")
#elif defined(__arm__) || defined(__aarch64__)
#define CPU_PAUSE()     asm("yield")
#else
#define CPU_PAUSE()
#endif

/// 为了通用性，这里用一个结构体封装了原子标志与普通的浮点数对象
struct MyAtomicFloat {
    volatile atomic_flag atomFlag;
    // 出于性能上考虑，我们应该尽量让原子对象与普通对象之间留有些空间
    int padding;
    // 如果当前编译器能支持C11的alignas的话，
    // 那么我们也能使用alignas来做字节对齐
    alignas(16) float value;
};

/// 定义一个将被多线程共享的原子浮点数对象
static volatile struct MyAtomicFloat sAtomicFLoatObject;

/// 对多线程共享的原子对象进行求递增操作
/// @param nLoops 指定对共享原子对象操作几次
static void AtomicValueInc(int nLoops) {
    // 这里对共享原子对象操作nLoops次
    for (int loop = 0; loop < nLoops; loop++) {
        // 先进行上锁
        while (atomic_flag_test_and_set(&sAtomicFLoatObject.atomFlag)) {
            CPU_PAUSE();
        }
        // 对共享数据做递增操作
        sAtomicFLoatObject.value += 1.0f;
        // 最后释放锁
        atomic_flag_clear(&sAtomicFLoatObject.atomFlag);
    }
}

/// 线程处理函数
static void *ThreadProc(void *args) {
    // 在用户线程中执行10000次
    AtomicValueInc(10000);
    return NULL;
}

int main(int argc, const char *argv[]) {
    printf("The size is: %zu, `value` offset is: %zu\n",
           sizeof(sAtomicFLoatObject), offsetof(struct MyAtomicFloat, value));
    // 对原子浮点数对象先进行初始化
    sAtomicFLoatObject.atomFlag = (atomic_flag) ATOMIC_FLAG_INIT;
    sAtomicFLoatObject.value = 0.0f;

    pthread_t threadID;
    // 创建线程并调度执行
    if (pthread_create(&threadID, NULL, ThreadProc, NULL) != 0) {
        puts("Failed to create a thread!");
        return 0;
    }
    // 在主线程中也执行10000次
    AtomicValueInc(10000);
    // 等待线程执行完毕
    pthread_join(threadID, NULL);
    // 输出最终结果
    printf("The final result is: %f\n", sAtomicFLoatObject.value);
}
//
// Created by Admin on 2021/7/2.
//

// 在执行多任务前，原子锁对象初始值为0
volatile int g_atomic_lock = 0;

// 这里是多个线程可能共同的代码
void AtomicModify(void) {
    // SWAP的第一个参数指向某一原子对象的地址。
    // SWAP操作一般是将第二个实参的值写入到原子对象中去，
    // 然后返回该原子对象在SWAP操作之前的值。
    while (SWAP(&g_atomic_lock, 1) == 1) {
        // 如果SWAP操作返回1，说明之前已经有线程对该对象上了锁，
        // 此时只能等待该原子对象重新变为0。
        CPU_PAUSE();    // 这里暗示CPU可以做对其他线程的调度
    }
    // SWAP操作成功之后，g_atomic_lock的值变为1了，
    // 此时对多个线程所共享的对象进行操作
    DoModificationToSharedObject();

    // 对共享对象操作完之后，释放原子锁
    SWAP(&g_atomic_lock, 0);
}

void AtomicSumOfSquares(volatile int *atom, int b) {
    int orgValue, dstValue;
    do {
        // 先加载原子对象的当前值
        orgValue = *atom;

        // 再对原始值做平方和计算，作为最终写入的结果
        dstValue = orgValue * orgValue + b * b;
    }
        // 这里的CAS函数，第一个参数指向一个原子对象；
        // 第二个参数指向之前加载该原子对象的变量；
        // 第三个参数则是比较成功后，最后写入到该原子对象的值。
        // CAS先将原子对象的内容与之前加载它的变量的值进行比较，两者是否相同；
        // 如果相同，说明在此操作期间没有其他线程对该原子进行修改，
        // 则将第三个参数的值写到该原子对象中去，然后返回true；
        // 如果两者不同，说明这期间已经有某个线程对该原子对象进行了修改，返回false。
    while (!CAS(atom, &orgValue, dstValue);

    return dstValue;
}

int main(int argc, char **argv) {

}
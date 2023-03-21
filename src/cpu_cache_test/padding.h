//在设计数据结构的时候，尽量将只读数据与读写数据分开，并具尽量将同一时间访问的数据组合在一起。这样CPU能一次将需要的数据读入
//缓存与内存对齐
#define CACHE_LINE_SIZE 64  //缓存行长度

typedef struct {
    int id; // 不易变
    int factor;// 易变
    char name[64];// 不易变
    int value;// 易变
} AData;

typedef struct {
    int id; // 不易变
    char name[32];// 不易变
    char __align[CACHE_LINE_SIZE - sizeof(int) - sizeof(32) * sizeof(char) % CACHE_LINE_SIZE];
    int factor;     // 易变
    int value;      // 易变
    char __align2[CACHE_LINE_SIZE - 2 * sizeof(int) % CACHE_LINE_SIZE];
} BData;

typedef struct {
    int a;
    char padding[CACHE_LINE_SIZE - sizeof(int)];
    int b;
} PaddingData;

typedef struct {
    int a;
//    char padding[64]; // thread2.c代码
    int b;
} NoPaddingData;
int main(int __argc, char *__argv[]) {
    int *__p = (int *) __argc;
    (*__p) = 9999;
//asm("":::“memory”);
    if ((*__p) == 9999)
        return 5;
    return (*__p);
}
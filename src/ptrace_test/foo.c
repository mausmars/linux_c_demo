int foo(int a, int b) {
    int c;
    static double d = 5.0;
    c = a + b;
    return c;
}

int main() {
    int r;
    r = foo(2, 3);
    return 0;
}
// gcc -o array_test2 array_test2.c
// time ./array_test2

#define ARRAY_SIZE 10240

char array[ARRAY_SIZE][ARRAY_SIZE];

int main() {
    int i, j;
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++) {
            array[j][i] = 'a';
        }
    }
    return 0;
}
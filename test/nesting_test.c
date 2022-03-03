int inner(int a, int* b) {
    int x = a;
    return x+*b;
}

int outer(int N) {
    int i;
    int j;
    int x;
    int M;
    for (i = 0; i < N; i++) {
        x = i;
        if (i > 1) {
            x = x + 5;
        }
        int z = 5;
        int* z_ptr = &z;
        inner(x, z_ptr);
        M = inner(3, z_ptr);
        for (j = 1; j < M; j++) {
            if (i == 0) {
                x *= inner(j, z_ptr);
            }
        }
    }
    return x;
}

int main(void) {
    return outer(5);
}
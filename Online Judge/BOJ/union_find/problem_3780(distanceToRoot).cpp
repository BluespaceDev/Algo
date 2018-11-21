#include <cstdio>

#define MAX_N    20000

#define ABS(x)  ((x) > 0 ? (x) : -(x))

int T, N;
int uf[MAX_N+1];
int uf_size[MAX_N + 1];

int find(int a) {
    int a1 = a;
    while (a1 != uf[a1]) {
        a1 = uf[a1];
        uf_size[a] += uf_size[a1];
        uf[a] = uf[a1];
    }
    return uf_size[a];
}
void merge(int a, int b) {
    uf[a] = b;
    uf_size[a] = ABS(a - b) % 1000;
}

int main() {
    scanf("%d\n", &T);
    while (T--) {
        scanf("%d\n", &N);
        for (int i = 1; i <= N; ++i) {
            uf[i] = i;
            uf_size[i] = 0;
        }
        
        while (1) {
            char cmd;
            int a, b;
            scanf("%c\n", &cmd);
            if (cmd == 'E') {
                scanf("%d\n", &a);
                printf("%d\n", find(a));
            }
            else if (cmd == 'I') {
                scanf("%d %d\n", &a, &b);
                merge(a, b);
            }
            else {
                break;
            }
        }
    }
    return 0;
}

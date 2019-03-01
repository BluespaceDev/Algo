#include <cstdio>

#define MAX_N   100

int n,k;
bool adj[MAX_N][MAX_N];

int main(){
    scanf("%d %d", &n, &k);
    while(k--){
        int a,b;
        scanf("%d %d", &a, &b);
        adj[a-1][b-1] = true;
    }
    
    for(int i = 0; i < n; ++i)
        adj[i][i] = true;
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                adj[i][j] |= adj[i][k] && adj[k][j];

    for(int i = 0; i < n; ++i){
        int ans = n;
        for(int j = 0; j < n; ++j)
            if(adj[i][j] || adj[j][i])
                --ans;
        printf("%d\n", ans);
    }
    return 0;
}

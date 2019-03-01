#include <cstdio>

#define MAX_N   500

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

    int ans = 0;
    for(int i = 0; i < n; ++i){
        bool know = true;
        for(int j = 0; j < n; ++j){
            know &= adj[i][j] || adj[j][i];
        }
        if(know)    ++ans;
    }
    printf("%d", ans);
    
    return 0;
}

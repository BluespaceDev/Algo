#include <cstdio>
#include <cstring>

#define MAX_N   400

int n,k;
bool adj[MAX_N][MAX_N];

int main(){
    scanf("%d %d", &n, &k);
    while(k--){
        int a,b;
        scanf("%d %d", &a, &b);
        adj[a-1][b-1] = true;
    }
    
    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                adj[i][j] |= adj[i][k] && adj[k][j];

    int s;
    scanf("%d", &s);
    while(s--){
        int a,b;
        scanf("%d %d", &a, &b);
        a--; b--;
        if(adj[a][b])       printf("-1\n");
        else if(adj[b][a])  printf("1\n");
        else                printf("0\n");
    }
    
    return 0;
}

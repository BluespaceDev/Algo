#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_M   10000

int N, M;

vector<int> adj[MAX_M*2+1];
int dfs_num[MAX_M*2+1];
int dfs_low[MAX_M*2+1];
int dfs_count;
bool scc_visied[MAX_M*2+1];
int stack[MAX_M*2], s_top;

void scc(int u){
    dfs_num[u] = dfs_low[u] = ++dfs_count;
    stack[s_top++] = u;
    for(int v : adj[u]){
        if(dfs_num[v] == 0)
            scc(v);
        if(!scc_visied[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if(dfs_num[u] == dfs_low[u]){
        while(1){
            int v = stack[--s_top];
            scc_visied[v] = true;
            if(u == v)  break;
        }
    }
}

int main(){
    scanf("%d %d\n", &N, &M);
    for(int i = 0,a,b; i < N; ++i){
        scanf("%d %d\n", &a, &b);
        a = a > 0 ? a*2-1 : -a*2;
        b = b > 0 ? b*2-1 : -b*2;
        adj[a+(a%2?1:-1)].push_back(b);
        adj[b+(b%2?1:-1)].push_back(a);
    }
    
    M *= 2;
    for(int i = 1; i <= M; ++i)
        if(dfs_num[i] == 0)
            scc(i);
    
    for(int i = 1; i < M; i+=2)
        if(dfs_low[i] == dfs_low[i+1]){
            printf("OTL");
            return 0;
        }
    
    printf("^_^");
    
    return 0;
}

// false->true, true->false
// true->true 이 상황은 발생하면 안됨
// 명제 4개로 정의하여 둘다 거짓, 둘다 참일수는 없음

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N   2000

int T;
int n, m;

vector<int> adj[MAX_N*2+1];
int dfs_num[MAX_N*2+1];
int dfs_low[MAX_N*2+1];
int dfs_count;
bool scc_visited[MAX_N*2+1];
int stack[MAX_N*2], s_top;

void scc(int u){
    dfs_num[u] = dfs_low[u] = ++dfs_count;
    stack[s_top++] = u;
    for(int v : adj[u]){
        if(dfs_num[v] == 0)
            scc(v);
        if(!scc_visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if(dfs_num[u] == dfs_low[u]){
        while(1){
            int v = stack[--s_top];
            scc_visited[v] = true;
            if(u == v)  break;
        }
    }
}

int main(){
    scanf("%d\n", &T);
    for(int t = 1; t <= T; ++t){
        scanf("%d %d\n", &n, &m);
        for(int i = 0,a,b; i < m; ++i){
            scanf("%d %d\n", &a, &b);
            adj[a+n].push_back(b);
            adj[b+n].push_back(a);
            adj[a].push_back(b+n);
            adj[b].push_back(a+n);
        }
        
        for(int i = 1; i <= n*2; ++i)
            if(dfs_num[i] == 0)
                scc(i);
        
        bool vaild = true;
        for(int i = 1; i <= n; ++i)
            if(dfs_low[i] == dfs_low[i+n]){
                vaild = false;
                break;
            }
        
        printf("Scenario #%d:\n%s\n\n", t, vaild?"No suspicious bugs found!":"Suspicious bugs found!");
        
        memset(dfs_num, 0, sizeof(dfs_num));
        memset(dfs_low, 0, sizeof(dfs_low));
        memset(scc_visited, false, sizeof(scc_visited));
        dfs_count = 0;
        for(int i = 1; i <= n*2; ++i)
            adj[i].clear();
    }
    return 0;
}

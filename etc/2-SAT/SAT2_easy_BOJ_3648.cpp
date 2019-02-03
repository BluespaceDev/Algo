// 1번째 사람이 true인 조건 ~1 -> 1 추가 => (~1,x)라면 x가 true여야 ~1을 1로 변경가능

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N   1000

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
    while(scanf("%d %d", &n, &m) == 2){
        for(int i = 0,a,b; i < m; ++i){
            scanf("%d %d", &a, &b);
            a = a > 0 ? a : -a+n;
            b = b > 0 ? b : -b+n;
            adj[a<=n ? a+n : a-n].push_back(b);
            adj[b<=n ? b+n : b-n].push_back(a);
        }
        adj[1+n].push_back(1);
        
        for(int i = 1; i <= n*2; ++i)
            if(dfs_num[i] == 0)
                scc(i);
        
        bool vaild = true;
        for(int i = 1; i < n; ++i)
            if(dfs_low[i] == dfs_low[i+n]){
                vaild = false;
                break;
            }
        
        printf("%s\n", vaild?"yes":"no");
        
        memset(dfs_num, 0, sizeof(dfs_num));
        memset(dfs_low, 0, sizeof(dfs_low));
        memset(scc_visited, false, sizeof(scc_visited));
        dfs_count = 0;
        for(int i = 1; i <= n*2; ++i)
            adj[i].clear();
    }
    return 0;
}

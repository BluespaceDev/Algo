// 위상정렬 기본 문제

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_N   100+1

int n, m;
vector<int> adj[MAX_N];
vector<int> ts;
bool visited[MAX_N];

void dfs(int u){
    visited[u] = true;
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if(!visited[v])
            dfs(v);
    }
    ts.push_back(u);
}

int main(){
    while(true){
        scanf("%d %d\n", &n, &m);
        if(n == 0)  break;
        
        int a,b;
        for(int i = 0; i < m; ++i){
            scanf("%d %d\n", &a,&b);
            adj[a].push_back(b);
        }
        
        for(int i = 1; i <= n; ++i)
            if(!visited[i])
                dfs(i);
        
        for(int i = (int)ts.size()-1; i >= 0; --i){
            printf("%d ", ts[i]);
        }
        printf("\n");
        
        memset(visited,false,sizeof(visited));
        ts.clear();
        for(int i = 0; i < n; ++i)
            adj[i].clear();
    }
    return 0;
}

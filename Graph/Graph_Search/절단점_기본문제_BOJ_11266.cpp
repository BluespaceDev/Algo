// 절단점
// root node는 child 2개 이상되야 절단점
// 맨 마지막 node는 절단점 아님

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_V   10000+1
#define MAX_E   100000

int V, E, a, b;

vector<int> adj[MAX_V];
int dfs_num[MAX_V];
int dfs_low[MAX_V];
int dfs_parent[MAX_V];
int dfs_count;
int root_child;

bool articulation_vertex[MAX_V];
vector<int> ans;

void dfs(int u){
    dfs_num[u] = dfs_low[u] = ++dfs_count;
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if (dfs_num[v] == 0){
            dfs_parent[v] = u;
            if (dfs_parent[u] == -1)
                root_child++;
            
            dfs(v);
            
            if (dfs_low[v] >= dfs_num[u]) // 절단점
                articulation_vertex[u] = true;
            
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if(dfs_parent[u] != v){    // 이전 간선은 역방향 간선이 아님
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
    }
}

int main(){
    scanf("%d %d\n", &V, &E);
    for(int i = 0; i < E; ++i){
        scanf("%d %d\n", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    for(int i = 1; i <= V; ++i)
        if(dfs_num[i] == 0){
            dfs_parent[i] = -1;
            root_child = 0;
            dfs(i);
            articulation_vertex[i] = root_child > 1;
        }
    
    
    for(int i = 1; i <= V; ++i)
        if(articulation_vertex[i])
            ans.push_back(i);
    
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); ++i)
        printf("%d ", ans[i]);
    
    return 0;
}

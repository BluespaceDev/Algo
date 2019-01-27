// 절단선
// 절단점 u대신 v를 찾고, parent랑 묶인 edge를 찾음

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_V   100000+1
#define MAX_E   1000000

int V, E, a, b;

vector<int> adj[MAX_V];
int dfs_num[MAX_V];
int dfs_low[MAX_V];
int dfs_parent[MAX_V];
int dfs_count;

bool articulation_vertex[MAX_V];
vector<pair<int, int>> ans;

void dfs(int u){
    dfs_num[u] = dfs_low[u] = ++dfs_count;
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if (dfs_num[v] == 0){
            dfs_parent[v] = u;
            
            dfs(v);
            
            if (dfs_low[v] > dfs_num[u]) // 절단선
                articulation_vertex[v] = true;
            
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
        if(dfs_num[i] == 0)
            dfs(i);
    
    for(int i = 1; i <= V; ++i)
        if(articulation_vertex[i]){
            if(i < dfs_parent[i])
                ans.push_back(make_pair(i, dfs_parent[i]));
            else
                ans.push_back(make_pair(dfs_parent[i], i));
        }
    
    sort(ans.begin(), ans.end());
    
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); ++i)
        printf("%d %d\n", ans[i].first, ans[i].second);
    
    return 0;
}

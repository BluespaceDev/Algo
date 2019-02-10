// MST가 되지 않는 조건 필요
// LCA 때 높이 맞출때 음수가 되는 경우 조심 (실수)

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_V   50000
#define MAX_E   200000

int V, E;
vector<pair<int,pair<int,int>>> edges;

vector<pair<int,int>> mst[MAX_V+1];
bool mst_edge[MAX_E];

int p[MAX_V+1][19], d[MAX_V+1];
int max_w[MAX_V+1][19];

int g[MAX_V+1];

int find(int u){
    return g[u] == u ? u : g[u] = find(g[u]);
}
void merge(int u, int v){
    g[find(u)] = find(v);
}
bool disjoint(int u, int v){
    return find(u) != find(v);
}

void dfs(int u){
    for(auto e : mst[u]){
        if(p[e.second][0] == 0){
            max_w[e.second][0] = e.first;
            p[e.second][0] = u;
            d[e.second] = d[u] + 1;
            dfs(e.second);
        }
    }
}
// mst에 없는 간선들은 항상 같거나 큼, 같으면. MST가 되기 때문에 제외
int find_w(int u, int j, int mst_not_w){
    if(j == 0)  return max_w[u][j] == mst_not_w ? 0 : max_w[u][j];
    
    if(max_w[u][j] < mst_not_w) return max_w[u][j];
    
    return max(find_w(u, j-1, mst_not_w), find_w(p[u][j-1], j-1, mst_not_w));
}
int lca(int u, int v, int mst_not_w){
    if(d[u] < d[v]) swap(u,v);
    
    int max_ret = 0;
    for(int j = 18; j >= 0; --j){
        if(d[u] - d[v] >= (1<<j)){
            if(max_w[u][j] == mst_not_w)
                max_ret = max(max_ret, find_w(u,j,mst_not_w));
            else
                max_ret = max(max_ret, max_w[u][j]);
            
            u = p[u][j];
        }
    }
    
    if(u == v)  return max_ret;
    
    for(int j = 18; j >= 0; --j)
        if(p[u][j] != -1 && p[u][j] != p[v][j]){
            if(max_w[u][j] == mst_not_w)
                max_ret = max(max_ret, find_w(u, j, mst_not_w));
            else
                max_ret = max(max_ret, max_w[u][j]);

            if(max_w[v][j] == mst_not_w)
                max_ret = max(max_ret, find_w(v, j, mst_not_w));
            else
                max_ret = max(max_ret, max_w[v][j]);
            
            u = p[u][j];
            v = p[v][j];
        }
    
    if(max_w[u][0] < mst_not_w) max_ret = max(max_ret, max_w[u][0]);
    if(max_w[v][0] < mst_not_w) max_ret = max(max_ret, max_w[v][0]);
    
    return max_ret;
}

int main(){
    scanf("%d %d",&V, &E);
    for(int i = 0; i < E; ++i){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        edges.push_back({w,{u,v}});
    }
    //mst외에 다른 edge가 있어야 2-MST 가능
    if(E <= V-1){
        printf("-1\n");
        return 0;
    }
    
    // MST
    sort(edges.begin(), edges.end());
    
    for(int i = 1; i <= V; ++i)
        g[i] = i;
    
    int edge_count = 0;
    int mst_cost = 0;
    for(int i = 0; i < E; ++i){
        auto e = edges[i];
        auto v = e.second;
        if(disjoint(v.first,v.second)){
            merge(v.first, v.second);
            mst[v.first].push_back({e.first, v.second});
            mst[v.second].push_back({e.first, v.first});
            mst_cost += e.first;
            ++edge_count;
            mst_edge[i] = true;
        }
    }
    
    // MST는 간선의 수가 V-1개가 되어야 함(컴포넌트 1개)
    if(edge_count != V-1){
        printf("-1\n");
        return 0;
    }
    
    // LCA
    p[1][0] = 1;
    dfs(1);
    
    for(int j = 0; j < 17; ++j)
        for(int i = 1; i <= V; ++i){
            p[i][j+1] = p[p[i][j]][j];
            max_w[i][j+1] = max(max_w[i][j], max_w[p[i][j]][j]);
        }
    
    // 2-MST
    int ans = 1000000000;
    for(int i = 0; i < E; ++i){
        if(mst_edge[i]) continue;
        auto e = edges[i];
        auto v = e.second;
        int maxE = lca(v.first, v.second, e.first);
        int mst2_cost = mst_cost + e.first - maxE;
        if(mst2_cost > mst_cost)
            ans = min(ans, mst2_cost);
    }
    // MST가 여러개 있는 조건
    if(ans == 1000000000){
        printf("-1\n");
        return 0;
    }
    
    printf("%d\n", ans);
    
    return 0;
}

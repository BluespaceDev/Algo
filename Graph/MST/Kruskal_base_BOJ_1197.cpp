#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_V   10000

int V,E;
vector<int> adj[MAX_V+1];
vector<pair<int, pair<int,int>>> edges;

int unionGroup[MAX_V+1];

int find(int i){
    while(unionGroup[i] != i)
        i = unionGroup[i] = unionGroup[unionGroup[i]];
    return i;
}
void unionSet(int u, int v){
    u = find(u);
    v = find(v);
    unionGroup[u] = v;
}
bool isUnion(int u, int v){
    return find(u) == find(v);
}

int main(){
    scanf("%d %d", &V, &E);
    for(int i = 0; i < E; ++i){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back(make_pair(w, make_pair(u, v)));
    }
    sort(edges.begin(),edges.end());
    for(int i = 1; i <= V; ++i)
        unionGroup[i] = i;
    
    int mst_cost = 0;
    for(int i = 0; i < edges.size(); ++i){
        auto e = edges[i].second;
        if(!isUnion(e.first, e.second)){
            mst_cost += edges[i].first;
            unionSet(e.first, e.second);
        }
    }
    
    printf("%d\n", mst_cost);
    
    return 0;
}

// 2번 정렬할 필요없이 1번 정렬된 것에서 역순으로 하면 됨

#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#define MAX_V   1000

int V,E;
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
    for(int i = 0; i <= E; ++i){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back(make_pair(!w, make_pair(u, v)));
    }
 
    int up_cost = 0;
    sort(edges.begin(),edges.end(),greater<pair<int, pair<int,int>>>());
    for(int i = 0; i <= V; ++i)
        unionGroup[i] = i;
    for(int i = 0; i < edges.size(); ++i){
        auto e = edges[i].second;
        if(!isUnion(e.first, e.second)){
            up_cost += edges[i].first;
            unionSet(e.first, e.second);
        }
    }
    
    int down_cost = 0;
    for(int i = 0; i <= V; ++i)
        unionGroup[i] = i;
    for(int i = (int)edges.size()-1; i >= 0; --i){
        auto e = edges[i].second;
        if(!isUnion(e.first, e.second)){
            down_cost += edges[i].first;
            unionSet(e.first, e.second);
        }
    }
    
    printf("%d\n", up_cost*up_cost-down_cost*down_cost);
    
    return 0;
}

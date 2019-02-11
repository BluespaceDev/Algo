//SPFA - 최악의 경우 O(VE) 라 시간초과
//다익스트라 - q에 최대 O(E)만큼 들어감

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define MAX_V   20000
#define INF     1e9

int V, E, K;
vector<pair<int,int>> adj[MAX_V+1];

int main(){
    scanf("%d %d", &V, &E);
    scanf("%d", &K);
    while(E--){
        int u,v,w;
        scanf("%d %d %d",&u, &v, &w);
        adj[u].push_back({w,v});
    }
    
    vector<int> d(V+1, INF);

    d[K] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({d[K], K});
    while(!pq.empty()){
        auto& a = pq.top();
        int cost = -a.first;
        int u = a.second;
        pq.pop();
        if(d[u] < cost)    continue;
        for(auto& e : adj[u]){
            int v = e.second;
            int w = e.first;
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                pq.push({-d[v], v});
            }
        }
    }
    
    for(int i = 1; i <= V; ++i)
        if(d[i] >= INF) printf("INF\n");
        else            printf("%d\n", d[i]);
    
    return 0;
}

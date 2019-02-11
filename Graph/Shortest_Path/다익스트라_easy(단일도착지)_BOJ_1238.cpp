// 단일 도착지는 간선을 바꿔서 돌리면 됨

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define MAX_N   1000
#define INF     1e9

int N, M, X;
vector<pair<int,int>> adj[MAX_N+1];
vector<pair<int,int>> adj_rev[MAX_N+1];

int d1[MAX_N+1], d2[MAX_N+1];

void dijkstra(vector<pair<int,int>> adj[], int d[]){
    for(int i = 1; i <= N; ++i) d[i] = INF;
    
    d[X] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({d[X], X});
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
}

int main(){
    scanf("%d %d %d", &N, &M, &X);
    while(M--){
        int u,v,w;
        scanf("%d %d %d",&u, &v, &w);
        adj[u].push_back({w,v});
        adj_rev[v].push_back({w,u});
    }
    
    dijkstra(adj, d1);
    dijkstra(adj_rev, d2);
    
    int ans = d1[1]+d2[1];
    for(int i = 2; i <= N; ++i)
        if(ans < d1[i]+d2[i]) ans = d1[i]+d2[i];

    printf("%d", ans);
    
    return 0;
}

// s-u-v-t, s-v-u-t 2가지 방법
// s->u 거리가 멀더라도 total은 작을 수 있음

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N   800
#define INF     1e8

int N, M;
vector<pair<int,int>> adj[MAX_N+1];
int d1[MAX_N+1], d2[MAX_N+1], d3[MAX_N+1];

void dijkstra(int s, int d[]){
    for(int i = 0; i <= N; ++i)
        d[i] = INF;
    
    d[s] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({0, s});
    while(!pq.empty()){
        auto& a = pq.top();
        int u = a.second;
        int cost = -a.first;
        pq.pop();
        
        if(d[u] < cost)     continue;
        
        for(auto& e : adj[u]){
            int v = e.second;
            int cost2 = e.first + cost;
            if(d[v] > cost2){
                d[v] = cost2;
                pq.push({-cost2, v});
            }
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    while(M--){
        int u,v,w;
        scanf("%d %d %d",&u, &v, &w);
        adj[u].push_back({w,v});
        adj[v].push_back({w,u});
    }
    int u1, u2;
    scanf("%d %d", &u1, &u2);
    dijkstra(1, d1);
    dijkstra(u1, d2);
    dijkstra(u2, d3);
    int ans = min( d1[u1]+d2[u2]+d3[N], d1[u2]+d3[u1]+d2[N] );
    printf("%d", ans > INF ? -1 : ans);

    return 0;
}

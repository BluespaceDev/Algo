// dp = [V][K]
// 기존 다익스트라에 k 사용할때 cost 0 조건 추가

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N   10000
#define INF     1e13

int N, M, K;
vector<pair<int,int>> adj[MAX_N+1];
long long d[MAX_N+1][21];

void dijkstra(){
    for(int i = 1; i <= N; ++i)
        for(int j = 0; j <= K; ++j)
            d[i][j] = INF;
    
    d[1][0] = 0;
    priority_queue<pair<long long,pair<int,int>>> pq;
    pq.push({d[1][0], {0, 1}});
    while(!pq.empty()){
        auto& a = pq.top();
        long long cost = -a.first;
        int k = a.second.first;
        int u = a.second.second;
        pq.pop();
        
        if(d[u][k] < cost)    continue;
        
        for(auto& e : adj[u]){
            int v = e.second;
            long long c = e.first + cost;
            if(d[v][k] > c){
                d[v][k] = c;
                pq.push({-c, {k, v}});
            }
            if(k+1 <= K && d[v][k+1] > cost){
                d[v][k+1] = cost;
                pq.push({-cost, {k+1, v}});
            }
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &K);
    while(M--){
        int u,v,w;
        scanf("%d %d %d",&u, &v, &w);
        adj[u].push_back({w,v});
        adj[v].push_back({w,u});
    }
    
    dijkstra();
    
    long long ans = INF;
    for(int i = 0; i <= K; ++i)
        if(ans > d[N][i])   ans = d[N][i];
    
    printf("%lld\n", ans);
    
    return 0;
}

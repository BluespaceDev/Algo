#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N   10000
#define INF     1e9

int T;
int N, M, K;
vector<pair<int,int>> adj[MAX_N+1];
int d[MAX_N+1];

pair<int,int> dijkstra(){
    for(int i = 1; i <= N; ++i)
        d[i] = INF;
    
    d[K] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({d[K], K});
    while(!pq.empty()){
        auto& a = pq.top();
        int u = a.second;
        int cost = -a.first;
        pq.pop();
        
        if(d[u] < cost)    continue;
        
        for(auto& e : adj[u]){
            int v = e.second;
            int cost2 = e.first + cost;
            if(d[v] > cost2){
                d[v] = cost2;
                pq.push({-cost2, v});
            }
        }
    }
    
    int count = 0;
    int max_time = 0;
    for(int i = 1; i <= N; ++i){
        if(d[i] < INF){
            count++;
            if(d[i] > max_time) max_time = d[i];
        }
    }
    
    return {count, max_time};
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d", &N, &M, &K);
        while(M--){
            int u,v,w;
            scanf("%d %d %d",&u, &v, &w);
            adj[v].push_back({w,u});
        }
        
        auto ans = dijkstra();
        
        printf("%d %d\n", ans.first, ans.second);
        
        for(int i = 1; i <= N; ++i) adj[i].clear();
    }

    return 0;
}

// u-v 간선 전부 막고 검사해도 시간내에는 통과함 956ms
// 그럴필요 없이 최단 경로내에 간선만 체크해서 못갔을때 경로 측정하면 더 빠르게 통과 가능

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N   1000
#define INF     1e9

int N, M;
vector<pair<int,int>> adj[MAX_N+1];
int d[MAX_N+1];
int p[MAX_N+1];

int dijkstra(){
    for(int i = 1; i <= N; ++i)
        d[i] = INF;
    
    d[1] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({d[1], 1});
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
                p[v] = u;
                pq.push({-cost2, v});
            }
        }
    }
    
    return d[N];
}

int dijkstra_edge_ban(int u1, int v1){
    for(int i = 1; i <= N; ++i)
        d[i] = INF;
    
    d[1] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({d[1], 1});
    while(!pq.empty()){
        auto& a = pq.top();
        int u = a.second;
        int cost = -a.first;
        pq.pop();
        
        if(d[u] < cost)    continue;
        
        for(auto& e : adj[u]){
            int v = e.second;
            int cost2 = e.first + cost;
            if((u1 == u && v1 == v) || (u1 == v && v1 == u))  continue;
            if(d[v] > cost2){
                d[v] = cost2;
                p[v] = u;
                pq.push({-cost2, v});
            }
        }
    }
    
    return d[N];
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; ++i){
        int u,v,w;
        scanf("%d %d %d",&u, &v, &w);
        adj[u].push_back({w,v});
        adj[v].push_back({w,u});
    }
    
    int shortest = dijkstra();
    int maximum = -1;
    
    for(int u = 2; u <= N; ++u){
        int d2 = dijkstra_edge_ban(u, p[u]);
        if(maximum < d2)    maximum = d2;
    }
    
    printf("%d\n", maximum == INF ? -1 : maximum - shortest);

    return 0;
}

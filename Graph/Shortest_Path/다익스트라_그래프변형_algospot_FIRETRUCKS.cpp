/*
그래프 변형 : 시작 정점과 간선 추가하면 다중 출발점 문제 해결 가능
소방차가 아니라 불난곳을 연결해서 소방차에게 다 갈 수 있도록 그래프 구성
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_V   1000
#define INF     1e8

int V,E,N,M;
int fire[MAX_V+1], firetrucks[MAX_V+1];

vector<pair<int,int>> adj[MAX_V+1];
int d[MAX_V+1];

void dijkstra(){
    for(int i = 0; i <= V; ++i)
        d[i] = INF;
    
    d[0] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({0, 0});
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
    int C;
    scanf("%d",&C);
    while(C--){
        scanf("%d %d %d %d", &V, &E, &N, &M);
        while(E--){
            int u,v,w;
            scanf("%d %d %d",&u, &v, &w);
            adj[u].push_back({w,v});
            adj[v].push_back({w,u});
        }
        for(int i = 0; i < N; ++i)
            scanf("%d", &firetrucks[i]);
        for(int i = 0; i < M; ++i)
            scanf("%d", &fire[i]);
        
        // 시작정점, 간선 추가
        for(int i = 0; i < M; ++i){
            adj[0].push_back({0,fire[i]});
        }
        
        dijkstra();
        
        int ans = 0;
        for(int i = 0; i < N; ++i)
            ans += d[firetrucks[i]];
        printf("%d\n", ans);
        
        for(int i = 0; i <= V; ++i) adj[i].clear();
    }

    return 0;
}

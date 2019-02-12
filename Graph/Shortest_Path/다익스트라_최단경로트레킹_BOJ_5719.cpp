// 최단거리 경로는 도착지에서 출발하여 경로를 찾으면 됨
// 최단경로가 아닌 간선으로 할 때 d값이 갱신되기 때문에 다익스트라 다시 돌려야함

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N   500
#define INF     1e9

int N, M;
int S, D;
vector<pair<int,int>> adj[MAX_N];
vector<pair<int,int>> adj_rev[MAX_N];
int d[MAX_N];
bool shortest_path[MAX_N][MAX_N];

void dijkstra(){
    for(int i = 0; i < N; ++i) d[i] = INF;
    
    d[S] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({d[S], S});
    while(!pq.empty()){
        auto& a = pq.top();
        int cost = -a.first;
        int u = a.second;
        pq.pop();
        
        if(d[u] < cost)    continue;
        
        for(auto& e : adj[u]){
            int v = e.second;
            int c = e.first + d[u];
            if(!shortest_path[u][v] && d[v] > c){
                d[v] = c;
                pq.push({-d[v], v});
            }
        }
    }
}
// 최단 경로 찾아서 지우기
void bfs(){
    queue<int> q;
    q.push(D);
    while(!q.empty()){
        int u = q.front(); q.pop();
        
        if(u == S)  continue;
        for(auto& e : adj_rev[u]){
            int v = e.second;
            int w = e.first;
            if(d[u] == d[v] + w){
                q.push(v);
                shortest_path[v][u] = true;
            }
        }
    }
}

int main(){
    while(1){
        scanf("%d %d", &N, &M);
        if(N == 0)  break;
        scanf("%d %d", &S, &D);
        while(M--){
            int u,v,w;
            scanf("%d %d %d",&u, &v, &w);
            adj[u].push_back({w,v});
            adj_rev[v].push_back({w,u});
        }
        
        dijkstra();
        bfs();
        dijkstra();
        
        printf("%d\n", d[D] == INF ? -1 : d[D]);
        
        memset(shortest_path,false,sizeof(shortest_path));
        for(int i = 0; i < N; ++i)  adj[i].clear(), adj_rev[i].clear();
    }
    
    return 0;
}

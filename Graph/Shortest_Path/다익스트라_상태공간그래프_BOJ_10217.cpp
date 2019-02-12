// 상태공간 그래프로 품
// 근데 그냥 dp로도 풀기 가능...

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_N   100
#define MAX_M   10000
#define INF     1e9

struct edge{
    int v,c,d;
    edge(int v, int c, int d) : v(v), c(c), d(d) {}
    bool operator <(edge e) const { return d > e.d; }
};

int T;
int N, M, K;
vector<edge> adj[MAX_N+1];
int d[MAX_N+1][MAX_M+1];

void dijkstra(){
    for(int i = 1; i <= N; ++i)
        for(int j = 0; j <= M; ++j)
            d[i][j] = INF;
    
    d[1][M] = 0;
    priority_queue<edge> pq;
    pq.push({1,M,0});
    while(!pq.empty()){
        auto& a = pq.top();
        int u = a.v;
        int money = a.c;
        int dist = a.d;
        pq.pop();
        
        if(d[u][money] < dist)    continue;
        
        for(auto& e : adj[u]){
            int v = e.v;
            int dist2 = e.d + dist;
            int cost = money - e.c;
            if(cost >= 0 && d[v][cost] > dist2){
                d[v][cost] = dist2;
                pq.push({v, cost, dist2});
            }
        }
    }
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d", &N, &M, &K);
        while(K--){
            int u,v,c,d;
            scanf("%d %d %d %d",&u, &v, &c, &d);
            adj[u].push_back({v,c,d});
        }
        
        dijkstra();
        
        int ans = INF;
        for(int i = 0; i <= M; ++i)
            if(ans > d[N][i])   ans = d[N][i];
        
        if(ans == INF)  printf("Poor KCM\n");
        else            printf("%d\n", ans);
        
        for(int i = 1; i <= N; ++i) adj[i].clear();
    }

    return 0;
}

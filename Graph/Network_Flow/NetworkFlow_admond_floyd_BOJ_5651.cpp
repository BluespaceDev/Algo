/*
 중복 간선 처리 => 용량 더하고, 나중에 edge마다 연결확인함으로써 해결
 u->v 연결확인 => 플로이드를 이용하여 연결확인
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_N   300
#define INF     1000

int N, M;

int capacity[MAX_N+1][MAX_N+1];
int flow[MAX_N+1][MAX_N+1];
int parent[MAX_N+1];
int q[MAX_N+1], wq, rq;

bool floyd[MAX_N+1][MAX_N+1];

vector<pair<int,int>> edges;

int networkFlow_mincut(int source, int sink){
    while(true){
        memset(parent, -1, sizeof(parent));
        wq = rq = 0;
        
        q[wq++] = source;
        parent[source] = source;
        
        while(wq > rq && parent[sink] == -1){
            int u = q[rq++];
            for(int v = 1; v <= N; ++v){
                if(capacity[u][v] - flow[u][v] > 0 && parent[v] == -1){
                    q[wq++] = v;
                    parent[v] = u;
                }
            }
        }
    
        if(parent[sink] == -1) break;
        
        int amount = INF;
        for(int i = sink; parent[i] != i; i = parent[i])
            amount = min(amount, capacity[parent[i]][i] - flow[parent[i]][i]);
        
        for(int i = sink; parent[i] != i; i = parent[i]){
            flow[parent[i]][i] += amount;
            flow[i][parent[i]] -= amount;
        }
    }
    
    // 플로이드 이행적폐쇄
    memset(floyd, false, sizeof(floyd));
    for(int u = 1; u <= N; ++u)
        for(int v = 1; v <= N; ++v)
            if(capacity[u][v] - flow[u][v] > 0)
                floyd[u][v] = 1;
    
    for(int k = 1; k <= N; ++k)
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
                floyd[i][j] |= floyd[i][k] && floyd[k][j];
    
    
    int ans = 0;
    for(auto& e : edges){
        if(!floyd[e.first][e.second]){
            ++ans;
        }
    }
    
    return ans;
}

int main(){
    int K;
    scanf("%d", &K);
    while(K--){
        scanf("%d %d", &N, &M);
        for(int i = 0; i < M; ++i){
            int f,t,b;
            scanf("%d %d %d", &f, &t, &b);
            capacity[f][t] += b;
            edges.push_back({f,t});
        }
        
        printf("%d\n", networkFlow_mincut(1,N));
        
        edges.clear();
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
    }
    return 0;
}

/*
 벨만 포드 + 플로이드(연결되있는지 체크)
 틀린 부분 : 음의 가중치를 고려해야됨 (음의 가중치 순환으로 인해 도달 못해도 INF보다 작을 경우 발생 INF_M만큼)
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_V   100
#define INF     10000000
#define INF_M   100000      // 정점만큼 반복함 (벨만포드)

int V,W;

vector<pair<int,int>> adj[MAX_V];
int d[MAX_V];
bool reachable[MAX_V][MAX_V];

int ford(){
    for(int i = 0; i < V; ++i)  d[i] = INF;
    
    d[0] = 0;
    
    for(int i = 0; i < V-1; ++i){
        for(int u = 0; u < V; ++u)
            for(auto& j : adj[u]){
                int v = j.second;
                int c = j.first;
                if(d[v] > d[u] + c){
                    d[v] = d[u] + c;
                }
            }
    }
    // 음의순환 판단 (0->1 경로만 해당)
    for(int u = 0; u < V; ++u){
        for(auto& j : adj[u]){
            int v = j.second;
            int c = j.first;
            if(d[v] > d[u]+c){
                if(reachable[0][u] && reachable[u][1])
                    return -INF;
            }
        }
    }
    
    return d[1];
}

int main(){
    int C;
    scanf("%d",&C);
    while(C--){
        for(int i = 0; i < V; ++i)  adj[i].clear();
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
                reachable[i][j] = i == j;
        
        scanf("%d %d", &V, &W);
        for(int i = 0; i < W; ++i){
            int a,b,d;
            scanf("%d %d %d", &a, &b, &d);
            adj[a].push_back({d, b});
            reachable[a][b] = true;
        }
        
        for(int k = 0; k < V; k++)
            for(int i = 0; i < V; i++)
                for(int j = 0; j < V; j++)
                    reachable[i][j] |= reachable[i][k] && reachable[k][j];
        
        
        int ans_min = ford();
        if(ans_min >= INF-INF_M){  // 음의 가중치일 경우 1->1 일때 INF보다 작아지는 경우 발생
            puts("UNREACHABLE");
            continue;
        }
        
        if(ans_min == -INF)
            printf("INFINITY ");
        else
            printf("%d ", ans_min);
        
        for(int u = 0; u < V; ++u)
            for(auto& j : adj[u])
                j.first = -j.first;
        
        int ans_max = ford();
        
        if(ans_max == -INF)
            puts("INFINITY");
        else
            printf("%d\n", -ans_max);
    }
    return 0;
}

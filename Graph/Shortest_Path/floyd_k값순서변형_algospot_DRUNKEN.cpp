/*
 단속에 적게 시간이 걸리는 순서대로 진행
 => 문제가 최단거리+큰k 가 min인 값을 찾아야함 -> 큰k가 나중에 나와야됨
 => 플로이드 진행중에는 최단거리 완성이 안되서 진행하는 과정
 */

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_V   500
#define INF     500000

int V, E;
int T[MAX_V+1];

int adj[MAX_V+1][MAX_V+1];
int w[MAX_V+1][MAX_V+1];
vector<pair<int,int>> vertex;

void floyd(){
    for(int i = 1; i <= V; ++i)
        for(int j = 1; j <= V; ++j)
            w[i][j] = (i==j) ? 0 : adj[i][j];
    
    for(auto& v : vertex){
        int k = v.second;
        for(int i = 1; i <= V; ++i)
            for(int j = 1; j <= V; ++j){
                adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
                w[i][j] = min(w[i][j], adj[i][k]+adj[k][j]+T[k]);
            }
    }
}

int main(){
    scanf("%d %d", &V, &E);
    
    for(int i = 1; i <= V; ++i)
        for(int j = 1; j <= V; ++j)
            adj[i][j] = INF;
    
    for(int i = 1; i <= V; ++i){
        scanf("%d", &T[i]);
        vertex.push_back({T[i], i});
    }
    sort(vertex.begin(), vertex.end());
    
    for(int i = 0; i < E; ++i){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a][b] = c;
        adj[b][a] = c;
    }
    
    floyd();
    
    int C;
    scanf("%d", &C);
    while(C--){
        int s,t;
        scanf("%d %d", &s, &t);
        printf("%d\n", w[s][t]);
    }
    
    return 0;
}

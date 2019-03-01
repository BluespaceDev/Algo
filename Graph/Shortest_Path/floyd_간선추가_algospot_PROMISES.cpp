/*
 플로이드에서 정점 추가 대신 간선이 추가된다는 개념
 틀림1 : 입력할때 u->v를 그냥 대입함 -> u->v가 여러개 일 수도 있기 때문에 min값을 넣어야함
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_V   200
#define INF     200000000

int V, M, N;

int adj[MAX_V][MAX_V];

void floyd(){
    for(int i = 0; i < V; ++i)
        adj[i][i] = 0;
    for(int k = 0; k < V; ++k){
        for(int i = 0; i < V; ++i)
            for(int j = 0; j < V; ++j){
                adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
            }
    }
}
bool update(int a, int b, int c){
    if(adj[a][b] <= c)  return false;
    for(int i = 0; i < V; ++i)
        for(int j = 0; j < V; ++j)
            adj[i][j] = min(adj[i][j], min(adj[i][a]+adj[b][j], adj[i][b]+adj[a][j])+c);
    return true;
}

int main(){
    int C; scanf("%d", &C);
    while(C--){
        scanf("%d %d %d", &V, &M, &N);
        
        for(int i = 0; i < V; ++i)
            for(int j = 0; j < V; ++j)
                adj[i][j] = INF;
        
        for(int i = 0; i < M; ++i){
            int a,b,c;
            scanf("%d %d %d", &a, &b, &c);
            if(adj[a][b] > c){
                adj[a][b] = c;
                adj[b][a] = c;
            }
        }
        
        floyd();
        
        int ans = 0;
        for(int i = 0; i < N; ++i){
            int a,b,c;
            scanf("%d %d %d", &a, &b, &c);
            if(!update(a,b,c))   ++ans;
        }
        printf("%d\n", ans);    }
    return 0;
}

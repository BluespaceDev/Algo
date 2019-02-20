/*
그래프 만들기 문제
두개의 차이를 간선, 누적시간을 정점
정점 0으로 가는 최단거리 구하면 답
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 100000      // 200(미터) * 500개

int M;
vector<pair<int,int>> nthlons;

const int n = 200;
vector<pair<int,int>> adj[(n+1)*2];

int d[(n+1)*2];

void di(){
    for(int i = 0; i < 401; ++i)    d[i] = INF;
    
    priority_queue<pair<int,int>> q;
    d[401] = 0;
    q.push({0, 401});
    while(!q.empty()){
        auto& a = q.top();
        int cost = -a.first;
        int u = a.second;
        q.pop();
        
        if(cost > d[u]) continue;
        
        for(auto& e : adj[u]){
            int v = e.second;
            int d1 = cost + e.first;
            if(d1 < d[v]){
                d[v] = d1;
                q.push({-d1, v});
            }
        }
    }
}

int main(){
    int C;
    scanf("%d",&C);
    while(C--){
        scanf("%d", &M);
        for(int i = 0; i < M; ++i){
            int a,b;
            scanf("%d %d",&a,&b);
            nthlons.push_back({a,b});
        }
        
        for(auto& e : nthlons){
            int d = e.first - e.second;
            adj[401].push_back({e.first, n+d}); // (간선, 정점)
        }
        
        for(int d = -200; d <= 200; ++d){
            for(auto& e : nthlons){
                int d1 = d + e.first - e.second;
                if(abs(d1) > 200)   continue;
                adj[d+n].push_back({e.first, d1+n});
            }
        }
        
        di();
        
        if(d[n] == INF) printf("IMPOSSIBLE\n");
        else            printf("%d\n", d[n]);
        
        nthlons.clear();
        for(int i = 0; i < 402; ++i)    adj[i].clear();
    }
    return 0;
}

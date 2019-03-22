/*
 이분 매칭을 network flow로 푸는 기본 문제
 시작점s, 도착점t를 만들어 capacity가 1로 되게 서로 연결, 가축->축사도 1이 되게 연결
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#define INF 1000

#define MAX_N   200
#define MAX_M   200

#define MAX_V   (MAX_N+MAX_M+2)

int N, M;

int flow[MAX_V][MAX_V];
int capacity[MAX_V][MAX_V];

int s = 0, t = MAX_V-1;

int networkFlow(){
    int totalFlow = 0;
    memset(flow, 0, sizeof(flow));
    while(true){
        vector<int> parent(MAX_V, -1);
        
        queue<int> q;
        q.push(s);
        parent[s] = s;
        while(!q.empty() && parent[t] == -1){
            int u = q.front();  q.pop();
            for(int v = 0; v < MAX_V; ++v){
                if(capacity[u][v] - flow[u][v] > 0 && parent[v] == -1){
                    q.push(v);
                    parent[v] = u;
                }
            }
        }
        
        if(parent[t] == -1) break;
        
        int amount = INF;
        for(int p = t; p != s; p = parent[p])
            amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
        
        for(int p = t; p != s; p = parent[p]){
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }
        
        totalFlow += amount;
    }
    
    return totalFlow;
}

int main(){
    scanf("%d %d", &N, &M);
    
    for(int i = 1; i <= N; ++i){
        int si;
        scanf("%d", &si);
        for(int j = 0; j < si; ++j){
            int want;
            scanf("%d", &want);
            capacity[i][want+MAX_N] = 1;
        }
        capacity[s][i] = 1;
    }
    
    for(int i = 1; i <= M; ++i)
        capacity[i+MAX_N][t] = 1;
    
    printf("%d", networkFlow());
    
    return 0;
}

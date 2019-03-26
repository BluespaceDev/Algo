#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_N   (12+1)
#define MAX_M   100+1
#define SIZE    (MAX_N+MAX_M+2)
#define INF     1001

int N, M;
int player[MAX_N];
int s,t;

int c[SIZE][SIZE], f[SIZE][SIZE];
int q[SIZE], wq, rq;
int parent[SIZE];
int totalFlow;

int networkFlow(int source, int sink, int size){
    while(true){
        wq = rq = 0;
        memset(parent, -1, sizeof(parent));
        
        q[wq++] = source;
        parent[source] = source;
        while(wq > rq && parent[sink] == -1){
            int u = q[rq++];
            for(int v = 0; v < size; ++v){
                if(c[u][v]-f[u][v] > 0 && parent[v] == -1){
                    q[wq++] = v;
                    parent[v] = u;
                }
            }
        }
        if(parent[sink] == -1) break;
        
        int min_flow = INF;
        for(int i = sink; parent[i] != i; i = parent[i]){
            min_flow = min(min_flow, c[parent[i]][i]-f[parent[i]][i]);
        }
        
        for(int i = sink; parent[i] != i; i = parent[i]){
            f[parent[i]][i] += min_flow;
            f[i][parent[i]] -= min_flow;
        }
        
        totalFlow += min_flow;
    }
    return totalFlow;
}

// totalWins으로 0번 선수가 이길 수 있는지?
bool isWin(int totalWins){
    // 0번 아닌 플레이어의 win이 total보다는 작아야함 (0번이 total)
    for(int i = 1; i < N; ++i)
        if(player[i] >= totalWins)
            return false;
    
    c[0][t] = totalWins - player[0];
    for(int i = 1; i < N; ++i){
        c[i][t] = totalWins - 1 - player[i];
    }
    
    return networkFlow(s, t, t+1) == M;  // flow가 경기수랑 같아야 성립
}

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        scanf("%d %d", &N, &M);
        s = N+M;
        t = s+1;
        for(int i = 0; i < N; ++i){
            scanf("%d", &player[i]);
        }
        for(int i = 0; i < M; ++i){
            int a,b;
            scanf("%d %d",&a,&b);
            c[s][N+i] = 1;    // source -> a
            c[N+i][a] = 1;      // 1인 이유는 같은 경기수라도 다른 노드로 추가되기 떄문
            c[N+i][b] = 1;
        }
        
        int ans = -1;
        for(int w = player[0]; w <= player[0]+M; ++w){
            if(isWin(w)){
                ans = w;
                break;
            }
        }
        
        bool check = true;
        for(int i = 1; i < N; ++i)
            if(f[i][t]+player[i] >= f[0][t]+player[0]){
                check = false;
                break;
            }
        
        printf("%d\n", check ? ans : -1);
        
        totalFlow = 0;
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
    }
    return 0;
}

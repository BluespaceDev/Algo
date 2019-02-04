// CNF 절 구성하기
//(y1 && x2) || (x1 && y2)
//(y1 || x1) && (y1 || y2) (x2 || x1) (x2 || y2)
//~x -> y 식으로 풀어야함

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_N   1000
#define MAX_M   1000
#define SIZE    (MAX_N+MAX_M)

int T;
int n,m,k;
int N;

vector<int> adj[SIZE*2+1];

int dfs_num[SIZE*2+1];
int dfs_low[SIZE*2+1];
int scc_stack[SIZE*2], s_top;
int dfs_count;
bool scc_visited[SIZE*2+1];
int sccId[SIZE*2+1], scc_count;

inline int NOT(int x){
    return x>N ? x-N : x+N;
}

void scc(int u){
    dfs_low[u] = dfs_num[u] = ++dfs_count;
    scc_stack[s_top++] = u;
    for(int v : adj[u]){
        if(dfs_num[v] == 0)
            scc(v);
        
        if(!scc_visited[v])
            if(dfs_low[u] > dfs_low[v]) dfs_low[u] = dfs_low[v];
    }

    if(dfs_low[u] == dfs_num[u]){
        scc_count++;
        while(1){
            int v = scc_stack[--s_top];
            scc_visited[v] = true;
            sccId[v] = scc_count;
            if (u == v) break;
        }
    }
}

int main() {
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d", &n,&m,&k);
        N = n+m;
        while(k--){
            int a,b,c,d;
            scanf("%d %d %d %d", &a,&b,&c,&d);
            if(a == c && b == d)    continue;

            int y1,y2,x1,x2;
            if(a < c){
                x1 = b+n;
                x2 = d+n;
            } else {
                x1 = b+n+N;
                x2 = d+n+N;
            }
            if(b < d){
                y1 = a;
                y2 = c;
            } else {
                y1 = a+N;
                y2 = c+N;
            }
            
            if(a == c)
                adj[NOT(y1)].push_back(y1);
            else if(b == d)
                adj[NOT(x1)].push_back(x1);
            else{
                adj[NOT(y1)].push_back(x1);
                adj[NOT(x1)].push_back(y1);
                adj[NOT(y1)].push_back(y2);
                adj[NOT(y2)].push_back(y1);
                adj[NOT(x2)].push_back(x1);
                adj[NOT(x1)].push_back(x2);
                adj[NOT(x2)].push_back(y2);
                adj[NOT(y2)].push_back(x2);
            }
        }
        
        for (int i = 1; i <= 2 * N; i++)
            if (dfs_num[i] == 0)
                scc(i);
        
        bool vaild = true;
        for (int i = 1; i <= N; i++) {
            if (sccId[i] == sccId[i + N]) {
                vaild = false;
                break;
            }
        }
        printf("%s\n",vaild?"Yes":"No");
        
        memset(dfs_low,0,sizeof(dfs_low));
        memset(dfs_num,0,sizeof(dfs_num));
        memset(scc_visited,false,sizeof(scc_visited));
        scc_count = dfs_count = 0;
        for(int i = 1; i <= N*2; ++i)
            adj[i].clear();
    }
    return 0;
}

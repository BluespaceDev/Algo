#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_N   100
#define SIZE    (MAX_N*2)

int T;
int n,N;

vector<int> adj[SIZE*2];
pair<int,int> meetings[SIZE];

int dfs_num[SIZE*2];
int dfs_low[SIZE*2];
int scc_stack[SIZE*2], s_top;
int dfs_count;
bool scc_visited[SIZE*2];
int sccId[SIZE*2], scc_count;
int dag[SIZE*2], dag_top;
int var[SIZE*2];

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
            dag[dag_top++] = v;
            if (u == v) break;
        }
    }
}

bool disjoint(pair<int,int>& a, pair<int,int>& b){
    return a.second <= b.first || b.second <= a.first;
}

int main() {
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        N = n*2;
        for(int i = 0; i < n; ++i){
            int a,b,c,d;
            scanf("%d %d %d %d",&a,&b,&c,&d);
            meetings[i] = make_pair(a,b);
            meetings[i+n] = make_pair(c,d);
        }
        
        for(int i = 0; i < n; ++i){
            adj[i+N].push_back(i+n);
            adj[i+n+N].push_back(i);
        }
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < i; ++j){
                if(!disjoint(meetings[i], meetings[j])){
                    adj[i].push_back(j+N);  // ~a->b 가 아닌 것은 a,b가 필수가 아니기 때문
                    adj[j].push_back(i+N);  // 만약 a를 선택했다면 b를 선택하지 않아야 하는 조건
                }
            }
        }
        
        for (int i = 0; i < 2 * N; i++)
            if (dfs_num[i] == 0)
                scc(i);
        
        bool vaild = true;
        for (int i = 0; i < N; i++) {
            if (sccId[i] == sccId[i + N]) {
                vaild = false;
                break;
            }
        }
        
        if(vaild){
            printf("POSSIBLE\n");
            memset(var,-1,sizeof(var));
            for(int i = dag_top-1; i >= 0; --i){
                int u = dag[i] < N ? dag[i] : dag[i]-N;
                if(var[u] == -1)
                    var[u] = dag[i] < N ? 0 : 1;
            }
            for(int i = 0; i < n; ++i){
                auto meeting = var[i] ? meetings[i] : meetings[i+n];
                printf("%d %d\n", meeting.first, meeting.second);
            }
        }else{
            printf("IMPOSSIBLE\n");
        }
        
        memset(dfs_low,0,sizeof(dfs_low));
        memset(dfs_num,0,sizeof(dfs_num));
        memset(scc_visited,false,sizeof(scc_visited));
        scc_count = dfs_count = dag_top = 0;
        for(int i = 0; i < N*2; ++i)
            adj[i].clear();
    }
    return 0;
}

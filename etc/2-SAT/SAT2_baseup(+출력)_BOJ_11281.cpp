// CNF 1개의 절에서 false->true 라는 성질 사용하여 그래프 구성
// a->~a 이런 순환이 있을 경우 모순
// 홀수 = true, 짝수 = false

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N   10000

int N, M;

vector<int> adj[MAX_N*2+1];
int dfs_num[MAX_N*2+1];
int dfs_low[MAX_N*2+1];
int dfs_count = 1;
bool scc_visited[MAX_N*2+1];
int stack[MAX_N*2], s_top;
int dag[MAX_N*2], dag_top;
int var[MAX_N+1];

void tarjanSCC(int u){
    dfs_low[u] = dfs_num[u] = dfs_count++;
    scc_visited[u] = true;
    stack[s_top++] = u;
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if(!dfs_num[v])
            tarjanSCC(v);
        
        if(scc_visited[v])  // SCC 방문점 - cross edge일때 고려, 이미 SCC로 구성된 되있는 곳 방문하면 갱신안함
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    // SCC 구성
    if(dfs_low[u] == dfs_num[u]){
        while(1){
            int v = stack[--s_top];
            scc_visited[v] = false;
            dag[dag_top++] = v;
            if(u == v)  break;
        }
    }
}

int main(){
    scanf("%d %d\n", &N, &M);
    for(int i = 0, a, b; i < M; ++i){
        scanf("%d %d\n", &a, &b);
        
        a = a > 0 ? a * 2 - 1 : -a * 2;
        b = b > 0 ? b * 2 - 1 : -b * 2;
        
        adj[a+(a%2 ? 1 : -1)].push_back(b);  // ~a -> b
        adj[b+(b%2 ? 1 : -1)].push_back(a);  // ~b -> a
    }
    
    int N2 = N*2;
    
    for(int i = 1; i <= N2; ++i)
        if(dfs_num[i] == 0)
            tarjanSCC(i);
    
    for(int i = 1; i <= N2; i+=2){
        if(dfs_low[i] == dfs_low[i+1]){
            printf("0\n");
            return 0;
        }
    }
    
    printf("1\n");
    
    // SCC에서 생성된 DAG 순서대로
    memset(var,-1,sizeof(var));
    for(int i = N2-1, u; i >= 0; --i){
        u = (dag[i]+1)/2;
        if(var[u] == -1)    var[u] = !(dag[i]%2);   // 반대로(false)로 세팅.. ~a 이면 a로, a이면 ~a로 => 그래프 만들때 f->t로 만들어서, t->f 인 경로는 없음
    }
    
    for(int i = 1; i <= N; ++i)
        printf("%d ", var[i]);
    
    return 0;
}

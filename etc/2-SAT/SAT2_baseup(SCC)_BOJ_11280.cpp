// CNF 1개의 절에서 false->true 라는 성질 사용하여 그래프 구성
// a->~a 이런 순환이 있을 경우 모순
// 홀수 = true, 짝수 = false

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N   10000

int N, M;

vector<int> adj[MAX_N*2+1];
int dfs_num[MAX_N*2+1];
int dfs_low[MAX_N*2+1];
int dfs_count = 1;
bool visited[MAX_N*2+1];
vector<int> scc;

void tarjanSCC(int u){
    dfs_low[u] = dfs_num[u] = dfs_count++;
    visited[u] = true;
    scc.push_back(u);
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if(!dfs_num[v])
            tarjanSCC(v);
        
        if(visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if(dfs_low[u] == dfs_num[u]){
        while(1){
            int v = scc.back(); scc.pop_back();
            visited[v] = false;
            if (u == v) break;
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
    
    N *= 2;
    
    for(int i = 1; i <= N; ++i)
        if(!dfs_num[i])
            tarjanSCC(i);
    
    bool vaild = true;
    for(int i = 1; i <= N; i+=2){
        if(dfs_low[i] == dfs_low[i+1]){
            vaild = false;
            break;
        }
    }
    
    printf("%d\n", vaild);
    
    return 0;
}

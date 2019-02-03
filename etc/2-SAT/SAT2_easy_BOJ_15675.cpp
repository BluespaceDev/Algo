// 보석 : y 지나면 x는 지나면 안됨, 반대도 성립, 한번 지난 곳은 지날 수 없음
// 위치 : y 지나면 x는 꼭 지나가야됨, y를 안지나면 x도 지나면 안됨
// #define SIZE MAX_N+MAX_M 이 안먹힘

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N   1000
#define MAX_M   1000

int n, m;
char s[MAX_N+1];

vector<int> adj[4000];
int dfs_num[4000];
int dfs_low[4000];
int dfs_count;
bool scc_visited[4000];
int stack[4000], s_top;

void scc(int u){
    dfs_num[u] = dfs_low[u] = ++dfs_count;
    stack[s_top++] = u;
    for(int v : adj[u]){
        if(dfs_num[v] == 0)
            scc(v);
        if(!scc_visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if(dfs_num[u] == dfs_low[u]){
        while(1){
            int v = stack[--s_top];
            scc_visited[v] = true;
            if(u == v)  break;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    int N = n+m;
    for(int i = 0, y; i < n; ++i){
        scanf("%s", s);
        y = i + m;
        for(int x = 0; x < m; ++x){
            if(s[x] == '*'){
                adj[y+N].push_back(x);
                adj[x+N].push_back(y);
                adj[x].push_back(y+N);
                adj[y].push_back(x+N);
            } else if(s[x] == '#'){
                adj[y].push_back(x);
                adj[x].push_back(y);
                adj[y+N].push_back(x+N);
                adj[x+N].push_back(y+N);
            }
        }
    }
    
    for(int i = 0; i < N*2; ++i)
        if(dfs_num[i] == 0)
            scc(i);
    
    for(int i = 0; i < N; ++i)
        if(dfs_low[i] == dfs_low[i+N]){
            printf("0");
            return 0;
        }
    
    printf("1");
    return 0;
}

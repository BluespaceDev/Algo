// 방의 상태에 따라 CNF설정
// 각 절은 방이고 조건은 key조합

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_N   100000

int n,m;
bool room[MAX_N+1];
int room_key[MAX_N+1][2];

vector<int> adj[MAX_N*2];

int dfs_num[MAX_N*2];
int dfs_low[MAX_N*2];
int scc_stack[MAX_N*2], s_top;
int dfs_count;
bool scc_visited[MAX_N*2];
bool visited[MAX_N*2];
int sccId[MAX_N*2], scc_count;

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
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &room[i]);
    memset(room_key,-1,sizeof(room_key));
    for (int i = 0, k,x; i < m; i++) {
        scanf("%d", &k);
        while (k--) {
            scanf("%d", &x);
            if(room_key[x][0] == -1)
                room_key[x][0] = i;
            else
                room_key[x][1] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        int pu = room_key[i][0], nu = pu + m, pv = room_key[i][1], nv = pv + m;
        if (room[i]) {
            adj[pu].push_back(pv);
            adj[pv].push_back(pu);
            adj[nu].push_back(nv);
            adj[nv].push_back(nu);
        }
        else {
            adj[pu].push_back(nv);
            adj[pv].push_back(nu);
            adj[nu].push_back(pv);
            adj[nv].push_back(pu);
        }
    }
    
    for (int i = 0; i < 2 * m; i++)
        if (dfs_num[i] == 0)
            scc(i);
        
    
    for (int i = 0; i < m; i++) {
        if (sccId[i] == sccId[i + m]) {
            puts("0");
            return 0;
        }
    }
    puts("1");
    return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;

vector<int> adj[MAX + 1];
int depth[MAX + 1];
int parent[MAX + 1];
int p[MAX + 1][18];

void dfs(int u, int dep){
    depth[u] = dep;
    for (int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if (parent[v] == -1){
            parent[v] = u;
            dfs(v, dep + 1);
        }
    }
}

int lca(int u, int v){
    if (depth[u] < depth[v])
        swap(u, v);
    // 더 깊은 정점 u의 depth 거리 계산, 1,2,4,8,u,16 이면 8을 선택
    int log = 1;
    for (log = 1; (1 << log) <= depth[u]; log++);
    log -= 1;
    // u와 v의 depth를 같게 만듬. u를 큰거부터 작은 단위로 끌어 올림
    for (int i = log; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = p[u][i];
        }
    }
    
    if (u == v)
        return u;
    
    // u,v를 올리면서 같은 부모 찾기
    for (int i = log; i >= 0; i--) {
        if (p[u][i] != 0 && p[u][i] != p[v][i]) {
            u = p[u][i];
            v = p[v][i];
        }
    }
    return p[u][0];
}

int main()
{
    int n;
    scanf("%d", &n);
    
    int u, v;
    for (int i = 0; i < n - 1; ++i){
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(parent, -1, sizeof(parent));
    parent[1] = 0;
    dfs(1, 1);
    for (int i = 1; i <= n; ++i)
        p[i][0] = parent[i];
    for (int j = 1; (1 << j) < n; j++) {
        for (int i = 1; i <= n; i++) {
            if (p[i][j - 1] != 0) {
                p[i][j] = p[p[i][j - 1]][j - 1];
            }
        }
    }
    
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i){
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u, v));
    }
    
    return 0;
}

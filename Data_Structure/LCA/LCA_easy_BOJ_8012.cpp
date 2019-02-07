// 깊이가 이동거리가 됨.
// 공통부분이 중복되므로 마이너스 하면 구할 수 있음

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 30000;

vector<int> adj[MAX + 1];
int depth[MAX + 1];
int p[MAX + 1][18];

void dfs(int u){
    for (int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if (p[v][0] == 0){
            p[v][0] = u;
            depth[v] = depth[u]+1;
            dfs(v);
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
        if (p[u][i] != -1 && p[u][i] != p[v][i]) {
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
    
    p[1][0] = -1;
    dfs(1);
    for (int j = 0; j < 17; j++) {
        for (int i = 1; i <= n; i++) {
            if (p[i][j] != -1) {
                p[i][j+1] = p[p[i][j]][j];
            }
        }
    }
    
    int m;
    scanf("%d", &m);
    int ans = 0;
    u = 1;
    while(m--){
        scanf("%d", &v);
        int cp = lca(u, v);
        ans += depth[u] + depth[v] - 2*depth[cp];
        u = v;
    }
    
    printf("%d", ans);
    
    return 0;
}

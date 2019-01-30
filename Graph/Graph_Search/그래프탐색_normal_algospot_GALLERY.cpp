// 정점에 대해 state가 3개가 생김
// 루트일때도 검사해야됨

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_G   1001

#define UNWATCHED   0
#define WATCHED     1
#define INSTALLED   2

int C;
int G, H;

vector<int> adj[MAX_G];
bool visited[MAX_G];
int cover[MAX_G];
int ans;

void dfs(int u){
    visited[u] = true;
    bool install = false;
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if(!visited[v]){
            dfs(v);
            if(cover[v] == UNWATCHED)
                install = true;
            else if(cover[v] == INSTALLED)
                cover[u] = WATCHED;
        }
    }

    if(install){
        cover[u] = INSTALLED;
        ++ans;
    }
}

int main(){
    scanf("%d\n", &C);
    while(C--){
        scanf("%d %d\n",&G, &H);
        for(int i = 0, a, b; i < H; ++i){
            scanf("%d %d\n", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        ans = 0;
        for(int i = 0; i < G; ++i)
            if(!visited[i]){
                dfs(i);
                if(cover[i] == UNWATCHED)
                    ++ans;
            }

        printf("%d\n", ans);

        for(int i = 0; i < G; ++i)
            adj[i].clear();
        memset(visited,false,sizeof(visited));
        memset(cover,UNWATCHED,sizeof(cover));
    }
    return 0;
}

// 이분 그래프 검사 기본 문제 - UVa 10004

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_N   200

int n, l;
vector<int> adj[MAX_N];

int q[MAX_N], wq, rq;
int color[MAX_N];

int main(){
    while(true){
        scanf("%d\n", &n);
        if(n == 0)  break;
        
        scanf("%d\n", &l);
        int a,b;
        for(int i = 0; i < l; ++i){
            scanf("%d %d\n", &a,&b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        memset(color,-1,sizeof(color));
        
        wq = rq = 0;
        q[wq++] = 0;
        color[0] = 0;
        bool isBipartite = true;
        while(wq > rq){
            int u = q[rq++];
            for(int i = 0; i < adj[u].size(); ++i){
                int v = adj[u][i];
                if(color[v] == -1){
                    q[wq++] = v;
                    color[v] = 1 - color[u];    // color 반전
                }
                else if(color[v] == color[u]){
                    isBipartite = false;
                    wq = rq = 0;
                    break;
                }
            }
        }
        if (isBipartite)
            printf("BICOLORABLE.\n");
        else
            printf("NOT BICOLORABLE.\n");
        
        for(int i = 0; i < n; ++i)
            adj[i].clear();
    }
    return 0;
}

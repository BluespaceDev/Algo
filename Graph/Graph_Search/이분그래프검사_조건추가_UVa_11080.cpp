// 최소 가드수 구하기
// 연결된 간선 중 하나에 가드를 설치해야되는데,
// 최소 가드수를 구해야되기 때문에, 양쪽중 하나를 잘 선택해야됨

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_V   200

int v, e;

vector<int> adj[MAX_V];
int color[MAX_V];
int q[MAX_V], wq, rq;

int main(){
    int T;
    scanf("%d\n", &T);
    while(T--){
        scanf("%d %d\n", &v, &e);
        int a,b;
        for(int i = 0; i < e; ++i){
            scanf("%d %d\n", &a, &b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        int min_guard = 0;
        memset(color,-1,sizeof(color));
        wq = rq = 0;
        for(int i = 0; i < v && min_guard != -1; ++i){
            if(color[i] != -1)  continue;
            
            int v_count = 1;
            int guard = 1;
            color[i] = 1;
            q[wq++] = i;
            while(wq > rq){
                int u = q[rq++];
                
                for(int j = 0; j < adj[u].size(); ++j){
                    int k = adj[u][j];
                    if(color[k] == -1){
                        q[wq++] = k;
                        color[k] = 1 - color[u];
                        if(color[k] == 1)
                            guard++;
                        v_count++;
                    }
                    else if(color[k] == color[u]){
                        min_guard = -1;
                        rq = wq;
                        break;
                    }
                }
            }
            
            if(min_guard != -1){
                min_guard += (guard == v_count) ? guard : min(guard, v_count-guard);
            }
        }
        
        printf("ans (%d)\n", min_guard);
        
        for(int i = 0; i < v; ++i)
            adj[i].clear();
    }
    return 0;
}

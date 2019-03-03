/*
 답 = 상한-하한 이 최소가 되는 값, 변수가 2개일때 하나를 고정시키는 방법이 편함
 하한을 고정시켰을때 최소 상한을 구하는 방식으로 품
 */
#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N   2000
#define INF     10000000

using namespace std;

int N, M;
vector<pair<int,pair<int,int>>> edges;
int group[MAX_N];

int find(int u){
    return group[u] == u ? u : group[u] = find(group[u]);
}
void merge(int u, int v){
    u = find(u);
    v = find(v);
    group[u] = v;
}
bool isConnected(int u, int v){
    return find(u) == find(v);
}
int kruscal(int low){
    for(int i = 0; i < N; ++i)
        group[i] = i;

    for(auto& e : edges){
        int u = e.second.first;
        int v = e.second.second;
        int w = e.first;
        if(w < low) continue;
        merge(u, v);
        if(isConnected(0,N-1))  return w;
    }
    return INF;
}

int main(){
    int C;  scanf("%d",&C);
    while(C--){
        scanf("%d %d", &N, &M);
        for(int i = 0; i < M; ++i){
            int a,b,w;
            scanf("%d %d %d", &a, &b, &w);
            edges.push_back({w, {a,b}});
        }
        sort(edges.begin(), edges.end());
        
        int ans = INF;
        for(int w = edges[0].first; w <= edges[M-1].first; ++w){
            ans = min(ans, kruscal(w) - w);
        }
        printf("%d\n", ans);
        edges.clear();
    }
    return 0;
}

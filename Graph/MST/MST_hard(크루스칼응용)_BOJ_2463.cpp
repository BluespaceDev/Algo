// 문제에 대한 확실한 이해 필요
// 정점이 서로 끊어 질때 간선은 작은 간선
// 모든 간선에 대해 끊어진 간선은 다 같아 g_size를 곱함

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N   100000
#define MOD     1000000000

int N, M;
vector<pair<int,pair<int,int>>> edges;

long long total_w;

int g[MAX_N+1], g_size[MAX_N+1];

int find(int u){ return g[u] == u ? u : g[u] = find(g[u]);}
void merge(int u, int v){
    g[u] = v;
    g_size[v] += g_size[u];
}

int main(){
    scanf("%d %d", &N, &M);
    while(M--){
        int a,b,w;
        scanf("%d %d %d", &a, &b, &w);
        edges.push_back({-w,{a,b}});
        total_w += w;
    }
    
    int ans = 0;
    for(int i = 1; i <= N; ++i) {g[i] = i; g_size[i] = 1;}
    sort(edges.begin(), edges.end());
    for(auto e : edges){
        auto v = e.second;
        int u1 = find(v.first);
        int v1 = find(v.second);
        if(g[u1] != g[v1]){
            ans += ((total_w * g_size[u1] * g_size[v1])%MOD);
            ans %= MOD;
            merge(u1, v1);
        }
        total_w += e.first;
    }
    
    printf("%d", ans);
    
    return 0;
}

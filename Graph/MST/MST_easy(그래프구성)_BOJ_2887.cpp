// 인접한 간선만 생각해야됨 - 값이 1,2,3,4 로 있을때 1-4를 연결할 필요는 없음. (메모리초과)
// 실수 - 그래프 구성할때 i가 아니라 각 x,y,z 간선 v에 짝에 맞춰서 설정 (정렬시 second값이 흐트러짐) (fail원인)
// C++14 부터 람다식에 오토지원 sort(y, y+V, [](auto& a, auto& b) -> bool{return a.y < b.y;}); (컴파일에러)

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_V   100000

int V;
vector<pair<long long, pair<int,int>>> edges;

pair<int,int> x[MAX_V], y[MAX_V], z[MAX_V];

int unionGroup[MAX_V];

int find(int i){
    while(unionGroup[i] != i)   i = unionGroup[i] = unionGroup[unionGroup[i]];
    return i;
}
void unionSet(int u, int v){
    unionGroup[find(u)] = find(v);
}
bool isUnion(int u, int v){
    return find(u) == find(v);
}

int main(){
    scanf("%d", &V);
    for(int i = 0; i < V; ++i){
        scanf("%d %d %d", &x[i].first, &y[i].first, &z[i].first);
        x[i].second = y[i].second = z[i].second = i;
    }
    
    sort(x, x+V);
    sort(y, y+V);
    sort(z, z+V);
    for(int i = 1; i < V; ++i){
        edges.push_back(make_pair(x[i].first-x[i-1].first, make_pair(x[i].second, x[i-1].second)));
        edges.push_back(make_pair(y[i].first-y[i-1].first, make_pair(y[i].second, y[i-1].second)));
        edges.push_back(make_pair(z[i].first-z[i-1].first, make_pair(z[i].second, z[i-1].second)));
    }
    
    long long mst_cost = 0;
    sort(edges.begin(),edges.end());
    for(int i = 0; i < V; ++i)
        unionGroup[i] = i;
    for(int i = 0; i < edges.size(); ++i){
        auto e = edges[i].second;
        if(!isUnion(e.first, e.second)){
            mst_cost += edges[i].first;
            unionSet(e.first, e.second);
        }
    }
    
    printf("%lld\n", mst_cost);
    
    return 0;
}

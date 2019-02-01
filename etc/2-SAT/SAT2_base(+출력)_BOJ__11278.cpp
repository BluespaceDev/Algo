// 무식하게 다 해보기 (부분집합 모두) 2^n
// 변수 하나 바꿔가면서 CNF 다 돌림
// +출력

#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>

using namespace std;

#define MAX_N   20+1
#define MAX_M   100

#define FALSE   -1
#define TRUE    1

int N, M;
int var[MAX_N];
pair<int, int> clauses[MAX_M];
int t[2] = {FALSE, TRUE};

bool dfs(int u){
    if(u > N)   return 0;
    
    for(int i = 0; i < 2; ++i){
        var[u] = t[i];
        bool isContradiction = false;
        for(int j = 0; j < M; ++j){
            int a = abs(clauses[j].first);
            int b = abs(clauses[j].second);
            if(var[a] * clauses[j].first < 0 && var[b] * clauses[j].second < 0){
                isContradiction = true;
                break;
            }
        }
        if(!isContradiction || dfs(u+1)) return true;
    }
    return false;
}

int main(){
    scanf("%d %d\n", &N, &M);
    for(int i = 0,a,b; i < M; ++i){
        scanf("%d %d\n", &a, &b);
        clauses[i] = make_pair(a,b);
    }
    
    memset(var, -1, sizeof(var));
    
    if(dfs(1)){
        printf("1\n");
        for(int i = 1; i <= N; ++i){
            printf("%d ", var[i] == FALSE ? 0 : 1);
        }
    }
    else
        printf("0\n");
    
    return 0;
}

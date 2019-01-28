// 오일러서킷, 오일러트레일 둘다 가능
// 그래프 만들기 - 첫단어, 끝단어가 정점이고 단어가 간선으로 구성
// reverse 안하면 오답

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int C, N;
char words[100][11];
vector<pair<int,int>> adj[26];
int indegree[26];
int outdegree[26];
vector<int> ans;

void dfs(int u){
    for(int i = 0; i < adj[u].size(); ++i){
        if(adj[u][i].first == -1)   continue;
        int v = adj[u][i].first;
        adj[u][i].first = -1;
        dfs(v);
        ans.push_back(adj[u][i].second);
    }
}

int main(){
    scanf("%d\n", &C);
    while(C--){
        scanf("%d\n", &N);
        for(int i = 0; i < N; ++i){
            scanf("%s\n", words[i]);
            
            int last;
            for(last = 0; words[i][last] != 0; ++last);
            
            int in = words[i][last-1]-'a';
            int out = words[i][0]-'a';
            indegree[in]++;
            outdegree[out]++;
            adj[out].push_back(make_pair(in, i));
        }
        
        // 검사
        bool ok = true;
        int s = -1, e = -1;
        for(int i = 0; i < 26; ++i)
            if(outdegree[i] != indegree[i]){
                if(outdegree[i] == indegree[i] + 1){
                    if (s < 0)  s = i;
                    else{
                        ok = false;
                        break;
                    }
                } else if(outdegree[i] + 1 == indegree[i]){
                    if (e < 0)  e = i;
                    else{
                        ok = false;
                        break;
                    }
                } else {
                    ok = false;
                    break;
                }
            }
        
        // 실행
        if(ok){
            if (s < 0)  s = adj[words[0][0]-'a'][0].first;  // 첫번째 단어부터 시작
            dfs(s);
            reverse(ans.begin(), ans.end());
            for(int i = 0; i < ans.size(); ++i)
                printf("%s ", words[ans[i]]);
        }else{
            printf("IMPOSSIBLE");
        }
        printf("\n");

        for(int i = 0; i < 26; ++i)
            adj[i].clear();
        memset(indegree, 0, sizeof(indegree));
        memset(outdegree, 0, sizeof(outdegree));
        ans.clear();
    }
    return 0;
}

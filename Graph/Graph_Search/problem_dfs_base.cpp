//https://www.acmicpc.net/problem/16724

#include <stdio.h>

#define MAX_N   1000
#define MAX_M   1000

#define EXPLORED    1
#define VISITED     2

int n, m;
char map[MAX_N][MAX_M+1];

int state[MAX_N][MAX_M];

int group;

void dfs(int y, int x){
    if (state[y][x] == EXPLORED){
        ++group;
        return;
    }
    if (!state[y][x]) {
        state[y][x] = EXPLORED;
        
        if (map[y][x] == 'D')
            dfs(y+1,x);
        else if (map[y][x] == 'U')
            dfs(y-1,x);
        else if (map[y][x] == 'R')
            dfs(y,x+1);
        else
            dfs(y,x-1);
        
        state[y][x] = VISITED;
    }
}

int main(){
    scanf("%d %d\n", &n, &m);
    
    for (int i = 0; i < n; ++i)
        scanf("%s\n",map[i]);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!state[i][j]) {
                dfs(i, j);
            }
    
    printf("%d\n", group);
    
    return 0;
}

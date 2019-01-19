//
//  hungarian_boj_14216.cpp
//  Algorithms
//
//  Created by Hongseob Shin on 19/01/2019.
//  Copyright © 2019 Hongseob Shin. All rights reserved.
//

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_C   10000
#define INF     MAX_C + 1
#define MAX_N   500

int lx[MAX_N], ly[MAX_N];
bool S[MAX_N], T[MAX_N];    // Tree
int xy[MAX_N], yx[MAX_N];

int slack[MAX_N], slackx[MAX_N];
int prevx[MAX_N];

int q[MAX_N], wq, rq;

int max_match;

int n;
int cost[MAX_N][MAX_N];

void init_labels(){
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            lx[i] = max(lx[i], cost[i][j]);
}

void update_labels(){
    int delta = INF;
    
    // T에 없는 slack 으로 delta 찾기
    for(int j = 0; j < n; ++j)
        if(!T[j])
            delta = min(delta,slack[j]);
    
    for(int i = 0; i < n; ++i)
        if(S[i])
            lx[i] -= delta;
    for(int j = 0; j < n; ++j)
        if(T[j])
            ly[j] += delta;
    
    for(int j = 0; j < n; ++j)
        if(!T[j])
            slack[j] -= delta;
}

void add_tree(int x, int prev_x){
    S[x] = true;
    prevx[x] = prev_x;
    
    // 새로운 점 x에 대해 slack update할 부분 있으면 update
    for(int j = 0; j < n; ++j){
        if(lx[x]+ly[j]-cost[x][j] < slack[j]){
            slack[j] = lx[x]+ly[j]-cost[x][j];
            slackx[j] = x;
        }
    }
}

void argument(){
    if(max_match == n)  return;
    
    memset(S,false,sizeof(S));
    memset(T,false,sizeof(T));
    memset(prevx, -1, sizeof(prevx));
    
    wq = rq = 0;
    
    // find root of tree
    int root;
    for(root = 0; root < n; ++root)
        if(xy[root] == -1){
            S[root] = true;
            prevx[root] = -2;
            q[wq++] = root;
            break;
        }
    
    for(int j = 0; j < n; ++j){
        slack[j] = lx[root]+ly[j]-cost[root][j];
        slackx[j] = root;
    }
    
    int x, y;
    while(true){
        // build tree in equality graph
        while(rq < wq){
            x = q[rq++];
            for(y = 0; y < n; ++y){
                if(lx[x]+ly[y] == cost[x][y] && !T[y]){
                    // y is exposed -> find argument path
                    if (yx[y] == -1){
                        wq = rq = 0;
                        break;
                    }
                    
                    T[y] = true;
                    q[wq++] = yx[y];
                    add_tree(yx[y], x);
                }
            }
        }
        if(y < n)   break;
        
        update_labels();
        
        //라벨 업데이트 했으니, J_gl(S)에서 트리 밖의(!T) tree 구축
        for(y = 0; y < n; ++y){
            if(!T[y] && slack[y] == 0){
                if(yx[y] == -1){
                    x = slackx[y];
                    break;
                }
                else {
                    T[y] = true;
                    
                    if(!S[yx[y]]){
                        q[wq++] = yx[y];
                        add_tree(yx[y],slackx[y]);
                    }
                }
            }
        }
        if(y < n)   break;
    }
    
    //argument path 맞으면 matching
    if(y < n){
        ++max_match;
        for(int cx = x, cy = y, ty; cx != -2; cx = prevx[cx], cy = ty){
            ty = xy[cx];
            xy[cx] = cy;
            yx[cy] = cx;
        }
        argument();
    }
}

int hungarian(){
    max_match = 0;
    
    memset(xy,-1,sizeof(xy));
    memset(yx,-1,sizeof(yx));
    
    init_labels();
    argument();
    
    int ret = 0;
    for(int x = 0; x < n; ++x)
        ret += cost[x][xy[x]];
    return ret;
}

int main(){
    scanf("%d\n", &n);
    int max_cost = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j){
            scanf("%d", &cost[i][j]);
            max_cost = max(max_cost, cost[i][j]);
        }
    
    // min -> max로 변환 (헝가리안은 max를 찾기 때문)
    for(int i = 0 ; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cost[i][j] = max_cost - cost[i][j];

    printf("%d\n", max_cost*n - hungarian());
    return 0;
}

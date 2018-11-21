//
//  union_find2.cpp
//  Algorithms
//
//  Created by Hongseob Shin on 2018. 11. 14..
//  Copyright © 2018년 Hongseob Shin. All rights reserved.
//
// union-find base problem -> https://www.acmicpc.net/problem/1976

#include <stdio.h>

#define MAX_N   200
#define MAX_M   1000

int N, M;

int uf[MAX_N+1];

int root(int a){
    while(a != uf[a]){
        uf[a] = uf[uf[a]];
        a = uf[a];
    }
    return a;
}
bool isConnected(int a, int b){
    return root(a) == root(b);
}
void union1(int a, int b){
    a = root(a);
    b = root(b);
    uf[a] = b;
}

int main(){
    scanf("%d %d", &N, &M);
    
    for(int i = 1; i <= N; ++i)
        uf[i] = i;
    
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j){
            int c;
            scanf("%d ", &c);
            if(c)
                union1(i, j);
        }

    int p1;
    scanf("%d ", &p1);
    for(int i = 1; i < M; ++i){
        int p2;
        scanf("%d ", &p2);
        if(!isConnected(p1, p2)){
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}

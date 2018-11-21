//
//  union_find.cpp
//  Algorithms
//
//  Created by Hongseob Shin on 2018. 11. 8..
//  Copyright © 2018년 Hongseob Shin. All rights reserved.
//
// union-find base problem -> https://www.acmicpc.net/problem/1717

#include <stdio.h>

#define MAX_N   1000000

int arr[MAX_N];

// a와 b를 union
// a의 트리를 b에 연결
int root1(int i){   // recursive
    return (i == arr[i]) ? i : arr[i] = root1(arr[i]);  // path-compresstion
}
int root2(int i){   // while1 - coursera
    while(arr[i] != i){
        arr[i] = arr[arr[i]];   // path-compresstion
        i = arr[i];
    }
    return i;
}
int root3(int a){   // while2
    int r = a;
    while (arr[r] != r)    r = arr[r];
    return arr[a] = r;
}

void union1(int a, int b){
    int i = root1(a);
    int j = root1(b);
    arr[i] = j;
    //find tree size (not depth)
    //if (i == j) return;
    //if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
    //else { id[j] = i; sz[i] += sz[j]; }
}

bool connected(int i, int j){
    return root1(i) == root1(j);
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    for (int i = 1; i <= N; ++i)
        arr[i] = i;
    
    int cmd, a, b;
    for (int i = 0; i < M; ++i){
        scanf("%d %d %d", &cmd, &a, &b);
        if (cmd){
            if (connected(a, b))
                printf("YES\n");
            else
                printf("NO\n");
        }
        else{
            union1(a, b);
        }
    }
    
    return 0;
}

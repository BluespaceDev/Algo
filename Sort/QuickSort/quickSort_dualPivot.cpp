//
//  quickSort_dualPivot.cpp
//  Algorithms
//
//  Created by Hongseob Shin on 02/12/2018.
//  Copyright © 2018 Hongseob Shin. All rights reserved.
//
// https://www.acmicpc.net/problem/2750

#include <stdio.h>

#define MAX_N   10000000

int data[MAX_N];

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

void qsort(int low, int high){
    if (low >= high)    return ;
    
    if (data[low] > data[high])
        swap(data[low], data[high]);
    
    int lo = low+1;
    int hi = high-1;
    int i = lo;
    
    while(i <= hi){
        // < low
        if (data[i] < data[low])
            swap(data[i++], data[lo++]);
        // > high
        else if (data[i] > data[high]){
            while(data[hi] > data[high] && i < hi)  --hi;
            swap(data[i], data[hi--]);
        }
        else
            ++i;
    }
    
    swap(data[low], data[--lo]);
    swap(data[high], data[++hi]);
    
    qsort(low, lo-1);
    qsort(lo+1, hi-1);
    qsort(hi+1, high);
}

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i)
        scanf("%d\n", &data[i]);
    
    qsort(0, N-1);
    
    for(int i = 0; i < N; ++i)
        printf("%d\n", data[i]);
    
    return 0;
}

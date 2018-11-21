// https://www.acmicpc.net/problem/4195

#include <cstdio>
#include <unordered_map>
#include <string>
#include <iostream>

#define MAX_F   100000*2
#define MAX_NAME    20

using namespace std;

int T, F;
int uf[MAX_F];
int groupSize[MAX_F];

unordered_map<string, int> names;

int root(int a){
    while(a != uf[a]){
        uf[a] = uf[uf[a]];
        a = uf[a];
    }
    return a;
}
int union1(int a, int b){
    a = root(a);
    b = root(b);
    if (a != b){
        uf[a] = b;
        groupSize[b] += groupSize[a];
    }
    return groupSize[b];
}

int main(){
    scanf("%d\n", &T);
    while(T--){
        scanf("%d\n", &F);
        names.clear();
        for(int i = 0; i < MAX_F; ++i){
            uf[i] = i;
            groupSize[i] = 1;
        }
        
        for(int i = 0; i < F; ++i){
            char name1[MAX_NAME+1];
            char name2[MAX_NAME+1];
            //string name1,name2;       // cin is very slow
            //cin >> name1 >> name2;
            scanf("%s %s\n", name1, name2);
            string p1 = name1;
            string p2 = name2;
            if(names.count(p1) == 0)
                names[p1] = (int)names.size();
            if(names.count(p2) == 0)
                names[p2] = (int)names.size();
            
            printf("%d\n", union1(names[name1], names[name2]));
        }
        
    }
    return 0;
}

# Trie
  
접미사(suffix) : i번째 글자부터 마지막 글자까지 이루어진 문자열  
Ex) ‘STEVEN’ 의 2번째 suffix = ‘EVEN’  
4번째 suffix = ‘EN’  

## 접미사 Trie
Suffix trie : 문자열 집합에 속한 문자열들의 가능한 모든 접미사로 이루어진 트리  
영어 문자열 이라면 26개 자식노드 존재
모든 접미사  
Ex) S = {‘CAR’, ‘CAT’, ‘RAT’} => {‘AR’, ‘AT’, ‘CAR’, ‘CAT’, ‘R’, ‘RAT’, ‘T’} (중복제거)  
  
## 접미사 트리 
  
### 접미사 트라이 단점 극복
여러개 문자열이 아닌 긴 문자열을 다룸 (경로 압축)  
문자열이 길어질수록 접미사 트라이에 중복되는 정점이 많아짐  
  
### 특징
정점의 개수 2n, 간선의 개수 2n-1  
  
시간 복잡도 : O(m+ooc)  
Ooc : 패턴이 몇번 출현하는 지  
=> 입력 문자열이 대해 시간복잡도가 영향을 받지 않음  
  
### 문제 활용
1. 최장 반복 부분 문자열을 효율적으로 구할 수 있다.  
반복 문자열 => 정점 x에 대해 자식들이 여러개 (접미사들)  
최장 => 같은 접두사를 가지고 있고, x가 루트로부터 가장 깊은 곳에 있는 정점  
  
2. 최장 공통 부분 문자열  
문자열 T1, T2에 대한 접미사 트리를 결합하여 일반화된 접미사 트리를 구축  
T1, T2의 접미사에 대해 공통의 접두사(같은 루트)  
그 중에 가장 긴 접두사를 구함(루트에서 정점x까지 길이)  
  
## 접미사 배열
  
접미사 트리는 효율적으로 구축하기에는 복잡하여 대회에서 사용하기에는 위험.  
간편하게 구축할 수 있는 것이 접미사 배열  
  
### 구축 방법
간단하게 모든 접미사를 구하고 정렬하는 방법.  
n < 1000 정도 밖에 못함.  
```c++
#define MAX_N 1010  // 첫번째 방법 O(n^2 logn)
int SA[MAX_N], n;
bool cmp(int a, int b) { return strcmp(T + a, T + b) < 0; }      // compare O(n)
int main(){
  n = (int)strlen(gets(T));               // 한 줄 읽으며 입력에 대한 길이 구함
  for (int i = 0; i < n; ++i) SA[i] = i;  // 처음의 SA는 {0, 1, 2,..., n-1}
  sort(SA, SA + n, cmp);                  // 정렬 O(n*logn) * cmp O(n) = O(n^2 logn)
}
```
  
더 나은 방법으로 각 접미사에 대한 랭킹 페어(ranking pair)를 정렬하는 것.  
n < 10000 정도 가능 (비교 정렬).  
n < 100000 가능 (계수 정렬).  
SA[i]에 대한 랭킹 페어 (RA[SA[i]], RA[SA[i]+k])  
k = 1,2,4...(2의 거듭제곱이고 n보다 작음)  

k=1 일때, 
1: ('ACA') -> ('A','C') = (65, 67)  
2: ('AGACA') -> ('A','G') = (65, 71)  
1번이 먼저 나오고 2번이 나오는 형태로 정렬됨.  
k=2 일때, 두 글자를 살펴봄.  
먼저 
1: ('GACA') -> ('GA','CA') = (6, 5) // 'GA' 는 이전 정렬에서 랭킹 6으로 결정됨  
RA[SA[n-1]] == n-1 인지 검사하면 랭킹이 다 부여 되었는지 알 수 있다.  
  
정렬 : O(nlogn), 계수 정렬 사용하면 O(n)
반복 : O(logn)  
시간 복잡도 : O(n log^2 n), O(nlogn)

```c++
void countingSort(int k) {                                          // O(n)
  int i, sum, maxi = max(300, n);   // up to 255 ASCII chars or length of n
  memset(c, 0, sizeof c);                          // clear frequency table
  for (i = 0; i < n; i++)       // count the frequency of each integer rank
    c[i + k < n ? RA[i + k] : 0]++;
  for (i = sum = 0; i < maxi; i++) {
    int t = c[i]; c[i] = sum; sum += t;
  }
  for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; i++)                     // update the suffix array SA
    SA[i] = tempSA[i];
}

void constructSA() {         // this version can go up to 100000 characters
  int i, k, r;
  for (i = 0; i < n; i++) RA[i] = T[i];                 // initial rankings
  for (i = 0; i < n; i++) SA[i] = i;     // initial SA: {0, 1, 2, ..., n-1}
  for (k = 1; k < n; k <<= 1) {       // repeat sorting process log n times
    countingSort(k);  // actually radix sort: sort based on the second item
    countingSort(0);          // then (stable) sort based on the first item
    tempRA[SA[0]] = r = 0;             // re-ranking; start from rank r = 0
    for (i = 1; i < n; i++)                    // compare adjacent suffixes
      tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
      (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++)                     // update the rank array RA
      RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;               // nice optimization trick
} }

int main() {
  n (int)strlen(gets(T));
  T[n++] = '$';
  constructSA();
}
```

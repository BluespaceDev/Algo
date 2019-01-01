# RMQ(Range Minimum Query)
  
## Brute-force
일반적으로 다 구하면 [i, j] 구간의 최소값을 찾을때, O(N)만큼 걸림.  
쿼리의 개수가 M개라면, O(MN)만큼 시간이 걸림.  

## DP 방법
N^2 크기의 배열하나 필요.  
최소값을 구하는데는 O(1)  
D[i][j] : i ~ j 중 최소값 저장 
또는  
D[i][j] : i ~ 2^j개의 최소값 (트리랑 비슷)  

## Segment 트리 방법
이진 트리 형태 인덱스 사용  
2xP(왼쪽자식), 2xP+1(오른쪽자식)  
[L, (L+R)/2], [(L+R)/2+1, R]  
  
N이 2의 제곱인 경우 Full Binery Tree  
리프 노드가 N개인 경우 필요한 노드 갯수 : 2N-1  
필요한 배열의 크기 : 2^(H+1)-1, 높이 H = ceil(lgN)  
  
```c++
// d : tree
// a : input data
void build(int node, int start, int end) {
    if (start == end) // 리프노드
        d[node] = a[start];
    else {
        build(node*2, start, (start+end)/2);    // 왼쪽자식
        build(node*2+1, (start+end)/2+1, end);  // 오른쪽자식
        d[node] = min(d[node*2], d[node*2+1]);  // 부모
    }
}
int query(int node, int start, int end, int i, int j) {
    if (i > end || j < start)
        return -1;
    if (i <= start && end <= j) // 범위가 포함되면 return
        return d[node];
    int m1 = query(node*2, start, (start+end)/2, i, j);
    int m2 = query(node*2+1, (start+end)/2+1, end, i, j);
    if (m1 == -1) return m2;
    else if (m2 == -1) return m1;
    else return min(m1,m2);
}
```


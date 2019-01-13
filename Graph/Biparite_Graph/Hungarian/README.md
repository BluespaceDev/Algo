# Hungarian Algorithm
  
할당 문제  
N명의 worker, N개의 jobs를 어떻게 할당할 것인가?  
c_ij = cost matrix, i번 worker에 j번 job을 할당할 때의 cost  
x_ij = result binary matrix, i번 worker에 j번 job이 할당되면 1 아니면 0  
1명의 worker는 1개의 job을 할당, 
1개의 job 역시 1명의 worker에게 할당,  
C_ij * X_ij 모든 합이 최소가 되어야 함.  
  
이러한 할당문제는 min-cost flow 문제의 특별한 경우이다.  
  
## O(n^4) algorithm
main-idea : weight가 0인 edge(“0-weight edges”)를 선택하면 매칭을 찾을 수 있다.  
매칭을 못찾게 되면 weight를 변경해가면서 “0-weight edges”를 추가한다. (이러한 것은 optimal solution에 영향x)  


### 알고리즘 동작
#### Step 0) “0-weight edges” 만드는 작업 (이 step은 안해도 상관없음)  
A. W (worker 정점 집합)에 나가는 edge중 최소값을 선택해 W에 연결된 모든 edge에 뺀다.  
B. J (job 정점 집합)에 나가는 edge중 최소값을 선택해 J에 연결된 모든 edge에 뺀다.  

#### Step 1) maximum matching 찾기
A. “0-weight edges” 만 이용해서 (subgraph=“0-weight edges”만 있는 graph) maximum matching을 찾는다. (max-flow algorithm, augmenting path algorithm, etc)  
B. matching 되면 solve, 아니면 minimum vertex cover V (subgraph 에서)를 찾는다. (Köning’s graph theorem 이용)  
(Kőnig's theorem : 이분 그래프에서 최대 매칭 문제와 최소 버텍스 커버 문제의 답이 같다는 내용)  
(Vertex cover : 정점이 모든 간선을 cover함, 모든 간선과 정점이 연결되어 있어야 함)  
(Minimum vertex cover : vertex cover집합 중에 개수가 최소인 것, vertex cover는 모든 정점을 선택해도 됨)  
  
#### Step 2) cost 재 계산
delta = min(c_ij), i,j 모두 V에 속하지 않음 // V에 속하지 않은 edge의 cost중에 최소값  
c_ij  
= c_ij - delta (i,j 모두 V에 속하지 않음)  
= c_ij (i가 V에 속하거나 j가 V에 속함)  
= c_ij + delta (i,j 모두 V에 속함)  
  
#### Step 3) 해결될때까지 Step 1 반복
  
Step에서 걸리는 시간 O(N^2), Step 1에서 O(n^5)이 되지 않기 위해 이전 step에서 matching 수정필요.  
최대 O(N^2)번 반복 (매번 최소 1개의 "0-weight edge"를 찾기 때문)  
Total O(N^4)  
  
  
## O(n^3) algorithm
Maximum-weighted matching 문제를 다루기 때문에  
minimum -> maximum로 변경, 가중치를 바꾸면 쉽게 가능.  
w(x,y) = -w(x,y)  // 음수 방법  
w(x,y) = M-w(x,y), M=max w(x,y) // 양수 방법  
  
### 기본 정리
complete bipartite라 고려하면,
graph G = (V,E), V는 X와 Y의 합집합 (교집합은 없음)  

#### Vertex labeling  
각 정점은 l(x)+l(y) >= w(x,y)를 만족하는 번호를 부여받음 (edge에 연결된 x,y 라벨의 합은 가중치보다 작아야함)  
  
#### Equality subgraph  
spanning subgraph GI = (V,EI)  
EI집합은 (x,y)를 연결하는 edge가 있고, l(x)+l(y)=w(x,y)인 edge.  
  
#### 추가 이론
Equality subgraph GI에서 perfect matching M* 이 되면 M* 는 Graph G에서 maximum-weighted matching이 된다.
  
#### Alternating path and alternating tree
matching M에서 matched vertex와 exposed(unmatched) vertex가 있다.  
alternating path : path P에서 서로 다른 P (같이 선택할 수 없는), 어떤 경로를 선택하느냐에 따라 서로 다른 matching이 된다.  
augmenting : alternating path에서 첫번째나 마지막 정점이 exposed 상태이면 edge를 도치시키면서 matching의 크기를 늘릴 수 있음.  
alternating tree : exposed vertex 인 root를 가졌고, root에서 시작하는 경로가 alternating인 tree.  
  
  
  
참고 사이트  
https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/

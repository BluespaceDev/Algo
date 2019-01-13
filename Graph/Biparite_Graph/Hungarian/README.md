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


참고 사이트  
https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/

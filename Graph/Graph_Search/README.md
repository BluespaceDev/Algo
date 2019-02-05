# Graph Search

## DFS
재귀적인 코드를 사용하여 간단히 구현 가능.  
정점의 각 상태를 표기하여 다양한 정보로 활용.  
인접리스트 O(V+E), 인접행렬 O(V^2)  
backtracking과 다른 점은 퇴각할때 정점의 표시를 이전 상태로 되돌리는 작업.  
  
### 그래프 간선의 속성
트리 간선 : DFS가 탐색하는 간선. 현재 상태가 EXPLORED -> UNVISITED 로 향하는 간선  
역방향 간선 : 사이클에 해당하는 간선. 현재 상태가 EXPLORED -> EXPLORED 로 향하는 간선. (양방향 간선은 사이클로 취급하지 않음). 
순방향 간선, 교차 간선 : EXPLORED -> VISITED

```c++
void graphCheck(int u){
    dfs_num[u] = EXPLORED;
    time_d[u] = time++;   // 시간 기록
    for (int j = 0; j < AdjList[u].size(); ++j){
        int v = AdjList[u][j];
        if (dfs_num[v] == UNVISITED){ // 트리 간선, EXPLORED->UNVISITED
            dfs_parent[v] = u;
            graphCheck(v);
        }
        else if (dfs_num[v] == EXPLOED){ //
            if (v == dfs_parent[u])
                // 양방향 간선
            else
                // 역방향 간선 (사이클 여부 조사)
        }
        else if (dfs_num[v] == VISITED) // EXPLORED->VISITED
            // forward/cross edge
    }
    dfs_num[u] = VISITED;
    time_f[u] = time++;
}
```

각 정점에 시간을 기록하여 그래프 구조에 관한 중요한 정보 제공.  
  
괄호 정리.  
흰색 경로 정리 - u가 발견 될 때, u->v 까지 모든 경로상 정점들은 흰색 정점으로 구성된다.   

무방향 그래프에서는 트리간선, 역행간선만 존재 (순행, 교차간선은 없음)  
=> 순행이 없는 것은 무방향이라 u->v->w에서 w에 도착했을때 w->u(역행) 간선으로 취급됨.  
=> 교차도 마찬가지로, 방문 안했다면 트리간선이 되고 방문 했다면 역행간선이 됨.  

## BFS
queue를 이용하여 간단히 구현 가능.  
진행 정도에 따라 coloring을 함.  
흰색(방문x)->회색(방문예정,q에 있는 상태)->검은색(방문끝)  
회색은 발견된 정점과 발견하지 않은 정점의 경계선을 나타낸다.  
수행시간은 인접리스트 O(V+E), 인접행렬 O(V^2)  
```c++
for 각 정점 u {
    u.color = WHITE
    u.d = INF       // s부터 u까지 거리
    u.p = NULL      // u 정점의 직전원소(부모)
}
s.color = GRAY
s.d = 0
s.p = NULL
enqueue(s)
while(!q.empty()){
    u = dequeue();
    for u와 연결된 정점 v {
        if (v.color == WHITE){
            v.color = GRAY
            v.d = u.d + 1   // edge 가중치 1, 진행하는 layer라고도 볼 수 있음
            v.p = u
            enqueue(v)
        }
    }
    u.color = BLACK
}
```

u.d : (s,u) 까지 최단 경로가 저장된다.  
보조정리 - (s,v) <= (s,u)+1  
s에서 u로 도달가능하면 s에서 v도 도달 가능하다.  
보조정리 - BFS가 끝났을 때 각 정점에 계산된 v.d는 v.d >= (s,v)를 만족한다.  

### 트리의 지름
임의의 정점 하나를 선택해서 가장 먼 점 v를 찾고,  
v를 시작정점으로 가장 먼 점 u를 찾으면,  
u-v는 트리의 지름이 됨.  

### BFS를 이용한 최단경로


## 위상정렬
DAG(Directed Acyclic Graph) = 사이클이 없는 방향 그래프.  
에서 선형 순서를 정렬.  
예를 들면, 대학생 졸업 요건을 갖추기 위해 각 과목이 있고 선수 과목이 있다.  
선수 과목을 들어야 다음 과목을 들을 수 있다.  
이러한 선수 관계를 위상 정렬하면 들어야할 과목 순서를 정할 수 있다.  

```c++
vector<int> ts; // 위상 정렬을 역순으로 저장하기 위한 변수

void dfs(int u){
    dfs_num[u] = VISITED;
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if (dfs_num[v] == UNVISITED)
            dfs(v);
    }
    ts.push_back(u); // 기존 dfs에서 이 부분만 추가하면 됨. 방문이 끝나면서 하나씩 담음
}
```

정리 - 방향 그래프가 비순환이면, dfs는 역행 간선을 만들지 않고 그 역도 성립한다.  

### 칸 알고리즘 (위상정렬)
BFS를 응용함.  
DFS기반 알고리즘으로 풀지 못할 경우도 있음. 그럴때 사용.  
```c++
// 진입 차수가 0인 정점들을 우선순위 큐에 삽입
while(!q.empty()){
    int u = q.dequeue();
    ts.push_back(u);    // 정점 u를 위상 정렬 목록에 추가
    
    for(int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        in_edge[v]--;   // 정점 u에 모든 진출 간선을 제거
        if (in_edge[v] == 0) // 제거 하면서 u에 연결된 정점 v가 진입 차수가 0이 되면,
            q.enqueue(v);
    }
}
```

Q. 위 알고리즘들은 위상정렬 1개만 구함. 만약 가능한 모든 위상정렬을 구하려면?  

## 이분 그래프 검사
DFS, BFS 모두 사용할 수 있으나 BFS가 더 자연스러울 것.  
정점 0으로 색칠하고 다음 정점 1로 색칠 하면서 두 가지 색깔로 색칠하면서 검사.  

```c++
queue<int> q;
q.push(s);    // 시작 정점 s
int color[V];
color[s] = 0;
bool isBipartite = true;
while(!q.empty() & isBipartite){
    int u = q.front(); q.pop();
    for (int i = 0; i < adj[u].size(); ++i){
        int v = adj[u][i];
        if (color[v] == INF){  // v가 색칠 안되었으면,
            color[v] = 1 - color[u];  // {0, 1} 중 하나 색칠
            q.push(v);
        }
        else if (color[v] == color[u]){ // v가 색칠되어 있는데 u랑 같은 색이면, 충돌
            isBipartite = false;
            break;
        }
    }
}
```

Q. 정점 v개인 단순 그래프가 이분 그래프라면 최대 간선의 개수는?  
A. S, T 정점 그룹으로 나눠지니, S-T 연결되는 최대 간선 SxT개  

## 오일러 서킷, 오일러 트레일
한붓그리기 같은 문제.  
오일러 서킷은 모든 간선을 한번씩만 지나서 시작점으로 돌아오는 경로 찾기.  
나가는 간선, 들어오는 간선의 수가 같아야함. (무방향 그래프에서는 짝수개)  
시작점 u, 끝점 v라고 하면,  
u != v 면, v는 홀수개 간선 (홀수가는건 들어가기는 하나 나갈 수 없음).  
u == v 면, v는 항상 짝수, u에서 나가서 다시 u로 들어와야함.  
깊이우선탐색 하면서 u에서 다시 u로 돌아왔을때 남아있는 간선들은 어떻게 할까?  
여러개 서킷들을 합치면 하나의 서킷이 됨.  
이유는 간선들이 짝수개이기 때문에 나가고 들어가고 할 수 있음.  
  
오일러 트레일은 오일러 서킷에서 시작점과 끝점이 주어진 형태.  
a에서 b로 끝나는 오일러 트레일 찾고 싶으면,  
(b,a)간선 추가하고 오일러서킷을 찾으면 됨. 그러면 다시 a로 돌아와서 오일러서킷  

```c++
void euler(int u){
    for(int v = 0; v < size; ++v){
        while(adj[u][v] > 0){
            adj[u][v]--;  // 간선을 지운다
            adj[v][u]--;
            euler(v);
        }
    }
    circuit.push_back(u); // reverse 필요
}
```
인접리스트를 사용한다면, 조금 더 복잡해짐.  
인접행렬 O(VE), 인접리스트 O(E)

## 절단점 및 다리 구하기(무방향 그래프)
절단점 : 그래프의 정점 중에 정점을 제거 했을 때(간선도 포함하여 제거됨) 그래프가 연결되지 않도록 많드는 정점.  
DFS 1번이면 모든 절단점과 다리를 구할 수 있다. O(V+E)  
dfs_num(몇번째 방문인지), dfs_low(도달 가능한 최소의 dfs_num값) 값을 유지해 나감.  
dfs_low(v) >= dfs_num(u) 이면, 정점 u는 절단점이다. dfs_low(v)가 dfs_num(u)보다 작지 않다는 것으로 유추.  
u->v->w 일때, 정점w로 도달할 수 있는 역방향 간선이 존재하지 않는 다는 뜻. 역방향 간선이 존재하지 않으면 해당 정점을 끊으면 그래프도 끊김.  
(단, 루트가 절단점이 되려면 자식 2개 이상 가지고 있어야 함.)  
절단 다리는 dfs_low(v) > dfs_num(u) 로 "=" 부호만 빠지면 된다. (=부호는 양방향일때 의미).  
절단점에서 dfs_low(v) == dfs_num(u) 인 경우는 back edge의 도착점일 경우 그 점(dfs_low인 점)은 절단점이 될 수 있다.  

```c++
void articulationPointAndBridge(int u){
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // 처음에는 두개의 값이 동일하게 세팅됨.
    for (int j = 0; j < AdjList[u].size(); ++j){
        int v = AdjList[u][j];
        if (dfs_num[v] == UNVISITED) { // 트리 간선
            dfs_parent[v] = u;
            if (u == dfsRoot) rootChildren++;
            
            articulationPointAndBridge(v);
            
            if (dfs_low[v] >= dfs_num[u]) // 절단점
                articulation_vertex[u] = true;
            if (dfs_low[v] > dfs_num[u])  // 절단 다리
                printf("edge(%d-%d) is bridge", u, v);
            
            dfs_low[u] = min(dfs_low[u], dfs_low[v]); // dfs_low[u] 갱신
        }
        else if (v != dfs_parent[u]) // 역방향 간선이며, 양방향이 아니라면, (u(parent[u])->v(u)->u(v))
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}
```

## 강결합 컴포넌트 구하기 (방향 그래프)
SCC(Strongly Connected Component) : 하나의 연결된 컴포넌트, 어느 두 정점을 선택하더라도 경로가 있고 반대의 경로도 있다.  
SCC를 그룹으로 표현하면 DAG를 이룸.  
코사라주 알고리즘, 타잔 알고리즘이 있다.  

### 타잔 알고리즘
SCC가 DFS 스패닝 트리에서 서브트리를 이룬다는 기본적인 아이디어.  
절단점과 다르게 visited 인 정점에서만 dfs_low(u)를 갱신한다.  
스패닝 트리에서 dfs_low(u) == dfs_num(u) 이면, u가 하나의 SCC 시작정점이 된다.  

```c++
vi dfs_num, dfs_low, visited;
    
void tarjanSCC(int u){
    dfs_low[u] = dfs_num[u] = dfsNumberCount++;
    S.push_back(u) // u를 방문 순서에 따라 배열에 저장.  
    visited[u] = 1;
    for (int j = 0; j < AdjList[u].size(); ++j){
        int v = AdjList[u][j];
        if (dfs_num[v] == UNVISITED)
            tarjanSCC(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    
    if (dfs_low[u] == dfs_num[u]){ // SCC 루트를 구했으니 하나씩 꺼냄
        while(1){
            int v = S.back(); S.pop_back();
            visited[v] = 0;
            if (u == v) break;
        }
    }
}
```

### 코사라주 알고리즘
그래프 G와 전치 그래프 G'를 이용한다.  
전치 그래프 G'는 그래프 G의 간선을 거꾸로 된 방향으로 바꾼 것이다. (u->v) => (v->u)  
G와 G'는 서로 같은 SCC를 가진다. (SCC정의 대로 서로 도달하는 부분은 방향을 바꿔도 서로 도달하기 때문)  

```c++
1. 각 정점 u에 대해 종료 시간 u.f를 계산 (dfs(G) 호출)
2. 전치 그래프 G'를 생성
3. DFS(G')를 호출한다. 호출할 때, u.f가 감소하는 순서(늦게 끝난 정점부터)로 호출한다.
4. 3에서 깊이 우선 포레스트를 만드는데(SCC가 DAG를 이루는 데 역순으로 호출하면 각 SCC하나씩 생성됨) 그것을 출력한다.
```

### 정리들
정리1. SCC는 DAG를 이룬다.  

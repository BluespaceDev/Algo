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
}
```

## BFS
queue를 이용하여 간단히 구현 가능.  

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

## 절단점 및 다리 구하기(무방향 그래프)
절단점 : 그래프의 정점 중에 정점을 제거 했을 때(간선도 포함하여 제거됨) 그래프가 연결되지 않도록 많드는 정점.  
DFS 1번이면 모든 절단점과 다리를 구할 수 있다. O(V+E)  
dfs_num(몇번째 방문인지), dfs_low(도달 가능한 최소의 dfs_num값) 값을 유지해 나감.  
dfs_low(v) >= dfs_num(u) 이면, 정점 u는 절단점이다. dfs_low(v)가 dfs_num(u)보다 작지 않다는 것으로 유추.  
u->v->w 일때, 정점w로 도달할 수 있는 역방향 간선이 존재하지 않는 다는 뜻. 역방향 간선이 존재하지 않으면 해당 정점을 끊으면 그래프도 끊김.  
(단, 루트가 절단점이 되려면 자식 2개 이상 가지고 있어야 함.)  
절단 다리는 dfs_low(v) > dfs_num(u) 로 = 부호만 빠지면 된다. (=부호는 양방향일때 의미).  

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

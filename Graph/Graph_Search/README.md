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

## 절단점 및 다리 구하기(무방향 그래프)
절단점 : 그래프의 정점 중에 정점을 제거 했을 때(간선도 포함하여 제거됨) 그래프가 연결되지 않도록 많드는 정점.  
DFS 1번이면 모든 절단점과 다리를 구할 수 있다. O(V+E)  
dfs_num(몇번째 방문인지), dfs_low(도달 가능한 최소의 dfs_num값) 값을 유지해 나감.  
dfs_low(v) >= dfs_num(u) 이면, 정점 u는 절단점이다. dfs_low(v)가 dfs_num(u)보다 작지 않다는 것으로 유추.  
u->v->u 일때, 

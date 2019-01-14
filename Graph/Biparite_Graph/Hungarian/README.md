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
J_G(v) = {u|(v,u)} // graph G에서 정점 v와 연결된 정점들 u
J_G(S) = U J_G(v)  // graph G에서 정점들의 부분집합 S와 연결된 모든 정점들

#### Vertex labeling  
각 정점은 l(x)+l(y) >= w(x,y)를 만족하는 번호를 부여받음 (edge에 연결된 x,y 라벨의 합은 가중치보다 작아야함)  
  
#### Equality subgraph  
spanning subgraph GI = (V,EI)  
EI집합은 (x,y)를 연결하는 edge가 있고, l(x)+l(y)=w(x,y)인 edge.  
  
#### 추가 이론
Equality subgraph GI에서 perfect matching M* 이 되면 M* 는 Graph G에서 maximum-weighted matching이 된다.
  
#### Alternating path and alternating tree
matching M에서 matched vertex와 exposed(unmatched) vertex가 있다.  
alternating path : 한 정점에서 시작해서 여러 경로가 나옴. path P에서 서로 다른 P (같이 선택할 수 없는), 어떤 경로를 선택하느냐에 따라 서로 다른 matching이 된다.  
augmenting : alternating path에서 첫번째나 마지막 정점이 exposed 상태이면 edge를 도치시키면서 matching의 크기를 늘릴 수 있음.  
alternating tree : exposed vertex 인 root를 가졌고, root에서 시작하는 경로가 alternating인 tree.  
  
### 알고리즘 동작

#### Step 0) 초기화
vertex labaling, 

```cpp
// 라벨링 초기화
void init_labels()
{
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
            lx[x] = max(lx[x], cost[x][y]); // 정점 x와 연결된 edge중 cost가 가장 높은 값을 labeling
}
```

#### Step 1)
A. matching M이 다 연결되면 종료, 그렇지 않으면  
B. 일부 정점 x가 exposed면 S={x},T={} (x는 build를 진행할 alternating tree의 root), 그리고 Step 2로 진행  
  
```cpp
void augment() //main function of the algorithm
{
    // step1
    if (max_match == n) return; //A. check whether matching is already perfect
    int x, y, root; //just counters and root vertex
    int q[N], wr = 0, rd = 0; //q - queue for bfs, wr,rd - write and read
    //pos in queue
    memset(S, false, sizeof(S)); //init set S
    memset(T, false, sizeof(T)); //init set T
    memset(prev, -1, sizeof(prev)); //init set prev - for the alternating tree
    // B. X part로부터 exposed vertex 를 여러개 찾는다.
    // finding root of the tree
    for (x = 0; x < n; x++)
        if (xy[x] == -1)
        {
            q[wr++] = root = x;
            prev[x] = -2;
            S[x] = true;
            break;
        }
    //initializing slack array
    for (y = 0; y < n; y++)
    {
        slack[y] = lx[root] + ly[y] - cost[root][y];
        slackx[y] = root;
    }
    // end of step 1
    ...
}
```

  
#### Step 2)
A. J_Gl(S) != T (Equality subgraph Gl에서 S와 T가 연결x) 이면, Step 3로 진행.  
B. J_Gl(S) = T (연결되어 있으면), labeling을 업데이트 한다.  
delta = min(l(x)+l(y)-w(x,y)) // x는 S의 정점, y는 T밖의 정점, S에서 T에 있지 않은 정점y와 연결된 값중 최소값.  
l'(v) // 존재하는 라벨들을 업데이트  
= l(v) - delta // v가 S에 있으면  
= l(v) + delta // v가 T에 있으면  
= l(v) // 둘다 없을 경우  
  
```cpp
// alternating tree는 build된 상태이나 augmenting path는 찾지 못했음.
// 그래서 update labeling 필요.
// 새로운 edge를 equality subgraph 추가 (alternating tree 확장)
// main idea : equality graph에서 현재 label상태로 augmenting path를 찾을 때까지 update label 반복
// 그냥하면 O(n^4)인데 step 1에서 slack초기화해서 O(n)만 걸림
// slack update - delta찾을때 O(n^2)을 O(n)으로 하게 해줌
// step 3) vertex x를 S에 옮김 O(n)
// step 2) updating labeling 할때 O(n)
void update_labels()
{
    int x, y, delta = INF; //init delta as infinity
    for (y = 0; y < n; y++) //calculate delta using slack
        if (!T[y])
            delta = min(delta, slack[y]);
    for (x = 0; x < n; x++) //update X labels
        if (S[x]) lx[x] -= delta;
    for (y = 0; y < n; y++) //update Y labels
        if (T[y]) ly[y] += delta;
    for (y = 0; y < n; y++) //update slack array
        if (!T[y])
            slack[y] -= delta;
}
```
  
  
#### Step 3)
A. 일부 정점 y (T에 속해 있고 Equality subgraph Gl에서 S와 연결되어 있지 않음) 를 찾는다.
B. y가 exposed이고, x(root of the tree)에서 y로 alternating path가 존재하면, 이 경로를 따라서 augment matching한다. 그 후 Step 1으로 진행  
C. y가 M에서 일부 정점 z와 연결되어 있으면 (z,y)를 alternating tree에 추가한다. (S+={z}, T+={y}), 그 후 Step 2로 진행.  
  
각 edge는 1번만 사용된다.  

```cpp
//x - current vertex,prevx - vertex from X before x in the alternating path,
//so we add edges (prevx, xy[x]), (xy[x], x)
void add_to_tree(int x, int prevx)
{
    S[x] = true; //add x to S
    prev[x] = prevx; //we need this when augmenting
    for (int y = 0; y < n; y++) //update slacks, because we add new vertex to S
        if (lx[x] + ly[y] - cost[x][y] < slack[y])
        {
            slack[y] = lx[x] + ly[y] - cost[x][y];
            slackx[y] = x;
        }
}
void augment() //main function of the algorithm
{
...
    while (true) //main cycle
    {
        // A. 몇몇 exposed vertex에서 시작하여 alternating tree를 build 함.
        while (rd < wr) //building tree with bfs cycle
        {
            x = q[rd++]; //current vertex from X part
            for (y = 0; y < n; y++) //iterate through all edges in equality graph
                if (cost[x][y] == lx[x] + ly[y] && !T[y])
                {
                    if (yx[y] == -1) break; //an exposed vertex in Y found, so
                    //augmenting path exists!
                    T[y] = true; //else just add y to T,
                    q[wr++] = yx[y]; //add vertex yx[y], which is matched
                    //with y, to the queue
                    add_to_tree(yx[y], x); //add edges (x,y) and (y,yx[y]) to the tree
                }
            if (y < n) break; //augmenting path found!
        }
        if (y < n) break; //augmenting path found!
        
        update_labels(); //augmenting path not found, so improve labeling
        wr = rd = 0;
        for (y = 0; y < n; y++)
            //in this cycle we add edges that were added to the equality graph as a
            //result of improving the labeling, we add edge (slackx[y], y) to the tree if
            //and only if !T[y] && slack[y] == 0, also with this edge we add another one
            //(y, yx[y]) or augment the matching, if y was exposed
            if (!T[y] && slack[y] == 0)
            {
                if (yx[y] == -1) //exposed vertex in Y found - augmenting path exists!
                {
                    x = slackx[y];
                    break;
                }
                else
                {
                    T[y] = true; //else just add y to T,
                    if (!S[yx[y]])
                    {
                        q[wr++] = yx[y]; //add vertex yx[y], which is matched with
                        //y, to the queue
                        add_to_tree(yx[y], slackx[y]); //and add edges (x,y) and (y,
                        //yx[y]) to the tree
                    }
                }
            }
        if (y < n) break; //augmenting path found!
    } // end of while
    
    if (y < n) //we found augmenting path!
    {
        max_match++; //increment matching
        //in this cycle we inverse edges along augmenting path
        for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty)
        {
            ty = xy[cx];
            yx[cy] = cx;
            xy[cx] = cy;
        }
        augment(); //recall function, go to step 1 of the algorithm
    }
}
```

### Code
```cpp
int hungarian()
{
    int ret = 0; //weight of the optimal matching
    max_match = 0; //number of vertices in current matching
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));
    init_labels(); //step 0
    augment(); //steps 1-3
    for (int x = 0; x < n; x++) //forming answer there
        ret += cost[x][xy[x]];
    return ret;
}

```


  
참고 사이트  
https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/

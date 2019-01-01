# Fenwick Tree(= Binary Indexed Tree, BIT)
  
**동적인 누적 빈도수 테이블** 사용시 유용한 자료 구조  
Ex) 학생들의 시험 점수별로 빈도수가 어떻게 되는가?  
이진수 표현의 인덱스 사용  
비트연산  
bit의 마지막 1의 위치로 판단  
1의 위치가 높으면 아래 부분 다 포함 상태  


```c++
// 누적값 업데이트, 위에 트리들을 업뎃
void update(int i, int num) {
    while (i <= n) {
        tree[i] += num;
        i += (i & -i);
    }
}
// 누적값에 대한 연산
int sum(int i) {
    int ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
```
  
추가 참고 사이트  
https://www.acmicpc.net/blog/view/21
  
https://kks227.blog.me/220791986409?Redirect=Log&from=postView

# Sort
---  
  
# Sort 종류
- QuickSort
- InsertSort
- MergeSort
- HeapSort


비교 정렬 성능의 한계를 알기 위해 **결정 트리 모델** 사용  
이 모델을 사용하여 최악의 경우, 수행시간의 하한이 Ω(nlgn) 증명  
그러나  
원소끼리 비교하는 것 이외의 수단으로 원소의 정렬에 관한 정보를 얻을 수 있으면,  
하한 Ω(nlgn) 극복 가능.  
ex) 계수 정렬 : 상대 순서를 결정할 때 배열 인덱스 사용함으로써 숫자 n개(1,..,k)를 Θ(k+n)  

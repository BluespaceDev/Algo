# Quick Sort



## Quick Sort 3 Way
### PROPERTIES
- not stable
- O(lg(n)) extra space
- O(n2) time, but typically O(n·lg(n)) time
- Best case: O(n) time when O(1) unique keys

### DISCUSSION
The 3-way partition variation of quick sort has slightly higher overhead compared to the standard 2-way partition version. Both have the same best, typical, and worst case time bounds, but this version is highly adaptive in the very common case of sorting with few unique keys.

The 3-way partitioning code shown above is written for clarity rather than optimal performance; it exhibits poor locality, and performs more swaps than necessary. A more efficient but more elaborate 3-way partitioning method is given in Quicksort is Optimal by Robert Sedgewick and Jon Bentley.

When stability is not required, quick sort is the general purpose sorting algorithm of choice. Recently, a novel dual-pivot variant of 3-way partitioning has been discovered that beats the single-pivot 3-way partitioning method both in theory and in practice.

## Dual-pivot 3 Way
fastest of quick sort (random case, dupl case)  
array shape : > pivot_low | <= pivot_low && >= pivot_high | < pivot_high

```
1     2                  3 4 5 6 7 8           9                           10  
|     |                                        |                            |  
low   lo                                       hi                          high  
pivot lo밑 index는 low pivot 보다 작음           hi위 index는 high pivot보다 큼  pivot 
i는 lo부터 hi까지
```

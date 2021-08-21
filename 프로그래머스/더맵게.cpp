#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void push(vector<int>& pq, int val) {
    pq.push_back(val);
    
    int i = pq.size()-1;
    int p = (i-1)/2;
    while(i > 0 && pq[p] > pq[i]) {
        swap(pq[p], pq[i]);
        
        i = p;
        p = (i-1)/2;
    }
}
int pop(vector<int>& pq) {
    auto ans = pq[0];
    
    pq[0] = pq.back();
    pq.pop_back();
    
    int i = 0;
    while(1) {
        int l = i*2+1;
        
        if (l >= pq.size())
            break;
        
        int t = i;
        if (pq[t] > pq[l])
            t = l;
        
        int r = l+1;
        if (r < pq.size() && pq[t] > pq[r])
            t = r;
        
        if (t == i)
            break;
        
        swap(pq[i], pq[t]);
        i = t;
    }
    
    return ans;
}

int solution(vector<int> scoville, int K) {
    vector<int> pq;
    for (auto s : scoville)
        push(pq, s);
    
    int count = 0;
    while(pq[0] < K) {
        if (pq.size() == 1) {
            return -1;
        }
        auto a1 = pop(pq);
        auto a2 = pop(pq);
        push(pq, a1+a2*2);
        count++;
    }
    
    return count;
}

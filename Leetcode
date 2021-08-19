/*
탐색하는 방법과 total_sum에 대한 아이디어를 생각하는 알고리즘

탐색 전에 미리 내 하위 노드에 대한 결과값을 저장할 필요가 있음

곱셈은 범위를 벗어나기 때문에 long 으로 한다음 mod 처리
*/

class Solution {
public:
    const int mod = 1e9+7;
    
    int maxProduct(TreeNode* root) {
        int total_sum = sum(root);
        return find(root, total_sum) % mod;
    }
    int sum(TreeNode* node) {
        if (node == nullptr)
            return 0;
        node->val += sum(node->left) + sum(node->right);
        return node->val;
    }
    long find(TreeNode* node, int total_sum) {
        if (node == nullptr)
            return 0;
        
        long ans = ((long)(total_sum - node->val) * node->val);
        ans = max(ans, find(node->left, total_sum));
        ans = max(ans, find(node->right, total_sum));
        return ans;
    }
};

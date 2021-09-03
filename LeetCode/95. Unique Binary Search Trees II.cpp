//https://leetcode.com/problems/unique-binary-search-trees-ii/
// nullptr 을 생각하면 더 쉽게 풀 수 있다.
// nullptr node 를 해서 코드를 

class Solution {
public:
    vector<TreeNode*> generate(vector<int>& nums) {
        vector<TreeNode*> ans;
        
        for (auto num1 : nums) {            
            vector<int> left_nums, right_nums;
            for (auto num2 : nums) {
                if (num2 < num1)
                    left_nums.push_back(num2);
                else if (num2 > num1)
                    right_nums.push_back(num2);
            }
            
            auto left_child = generate(left_nums);
            auto right_child = generate(right_nums);
            
            if (left_nums.size() && right_nums.size()) {
                for (auto left_node : left_child) {
                    for (auto right_node : right_child) {
                        TreeNode* node = new TreeNode(num1);
                        node->left = left_node;
                        node->right = right_node;
                        ans.push_back(node);
                    }
                }
            }
            else if (left_nums.size()) {
                for (auto left_node : left_child) {
                    TreeNode* node = new TreeNode(num1);
                    node->left = left_node;
                    ans.push_back(node);
                }
            }
            else if (right_child.size()) {
                for (auto right_node : right_child) {
                    TreeNode* node = new TreeNode(num1);
                    node->right = right_node;
                    ans.push_back(node);
                }
            }
            else {
                ans.push_back(new TreeNode(num1));
            }
        }
        
        return ans;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        vector<int> nums;
        for (int i = 1; i <= n; ++i)
            nums.push_back(i);
        return generate(nums);
    }
};

class Solution {
public:
    vector<TreeNode*> generateTrees(int s, int e) {
        if (s > e)
            return {nullptr};
        
        vector<TreeNode*> ans;
        for (int i = s; i <= e; ++i) {
            auto left = generateTrees(s, i-1);
            auto right = generateTrees(i+1, e);
            
            for (auto lnode : left) {
                for (auto rnode : right) {
                    auto node = new TreeNode(i);
                    node->left = lnode;
                    node->right = rnode;
                    ans.push_back(node);
                }
            }
        }
        return ans;
    }
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(1, n);
    }
};

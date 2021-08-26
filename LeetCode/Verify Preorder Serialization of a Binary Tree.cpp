//https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/

class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<string> tree = split(preorder, ',');
        return dfs(tree, 0) == tree.size()-1;
    }
    int dfs(vector<string>& tree, int i) {
        if (tree.size() == i)
            return -1;
        if (tree[i].compare("#") == 0)
            return i;
        
        int l = dfs(tree, i+1);
        if (l == -1)
            return -1;
        return dfs(tree, l+1);
    }
    vector<string> split(string input, char delimiter) {
        vector<string> answer;
        stringstream ss(input);
        string temp;

        while (getline(ss, temp, delimiter)) {
            answer.push_back(temp);
        }

        return answer;
    }
};

class Solution {
public:
    bool isValidSerialization(string preorder) {
        int size = 1;
        for (int i = 0; i < preorder.size(); ++i) {
            while(preorder[i] != ',' && i < preorder.size())
                ++i;
            
            size--;
            if (size < 0)
                return false;
            
            int j = i - 1;
            if (preorder[j] != '#') 
                size += 2;
        }
        return size == 0;
    }
};

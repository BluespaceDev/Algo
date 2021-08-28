class Trie {
public:
    Trie* child[26] = {nullptr,}; // nullptr 로 초기화 안하면 잘못된 주소값(쓰레기값) 참조로 런타임 에러 
    vector<int> ids;
    
    void insert(string& s, int id) {
        Trie* node = this;
        for (auto c : s) {
            int j = c - 'a';
            if (node->child[j] == nullptr) {
                node->child[j] = new Trie();
            }
            node = node->child[j];
        }
        node->ids.push_back(id);
    }
    bool find(string& s, int id) {
        Trie* node = this;
        for (auto c : s) {
            int i = c - 'a';
            if (node->child[i] == nullptr)
                return false;
            node = node->child[i];
        }
        
        for (auto i : node->ids) {
            if (i == id)
                continue;
            return true;
        }
        
        return false;
    }
};

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        Trie trie;
        for (int i = 0; i < strs.size(); ++i) {
            auto words = sub(strs[i], 0);
            for (auto& s : words) {
                trie.insert(s, i);
            }
        }
        
        int lus = -1;
        for (int i = 0; i < strs.size(); ++i) {
            if (!trie.find(strs[i], i)) {
                lus = max(lus, (int)strs[i].length());
            }
        }
        return lus;
    }
    
    vector<string> sub(string s, int i) {
        vector<string> ans;
        
        if (s.length() <= i) {
            ans.push_back(s);
            return ans;
        }

        auto a = sub(s, i+1);
        ans.insert(ans.end(), a.begin(), a.end());
        
        auto b = sub(s.erase(i, 1), i);
        ans.insert(ans.end(), b.begin(), b.end());
        
        return ans;
    }
};

class Solution {
public:
    bool lcs(string& a, string& b) {
        if (a.length() > b.length())
            return false;
        
        int i = 0;
        for (auto c : b) {
            if (i < a.length() && a[i] == c) {
                ++i;
            }
        }
        return i == a.length();
    }
    
    int findLUSlength(vector<string>& strs) {
        int length = -1;
        for (int i = 0; i < strs.size(); ++i) {
            int j = 0;
            for (; j < strs.size(); ++j) {
                if (i == j)
                    continue;
                
                if (lcs(strs[i], strs[j]))
                    break;
            }
            
            if (j == strs.size())
                length = max(length, (int)strs[i].length());
        }
        return length;
    }
};

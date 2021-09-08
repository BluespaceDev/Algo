// https://leetcode.com/problems/shifting-letters/

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        for (int i = shifts.size()-1; i > 0; --i)
            shifts[i-1] += shifts[i] % 26;
        
        for (int i = 0; i < s.length(); ++i)
            shifts[i] = (shifts[i] + s[i] - 'a') % 26;
        
        for (int i = 0; i < s.length(); ++i)
            s[i] = shifts[i] + 'a';
        
        return s;
    }
};

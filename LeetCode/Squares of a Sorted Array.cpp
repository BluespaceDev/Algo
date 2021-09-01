class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int min_value = abs(nums[0]);
        int min_index = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (abs(nums[i]) < min_value) {
                min_value = abs(nums[i]);
                min_index = i;
            }
        }
        
        vector<int> squares(nums.size(), 0);
        squares[0] = nums[min_index] * nums[min_index];
        
        int left = min_index-1;
        int right = min_index+1;
        int i = 1;
        while(i < squares.size()) {
            int lv = (left >= 0) ? abs(nums[left]) : 99999;
            int rv = (right < nums.size()) ? abs(nums[right]) : 99999;
            
            if (lv < rv) {
                squares[i++] = lv * lv;
                --left;
            } else {
                squares[i++] = rv * rv;
                ++right;
            }
        }
        
        return squares;
    }
};

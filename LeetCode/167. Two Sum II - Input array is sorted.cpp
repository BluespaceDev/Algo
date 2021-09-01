class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int a = 0;
        int b = numbers.size()-1;
        while (a < b){
            int sum = numbers[a] + numbers[b];
            if (sum < target)
                ++a;
            else if(sum > target)
                --b;
            else
                break;
        }
        return {a+1, b+1};
    }
};

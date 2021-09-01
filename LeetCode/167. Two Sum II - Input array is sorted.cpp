class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for (int i = 0; i < numbers.size(); ++i) {
            int v = target - numbers[i];
            int j = lower_bound(numbers.begin()+i+1, numbers.end(), v) - numbers.begin();
            if (j >= numbers.size())
                continue;
            
            if (numbers[j] == v)
                return {i+1, j+1};
        }
        return vector<int>();
    }
};


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

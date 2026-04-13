#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = nums[0];
        int Maxsum = nums[0];

        for(int i = 1; i < nums.size(); i++) {
            sum = max(nums[i], sum + nums[i]);
            Maxsum = max(Maxsum, sum);
        }

        return Maxsum;
    }
};

int main() {
    Solution sol;

    
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int result = sol.maxSubArray(nums);

    cout << "Maximum Subarray Sum: " << result << endl;

    return 0;
}

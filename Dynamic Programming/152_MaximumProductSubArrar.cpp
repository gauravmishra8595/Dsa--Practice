#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int curr_max = nums[0];
        int curr_min = nums[0];
        int result = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < 0) {
                swap(curr_max, curr_min);
            }

            curr_max = max(nums[i], curr_max * nums[i]);
            curr_min = min(nums[i], curr_min * nums[i]);

            result = max(result, curr_max);
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-2, 3, -4};
    cout << sol.maxProduct(nums) << endl;  // Expected: 24
    return 0;
}
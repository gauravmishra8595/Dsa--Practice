#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            if (abs(nums[left]) < abs(nums[right])) {
                ans[i] = nums[right] * nums[right];
                right--;
            } else {
                ans[i] = nums[left] * nums[left];
                left++;
            }
        }
        return ans;
    }
};

int main() {
    Solution obj;
    vector<int> nums = {-4, -1, 0,2, 3, 10,19};

    vector<int> result = obj.sortedSquares(nums);

    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}
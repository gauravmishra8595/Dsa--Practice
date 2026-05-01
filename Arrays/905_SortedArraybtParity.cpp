#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        int left = 0, right = n - 1;

        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 0) {
                ans[left++] = nums[i];
            } else {
                ans[right--] = nums[i];
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums = {3, 1, 2, 4};

    Solution obj;
    vector<int> result = obj.sortArrayByParity(nums);

    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}
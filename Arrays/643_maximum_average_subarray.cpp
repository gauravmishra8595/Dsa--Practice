#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();

        int sum = 0;
        for (int i = 0; i < k; i++) {
            sum += nums[i];
        }

        int maxSum = sum;

        for (int i = k; i < n; i++) {
            sum += nums[i];
            sum -= nums[i - k];
            maxSum = max(maxSum, sum);
        }

        return (double) maxSum / k;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 12, -5, -6, 50, 3};
    int k = 4;

    cout << fixed << setprecision(5)
         << sol.findMaxAverage(nums, k) << endl;

    return 0;
}

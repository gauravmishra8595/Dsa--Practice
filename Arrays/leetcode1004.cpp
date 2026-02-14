#include <iostream>
#include <vector>
#include <algorithm> // for max
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, maxLen = 0, zeroCount = 0;

        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) zeroCount++;

            while (zeroCount > k) {
                if (nums[left] == 0) zeroCount--;
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

int main() {
    Solution sol;

    int n, k;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the elements (0 or 1): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter k (maximum zeros to flip): ";
    cin >> k;

    int result = sol.longestOnes(nums, k);
    cout << "Maximum consecutive ones after flipping at most " << k << " zeros: " << result << endl;

    return 0;
}

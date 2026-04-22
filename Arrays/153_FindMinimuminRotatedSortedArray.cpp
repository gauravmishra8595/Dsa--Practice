#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int s = 0;
        int e = nums.size() - 1;

        while (s < e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] > nums[e]) {
                s = mid + 1;
            } else {
                e = mid;
            }
        }

        return nums[s];
    }
};

int main() {
    Solution obj;

    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

    cout << "Minimum element is: " << obj.findMin(nums) << endl;

    return 0;
}
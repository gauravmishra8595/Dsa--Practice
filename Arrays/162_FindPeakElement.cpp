#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int s = 0;
        int e = nums.size() - 1;

        while (s < e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] < nums[mid + 1]) {
                s = mid + 1;
            } else {
                e = mid;
            }
        }

        return s;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 1};
    int peak1 = sol.findPeakElement(nums1);
    cout << "Peak index (test 1): " << peak1 
         << ", value: " << nums1[peak1] << endl;

    vector<int> nums2 = {1, 2, 1, 3, 5, 6, 4};
    int peak2 = sol.findPeakElement(nums2);
    cout << "Peak index (test 2): " << peak2 
         << ", value: " << nums2[peak2] << endl;

    return 0;
}
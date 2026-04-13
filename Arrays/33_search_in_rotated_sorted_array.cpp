#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int s = 0;
        int e = nums.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] == target)
                return mid;

            // Left half sorted
            if (nums[s] <= nums[mid]) {
                if (nums[s] <= target && target < nums[mid])
                    e = mid - 1;
                else
                    s = mid + 1;
            }
            // Right half sorted
            else {
                if (nums[mid] < target && target <= nums[e])
                    s = mid + 1;
                else
                    e = mid - 1;
            }
        }

        return -1;
    }
};

int main() {
    Solution obj;
    vector<int> nums = {4,5,6,7,0,1,2};
    int target = 0;

    int result = obj.search(nums, target);

    if (result != -1)
        cout << "Target found at index: " << result << endl;
    else
        cout << "Target not found" << endl;

    return 0;
}
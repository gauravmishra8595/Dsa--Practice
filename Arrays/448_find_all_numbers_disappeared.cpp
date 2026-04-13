#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();

        for (const int num : nums) {
            int index = abs(num) - 1;
            nums[index] = -abs(nums[index]);
        }

        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                ans.push_back(i + 1);
            }
        }

        return ans;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};

    vector<int> result = obj.findDisappearedNumbers(nums);

    cout << "Missing numbers: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
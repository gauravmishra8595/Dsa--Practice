#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
public:
    vector<int> findErrorNums(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> res(2, 0);

        // Step 1: find duplicate
        for (int i = 0; i < n; i++)
        {
            int idx = abs(nums[i]) - 1;

            if (nums[idx] < 0)
            {
                res[0] = abs(nums[i]); // duplicate
            }
            else
            {
                nums[idx] = -nums[idx];
            }
        }

        // Step 2: find missing
        for (int i = 0; i < n; i++)
        {
            if (nums[i] > 0)
            {
                res[1] = i + 1;
            }
        }

        return res;
    }
};

int main()
{
    vector<int> nums = {1, 2, 2, 4};

    Solution sol;
    vector<int> ans = sol.findErrorNums(nums);

    cout << "Duplicate: " << ans[0] << endl;
    cout << "Missing: " << ans[1] << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    void getPerms(vector<int> &nums, int idx, vector<vector<int>> &ans)
    {
        if (idx == nums.size())
        {
            ans.push_back(nums);
            return;
        }

        for (int i = idx; i < nums.size(); i++)
        {
            swap(nums[idx], nums[i]);

            getPerms(nums, idx + 1, ans);

            swap(nums[idx], nums[i]); // backtrack
        }
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> ans;
        getPerms(nums, 0, ans);
        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 2, 3};

    vector<vector<int>> result = sol.permute(nums);

    cout << "Permutations:\n";

    for (const auto &perm : result)
    {
        cout << "[ ";
        for (int x : perm)
        {
            cout << x << " ";
        }
        cout << "]\n";
    }

    return 0;
}
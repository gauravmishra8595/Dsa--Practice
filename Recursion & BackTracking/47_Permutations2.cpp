#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

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

        unordered_set<int> used; // values used at this recursion level

        for (int i = idx; i < nums.size(); i++)
        {

            if (used.count(nums[i]))
            {
                continue; // skip duplicates
            }

            used.insert(nums[i]);

            swap(nums[idx], nums[i]);

            getPerms(nums, idx + 1, ans);

            swap(nums[idx], nums[i]); // backtrack
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;
        getPerms(nums, 0, ans);

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 1, 2};

    vector<vector<int>> result = sol.permuteUnique(nums);

    cout << "Unique Permutations:\n";

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
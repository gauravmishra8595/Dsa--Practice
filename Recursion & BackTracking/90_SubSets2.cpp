#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void getAllSubsets(vector<int> &nums,
                       vector<int> &ans,
                       int i,
                       vector<vector<int>> &allSubsets)
    {

        if (i == nums.size())
        {
            allSubsets.push_back(ans);
            return;
        }

        // Include current element
        ans.push_back(nums[i]);
        getAllSubsets(nums, ans, i + 1, allSubsets);
        ans.pop_back();

        // Skip duplicates
        int idx = i + 1;
        while (idx < nums.size() && nums[idx] == nums[idx - 1])
        {
            idx++;
        }

        // Exclude current element and all duplicates
        getAllSubsets(nums, ans, idx, allSubsets);
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        sort(nums.begin(), nums.end()); // important for handling duplicates

        vector<vector<int>> allSubsets;
        vector<int> ans;

        getAllSubsets(nums, ans, 0, allSubsets);

        return allSubsets;
    }
};

// -------- main function for VS Code testing --------
int main()
{
    Solution sol;

    vector<int> nums = {1, 2, 2};

    vector<vector<int>> result = sol.subsetsWithDup(nums);

    cout << "Unique Subsets:\n";
    for (auto &subset : result)
    {
        cout << "{ ";
        for (int x : subset)
        {
            cout << x << " ";
        }
        cout << "}\n";
    }

    return 0;
}
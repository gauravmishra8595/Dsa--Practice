#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void allSubsets(vector<int> &nums,
                    vector<int> &ans,
                    int i,
                    vector<vector<int>> &getsubsets)
    {

        if (i == nums.size())
        {
            getsubsets.push_back(ans);
            return;
        }

        // Include current element
        ans.push_back(nums[i]);
        allSubsets(nums, ans, i + 1, getsubsets);

        // Exclude current element (backtrack)
        ans.pop_back();
        allSubsets(nums, ans, i + 1, getsubsets);
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> getsubsets;
        vector<int> ans;

        allSubsets(nums, ans, 0, getsubsets);

        return getsubsets;
    }
};

// Optional main function for VS Code testing
int main()
{
    Solution sol;

    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = sol.subsets(nums);

    for (auto &subset : result)
    {
        cout << "{ ";
        for (int x : subset)
        {
            cout << x << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
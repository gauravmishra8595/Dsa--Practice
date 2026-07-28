#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    void backtrack(vector<int> &candidates,
                   int target,
                   int start,
                   vector<int> &path,
                   vector<vector<int>> &result)
    {

        if (target == 0)
        {
            result.push_back(path);
            return;
        }

        for (int i = start; i < candidates.size(); i++)
        {

            if (i > start && candidates[i] == candidates[i - 1])
            {
                continue;
            }

            if (candidates[i] > target)
            {
                break;
            }

            path.push_back(candidates[i]);

            backtrack(candidates,
                      target - candidates[i],
                      i + 1,
                      path,
                      result);

            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {

        sort(candidates.begin(), candidates.end());

        vector<vector<int>> result;
        vector<int> path;

        backtrack(candidates, target, 0, path, result);

        return result;
    }
};

int main()
{
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    Solution obj;
    vector<vector<int>> ans = obj.combinationSum2(candidates, target);

    for (auto &vec : ans)
    {
        cout << "[ ";
        for (int x : vec)
        {
            cout << x << " ";
        }
        cout << "]\n";
    }

    return 0;
}
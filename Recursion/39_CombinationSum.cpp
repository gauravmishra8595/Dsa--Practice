#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void GetSum(vector<int>& candidates,
                int target,
                int i,
                vector<int>& path,
                vector<vector<int>>& result) {

        // Valid combination found
        if (target == 0) {
            result.push_back(path);
            return;
        }

        // Invalid path
        if (i == candidates.size() || target < 0) {
            return;
        }

        // Choice 1: Take current candidate
        path.push_back(candidates[i]);
        GetSum(candidates,
               target - candidates[i],
               i,               // stay at same index
               path,
               result);

        path.pop_back();        // backtrack

        // Choice 2: Skip current candidate
        GetSum(candidates,
               target,
               i + 1,
               path,
               result);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> path;

        GetSum(candidates, target, 0, path, result);

        return result;
    }
};

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    Solution obj;
    vector<vector<int>> ans = obj.combinationSum(candidates, target);

    cout << "Combinations:\n";

    for (auto &vec : ans) {
        cout << "[ ";
        for (int num : vec) {
            cout << num << " ";
        }
        cout << "]\n";
    }

    return 0;
}
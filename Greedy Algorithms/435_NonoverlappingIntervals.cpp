#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.empty())
            return 0;

        // sort by end time
        sort(intervals.begin(), intervals.end(),
             [](const vector<int> &a, const vector<int> &b)
             {
                 return a[1] < b[1];
             });

        int count = 0;
        int end = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] < end)
            {
                // overlap → remove it
                count++;
            }
            else
            {
                // no overlap → take it
                end = intervals[i][1];
            }
        }

        return count;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> intervals1 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    vector<vector<int>> intervals2 = {{1, 2}, {1, 2}, {1, 2}};
    vector<vector<int>> intervals3 = {{1, 2}, {2, 3}};

    cout << "Test 1: " << sol.eraseOverlapIntervals(intervals1) << endl;
    cout << "Test 2: " << sol.eraseOverlapIntervals(intervals2) << endl;
    cout << "Test 3: " << sol.eraseOverlapIntervals(intervals3) << endl;

    return 0;
}
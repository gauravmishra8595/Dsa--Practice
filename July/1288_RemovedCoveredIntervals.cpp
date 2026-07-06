#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {

        sort(intervals.begin(), intervals.end(),
             [](vector<int>& a, vector<int>& b) {
                 if (a[0] == b[0])
                     return a[1] > b[1];
                 return a[0] < b[0];
             });

        int count = 1;
        int maxRight = intervals[0][1];

        for (int i = 1; i < intervals.size(); i++) {

            // Current interval is covered
            if (intervals[i][1] <= maxRight) {
                continue;
            }

            // Not covered
            count++;
            maxRight = intervals[i][1];
        }

        return count;
    }
};

int main() {

    Solution obj;

    vector<vector<int>> intervals = {
        {1,4},
        {3,6},
        {2,8}
    };

    cout << "Remaining Intervals = "
         << obj.removeCoveredIntervals(intervals);

    return 0;
}

/*
======================== BRUTE FORCE ========================

Idea:
For every interval, check every other interval.
If another interval completely covers it,
mark it as covered.

Condition:
Interval A covers Interval B if

A.start <= B.start
AND
A.end >= B.end

Time Complexity:
O(n^2)

Space Complexity:
O(1)


Pseudo Code

covered = 0

for every interval i
    for every interval j
        if i != j and
           intervals[j][0] <= intervals[i][0] &&
           intervals[j][1] >= intervals[i][1]
            covered++
            break

return n - covered


=============================================================



======================== OPTIMAL ============================

Observation:
After sorting,

1. Smaller starting interval comes first.
2. If two intervals have same start,
   larger ending interval comes first.

Example:

[1,4]
[1,3]

instead of

[1,3]
[1,4]

Now simply keep track of the maximum right endpoint seen so far.

If current interval's end <= maxRight,
then it is completely covered.

Otherwise,
it survives and update maxRight.

Time Complexity:
Sorting : O(n log n)
Traversal : O(n)

Overall:
O(n log n)

Space Complexity:
O(1) (excluding sorting stack)

=============================================================*/
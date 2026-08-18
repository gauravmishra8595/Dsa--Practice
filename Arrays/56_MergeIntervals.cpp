#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ans;

        for (auto &interval : intervals) {
            if (ans.empty() || ans.back()[1] < interval[0]) {
                ans.push_back(interval);
            }
            else {
                ans.back()[1] = max(ans.back()[1], interval[1]);
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals = {
        {1, 3},
        {2, 6},
        {8, 10},
        {15, 18}
    };

    vector<vector<int>> ans = sol.merge(intervals);

    for (auto &interval : ans) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }

    cout << '\n';

    return 0;
}

/*
======================================================================
LeetCode 56 - Merge Intervals
======================================================================

Problem Statement
-----------------
Given an array of intervals where:

intervals[i] = [starti, endi]

merge all overlapping intervals and return an array of the
non-overlapping intervals that cover all the intervals in the input.


Example
-------
Input:
intervals = [[1,3],[2,6],[8,10],[15,18]]

Output:
[[1,6],[8,10],[15,18]]

Explanation:

[1,3] and [2,6] overlap.

They are merged into:

[1,6]

The remaining intervals do not overlap.


----------------------------------------------------------------------
Brute Force Approach
----------------------------------------------------------------------

Idea
----
Compare every interval with every other interval and repeatedly merge
overlapping intervals.

One simple approach is to keep checking pairs of intervals. Whenever
two intervals overlap, merge them and restart the process.

This approach is inefficient because the same intervals may be checked
many times.


Pseudo Code
-----------
1. Repeat until no changes are made:
      For every pair of intervals:
          If they overlap:
              Merge them.
              Remove the second interval.
              Mark that a change occurred.

2. Return the intervals.


Complete Brute Force Code
--------------------------
The following code is only for revision.

    /*
    vector<vector<int>> mergeBruteForce(vector<vector<int>>& intervals) {
        bool changed = true;

        while (changed) {
            changed = false;

            for (int i = 0; i < intervals.size(); i++) {
                for (int j = i + 1; j < intervals.size(); j++) {

                    if (intervals[i][1] >= intervals[j][0] &&
                        intervals[j][1] >= intervals[i][0]) {

                        intervals[i][0] =
                            min(intervals[i][0], intervals[j][0]);

                        intervals[i][1] =
                            max(intervals[i][1], intervals[j][1]);

                        intervals.erase(intervals.begin() + j);

                        changed = true;
                        break;
                    }
                }

                if (changed)
                    break;
            }
        }

        return intervals;
    }
    */


// Time Complexity
// ---------------
// In the worst case, many repeated comparisons and erasures occur.

// Time = O(n²)


// Space Complexity
// ----------------
// Apart from the input and output:

// Space = O(1)

// Depending on vector erasures, additional shifting may also occur.


// ----------------------------------------------------------------------
// Optimal Approach
// ----------------------------------------------------------------------

// Observation
// -----------
// Sort all intervals by their starting point.

// Example:

// [[1,3], [2,6], [8,10], [15,18]]

// After sorting, intervals are arranged from left to right.

// Now we only need to compare the current interval with the last
// merged interval.


// Intuition
// ---------
// Suppose the last merged interval is:

// [1,6]

// and the current interval is:

// [2,8]

// Since:

// 6 >= 2

// they overlap.

// Therefore, merge them:

// [1,8]


// If instead:

// last = [1,6]
// current = [8,10]

// Since:

// 6 < 8

// there is no overlap.

// So we start a new interval.


// The important greedy idea is:

// "After sorting by start time, only compare the current interval with
// the last interval in the answer."


// Pseudo Code
// -----------
// 1. Sort intervals by starting time.

// 2. Create an empty answer array.

// 3. For every interval [start, end]:

//       If answer is empty OR
//          answer.back().end < start:

//           Add current interval.

//       Else:

//           Merge:
//           answer.back().end =
//               max(answer.back().end, end)

// 4. Return answer.


// Complete Optimal Code
// ----------------------
// LeetCode version:

    /*
    class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            sort(intervals.begin(), intervals.end());

            vector<vector<int>> ans;

            for (auto &interval : intervals) {

                if (ans.empty() ||
                    ans.back()[1] < interval[0]) {

                    ans.push_back(interval);
                }
                else {
                    ans.back()[1] =
                        max(ans.back()[1], interval[1]);
                }
            }

            return ans;
        }
    };
    */


// Time Complexity
// ---------------
// Sorting:

// O(n log n)

// Traversal:

// O(n)

// Overall:

// Time = O(n log n)


// Space Complexity
// ----------------
// Output array:

// O(n)

// Ignoring the output:

// O(1) auxiliary space apart from sorting.


// ----------------------------------------------------------------------
// Dry Run
// ----------------------------------------------------------------------

// Input:

// intervals = [[1,3],[2,6],[8,10],[15,18]]


// Step 1: Sort

// [[1,3],[2,6],[8,10],[15,18]]


// Step 2:

// Current = [1,3]

// Answer is empty.

// Add:

// ans = [[1,3]]


// Step 3:

// Current = [2,6]

// Last merged interval = [1,3]

// Check:

// 3 >= 2

// They overlap.

// Merge:

// ans = [[1,6]]


// Step 4:

// Current = [8,10]

// Last merged interval = [1,6]

// Check:

// 6 < 8

// No overlap.

// Add:

// ans = [[1,6],[8,10]]


// Step 5:

// Current = [15,18]

// Last merged interval = [8,10]

// Check:

// 10 < 15

// No overlap.

// Add:

// ans = [[1,6],[8,10],[15,18]]


// Final Answer:

// [[1,6],[8,10],[15,18]]


// ----------------------------------------------------------------------
// Interview Notes
// ----------------------------------------------------------------------

// Pattern
// -------
// Sorting + Greedy + Interval Merging


// Key Observation
// ---------------
// After sorting by start time, an interval only needs to be compared
// with the last merged interval.


// Common Mistakes
// ---------------
// 1. Forgetting to sort the intervals first.

// 2. Using:

//    lastEnd <= currentStart

//    when the problem considers touching intervals as overlapping.

//    Correct condition:

//    lastEnd < currentStart

//    means no overlap.

// 3. Updating both start and end unnecessarily.

//    Once sorted, the start of the merged interval is already correct.

// 4. Creating a new interval instead of extending the existing one
//    when intervals overlap.

// 5. Forgetting to take the maximum end:

//    max(lastEnd, currentEnd)


// When to Use This Approach
// -------------------------
// Use this pattern when:

// - You are given intervals.
// - You need to merge overlapping ranges.
// - You need non-overlapping ranges.
// - Intervals can be ordered by their starting points.

// General Rule:

// "For interval problems, sorting by start time often turns a
// complicated overlap problem into a simple one-pass greedy solution."

// ======================================================================
// */
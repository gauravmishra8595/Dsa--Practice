#include <bits/stdc++.h>
using namespace std;

/* =========================
   OPTIMAL SOLUTION
   ========================= */
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int minDiff = INT_MAX;
        vector<vector<int>> ans;

        for (int i = 1; i < arr.size(); i++) {
            int diff = arr[i] - arr[i - 1];

            if (diff < minDiff) {
                minDiff = diff;
                ans.clear();
                ans.push_back({arr[i - 1], arr[i]});
            }
            else if (diff == minDiff) {
                ans.push_back({arr[i - 1], arr[i]});
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {4, 2, 1, 3};

    vector<vector<int>> ans = sol.minimumAbsDifference(arr);

    for (auto &pair : ans) {
        cout << "[" << pair[0] << ", " << pair[1] << "] ";
    }

    cout << '\n';

    return 0;
}

/*
======================================================================
LeetCode 1200 - Minimum Absolute Difference
======================================================================

Problem Statement
-----------------
Given an array of distinct integers arr, find all pairs of elements
with the minimum absolute difference among all possible pairs.

Return a list of pairs in ascending order.

Each pair [a, b] should satisfy:

a < b

The pairs should also be returned in lexicographical order.


Example
-------
Input:
arr = [4, 2, 1, 3]

Output:
[[1, 2], [2, 3], [3, 4]]

Explanation:

After sorting:

[1, 2, 3, 4]

Differences:

2 - 1 = 1
3 - 2 = 1
4 - 3 = 1

Minimum difference = 1

Therefore:

[1, 2]
[2, 3]
[3, 4]


----------------------------------------------------------------------
Brute Force Approach
----------------------------------------------------------------------

Idea
----
Check every possible pair of elements.

For every pair (i, j):

1. Calculate the absolute difference.
2. Keep track of the minimum difference.
3. If the difference is smaller than the current minimum:
      Clear the answer and add this pair.
4. If the difference is equal to the minimum:
      Add this pair.


Pseudo Code
-----------
1. minDiff = infinity
2. ans = empty list

3. For i = 0 to n - 1:
      For j = i + 1 to n - 1:

          diff = abs(arr[i] - arr[j])

          If diff < minDiff:
              minDiff = diff
              clear ans
              add [min(arr[i], arr[j]), max(arr[i], arr[j])]

          Else if diff == minDiff:
              add the pair

4. Sort ans.
5. Return ans.


Complete Brute Force Code
--------------------------
The following code is only for revision.

    /*
    vector<vector<int>> minimumAbsDifferenceBruteForce(
        vector<int>& arr) {

        int n = arr.size();
        int minDiff = INT_MAX;

        vector<vector<int>> ans;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int a = min(arr[i], arr[j]);
                int b = max(arr[i], arr[j]);

                int diff = b - a;

                if (diff < minDiff) {
                    minDiff = diff;
                    ans.clear();
                    ans.push_back({a, b});
                }
                else if (diff == minDiff) {
                    ans.push_back({a, b});
                }
            }
        }

        sort(ans.begin(), ans.end());

        return ans;
    }
    */


// Time Complexity
// ---------------
// There are O(n²) pairs.

// Time = O(n²)


// Space Complexity
// ----------------
// Apart from the answer:

// Space = O(1)

// Including the answer:

// Space = O(n)


// ----------------------------------------------------------------------
// Optimal Approach
// ----------------------------------------------------------------------

// Observation
// -----------
// Sort the array first.

// After sorting:

// a[0] < a[1] < a[2] < ... < a[n-1]

// The minimum absolute difference must always occur between two
// adjacent elements.

// Why?

// Suppose we have:

// a < b < c

// Then:

// c - a > b - a
// and
// c - a > c - b

// So a non-adjacent pair cannot have a smaller difference than the
// adjacent elements between them.


// Intuition
// ---------
// Sorting converts the problem into a neighboring-elements problem.

// Example:

// Original:
// [4, 2, 1, 3]

// After sorting:
// [1, 2, 3, 4]

// Now we only need to check:

// 1, 2 -> difference 1
// 2, 3 -> difference 1
// 3, 4 -> difference 1

// The minimum difference is 1.

// Whenever we find a smaller difference, clear the answer and store
// the new pair.

// Whenever we find the same difference, add the pair.


// Pseudo Code
// -----------
// 1. Sort arr.

// 2. minDiff = infinity
// 3. ans = empty list

// 4. For i = 1 to n - 1:

//       diff = arr[i] - arr[i - 1]

//       If diff < minDiff:
//           minDiff = diff
//           clear ans
//           add [arr[i - 1], arr[i]]

//       Else if diff == minDiff:
//           add [arr[i - 1], arr[i]]

// 5. Return ans.


// Complete Optimal Code
// ----------------------
// LeetCode version:

    /*
    class Solution {
    public:
        vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
            sort(arr.begin(), arr.end());

            int minDiff = INT_MAX;
            vector<vector<int>> ans;

            for (int i = 1; i < arr.size(); i++) {
                int diff = arr[i] - arr[i - 1];

                if (diff < minDiff) {
                    minDiff = diff;
                    ans.clear();
                    ans.push_back({arr[i - 1], arr[i]});
                }
                else if (diff == minDiff) {
                    ans.push_back({arr[i - 1], arr[i]});
                }
            }

            return ans;
        }
    };
    */


// Time Complexity
// ---------------
// Sorting takes:

// O(n log n)

// The single loop takes:

// O(n)

// Therefore:

// Time = O(n log n)


// Space Complexity
// ----------------
// The sorting algorithm uses O(log n) auxiliary stack space
// in typical implementations.

// Ignoring the output:

// Space = O(log n)

// Including the answer:

// Space = O(n)


// ----------------------------------------------------------------------
// Dry Run
// ----------------------------------------------------------------------

// arr = [4, 2, 1, 3]

// Step 1: Sort

// arr = [1, 2, 3, 4]


// Step 2: Check adjacent differences

// i = 1:

// Pair = [1, 2]
// diff = 2 - 1 = 1

// minDiff = 1

// ans = [[1, 2]]


// i = 2:

// Pair = [2, 3]
// diff = 3 - 2 = 1

// diff == minDiff

// ans = [[1, 2], [2, 3]]


// i = 3:

// Pair = [3, 4]
// diff = 4 - 3 = 1

// diff == minDiff

// ans = [[1, 2], [2, 3], [3, 4]]


// Final Answer:

// [[1, 2], [2, 3], [3, 4]]


// ----------------------------------------------------------------------
// Interview Notes
// ----------------------------------------------------------------------

// Pattern
// -------
// Sorting + Adjacent Element Comparison


// Key Observation
// ---------------
// After sorting, the minimum absolute difference can only occur
// between adjacent elements.


// Common Mistakes
// ---------------
// 1. Checking every pair after sorting.

//    This unnecessarily gives O(n²).

// 2. Forgetting to clear the answer when a smaller difference is found.

// 3. Using abs() unnecessarily after sorting.

//    Since arr is sorted:

//    arr[i] - arr[i - 1]

//    is always non-negative.

// 4. Forgetting to add pairs when the difference equals minDiff.

// 5. Not sorting the array first.


// When to Use This Approach
// -------------------------
// Use this pattern when:

// - You need the minimum difference between any two values.
// - You need all pairs having the minimum difference.
// - Sorting can establish an ordering relationship.
// - A global pair comparison can be reduced to adjacent comparisons.

// General Rule:

// "When looking for the minimum difference between numbers,
// try sorting first and check adjacent elements."

// ======================================================================
// */
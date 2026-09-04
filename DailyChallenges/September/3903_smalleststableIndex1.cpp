#include <bits/stdc++.h>
using namespace std;

// Optimal solution
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> minfromindex(n);
        int minele = INT_MAX;

        for (int i = n - 1; i >= 0; i--) {
            minele = min(minele, nums[i]);
            minfromindex[i] = minele;
        }

        int maxel = INT_MIN;

        for (int i = 0; i < n; i++) {
            maxel = max(maxel, nums[i]);

            if (maxel - minfromindex[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {10, 5, 8, 7, 6};
    int k = 3;

    cout << sol.firstStableIndex(nums, k) << '\n';

    return 0;
}

/*
======================================================================
                         DSA NOTEBOOK
======================================================================

Problem Statement:
------------------
Given an array nums and an integer k, find the first index i such that:

    max(nums[0 ... i]) - min(nums[i ... n-1]) <= k

Return the first such index. If no such index exists, return -1.

Example:
--------
nums = [10, 5, 8, 7, 6]
k = 3

For i = 0:
    max(nums[0...0]) = 10
    min(nums[0...4]) = 5
    difference = 10 - 5 = 5 > 3

For i = 1:
    max(nums[0...1]) = 10
    min(nums[1...4]) = 5
    difference = 10 - 5 = 5 > 3

For i = 2:
    max(nums[0...2]) = 10
    min(nums[2...4]) = 6
    difference = 10 - 6 = 4 > 3

For i = 3:
    max(nums[0...3]) = 10
    min(nums[3...4]) = 6
    difference = 10 - 6 = 4 > 3

For i = 4:
    max(nums[0...4]) = 10
    min(nums[4...4]) = 6
    difference = 10 - 6 = 4 > 3

Answer = -1


----------------------------------------------------------------------
Brute Force Approach
----------------------------------------------------------------------

Idea:
-----
For every index i:
    1. Find maximum element in nums[0 ... i].
    2. Find minimum element in nums[i ... n-1].
    3. Check whether their difference is <= k.
    4. Return the first valid index.

This directly follows the definition but repeatedly scans the array.

Pseudo Code:
------------
for i = 0 to n-1:
    leftMax = -infinity
    for j = 0 to i:
        leftMax = max(leftMax, nums[j])

    rightMin = +infinity
    for j = i to n-1:
        rightMin = min(rightMin, nums[j])

    if leftMax - rightMin <= k:
        return i

return -1


Complete Brute Force Code:
--------------------------
/*
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int leftMax = INT_MIN;

            for (int j = 0; j <= i; j++) {
                leftMax = max(leftMax, nums[j]);
            }

            int rightMin = INT_MAX;

            for (int j = i; j < n; j++) {
                rightMin = min(rightMin, nums[j]);
            }

            if (leftMax - rightMin <= k) {
                return i;
            }
        }

        return -1;
    }
};
*/

// Time Complexity:
// ----------------
// O(N^2)

// Space Complexity:
// -----------------
// O(1)


// ----------------------------------------------------------------------
// Optimal Approach
// ----------------------------------------------------------------------

// Observation:
// ------------
// For every index i, we need:

//     max(nums[0 ... i])

// and

//     min(nums[i ... n-1])

// The prefix maximum can be maintained while traversing from left to right.

// The suffix minimum can be precomputed by traversing from right to left.

// Thus, both required values can be obtained in O(1) for every index.

// Intuition:
// ----------
// Precompute:

//     minfromindex[i] = minimum element from i to n-1.

// Then while moving from left to right, maintain:

//     maxel = maximum element from 0 to i.

// At every index:

//     maxel - minfromindex[i] <= k

// If true, i is the first stable index, so return immediately.

// Pseudo Code:
// ------------
// n = nums.size()

// Create suffix minimum array minfromindex

// minele = +infinity

// for i = n-1 down to 0:
//     minele = min(minele, nums[i])
//     minfromindex[i] = minele

// maxel = -infinity

// for i = 0 to n-1:
//     maxel = max(maxel, nums[i])

//     if maxel - minfromindex[i] <= k:
//         return i

// return -1


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> minfromindex(n);
        int minele = INT_MAX;

        for (int i = n - 1; i >= 0; i--) {
            minele = min(minele, nums[i]);
            minfromindex[i] = minele;
        }

        int maxel = INT_MIN;

        for (int i = 0; i < n; i++) {
            maxel = max(maxel, nums[i]);

            if (maxel - minfromindex[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};
*/

// Time Complexity:
// ----------------
// O(N)

// One pass to build suffix minimum.
// One pass to find the first valid index.

// Total = O(N)

// Space Complexity:
// -----------------
// O(N)

// The suffix minimum array requires O(N) extra space.


// ----------------------------------------------------------------------
// Dry Run with Example
// ----------------------------------------------------------------------

// nums = [10, 5, 8, 7, 6]
// k = 3

// Step 1: Build suffix minimum array

// i = 4:
//     min = 6
//     suffix[4] = 6

// i = 3:
//     min = min(6, 7) = 6
//     suffix[3] = 6

// i = 2:
//     min = min(6, 8) = 6
//     suffix[2] = 6

// i = 1:
//     min = min(6, 5) = 5
//     suffix[1] = 5

// i = 0:
//     min = min(5, 10) = 5
//     suffix[0] = 5

// suffix = [5, 5, 6, 6, 6]


// Step 2: Traverse from left to right

// i = 0:
//     maxel = 10
//     10 - 5 = 5 > 3
//     Not valid.

// i = 1:
//     maxel = max(10, 5) = 10
//     10 - 5 = 5 > 3
//     Not valid.

// i = 2:
//     maxel = max(10, 8) = 10
//     10 - 6 = 4 > 3
//     Not valid.

// i = 3:
//     maxel = max(10, 7) = 10
//     10 - 6 = 4 > 3
//     Not valid.

// i = 4:
//     maxel = max(10, 6) = 10
//     10 - 6 = 4 > 3
//     Not valid.

// Answer = -1


// ----------------------------------------------------------------------
// Interview Notes
// ----------------------------------------------------------------------

// Pattern:
// --------
// Prefix Maximum + Suffix Minimum

// Key Observation:
// ----------------
// At each index i, the condition depends only on:

//     maximum of the prefix [0 ... i]
//     minimum of the suffix [i ... n-1]

// Precomputing one of these arrays and maintaining the other incrementally
// reduces the solution from O(N^2) to O(N).

// Common Mistakes:
// ----------------
// 1. Recomputing prefix maximum for every index.
// 2. Recomputing suffix minimum for every index.
// 3. Using the minimum of the prefix instead of the suffix.
// 4. Using the maximum of the suffix instead of the prefix.
// 5. Returning the last valid index instead of the first valid index.
// 6. Forgetting to handle the case where no valid index exists.
// 7. Using int when the problem's constraints can make the subtraction
//    overflow; use long long if required by the constraints.

// When to use this approach:
// --------------------------
// Use Prefix/Suffix preprocessing when:

// - A condition involves a prefix aggregate and a suffix aggregate.
// - You repeatedly need max/min over ranges sharing an endpoint.
// - A direct nested-loop solution is O(N^2).
// - The aggregate operation is associative and can be maintained
//   incrementally, such as min, max, sum, etc.

// Core Template:
// --------------
// suffix[i] = aggregate of nums[i ... n-1]

// Then scan from left to right while maintaining:

// prefixAggregate = aggregate of nums[0 ... i]

// Check the required condition at every index.

// ======================================================================
// */

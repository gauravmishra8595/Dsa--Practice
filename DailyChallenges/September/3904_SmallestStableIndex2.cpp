#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(nums[i], suffixMin[i + 1]);
        }

        int prefixMax = nums[0];

        for (int i = 0; i < n; ++i) {
            prefixMax = max(prefixMax, nums[i]);

            if (prefixMax - suffixMin[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {5, 0, 1, 4};
    cout << sol.firstStableIndex(nums1, 3) << '\n';  // 3

    vector<int> nums2 = {3, 2, 1};
    cout << sol.firstStableIndex(nums2, 1) << '\n';  // -1

    vector<int> nums3 = {0};
    cout << sol.firstStableIndex(nums3, 0) << '\n';  // 0

    return 0;
}

/*
================================================================================
                    LEETCODE 3904 - SMALLEST STABLE INDEX II
================================================================================

Problem Statement:
------------------
You are given an integer array nums of length n and an integer k.

For every index i, define its instability score as:

    max(nums[0..i]) - min(nums[i..n-1])

An index i is stable if its instability score is <= k.

Return the smallest stable index. If no stable index exists, return -1.


Example:
--------
nums = [5, 0, 1, 4], k = 3

Index 0:
    max([5]) = 5
    min([5,0,1,4]) = 0
    score = 5 - 0 = 5

Index 1:
    max([5,0]) = 5
    min([0,1,4]) = 0
    score = 5 - 0 = 5

Index 2:
    max([5,0,1]) = 5
    min([1,4]) = 1
    score = 5 - 1 = 4

Index 3:
    max([5,0,1,4]) = 5
    min([4]) = 4
    score = 5 - 4 = 1

Since 1 <= 3, index 3 is stable.

Answer = 3


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
For every index i:

1. Find the maximum from nums[0] to nums[i].
2. Find the minimum from nums[i] to nums[n-1].
3. Check whether:
       maxLeft - minRight <= k
4. Return the first valid index.

The problem is that we repeatedly scan the same elements.

Pseudo Code:
------------
for i = 0 to n-1:
    maxLeft = -INF
    for j = 0 to i:
        maxLeft = max(maxLeft, nums[j])

    minRight = INF
    for j = i to n-1:
        minRight = min(minRight, nums[j])

    if maxLeft - minRight <= k:
        return i

return -1


Complete Brute Force Code:
--------------------------
/*
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            int maxLeft = INT_MIN;
            int minRight = INT_MAX;

            for (int j = 0; j <= i; ++j) {
                maxLeft = max(maxLeft, nums[j]);
            }

            for (int j = i; j < n; ++j) {
                minRight = min(minRight, nums[j]);
            }

            if (maxLeft - minRight <= k) {
                return i;
            }
        }

        return -1;
    }
};
*/

// Time Complexity:
// ----------------
// O(n^2)

// For every index, we may scan O(n) elements.


// Space Complexity:
// -----------------
// O(1) extra space.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The repeated work is finding:

//     max(nums[0..i])
//     min(nums[i..n-1])

// The prefix maximum can be maintained while traversing from left to right.

// The suffix minimum can be precomputed once from right to left.

// Define:

//     suffixMin[i] = min(nums[i..n-1])

// Then for every index i:

//     instability = prefixMax - suffixMin[i]

// Both values are available in O(1).


// Intuition:
// ----------
// Instead of recomputing the maximum and minimum for every index:

// 1. Precompute all suffix minimums.
// 2. Maintain the prefix maximum while scanning from left to right.
// 3. The first index satisfying:

//        prefixMax - suffixMin[i] <= k

//    is the answer.

// Because we scan indices from left to right, the first valid index is
// automatically the smallest stable index.


// Pseudo Code:
// ------------
// n = nums.size()

// Create suffixMin array of size n.

// suffixMin[n-1] = nums[n-1]

// for i = n-2 down to 0:
//     suffixMin[i] = min(nums[i], suffixMin[i+1])

// prefixMax = nums[0]

// for i = 0 to n-1:
//     prefixMax = max(prefixMax, nums[i])

//     if prefixMax - suffixMin[i] <= k:
//         return i

// return -1


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(nums[i], suffixMin[i + 1]);
        }

        int prefixMax = nums[0];

        for (int i = 0; i < n; ++i) {
            prefixMax = max(prefixMax, nums[i]);

            if (prefixMax - suffixMin[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};
*/


// Time Complexity:
// ----------------
// O(n)

// - O(n) to build suffixMin.
// - O(n) to scan and maintain prefixMax.

// Total = O(n)


// Space Complexity:
// -----------------
// O(n)

// The suffixMin array requires O(n) extra space.


// ================================================================================
// DRY RUN
// ================================================================================

// nums = [5, 0, 1, 4]
// k = 3

// Step 1: Build suffix minimum array.

// From right to left:

// suffixMin[3] = 4

// suffixMin[2] = min(1, 4) = 1

// suffixMin[1] = min(0, 1) = 0

// suffixMin[0] = min(5, 0) = 0

// Therefore:

//     suffixMin = [0, 0, 1, 4]


// Step 2: Scan from left to right.

// i = 0:
//     prefixMax = 5
//     suffixMin[0] = 0
//     score = 5 - 0 = 5

//     5 > 3 -> Not stable.


// i = 1:
//     prefixMax = max(5, 0) = 5
//     suffixMin[1] = 0
//     score = 5 - 0 = 5

//     5 > 3 -> Not stable.


// i = 2:
//     prefixMax = max(5, 1) = 5
//     suffixMin[2] = 1
//     score = 5 - 1 = 4

//     4 > 3 -> Not stable.


// i = 3:
//     prefixMax = max(5, 4) = 5
//     suffixMin[3] = 4
//     score = 5 - 4 = 1

//     1 <= 3 -> Stable.

// Return 3.


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Prefix + Suffix Preprocessing


// Key Observation:
// ----------------
// For every index i, we need:

//     max(nums[0..i])
//     min(nums[i..n-1])

// Prefix maximum can be maintained incrementally.

// Suffix minimum can be precomputed from right to left.

// This reduces repeated O(n) work to O(1) work per index.


// Common Mistakes:
// ----------------
// 1. Using nums[i] instead of min(nums[i..n-1]).

// 2. Forgetting that both ranges include index i.

// 3. Returning the last stable index instead of the FIRST stable index.

// 4. Recomputing prefix maximum and suffix minimum for every index,
//    resulting in O(n^2).

// 5. Forgetting to return -1 when no stable index exists.

// 6. Using an incorrect initialization for suffixMin.

// 7. Not handling n = 1.


// When to Use This Approach:
// --------------------------
// Use prefix/suffix preprocessing when:

// - Each query asks about a prefix and/or suffix.
// - You repeatedly need prefix maximum/minimum.
// - You repeatedly need suffix maximum/minimum.
// - The array is static and preprocessing is allowed.
// - You want to convert repeated range scans into O(1) lookups.

// Typical patterns include:

//     prefixMax[i] = max(nums[0..i])
//     prefixMin[i] = min(nums[0..i])
//     suffixMax[i] = max(nums[i..n-1])
//     suffixMin[i] = min(nums[i..n-1])

// For this problem:

//     instability(i)
//         = prefixMax[i] - suffixMin[i]

// Hence the complete solution is O(n).


// ================================================================================
// */

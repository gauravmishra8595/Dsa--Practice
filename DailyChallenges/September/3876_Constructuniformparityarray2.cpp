#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = INT_MAX;

        for (int x : nums1) {
            if (x % 2 == 1) {
                mn = min(mn, x);
            }
        }

        for (int x : nums1) {
            if (x % 2 == 0 && mn != INT_MAX && x < mn) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 4, 7};

    cout << boolalpha << sol.uniformArray(nums1) << '\n';

    return 0;
}

/*
======================================================================
              LEETCODE 3876 - CONSTRUCT UNIFORM PARITY ARRAY II
======================================================================

PROBLEM STATEMENT
-----------------

You are given an array nums1 of distinct positive integers.

You need to construct nums2 of the same length such that all
elements of nums2 are either:

    - all odd, OR
    - all even.

For every index i, you can choose exactly one:

    1. nums2[i] = nums1[i]

    2. nums2[i] = nums1[i] - nums1[j]
       where j != i and nums1[i] - nums1[j] >= 1.

Return true if such a nums2 can be constructed, otherwise false.


======================================================================
                              EXAMPLE
======================================================================

Example 1:

Input:
nums1 = [1, 4, 7]

Output:
true

Construction:

nums2[0] = 1
nums2[1] = 4 - 1 = 3
nums2[2] = 7

nums2 = [1, 3, 7]

All elements are odd.


Example 2:

Input:
nums1 = [2, 3]

Output:
false

There are only two elements with different parity, and no valid
subtraction can make both resulting elements have the same parity.


Example 3:

Input:
nums1 = [4, 6]

Output:
true

nums2 = [4, 6]

Both elements are already even.


======================================================================
                         BRUTE FORCE APPROACH
======================================================================

Idea
----

For every nums1[i], try both possible choices:

    1. Keep nums1[i]
    2. Subtract some nums1[j], j != i, if the result is positive.

Generate all possible values for every position and try every
combination.

For every generated nums2, check whether all elements have the
same parity.

This directly follows the definition of the problem, but it is
far too expensive because there can be many choices for every index.


Pseudo Code
-----------

function solve(nums1):

    for every possible choice of value for each index:
        if all values in nums2 have the same parity:
            return true

    return false


Complete Brute Force Code
--------------------------

/*
class Solution {
public:

    bool check(vector<int>& nums2) {
        int parity = nums2[0] % 2;

        for (int x : nums2) {
            if (x % 2 != parity) {
                return false;
            }
        }

        return true;
    }

    bool dfs(int i, vector<int>& nums1, vector<int>& nums2) {

        if (i == nums1.size()) {
            return check(nums2);
        }

        // Option 1: Keep nums1[i]
        nums2[i] = nums1[i];

        if (dfs(i + 1, nums1, nums2)) {
            return true;
        }

        // Option 2: Subtract any valid nums1[j]
        for (int j = 0; j < nums1.size(); j++) {

            if (i == j) continue;

            int value = nums1[i] - nums1[j];

            if (value >= 1) {
                nums2[i] = value;

                if (dfs(i + 1, nums1, nums2)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool uniformArray(vector<int>& nums1) {
        vector<int> nums2(nums1.size());

        return dfs(0, nums1, nums2);
    }
};
*/


// Time Complexity
// ---------------

// There can be O(N) choices for each of N positions.

// Worst case:

//     O(N^N)

// Space Complexity
// ----------------

// O(N) recursion depth + O(N) for nums2.

// Overall:

//     O(N) auxiliary space.


// ======================================================================
//                          OPTIMAL APPROACH
// ======================================================================

// Observation
// -----------

// Suppose there is at least one odd number.

// Let:

//     mn = smallest odd number in nums1.

// Consider an even number x.

// To make x odd, we need to subtract an odd number:

//     even - odd = odd

// The smallest available odd number is mn.

// Therefore, if:

//     x < mn

// then x cannot subtract any odd number, because every odd number is
// greater than x.

// So x is forced to remain even.

// At the same time, the smallest odd number mn cannot subtract a
// smaller number to change its parity appropriately.

// Hence, an even number smaller than the minimum odd number makes the
// answer impossible.


// The only condition we need to check is:

//     Is there an even x such that x < smallest odd number?


// If yes:

//     return false

// Otherwise:

//     return true


// Important special case:

// If there is no odd number at all, every element is already even.

// So the answer is automatically true.


// Intuition
// ---------

// We want to make every number have the same parity.

// For an even number to become odd, it must subtract an odd number.

// The subtraction must also remain positive.

// Therefore, an even number x can only become odd if there exists an
// odd number smaller than x.

// The smallest odd number is the best possible candidate.

// So:

//     smallest odd = mn

// Every even number must satisfy:

//     even number >= mn

// If an even number is smaller than mn, it cannot become odd.

// Since the array contains both parities, it also cannot simply remain
// even while all odd elements become even.

// Therefore, that case is impossible.


// Pseudo Code
// -----------

// function uniformArray(nums1):

//     mn = infinity

//     for every x in nums1:
//         if x is odd:
//             mn = min(mn, x)

//     for every x in nums1:
//         if x is even AND mn exists AND x < mn:
//             return false

//     return true


// Complete Optimal LeetCode Code
// -------------------------------

/*
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {

        int mn = INT_MAX;

        // Find the smallest odd number.
        for (int x : nums1) {
            if (x % 2 == 1) {
                mn = min(mn, x);
            }
        }

        // An even number smaller than the smallest odd
        // number cannot be converted to odd.
        for (int x : nums1) {
            if (x % 2 == 0 && mn != INT_MAX && x < mn) {
                return false;
            }
        }

        return true;
    }
};
*/


// Time Complexity
// ---------------

// First pass:

//     O(N)

// Second pass:

//     O(N)

// Total:

//     O(N)


// Space Complexity
// ----------------

// Only one variable mn is used.

//     O(1) auxiliary space.


// ======================================================================
//                             DRY RUN
// ======================================================================

// Example:

// nums1 = [1, 4, 7]


// Step 1: Find the smallest odd number.

// 1 -> odd  -> mn = 1
// 4 -> even
// 7 -> odd  -> mn = 1

// So:

//     mn = 1


// Step 2: Check every even number.

// 4 is even.

// Check:

//     4 < 1 ? No

// So there is no problematic even number.


// 7 and 1 are odd.

// Therefore:

//     return true


// One possible construction:

//     nums2 = [1, 3, 7]

// where:

//     4 - 1 = 3

// All values are odd.

// Answer:

//     true


// ------------------------------------------------------------

// Another Example:

// nums1 = [2, 3]


// Step 1:

// 3 is odd.

// Therefore:

//     mn = 3


// Step 2:

// 2 is even.

// Check:

//     2 < 3 ? Yes


// Therefore, 2 cannot subtract an odd number while keeping the
// result positive.

// So:

//     return false


// Answer:

//     false


// ------------------------------------------------------------

// Example:

// nums1 = [4, 6, 8]


// There is no odd number.

// Therefore all elements are already even.

//     mn = INT_MAX

// No invalid case exists.

// Answer:

//     true


// ======================================================================
//                          INTERVIEW NOTES
// ======================================================================

// Pattern
// -------

// Mathematical Observation / Parity / Greedy


// Key Observation
// ----------------

// Find the smallest odd element.

// If it is mn, then every even element must satisfy:

//     x >= mn

// Otherwise, that even element cannot subtract an odd number and
// become odd.

// Therefore:

//     smallest even < smallest odd
//         -> false

//     otherwise
//         -> true


// Common Mistakes
// ---------------

// 1. Checking only whether the array contains both odd and even
//    numbers.

//    Mixed parity does NOT automatically mean false.

//    Example:

//        [1, 4, 7]

//    is valid.


// 2. Using the minimum element instead of the minimum ODD element.

//    The important value is:

//        smallest odd number


// 3. Assuming every even number can become odd.

//    It can only become odd by subtracting an odd number that is
//    smaller than it.


// 4. Forgetting the all-even case.

//    If there is no odd number, the array is already uniform.


// 5. Simulating every possible subtraction.

//    The constraints allow N up to 10^5, so an O(N^2) or exponential
//    approach is unnecessary.


// 6. Forgetting the positive-result condition.

//    The subtraction must satisfy:

//        nums1[i] - nums1[j] >= 1

//    This is exactly why an even number smaller than the smallest odd
//    number is problematic.


// When to Use This Approach
// -------------------------

// Use this approach when:

//     - Operations affect only parity.
//     - Subtraction must remain positive.
//     - You need to determine whether all values can be made to have
//       the same parity.
//     - A smallest/largest element can act as the limiting value.

// The key competitive-programming technique is to avoid simulating
// the operation and instead identify the smallest value that can
// perform the required parity-changing operation.


// FINAL COMPLEXITY
// ----------------

// Time  : O(N)
// Space : O(1)


// ======================================================================
// */

#include <bits/stdc++.h>
using namespace std;

/* =========================
   OPTIMAL SOLUTION
   ========================= */
class Solution
{
public:
    int reductionOperations(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        int ans = 0;
        int distinctLevels = 0;

        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] != nums[i - 1])
            {
                distinctLevels++;
            }

            ans += distinctLevels;
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 1, 2, 2, 3};

    cout << sol.reductionOperations(nums) << '\n';

    return 0;
}

/*
======================================================================
LeetCode 1887 - Reduction Operations to Make the Array Elements Equal
======================================================================

Problem Statement
-----------------
Given an integer array nums, you can perform the following operation:

Choose the largest element in the array and replace it with the next
largest element that is smaller than it.

Return the minimum number of operations needed to make all elements
equal.


Example
-------
Input:
nums = [1, 1, 2, 2, 3]

Output:
4

Explanation:

For every 2:
2 -> 1

There are two 2s, so:
2 operations.

For 3:
3 -> 2 -> 1

So:
2 operations.

Total:
2 + 2 = 4.


----------------------------------------------------------------------
Brute Force Approach
----------------------------------------------------------------------

Idea
----
Repeatedly find the largest element and reduce one occurrence of it
to the next smaller distinct value.

Continue until all elements become equal.

This directly simulates the operations.


Pseudo Code
-----------
1. Set operations = 0.

2. While not all elements are equal:
      Find the largest value.
      Find the next smaller distinct value.
      Replace one occurrence of the largest value.
      operations++

3. Return operations.


Complete Brute Force Code
--------------------------
The following code is only for revision.

    /*
    int reductionOperationsBruteForce(vector<int>& nums) {
        int operations = 0;

        while (true) {
            int largest = *max_element(nums.begin(), nums.end());

            bool allEqual = true;

            for (int x : nums) {
                if (x != largest) {
                    allEqual = false;
                    break;
                }
            }

            if (allEqual)
                break;

            int nextSmaller = INT_MIN;

            for (int x : nums) {
                if (x < largest) {
                    nextSmaller = max(nextSmaller, x);
                }
            }

            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] == largest) {
                    nums[i] = nextSmaller;
                    operations++;
                    break;
                }
            }
        }

        return operations;
    }
    */

// Time Complexity-- -- -- -- -- -- -- -Finding the largest and next smaller element repeatedly can take
// O(n)
// per operation.

//     In the worst case,
//     there can be O(n²) operations.

//     Time = O(n²)

//                Space Complexity
//            -- -- -- -- -- -- -- --O(1) extra space.

//            -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --Optimal Approach
//            -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

//            Observation
//            -- -- -- -- -- -Sort the array.

//            Example:

// nums = [ 1, 1, 2, 2, 3 ]

//        After sorting :

//     [ 1, 1, 2, 2, 3 ]

//     Now think about how many smaller DISTINCT values each element has.

//     For value 1 :

//     There are 0 smaller distinct values.

//     Cost = 0

//            For value 2 :

//     There is 1 smaller distinct value :

//     1

//     Therefore :

//     2->1

//     Each 2
//         requires 1 operation.

// There are two 2s:

// 2 × 1 = 2


// For value 3:

// There are 2 smaller distinct values:

// 1, 2

// Therefore:

// 3 -> 2 -> 1

// Each 3 requires 2 operations.

// There is one 3:

// 1 × 2 = 2


// Total:

// 2 + 2 = 4


// Intuition
// ---------
// After sorting, maintain the number of distinct values seen so far.

// Whenever we encounter a new distinct value, increase the number of
// distinct levels.

// Every element from that point onward needs one operation for each
// smaller distinct level.

// Therefore, for every position:

// ans += number of smaller distinct values


// Pseudo Code
// -----------
// 1. Sort nums.

// 2. ans = 0
// 3. distinctLevels = 0

// 4. For i = 1 to n - 1:

//       If nums[i] != nums[i - 1]:
//           distinctLevels++

//       ans += distinctLevels

// 5. Return ans.


// Complete Optimal Code
// ----------------------
// LeetCode version:

    /*
    class Solution {
    public:
        int reductionOperations(vector<int>& nums) {
            sort(nums.begin(), nums.end());

            int ans = 0;
            int distinctLevels = 0;

            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] != nums[i - 1]) {
                    distinctLevels++;
                }

                ans += distinctLevels;
            }

            return ans;
        }
    };
    */


// Time Complexity
// ---------------
// Sorting:

// O(n log n)

// Single traversal:

// O(n)

// Overall:

// Time = O(n log n)


// Space Complexity
// ----------------
// Ignoring the internal sorting stack:

// Space = O(1)


// ----------------------------------------------------------------------
// Dry Run with Example
// ----------------------------------------------------------------------

// nums = [1, 1, 2, 2, 3]

// Step 1: Sort

// [1, 1, 2, 2, 3]


// Initialize:

// ans = 0
// distinctLevels = 0


// i = 1

// nums[1] = 1
// nums[0] = 1

// Same value.

// distinctLevels = 0

// ans += 0

// ans = 0


// i = 2

// nums[2] = 2
// nums[1] = 1

// New distinct value.

// distinctLevels = 1

// ans += 1

// ans = 1


// i = 3

// nums[3] = 2
// nums[2] = 2

// Same value.

// distinctLevels = 1

// ans += 1

// ans = 2


// i = 4

// nums[4] = 3
// nums[3] = 2

// New distinct value.

// distinctLevels = 2

// ans += 2

// ans = 4


// Final Answer:

// 4


// ----------------------------------------------------------------------
// Interview Notes
// ----------------------------------------------------------------------

// Pattern
// -------
// Sorting + Greedy + Counting Distinct Levels


// Key Observation
// ---------------
// Each element needs one operation for every DISTINCT value smaller
// than it.

// Therefore:

// cost of x = number of smaller distinct values.


// Common Mistakes
// ---------------
// 1. Using the index as the contribution.

//    WRONG:
//    ans += i

//    Example:

//    [1, 1, 2, 2, 3]

//    For 3, index = 4, but it only needs 2 operations.

// 2. Counting duplicate values as separate levels.

//    Only distinct values matter.

// 3. Simulating every operation.

//    This is unnecessary.

// 4. Forgetting that each occurrence contributes separately.

//    For:

//    [1, 1, 2, 2]

//    Both 2s need one operation.

//    Total = 2.


// When to Use This Approach
// -------------------------
// Use this approach when:

// - Larger values are repeatedly reduced toward smaller values.
// - The operation moves through distinct value levels.
// - Sorting allows us to determine how many levels each element must
//   cross.
// - We need the total number of operations rather than simulating them.

// General Rule:

// "When every element must pass through smaller DISTINCT values,
// count the distinct levels instead of simulating the operations."

// ======================================================================
// */
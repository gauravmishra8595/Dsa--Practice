#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();

        int totalEven = 0, totalOdd = 0;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                totalEven += nums[i];
            else
                totalOdd += nums[i];
        }

        int leftEven = 0, leftOdd = 0;
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                totalEven -= nums[i];
            else
                totalOdd -= nums[i];

            // After removing i, elements on the right shift by one position.
            int newEven = leftEven + totalOdd;
            int newOdd = leftOdd + totalEven;

            if (newEven == newOdd)
                ans++;

            if (i % 2 == 0)
                leftEven += nums[i];
            else
                leftOdd += nums[i];
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 1, 6, 4};
    vector<int> nums2 = {1, 1, 1};

    cout << sol.waysToMakeFair(nums1) << '\n'; // 1
    cout << sol.waysToMakeFair(nums2) << '\n'; // 3

    return 0;
}

/*
================================================================================
                         LEETCODE 1664
                 WAYS TO MAKE A FAIR ARRAY
================================================================================

Problem Statement:
------------------
Given an integer array nums, remove exactly one element from the array.

After removing the element, all elements to its right shift one position
to the left.

An array is called fair if:

    sum of elements at even indices
    =
    sum of elements at odd indices

Return the number of indices that can be removed to make the array fair.


Example:
--------
Input:
    nums = [2, 1, 6, 4]

Remove index 2:

    [2, 1, 4]

Even index sum:
    2 + 4 = 6

Odd index sum:
    1 = 1

Not fair.

Remove index 1:

    [2, 6, 4]

Even index sum:
    2 + 4 = 6

Odd index sum:
    6 = 6

Fair.

Answer:
    1


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
When we remove index i, the elements before i keep their original parity.

But every element after i shifts one position to the left, so its parity
changes.

Therefore:

    Original even position on the right -> becomes odd
    Original odd position on the right  -> becomes even


Intuition:
---------
Maintain four sums:

    leftEven  = sum of even-indexed elements before i
    leftOdd   = sum of odd-indexed elements before i

    totalEven = sum of even-indexed elements from i onward
    totalOdd  = sum of odd-indexed elements from i onward

First calculate totalEven and totalOdd for the entire array.

For every index i:

1. Remove nums[i] from the corresponding right-side sum.
2. After removing i:
       newEven = leftEven + rightOdd
       newOdd  = leftOdd + rightEven

   because the right side shifts by one position.
3. If newEven == newOdd, this removal is valid.
4. Add nums[i] to the appropriate left-side sum.


Pseudo Code:
------------
calculate totalEven and totalOdd

leftEven = 0
leftOdd = 0
answer = 0

for every index i:

    remove nums[i] from totalEven or totalOdd

    newEven = leftEven + totalOdd
    newOdd = leftOdd + totalEven

    if newEven == newOdd:
        answer++

    add nums[i] to leftEven or leftOdd

return answer


Complete Optimal Code:
----------------------
/*
class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();

        int totalEven = 0, totalOdd = 0;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                totalEven += nums[i];
            else
                totalOdd += nums[i];
        }

        int leftEven = 0, leftOdd = 0;
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                totalEven -= nums[i];
            else
                totalOdd -= nums[i];

            int newEven = leftEven + totalOdd;
            int newOdd = leftOdd + totalEven;

            if (newEven == newOdd)
                ans++;

            if (i % 2 == 0)
                leftEven += nums[i];
            else
                leftOdd += nums[i];
        }

        return ans;
    }
};
*/


// ================================================================================
// DRY RUN
// ================================================================================

// Example:
//     nums = [2, 1, 6, 4]

// Initial total sums:

//     Even indices:
//         index 0 -> 2
//         index 2 -> 6

//         totalEven = 8

//     Odd indices:
//         index 1 -> 1
//         index 3 -> 4

//         totalOdd = 5

// Initial:
//     leftEven = 0
//     leftOdd = 0


// i = 0, nums[0] = 2

// Remove 2 from totalEven:

//     totalEven = 6
//     totalOdd = 5

// Right side shifts:

//     newEven = leftEven + totalOdd
//             = 0 + 5
//             = 5

//     newOdd = leftOdd + totalEven
//            = 0 + 6
//            = 6

// Not fair.

// Move nums[0] to left:

//     leftEven = 2


// i = 1, nums[1] = 1

// Remove 1 from totalOdd:

//     totalEven = 6
//     totalOdd = 4

//     newEven = leftEven + totalOdd
//             = 2 + 4
//             = 6

//     newOdd = leftOdd + totalEven
//            = 0 + 6
//            = 6

// Fair!

//     answer = 1

// Move nums[1] to left:

//     leftOdd = 1


// i = 2, nums[2] = 6

// Remove 6 from totalEven:

//     totalEven = 0
//     totalOdd = 4

//     newEven = leftEven + totalOdd
//             = 2 + 4
//             = 6

//     newOdd = leftOdd + totalEven
//            = 1 + 0
//            = 1

// Not fair.

// Move nums[2] to left:

//     leftEven = 8


// i = 3, nums[3] = 4

// Remove 4 from totalOdd:

//     totalEven = 0
//     totalOdd = 0

//     newEven = leftEven + totalOdd
//             = 8 + 0
//             = 8

//     newOdd = leftOdd + totalEven
//            = 1 + 0
//            = 1

// Not fair.

// Final answer:

//     1


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Prefix Sum / Running Sum + Parity


// Key Observation:
// ----------------
// After removing an element, every element to its right changes parity.

// Therefore:

//     newEven = leftEven + rightOdd
//     newOdd  = leftOdd + rightEven


// Common Mistakes:
// ----------------
// 1. Forgetting that elements on the right shift by one position.

// 2. Using:

//        newEven = leftEven + rightEven

//    This is incorrect because the right side changes parity.

// 3. Forgetting to remove nums[i] from the right-side sum before calculating
//    the new sums.

// 4. Recalculating sums for every removal.

//    That leads to O(N^2).

// 5. Updating the left sums before checking the current removal.

// 6. Confusing the original index parity with the parity after deletion.


// When to use this approach:
// --------------------------
// Use this approach when:
// - Removing one element changes the parity/index of all elements to its right.
// - You need to evaluate every possible removal.
// - Recomputing the array after each removal would be O(N^2).
// - Prefix/running sums can represent the left and right portions efficiently.


// Interview Questions:
// --------------------
// Q1. Why do elements on the right change parity?

// A:
// Removing nums[i] shifts every element after i one position to the left.
// Therefore, every right-side index changes from even to odd or odd to even.


// Q2. Why do we add rightOdd to the new even sum?

// A:
// An element that was at an odd index on the right becomes even after shifting
// one position to the left.


// Q3. What is the time complexity?

// A:
// O(N), because we make two linear passes over the array.


// Q4. What is the space complexity?

// A:
// O(1), because only four running sums and the answer are maintained.


// Q5. Can this be solved using prefix sums?

// A:
// Yes. Prefix sums can be used to calculate left and right even/odd sums,
// but maintaining four running sums is simpler and achieves the same O(N) time
// and O(1) extra space.


// Q6. What is the main trick in this problem?

// A:
// The key trick is recognizing that deleting an element flips the parity of
// every element to its right.


// Complexity:
// -----------
// Time  : O(N)
// Space : O(1)

// ================================================================================
// */

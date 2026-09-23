#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = total - x;

        // x is greater than the sum of all elements
        if (target < 0)
            return -1;

        // Need to remove all elements
        if (target == 0)
            return n;

        int left = 0;
        int currSum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {
            currSum += nums[right];

            while (currSum > target) {
                currSum -= nums[left];
                left++;
            }

            if (currSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        return maxLen == -1 ? -1 : n - maxLen;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 1, 4, 2, 3};
    int x = 5;

    cout << sol.minOperations(nums, x) << '\n';

    return 0;
}

/*
======================================================================
        LEETCODE 1658 - MINIMUM OPERATIONS TO REDUCE X TO ZERO
======================================================================

PROBLEM STATEMENT
-----------------

You are given an integer array nums and an integer x.

In one operation, you can remove the leftmost or rightmost element
from nums and subtract its value from x.

Return the minimum number of operations required to reduce x exactly
to 0.

If it is impossible, return -1.

EXAMPLE
-------

Input:
    nums = [1,1,4,2,3]
    x = 5

Output:
    2

Explanation:

Remove 2 from the right:
    [1,1,4,3]
    x = 3

Remove 3 from the right:
    [1,1,4]
    x = 0

Answer = 2.

======================================================================
BRUTE FORCE APPROACH
======================================================================

IDEA
----

At every step, there are two choices:

1. Remove the leftmost element.
2. Remove the rightmost element.

Try both choices recursively and take the minimum number of
operations.

PSEUDO CODE
-----------

solve(left, right, x):

    if x == 0:
        return 0

    if left > right OR x < 0:
        return INF

    removeLeft =
        solve(left + 1, right, x - nums[left])

    removeRight =
        solve(left, right - 1, x - nums[right])

    return 1 + min(removeLeft, removeRight)

COMPLETE BRUTE FORCE CODE
-------------------------

/*
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& nums, int left, int right, int x) {

    if (x == 0)
        return 0;

    if (left > right || x < 0)
        return INT_MAX / 2;

    int removeLeft =
        solve(nums, left + 1, right, x - nums[left]);

    int removeRight =
        solve(nums, left, right - 1, x - nums[right]);

    return 1 + min(removeLeft, removeRight);
}

int minOperations(vector<int>& nums, int x) {

    int ans = solve(nums, 0, nums.size() - 1, x);

    return ans >= INT_MAX / 2 ? -1 : ans;
}

int main() {

    vector<int> nums = {1, 1, 4, 2, 3};
    int x = 5;

    cout << minOperations(nums, x) << '\n';

    return 0;
}
*/

// TIME COMPLEXITY
// ----------------

// O(2^n)

// At every step we have two choices:

//     Remove from left
//     Remove from right

// SPACE COMPLEXITY
// ----------------

// O(n)

// Due to recursion depth.

// ======================================================================
// OPTIMAL APPROACH
// ======================================================================

// OBSERVATION
// -----------

// Let:

//     total = sum of all elements

// We need to remove elements from the two ends whose sum is x.

// Therefore, the elements that remain in the middle must have sum:

//     total - x

// Example:

//     nums = [1,1,4,2,3]

//     total = 11
//     x = 5

// Therefore:

//     target = total - x
//            = 11 - 5
//            = 6

// Instead of finding the minimum number of elements to REMOVE,
// we find the maximum number of elements to KEEP whose sum is target.

// Therefore:

//     answer = n - longest valid subarray length

// INTUITION
// ---------

// Since we can only remove elements from the left and right ends,
// the elements that remain must form one contiguous subarray.

// So we need to find:

//     Longest subarray with sum = total - x

// Because nums contains positive integers, we can use:

//     Sliding Window / Two Pointers

// If:

//     currSum > target

// then move the left pointer forward.

// If:

//     currSum == target

// update the maximum length.

// IMPORTANT EDGE CASES
// --------------------

// 1. If:

//        target < 0

//    then:

//        x > total

//    It is impossible to remove enough sum.

//    Return -1.

// 2. If:

//        target == 0

//    then we need to keep an empty subarray.

//    Therefore, every element must be removed.

//    Return n.

// PSEUDO CODE
// -----------

// total = sum(nums)

// target = total - x

// if target < 0:
//     return -1

// if target == 0:
//     return n

// left = 0
// currSum = 0
// maxLen = -1

// for right = 0 to n - 1:

//     currSum += nums[right]

//     while currSum > target:

//         currSum -= nums[left]
//         left++

//     if currSum == target:

//         maxLen = max(maxLen,
//                      right - left + 1)

// if maxLen == -1:
//     return -1

// return n - maxLen

// COMPLETE OPTIMAL CODE
// ---------------------

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {

        int n = nums.size();

        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = total - x;

        if (target < 0)
            return -1;

        if (target == 0)
            return n;

        int left = 0;
        int currSum = 0;
        int maxLen = -1;

        for (int right = 0; right < n; right++) {

            currSum += nums[right];

            while (currSum > target) {
                currSum -= nums[left];
                left++;
            }

            if (currSum == target) {
                maxLen = max(maxLen,
                             right - left + 1);
            }
        }

        return maxLen == -1 ? -1 : n - maxLen;
    }
};

int main() {

    Solution sol;

    vector<int> nums = {1, 1, 4, 2, 3};
    int x = 5;

    cout << sol.minOperations(nums, x) << '\n';

    return 0;
}
*/

// TIME COMPLEXITY
// ----------------

// O(n)

// The right pointer moves from left to right once.

// The left pointer also moves from left to right at most once.

// Therefore total work is O(n).

// SPACE COMPLEXITY
// ----------------

// O(1)

// Only a constant number of variables are used.

// ======================================================================
// DRY RUN WITH EXAMPLE
// ======================================================================

// nums = [1,1,4,2,3]
// x = 5

// n = 5

// Step 1:
// -------

// total = 1 + 1 + 4 + 2 + 3
//       = 11

// target = total - x
//        = 11 - 5
//        = 6

// We need the longest subarray with sum = 6.

// Step 2:
// -------

// right = 0

// window = [1]

// currSum = 1

// 1 < 6

// Continue.

// Step 3:
// -------

// right = 1

// window = [1,1]

// currSum = 2

// 2 < 6

// Continue.

// Step 4:
// -------

// right = 2

// window = [1,1,4]

// currSum = 6

// currSum == target.

// Length:

//     2 - 0 + 1 = 3

// maxLen = 3

// Step 5:
// -------

// right = 3

// window = [1,1,4,2]

// currSum = 8

// 8 > 6

// Remove nums[left]:

//     Remove 1

// window = [1,4,2]

// currSum = 7

// Still greater than 6.

// Remove nums[left]:

//     Remove 1

// window = [4,2]

// currSum = 6

// currSum == target.

// Length = 2

// maxLen remains 3.

// Step 6:
// -------

// right = 4

// Add 3:

// window = [4,2,3]

// currSum = 9

// 9 > 6

// Remove 4:

// window = [2,3]

// currSum = 5

// No match.

// FINAL ANSWER
// ------------

// maxLen = 3
// n = 5

// answer = n - maxLen

//         = 5 - 3

//         = 2

// Answer = 2

// ======================================================================
// INTERVIEW NOTES
// ======================================================================

// PATTERN
// -------

// Sliding Window
// Two Pointers

// KEY OBSERVATION
// ---------------

// Convert:

//     Minimum elements to REMOVE from ends

// into:

//     Maximum length subarray to KEEP.

// If:

//     total = sum(nums)

// then:

//     remaining sum = total - x

// Therefore:

//     answer = n - longest subarray
//                  having sum (total - x)

// COMMON MISTAKES
// ---------------

// 1. Looking directly for elements to remove.

//    Instead, find the longest subarray to keep.

// 2. Using:

//        target = x

//    This is incorrect.

//    Correct:

//        target = total - x

// 3. Forgetting:

//        target < 0

//    If x > total, the answer is -1.

// 4. Forgetting:

//        target == 0

//    In this case, all elements must be removed.

//    Answer = n.

// 5. Returning maxLen.

//    maxLen represents the number of elements kept.

//    Therefore:

//        answer = n - maxLen

// 6. Forgetting the impossible case.

//    If no valid subarray exists:

//        maxLen == -1

//    Return -1.

// 7. Using this sliding-window approach with negative numbers.

//    This solution relies on nums containing positive integers.

// WHEN TO USE THIS APPROACH
// -------------------------

// Use this approach when:

// - Elements can only be removed from the left or right ends.
// - The removed elements must satisfy a sum condition.
// - Array elements are positive.
// - We need the minimum number of removals.

// General pattern:

//     Minimum removals from ends
//             =
//     n - Maximum length valid middle subarray





// */
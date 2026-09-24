#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            int sum = 0;
            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }
            if (sum == i)
                return i;
        }
        return -1;
    }
};
int main() {
    Solution sol;
    vector<int> nums = {1, 3, 2};
    cout << sol.smallestIndex(nums) << '\n';
    return 0;
}
/*
================================================================================
LEETCODE 3550 - SMALLEST INDEX WITH DIGIT SUM EQUAL TO INDEX
================================================================================

Problem Statement:
------------------
Given an integer array nums, return the smallest index i such that the sum
of the digits of nums[i] is equal to i.

If no such index exists, return -1.

Example:
--------
Input:
nums = [1, 3, 2]

Output:
2

Explanation:
nums[0] = 1  -> digit sum = 1 != 0
nums[1] = 3  -> digit sum = 3 != 1
nums[2] = 2  -> digit sum = 2 == 2

Therefore, answer = 2.


Brute Force Approach:
---------------------

Idea:
-----
Check every index i and calculate the digit sum of nums[i].
If the digit sum equals i, return i.

This is technically already optimal for the given problem because every index
may need to be checked. There is no need for sorting, hashing, or extra data
structures.

Pseudo Code:
------------
for i = 0 to n-1:
    calculate digit sum of nums[i]
    if digit sum == i:
        return i

return -1


Complete Brute Force Code:
--------------------------

// class Solution {
// public:
//     int smallestIndex(vector<int>& nums) {
//         for (int i = 0; i < nums.size(); i++) {
//             int x = nums[i];
//             int sum = 0;
//
//             while (x > 0) {
//                 sum += x % 10;
//                 x /= 10;
//             }
//
//             if (sum == i)
//                 return i;
//         }
//
//         return -1;
//     }
// };


Time Complexity:
----------------
O(n * d)

where:
n = number of elements
d = number of digits in each number

Since nums[i] <= 1000, d <= 4, so practically this is O(n).


Space Complexity:
-----------------
O(1)


Optimal Approach:
-----------------

Observation:
------------
We need the SMALLEST index satisfying:

digitSum(nums[i]) == i

Therefore, scan from left to right.

The first index satisfying the condition is automatically the smallest index.


Intuition:
----------
For each element:

1. Extract its last digit using x % 10.
2. Add it to the digit sum.
3. Remove the last digit using x /= 10.
4. Compare the digit sum with the current index.
5. Return immediately when they are equal.

No sorting or extra data structure is required.


Pseudo Code:
------------
for i = 0 to n-1:
    x = nums[i]
    sum = 0

    while x > 0:
        sum += x % 10
        x /= 10

    if sum == i:
        return i

return -1


Complete Optimal Code:
----------------------

// class Solution {
// public:
//     int smallestIndex(vector<int>& nums) {
//         for (int i = 0; i < nums.size(); i++) {
//             int x = nums[i];
//             int sum = 0;
//
//             while (x > 0) {
//                 sum += x % 10;
//                 x /= 10;
//             }
//
//             if (sum == i)
//                 return i;
//         }
//
//         return -1;
//     }
// };


Time Complexity:
----------------
O(n * d)

For the given constraints, d <= 4, so this is effectively O(n).


Space Complexity:
-----------------
O(1)


Dry Run with Example:
---------------------

nums = [1, 3, 2]

i = 0:
    nums[0] = 1
    digit sum = 1
    1 != 0
    Continue.

i = 1:
    nums[1] = 3
    digit sum = 3
    3 != 1
    Continue.

i = 2:
    nums[2] = 2
    digit sum = 2
    2 == 2
    Return 2.

Answer = 2


Another Example:
----------------

nums = [1, 10, 11]

i = 0:
    digit sum of 1 = 1
    1 != 0

i = 1:
    digit sum of 10 = 1 + 0 = 1
    1 == 1

Return 1 immediately.

Answer = 1


Interview Notes:
----------------

Pattern:
    Array Traversal + Digit Manipulation

Key Observation:
    Since we need the smallest index, scan from left to right and return
    immediately when digitSum(nums[i]) == i.

Common Mistakes:
    1. Returning the last matching index instead of the first.
    2. Forgetting that index starts from 0.
    3. Using nums[i] directly instead of calculating its digit sum.
    4. Forgetting to handle nums[i] = 0.
       For x = 0, the digit sum remains 0, which is correct.
    5. Using unnecessary sorting or extra data structures.

When to use this approach:
    Use this pattern when:
    - You need the first/smallest index satisfying a condition.
    - The condition can be checked independently for each element.
    - The required property involves digit extraction or digit sums.
    - No relationship between different array elements is needed.

================================================================================
*/

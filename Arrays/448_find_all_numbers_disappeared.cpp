#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        int n = nums.size();
        for (int x : nums)
        {
            int idx = abs(x) - 1;
            nums[idx] = -abs(nums[idx]);
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] > 0)
            {
                ans.push_back(i + 1);
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};

    vector<int> ans = sol.findDisappearedNumbers(nums);

    cout << "Missing numbers: ";
    for (int x : ans)
    {
        cout << x << " ";
    }
    cout << '\n';

    return 0;
}

/*
===============================================================================
              LEETCODE 448 - FIND ALL NUMBERS DISAPPEARED IN AN ARRAY
===============================================================================

Problem Statement
-----------------
Given an array nums of n integers where:

    1 <= nums[i] <= n

Some elements appear twice and some elements appear once.

Find all the integers in the range [1, n] that do not appear in nums.

Return the missing numbers in any order.

The solution must run in O(n) time and use O(1) extra space
(excluding the returned answer).

Example
-------
Input:
    nums = [4, 3, 2, 7, 8, 2, 3, 1]

Output:
    [5, 6]

Explanation:
    Numbers from 1 to 8 should be present.

    Present:
        1, 2, 3, 4, 7, 8

    Missing:
        5, 6

===============================================================================
                         BRUTE FORCE APPROACH
===============================================================================

Idea
----
For every number from 1 to n, check whether it exists in nums.

If a number is not found, add it to the answer.

Pseudo Code
-----------
    n = nums.size()
    ans = empty array

    for i from 1 to n:
        found = false

        for x in nums:
            if x == i:
                found = true
                break

        if found == false:
            ans.push_back(i)

    return ans

Complete Brute Force Code
-------------------------
    class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            int n = nums.size();
            vector<int> ans;

            for (int i = 1; i <= n; i++) {
                bool found = false;

                for (int x : nums) {
                    if (x == i) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    ans.push_back(i);
                }
            }

            return ans;
        }
    };

Time Complexity
---------------
    O(n^2)

Space Complexity
----------------
    O(1) extra space, excluding the answer.

===============================================================================
                          OPTIMAL APPROACH
===============================================================================

Observation
-----------
Every number is in the range:

    1 to n

Therefore, every number can be mapped to an array index:

    number x -> index x - 1

For example:

    1 -> index 0
    2 -> index 1
    3 -> index 2
    ...
    n -> index n - 1

We can use the input array itself as a marking array.

Intuition
---------
For every number x in nums:

    idx = x - 1

Mark nums[idx] as negative.

A number may appear multiple times, but using:

    nums[idx] = -abs(nums[idx])

ensures that the value remains negative.

After marking all numbers:

    nums[i] < 0
        => number i + 1 exists

    nums[i] > 0
        => number i + 1 is missing

This works because every present number marks its corresponding index.

Pseudo Code
-----------
    n = nums.size()

    for every x in nums:
        idx = abs(x) - 1
        nums[idx] = -abs(nums[idx])

    ans = empty array

    for i from 0 to n - 1:
        if nums[i] > 0:
            ans.push_back(i + 1)

    return ans

Complete Optimal Code
---------------------
    class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            int n = nums.size();

            for (int x : nums) {
                int idx = abs(x) - 1;
                nums[idx] = -abs(nums[idx]);
            }

            vector<int> ans;

            for (int i = 0; i < n; i++) {
                if (nums[i] > 0) {
                    ans.push_back(i + 1);
                }
            }

            return ans;
        }
    };

Time Complexity
---------------
    O(n)

    First loop:
        O(n)

    Second loop:
        O(n)

    Total:
        O(n)

Space Complexity
----------------
    O(1) extra space.

    The returned answer is not considered extra auxiliary space.

===============================================================================
                              DRY RUN
===============================================================================

Example:
    nums = [4, 3, 2, 7, 8, 2, 3, 1]

n = 8

Initially:

    Index:  0  1  2  3  4  5  6  7
    Value:  4  3  2  7  8  2  3  1

Process 4:
    index = 4 - 1 = 3
    nums[3] becomes negative

    [4, 3, 2, -7, 8, 2, 3, 1]

Process 3:
    index = 3 - 1 = 2

    [4, 3, -2, -7, 8, 2, 3, 1]

Process 2:
    index = 2 - 1 = 1

    [4, -3, -2, -7, 8, 2, 3, 1]

Process 7:
    index = 7 - 1 = 6

    [4, -3, -2, -7, 8, 2, -3, 1]

Process 8:
    index = 8 - 1 = 7

    [4, -3, -2, -7, 8, 2, -3, -1]

Process 2 again:
    index = 1

    Already negative, remains negative.

Process 3 again:
    index = 2

    Already negative, remains negative.

Process 1:
    index = 0

    [ -4, -3, -2, -7, 8, 2, -3, -1 ]

Final array:

    Index:  0   1   2   3   4  5   6   7
    Value: -4  -3  -2  -7   8  2  -3  -1

Positive values are at:

    index 4 -> number 5
    index 5 -> number 6

Therefore:

    Answer = [5, 6]

===============================================================================
                              INTERVIEW NOTES
===============================================================================

Pattern
-------
    Array Index Marking / In-place Hashing

Key Observation
---------------
    Values are restricted to [1, n].

    Therefore:

        value x -> index x - 1

    We can use the sign of nums[index] to record whether a number exists.

Common Mistakes
---------------
    1. Forgetting to use abs(x).

       nums[x] may already have been changed to negative.

       Correct:
           int idx = abs(x) - 1;

    2. Using:

           nums[idx] *= -1;

       blindly can turn an already-negative value positive when a duplicate
       occurs.

       Correct:
           nums[idx] = -abs(nums[idx]);

    3. Using x instead of x - 1 for the index.

       Number 1 maps to index 0.

    4. Creating a separate frequency array when O(1) extra space is required.

    5. Forgetting that modifying the input array is allowed for this problem.

When to Use This Approach
-------------------------
    Use index marking when:

    - Array values are in the range [1, n].
    - We need to determine which values are present/missing.
    - O(n) time is required.
    - O(1) extra space is required.
    - Modifying the input array is allowed.

Related Problems
----------------
    This same pattern is useful for:

    - Finding duplicates in an array.
    - Finding missing numbers.
    - Checking which values from 1..n are present.
    - In-place frequency/visited marking problems.

Complexity Summary
------------------
    Brute Force:
        Time  = O(n^2)
        Space = O(1) excluding answer

    Optimal:
        Time  = O(n)
        Space = O(1) excluding answer

===============================================================================
*/
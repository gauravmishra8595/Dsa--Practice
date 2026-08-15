#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int longestSubsequence(vector<int> &nums)
    {
        int n = nums.size();
        int totalXor = 0;
        bool hasNonZero = false;

        for (int x : nums)
        {
            totalXor ^= x;

            if (x != 0)
                hasNonZero = true;
        }

        if (totalXor != 0)
            return n;

        if (hasNonZero)
            return n - 1;

        return 0;
    }
};

int main()
{
    vector<int> nums = {1, 2, 3};

    Solution obj;
    cout << obj.longestSubsequence(nums) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 3702 - CP NOTEBOOK
        Longest Subsequence With Non-Zero Bitwise XOR
================================================================================

Problem Statement:
------------------
Given an integer array nums, return the length of the longest subsequence
whose bitwise XOR is non-zero.

If no such subsequence exists, return 0.

A subsequence is obtained by deleting zero or more elements while keeping
the relative order of the remaining elements.


Example:
--------
Input:
nums = [1, 2, 3]

Output:
2

Explanation:
1 ^ 2 ^ 3 = 0

So the complete array is not valid.

Remove 1:
2 ^ 3 = 1 != 0

Therefore, the longest valid subsequence has length 2.


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Generate every possible subsequence.

For every subsequence:
1. Calculate its XOR.
2. If XOR != 0, update the maximum length.

There are 2^n possible subsequences, so this approach is useful only for
small constraints.


Pseudo Code:
------------
function solve(nums):

    ans = 0

    for every mask from 1 to (2^n - 1):

        xorValue = 0
        length = 0

        for i from 0 to n - 1:

            if bit i is set in mask:

                xorValue ^= nums[i]
                length++

        if xorValue != 0:
            ans = max(ans, length)

    return ans


Complete Brute Force Code:
---------------------------

int bruteForce(vector<int> &nums)
{
    int n = nums.size();
    int ans = 0;

    for (int mask = 1; mask < (1 << n); mask++)
    {
        int xorValue = 0;
        int len = 0;

        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                xorValue ^= nums[i];
                len++;
            }
        }

        if (xorValue != 0)
            ans = max(ans, len);
    }

    return ans;
}


Time Complexity:
----------------
O(n * 2^n)


Space Complexity:
-----------------
O(1) auxiliary space.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------
There are only three possible cases.


Case 1:
-------
The XOR of the complete array is non-zero.

Then the complete array itself is a valid subsequence.

Therefore:

answer = n


Case 2:
-------
The XOR of the complete array is zero, but at least one element is non-zero.

Suppose we remove a non-zero element x.

Let:

totalXor = 0

Then:

XOR(remaining)
= totalXor ^ x
= 0 ^ x
= x

Since x != 0, the remaining XOR is non-zero.

Therefore, we can always create a valid subsequence of length:

n - 1

Also, we cannot have length n because the XOR of the complete array is zero.

Therefore:

answer = n - 1


Case 3:
-------
All elements are zero.

Any subsequence will contain only zeroes.

XOR of zeroes is always zero.

Therefore, no valid subsequence exists.

answer = 0


Intuition:
---------
The problem looks like a subsequence problem because there can be
exponentially many subsequences.

But we only need the maximum possible length.

First, check whether the entire array already has non-zero XOR.

If yes:

    answer = n

Otherwise, the XOR of the entire array is zero.

If there is at least one non-zero element, remove that element.

Because:

    totalXor = 0

and

    remainingXor = totalXor ^ removedElement

therefore:

    remainingXor = removedElement

So, removing any non-zero element produces a valid subsequence
of length n - 1.

If every element is zero, no valid subsequence exists.


Pseudo Code:
------------
function solve(nums):

    n = size(nums)
    totalXor = 0
    hasNonZero = false

    for x in nums:

        totalXor ^= x

        if x != 0:
            hasNonZero = true

    if totalXor != 0:
        return n

    if hasNonZero:
        return n - 1

    return 0


Complete Optimal Code:
-----------------------

class Solution
{
public:
    int longestSubsequence(vector<int> &nums)
    {
        int n = nums.size();
        int totalXor = 0;
        bool hasNonZero = false;

        for (int x : nums)
        {
            totalXor ^= x;

            if (x != 0)
                hasNonZero = true;
        }

        if (totalXor != 0)
            return n;

        if (hasNonZero)
            return n - 1;

        return 0;
    }
};


Time Complexity:
----------------
O(n)

We scan the array only once.


Space Complexity:
-----------------
O(1)

Only a few variables are used.


===============================================================================
Dry Run With Example
===============================================================================

Example:
nums = [1, 2, 3]


Step 1:
-------
totalXor = 0

x = 1:

    totalXor = 0 ^ 1
             = 1


Step 2:
-------
x = 2:

    totalXor = 1 ^ 2
             = 3


Step 3:
-------
x = 3:

    totalXor = 3 ^ 3
             = 0


At the end:

    totalXor = 0
    hasNonZero = true
    n = 3


The complete array is invalid because its XOR is zero.

Remove one non-zero element, for example 1:

Remaining:

    [2, 3]

XOR:

    2 ^ 3 = 1

Since:

    1 != 0

the subsequence is valid.

Length:

    n - 1
    = 3 - 1
    = 2

Answer = 2


Another Example:
-----------------
nums = [2, 3, 4]

Calculate XOR:

    0 ^ 2 = 2
    2 ^ 3 = 1
    1 ^ 4 = 5

Therefore:

    totalXor = 5

Since:

    totalXor != 0

the entire array is valid.

Answer = 3


Edge Case:
----------
nums = [0, 0, 0]

Then:

    totalXor = 0
    hasNonZero = false

Every possible subsequence has XOR = 0.

Therefore:

    answer = 0


===============================================================================
Interview Notes
===============================================================================

Pattern:
--------
Bit Manipulation + Greedy / Mathematical Observation


Key Observation:
----------------
If:

    totalXor != 0

then:

    answer = n


If:

    totalXor == 0

and at least one element is non-zero:

    answer = n - 1


If every element is zero:

    answer = 0


Important XOR Properties:
-------------------------

1. x ^ 0 = x

2. x ^ x = 0

3. XOR is associative:

       (a ^ b) ^ c = a ^ (b ^ c)

4. XOR is commutative:

       a ^ b = b ^ a

5. If totalXor = 0, removing x gives:

       remainingXor = 0 ^ x
                    = x


Common Mistakes:
----------------

1. Using DP over all subsequences.

   This is unnecessary because the answer can only be:

       n
       n - 1
       0


2. Returning n - 1 whenever totalXor == 0.

   This is wrong for an all-zero array.


3. Forgetting the all-zero case.

   Example:

       [0, 0, 0]

   Answer:

       0


4. Using brute force.

   There can be 2^n subsequences, which is impossible for large n.


5. Thinking that subsequence order affects XOR.

   XOR is commutative and associative, so only the selected elements
   determine the final XOR.


When To Use This Approach:
--------------------------

Use this approach when:

- The problem asks for maximum subsequence length.
- The condition depends on XOR.
- The whole array can be checked directly.
- Removing one element can make the condition valid.
- Constraints are too large for O(2^n).


Core Mental Template:
---------------------

Calculate total XOR.

    if totalXor != 0:
        return n

    if any element is non-zero:
        return n - 1

    return 0


Final Complexity:
-----------------

Time  : O(n)
Space : O(1)

================================================================================
*/
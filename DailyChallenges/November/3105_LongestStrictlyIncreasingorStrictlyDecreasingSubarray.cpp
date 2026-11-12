
#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    int longestMonotonicSubarray(vector<int> &nums)
    {
        int n = nums.size();

        int inc = 1;
        int dec = 1;
        int ans = 1;

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > nums[i - 1])
            {
                inc++;
                dec = 1;
            }
            else if (nums[i] < nums[i - 1])
            {
                dec++;
                inc = 1;
            }
            else
            {
                inc = 1;
                dec = 1;
            }

            ans = max(ans, max(inc, dec));
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {1, 4, 3, 3, 2};

    cout << obj.longestMonotonicSubarray(nums) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 3105 - CP NOTEBOOK
       Longest Strictly Increasing or Strictly Decreasing Subarray
================================================================================

Problem Statement:
------------------
Given an integer array nums, return the length of the longest subarray
that is either:

1. Strictly Increasing
2. Strictly Decreasing

A subarray must contain contiguous elements.

In other words:

For strictly increasing:

    nums[i] < nums[i+1] < nums[i+2] ...

For strictly decreasing:

    nums[i] > nums[i+1] > nums[i+2] ...

Return the maximum length.


Example:
--------
Input:

    nums = [1, 4, 3, 3, 2]

Output:

    2

Explanation:

Increasing subarray:

    [1, 4]

Length = 2

Decreasing subarray:

    [4, 3]

Length = 2

Another decreasing subarray:

    [3, 2]

Length = 2

Therefore:

    Answer = 2


Another Example:
----------------

Input:

    nums = [3, 2, 1]

Output:

    3

Explanation:

The entire array is strictly decreasing.

    [3, 2, 1]

Length = 3


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Generate all possible subarrays.

For every subarray:

1. Check whether it is strictly increasing.
2. Check whether it is strictly decreasing.
3. If either condition is satisfied, update the answer.

We can use two boolean variables:

    inc = true
    dec = true

If an increasing condition breaks:

    inc = false

If a decreasing condition breaks:

    dec = false

If both become false, stop checking that subarray.


Pseudo Code:
------------

function longestMonotonicSubarray(nums):

    n = size(nums)

    ans = 1

    for i from 0 to n - 1:

        inc = true
        dec = true

        for j from i + 1 to n - 1:

            if nums[j] > nums[j - 1]:

                dec = false

            else if nums[j] < nums[j - 1]:

                inc = false

            else:

                break

            if inc == false AND dec == false:

                break

            ans = max(ans, j - i + 1)

    return ans


Complete Brute Force Code:
---------------------------

int bruteForce(vector<int> &nums)
{
    int n = nums.size();

    int ans = 1;

    for (int i = 0; i < n; i++)
    {
        bool inc = true;
        bool dec = true;

        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] > nums[j - 1])
            {
                dec = false;
            }
            else if (nums[j] < nums[j - 1])
            {
                inc = false;
            }
            else
            {
                break;
            }

            if (!inc && !dec)
                break;

            ans = max(ans, j - i + 1);
        }
    }

    return ans;
}


Time Complexity:
----------------
O(n^2)

We use two nested loops to generate and check subarrays.

Space Complexity:
-----------------
O(1)

Only boolean variables and an answer variable are used.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------

We only need to compare adjacent elements.

Instead of generating every possible subarray, maintain two counters:

    inc = Length of current increasing subarray.

    dec = Length of current decreasing subarray.

    ans = Maximum length found.

Initially:

    inc = 1
    dec = 1
    ans = 1


Intuition:
----------

There are three possible cases when comparing:

    nums[i] with nums[i - 1]


CASE 1: STRICTLY INCREASING
----------------------------

Condition:

    nums[i] > nums[i - 1]

Example:

    [1, 2, 3]

The increasing sequence continues.

Therefore:

    inc++

The decreasing sequence breaks.

Therefore:

    dec = 1


CASE 2: STRICTLY DECREASING
----------------------------

Condition:

    nums[i] < nums[i - 1]

Example:

    [5, 4, 3]

The decreasing sequence continues.

Therefore:

    dec++

The increasing sequence breaks.

Therefore:

    inc = 1


CASE 3: EQUAL ELEMENTS
----------------------

Condition:

    nums[i] == nums[i - 1]

Example:

    [2, 2]

Equal elements cannot form a strictly increasing or decreasing sequence.

Therefore:

    inc = 1
    dec = 1


Finally:
--------

After every comparison:

    ans = max(ans, max(inc, dec));

This maintains the maximum length.


Pseudo Code:
------------

function longestMonotonicSubarray(nums):

    n = size(nums)

    inc = 1
    dec = 1
    ans = 1

    for i from 1 to n - 1:

        if nums[i] > nums[i - 1]:

            inc++
            dec = 1

        else if nums[i] < nums[i - 1]:

            dec++
            inc = 1

        else:

            inc = 1
            dec = 1

        ans = max(ans, max(inc, dec))

    return ans


Complete Optimal Code:
-----------------------

class Solution
{
public:
    int longestMonotonicSubarray(vector<int> &nums)
    {
        int n = nums.size();

        int inc = 1;
        int dec = 1;
        int ans = 1;

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > nums[i - 1])
            {
                inc++;
                dec = 1;
            }
            else if (nums[i] < nums[i - 1])
            {
                dec++;
                inc = 1;
            }
            else
            {
                inc = 1;
                dec = 1;
            }

            ans = max(ans, max(inc, dec));
        }

        return ans;
    }
};


Time Complexity:
----------------
O(n)

We traverse the array only once.

Every iteration performs constant-time comparisons and updates.


Space Complexity:
-----------------
O(1)

Only three variables are used:

    inc
    dec
    ans

No additional data structure is required.


===============================================================================
Dry Run With Example
===============================================================================

Example:

    nums = [1, 4, 3, 3, 2]

n = 5

Initially:

    inc = 1
    dec = 1
    ans = 1


Step 1:
-------

i = 1

    nums[1] = 4
    nums[0] = 1

Condition:

    4 > 1

Increasing sequence.

Update:

    inc = 2
    dec = 1
    ans = 2


Step 2:
-------

i = 2

    nums[2] = 3
    nums[1] = 4

Condition:

    3 < 4

Decreasing sequence.

Update:

    dec = 2
    inc = 1
    ans = 2


Step 3:
-------

i = 3

    nums[3] = 3
    nums[2] = 3

Condition:

    3 == 3

Equal elements.

Update:

    inc = 1
    dec = 1
    ans = 2


Step 4:
-------

i = 4

    nums[4] = 2
    nums[3] = 3

Condition:

    2 < 3

Decreasing sequence.

Update:

    dec = 2
    inc = 1
    ans = 2


Final Answer:
-------------

    ans = 2


===============================================================================
Dry Run Table
===============================================================================

Input:

    nums = [1, 4, 3, 3, 2]

Initially:

    inc = 1
    dec = 1
    ans = 1


i | nums[i] | Condition   | inc | dec | ans
--|---------|-------------|-----|-----|----
0 | 1       | Initial     | 1   | 1   | 1
1 | 4       | Increasing  | 2   | 1   | 2
2 | 3       | Decreasing  | 1   | 2   | 2
3 | 3       | Equal       | 1   | 1   | 2
4 | 2       | Decreasing  | 1   | 2   | 2


===============================================================================
Another Dry Run
===============================================================================

Example:

    nums = [3, 2, 1]

Initially:

    inc = 1
    dec = 1
    ans = 1


i = 1:

    2 < 3

    dec = 2
    inc = 1
    ans = 2


i = 2:

    1 < 2

    dec = 3
    inc = 1
    ans = 3


Final Answer:

    3


===============================================================================
Edge Cases
===============================================================================

1. Empty array:

       []

   Note: LeetCode guarantees at least one element.

   If empty arrays were allowed, handle n == 0 separately.


2. Single element:

       [5]

   Answer:

       1


3. All equal elements:

       [3, 3, 3, 3]

   No strictly increasing or decreasing subarray of length > 1.

   Answer:

       1


4. Completely increasing:

       [1, 2, 3, 4, 5]

   Entire array is strictly increasing.

   Answer:

       5


5. Completely decreasing:

       [5, 4, 3, 2, 1]

   Entire array is strictly decreasing.

   Answer:

       5


6. Contains duplicates:

       [1, 2, 2, 3, 4]

   Longest monotonic subarray:

       [2, 3, 4]

   Answer:

       3


7. Mixed increasing and decreasing:

       [1, 5, 4, 3, 2]

   Longest monotonic subarray:

       [5, 4, 3, 2]

   Answer:

       4


8. Negative numbers:

       [-5, -4, -3, -2]

   Entire array is strictly increasing.

   Answer:

       4


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Array + Greedy + Single Traversal + Two Counters


Key Observation:
----------------
Only adjacent elements need to be compared.

We do not need sorting or generating all subarrays.

Maintain two counters:

    inc = Increasing subarray length

    dec = Decreasing subarray length


Core Idea:
----------

If current element is greater:

    inc++
    dec = 1


If current element is smaller:

    dec++
    inc = 1


If current element is equal:

    inc = 1
    dec = 1


Update:

    ans = max(ans, max(inc, dec))


Common Mistakes:
----------------

1. Sorting the array.

   Sorting changes the original order and destroys
   the contiguous subarray information.


2. Using >= instead of >.

   The subarray must be strictly increasing.


3. Using <= instead of <.

   The subarray must be strictly decreasing.


4. Forgetting to reset the opposite counter.

   When increasing, reset dec.

   When decreasing, reset inc.


5. Forgetting to reset both counters when equal elements occur.


6. Initializing inc, dec and ans with 0 instead of 1.

   A single element is itself a valid monotonic subarray.


7. Using nested loops unnecessarily.

   The optimal approach requires only one traversal.


When To Use This Approach:
--------------------------

1. When finding the longest contiguous increasing sequence.

2. When finding the longest contiguous decreasing sequence.

3. When adjacent comparisons determine whether a sequence continues.

4. When a problem can be solved using counters.

5. When O(n) time and O(1) extra space are required.


===============================================================================
Important Difference: Subarray vs Subsequence
===============================================================================

SUBARRAY:
---------

Elements must be contiguous.

Example:

    [1, 2, 3, 4]

    [1, 2, 3] is a subarray.

    [1, 3, 4] is NOT a subarray.


SUBSEQUENCE:
------------

Elements do not need to be contiguous.

Example:

    [1, 2, 3, 4]

    [1, 3, 4] is a subsequence.


LeetCode 3105 asks for a SUBARRAY.

Therefore, we compare adjacent elements.


===============================================================================
VS CODE TESTING
===============================================================================

Expected Output:

    Test Case 1: 2
    Test Case 2: 1
    Test Case 3: 3
    Test Case 4: 5
    Test Case 5: 5
    Test Case 6: 3


Compile:

    g++ -std=c++17 main.cpp -o main

Run:

    ./main


===============================================================================
FINAL COMPLEXITY
===============================================================================

Time Complexity:

    O(n)

Space Complexity:

    O(1)


FINAL TAKEAWAY:
---------------

Increasing  -> inc++, reset dec

Decreasing  -> dec++, reset inc

Equal       -> reset both

This is a SINGLE TRAVERSAL solution.

================================================================================
                         END OF LEETCODE 3105
================================================================================
*/

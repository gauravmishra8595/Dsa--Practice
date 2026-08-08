#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> shuffle(vector<int> &nums, int n)
    {
        vector<int> ans(2 * n);

        for (int i = 0; i < n; i++)
        {
            ans[2 * i] = nums[i];
            ans[2 * i + 1] = nums[i + n];
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {2, 5, 1, 3, 4, 7};
    int n = 3;

    vector<int> ans = sol.shuffle(nums, n);

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*
================================================================================
Q2. Shuffle the Array - LeetCode 1470
================================================================================

Problem Statement
-----------------
Given an array nums consisting of 2n elements in the form:

    [x1, x2, ..., xn, y1, y2, ..., yn]

Return the array in the form:

    [x1, y1, x2, y2, ..., xn, yn]


Example
-------
Input:
    nums = [2,5,1,3,4,7]
    n = 3

Output:
    [2,3,5,4,1,7]

Explanation:

    First half:
        [2, 5, 1]

    Second half:
        [3, 4, 7]

    Shuffle:
        [2,3,5,4,1,7]


================================================================================
Brute Force Approach
================================================================================

Idea
----
Create an empty answer array.

For every i from 0 to n-1:

    Add nums[i]
    Add nums[i+n]

This is already the simplest direct approach, so there is no
meaningful slower brute-force algorithm for this problem.


Pseudo Code
-----------
    create empty ans

    for i = 0 to n-1:
        ans.push_back(nums[i])
        ans.push_back(nums[i+n])

    return ans


Complete Brute Force Code
-------------------------
(The following code is inside comments only.)

class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans;

        for (int i = 0; i < n; i++) {
            ans.push_back(nums[i]);
            ans.push_back(nums[i + n]);
        }

        return ans;
    }
};


Time Complexity
---------------
    O(n)

Space Complexity
----------------
    O(n)

The output array itself requires O(2n) space.


================================================================================
Optimal Approach
================================================================================

Observation
-----------
The array is divided into two equal halves:

    X = [x1, x2, ..., xn]
    Y = [y1, y2, ..., yn]

We need:

    [x1, y1, x2, y2, ..., xn, yn]

Therefore, for every i:

    ans[2*i]     = nums[i]
    ans[2*i + 1] = nums[i+n]


Intuition
---------
The first n elements belong to the X sequence.

The next n elements belong to the Y sequence.

We simply take one element from each half at every step.

For example:

    nums = [2,5,1,3,4,7]
             X       Y

    X = [2,5,1]
    Y = [3,4,7]

i = 0:
    ans[0] = 2
    ans[1] = 3

i = 1:
    ans[2] = 5
    ans[3] = 4

i = 2:
    ans[4] = 1
    ans[5] = 7

Result:

    [2,3,5,4,1,7]


Pseudo Code
-----------
    create ans of size 2*n

    for i = 0 to n-1:

        ans[2*i]     = nums[i]
        ans[2*i + 1] = nums[i+n]

    return ans


Complete Optimal Code
---------------------
(The following code is inside comments only.)

class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(2 * n);

        for (int i = 0; i < n; i++) {
            ans[2 * i] = nums[i];
            ans[2 * i + 1] = nums[i + n];
        }

        return ans;
    }
};


Time Complexity
---------------
We process each pair exactly once.

    O(n)


Space Complexity
----------------
The result contains 2n elements.

    O(n)

The extra space is required for the returned array.


================================================================================
Dry Run with Example
================================================================================

Input:

    nums = [2, 5, 1, 3, 4, 7]
    n = 3


Initial:

    ans = [_, _, _, _, _, _]


i = 0:

    ans[0] = nums[0] = 2
    ans[1] = nums[3] = 3

    ans = [2, 3, _, _, _, _]


i = 1:

    ans[2] = nums[1] = 5
    ans[3] = nums[4] = 4

    ans = [2, 3, 5, 4, _, _]


i = 2:

    ans[4] = nums[2] = 1
    ans[5] = nums[5] = 7

    ans = [2, 3, 5, 4, 1, 7]


Final Answer:

    [2, 3, 5, 4, 1, 7]


================================================================================
Interview Notes
================================================================================

Pattern
-------
Array Traversal + Index Mapping


Key Observation
---------------
The array has two halves:

    [x1, x2, ..., xn] [y1, y2, ..., yn]

We need to alternate them:

    x1, y1, x2, y2, ..., xn, yn

The index mapping is:

    nums[i]       -> ans[2*i]
    nums[i+n]     -> ans[2*i+1]


Common Mistakes
---------------
1. Forgetting that the second half starts at index n.

       nums[i+n]

2. Using the wrong answer indices.

       ans[2*i]
       ans[2*i+1]

3. Trying to rearrange nums in-place unnecessarily.

   A new array makes the solution simple and clean.

4. Confusing n with nums.size().

   nums.size() = 2*n


When to Use This Approach
-------------------------
Use this direct index-mapping approach when:

    - An array is divided into known sections.
    - Elements from different sections need to be interleaved.
    - The required output positions can be calculated directly.
    - You want an O(n) solution without complicated data structures.


Final Complexity:

    Time  = O(n)
    Space = O(n)

================================================================================
*/
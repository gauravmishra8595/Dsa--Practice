#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> getConcatenation(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ans(2 * n);

        for (int i = 0; i < n; i++)
        {
            ans[i] = nums[i];
            ans[i + n] = nums[i];
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 2, 1};

    vector<int> ans = sol.getConcatenation(nums);

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*
================================================================================
Q1. Concatenation of Array
================================================================================

Problem Statement
-----------------
Given an integer array nums of length n, create an array ans of length 2n
such that:

    ans[i] == nums[i]
    ans[i + n] == nums[i]

for every 0 <= i < n.

In simple words:

    ans = nums + nums

Example
-------
Input:
    nums = [1, 2, 1]

Output:
    [1, 2, 1, 1, 2, 1]

Explanation:
    Concatenating nums with itself gives:

    [1, 2, 1] + [1, 2, 1]
    = [1, 2, 1, 1, 2, 1]


================================================================================
Brute Force Approach
================================================================================

Idea
----
Create the answer array and append every element of nums twice.

One simple way is to use push_back() twice for every element.

Pseudo Code
-----------
    create empty ans

    for each x in nums:
        add x to ans
        add x to ans

    return ans


Complete Brute Force Code
-------------------------
(The following code is inside comments only.)

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        vector<int> ans;

        for (int x : nums) {
            ans.push_back(x);
            ans.push_back(x);
        }

        This produces:
        [1,1,2,2,1,1]
        which is NOT the required order.
    }
};


Better Direct Construction
--------------------------
Since the required order is:

    nums[0], nums[1], ..., nums[n-1],
    nums[0], nums[1], ..., nums[n-1]

we should copy the entire array twice.

Time Complexity
---------------
    O(n)

Space Complexity
----------------
    O(n)

The output itself requires O(2n) space.


================================================================================
Optimal Approach
================================================================================

Observation
-----------
The answer is simply nums concatenated with itself:

    ans = nums + nums

For every index i:

    ans[i]     = nums[i]
    ans[i + n] = nums[i]


Intuition
---------
We already know exactly where every element should go.

If:

    nums = [1, 2, 1]
    n = 3

then:

    ans[0] = nums[0]
    ans[1] = nums[1]
    ans[2] = nums[2]

and the second copy is:

    ans[3] = nums[0]
    ans[4] = nums[1]
    ans[5] = nums[2]

So we can fill both positions in one loop.


Pseudo Code
-----------
    n = nums.size()

    create ans of size 2 * n

    for i = 0 to n - 1:
        ans[i] = nums[i]
        ans[i + n] = nums[i]

    return ans


Complete Optimal Code
---------------------
(The following code is inside comments only.)

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();

        vector<int> ans(2 * n);

        for (int i = 0; i < n; i++) {
            ans[i] = nums[i];
            ans[i + n] = nums[i];
        }

        return ans;
    }
};


Time Complexity
---------------
We visit each element once and place it twice.

    O(n)


Space Complexity
----------------
The answer contains 2n elements.

    O(n)

Output space is unavoidable because we must return 2n elements.


================================================================================
Dry Run with Example
================================================================================

Input:

    nums = [1, 2, 1]

Step 1:
    n = 3

Create:

    ans = [_, _, _, _, _, _]


Step 2:
    i = 0

    ans[0] = nums[0] = 1
    ans[3] = nums[0] = 1

    ans = [1, _, _, 1, _, _]


Step 3:
    i = 1

    ans[1] = nums[1] = 2
    ans[4] = nums[1] = 2

    ans = [1, 2, _, 1, 2, _]


Step 4:
    i = 2

    ans[2] = nums[2] = 1
    ans[5] = nums[2] = 1

    ans = [1, 2, 1, 1, 2, 1]


Final Answer:

    [1, 2, 1, 1, 2, 1]


================================================================================
Interview Notes
================================================================================

Pattern
-------
Array Traversal / Direct Construction


Key Observation
---------------
The required array is simply:

    nums + nums

For every element at index i, place it at:

    i
    i + n


Common Mistakes
---------------
1. Using:

       ans.push_back(nums[i]);
       ans.push_back(nums[i]);

   This produces:

       [1,1,2,2,1,1]

   instead of:

       [1,2,1,1,2,1]

2. Forgetting that the answer has size 2 * n.

3. Accidentally modifying nums instead of creating the required
   concatenated array.


When to Use This Approach
-------------------------
Use direct index mapping when:

    - The output positions are known beforehand.
    - An array needs to be duplicated or transformed by index.
    - You want a simple O(n) construction.
    - You want to avoid unnecessary insertions/reallocations.


Final Complexity:

    Time  = O(n)
    Space = O(n)

================================================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findMaxConsecutiveOnes(vector<int> &nums)
    {
        int ans = 0;
        int count = 0;

        for (int x : nums)
        {
            if (x == 1)
            {
                count++;
                ans = max(ans, count);
            }
            else
            {
                count = 0;
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 1, 0, 1, 1, 1};

    cout << sol.findMaxConsecutiveOnes(nums) << '\n';

    return 0;
}

/*
================================================================================
Q4. Max Consecutive Ones - LeetCode 485
================================================================================

Problem Statement
-----------------
Given a binary array nums, return the maximum number of consecutive 1s
in the array.


Example
-------
Input:
    nums = [1,1,0,1,1,1]

Output:
    3

Explanation:
    The longest consecutive sequence of 1s is:

        [1,1,1]

    Its length is 3.


================================================================================
Brute Force Approach
================================================================================

Idea
----
For every position containing 1, start counting consecutive 1s until
we encounter a 0.

Keep track of the maximum count found.

This repeatedly scans parts of the array and is less efficient than
the one-pass solution.


Pseudo Code
-----------
    ans = 0

    for i = 0 to n-1:

        if nums[i] == 1:

            count = 0

            for j = i to n-1:

                if nums[j] == 1:
                    count++
                else:
                    break

            ans = max(ans, count)

    return ans


Complete Brute Force Code
-------------------------
(The following code is inside comments only.)

class BruteForceSolution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (nums[i] == 1) {
                int count = 0;

                for (int j = i; j < n; j++) {

                    if (nums[j] == 1)
                        count++;
                    else
                        break;
                }

                ans = max(ans, count);
            }
        }

        return ans;
    }
};


Time Complexity
---------------
Worst case, when all elements are 1, the inner loop is executed
repeatedly.

    O(n^2)


Space Complexity
----------------
Only variables are used.

    O(1)


================================================================================
Optimal Approach
================================================================================

Observation
-----------
We only need to know:

    1. Current consecutive count of 1s.
    2. Maximum consecutive count seen so far.

Whenever we see a 1:

    count++

Whenever we see a 0:

    count = 0

At every 1, update the answer.


Intuition
---------
Think of count as the length of the current block of consecutive 1s.

Example:

    [1, 1, 0, 1, 1, 1]

    1 -> count = 1
    1 -> count = 2
    0 -> count = 0
    1 -> count = 1
    1 -> count = 2
    1 -> count = 3

The largest value of count is 3.


Pseudo Code
-----------
    ans = 0
    count = 0

    for each x in nums:

        if x == 1:
            count++
            ans = max(ans, count)

        else:
            count = 0

    return ans


Complete Optimal Code
---------------------
(The following code is inside comments only.)

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int ans = 0;
        int count = 0;

        for (int x : nums) {

            if (x == 1) {
                count++;
                ans = max(ans, count);
            }
            else {
                count = 0;
            }
        }

        return ans;
    }
};


Time Complexity
---------------
We traverse the array exactly once.

    O(n)


Space Complexity
----------------
Only two integer variables are used.

    O(1)


================================================================================
Dry Run with Example
================================================================================

Input:

    nums = [1,1,0,1,1,1]


Initially:

    count = 0
    ans = 0


i = 0:
    nums[0] = 1

    count = 1
    ans = 1


i = 1:
    nums[1] = 1

    count = 2
    ans = 2


i = 2:
    nums[2] = 0

    count = 0
    ans = 2


i = 3:
    nums[3] = 1

    count = 1
    ans = 2


i = 4:
    nums[4] = 1

    count = 2
    ans = 2


i = 5:
    nums[5] = 1

    count = 3
    ans = 3


Final Answer:

    3


================================================================================
Interview Notes
================================================================================

Pattern
-------
Simple Array Traversal / Counting


Key Observation
---------------
A zero breaks the current sequence of consecutive 1s.

Therefore:

    1 -> increase count
    0 -> reset count to 0


Common Mistakes
---------------
1. Forgetting to reset count when a 0 appears.

2. Returning count instead of ans.

   count represents only the current sequence.

   ans represents the maximum sequence found anywhere.

3. Updating ans after resetting count.

   The answer should be updated when we process a 1.


When to Use This Approach
-------------------------
Use this pattern when:

    - You need the longest consecutive sequence.
    - A particular value breaks the sequence.
    - You only need the length, not the actual indices.
    - The array can be processed in one pass.


General Template
----------------
    current = 0
    answer = 0

    for each element:

        if element satisfies condition:
            current++
            answer = max(answer, current)
        else:
            current = 0


Final Complexity:

    Time  = O(n)
    Space = O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        int prev2 = nums[0];
        int prev1 = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++)
        {
            int curr = max(prev1, nums[i] + prev2);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    Solution obj;

    cout << obj.rob(nums);

    return 0;
}

/*
=========================================================
             LeetCode 198. House Robber
=========================================================

Problem Statement
-----------------
You are a professional robber planning to rob houses along a
street.

Each house has some amount of money stored in it.

You cannot rob two adjacent houses because the security system
will be triggered.

Return the maximum amount of money you can rob tonight without
alerting the police.

---------------------------------------------------------
Example
---------------------------------------------------------

Input:
nums = [2,7,9,3,1]

Output:
12

Explanation:

Rob house 0 -> 2
Rob house 2 -> 9
Rob house 4 -> 1

Total = 2 + 9 + 1 = 12

=========================================================
Brute Force Approach (Recursion)
=========================================================

Idea
----
At every house we have two choices:

1. Rob the current house.
   - Add nums[i]
   - Move to i-2 because adjacent houses cannot be robbed.

2. Skip the current house.
   - Move to i-1.

Take the maximum of both choices.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(index):

    if index < 0:
        return 0

    rob = nums[index] + solve(index-2)

    skip = solve(index-1)

    return max(rob, skip)


Answer:
solve(n-1)

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:

    int solve(vector<int>& nums, int i) {

        if(i < 0)
            return 0;

        int rob = nums[i] + solve(nums, i-2);

        int skip = solve(nums, i-1);

        return max(rob, skip);
    }


    int rob(vector<int>& nums) {

        int n = nums.size();

        return solve(nums, n-1);
    }
};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

O(2^n)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(n)

(Recursion Stack)

=========================================================
Optimal Approach (Dynamic Programming + Space Optimization)
=========================================================

Observation
-----------
For every house i:

Two choices:

1. Do not rob house i:
   Answer remains dp[i-1]

2. Rob house i:
   Add nums[i] with best answer till i-2

Therefore:

dp[i] = max(dp[i-1], nums[i] + dp[i-2])

---------------------------------------------------------
Intuition
---------
The answer for the current house depends only on the previous
two states.

So we do not need a complete DP array.

Maintain:

prev2 = dp[i-2]

prev1 = dp[i-1]

Current answer:

curr = max(prev1, nums[i] + prev2)

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

if n == 1:
    return nums[0]


prev2 = nums[0]

prev1 = max(nums[0], nums[1])


for i = 2 to n-1:

    curr = max(prev1, nums[i] + prev2)

    prev2 = prev1

    prev1 = curr


return prev1

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {
public:

    int rob(vector<int>& nums) {

        int n = nums.size();

        if(n == 1)
            return nums[0];


        int prev2 = nums[0];

        int prev1 = max(nums[0], nums[1]);


        for(int i=2;i<n;i++) {

            int curr = max(prev1,
                           nums[i] + prev2);

            prev2 = prev1;

            prev1 = curr;
        }


        return prev1;
    }
};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

O(n)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(1)

=========================================================
Dry Run
=========================================================

nums = [2,7,9,3,1]


Initial:

prev2 = 2

prev1 = max(2,7)

prev1 = 7


i = 2

curr = max(7, 9+2)

curr = max(7,11)

curr = 11


Update:

prev2 = 7

prev1 = 11


i = 3

curr = max(11,3+7)

curr = max(11,10)

curr = 11


Update:

prev2 = 11

prev1 = 11


i = 4

curr = max(11,1+11)

curr = max(11,12)

curr = 12


Answer = 12


=========================================================
Interview Notes
=========================================================

Pattern
-------

Dynamic Programming

1D DP

Maximum Sum with No Adjacent Elements


---------------------------------------------------------
Key Observation
---------------------------------------------------------

At every index:

Either take the current house
or skip it.

The current choice depends only on previous two choices.


---------------------------------------------------------
Common Mistakes
---------------------------------------------------------

1. Adding adjacent houses together.

2. Forgetting the n==1 case.

3. Using nums[i-1] instead of dp[i-1].

4. Using recursion without memoization.

5. Returning the wrong final state.


---------------------------------------------------------
When to use this approach
---------------------------------------------------------

Use this pattern when:

- You need maximum/minimum value from a sequence.

- Adjacent elements cannot be selected together.

- Current state depends on previous one or two states.

Examples:

- House Robber
- Maximum sum of non-adjacent elements
- Similar linear DP problems


=========================================================
*/
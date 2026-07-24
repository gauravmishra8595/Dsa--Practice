#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: Memoization (Top-Down DP)
class Solution
{
public:
    bool solve(vector<int> &nums, int idx, int target, vector<vector<int>> &dp)
    {
        if (target == 0)
            return true;

        if (idx == nums.size())
            return false;

        if (dp[idx][target] != -1)
            return dp[idx][target];

        bool take = false;

        if (nums[idx] <= target)
        {
            take = solve(nums, idx + 1, target - nums[idx], dp);
        }

        bool notTake = solve(nums, idx + 1, target, dp);

        return dp[idx][target] = take || notTake;
    }

    bool canPartition(vector<int> &nums)
    {
        int totalSum = 0;

        for (int x : nums)
            totalSum += x;

        if (totalSum % 2 != 0)
            return false;

        int target = totalSum / 2;

        vector<vector<int>> dp(nums.size(), vector<int>(target + 1, -1));

        return solve(nums, 0, target, dp);
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {1, 5, 11, 5};

    if (obj.canPartition(nums))
        cout << "true";
    else
        cout << "false";

    return 0;
}

/*

============================================================
                 LEETCODE 416 - PARTITION EQUAL SUBSET SUM
============================================================


Problem Statement:
------------------
Given an integer array nums, return true if you can partition the
array into two subsets such that the sum of elements in both subsets
is equal. Otherwise, return false.


Example:
--------
Input:
nums = [1,5,11,5]

Output:
true

Explanation:
Total sum = 22
Two subsets with equal sum:
[11,5] and [1,5,10] (conceptually target = 11)



============================================================
BRUTE FORCE APPROACH
============================================================


Idea:
-----
Try every possible subset and check if any subset has sum equal to
half of the total sum.

At every index:
1. Include current element.
2. Exclude current element.


Pseudo Code:
------------

solve(index, target):

    if target == 0:
        return true

    if index == n:
        return false

    take = solve(index + 1, target - nums[index])

    notTake = solve(index + 1, target)

    return take OR notTake


Complete Brute Force Code:

class Solution {
public:
    bool solve(vector<int>& nums, int idx, int target) {

        if(target == 0)
            return true;

        if(idx == nums.size())
            return false;

        bool take = false;

        if(nums[idx] <= target)
            take = solve(nums, idx + 1,
                         target - nums[idx]);

        bool notTake = solve(nums, idx + 1,
                             target);

        return take || notTake;
    }


    bool canPartition(vector<int>& nums) {

        int sum = 0;

        for(int x : nums)
            sum += x;

        if(sum % 2 != 0)
            return false;

        return solve(nums, 0, sum/2);
    }
};


Time Complexity:
----------------
O(2^n)

Space Complexity:
-----------------
O(n) recursion stack



============================================================
OPTIMAL APPROACH
============================================================


Observation:
------------
If total sum is odd, we cannot divide it into two equal parts.

If total sum is even, the problem becomes:

"Can we find a subset whose sum is totalSum/2?"


Intuition:
----------
This is a classic Subset Sum problem.

For every index, we have two choices:

1. Take the element.
2. Skip the element.

Since many states repeat, store the result of each
(index, target) combination using DP.


Pseudo Code:
------------

solve(index, target):

    if target == 0:
        return true

    if index == n:
        return false

    if dp[index][target] already exists:
        return stored answer


    take = false

    if nums[index] <= target:
        take = solve(index+1,
                     target-nums[index])


    notTake = solve(index+1,
                    target)


    store and return:
    dp[index][target] = take OR notTake



Complete Optimal Code:

class Solution {
public:

    bool solve(vector<int>& nums,
               int idx,
               int target,
               vector<vector<int>>& dp) {

        if(target == 0)
            return true;

        if(idx == nums.size())
            return false;


        if(dp[idx][target] != -1)
            return dp[idx][target];


        bool take = false;

        if(nums[idx] <= target) {

            take = solve(nums,
                         idx+1,
                         target-nums[idx],
                         dp);
        }


        bool notTake = solve(nums,
                             idx+1,
                             target,
                             dp);


        return dp[idx][target] = take || notTake;
    }



    bool canPartition(vector<int>& nums) {

        int totalSum = 0;

        for(int x : nums)
            totalSum += x;


        if(totalSum % 2 != 0)
            return false;


        int target = totalSum / 2;


        vector<vector<int>> dp(
            nums.size(),
            vector<int>(target+1, -1)
        );


        return solve(nums, 0, target, dp);
    }
};



Time Complexity:
----------------
O(n * target)

where target = totalSum / 2


Space Complexity:
-----------------
O(n * target) for DP table

+ O(n) recursion stack



============================================================
DRY RUN
============================================================


nums = [1,5,11,5]

Total Sum = 22

Target = 22/2 = 11


Start:
solve(index = 0, target = 11)


Choices:

Take 1:
target becomes 10

Skip 1:
target remains 11


Continue exploring choices.

When we reach element 11:

Take 11:
target becomes 0


target == 0

Return true.


Therefore:
A subset with sum 11 exists.

Answer = true



============================================================
INTERVIEW NOTES
============================================================


Pattern:
--------
Dynamic Programming
Subset Sum
0/1 Knapsack


Key Observation:
----------------
Equal partition means finding one subset with sum:

totalSum / 2


Common Mistakes:
----------------
1. Forgetting to check if total sum is odd.

2. Using only dp[index] instead of dp[index][target].

3. Returning true only because total sum is even.

4. Forgetting to store calculated states.

5. Not handling target == 0 base case.


When to use this approach:
--------------------------
Use this pattern when:

- Each element can be either chosen or skipped.
- We need to find a subset with a particular sum.
- The problem involves partitioning, selection, or target sum.

This is the standard 0/1 Knapsack pattern.

============================================================

*/
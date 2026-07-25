#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {

        int total = 0;

        for (int num : nums)
            total += num;

        // If target is outside possible range
        if (abs(target) > total)
            return 0;

        // Target + total must be even
        if ((target + total) % 2 != 0)
            return 0;

        int requiredSum = (target + total) / 2;

        vector<int> dp(requiredSum + 1, 0);

        // There is one way to make sum 0
        dp[0] = 1;

        for (int num : nums)
        {

            // Traverse backwards to avoid using same number twice
            for (int sum = requiredSum; sum >= num; sum--)
            {

                dp[sum] += dp[sum - num];
            }
        }

        return dp[requiredSum];
    }
};

int main()
{

    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    int target;
    cin >> target;

    Solution obj;

    cout << obj.findTargetSumWays(nums, target);

    return 0;
}

/*

=========================================================
LeetCode 494. Target Sum
=========================================================


Problem Statement:
------------------

You are given an integer array nums and an integer target.

You need to place either '+' or '-' before every number
so that the final expression equals target.

Return the number of possible expressions.


=========================================================
Example:
=========================================================

Input:

nums = [1,1,1,1,1]
target = 3


Output:

5


Explanation:

+1+1+1+1-1 = 3
+1+1+1-1+1 = 3
+1+1-1+1+1 = 3
+1-1+1+1+1 = 3
-1+1+1+1+1 = 3


=========================================================
Brute Force Approach:
=========================================================


Idea:
-----

For every number we have two choices:

1. Add '+'
2. Add '-'


Generate all possible combinations.

When all numbers are processed,
check whether the current sum equals target.


Pseudo Code:
------------

solve(index, sum)

if index == nums.size()

    if sum == target
        return 1

    else
        return 0


choose '+'

take = solve(index+1, sum + nums[index])


choose '-'

notTake = solve(index+1, sum - nums[index])


return take + notTake



Complete Brute Force Code:
--------------------------

class Solution {

public:

    int solve(vector<int>& nums, int idx, int sum, int target) {

        if(idx == nums.size()) {

            return sum == target;

        }


        int add = solve(nums,
                        idx + 1,
                        sum + nums[idx],
                        target);


        int subtract = solve(nums,
                             idx + 1,
                             sum - nums[idx],
                             target);


        return add + subtract;

    }


    int findTargetSumWays(vector<int>& nums, int target) {

        return solve(nums,0,0,target);

    }

};


Time Complexity:
----------------

O(2^N)


Space Complexity:
-----------------

O(N)

(recursion stack)



=========================================================
Optimal Approach:
=========================================================


Observation:
------------

Let:

Positive sum = P

Negative sum = N


We know:

P - N = target


Also:

P + N = totalSum


Adding both equations:

2P = target + totalSum


Therefore:

P = (target + totalSum) / 2


Now the problem becomes:

"Count subsets whose sum is P"



Intuition:
----------

Instead of deciding '+' and '-' separately,

we find how many subsets can create the required
positive sum.

This becomes a classic:

0/1 Knapsack Count Subset Sum problem.



Pseudo Code:
------------


calculate total sum


requiredSum = (total + target) / 2


create dp array


dp[0] = 1


for every number:

    for sum from requiredSum down to number:

        dp[sum] += dp[sum-number]


return dp[requiredSum]




Complete Optimal Code:
----------------------


class Solution {

public:

    int findTargetSumWays(vector<int>& nums,int target){

        int total = 0;


        for(int x : nums)
            total += x;


        if(abs(target) > total)
            return 0;


        if((total + target) % 2 != 0)
            return 0;


        int requiredSum = (total + target)/2;


        vector<int> dp(requiredSum+1,0);


        dp[0] = 1;


        for(int num : nums){

            for(int sum = requiredSum;
                sum >= num;
                sum--){

                dp[sum] += dp[sum-num];

            }

        }


        return dp[requiredSum];

    }

};



Time Complexity:
----------------

O(N * Sum)


where Sum = (totalSum + target)/2



Space Complexity:
-----------------

O(Sum)



=========================================================
Dry Run:
=========================================================


nums = [1,1,1,1,1]

target = 3


Total sum:

5


Required positive sum:


(5 + 3) / 2


= 4



Now count subsets with sum 4.


Possible subsets:

1+1+1+1


There are 5 ways to choose four 1's
from five numbers.


Answer:

5



=========================================================
Interview Notes:
=========================================================


Pattern:
--------

0/1 Knapsack

Subset Sum Counting



Key Observation:
----------------

Target Sum can be converted into:

Count subsets with a required sum.



Common Mistakes:
----------------

1. Forgetting impossible cases.

2. Not checking odd value of:

   total + target


3. Traversing dp from left to right.

   It will reuse the same number multiple times.


4. Confusing subset sum with normal subset existence.


When to use this approach:
--------------------------

Use this when:

- Every element has two choices (+/-)
- Need number of ways
- Need count of subsets
- Target based problems
- Knapsack style problems


=========================================================

*/
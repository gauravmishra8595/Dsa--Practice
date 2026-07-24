#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: Memoization (Top-Down DP)
class Solution
{
public:
    int solve(vector<int> &coins, int amount, vector<int> &dp)
    {

        if (amount == 0)
            return 0;

        if (amount < 0)
            return INT_MAX - 1;

        if (dp[amount] != -1)
            return dp[amount];

        int ans = INT_MAX - 1;

        for (int coin : coins)
        {

            int result = solve(coins, amount - coin, dp);

            if (result != INT_MAX - 1)
            {
                ans = min(ans, 1 + result);
            }
        }

        return dp[amount] = ans;
    }

    int coinChange(vector<int> &coins, int amount)
    {

        vector<int> dp(amount + 1, -1);

        int ans = solve(coins, amount, dp);

        if (ans == INT_MAX - 1)
            return -1;

        return ans;
    }
};

int main()
{

    Solution obj;

    vector<int> coins = {1, 2, 5};
    int amount = 11;

    cout << obj.coinChange(coins, amount);

    return 0;
}

/*

============================================================
                 LEETCODE 322 - COIN CHANGE
============================================================


Problem Statement:
------------------

You are given an integer array coins representing different
denominations and an integer amount.

Return the fewest number of coins needed to make up that amount.

If the amount cannot be made using any combination of coins,
return -1.

You can use each coin denomination unlimited times.



Example:
--------

Input:
coins = [1,2,5]
amount = 11

Output:
3

Explanation:

11 = 5 + 5 + 1

Minimum coins required = 3



============================================================
BRUTE FORCE APPROACH
============================================================


Idea:
-----

Try every possible coin choice recursively.

For every amount:

1. Pick a coin.
2. Reduce the remaining amount.
3. Find the minimum coins required.

There will be many repeated calculations.



Pseudo Code:
------------

solve(amount):

    if amount == 0:
        return 0

    if amount < 0:
        return infinity


    answer = infinity


    for every coin:

        answer = min(answer,
                     1 + solve(amount - coin))


    return answer



Complete Brute Force Code:

class Solution {

public:

    int solve(vector<int>& coins, int amount) {

        if(amount == 0)
            return 0;


        if(amount < 0)
            return INT_MAX - 1;


        int ans = INT_MAX - 1;


        for(int coin : coins) {

            int result =
            solve(coins,
                  amount - coin);


            if(result != INT_MAX - 1)
                ans = min(ans,
                          1 + result);
        }


        return ans;
    }



    int coinChange(vector<int>& coins,
                   int amount) {


        int ans = solve(coins, amount);


        if(ans == INT_MAX - 1)
            return -1;


        return ans;
    }

};



Time Complexity:
----------------

O(coins^amount)

Exponential recursion.



Space Complexity:
-----------------

O(amount)

Recursion stack.



============================================================
OPTIMAL APPROACH
============================================================


Observation:
------------

The same amount values are calculated multiple times.

Example:

solve(5)

can be reached from different paths.

So store the answer for every amount.



Intuition:
----------

This is an Unbounded Knapsack problem.

Difference from 0/1 Knapsack:

- Coin can be used multiple times.
- After taking a coin, we solve the remaining amount.

State:

dp[amount]

stores the minimum coins needed for that amount.



Pseudo Code:
------------


solve(amount):

    if amount == 0:
        return 0


    if amount < 0:
        return infinity


    if dp[amount] exists:
        return stored answer


    answer = infinity


    for every coin:

        result = solve(amount - coin)

        if result is valid:

            answer = min(answer,
                         1 + result)


    store answer

    return answer



Complete Optimal Code:

class Solution {

public:

    int solve(vector<int>& coins,
              int amount,
              vector<int>& dp) {


        if(amount == 0)
            return 0;


        if(amount < 0)
            return INT_MAX - 1;


        if(dp[amount] != -1)
            return dp[amount];



        int ans = INT_MAX - 1;



        for(int coin : coins) {


            int result =
            solve(coins,
                  amount - coin,
                  dp);



            if(result != INT_MAX - 1) {

                ans = min(ans,
                          1 + result);
            }
        }



        return dp[amount] = ans;
    }



    int coinChange(vector<int>& coins,
                   int amount) {


        vector<int> dp(amount + 1, -1);



        int ans =
        solve(coins,
              amount,
              dp);



        if(ans == INT_MAX - 1)
            return -1;



        return ans;
    }

};



Time Complexity:
----------------

O(amount * number_of_coins)


Every amount state is calculated once.



Space Complexity:
-----------------

O(amount)

DP array + recursion stack.



============================================================
DRY RUN
============================================================


coins = [1,2,5]

amount = 11



solve(11)


Try coins:

Take 1:

solve(10) + 1


Take 2:

solve(9) + 1


Take 5:

solve(6) + 1



Best path:

11
 |
 5
 |
 5
 |
 1
 |
 0



Coins used:

5 + 5 + 1 = 3



Answer:

3



============================================================
INTERVIEW NOTES
============================================================


Pattern:
--------

Dynamic Programming

Unbounded Knapsack



Key Observation:
----------------

Coins can be selected unlimited times.

The state depends only on:

remaining amount



Common Mistakes:
----------------

1. Treating it as 0/1 Knapsack.

2. Moving index after taking a coin.

3. Using INT_MAX and adding 1 to it.

4. Forgetting impossible cases.

5. Not memoizing repeated amounts.



When to use this approach:
--------------------------

Use this pattern when:

- Elements can be reused unlimited times.
- Need minimum or maximum count/value.
- Need to reach a target sum.

Examples:

- Coin Change
- Rod Cutting
- Unlimited Knapsack



============================================================

*/
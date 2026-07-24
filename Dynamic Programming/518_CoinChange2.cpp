#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: Memoization (Top-Down DP)
class Solution
{
public:
    long long solve(vector<int> &coins, int idx, int amount, vector<vector<long long>> &dp)
    {

        if (amount == 0)
            return 1;

        if (idx == coins.size())
            return 0;

        if (dp[idx][amount] != -1)
            return dp[idx][amount];

        long long take = 0;

        if (coins[idx] <= amount)
        {
            take = solve(coins, idx, amount - coins[idx], dp);
        }

        long long notTake = solve(coins, idx + 1, amount, dp);

        return dp[idx][amount] = take + notTake;
    }

    int change(int amount, vector<int> &coins)
    {

        vector<vector<long long>> dp(
            coins.size(),
            vector<long long>(amount + 1, -1));

        return solve(coins, 0, amount, dp);
    }
};

int main()
{

    Solution obj;

    vector<int> coins = {1, 2, 5};
    int amount = 5;

    cout << obj.change(amount, coins);

    return 0;
}

/*

============================================================
             LEETCODE 518 - COIN CHANGE II
============================================================


Problem Statement:
------------------

You are given an integer array coins representing coins of different
denominations and an integer amount.

Return the number of combinations that make up that amount.

You may use each coin unlimited times.

Two combinations are considered different if the frequency of
at least one coin denomination is different.

Order of coins does not matter.



Example:
--------

Input:

coins = [1,2,5]
amount = 5


Output:

4


Explanation:

Possible combinations:

5

2 + 2 + 1

2 + 1 + 1 + 1

1 + 1 + 1 + 1 + 1



============================================================
BRUTE FORCE APPROACH
============================================================


Idea:
-----

Try every possible combination.

At every coin:

1. Take the coin.
2. Skip the coin.

Since coins can be reused, after taking a coin we stay at the
same index.

Count all valid ways.



Pseudo Code:
------------

solve(index, amount):

    if amount == 0:
        return 1


    if index == coins.size():
        return 0


    take = 0

    if coins[index] <= amount:

        take = solve(index,
                     amount - coins[index])


    notTake = solve(index + 1,
                    amount)


    return take + notTake



Complete Brute Force Code:

class Solution {

public:

    long long solve(vector<int>& coins,
                    int idx,
                    int amount) {


        if(amount == 0)
            return 1;


        if(idx == coins.size())
            return 0;



        long long take = 0;


        if(coins[idx] <= amount) {

            take = solve(coins,
                         idx,
                         amount - coins[idx]);
        }



        long long notTake =
        solve(coins,
              idx + 1,
              amount);



        return take + notTake;
    }



    int change(int amount,
               vector<int>& coins) {


        return solve(coins,
                     0,
                     amount);
    }
};



Time Complexity:
----------------

Exponential

O(2^amount)



Space Complexity:
-----------------

O(amount)

Recursion stack.



============================================================
OPTIMAL APPROACH
============================================================


Observation:
------------

The same states are calculated repeatedly.

State depends on:

1. Current coin index.
2. Remaining amount.


So store results using:

dp[index][amount]



Intuition:
----------

This is an Unbounded Knapsack problem.

Difference from 322 Coin Change:

322:
- Find minimum number of coins.
- Use minimum operation.

518:
- Count number of combinations.
- Add all possible ways.

When we take a coin:

We stay at the same index because coins can be reused.

When we skip:

Move to the next coin.



Pseudo Code:
------------

solve(index, amount):

    if amount == 0:
        return 1


    if index == n:
        return 0


    if dp[index][amount] exists:

        return stored answer



    take = 0


    if coin[index] <= amount:

        take = solve(index,
                     amount - coin[index])



    notTake = solve(index + 1,
                    amount)



    dp[index][amount] =
        take + notTake


    return dp[index][amount]



Complete Optimal Code:

class Solution {

public:

    long long solve(vector<int>& coins,
                    int idx,
                    int amount,
                    vector<vector<long long>>& dp) {


        if(amount == 0)
            return 1;


        if(idx == coins.size())
            return 0;



        if(dp[idx][amount] != -1)
            return dp[idx][amount];



        long long take = 0;



        if(coins[idx] <= amount) {

            take = solve(coins,
                         idx,
                         amount - coins[idx],
                         dp);
        }



        long long notTake =
        solve(coins,
              idx + 1,
              amount,
              dp);



        return dp[idx][amount] =
               take + notTake;
    }



    int change(int amount,
               vector<int>& coins) {


        vector<vector<long long>> dp(
            coins.size(),
            vector<long long>(amount + 1, -1)
        );


        return solve(coins,
                     0,
                     amount,
                     dp);
    }
};



Time Complexity:
----------------

O(number of coins * amount)


Every state (index, amount) is solved once.



Space Complexity:
-----------------

O(number of coins * amount)

For DP table.

+ O(amount) recursion stack.



============================================================
DRY RUN
============================================================


coins = [1,2,5]

amount = 5



Start:

solve(index = 0, amount = 5)



Using coin 1:

Ways to make amount 4 using coin 1

Continue...



Skip coin 1:

Move to coin 2



Using coin 2:

5 can become:

2 + 2 + 1



Skip to coin 5:

5 can become:

5



All valid combinations:

1+1+1+1+1

2+1+1+1

2+2+1

5



Answer = 4



============================================================
INTERVIEW NOTES
============================================================


Pattern:
--------

Dynamic Programming

Unbounded Knapsack



Key Observation:
----------------

Coins can be reused unlimited times.

For counting combinations:

take + notTake



Common Mistakes:
----------------

1. Using multiplication instead of addition.

2. Moving index forward after taking a coin.

3. Counting different orders as different answers.

Example:

2 + 1 and 1 + 2 are the same combination.


4. Forgetting that order does not matter.

5. Using 322 logic of minimum coins.



When to use this approach:
--------------------------

Use this pattern when:

- Elements can be chosen multiple times.
- Need number of ways/combinations.
- Order of selection does not matter.

Examples:

- Coin Change II
- Unbounded Knapsack counting problems
- Ways to reach a target sum



============================================================

*/
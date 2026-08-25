#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> dp;

    int solve(int i, int j, vector<int> &nums)
    {
        if (i == j)
            return nums[i];

        if (dp[i][j] != INT_MIN)
            return dp[i][j];

        int takeLeft = nums[i] - solve(i + 1, j, nums);
        int takeRight = nums[j] - solve(i, j - 1, nums);

        return dp[i][j] = max(takeLeft, takeRight);
    }

    bool predictTheWinner(vector<int> &nums)
    {
        int n = nums.size();
        dp.assign(n, vector<int>(n, INT_MIN));

        return solve(0, n - 1, nums) >= 0;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {1, 5, 2};

    cout << (obj.predictTheWinner(nums) ? "true" : "false") << endl;

    return 0;
}

/*

===========================
Leetcode 486. Predict the Winner
===========================

Problem Statement:
------------------
Two players are playing a game with an integer array nums.

Player 1 and Player 2 take turns, with Player 1 starting first.

On each turn, a player picks either the first or last number of the remaining array.
The picked number is added to that player's score.

Both players play optimally.

Return true if Player 1 can win or tie, otherwise return false.


Example:
--------
Input:
nums = [1,5,2]

Output:
false

Explanation:
Player1 cannot obtain a score greater than or equal to Player2.


====================================================
Brute Force Approach
====================================================

Idea:
-----
Try every possible move.

For every state (i,j):
1. Pick left.
2. Pick right.
3. Assume opponent also plays optimally.
4. Return maximum score obtainable.

Overlapping subproblems make this exponential.


Pseudo Code:
------------

solve(i,j)

if i>j
    return 0

takeLeft =
nums[i] +
min(
solve(i+2,j),
solve(i+1,j-1)
)

takeRight =
nums[j] +
min(
solve(i,j-2),
solve(i+1,j-1)
)

return max(takeLeft,takeRight)


Complete Brute Force Code:
--------------------------

class Solution {
public:

    int solve(int i,int j,vector<int>& nums){

        if(i>j)
            return 0;

        if(i==j)
            return nums[i];

        int takeLeft =
            nums[i] +
            min(
                solve(i+2,j,nums),
                solve(i+1,j-1,nums)
            );

        int takeRight =
            nums[j] +
            min(
                solve(i,j-2,nums),
                solve(i+1,j-1,nums)
            );

        return max(takeLeft,takeRight);
    }

    bool PredictTheWinner(vector<int>& nums){

        int total=accumulate(nums.begin(),nums.end(),0);

        int p1=solve(0,nums.size()-1,nums);

        return p1>=total-p1;
    }
};


Time Complexity:
----------------
O(2^N)

Space Complexity:
-----------------
O(N) recursion stack


====================================================
Optimal Approach (DP on Score Difference)
====================================================

Observation:
------------
Instead of calculating Player1's total score directly,
calculate the maximum score difference that the current player
can achieve over the opponent.

dp(i,j) =
(Current Player Score - Opponent Score)

If current player picks left,

difference =
nums[i] - solve(i+1,j)

because after taking nums[i], opponent becomes the current player.

Similarly,

difference =
nums[j] - solve(i,j-1)

Take the maximum.


Intuition:
----------
The game is zero-sum.

Whatever advantage the opponent gains is a loss for the current player.

Thus,

Current Gain - Opponent's Best Difference

gives the net advantage.


Pseudo Code:
------------

solve(i,j)

if i==j
    return nums[i]

takeLeft =
nums[i]-solve(i+1,j)

takeRight =
nums[j]-solve(i,j-1)

return max(takeLeft,takeRight)


Answer:

solve(0,n-1)>=0


Complete Optimal Code:
----------------------

class Solution {
public:

    vector<vector<int>> dp;

    int solve(int i,int j,vector<int>& nums){

        if(i==j)
            return nums[i];

        if(dp[i][j]!=INT_MIN)
            return dp[i][j];

        int takeLeft =
            nums[i]-solve(i+1,j,nums);

        int takeRight =
            nums[j]-solve(i,j-1,nums);

        return dp[i][j]=max(takeLeft,takeRight);
    }

    bool PredictTheWinner(vector<int>& nums){

        int n=nums.size();

        dp.assign(n,vector<int>(n,INT_MIN));

        return solve(0,n-1,nums)>=0;
    }
};


Time Complexity:
----------------
O(N^2)

Space Complexity:
-----------------
O(N^2) + O(N) recursion stack


====================================================
Dry Run
====================================================

nums = [1,5,2]

solve(0,2)

Take Left

1 - solve(1,2)

solve(1,2)

max(
5-2,
2-5
)

=max(3,-3)=3

Difference

1-3=-2


Take Right

2-solve(0,1)

solve(0,1)

max(
1-5,
5-1
)

=max(-4,4)=4

Difference

2-4=-2

Final

max(-2,-2)=-2

Since answer < 0

Player1 loses.

Return false.


====================================================
Interview Notes
====================================================

Pattern:
--------
Game Theory + Interval DP + Minimax

Key Observation:
----------------
Store score difference instead of actual scores.

This removes the need for the complicated min() transitions.

Common Mistakes:
----------------
1. Storing total score instead of score difference.
2. Forgetting memoization.
3. Returning total score instead of checking difference >= 0.
4. Using -1 as DP initialization (score difference can be -1).

When to use this approach:
--------------------------
Whenever:
- Two players play optimally.
- Turns alternate.
- Pick from ends.
- Zero-sum game.
- Need winner determination rather than actual sequence.

Classic Problems:
- Predict the Winner
- Stone Game
- Optimal Strategy for a Game
- Removal Games

*/

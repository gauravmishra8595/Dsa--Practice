#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int solve(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp)
    {
        int m = grid.size();
        int n = grid[0].size();

        if (i >= m || j >= n)
            return INT_MAX;

        if (i == m - 1 && j == n - 1)
            return grid[i][j];

        if (dp[i][j] != -1)
            return dp[i][j];

        int right = solve(grid, i, j + 1, dp);
        int down = solve(grid, i + 1, j, dp);

        return dp[i][j] = grid[i][j] + min(right, down);
    }

    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, -1));

        return solve(grid, 0, 0, dp);
    }
};

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }

    Solution obj;
    cout << obj.minPathSum(grid);

    return 0;
}

/*

=========================================================
LeetCode 64. Minimum Path Sum
=========================================================

Problem Statement
-----------------
Given an m x n grid filled with non-negative numbers, find a path
from top-left to bottom-right which minimizes the sum of all numbers
along its path.

You can only move:
1. Right
2. Down

Return the minimum path sum.

=========================================================
Example
=========================================================

Input:

grid =
[
 [1,3,1],
 [1,5,1],
 [4,2,1]
]

Output:
7

Explanation:

Path:
1 → 3 → 1 → 1 → 1

Total = 7

=========================================================
Brute Force Approach
=========================================================

Idea
----

At every cell we have two choices:

1. Move Right
2. Move Down

Try both recursively and return the minimum.

Since many paths overlap, recursion recomputes the same states.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(i,j)

if out of grid
    return INF

if destination
    return grid[i][j]

right = solve(i,j+1)

down = solve(i+1,j)

return grid[i][j] + min(right,down)

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:

    int solve(vector<vector<int>>& grid,int i,int j){

        int m=grid.size();
        int n=grid[0].size();

        if(i>=m || j>=n)
            return INT_MAX;

        if(i==m-1 && j==n-1)
            return grid[i][j];

        int right=solve(grid,i,j+1);
        int down=solve(grid,i+1,j);

        return grid[i][j]+min(right,down);
    }

    int minPathSum(vector<vector<int>>& grid) {
        return solve(grid,0,0);
    }
};

Time Complexity
---------------
O(2^(m+n))

Space Complexity
----------------
O(m+n) recursion stack

=========================================================
Optimal Approach (Memoization)
=========================================================

Observation
-----------

The minimum path from a cell is calculated many times.

Example:

solve(1,1)

can be reached from

solve(0,1)

and

solve(1,0)

Store every answer once.

---------------------------------------------------------
Intuition
---------------------------------------------------------

Define

dp[i][j]

= Minimum path sum starting from cell (i,j).

If already computed, directly return it.

Otherwise,

dp[i][j]

=
grid[i][j]

+

min(right path,
down path)

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(i,j)

if outside grid
    return INF

if destination
    return value

if already computed
    return dp

right = solve(i,j+1)

down = solve(i+1,j)

store

grid[i][j]+min(right,down)

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {
public:

    int solve(vector<vector<int>>& grid,int i,int j,
              vector<vector<int>>& dp){

        int m=grid.size();
        int n=grid[0].size();

        if(i>=m || j>=n)
            return INT_MAX;

        if(i==m-1 && j==n-1)
            return grid[i][j];

        if(dp[i][j]!=-1)
            return dp[i][j];

        int right=solve(grid,i,j+1,dp);
        int down=solve(grid,i+1,j,dp);

        return dp[i][j]=grid[i][j]+min(right,down);
    }

    int minPathSum(vector<vector<int>>& grid) {

        int m=grid.size();
        int n=grid[0].size();

        vector<vector<int>> dp(m,vector<int>(n,-1));

        return solve(grid,0,0,dp);
    }
};

Time Complexity
---------------
O(m*n)

Space Complexity
----------------
O(m*n) DP

+
O(m+n) recursion stack

=========================================================
Dry Run
=========================================================

Input

1 3 1
1 5 1
4 2 1

Start

solve(0,0)

Need

min(right,down)

↓

solve(0,1)

↓

solve(0,2)

↓

solve(1,2)

↓

solve(2,2)

Destination

returns 1

Now backtrack

dp[1][2]=1+1=2

dp[0][2]=1+2=3

dp[2][1]=2+1=3

dp[2][0]=4+3=7

dp[1][1]=5+min(2,3)=7

dp[1][0]=1+min(7,7)=8

dp[0][1]=3+min(3,7)=6

dp[0][0]=1+min(6,8)=7

Answer = 7

=========================================================
Interview Notes
=========================================================

Pattern
-------
Grid DP

Recursion + Memoization

Top-Down DP

---------------------------------------------------------

Key Observation
---------------

Every state depends only on:

Right cell

Down cell

Hence only two recursive calls.

---------------------------------------------------------

Common Mistakes
---------------

1. Wrong base case (i==j).

2. Forgetting boundary check.

3. Returning 0 for invalid cells instead of INF.

4. Forgetting memoization.

5. Using INT_MAX + grid value without ensuring invalid paths
   are never chosen.

---------------------------------------------------------

When to use this approach
-------------------------

Whenever a grid problem asks for:

• Minimum Cost

• Maximum Cost

• Number of Ways

• Only Right/Down movement

• Overlapping subproblems

This is a classic 2D Dynamic Programming problem.

=========================================================

*/
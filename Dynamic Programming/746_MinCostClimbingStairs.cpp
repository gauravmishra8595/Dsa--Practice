#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();

        int prev2 = cost[0];
        int prev1 = cost[1];

        for (int i = 2; i < n; i++)
        {
            int curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return min(prev1, prev2);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> cost(n);
    for (int i = 0; i < n; i++)
        cin >> cost[i];

    Solution obj;
    cout << obj.minCostClimbingStairs(cost);

    return 0;
}

/*
=========================================================
        LeetCode 746. Min Cost Climbing Stairs
=========================================================

Problem Statement
-----------------
You are given an integer array cost where cost[i] is the cost of
the i-th stair.

Once you pay the cost, you can climb either:
1. One stair
2. Two stairs

You can start from either stair 0 or stair 1.

Return the minimum cost to reach the top of the floor.

Note:
The top is just beyond the last stair and has no cost.

---------------------------------------------------------
Example
---------------------------------------------------------

Input:
cost = [10,15,20]

Output:
15

Explanation:

Start from stair 1.

Pay 15
Jump directly to the top.

Minimum Cost = 15

=========================================================
Brute Force Approach (Recursion)
=========================================================

Idea
----
To reach stair n,

Last move can come from:
- n-1
- n-2

Recursively compute the minimum cost to reach every stair.

This recomputes the same states many times.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(i)

if i==0
    return cost[0]

if i==1
    return cost[1]

return cost[i] + min(
            solve(i-1),
            solve(i-2)
       )

Answer:

min(
    solve(n-1),
    solve(n-2)
)

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:

    int solve(vector<int>& cost,int i){

        if(i==0)
            return cost[0];

        if(i==1)
            return cost[1];

        return cost[i] + min(
                    solve(cost,i-1),
                    solve(cost,i-2)
               );
    }

    int minCostClimbingStairs(vector<int>& cost) {

        int n=cost.size();

        return min(
            solve(cost,n-1),
            solve(cost,n-2)
        );
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

=========================================================
Optimal Approach (DP + Space Optimization)
=========================================================

Observation
-----------
Minimum cost to reach stair i depends only on:

dp[i-1]
dp[i-2]

Relation:

dp[i] = cost[i] + min(dp[i-1], dp[i-2])

Final Answer:

min(dp[n-1], dp[n-2])

because the top itself has no cost.

---------------------------------------------------------
Intuition
---------------------------------------------------------
Only the previous two DP states are required.

Instead of storing the entire DP array,
keep only:

prev2 = dp[i-2]

prev1 = dp[i-1]

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

if n==2
    return min(cost[0],cost[1])

prev2=cost[0]
prev1=cost[1]

for i=2 to n-1

    curr=cost[i]+min(prev1,prev2)

    prev2=prev1

    prev1=curr

return min(prev1,prev2)

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {
public:

    int minCostClimbingStairs(vector<int>& cost) {

        int n=cost.size();

        int prev2=cost[0];
        int prev1=cost[1];

        for(int i=2;i<n;i++){

            int curr=cost[i]+min(prev1,prev2);

            prev2=prev1;
            prev1=curr;
        }

        return min(prev1,prev2);
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

cost = [10,15,20]

Initial

prev2 = 10
prev1 = 15

i = 2

curr = 20 + min(10,15)

     = 20 + 10

     = 30

prev2 = 15
prev1 = 30

Loop Ends

Answer

min(15,30)=15

=========================================================
Interview Notes
=========================================================

Pattern
-------
Dynamic Programming

Linear DP

Space Optimization

---------------------------------------------------------
Key Observation
---------------------------------------------------------

Each stair depends only on the previous two stairs.

dp[i]=cost[i]+min(dp[i-1],dp[i-2])

The destination (top) has zero cost.

Hence answer is:

min(dp[n-1],dp[n-2])

---------------------------------------------------------
Common Mistakes
---------------------------------------------------------

1. Accessing cost[n] (out of bounds).

2. Forgetting that the top has no cost.

3. Returning dp[n-1] instead of
   min(dp[n-1],dp[n-2]).

4. Initializing DP incorrectly.

5. Confusing stair index with top index.

---------------------------------------------------------
When to use this approach
---------------------------------------------------------

Use whenever:

- State depends on previous one/two states.

- Need minimum/maximum cost.

- DP array can be reduced to constant space.

=========================================================
*/
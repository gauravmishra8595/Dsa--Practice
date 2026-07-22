#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;

        int prev2 = 1, prev1 = 2;

        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution obj;

    int n;
    cin >> n;

    cout << obj.climbStairs(n);

    return 0;
}

/*
=========================================================
                LeetCode 70. Climbing Stairs
=========================================================

Problem Statement
-----------------
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb:
1. 1 step
2. 2 steps

Return the number of distinct ways to reach the top.

---------------------------------------------------------
Example
---------------------------------------------------------

Input:
n = 5

Output:
8

Explanation:

1 1 1 1 1
1 1 1 2
1 1 2 1
1 2 1 1
2 1 1 1
2 2 1
2 1 2
1 2 2

Total = 8 ways

=========================================================
Brute Force Approach (Recursion)
=========================================================

Idea
----
At every stair we have two choices:
- Take 1 step
- Take 2 steps

So recursively compute:

ways(n) = ways(n-1) + ways(n-2)

This recomputes the same states many times.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

function solve(n):
    if n==1 return 1
    if n==2 return 2

    return solve(n-1)+solve(n-2)

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:
    int climbStairs(int n) {
        if(n<=2)
            return n;

        return climbStairs(n-1)+climbStairs(n-2);
    }
};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

O(2^n)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(n) (Recursion Stack)

=========================================================
Optimal Approach (DP - Fibonacci)
=========================================================

Observation
-----------
To reach stair n,

Last move can be:
1. From n-1 using one step.
2. From n-2 using two steps.

Therefore,

ways(n)=ways(n-1)+ways(n-2)

This is exactly the Fibonacci pattern.

---------------------------------------------------------
Intuition
---------------------------------------------------------
Instead of recomputing values repeatedly,
keep only the last two answers.

prev2 = ways(i-2)
prev1 = ways(i-1)

curr = prev1 + prev2

Update them while iterating.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

if n<=2
    return n

prev2=1
prev1=2

for i=3 to n
    curr=prev1+prev2
    prev2=prev1
    prev1=curr

return prev1

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {
public:
    int climbStairs(int n) {

        if(n<=2)
            return n;

        int prev2=1;
        int prev1=2;

        for(int i=3;i<=n;i++){

            int curr=prev1+prev2;

            prev2=prev1;
            prev1=curr;
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

n = 5

Initial

prev2 = 1
prev1 = 2

i = 3

curr = 1+2 = 3

prev2 = 2
prev1 = 3

------------------

i = 4

curr = 2+3 = 5

prev2 = 3
prev1 = 5

------------------

i = 5

curr = 3+5 = 8

prev2 = 5
prev1 = 8

Answer = 8

=========================================================
Interview Notes
=========================================================

Pattern
-------
Dynamic Programming
Fibonacci
Linear DP
Space Optimization

---------------------------------------------------------
Key Observation
---------------------------------------------------------

Every stair depends only on the previous two stairs.

dp[i] = dp[i-1] + dp[i-2]

Hence entire DP array is unnecessary.

---------------------------------------------------------
Common Mistakes
---------------------------------------------------------

1. Returning n directly.
2. Wrong base cases.
3. Starting loop from incorrect index.
4. Using recursion without memoization (TLE).
5. Forgetting n<=2 edge case.

---------------------------------------------------------
When to use this approach
---------------------------------------------------------

Whenever:
- Current state depends only on previous one or two states.
- Fibonacci-like recurrence exists.
- DP array can be reduced to constant space.

=========================================================
*/
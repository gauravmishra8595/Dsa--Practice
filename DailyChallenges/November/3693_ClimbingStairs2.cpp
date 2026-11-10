#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int jump = 1; jump <= 3; jump++) {
                int prev = i - jump;

                if (prev >= 0) {
                    int currCost = dp[prev] + costs[i - 1]
                                   + jump * jump;

                    dp[i] = min(dp[i], currCost);
                }
            }
        }

        return dp[n];
    }
};

//======================================================
//                       MAIN
//======================================================

int main() {
    Solution obj;

    int n = 4;
    vector<int> costs = {1, 2, 3, 4};

    cout << obj.climbStairs(n, costs) << endl;

    return 0;
}

/*

======================================================
       LEETCODE 3693 - CLIMBING STAIRS II
======================================================


1. PROBLEM STATEMENT
------------------------------------------------------

You are climbing a staircase with n + 1 steps,
numbered from 0 to n.

You are given an array costs of size n.

From step i, you can jump to:
    1. Step i + 1
    2. Step i + 2
    3. Step i + 3

Cost of jumping from step i to step j:

    costs[j - 1] + (j - i)^2

Initially, you are at step 0 with cost 0.

Return the minimum total cost to reach step n.


2. EXAMPLE
------------------------------------------------------

Input:
n = 4
costs = [1, 2, 3, 4]

Output:
13

Explanation:

One optimal path:

0 -> 1 -> 2 -> 4

Jump 0 -> 1:
Cost = 1 + 1^2 = 2

Jump 1 -> 2:
Cost = 2 + 1^2 = 3

Jump 2 -> 4:
Cost = 4 + 2^2 = 8

Total Cost = 2 + 3 + 8 = 13


======================================================
              3. BRUTE FORCE APPROACH
======================================================

IDEA:

Try all possible jumps from the current position.

At every position, recursively explore:
    1. Jump of 1 step
    2. Jump of 2 steps
    3. Jump of 3 steps

Calculate the cost of every possible path
and return the minimum cost.

BASE CASE:

If current position == n:
    Return 0


PSEUDO CODE:

function solve(i):

    if i == n:
        return 0

    ans = INF

    for jump = 1 to 3:

        next = i + jump

        if next <= n:

            cost = costs[next - 1] + jump * jump

            ans = min(ans, cost + solve(next))

    return ans

answer = solve(0)


COMPLETE BRUTE FORCE CODE:

    int solve(int i, int n, vector<int>& costs) {

        if (i == n)
            return 0;

        int ans = INT_MAX;

        for (int jump = 1; jump <= 3; jump++) {

            int next = i + jump;

            if (next <= n) {

                int cost = costs[next - 1]
                           + jump * jump;

                ans = min(ans,
                          cost + solve(next, n, costs));
            }
        }

        return ans;
    }

    int climbStairsBrute(int n, vector<int>& costs) {
        return solve(0, n, costs);
    }


TIME COMPLEXITY:

O(3^n)

At every position, we explore up to 3 choices.

SPACE COMPLEXITY:

O(n)

Recursive call stack depth can be at most n.


WHY BRUTE FORCE IS INEFFICIENT?

- Recalculates the same states repeatedly.
- Explores multiple overlapping paths.
- Exponential time complexity.

Solution: Dynamic Programming.


======================================================
              4. OPTIMAL APPROACH
======================================================

OBSERVATION:

To reach step i, we can come from:

    i - 1
    i - 2
    i - 3

Therefore, the minimum cost to reach step i
depends only on the previous three positions.


INTUITION:

Define:

    dp[i] = Minimum cost required to reach step i.

BASE CASE:

    dp[0] = 0

Because we start at step 0 without paying anything.

TRANSITION:

For every position i, try all possible jumps.

If jump = 1:
    Previous position = i - 1
    Jump penalty = 1^2

If jump = 2:
    Previous position = i - 2
    Jump penalty = 2^2

If jump = 3:
    Previous position = i - 3
    Jump penalty = 3^2

GENERAL FORMULA:

    dp[i] = min(
        dp[i-j] + costs[i-1] + j*j
    )

    where j = 1, 2, 3

Consider only valid previous positions.


PSEUDO CODE:

Initialize dp array of size n + 1 with INF.

dp[0] = 0

for i = 1 to n:

    for jump = 1 to 3:

        prev = i - jump

        if prev >= 0:

            currCost =
                dp[prev] + costs[i-1] + jump*jump

            dp[i] = min(dp[i], currCost)

return dp[n]


COMPLETE OPTIMAL CODE:

    class Solution {
    public:
        int climbStairs(int n, vector<int>& costs) {

            vector<int> dp(n + 1, INT_MAX);

            dp[0] = 0;

            for (int i = 1; i <= n; i++) {

                for (int jump = 1; jump <= 3; jump++) {

                    int prev = i - jump;

                    if (prev >= 0) {

                        int currCost = dp[prev]
                                       + costs[i - 1]
                                       + jump * jump;

                        dp[i] = min(dp[i], currCost);
                    }
                }
            }

            return dp[n];
        }
    };


TIME COMPLEXITY:

O(n * 3)

O(n)

For every position, we check only 3 possible jumps.


SPACE COMPLEXITY:

O(n)

We maintain a DP array of size n + 1.


======================================================
                  5. DRY RUN
======================================================

INPUT:

n = 4
costs = [1, 2, 3, 4]

INITIALIZATION:

dp = [0, INF, INF, INF, INF]


STEP 1: i = 1
------------------------------------------------------

Jump = 1:

dp[0] + costs[0] + 1^2
= 0 + 1 + 1
= 2

dp[1] = 2

dp = [0, 2, INF, INF, INF]


STEP 2: i = 2
------------------------------------------------------

Jump = 1:

dp[1] + costs[1] + 1^2
= 2 + 2 + 1
= 5

Jump = 2:

dp[0] + costs[1] + 2^2
= 0 + 2 + 4
= 6

Minimum = 5

dp = [0, 2, 5, INF, INF]


STEP 3: i = 3
------------------------------------------------------

Jump = 1:

dp[2] + costs[2] + 1^2
= 5 + 3 + 1
= 9

Jump = 2:

dp[1] + costs[2] + 2^2
= 2 + 3 + 4
= 9

Jump = 3:

dp[0] + costs[2] + 3^2
= 0 + 3 + 9
= 12

Minimum = 9

dp = [0, 2, 5, 9, INF]


STEP 4: i = 4
------------------------------------------------------

Jump = 1:

dp[3] + costs[3] + 1^2
= 9 + 4 + 1
= 14

Jump = 2:

dp[2] + costs[3] + 2^2
= 5 + 4 + 4
= 13

Jump = 3:

dp[1] + costs[3] + 3^2
= 2 + 4 + 9
= 15

Minimum = 13

dp = [0, 2, 5, 9, 13]


FINAL ANSWER:

dp[4] = 13

Output = 13


======================================================
                  6. INTERVIEW NOTES
======================================================

PATTERN:

Dynamic Programming - 1D DP

Sub-patterns:
- Minimum Cost DP
- Multi-step Transition DP
- Bottom-Up Tabulation


KEY OBSERVATION:

The minimum cost to reach the current position
depends only on the previous 3 positions.

Instead of exploring every possible path,
store the minimum cost for every position.


COMMON MISTAKES:

1. WRONG ARRAY INDEXING:

   Wrong:
       costs[i]

   Correct:
       costs[i - 1]

   Because vector indexing starts from 0.

2. WRONG JUMP PENALTY:

   Wrong:
       i * i

   Correct:
       jump * jump

   Penalty depends on jump distance,
   not destination position.

3. FORGETTING BASE CASE:

       dp[0] = 0

4. NOT CHECKING VALID POSITIONS:

       if (prev >= 0)

5. WRONG INITIALIZATION:

   Use INT_MAX for minimum cost DP,
   not zero.

6. USING RECURSION WITHOUT MEMOIZATION:

   This causes repeated calculations.


WHEN TO USE THIS APPROACH:

Use this pattern when:

- You need minimum or maximum cost.
- You can reach a position from a fixed number
  of previous positions.
- Every transition adds some cost.
- Previous states can be reused.


SIMILAR PROBLEMS:

1. LeetCode 70  - Climbing Stairs
2. LeetCode 746 - Min Cost Climbing Stairs
3. LeetCode 3693 - Climbing Stairs II
4. Frog Jump
5. Minimum Path Sum


======================================================
                  END OF NOTES
======================================================

*/
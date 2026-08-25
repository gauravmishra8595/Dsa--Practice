#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<vector<int>> dp;
    vector<int> suffix;

    int solve(int idx, int M, vector<int>& piles) {
        if (idx >= n) return 0;

        if (2 * M >= n - idx)
            return suffix[idx];

        if (dp[idx][M] != -1)
            return dp[idx][M];

        int ans = 0;

        for (int x = 1; x <= 2 * M; x++) {
            ans = max(ans, suffix[idx] - solve(idx + x, max(M, x), piles));
        }

        return dp[idx][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();
        suffix.assign(n + 1, 0);

        for (int i = n - 1; i >= 0; i--)
            suffix[i] = suffix[i + 1] + piles[i];

        dp.assign(n + 1, vector<int>(n + 1, -1));

        return solve(0, 1, piles);
    }
};

int main() {
    Solution obj;

    vector<int> piles = {2, 7, 9, 4, 4};

    cout << obj.stoneGameII(piles) << endl;

    return 0;
}

/*

===========================
LeetCode 1140 - Stone Game II
===========================

----------------------------------
Problem Statement
----------------------------------

Alice and Bob play a game with an array piles where piles[i] represents the number
of stones in the ith pile.

Initially:

- Alice starts first.
- M = 1.

On each turn, the current player can take the first X remaining piles where

1 <= X <= 2*M

After taking X piles,

M = max(M, X)

The game continues until all piles are taken.

Both players play optimally.

Return the maximum stones Alice can obtain.

----------------------------------
Example
----------------------------------

Input:
piles = [2,7,9,4,4]

Output:
10

Explanation:

Optimal play gives Alice 10 stones.

===========================================================
Brute Force Approach
===========================================================

Idea
-----

Try every possible value of X (1 to 2*M).

Recursively compute the result assuming both players
play optimally.

Without memoization, many states repeat.

----------------------------------
Pseudo Code
----------------------------------

function solve(idx,M):

    if no piles left
        return 0

    ans=0

    for X=1 to min(2*M,remaining)

        taken=sum(idx...idx+X-1)

        opponent=solve(idx+X,max(M,X))

        ans=max(ans,totalRemaining-opponent)

return ans

----------------------------------
Complete Brute Force Code
----------------------------------

class Solution {
public:

    int solve(int idx,int M,vector<int>& piles){

        if(idx>=piles.size())
            return 0;

        int total=0;
        for(int i=idx;i<piles.size();i++)
            total+=piles[i];

        int ans=0;

        int take=0;

        for(int x=1;x<=2*M && idx+x<=piles.size();x++){

            take+=piles[idx+x-1];

            ans=max(ans,total-solve(idx+x,max(M,x),piles));
        }

        return ans;
    }

    int stoneGameII(vector<int>& piles) {

        return solve(0,1,piles);
    }
};

----------------------------------
Time Complexity
----------------------------------

Exponential

O(2^N)

----------------------------------
Space Complexity
----------------------------------

O(N)

(recursion stack)

===========================================================
Optimal Approach
===========================================================

Observation
------------

A state is completely determined by

(index, M)

Many recursive calls revisit the same state.

Use DP memoization.

Also,

suffix[i]

stores total stones from i to end.

Remaining stones are available in O(1).

----------------------------------
Intuition
----------------------------------

Suppose current player is at

(index,M)

Remaining stones = suffix[index]

If current player chooses X piles,

Opponent gets

solve(index+X,max(M,X))

So current player gets

Remaining - OpponentBest

Take maximum over every valid X.

----------------------------------
Pseudo Code
----------------------------------

Build suffix sum

solve(idx,M)

if all piles taken
    return 0

if 2*M >= remaining piles
    return suffix[idx]

if memo exists
    return memo

ans=0

for X=1 to 2*M

    ans=max(ans,
            suffix[idx]-
            solve(idx+X,max(M,X)))

store answer

return answer

----------------------------------
Complete Optimal Code
----------------------------------

class Solution {
public:

    int n;
    vector<vector<int>> dp;
    vector<int> suffix;

    int solve(int idx,int M,vector<int>& piles){

        if(idx>=n)
            return 0;

        if(2*M>=n-idx)
            return suffix[idx];

        if(dp[idx][M]!=-1)
            return dp[idx][M];

        int ans=0;

        for(int x=1;x<=2*M;x++){

            ans=max(ans,
                    suffix[idx]-
                    solve(idx+x,max(M,x),piles));
        }

        return dp[idx][M]=ans;
    }

    int stoneGameII(vector<int>& piles){

        n=piles.size();

        suffix.assign(n+1,0);

        for(int i=n-1;i>=0;i--)
            suffix[i]=suffix[i+1]+piles[i];

        dp.assign(n+1,vector<int>(n+1,-1));

        return solve(0,1,piles);
    }
};

----------------------------------
Time Complexity
----------------------------------

O(N^3)

N^2 states

Each state tries at most O(N) moves.

----------------------------------
Space Complexity
----------------------------------

O(N^2)

DP Table

+
O(N)

Recursion

===========================================================
Dry Run
===========================================================

Input

[2,7,9,4,4]

Suffix

[26,24,17,8,4]

Start

solve(0,1)

Choices

Take 1 pile

Alice gets

26 - solve(1,1)

Take 2 piles

Alice gets

26 - solve(2,2)

DP recursively evaluates every state only once.

Maximum answer becomes

10

===========================================================
Interview Notes
===========================================================

Pattern
--------

Game Theory

Minimax

DP on States

Memoization

Key Observation
---------------

Current player's score

=

Remaining Stones

-

Opponent's Best Score

Common Mistakes
---------------

1. Forgetting suffix sums.

2. Calculating remaining sum every recursion.

3. Incorrect M update.

4. Using prefix instead of suffix.

5. Missing base case

2*M >= remaining piles

When to use this approach
-------------------------

Whenever

- Two-player optimal game
- Alternate turns
- State depends on position and game parameters
- Opponent also plays optimally
- Minimax + DP

*/
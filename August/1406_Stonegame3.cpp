#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            int take = 0;
            dp[i] = INT_MIN;

            for (int k = 0; k < 3 && i + k < n; k++) {
                take += stoneValue[i + k];
                dp[i] = max(dp[i], take - dp[i + k + 1]);
            }
        }

        if (dp[0] > 0)
            return "Alice";
        if (dp[0] < 0)
            return "Bob";
        return "Tie";
    }
};

int main() {
    Solution obj;

    vector<int> stoneValue = {1, 2, 3, 7};

    cout << obj.stoneGameIII(stoneValue) << endl;

    return 0;
}

/*

==========================
LeetCode 1406. Stone Game III
==========================

-------------------
Problem Statement
-------------------
Alice and Bob play a game with a row of stones.

Each stone has an integer value (can be positive or negative).

Players play alternately, with Alice starting first.

On each turn, a player may take the first 1, 2, or 3 stones from the remaining row.

Each player's score is the sum of values of stones they picked.

Both players play optimally.

Return:
- "Alice" if Alice wins.
- "Bob" if Bob wins.
- "Tie" if both scores are equal.

----------------------------------------------------
Example
----------------------------------------------------

Input:
stoneValue = [1,2,3,7]

Output:
Bob

Explanation:

Alice cannot avoid Bob getting a better score.

====================================================
Brute Force Approach
====================================================

Idea
-----

Try every possible move (take 1,2,3 stones).

For every move recursively solve the remaining game.

Current player wants maximum score difference.

This causes huge overlapping subproblems.

------------------------------------
Pseudo Code
------------------------------------

function solve(i):
    if i==n
        return 0

    ans = -INF
    take = 0

    for k=1 to 3
        if possible
            take += value
            ans=max(ans,take-solve(next))

    return ans

------------------------------------
Complete Brute Force Code
------------------------------------

class Solution {
public:

    int solve(int i, vector<int>& a){

        if(i>=a.size())
            return 0;

        int ans=INT_MIN;
        int take=0;

        for(int k=0;k<3 && i+k<a.size();k++){

            take+=a[i+k];

            ans=max(ans,take-solve(i+k+1,a));
        }

        return ans;
    }

    string stoneGameIII(vector<int>& stoneValue) {

        int diff=solve(0,stoneValue);

        if(diff>0)
            return "Alice";
        if(diff<0)
            return "Bob";

        return "Tie";
    }
};

------------------------------------
Time Complexity
------------------------------------

O(3^N)

------------------------------------
Space Complexity
------------------------------------

O(N)

====================================================
Optimal Approach (DP)
====================================================

Observation
-----------

Instead of storing maximum score,

store

Maximum Score Difference
(Current Player - Opponent)

dp[i]

Meaning:

Starting from index i,
what is the best score difference current player can achieve?

Transition:

Take 1 stone

take - dp[next]

Take 2 stones

take - dp[next]

Take 3 stones

take - dp[next]

Choose maximum.

----------------------------------------------------
Intuition
----------------------------------------------------

Suppose current player gains

take

Then opponent starts from next position.

Opponent can achieve

dp[next]

So final advantage becomes

take - dp[next]

Choose the move giving maximum advantage.

----------------------------------------------------
Pseudo Code
----------------------------------------------------

dp[n]=0

for i=n-1 to 0

    ans=-INF
    take=0

    for next 3 stones

        take+=value

        ans=max(ans,take-dp[next])

    dp[i]=ans

if dp[0]>0
    Alice

else if dp[0]<0
    Bob

else
    Tie

----------------------------------------------------
Complete Optimal Code
----------------------------------------------------

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {

        int n=stoneValue.size();

        vector<int> dp(n+1,0);

        for(int i=n-1;i>=0;i--){

            int take=0;
            dp[i]=INT_MIN;

            for(int k=0;k<3 && i+k<n;k++){

                take+=stoneValue[i+k];

                dp[i]=max(dp[i],take-dp[i+k+1]);
            }
        }

        if(dp[0]>0)
            return "Alice";

        if(dp[0]<0)
            return "Bob";

        return "Tie";
    }
};

----------------------------------------------------
Time Complexity
----------------------------------------------------

O(N)

----------------------------------------------------
Space Complexity
----------------------------------------------------

O(N)

Can be optimized to O(1) since only next three states are needed.

====================================================
Dry Run
====================================================

Input

[1,2,3,7]

n=4

dp[4]=0

i=3

Take7

dp[3]=7

------------------

i=2

Take3

3-7=-4

Take3+7

10-0=10

dp[2]=10

------------------

i=1

Take2

2-10=-8

Take2+3

5-7=-2

Take2+3+7

12-0=12

dp[1]=12

------------------

i=0

Take1

1-12=-11

Take1+2

3-10=-7

Take1+2+3

6-7=-1

dp[0]=-1

Since dp[0]<0

Answer = Bob

====================================================
Interview Notes
====================================================

Pattern
-------

Game Theory + Dynamic Programming

or

Minimax DP

------------------------------------

Key Observation
---------------

Store score difference instead of storing Alice's score and Bob's score separately.

This simplifies transitions dramatically.

------------------------------------

Common Mistakes
---------------

1. Trying to maximize absolute score.

2. Forgetting to subtract opponent's optimal answer.

3. Wrong DP definition.

4. Missing negative values.

5. Using greedy.

------------------------------------

When to use this approach
-------------------------

Whenever

- Two-player game
- Both play optimally
- Alternate turns
- Pick limited moves
- Need winner or score difference

Typical keywords:

"Both players play optimally"

Usually indicates

Minimax DP / Score Difference DP.

*/
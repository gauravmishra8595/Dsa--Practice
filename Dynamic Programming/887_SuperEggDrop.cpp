#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int superEggDrop(int k, int n)
    {
        vector<long long> dp(k + 1, 0);
        int moves = 0;

        while (dp[k] < n)
        {
            moves++;
            for (int eggs = k; eggs >= 1; eggs--)
            {
                dp[eggs] = dp[eggs] + dp[eggs - 1] + 1;
            }
        }

        return moves;
    }
};

int main()
{
    Solution obj;

    int k = 2, n = 6;
    cout << obj.superEggDrop(k, n) << endl;

    return 0;
}

/*

===========================
Problem Statement
===========================

You are given k eggs and n floors.

There exists a critical floor f such that:
- Any egg dropped from a floor higher than f breaks.
- Any egg dropped from floor f or below does not break.

Return the minimum number of moves required in the worst case to determine the value of f.

==================================================
Example
==================================================

Input:
k = 2
n = 6

Output:
3

Explanation:
Move 1 -> Drop from floor 3
If breaks -> check floors 1-2
If survives -> check floors 4-6

Minimum worst-case moves = 3.

==================================================
Brute Force Approach
==================================================

Idea
----
For every state (eggs, floors), try dropping from every possible floor.

For each floor x:
1. Egg breaks -> solve(eggs-1, x-1)
2. Egg survives -> solve(eggs, floors-x)

Worst case:
max(break, survive)

Take minimum among all floors.

Pseudo Code
-----------

solve(e,f):
    if f<=1 return f
    if e==1 return f

    ans = INF

    for x=1 to f
        breakCase = solve(e-1,x-1)
        surviveCase = solve(e,f-x)

        ans=min(ans,1+max(breakCase,surviveCase))

    return ans

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:

    int solve(int eggs,int floors){

        if(floors<=1)
            return floors;

        if(eggs==1)
            return floors;

        int ans=INT_MAX;

        for(int x=1;x<=floors;x++){

            int broken=solve(eggs-1,x-1);
            int survive=solve(eggs,floors-x);

            ans=min(ans,1+max(broken,survive));
        }

        return ans;
    }

    int superEggDrop(int k,int n){
        return solve(k,n);
    }
};

Time Complexity
---------------
Exponential

Space Complexity
----------------
O(N)

==================================================
Optimal Approach
==================================================

Observation
-----------
Instead of asking:

"Minimum moves needed for N floors?"

Ask:

"With M moves and K eggs, how many floors can be tested?"

Let

dp[e] = maximum floors testable using current moves and e eggs.

Transition:

dp[e] = dp[e] + dp[e-1] + 1

Explanation:

If egg breaks:
    dp[e-1] floors below

If egg survives:
    dp[e] floors above

Current floor:
    +1

Hence,

dp[e] = below + above + current floor

Increase moves until

dp[k] >= n

Intuition
---------
Each move greatly increases the searchable floors.

Instead of binary searching floors, we count how much coverage every move provides.

This converts an O(KN²) DP into an O(K log N) style solution (moves are usually small).

Pseudo Code
-----------

dp[0...k]=0

moves=0

while dp[k]<n

    moves++

    for eggs=k down to 1

        dp[eggs]=dp[eggs]+dp[eggs-1]+1

return moves

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<long long> dp(k + 1, 0);
        int moves = 0;

        while (dp[k] < n) {
            moves++;
            for (int eggs = k; eggs >= 1; eggs--) {
                dp[eggs] = dp[eggs] + dp[eggs - 1] + 1;
            }
        }

        return moves;
    }
};

Time Complexity
---------------
O(K × Answer)

Typically Answer ≈ O(log N)

Space Complexity
----------------
O(K)

==================================================
Dry Run
==================================================

Example:

k=2
n=6

Initially

dp=[0,0,0]

Move 1

dp2=0+0+1=1
dp1=0+0+1=1

dp=[0,1,1]

Move 2

dp2=1+1+1=3
dp1=1+0+1=2

dp=[0,2,3]

Move 3

dp2=3+2+1=6
dp1=2+0+1=3

dp=[0,3,6]

Now dp[2]=6 >= n

Answer = 3

==================================================
Interview Notes
==================================================

Pattern
-------
DP with State Compression

Key Observation
---------------
Think in terms of:
"How many floors can be covered with M moves?"

instead of

"How many moves for N floors?"

This recurrence is the key interview insight.

Common Mistakes
---------------
1. Using floor-based DP O(KN²)
2. Forgetting to iterate eggs backwards
3. Using int when floors become large
4. Mixing moves DP with floor DP

When to use this approach
-------------------------
Whenever:
- Worst-case minimisation
- Binary decision (break / not break)
- Two outcomes after every action
- Need minimum trials
- Egg Dropping type DP

*/
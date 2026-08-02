#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};

int main() {
    Solution obj;

    vector<int> piles = {5, 3, 4, 5};

    cout << (obj.stoneGame(piles) ? "true" : "false") << endl;

    return 0;
}

/*

===========================
Problem Statement
===========================

Alice and Bob play a game with an even number of piles of stones.
Each pile has a positive integer number of stones.

Rules:
- Alice and Bob take turns.
- Alice starts first.
- On each turn, a player picks either the leftmost or rightmost pile.
- The picked pile is removed.
- The player with more total stones wins.

Return true if Alice wins assuming both play optimally.

Leetcode 877 - Stone Game

===========================
Example
===========================

Input:
piles = [5,3,4,5]

Output:
true

Explanation:
Alice can always secure more stones than Bob.

==========================================================
Brute Force Approach
==========================================================

Idea:
Explore every possible move.
At every turn choose either left pile or right pile.
Use recursion/minimax to compute the maximum score difference.

Pseudo Code:

solve(l,r):
    if l==r
        return piles[l]

    takeLeft = piles[l] - solve(l+1,r)
    takeRight = piles[r] - solve(l,r-1)

    return max(takeLeft,takeRight)

return solve(0,n-1) > 0

----------------------------------------------------------
Complete Brute Force Code
----------------------------------------------------------

class Solution {
public:

    int solve(int l,int r,vector<int>& piles){

        if(l==r)
            return piles[l];

        int left = piles[l] - solve(l+1,r,piles);
        int right = piles[r] - solve(l,r-1,piles);

        return max(left,right);
    }

    bool stoneGame(vector<int>& piles) {
        return solve(0,piles.size()-1,piles)>0;
    }
};

Time Complexity:
O(2^N)

Space Complexity:
O(N)

==========================================================
Optimal Approach
==========================================================

Observation:

Since:
1. Number of piles is even.
2. Total stones are odd.
3. Alice moves first.

Alice can decide before the game starts whether to collect
all piles at even indices or all piles at odd indices.

One of these two groups always has a strictly greater total.
On her first move Alice chooses accordingly and can always
force taking that parity throughout the game.

Hence Alice always wins.

Therefore answer is always true.

Intuition:

This is actually a mathematical game theory observation.

No DP or recursion is required.

Pseudo Code:

return true

----------------------------------------------------------
Complete Optimal Code
----------------------------------------------------------

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};

Time Complexity:
O(1)

Space Complexity:
O(1)

==========================================================
Dry Run
==========================================================

Input:

[5,3,4,5]

Even indexed piles:
5 + 4 = 9

Odd indexed piles:
3 + 5 = 8

Alice chooses the parity with larger total
(i.e. even indexed piles).

She can always force taking those piles.

Final:
Alice = 9
Bob = 8

Answer = true

==========================================================
Interview Notes
==========================================================

Pattern:
- Game Theory
- Mathematical Observation

Key Observation:
- Even number of piles.
- Alice moves first.
- Alice can commit to either even-indexed piles or odd-indexed piles.
- One parity always has a larger total.
- Therefore Alice always wins.

Common Mistakes:
- Implementing unnecessary DP.
- Forgetting that constraints guarantee even number of piles.
- Missing the parity strategy.

When to use this approach:
- Two-player optimal game.
- Picking from ends.
- Constraints guarantee parity-based strategy.
- Problem specifically asks Leetcode 877.

*/

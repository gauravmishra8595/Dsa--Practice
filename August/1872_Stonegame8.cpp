#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        vector<int> prefix(n);
        prefix[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        int dp = prefix[n - 1];

        for (int i = n - 2; i >= 1; i--) {
            dp = max(dp, prefix[i] - dp);
        }

        return dp;
    }
};

int main() {
    Solution sol;

    vector<int> stones = {-1, 2, -3, 4, -5};

    cout << sol.stoneGameVIII(stones) << '\n';

    return 0;
}

/*
================================================================================
                        LEETCODE 1872 - STONE GAME VIII
================================================================================

Problem Statement:
------------------
Alice and Bob play a game with an array of stones.

Initially, Alice starts with score 0 and Bob starts with score 0.

On each turn:
1. The player must take at least two stones from the left.
2. The taken stones are merged into one stone whose value is their sum.
3. The player adds the sum of the taken stones to their score.
4. The merged stone is placed back at the left.
5. The turn changes.

The game continues until only one stone remains.

Both players play optimally.

Return the difference between Alice's score and Bob's score.

LeetCode:
1872. Stone Game VIII


Example:
--------
Input:
stones = [-1, 2, -3, 4, -5]

Output:
5

Explanation:
Alice and Bob play optimally and the maximum possible score
difference is 5.


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
At every turn, a player can choose how many stones from the left to merge.

If there are n stones, the first player can choose:
2, 3, 4, ..., n stones.

We can recursively try every possible choice and calculate the
maximum score difference assuming both players play optimally.

The state can be represented by the current array of stones.

For each possible prefix that can be merged:
    current player's gain = sum of chosen prefix
    future advantage = result of the opponent's optimal play

Therefore:

    current_difference = gain - opponent_difference

Take the maximum over all possible choices.

This is exponential because the same states can be reached repeatedly.


Pseudo Code:
-----------
function solve(stones):
    if size(stones) == 1:
        return 0

    ans = -INF

    for i = 2 to size(stones):
        sum = sum of first i stones

        newStones = [sum] + remaining stones

        opponent = solve(newStones)

        ans = max(ans, sum - opponent)

    return ans


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int dfs(vector<int> stones) {
        if (stones.size() == 1)
            return 0;

        int ans = INT_MIN;
        int sum = 0;

        for (int i = 0; i < stones.size(); i++) {
            sum += stones[i];

            if (i + 1 < 2)
                continue;

            vector<int> next;
            next.push_back(sum);

            for (int j = i + 1; j < stones.size(); j++) {
                next.push_back(stones[j]);
            }

            int opponent = dfs(next);

            ans = max(ans, sum - opponent);
        }

        return ans;
    }

    int stoneGameVIII(vector<int>& stones) {
        return dfs(stones);
    }
};


Time Complexity:
----------------
Exponential, approximately O(2^N) or worse depending on state
representation and repeated vector construction.

Space Complexity:
-----------------
O(N) recursion depth, excluding the copied vectors.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
The important observation is that after merging a prefix of stones,
the exact individual stones inside that prefix no longer matter.

Only their total sum matters.

Define:

    prefix[i] = stones[0] + stones[1] + ... + stones[i]

If a player chooses to merge the first i+1 stones, their score
increases by:

    prefix[i]

After that operation, the remaining game can be viewed as another
game whose optimal score difference is known.

Therefore, we can formulate the transition as:

    current_answer = prefix[i] - previous_answer


Intuition:
----------
Instead of simulating the changing array, consider only the point
where the first merge ends.

Suppose the opponent can achieve a score difference of dp in the
remaining game.

If the current player takes a prefix having sum prefix[i], then:

    current advantage = prefix[i] - dp

because the opponent's advantage is subtracted.

We process possible prefix lengths from right to left.

For the complete remaining array, the first player can take all
stones, so the initial answer is:

    dp = prefix[n - 1]

Then consider shorter valid prefixes:

    dp = max(dp, prefix[i] - dp)

The first valid prefix has length 2, so i starts from 1.


Pseudo Code:
-----------
prefix = prefix sums of stones

dp = prefix[n - 1]

for i = n - 2 down to 1:
    dp = max(dp, prefix[i] - dp)

return dp


Complete Optimal Code:
----------------------

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();

        vector<int> prefix(n);
        prefix[0] = stones[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + stones[i];
        }

        int dp = prefix[n - 1];

        for (int i = n - 2; i >= 1; i--) {
            dp = max(dp, prefix[i] - dp);
        }

        return dp;
    }
};


Time Complexity:
----------------
O(N)

Building prefix sums: O(N)
DP traversal:         O(N)

Total: O(N)


Space Complexity:
-----------------
O(N) for the prefix sum array.

Can be reduced to O(1) extra space if prefix sums are stored
directly inside the input array.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

stones:
[-1, 2, -3, 4, -5]

Prefix sums:

index:     0   1   2   3   4
prefix:   -1   1  -2   2  -3

Initial:
dp = prefix[4]
   = -3


i = 3:
prefix[3] = 2

dp = max(dp, prefix[3] - dp)
   = max(-3, 2 - (-3))
   = max(-3, 5)
   = 5


i = 2:
prefix[2] = -2

dp = max(5, -2 - 5)
   = max(5, -7)
   = 5


i = 1:
prefix[1] = 1

dp = max(5, 1 - 5)
   = max(5, -4)
   = 5


Answer = 5


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Game DP / Minimax DP + Prefix Sum + Score Difference DP


Key Observation:
----------------
After merging a prefix, only the SUM of that prefix matters.

So instead of tracking the complete array state, we only need
prefix sums and the optimal score difference.

The core transition is:

    dp = max(dp, prefix[i] - dp)


Common Mistakes:
----------------
1. Forgetting that at least TWO stones must be merged.

2. Starting the loop from i = 0.
   prefix[0] represents only one stone, which is not a valid move.

3. Using:
       dp = min(...)
   instead of max.

4. Forgetting the score-difference perspective.
   The opponent's optimal difference must be SUBTRACTED:

       current = prefix[i] - opponent

5. Simulating the entire array after every merge.
   This leads to unnecessary exponential complexity.

6. Using int without checking constraints.
   For LeetCode 1872, int is sufficient under the given constraints.


When to Use This Approach:
--------------------------
Use this approach when:

- It is a two-player optimal game.
- Both players maximize their own advantage.
- The result can be represented as a score difference.
- A move reduces the problem to another similar game.
- A prefix/suffix operation can be summarized using prefix sums.
- The exact internal state of a merged prefix is irrelevant.

General Game-DP Template:

    current_score_difference
        =
    current_move_gain
        -
    opponent_best_difference

Then maximize the current player's difference.

Final Pattern:

    prefix sums
        +
    score-difference minimax
        +
    bottom-up DP

Time:  O(N)
Space: O(N)

================================================================================
*/

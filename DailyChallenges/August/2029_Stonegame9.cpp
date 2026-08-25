#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones)
            cnt[x % 3]++;

        if (cnt[0] % 2 == 0)
            return cnt[1] > 0 && cnt[2] > 0;

        return abs(cnt[1] - cnt[2]) > 2;
    }
};

int main() {
    Solution sol;

    vector<int> a = {2, 1};
    vector<int> b = {2};
    vector<int> c = {5, 1, 2, 4, 3};

    cout << boolalpha;
    cout << sol.stoneGameIX(a) << '\n'; // true
    cout << sol.stoneGameIX(b) << '\n'; // false
    cout << sol.stoneGameIX(c) << '\n'; // false

    return 0;
}

/*
================================================================================
                           LEETCODE 2029
                         STONE GAME IX
================================================================================

Problem Statement:
------------------
Alice and Bob take turns removing stones from a pile.

There are n stones in the pile. The i-th stone has a value stones[i].

On each turn, a player removes exactly one stone from the pile.

The game follows these rules:
1. The sum of the values of all removed stones is maintained.
2. If the sum becomes divisible by 3 after a player's move, that player loses.
3. If all stones are removed without anyone losing, the player who cannot
   make a move loses.

Alice moves first.

Return true if Alice can win assuming both players play optimally.

Constraints:
- 1 <= stones.length <= 10^5
- 1 <= stones[i] <= 10^9


Example:
--------
Input:
stones = [2, 1]

Output:
true

Explanation:
Alice removes 1.
Current sum = 1.

Bob must remove 2.
Current sum = 3, which is divisible by 3.

Therefore Bob loses and Alice wins.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Try every possible stone that the current player can remove.

At every state:
- Add the selected stone to the current sum.
- If the new sum is divisible by 3, the current player loses.
- Otherwise, recursively let the opponent play.
- The current player wins if there exists at least one move that makes the
  opponent lose.

This directly simulates the game.

Pseudo Code:
------------
solve(stones, mask, sum, aliceTurn):

    for every unused stone i:
        newSum = sum + stones[i]

        if newSum % 3 == 0:
            current player loses
            continue

        if opponent loses after this move:
            current player wins

    current player loses


Complete Brute Force Code:
--------------------------
/*
class BruteForceSolution {
public:
    bool dfs(vector<int>& stones, int mask, int sum) {
        int n = stones.size();

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                continue;

            int newSum = sum + stones[i];

            // Current player immediately loses.
            if (newSum % 3 == 0)
                continue;

            // If opponent loses, current player wins.
            if (!dfs(stones, mask | (1 << i), newSum))
                return true;
        }

        return false;
    }

    bool stoneGameIX(vector<int>& stones) {
        return dfs(stones, 0, 0);
    }
};
*/

// Time Complexity:
// ----------------
// O(N * 2^N)

// Space Complexity:
// -----------------
// O(2^N)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// Only the remainder of each stone modulo 3 matters.

// Every stone belongs to one of three groups:

//     remainder 0 -> cnt[0]
//     remainder 1 -> cnt[1]
//     remainder 2 -> cnt[2]

// The running sum also only matters modulo 3.

// Important properties:

// 1. Removing a remainder-0 stone does not change the current sum modulo 3.
// 2. Two consecutive remainder-0 stones essentially give the same player
//    another turn.
// 3. Therefore, the parity of cnt[0] determines how the game behaves.
// 4. Stones with remainder 1 and 2 are opposites:
//        1 + 2 = 0 (mod 3)

// The game can therefore be reduced to the counts of the three remainders.


// Intuition:
// ---------
// Case 1: cnt[0] is EVEN
// ----------------------
// The zero-remainder stones can effectively be paired.

// Alice can win only if both remainder-1 and remainder-2 stones exist.

// Therefore:

//     cnt[0] % 2 == 0
//     => Alice wins iff cnt[1] > 0 AND cnt[2] > 0


// Case 2: cnt[0] is ODD
// ---------------------
// Now the zero-remainder stones change the effective turn structure.

// Alice wins only when one of the two non-zero remainder groups is sufficiently
// larger than the other.

// The required condition is:

//     abs(cnt[1] - cnt[2]) > 2


// Therefore the complete condition is:

//     if cnt[0] is even:
//         return cnt[1] > 0 && cnt[2] > 0

//     otherwise:
//         return abs(cnt[1] - cnt[2]) > 2


// Pseudo Code:
// ------------
// count the number of stones with each remainder modulo 3

// if cnt[0] is even:
//     return cnt[1] > 0 AND cnt[2] > 0

// return abs(cnt[1] - cnt[2]) > 2


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones)
            cnt[x % 3]++;

        if (cnt[0] % 2 == 0)
            return cnt[1] > 0 && cnt[2] > 0;

        return abs(cnt[1] - cnt[2]) > 2;
    }
};
*/

// Time Complexity:
// ----------------
// O(N)

// We only scan the array once.


// Space Complexity:
// -----------------
// O(1)

// Only three counters are required.


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// Example:
//     stones = [2, 1]

// Step 1:
//     2 % 3 = 2
//     1 % 3 = 1

// Therefore:

//     cnt[0] = 0
//     cnt[1] = 1
//     cnt[2] = 1

// Step 2:
//     cnt[0] = 0, which is even.

// So use:

//     cnt[1] > 0 && cnt[2] > 0

// Both are true.

// Therefore:

//     Answer = true


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Game Theory + Modular Arithmetic + Counting


// Key Observation:
// ----------------
// Only values modulo 3 matter.

// Instead of tracking every possible game state, count how many numbers have
// remainder 0, 1, and 2.


// Common Mistakes:
// ----------------
// 1. Simulating every possible sequence of moves.
// 2. Using the actual stone values instead of their remainders.
// 3. Forgetting that remainder-0 stones affect turn parity.
// 4. Using:
//        cnt[1] != cnt[2]
//    instead of the required conditions.
// 5. Confusing the condition for even and odd cnt[0].
// 6. Forgetting that a move making the sum divisible by 3 immediately loses.


// When to use this approach:
// --------------------------
// Use this technique when:
// - The game condition depends only on a value modulo k.
// - The order of individual values does not matter.
// - The input is too large for state-space simulation.
// - You can group elements by their remainder classes.
// - Turn-based game behavior can be reduced to counts and parity.


// Final Formula:
// --------------
// if cnt[0] % 2 == 0:
//     Alice wins iff cnt[1] > 0 && cnt[2] > 0

// else:
//     Alice wins iff abs(cnt[1] - cnt[2]) > 2


// Complexity:
// -----------
// Time  : O(N)
// Space : O(1)

// ================================================================================
// */

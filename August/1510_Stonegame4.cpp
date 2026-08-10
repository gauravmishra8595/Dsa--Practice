#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: DP
class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;

    int n;
    cin >> n;

    cout << boolalpha << sol.winnerSquareGame(n) << '\n';

    return 0;
}

/*
===============================================================================
                         LEETCODE 1510
                    Winner Square Game
===============================================================================

Problem Statement
-----------------
Alice and Bob play a game with a number n.

Alice starts with n stones.

On each turn, a player must remove a non-zero perfect square number of stones
from the pile.

For example, a player can remove 1, 4, 9, 16, ...

The player who cannot make a move loses.

Return true if Alice wins assuming both players play optimally.

Example
-------
Input:
n = 7

Output:
false

Explanation:
Alice can remove 1 or 4.

If Alice removes 1:
    7 -> 6
Bob can remove 1:
    6 -> 5
Alice can remove 1:
    5 -> 4
Bob removes 4:
    4 -> 0

So Alice loses with optimal play.

===============================================================================
Brute Force Approach
===============================================================================

Idea
----
Try every possible perfect square at every state using recursion.

For a given n:
- Try removing 1^2, 2^2, 3^2, ...
- If any move makes the opponent lose, current player wins.
- Otherwise, current player loses.

This directly follows the game definition, but the same states are calculated
many times.

Pseudo Code
-----------
win(n):
    if n == 0:
        return false

    for every square s <= n:
        if win(n - s) == false:
            return true

    return false

winnerSquareGame(n):
    return win(n)

Complete Brute Force Code
--------------------------

// #include <bits/stdc++.h>
// using namespace std;
//
// class Solution {
// public:
//     bool win(int n) {
//         if (n == 0)
//             return false;
//
//         for (int i = 1; i * i <= n; i++) {
//             if (!win(n - i * i)) {
//                 return true;
//             }
//         }
//
//         return false;
//     }
//
//     bool winnerSquareGame(int n) {
//         return win(n);
//     }
// };
//
// int main() {
//     Solution sol;
//
//     int n;
//     cin >> n;
//
//     cout << boolalpha << sol.winnerSquareGame(n) << '\n';
//
//     return 0;
// }

Time Complexity
---------------
Exponential in n.

Space Complexity
-----------------
O(n) recursion stack in the worst case.


===============================================================================
Optimal Approach
===============================================================================

Observation
-----------
Define:

    dp[i] = true  -> current player can win with i stones.
    dp[i] = false -> current player loses with i stones.

For every i, we can remove any perfect square j*j <= i.

If after making a move we reach a losing state for the opponent:

    dp[i - j*j] == false

then the current state is winning:

    dp[i] = true

Therefore:

    dp[i] = true if there exists a square j*j <= i
            such that dp[i - j*j] == false.

Base Case:

    dp[0] = false

Because when there are 0 stones, no move is possible, so the player loses.

Intuition
---------
This is a classic "winning state / losing state" game DP.

Instead of exploring the same game states repeatedly, calculate each state once.

For every number i:
- Check all perfect squares <= i.
- If even one move takes us to a losing state, i is winning.
- If no such move exists, i is losing.

Pseudo Code
-----------
dp[0] = false

for i = 1 to n:
    dp[i] = false

    for j = 1 while j*j <= i:
        if dp[i - j*j] == false:
            dp[i] = true
            break

return dp[n]

Complete Optimal Code
---------------------

// #include <bits/stdc++.h>
// using namespace std;
//
// class Solution {
// public:
//     bool winnerSquareGame(int n) {
//         vector<bool> dp(n + 1, false);
//
//         for (int i = 1; i <= n; i++) {
//             for (int j = 1; j * j <= i; j++) {
//                 if (!dp[i - j * j]) {
//                     dp[i] = true;
//                     break;
//                 }
//             }
//         }
//
//         return dp[n];
//     }
// };
//
// int main() {
//     Solution sol;
//
//     int n;
//     cin >> n;
//
//     cout << boolalpha << sol.winnerSquareGame(n) << '\n';
//
//     return 0;
// }

Time Complexity
---------------
For every i from 1 to n, we check at most sqrt(i) perfect squares.

Total:

    O(n * sqrt(n))

Space Complexity
----------------
    O(n)

===============================================================================
Dry Run with Example
===============================================================================

Example:
n = 7

Start:

dp[0] = false

i = 1:
Squares <= 1: 1

1 - 1 = 0
dp[0] = false

Therefore:
dp[1] = true

--------------------------------

i = 2:
Square: 1

2 - 1 = 1
dp[1] = true

No move reaches a losing state.

Therefore:
dp[2] = false

--------------------------------

i = 3:
Square: 1

3 - 1 = 2
dp[2] = false

Therefore:
dp[3] = true

--------------------------------

i = 4:
Squares: 1, 4

Try 1:
4 - 1 = 3
dp[3] = true

Try 4:
4 - 4 = 0
dp[0] = false

Therefore:
dp[4] = true

--------------------------------

i = 5:
Squares: 1, 4

Try 1:
5 - 1 = 4
dp[4] = true

Try 4:
5 - 4 = 1
dp[1] = true

No losing state is reachable.

Therefore:
dp[5] = false

--------------------------------

i = 6:
Squares: 1, 4

Try 1:
6 - 1 = 5
dp[5] = false

Therefore:
dp[6] = true

--------------------------------

i = 7:
Squares: 1, 4

Try 1:
7 - 1 = 6
dp[6] = true

Try 4:
7 - 4 = 3
dp[3] = true

No losing state is reachable.

Therefore:
dp[7] = false

Final:

dp = [F, T, F, T, T, F, T, F]

Answer:

false

===============================================================================
Interview Notes
===============================================================================

Pattern
-------
Game Theory + Dynamic Programming

Key Observation
---------------
A state is winning if there exists at least one move that takes the opponent
to a losing state.

In short:

    WIN = exists a move to LOSE
    LOSE = every move goes to WIN

Common Mistakes
---------------
1. Forgetting that dp[0] is false.
2. Checking only one perfect square instead of all possible squares.
3. Using recursion without memoization, causing exponential complexity.
4. Marking a state as winning simply because a move is possible.
5. Confusing the current player's state with the opponent's state.

When to use this approach
-------------------------
Use this approach for turn-based games where:
- Players have the same set of moves.
- A state can be represented compactly.
- The goal is to determine whether the current player can force a win.
- A move transitions from one state to another smaller state.

Typical recurrence:

    dp[state] = true
    if there exists a move such that
    dp[nextState] == false

This "winning state / losing state" DP pattern is very common in
competitive programming game problems.

===============================================================================
*/
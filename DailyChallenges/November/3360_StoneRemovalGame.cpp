#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canAliceWin(int n) {
        int take = 10;
        int steps = 0;
        while (n >= take) {
            n -= take;
            take--;

            steps++;
        }

        return steps % 2 != 0;
    }
};

int main() {
    Solution sol;

    int n = 12;

    cout << (sol.canAliceWin(n) ? "Alice Wins" : "Bob Wins") << endl;

    return 0;
}

/*
============================================================
                 LEETCODE 3360
              STONE REMOVAL GAME
============================================================

1. PROBLEM STATEMENT
--------------------
Alice and Bob play a game with n stones.

Rules:
1. Alice starts by removing 10 stones.
2. Bob removes 9 stones.
3. Alice removes 8 stones.
4. Bob removes 7 stones.
5. This continues, decreasing the number of
   stones removed by 1 after every turn.

A player who cannot remove the required number
of stones loses.

Return true if Alice wins, otherwise false.

------------------------------------------------------------
2. EXAMPLE
------------------------------------------------------------

Input: n = 12

Output: true

Explanation:

Initial stones = 12

Alice removes 10 stones.
Remaining = 12 - 10 = 2

Bob needs to remove 9 stones.
But only 2 stones remain.

Bob cannot make a move.

Therefore, Alice wins.

------------------------------------------------------------
3. BRUTE FORCE APPROACH
------------------------------------------------------------

IDEA:
----
Simulate the game turn by turn.

Maintain:
- take: Number of stones to remove.
- aliceTurn: Tracks whose turn it is.

If the current player cannot remove the
required stones, that player loses.

PSEUDO CODE:
------------
1. Initialize take = 10.
2. Initialize aliceTurn = true.
3. While n >= take:
      n = n - take
      take = take - 1
      aliceTurn = !aliceTurn
4. Return !aliceTurn.

COMPLETE BRUTE FORCE CODE:
--------------------------

bool canAliceWin(int n) {
    int take = 10;
    bool aliceTurn = true;

    while (n >= take) {
        n -= take;
        take--;

        aliceTurn = !aliceTurn;
    }

    return !aliceTurn;
}

TIME COMPLEXITY:
----------------
O(1)

At most 10 iterations are performed.

SPACE COMPLEXITY:
-----------------
O(1)

Only constant extra variables are used.

------------------------------------------------------------
4. OPTIMAL APPROACH
------------------------------------------------------------

OBSERVATION:
------------
The number of stones removed decreases by 1
after every successful move.

The removal sequence is:

10, 9, 8, 7, 6, 5, 4, 3, 2, 1

INTUITION:
----------
We can directly simulate the game and count
the number of successful moves.

Since Alice starts first:

- Odd number of successful moves:
  Alice makes the last successful move.
  Bob cannot move.
  Alice wins.

- Even number of successful moves:
  Bob makes the last successful move.
  Alice cannot move.
  Bob wins.

Therefore, Alice wins if steps is odd.

PSEUDO CODE:
------------
1. Initialize take = 10.
2. Initialize steps = 0.
3. While n >= take:
      n = n - take
      take = take - 1
      steps++
4. If steps is odd:
      Return true.
5. Otherwise:
      Return false.

COMPLETE OPTIMAL CODE:
----------------------

bool canAliceWin(int n) {
    int take = 10;
    int steps = 0;

    while (n >= take) {
        n -= take;
        take--;
        steps++;
    }

    return steps % 2 != 0;
}

TIME COMPLEXITY:
----------------
O(1)

Maximum 10 iterations because take starts
at 10 and decreases after every move.

SPACE COMPLEXITY:
-----------------
O(1)

Only two integer variables are used.

------------------------------------------------------------
5. DRY RUN WITH EXAMPLE
------------------------------------------------------------

Input: n = 25

Initial:
n = 25
take = 10
steps = 0

ITERATION 1:
------------
25 >= 10

n = 25 - 10 = 15
take = 9
steps = 1

Alice plays.

ITERATION 2:
------------
15 >= 9

n = 15 - 9 = 6
take = 8
steps = 2

Bob plays.

ITERATION 3:
------------
6 < 8

Loop terminates.

Final:
------
steps = 2

steps % 2 == 0

Output: false

Bob wins because Alice cannot make the
next move.

------------------------------------------------------------
6. INTERVIEW NOTES
------------------------------------------------------------

PATTERN:
--------
Simulation / Turn-Based Game

KEY OBSERVATION:
----------------
The number of stones removed decreases by
one after every successful move.

Count successful moves to determine the
winner using parity (odd/even).

COMMON MISTAKES:
----------------
1. Forgetting to decrease take after every move.
2. Incorrectly counting unsuccessful moves.
3. Returning true for even steps instead of odd.
4. Using unnecessary recursion or extra data structures.

WHEN TO USE THIS APPROACH:
--------------------------
1. Turn-based games with deterministic moves.
2. Games where each move follows a fixed sequence.
3. Problems where the winner depends on move parity.
4. Small bounded simulations.

============================================================
                 END OF NOTES
============================================================
*/
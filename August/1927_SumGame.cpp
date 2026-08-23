#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sumGame(string num) {
        int n = num.length();

        int sum = 0;
        int cnt1 = 0;
        int cnt2 = 0;

        for (int i = 0; i < n; i++) {
            if (i < n / 2) {
                if (num[i] == '?')
                    cnt1++;
                else
                    sum += num[i] - '0';
            } 
            else {
                if (num[i] == '?')
                    cnt2++;
                else
                    sum -= num[i] - '0';
            }
        }

        // Odd number of '?' -> Alice wins
        if ((cnt1 + cnt2) % 2 == 1)
            return true;

        int ans = sum + (cnt1 / 2) * 9 - (cnt2 / 2) * 9;

        return ans != 0;
    }
};

int main() {
    Solution sol;

    cout << boolalpha;

    cout << sol.sumGame("5023") << '\n';        // false
    cout << sol.sumGame("25??") << '\n';        // true
    cout << sol.sumGame("?3295???") << '\n';    // false
    cout << sol.sumGame("?6?6?000?3") << '\n';  // true

    return 0;
}

/*
================================================================================
                         LEETCODE 1927 - SUM GAME
================================================================================

Problem Statement:
------------------
Alice and Bob take turns replacing '?' with digits from 0 to 9.

Alice moves first.

The string has even length and is divided into two equal halves.

After all '?' are replaced:

    Equal sums  -> Bob wins
    Unequal sums -> Alice wins

Return true if Alice wins.


Example:
--------
num = "25??"

Left half:
    25 -> sum = 7

Right half:
    ?? -> unknown

Alice can put 9 in the right half.

The remaining '?' can contribute at most 9, so Bob cannot make
the two sums equal.

Therefore:

    true


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Try every possible digit from 0 to 9 for every '?'.

Because this is a game, we need Minimax:

    Alice:
        needs at least one move that makes her win.

    Bob:
        needs at least one move that makes Alice lose.

Pseudo Code:
-----------
solve(state, turn):

    if no '?' remains:
        return leftSum != rightSum

    if Alice's turn:
        try every digit
        if any move lets Alice win:
            return true
        return false

    if Bob's turn:
        try every digit
        if any move makes Alice lose:
            return false
        return true


Complete Brute Force Code:
--------------------------

class BruteForceSolution {
public:
    bool dfs(string &num, int pos, bool aliceTurn) {

        while (pos < num.size() && num[pos] != '?')
            pos++;

        if (pos == num.size()) {
            int n = num.size();

            int leftSum = 0;
            int rightSum = 0;

            for (int i = 0; i < n / 2; i++)
                leftSum += num[i] - '0';

            for (int i = n / 2; i < n; i++)
                rightSum += num[i] - '0';

            return leftSum != rightSum;
        }

        if (aliceTurn) {
            for (char digit = '0'; digit <= '9'; digit++) {
                num[pos] = digit;

                if (dfs(num, pos + 1, false)) {
                    num[pos] = '?';
                    return true;
                }
            }

            num[pos] = '?';
            return false;
        }

        for (char digit = '0'; digit <= '9'; digit++) {
            num[pos] = digit;

            if (!dfs(num, pos + 1, true)) {
                num[pos] = '?';
                return false;
            }
        }

        num[pos] = '?';
        return true;
    }

    bool sumGame(string num) {
        return dfs(num, 0, true);
    }
};

Time Complexity:
----------------
O(10^q)

where q = number of '?'.

Space Complexity:
-----------------
O(q)


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
Instead of separately calculating the left and right sums, maintain one
variable:

    sum = leftSum - rightSum

For every known digit:

    Left half  -> add digit
    Right half -> subtract digit


Also count:

    cnt1 = '?' in left half
    cnt2 = '?' in right half


Now consider the number of '?'.

If:

    cnt1 + cnt2

is odd, Alice gets the last move.

Therefore Alice can always force the final sums to be different.

So:

    if ((cnt1 + cnt2) % 2 == 1)
        return true;


When the number of '?' is even:
--------------------------------
Alice and Bob make the same number of moves.

The balancing effect of the '?' characters can be represented by:

    (cnt1 / 2) * 9

from the left side and

    (cnt2 / 2) * 9

from the right side.

Therefore:

    ans = sum
          + (cnt1 / 2) * 9
          - (cnt2 / 2) * 9


If:

    ans == 0

Bob can force the sums to become equal.

Otherwise:

    Alice wins.


Key Formula:
------------

    ans = sum + (cnt1 / 2) * 9 - (cnt2 / 2) * 9

Answer:

    ans != 0


Intuition:
---------
We treat the left side as positive and the right side as negative.

For example:

    num = "25??"

Initial:

    sum = 2 + 5 = 7

    cnt1 = 0
    cnt2 = 2

Total '?' is even.

Therefore:

    ans = 7 + 0 * 9 - 1 * 9
        = -2

Since:

    ans != 0

Alice wins.


Dry Run:
--------
num = "?6?6?000?3"

Left:
    ?6?6?

Known sum:

    6 + 6 = 12

cnt1:

    3

Right:
    000?3

Known sum:

    0 + 0 + 0 + 3 = 3

Since right side is negative:

    sum = 12 - 3
         = 9

cnt2:

    1


Total '?':

    cnt1 + cnt2
    = 3 + 1
    = 4

Even, so continue.


Calculate:

    ans = sum + (cnt1 / 2) * 9 - (cnt2 / 2) * 9

        = 9 + (3 / 2) * 9 - (1 / 2) * 9

        = 9 + 1 * 9 - 0 * 9

        = 18


Therefore:

    ans != 0

Alice wins.

Answer:

    true


Complete Optimal Code:
----------------------

class Solution {
public:
    bool sumGame(string num) {
        int n = num.length();

        int sum = 0;
        int cnt1 = 0;
        int cnt2 = 0;

        for (int i = 0; i < n; i++) {

            if (i < n / 2) {

                if (num[i] == '?')
                    cnt1++;
                else
                    sum += num[i] - '0';

            } else {

                if (num[i] == '?')
                    cnt2++;
                else
                    sum -= num[i] - '0';
            }
        }

        if ((cnt1 + cnt2) % 2 == 1)
            return true;

        int ans = sum
                + (cnt1 / 2) * 9
                - (cnt2 / 2) * 9;

        return ans != 0;
    }
};


Time Complexity:
----------------
O(n)

We scan the string once.

Space Complexity:
-----------------
O(1)


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Game Theory + Mathematical Observation


Key Observation:
----------------
Convert the problem into one difference:

    sum = leftSum - rightSum


Then:

    '?' in left  -> cnt1
    '?' in right -> cnt2


If total '?' is odd:

    Alice wins.


Otherwise:

    ans = sum + (cnt1 / 2) * 9 - (cnt2 / 2) * 9

    ans == 0 -> Bob wins
    ans != 0 -> Alice wins


Common Mistakes:
----------------
1. Using brute force.

   There can be up to 10^5 characters, so brute force is impossible.

2. Forgetting that Alice moves first.

3. Forgetting the odd number of '?' case.

4. Using abs() incorrectly.

   The direction of the difference matters.

5. Mixing up left and right signs.

   Left digit:
       sum += digit

   Right digit:
       sum -= digit


When to Use This Approach:
--------------------------
Use this approach when:

    - Two players alternately make choices.
    - The final condition is based on equality.
    - Each move changes a numerical difference.
    - There are too many possible game states for brute force.
    - The game has a mathematical invariant.

The main trick here is:

    Don't simulate the game.

    Track only the difference between the two halves
    and the number of '?' on each side.

================================================================================
*/
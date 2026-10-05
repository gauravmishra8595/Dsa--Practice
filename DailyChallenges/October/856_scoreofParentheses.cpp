#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        int depth = 0;

        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;

                // "()" at current depth contributes 2^depth
                if (s[i - 1] == '(') {
                    score += (1 << depth);
                }
            }
        }

        return score;
    }
};

int main() {
    Solution sol;

    string s;
    cin >> s;

    cout << sol.scoreOfParentheses(s) << '\n';

    return 0;
}

/*
================================================================================
                    SCORE OF PARENTHESES
================================================================================

Problem Statement:
------------------
Given a balanced parentheses string s, calculate its score using these rules:

1. "()" has score 1.
2. AB has score score(A) + score(B), where A and B are balanced strings.
3. (A) has score 2 * score(A).

Return the total score of the given balanced parentheses string.

Example:
--------
Input:
(()(()))

Output:
6

Explanation:
()       = 1
(()())   = 2 * (1 + 1) = 4
Therefore:
(()(())) = 2 + 4 = 6

================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Repeatedly find the innermost "()" and replace it with its score "1".

For a pair like:
    (A)

first calculate the score of A and then multiply it by 2.

This can be implemented recursively by finding matching parentheses and
calculating the score of every nested section.

Pseudo Code:
------------
function solve(s, l, r):
    score = 0
    i = l

    while i < r:
        if s[i] == '(':
            find matching ')' for this '('

            if the pair is "()":
                score += 1
            else:
                inside = solve(s, i + 1, matching - 1)
                score += 2 * inside

            i = matching + 1
        else:
            i++

    return score

Complete Brute Force Code:
---------------------------

class Solution {
public:
    int solve(string &s, int l, int r) {
        int score = 0;
        int i = l;

        while (i <= r) {
            if (s[i] == '(') {
                int balance = 1;
                int j = i + 1;

                while (j <= r && balance > 0) {
                    if (s[j] == '(')
                        balance++;
                    else
                        balance--;

                    j++;
                }

                int close = j - 1;

                if (i + 1 == close) {
                    score += 1;
                } else {
                    score += 2 * solve(s, i + 1, close - 1);
                }

                i = close + 1;
            } else {
                i++;
            }
        }

        return score;
    }

    int scoreOfParentheses(string s) {
        return solve(s, 0, (int)s.size() - 1);
    }
};

Time Complexity:
----------------
O(N^2) in the worst case because matching parentheses may require repeated
scanning of the string.

Space Complexity:
-----------------
O(N) due to recursive call stack in the worst case.

================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
A primitive "()" contributes 1.

If "()" occurs one level deeper:

    ()
    (())

The inner "()" has score 1, and the outer parentheses double it:

    (()) = 2

Therefore, a "()" pair occurring at depth d contributes:

    2^(d - 1)

We only need to know the current nesting depth.

Intuition:
----------
Whenever we see '(':
    increase depth.

Whenever we see ')':
    decrease depth.

If the current ')' closes an immediate "()", then the pair contributes:

    2^depth

because depth has already been decreased.

For example:

    (()())

At the inner "()" pair:
    depth becomes 1 after ')'
    contribution = 2^1 = 2

At the next "()" pair:
    depth becomes 1
    contribution = 2

Total = 4.

Pseudo Code:
------------
score = 0
depth = 0

for every character:
    if character == '(':
        depth++

    else:
        depth--

        if previous character == '(':
            score += 2^depth

return score

Complete Optimal Code:
----------------------

class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        int depth = 0;

        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;

                if (s[i - 1] == '(') {
                    score += (1 << depth);
                }
            }
        }

        return score;
    }
};

Time Complexity:
----------------
O(N)

Each character is processed exactly once.

Space Complexity:
-----------------
O(1)

Only score and depth variables are used.

================================================================================
DRY RUN
================================================================================

Example:
    s = "(()(()))"

Initial:
    score = 0
    depth = 0

Character   Action                    depth    score
----------------------------------------------------
'('         depth++                     1       0
'('         depth++                     2       0
')'         depth--                     1       2
'('         depth++                     2       2
'('         depth++                     3       2
')'         depth--                     2       4
')'         depth--                     1       6
')'         depth--                     0       6

Final Answer:
    6

Why?
----
The first "()" is at depth 1:
    contribution = 2^1 = 2

The second inner "()" is at depth 2:
    contribution = 2^2 = 4

Total:
    2 + 4 = 6

================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Parentheses / Stack / Nesting Depth

Key Observation:
----------------
Only an immediate "()" creates a new base score.

If "()" is found at depth d after closing the pair, its contribution is:

    2^d

So we don't need an explicit stack.

Common Mistakes:
----------------
1. Forgetting that "(A)" doubles the score of A.
2. Using the wrong depth while calculating 2^depth.
3. Confusing concatenation with nesting:
       AB       -> score(A) + score(B)
       (A)      -> 2 * score(A)
4. Using floating-point pow() unnecessarily.
5. Forgetting that after encountering ')', depth must be decreased first.
6. Using O(N) stack space when O(1) space is possible.

When to use this approach:
--------------------------
Use this depth-based approach when:

- The input is guaranteed to be balanced.
- The score depends on nesting depth.
- A base pattern contributes a known value.
- Nested structures multiply the contribution by a fixed factor.

General technique:
    Track nesting depth.
    Detect the smallest/base pattern.
    Add its contribution based on current depth.

================================================================================
*/
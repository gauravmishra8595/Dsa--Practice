#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int n = s.length();
        int open = 0, close = 0, result = 0;

        // Left to Right
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close)
            {
                result = max(result, open + close);
            }
            else if (close > open)
            {
                open = close = 0;
            }
        }

        // Right to Left
        open = close = 0;

        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close)
            {
                result = max(result, open + close);
            }
            else if (open > close)
            {
                open = close = 0;
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;

    vector<string> testCases = {
        "(()",
        ")()())",
        "()(()",
        "((()))",
        ""};

    for (const string &s : testCases)
    {
        cout << "Input: " << s << '\n';
        cout << "Output: " << sol.longestValidParentheses(s) << "\n\n";
    }

    return 0;
}

/*
================================================================================
                    LEETCODE 32 - LONGEST VALID PARENTHESES
================================================================================

PROBLEM STATEMENT
-----------------
Given a string s containing only '(' and ')', find the length of the longest
valid (well-formed) parentheses substring.

A valid parentheses string:
- Has matching '(' and ')' pairs.
- Every ')' has a corresponding '(' before it.
- The substring must be contiguous.

Example:
    Input:  s = ")()())"
    Output: 4

Explanation:
    The longest valid substring is "()()"
    Length = 4

================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Generate every possible substring and check whether that substring contains
valid parentheses.

A substring is valid if:
    - At every point, number of '(' >= number of ')'
    - At the end, number of '(' == number of ')'

PSEUDO CODE
-----------
for every starting index i:
    for every ending index j:
        check whether s[i...j] is valid
        if valid:
            update maximum length

COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:
    bool isValid(string s, int l, int r) {
        int balance = 0;

        for (int i = l; i <= r; i++) {
            if (s[i] == '(')
                balance++;
            else
                balance--;

            if (balance < 0)
                return false;
        }

        return balance == 0;
    }

    int longestValidParentheses(string s) {
        int n = s.length();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if ((j - i + 1) % 2 == 0) {
                    if (isValid(s, i, j)) {
                        ans = max(ans, j - i + 1);
                    }
                }
            }
        }

        return ans;
    }
};

TIME COMPLEXITY
---------------
O(n^3)

There are O(n^2) substrings and checking each substring can take O(n).

SPACE COMPLEXITY
----------------
O(1)

================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
We can solve the problem using two counters:

    open  = number of '('
    close = number of ')'

Whenever:

    open == close

we have a valid parentheses substring, so its length is:

    open + close

INTUITION
---------
We scan from LEFT to RIGHT first.

If:

    close > open

then there are more ')' than '('.

Such a substring can never become valid, so we reset both counters.

However, a left-to-right scan alone misses cases where there are extra '('.

Example:

    "((())"

From left to right:

    open > close

and we never get open == close, even though "(())" is a valid substring.

Therefore, we perform a SECOND scan from RIGHT to LEFT.

During the reverse scan, if:

    open > close

there are too many '(' from the right-side perspective, so we reset.

This handles the cases missed by the first pass.

PSEUDO CODE
-----------
result = 0

// Left to Right
open = 0
close = 0

for every character:
    if character == '(':
        open++
    else:
        close++

    if open == close:
        result = max(result, open + close)

    else if close > open:
        open = 0
        close = 0

// Right to Left
open = 0
close = 0

for every character from right to left:
    if character == '(':
        open++
    else:
        close++

    if open == close:
        result = max(result, open + close)

    else if open > close:
        open = 0
        close = 0

return result

COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        int open = 0, close = 0, result = 0;

        // Left to Right
        for (int i = 0; i < n; i++) {
            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close) {
                result = max(result, open + close);
            }
            else if (close > open) {
                open = close = 0;
            }
        }

        // Right to Left
        open = close = 0;

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close) {
                result = max(result, open + close);
            }
            else if (open > close) {
                open = close = 0;
            }
        }

        return result;
    }
};

TIME COMPLEXITY
---------------
O(n)

We scan the string twice:

    O(n) + O(n) = O(n)

SPACE COMPLEXITY
----------------
O(1)

Only a few integer variables are used.

================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Example:
    s = ")()())"

LEFT TO RIGHT:

Character    open    close    result
------------------------------------
    )          0       1       0
              reset
    (          1       0       0
    )          1       1       2
    (          2       1       2
    )          2       2       4
    )          2       3       4
              reset

Result = 4

Why do we need RIGHT TO LEFT?

Consider:

    s = "((())"

LEFT TO RIGHT:

    (   -> open = 1, close = 0
    (   -> open = 2, close = 0
    (   -> open = 3, close = 0
    )   -> open = 3, close = 1
    )   -> open = 3, close = 2

open never equals close.

But the substring:

    "(())"

is valid and has length 4.

The RIGHT TO LEFT pass finds it.

RIGHT TO LEFT:

    )   -> open = 0, close = 1
    )   -> open = 0, close = 2
    (   -> open = 1, close = 2
    (   -> open = 2, close = 2

Now:

    open == close

Therefore:

    result = 4

================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
Two-pass / Two-pointer-counter style.

Maintain counts of '(' and ')' while scanning from both directions.

KEY OBSERVATION
---------------
One direction is not enough.

Left-to-right catches cases where there are too many ')'.

Right-to-left catches cases where there are too many '('.

COMMON MISTAKES
---------------
1. Only doing left-to-right.

   This misses cases like:

       "((())"

2. Returning the number of pairs.

   For:

       "()()"

   Number of pairs = 2
   Answer = 4

   We need the LENGTH, not the number of pairs.

3. Not resetting when:

       close > open

   during the left-to-right scan.

4. Not resetting when:

       open > close

   during the right-to-left scan.

5. Confusing this problem with checking whether the entire string is valid.

   We need the LONGEST VALID SUBSTRING, not whether the complete string
   is valid.

WHEN TO USE THIS APPROACH
-------------------------
Use this approach when:

- The problem asks for the longest valid parentheses substring.
- The string contains only '(' and ')'.
- You want O(n) time.
- You want O(1) extra space.
- You need an alternative to stack or DP.

COMPARISON:

    Brute Force  -> O(n^3) time, O(1) space
    DP           -> O(n)   time, O(n) space
    Stack        -> O(n)   time, O(n) space
    Two Pass     -> O(n)   time, O(1) space   <-- Optimal Space

================================================================================
*/

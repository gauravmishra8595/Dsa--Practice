#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool checkValidString(string s)
    {
        int low = 0;
        int high = 0;
        for (char c : s)
        {
            if (c == '(')
            {
                ++low;
                ++high;
            }
            else if (c == ')')
            {
                low = max(0, --low);
                --high;
            }
            else
            { 
                low = max(0, --low);
                ++high;
            }

            if (high < 0)
                return false;
        }

        return low == 0;
    }
};

int main()
{
    Solution sol;

    vector<string> tests = {
        "()",
        "(*)",
        "(*))",
        "(((*)",
        ")*("};

    for (const string &s : tests)
    {
        cout << s << " -> "
             << (sol.checkValidString(s) ? "true" : "false")
             << '\n';
    }

    return 0;
}
/*
================================================================================
                    LEETCODE 678 - VALID PARENTHESIS STRING
================================================================================

PROBLEM STATEMENT
-----------------
Given a string s containing only three types of characters:
    '('
    ')'
    '*'

A '*' can be treated as:
    '('
    ')'
    or an empty string.

Return true if the string can be made valid by choosing a suitable
interpretation for every '*'.

A valid parenthesis string must have balanced opening and closing
parentheses, and every closing parenthesis must have a matching opening
parenthesis.

--------------------------------------------------------------------------------
EXAMPLE
--------------------------------------------------------------------------------

Input:
    s = "(*))"

Possible interpretation:
    "(())"

Output:
    true

Another example:
    s = ")*("

Output:
    false

--------------------------------------------------------------------------------
BRUTE FORCE APPROACH
--------------------------------------------------------------------------------

IDEA
----
For every '*', try all three possibilities:
    1. '('
    2. ')'
    3. empty

This generates all possible strings and checks whether at least one
interpretation is a valid parenthesis string.

PSEUDO CODE
-----------
function solve(s, index, balance):

    if balance < 0:
        return false

    if index == s.length:
        return balance == 0

    if s[index] == '(':
        return solve(s, index + 1, balance + 1)

    if s[index] == ')':
        return solve(s, index + 1, balance - 1)

    if s[index] == '*':
        return
            solve(s, index + 1, balance + 1) OR
            solve(s, index + 1, balance - 1) OR
            solve(s, index + 1, balance)

COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:
    bool solve(string& s, int index, int balance) {
        if (balance < 0)
            return false;

        if (index == s.size())
            return balance == 0;

        if (s[index] == '(')
            return solve(s, index + 1, balance + 1);

        if (s[index] == ')')
            return solve(s, index + 1, balance - 1);

        // '*'
        return solve(s, index + 1, balance + 1) ||
               solve(s, index + 1, balance - 1) ||
               solve(s, index + 1, balance);
    }

    bool checkValidString(string s) {
        return solve(s, 0, 0);
    }
};

TIME COMPLEXITY
---------------
O(3^n) in the worst case.

SPACE COMPLEXITY
----------------
O(n) recursion stack.

================================================================================
                            OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
We do not need to decide immediately what every '*' represents.

Instead, maintain a RANGE of possible unmatched '(' counts.

    low  = minimum possible number of unmatched '('
    high = maximum possible number of unmatched '('

For each character:

1. '('
   It must be an opening parenthesis.

       low++
       high++

2. ')'
   It must close an opening parenthesis.

       low--
       high--

   But low cannot go below zero because we can choose a previous '*'
   to act differently.

       low = max(0, low)

3. '*'
   It can be:
       '('  -> balance + 1
       ')'  -> balance - 1
       empty -> balance unchanged

   Therefore:

       low--
       high++

   Again:

       low = max(0, low)

If high becomes negative, even the maximum possible balance is negative.
That means there is no possible interpretation that can make the prefix valid.

At the end, if low == 0, there exists at least one valid interpretation.

INTUITION
---------
Instead of trying every possibility of '*', keep all possibilities
compressed into a range.

For example:

    low  = 1
    high = 3

means that depending on how '*' characters are interpreted, the number
of currently unmatched '(' can be anywhere from 1 to 3.

We only need to know the smallest and largest possible balance.

PSEUDO CODE
-----------
low = 0
high = 0

for every character c:

    if c == '(':
        low++
        high++

    else if c == ')':
        low = max(0, low - 1)
        high--

    else if c == '*':
        low = max(0, low - 1)
        high++

    if high < 0:
        return false

return low == 0

COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {
            if (c == '(') {
                ++low;
                ++high;
            }
            else if (c == ')') {
                low = max(0, --low);
                --high;
            }
            else { // '*'
                low = max(0, --low);
                ++high;
            }

            if (high < 0)
                return false;
        }

        return low == 0;
    }
};

TIME COMPLEXITY
---------------
O(n)

We process every character exactly once.

SPACE COMPLEXITY
----------------
O(1)

Only two integer variables are maintained:
    low
    high

================================================================================
                              DRY RUN
================================================================================

Example:
    s = "(*))"

Initial:
    low = 0
    high = 0

Character '(':
    low  = 1
    high = 1

    Possible balance:
        [1, 1]

Character '*':
    '*' can be '(', ')' or empty.

    low  = max(0, 1 - 1) = 0
    high = 1 + 1 = 2

    Possible balance:
        [0, 2]

Character ')':
    low  = max(0, 0 - 1) = 0
    high = 2 - 1 = 1

    Possible balance:
        [0, 1]

Character ')':
    low  = max(0, 0 - 1) = 0
    high = 1 - 1 = 0

    Possible balance:
        [0, 0]

At the end:
    low == 0

Therefore:
    true

One valid interpretation is:

    ( * ) )
      |
      ')'

Result:
    ( ( ) )

which is valid.

================================================================================
                              INTERVIEW NOTES
================================================================================

PATTERN
-------
Greedy + Range of Possibilities

This is useful when a character has multiple possible meanings and
we can represent all possibilities using a minimum and maximum state.

KEY OBSERVATION
---------------
Maintain:

    low  = minimum possible unmatched '('
    high = maximum possible unmatched '('

For '*':
    low  decreases because '*' can become ')'
    high increases because '*' can become '('

If:
    high < 0

then even the most favorable interpretation cannot make the prefix valid.

At the end:
    low == 0

means at least one valid interpretation exists.

COMMON MISTAKES
---------------
1. Treating '*' as only '(' or ')'.
   It can also be empty.

2. Forgetting:
       low = max(0, low)

3. Only checking the final balance.
   A prefix can become invalid before reaching the end.

4. Forgetting to check:
       high < 0

5. Using brute force recursion without considering exponential
   complexity.

6. Confusing low/high:
       low  = minimum possible balance
       high = maximum possible balance

WHEN TO USE THIS APPROACH
-------------------------
Use this technique when:

- A character has multiple possible interpretations.
- Each interpretation changes a running balance/state.
- We only need the minimum and maximum possible state.
- Exploring every possibility would be exponential.
- The possible states form a continuous range that can be compressed
  into [low, high].

FINAL COMPLEXITY
----------------
Optimal:
    Time  = O(n)
    Space = O(1)

This is optimal because every character must be inspected at least once.

================================================================================
*/

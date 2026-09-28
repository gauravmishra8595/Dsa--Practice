#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxDepth(string s) {
        int depth = 0;
        int ans = 0;

        for (char x : s) {
            if (x == '(') {
                depth++;
                ans = max(ans, depth);
            }
            else if (x == ')') {
                depth--;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    string s = "(1+(2*3)+((8)/4))+1";

    cout << sol.maxDepth(s) << endl;

    return 0;
}

/*
====================================================================
                         PROBLEM STATEMENT
====================================================================

Given a valid parentheses string s, return the maximum nesting depth
of the parentheses.

The nesting depth is the maximum number of currently open '('
parentheses at any point in the string.

Example:
    Input:  "(1+(2*3)+((8)/4))+1"
    Output: 3

Explanation:
    The deepest nesting is:

        ((8)/4)
          ^^^
    
    There are 3 open parentheses at the deepest point.

====================================================================
                            EXAMPLE
====================================================================

Input:
    s = "(1+(2*3)+((8)/4))+1"

Output:
    3

Another example:

Input:
    s = "(())"

Output:
    2


====================================================================
                       BRUTE FORCE APPROACH
====================================================================

----------------------------- IDEA --------------------------------

For every opening parenthesis '(', we can find its matching closing
parenthesis ')' and calculate how many parentheses are nested inside.

One simple brute-force idea is:

1. For every '(':
      - Find its matching ')'.
      - Count how many '(' occur before its matching ')' while still
        inside this pair.
2. Keep the maximum count.

Another straightforward brute-force method is to check every position
and count the number of '(' before it minus ')' before it.

This results in repeated scanning and is unnecessary because we can
maintain the current depth in one pass.

-------------------------- PSEUDO CODE -----------------------------

for every position i:
    if s[i] == '(':
        find the corresponding ')'
        calculate nesting depth
        update answer

return maximum depth

---------------------- COMPLETE BRUTE FORCE CODE -----------------

Brute force code for revision only:

class Solution {
public:
    int maxDepth(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] != '(')
                continue;

            int balance = 0;

            for (int j = i; j < n; j++) {
                if (s[j] == '(')
                    balance++;
                else if (s[j] == ')')
                    balance--;

                if (balance == 0) {
                    ans = max(ans, j - i + 1);
                    break;
                }
            }
        }

        // This method finds the longest parenthesis interval,
        // but for maximum nesting it still requires tracking
        // nesting within each interval.

        int maxDepth = 0;

        for (int i = 0; i < n; i++) {
            int depth = 0;

            for (int j = 0; j <= i; j++) {
                if (s[j] == '(')
                    depth++;
                else if (s[j] == ')')
                    depth--;
            }

            maxDepth = max(maxDepth, depth);
        }

        return maxDepth;
    }
};

------------------------ TIME COMPLEXITY --------------------------

O(N^2)

Because we repeatedly scan parts of the string.

------------------------- SPACE COMPLEXITY ------------------------

O(1)

Only a few integer variables are used.


====================================================================
                       OPTIMAL APPROACH
====================================================================

--------------------------- OBSERVATION ----------------------------

Every '(' increases the current nesting depth by 1.

Every ')' decreases the current nesting depth by 1.

Therefore, we only need to maintain:

    depth = current number of open parentheses

Whenever depth increases, check whether it is the maximum seen so
far.

---------------------------- INTUITION -----------------------------

Think of '(' as entering a new level and ')' as leaving that level.

Example:

    ((()))

Depth changes as:

    0
    1  -> '('
    2  -> '('
    3  -> '('
    2  -> ')'
    1  -> ')'
    0  -> ')'

The maximum value reached by depth is the answer.

Therefore:

    '('  -> depth++
    ')'  -> depth--

And after every '(':

    ans = max(ans, depth)

This allows us to solve the problem in one traversal.

-------------------------- PSEUDO CODE -----------------------------

depth = 0
ans = 0

for every character x in s:

    if x == '(':
        depth++
        ans = max(ans, depth)

    else if x == ')':
        depth--

return ans

---------------------- COMPLETE OPTIMAL CODE ----------------------

Optimal code for revision only:

class Solution {
public:
    int maxDepth(string s) {
        int depth = 0;
        int ans = 0;

        for (char x : s) {
            if (x == '(') {
                depth++;
                ans = max(ans, depth);
            }
            else if (x == ')') {
                depth--;
            }
        }

        return ans;
    }
};

------------------------ TIME COMPLEXITY --------------------------

O(N)

We traverse the string exactly once.

------------------------- SPACE COMPLEXITY ------------------------

O(1)

Only depth and ans are used.


====================================================================
                           DRY RUN
====================================================================

Example:

    s = "(1+(2*3)+((8)/4))+1"

Start:

    depth = 0
    ans   = 0

Character by character:

    '('  -> depth = 1, ans = 1
    '1'  -> depth = 1
    '+'  -> depth = 1
    '('  -> depth = 2, ans = 2
    '2'  -> depth = 2
    '*'  -> depth = 2
    '3'  -> depth = 2
    ')'  -> depth = 1
    '+'  -> depth = 1
    '('  -> depth = 2
    '('  -> depth = 3, ans = 3
    '8'  -> depth = 3
    ')'  -> depth = 2
    '/'  -> depth = 2
    '4'  -> depth = 2
    ')'  -> depth = 1
    ')'  -> depth = 0
    '+'  -> depth = 0
    '1'  -> depth = 0

Final:

    ans = 3

Therefore:

    Output = 3


====================================================================
                         INTERVIEW NOTES
====================================================================

----------------------------- PATTERN ------------------------------

This is a:

    Parentheses / Balance / Counting Depth

pattern.

It can be solved using a simple counter because the parentheses are
guaranteed to form a valid string.

------------------------ KEY OBSERVATION ---------------------------

'(' means:

    Enter one level
    depth++

')' means:

    Leave one level
    depth--

The maximum value of depth is the maximum nesting depth.

------------------------- COMMON MISTAKES --------------------------

1. Forgetting depth-- for ')'.

   Wrong:

       if (x == '(')
           depth++;

   Without depth--, depth will only increase.

2. Confusing total '(' count with nesting depth.

   Example:

       ()()()

   Total opening parentheses = 3

   Maximum nesting depth = 1

3. Writing:

       x == '(';

   This only compares x with '('.
   It does NOT update anything.

4. Increasing ans for every '(' without tracking depth.

   The answer is the maximum CURRENT depth, not the total number
   of opening parentheses.

5. Forgetting to update ans after increasing depth.

---------------------- WHEN TO USE THIS APPROACH -------------------

Use this approach when:

    - The problem involves valid parentheses.
    - You need maximum nesting depth.
    - You need current balance/depth.
    - Each '(' increases a level.
    - Each ')' decreases a level.
    - You only need the maximum depth, not the actual matching pairs.

The important idea is:

    Maintain the current state while traversing once.

Final complexity:

    Time  : O(N)
    Space : O(1)

====================================================================
*/
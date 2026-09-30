#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string removeOuterParentheses(string s)
    {
        string ans;
        int depth = 0;
        for (char c : s)
        {
            if (c == '(')
            {
                if (depth > 0)
                    ans += c;
                depth++;
            }
            else
            {
                depth--;
                if (depth > 0)
                    ans += c;
            }
        }
        return ans;
    }
};
int main()
{
    string s;
    cin >> s;
    Solution sol;
    cout << sol.removeOuterParentheses(s);
    return 0;
}
/*
================================================================================
PROBLEM STATEMENT
================================================================================

Given a valid parentheses string s, remove the outermost pair of parentheses
from every primitive valid parentheses substring.

A primitive parentheses string is a non-empty valid parentheses string that
cannot be split into two non-empty valid parentheses strings.

Return the resulting string.

================================================================================
EXAMPLE
================================================================================

Input:
    (()())(())

Split into primitive strings:

    (()()) (())

Remove the outermost pair from each:

    ()() ()

Output:
    ()()()

================================================================================
BRUTE FORCE APPROACH
================================================================================

-------------------------
Idea
-------------------------

Find every primitive parentheses substring separately.

For each primitive:
    1. Remove its first '('.
    2. Remove its last ')'.
    3. Append the remaining part to the answer.

To find primitive boundaries, maintain the current balance/depth.

Whenever depth becomes 0, one primitive substring is complete.

-------------------------
Pseudo Code
-------------------------

ans = ""
start = 0
depth = 0

for i from 0 to n-1:

    if s[i] == '(':
        depth++
    else:
        depth--

    if depth == 0:
        append s[start + 1 ... i - 1] to ans
        start = i + 1

return ans

-------------------------
Complete Brute Force Code
(For revision only - NOT executable)
-------------------------

string bruteForce(string s) {
    string ans = "";
    int depth = 0;
    int start = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(')
            depth++;
        else
            depth--;

        if (depth == 0) {
            for (int j = start + 1; j < i; j++) {
                ans += s[j];
            }

            start = i + 1;
        }
    }

    return ans;
}

-------------------------
Time Complexity
-------------------------

O(n)

Every character is processed a constant number of times.

-------------------------
Space Complexity
-------------------------

O(n)

For storing the resulting string.

================================================================================
OPTIMAL APPROACH
================================================================================

-------------------------
Observation
-------------------------

The outermost '(' of a primitive appears when:

    depth == 0

before processing '('.

The outermost ')' appears when:

    depth == 1

before processing ')'.

Therefore:

For '(':
    Add it only if depth > 0.
    Then increase depth.

For ')':
    First decrease depth.
    Add it only if depth > 0.

This allows us to remove the outermost parentheses without explicitly
finding each primitive substring.

-------------------------
Intuition
-------------------------

Consider:

    (()())

Depth changes like:

    (  -> 1
    (  -> 2
    )  -> 1
    (  -> 2
    )  -> 1
    )  -> 0

The first '(' takes depth from 0 -> 1.
It is the outermost '(' and should NOT be added.

The last ')' takes depth from 1 -> 0.
It is the outermost ')' and should NOT be added.

Everything between them is part of the answer.

So:

    '(' -> add only when old depth > 0
    ')' -> decrease depth first, then add only when new depth > 0

-------------------------
Pseudo Code
-------------------------

ans = ""
depth = 0

for every character c:

    if c == '(':

        if depth > 0:
            add c to ans

        depth++

    else:

        depth--

        if depth > 0:
            add c to ans

return ans

-------------------------
Complete Optimal Code
(For revision only)
-------------------------

class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int depth = 0;

        for (char c : s) {
            if (c == '(') {
                if (depth > 0)
                    ans += c;

                depth++;
            } else {
                depth--;

                if (depth > 0)
                    ans += c;
            }
        }

        return ans;
    }
};

-------------------------
Time Complexity
-------------------------

O(n)

We traverse the string exactly once.

-------------------------
Space Complexity
-------------------------

O(n)

The answer string can contain up to O(n) characters.

Auxiliary space excluding the output: O(1).

================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:

    s = "(()())"

Initially:

    depth = 0
    ans = ""

1. c = '('

   depth = 0
   depth > 0 ? No

   Do not add '('.

   depth = 1

   ans = ""

2. c = '('

   depth = 1
   depth > 0 ? Yes

   Add '('.

   depth = 2

   ans = "("

3. c = ')'

   depth = 2

   depth--
   depth = 1

   depth > 0 ? Yes

   Add ')'.

   ans = "()"

4. c = '('

   depth = 1
   depth > 0 ? Yes

   Add '('.

   depth = 2

   ans = "()("

5. c = ')'

   depth = 2

   depth--
   depth = 1

   Add ')'.

   ans = "()()"

6. c = ')'

   depth = 1

   depth--
   depth = 0

   depth > 0 ? No

   Do not add ')'.

Final:

    ans = "()()"

Therefore:

    Input  : (()())
    Output : ()()

================================================================================
INTERVIEW NOTES
================================================================================

-------------------------
Pattern
-------------------------

Depth / Balance Tracking + String Simulation

-------------------------
Key Observation
-------------------------

The outermost parentheses are exactly the parentheses that change the
depth between:

    0 -> 1

and

    1 -> 0

So they can be skipped using the current depth.

For '(':
    if depth > 0, keep it
    then depth++

For ')':
    depth--
    if depth > 0, keep it

-------------------------
Common Mistakes
-------------------------

1. Using vector<int> instead of string.

   The answer is a string.

2. For '(' checking depth after incrementing.

   The outermost '(' must be detected when depth is 0 before incrementing.

3. For ')' checking before decrementing.

   The outermost ')' must be detected when depth becomes 0 after decrementing.

4. Forgetting to reset or correctly maintain depth.

5. Using a stack unnecessarily.

   A simple depth counter is enough.

-------------------------
When to Use This Approach
-------------------------

Use depth tracking when:

- The input is a valid parentheses string.
- You need to identify nested levels.
- You need to detect primitive parentheses groups.
- The operation depends on entering or leaving the outermost level.

General pattern:

    '(' -> depth++
    ')' -> depth--

Then use the value of depth to decide what to keep or remove.

================================================================================
*/

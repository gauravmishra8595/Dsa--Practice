#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minAddToMakeValid(string s)
    {
        int open = 0;
        int additions = 0;

        for (char ch : s)
        {
            if (ch == '(')
            {
                open++;
            }
            else
            {
                if (open > 0)
                {
                    open--;
                }
                else
                {
                    additions++;
                }
            }
        }

        return additions + open;
    }
};

int main()
{
    Solution sol;

    vector<string> testCases = {
        "())",
        "(((",
        "()",
        "()))((",
        "()))(("};

    for (string s : testCases)
    {
        cout << s << " -> "
             << sol.minAddToMakeValid(s)
             << '\n';
    }

    return 0;
}

/*
============================================================
            LEETCODE 921: MINIMUM ADD TO MAKE
                  PARENTHESES VALID
============================================================

Problem Statement:
------------------
Given a parentheses string s containing only '(' and ')',
return the minimum number of parentheses that must be added
to make the string valid.

A valid parentheses string must have:
1. Every '(' matched with a ')'.
2. Every ')' matched with a previous '('.
3. Proper nesting of parentheses.

Example:
--------
Input:
s = "())"

Output:
1

Explanation:
Add one '(' at the beginning or one ')' at the end:

"()()" or "())()"


------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Use a stack to explicitly keep track of unmatched opening
parentheses.

- Push '(' into the stack.
- For ')':
    - If stack is not empty, match it with an opening '('.
    - Otherwise, this ')' is unmatched and requires adding
      one '('.

After processing the complete string, every '(' remaining
in the stack needs one ')' to match it.

Pseudo Code:
-----------
1. Create an empty stack.
2. Set additions = 0.
3. For every character ch:
      If ch == '(':
          push ch.
      Else:
          If stack is not empty:
              pop stack.
          Else:
              additions++.
4. Every remaining '(' needs one ')'.
5. Return additions + stack.size().

Complete Brute Force Code:
--------------------------

class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> st;
        int additions = 0;

        for (char ch : s) {
            if (ch == '(') {
                st.push(ch);
            }
            else {
                if (!st.empty()) {
                    st.pop();
                }
                else {
                    additions++;
                }
            }
        }

        return additions + st.size();
    }
};

Time Complexity:
----------------
O(n)

Each character is processed once.

Space Complexity:
-----------------
O(n)

The stack can contain up to n opening parentheses.


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
We do not actually need to store every '('.

We only need to know how many unmatched opening parentheses
currently exist.

So instead of a stack, maintain:

open = number of unmatched '('.

When we see ')':
- If open > 0, it can match an existing '('.
- Otherwise, this ')' is unmatched and requires one
  additional '('.

At the end, all remaining unmatched '(' require one ')'
each.

Intuition:
----------
There are two types of parentheses that need fixing:

1. Extra ')'
   Example: ")"
   We need to add '('.
   Count using additions.

2. Extra '('
   Example: "((("
   We need to add ')' for every remaining '('.
   Count using open.

Therefore:

Answer = additions + open


Pseudo Code:
------------
1. open = 0
2. additions = 0

3. For every character ch:
      If ch == '(':
          open++
      Else:
          If open > 0:
              open--
          Else:
              additions++

4. Return additions + open


Complete Optimal Code:
----------------------

class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0;
        int additions = 0;

        for (char ch : s) {
            if (ch == '(') {
                open++;
            }
            else {
                if (open > 0) {
                    open--;
                }
                else {
                    additions++;
                }
            }
        }

        return additions + open;
    }
};

Time Complexity:
----------------
O(n)

Every character is processed exactly once.

Space Complexity:
-----------------
O(1)

Only two integer variables are used.


------------------------------------------------------------
Dry Run with Example
------------------------------------------------------------

Input:
s = "()))(("

Initial:
open = 0
additions = 0

1. ch = '('
   open = 1

2. ch = ')'
   Match with '('
   open = 0

3. ch = ')'
   No '(' available.
   Need one '('.
   additions = 1

4. ch = ')'
   No '(' available.
   Need one '('.
   additions = 2

5. ch = '('
   open = 1

6. ch = '('
   open = 2

Final:
open = 2
additions = 2

The two unmatched ')' need two '('.
The two unmatched '(' need two ')'.

Answer:
2 + 2 = 4


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
Greedy + Balance Counting

Key Observation:
----------------
For every ')', if there is an unmatched '(' available,
use it.

Otherwise, that ')' itself requires adding '('.

At the end, every remaining unmatched '(' requires one ')'.

Common Mistakes:
----------------
1. Forgetting that unmatched ')' must be fixed immediately.
2. Returning only the number of unmatched '('.
3. Using a stack when only the count is required.
4. Forgetting to add the remaining 'open' count.
5. Confusing this problem with LeetCode 20:
   - LeetCode 20 asks whether the string is valid.
   - LeetCode 921 asks the minimum additions required.

When to use this approach:
--------------------------
Use this balance-counting technique when:
- The string contains only '(' and ')'.
- You need the number of unmatched parentheses.
- You do not need to know the exact positions.
- A stack's actual contents are unnecessary.

Key Formula:
------------
answer = unmatched ')' + unmatched '('

In the implementation:
answer = additions + open

This reduces the stack-based solution from O(n) auxiliary
space to O(1) auxiliary space.

============================================================
*/

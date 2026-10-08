#include <bits/stdc++.h>
using namespace std;

// LeetCode 1021 - Remove Outermost Parentheses

class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int depth = 0;

        for (char c : s) {
            if (c == '(') {
                if (depth > 0) ans += c;
                depth++;
            } else {
                depth--;
                if (depth > 0) ans += c;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    string s = "(()())(())";
    cout << sol.removeOuterParentheses(s) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 1021 - REMOVE OUTERMOST PARENTHESES
================================================================================

Problem Statement:
------------------
A valid parentheses string is either empty, "(" + A + ")", or A + B,
where A and B are valid parentheses strings.

A primitive valid parentheses string is a non-empty valid parentheses string
that cannot be split into two non-empty valid parentheses strings.

Given a valid parentheses string s, decompose it into primitive components
and remove the outermost parentheses of every primitive component.

Return the resulting string.

Example:
--------
Input:
s = "(()())(())"

Primitive components:
"(()())" + "(())"

After removing outermost parentheses:
"()()" + "()"

Output:
"()()"

Brute Force Approach:
---------------------

Idea:
-----
Find every primitive parentheses substring separately.

For each primitive:
1. Find its matching closing parenthesis.
2. Remove its first '(' and last ')'.
3. Append the remaining substring to the answer.

Pseudo Code:
-----------
1. Initialize ans = "".
2. Start from i = 0.
3. Maintain balance = 0.
4. Find the end of the current primitive.
5. Add primitive without first and last characters.
6. Continue with the next primitive.
7. Return ans.

Complete Brute Force Code:
--------------------------

class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int n = s.size();
        int i = 0;

        while (i < n) {
            int start = i;
            int balance = 0;

            while (i < n) {
                if (s[i] == '(')
                    balance++;
                else
                    balance--;

                i++;

                if (balance == 0)
                    break;
            }

            // Remove the outermost '(' and ')'
            ans += s.substr(start + 1, i - start - 2);
        }

        return ans;
    }
};

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n) for the resulting string and temporary substring.

Optimal Approach:
-----------------

Observation:
------------
For every primitive component:

    First '('  -> depth changes 0 -> 1
    Last ')'   -> depth changes 1 -> 0

These two parentheses are exactly the outermost parentheses.

Therefore:
- For '(' : add it only when current depth > 0.
- For ')' : decrease depth first, then add it only when depth > 0.

Intuition:
---------
Maintain the current nesting depth.

For an opening parenthesis:
    If depth == 0, it is an outermost '(' -> skip it.
    Otherwise, keep it.
    Then increase depth.

For a closing parenthesis:
    First decrease depth.
    If depth == 0, it is an outermost ')' -> skip it.
    Otherwise, keep it.

This removes the outermost pair of every primitive component
without explicitly splitting the string.

Pseudo Code:
-----------
1. Initialize ans = "" and depth = 0.
2. For every character c in s:
   a. If c == '(':
      - If depth > 0, add c to ans.
      - Increment depth.
   b. Otherwise:
      - Decrement depth.
      - If depth > 0, add c to ans.
3. Return ans.

Complete Optimal Code:
----------------------

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

Time Complexity:
----------------
O(n)

Each character is processed exactly once.

Space Complexity:
-----------------
O(n)

O(n) for the answer string.

Dry Run with Example:
---------------------

Input:
s = "(()())(())"

Initially:
ans = ""
depth = 0

Character: '('
depth = 0 -> outermost '(' -> skip
depth = 1

Character: '('
depth > 0 -> add '('
ans = "("
depth = 2

Character: ')'
depth becomes 1 -> add ')'
ans = "()"

Character: '('
depth > 0 -> add '('
ans = "()("
depth = 2

Character: ')'
depth becomes 1 -> add ')'
ans = "()()"

Character: ')'
depth becomes 0 -> outermost ')' -> skip

Character: '('
depth = 0 -> outermost '(' -> skip
depth = 1

Character: '('
depth > 0 -> add '('
ans = "()("
depth = 2

Character: ')'
depth becomes 1 -> add ')'
ans = "()()"

Character: ')'
depth becomes 0 -> outermost ')' -> skip

Final Answer:
"()()"

Interview Notes:
----------------

Pattern:
--------
Parentheses / Balanced Brackets + Depth Tracking

Key Observation:
----------------
The outermost parentheses of every primitive component are exactly the
parentheses that occur when the depth changes:

    0 -> 1   : outermost '('
    1 -> 0   : outermost ')'

So we simply skip parentheses at depth 0.

Common Mistakes:
----------------
1. Removing only the first and last character of the entire string.
   The string can contain multiple primitive components.

2. Checking depth after incrementing for '(' incorrectly.
   For '(' we check depth BEFORE incrementing.

3. Checking depth before decrementing for ')'.
   For ')' we must decrement first, then check whether depth became 0.

4. Using unnecessary stack operations.
   A simple integer depth is sufficient.

When to use this approach:
--------------------------
Use depth tracking whenever a problem involves balanced parentheses and
the required operation depends on nesting level.

Typical signals:
- Remove outer parentheses.
- Detect primitive components.
- Track nesting depth.
- Process characters differently at different levels.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char ch : s) {
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } 
            else {
                if (st.empty()) return false;

                char top = st.top();
                st.pop();

                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    return false;
                }
            }
        }

        return st.empty();
    }
};

int main() {
    Solution sol;

    vector<string> testCases = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "]"
    };

    for (string s : testCases) {
        cout << s << " -> "
             << (sol.isValid(s) ? "true" : "false")
             << '\n';
    }

    return 0;
}

/*
============================================================
                    LEETCODE 20
                  VALID PARENTHESES
============================================================

Problem Statement:
------------------
Given a string s containing just the characters
'(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

A string is valid if:
1. Every opening bracket has a corresponding closing bracket.
2. Brackets are closed in the correct order.
3. Every closing bracket matches the most recent unmatched
   opening bracket.

Example:
--------
Input:
s = "([{}])"

Output:
true

Explanation:
'(' matches ')'
'[' matches ']'
'{' matches '}'
and all brackets are properly nested.


------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Repeatedly remove valid adjacent pairs:
(), {}, []

If the string becomes empty, it is valid.
If no more pairs can be removed and characters remain,
the string is invalid.

Pseudo Code:
-----------
1. While s contains "()", "{}" or "[]":
       Remove one such pair.
2. If s is empty:
       return true
   Else:
       return false

Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool isValid(string s) {
        bool changed = true;

        while (changed) {
            changed = false;

            for (int i = 0; i + 1 < s.size(); i++) {
                if ((s[i] == '(' && s[i + 1] == ')') ||
                    (s[i] == '{' && s[i + 1] == '}') ||
                    (s[i] == '[' && s[i + 1] == ']')) {

                    s.erase(i, 2);
                    changed = true;
                    break;
                }
            }
        }

        return s.empty();
    }
};

Time Complexity:
----------------
O(n^2) in the worst case because removing characters from
a string can take O(n), and this may happen O(n) times.

Space Complexity:
-----------------
O(n) because string modifications may require additional
storage depending on implementation.


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
A closing bracket must match the most recently encountered
unmatched opening bracket.

This is exactly the Last-In-First-Out (LIFO) behavior of
a Stack.

Intuition:
----------
- Push every opening bracket onto the stack.
- When a closing bracket appears:
    1. The stack must not be empty.
    2. Its top must be the corresponding opening bracket.
    3. Remove that opening bracket.
- At the end, the stack must be empty.

For example:

s = "([{}])"

Process:
(  -> push
[  -> push
{  -> push
}  -> pop {
]  -> pop [
)  -> pop (

Stack becomes empty => valid.


Pseudo Code:
------------
1. Create an empty stack.
2. For every character ch in s:
      If ch is an opening bracket:
          push ch.
      Else:
          If stack is empty:
              return false.

          top = stack.top()
          pop stack.

          If ch does not match top:
              return false.
3. Return stack.empty().


Complete Optimal Code:
----------------------

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char ch : s) {
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            }
            else {
                if (st.empty()) return false;

                char top = st.top();
                st.pop();

                if ((ch == ')' && top != '(') ||
                    (ch == '}' && top != '{') ||
                    (ch == ']' && top != '[')) {
                    return false;
                }
            }
        }

        return st.empty();
    }
};

Time Complexity:
----------------
O(n)

Each character is pushed and/or popped at most once.

Space Complexity:
-----------------
O(n)

In the worst case, all characters are opening brackets
and are stored in the stack.


------------------------------------------------------------
Dry Run with Example
------------------------------------------------------------

Input:
s = "({[]})"

Initial:
stack = []

1. ch = '('
   Opening bracket -> push
   stack = [(]

2. ch = '{'
   Opening bracket -> push
   stack = [(, {]

3. ch = '['
   Opening bracket -> push
   stack = [(, {, []

4. ch = ']'
   Top = '['
   Matches ']'
   Pop
   stack = [(, {]

5. ch = '}'
   Top = '{'
   Matches '}'
   Pop
   stack = [(]

6. ch = ')'
   Top = '('
   Matches ')'
   Pop
   stack = []

Stack is empty.

Answer = true


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
Stack / LIFO

Key Observation:
----------------
A closing bracket must match the most recent unmatched
opening bracket.

Therefore, whenever an opening bracket is encountered,
store it in a stack.

Common Mistakes:
----------------
1. Forgetting to check if the stack is empty before pop().
2. Returning true without checking stack.empty() at the end.
3. Matching brackets incorrectly.
4. Using a queue instead of a stack.
5. Ignoring cases such as:
       "]"
       "([)]"
       "((("
       "())"

When to use this approach:
--------------------------
Use a stack when:
- Elements must be processed in reverse order of arrival.
- You need to match nested structures.
- You need to find the most recent unmatched element.
- The problem involves parentheses, brackets, or nested
  expressions.

Typical related problems:
- Valid Parentheses
- Min Stack
- Next Greater Element
- Daily Temperatures
- Largest Rectangle in Histogram
- Evaluate Reverse Polish Notation

============================================================
*/

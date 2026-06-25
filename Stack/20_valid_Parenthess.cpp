#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;

        for (char ch : s)
        {
            // Push opening brackets
            if (ch == '(' || ch == '{' || ch == '[')
            {
                st.push(ch);
            }
            else
            {
                // No matching opening bracket
                if (st.empty())
                    return false;

                char top = st.top();

                // Check if current closing bracket
                // matches the top opening bracket
                if ((ch == ')' && top == '(') ||
                    (ch == '}' && top == '{') ||
                    (ch == ']' && top == '['))
                {
                    st.pop();
                }
                else
                {
                    return false;
                }
            }
        }

        // Stack should be empty if valid
        return st.empty();
    }
};

int main()
{
    string s;

    cout << "Enter bracket string: ";
    cin >> s;

    Solution obj;

    if (obj.isValid(s))
        cout << "Valid Parentheses" << endl;
    else
        cout << "Invalid Parentheses" << endl;

    return 0;
}

/*
=========================================
LeetCode 20 : Valid Parentheses
=========================================

Problem:
Given a string containing only:

'(' , ')' , '{' , '}' , '[' , ']'

Determine whether the string is valid.

A string is valid if:
1. Every opening bracket has a matching closing bracket.
2. Brackets close in the correct order.

Example:

Input: "()[]{}"
Output: true

Input: "(]"
Output: false

=========================================
Brute Force Approach
=========================================

Idea:
Repeatedly remove valid pairs:

()
{}
[]

If the string becomes empty,
all brackets were matched correctly.

Algorithm:

1. Keep searching for:
      "()"
      "{}"
      "[]"

2. Remove them whenever found.

3. Repeat until no further changes occur.

4. If string becomes empty:
      Valid
   Else:
      Invalid

Code:

bool isValid(string s)
{
    int prevLength = -1;

    while (prevLength != s.length())
    {
        prevLength = s.length();

        size_t pos;

        while ((pos = s.find("()")) != string::npos)
            s.erase(pos, 2);

        while ((pos = s.find("{}")) != string::npos)
            s.erase(pos, 2);

        while ((pos = s.find("[]")) != string::npos)
            s.erase(pos, 2);
    }

    return s.empty();
}

Time Complexity: O(N²)
Space Complexity: O(N)

=========================================
Optimal Approach (Stack)
=========================================

Idea:

Opening Bracket:
    Push into stack

Closing Bracket:
    Must match stack top

If mismatch occurs:
    Invalid

At the end:
    Stack should be empty

Example:

Input:
"({[]})"

Process:

(  -> push
{  -> push
[  -> push
]  -> pop [
}  -> pop {
)  -> pop (

Stack Empty -> Valid

=========================================
Dry Run
=========================================

Input:
s = "([{}])"

Stack State:

(      -> (
[      -> ([
{      -> ([{
}      -> ([
]      -> (
)      -> empty

Result:
true

=========================================
Time & Space Complexity
=========================================

Brute Force:
Time  : O(N²)
Space : O(N)

Optimal Stack:
Time  : O(N)
Space : O(N)

=========================================
Interview Tip
=========================================

This is one of the most common
Stack-based interview questions.

Key Observation:

Last opened bracket
must be closed first.

This is exactly the behavior of a stack
(LIFO - Last In First Out).

Hence Stack is the expected
optimal solution in interviews.
=========================================
*/
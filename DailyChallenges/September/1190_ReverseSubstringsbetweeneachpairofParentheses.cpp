#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string curr;

        for (char c : s) {
            if (c == '(') {
                st.push(curr);
                curr.clear();
            }
            else if (c == ')') {
                reverse(curr.begin(), curr.end());
                curr = st.top() + curr;
                st.pop();
            }
            else {
                curr += c;
            }
        }

        return curr;
    }
};

int main() {
    Solution sol;

    string s;
    cin >> s;

    cout << sol.reverseParentheses(s) << '\n';

    return 0;
}

/*
===============================================================================
        LEETCODE 1190 - REVERSE SUBSTRINGS BETWEEN EACH PAIR OF PARENTHESES
===============================================================================

PROBLEM STATEMENT
-----------------
Given a string s containing lowercase English letters and parentheses.

Reverse the strings inside each pair of matching parentheses, starting from
the innermost pair.

Remove all parentheses from the final result.

Example:
    Input:
        (abcd)

    Output:
        dcba

Example:
    Input:
        (u(love)i)

    Output:
        iloveu

===============================================================================
EXAMPLE
===============================================================================

Input:
    (u(love)i)

Process:

    Inner parentheses:
        (love) -> evol

    String becomes:
        (uevoli)

    Outer parentheses:
        (uevoli) -> iloveu

Output:
    iloveu

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

IDEA
----
Repeatedly find the innermost pair of parentheses.

For every pair:
    1. Find the substring between '(' and ')'.
    2. Reverse that substring.
    3. Remove the parentheses.
    4. Continue until no parentheses remain.

This repeatedly modifies the string, so it can take O(N^2) time.

PSEUDO CODE
-----------
while there is '(' in the string:

    find the first ')'

    find the matching '(' before it

    reverse the substring between '(' and ')'

    remove '(' and ')'

return the resulting string

COMPLETE BRUTE FORCE CODE
-------------------------

/*
class Solution {
public:
    string reverseParentheses(string s) {

        while (s.find('(') != string::npos) {

            int right = s.find(')');
            int left = right - 1;

            while (s[left] != '(') {
                left--;
            }

            reverse(s.begin() + left + 1,
                    s.begin() + right);

            s.erase(right, 1);
            s.erase(left, 1);
        }

        return s;
    }
};
*/

// TIME COMPLEXITY
// ---------------
// O(N^2)

// Repeated searching, reversing and modifying the string can take O(N^2).

// SPACE COMPLEXITY
// ----------------
// O(N)

// String operations may require additional memory.

// ===============================================================================
// OPTIMAL APPROACH
// ===============================================================================

// OBSERVATION
// -----------
// When we encounter '(':

//     The string currently built belongs to the outer level.

//     So save it in the stack and start a fresh string.

// When we encounter ')':

//     The current string represents the content inside the parentheses.

//     Reverse it.

//     Then attach it to the string saved before '('.

// INTUITION
// ---------
// Use:

//     stack<string> st

// and:

//     string curr

// The stack stores the string that existed before every '('.

// For '(':

//     Push curr into the stack.
//     Clear curr.

// For a normal character:

//     Add it to curr.

// For ')':

//     Reverse curr.
//     Add it to the previous string.
//     Pop the previous string from the stack.

// PSEUDO CODE
// -----------
// create stack<string> st
// create string curr

// for every character c:

//     if c == '(':

//         push curr into stack
//         clear curr

//     else if c == ')':

//         reverse curr

//         curr = previous_string + curr

//         pop stack

//     else:

//         add c to curr

// return curr

// COMPLETE OPTIMAL CODE
// ---------------------

/*
class Solution {
public:
    string reverseParentheses(string s) {

        stack<string> st;
        string curr;

        for (char c : s) {

            if (c == '(') {
                st.push(curr);
                curr.clear();
            }

            else if (c == ')') {
                reverse(curr.begin(), curr.end());

                curr = st.top() + curr;
                st.pop();
            }

            else {
                curr += c;
            }
        }

        return curr;
    }
};
*/

// TIME COMPLEXITY
// ---------------
// O(N)

// Each character is processed while traversing the string.

// The total work of reversing nested sections is O(N) for this approach because
// each character participates in the required reversals as the parentheses are
// closed.

// SPACE COMPLEXITY
// ----------------
// O(N)

// The stack can store strings from different nesting levels, and curr can also
// contain characters.

// ===============================================================================
// DRY RUN
// ===============================================================================

// Input:

//     (u(love)i)

// Step 1:
//     c = '('

//     Push curr = ""

//     Stack:
//         [""]

//     curr:
//         ""

// Step 2:
//     c = 'u'

//     curr:
//         "u"

// Step 3:
//     c = '('

//     Push curr = "u"

//     Stack:
//         ["", "u"]

//     curr:
//         ""

// Step 4:
//     Read:

//         l o v e

//     curr:
//         "love"

// Step 5:
//     c = ')'

//     Reverse:

//         "love" -> "evol"

//     Previous string from stack:

//         "u"

//     Combine:

//         "u" + "evol"
//         = "uevol"

//     Stack:
//         [""]

//     curr:
//         "uevol"

// Step 6:
//     c = 'i'

//     curr:
//         "uevoli"

// Step 7:
//     c = ')'

//     Reverse:

//         "uevoli" -> "iloveu"

//     Previous string:

//         ""

//     Combine:

//         "" + "iloveu"
//         = "iloveu"

// Final Answer:

//     iloveu

// ===============================================================================
// INTERVIEW NOTES
// ===============================================================================

// PATTERN
// -------
// Stack + Nested String Processing

// KEY OBSERVATION
// ---------------
// Whenever '(' is encountered, save the current outer string.

// Whenever ')' is encountered, reverse the current inner string and attach it
// back to the saved outer string.

// The stack handles nested parentheses naturally.

// COMMON MISTAKES
// ---------------
// 1. Using queue instead of stack.

//    Parentheses are nested, so we need LIFO behavior.

// 2. Forgetting to clear curr after '('.

// 3. Forgetting to reverse curr when ')' is found.

// 4. Forgetting to pop the previous string from the stack.

// 5. Trying to reverse the entire string instead of only the current
//    parenthesized section.

// 6. Not handling nested parentheses correctly.

// 7. Using st.top() without checking that the stack contains the matching
//    opening parenthesis.

// WHEN TO USE THIS APPROACH
// -------------------------
// Use this stack + current-string approach when:

//     - The problem contains nested parentheses/brackets.
//     - You need to process the innermost section first.
//     - The previous outer state needs to be restored after closing a section.
//     - You need LIFO behavior.
//     - Strings need to be transformed inside nested structures.

// Similar patterns appear in:

//     - Valid Parentheses
//     - Remove Outermost Parentheses
//     - Decode String
//     - Evaluate Nested Expressions
//     - Basic Calculator
//     - Nested String Problems

// ===============================================================================
// */

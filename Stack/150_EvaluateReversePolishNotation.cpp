#include <bits/stdc++.h>
using namespace std;

// LeetCode 150: Evaluate Reverse Polish Notation
class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<long long> st;

        for (string &token : tokens)
        {
            if (token == "+" || token == "-" ||
                token == "*" || token == "/")
            {

                long long b = st.top();
                st.pop();
                long long a = st.top();
                st.pop();

                if (token == "+")
                    st.push(a + b);
                else if (token == "-")
                    st.push(a - b);
                else if (token == "*")
                    st.push(a * b);
                else
                    st.push(a / b);
            }
            else
            {
                st.push(stoll(token));
            }
        }

        return (int)st.top();
    }
};

int main()
{
    Solution sol;

    vector<string> tokens = {"2", "1", "+", "3", "*"};

    cout << sol.evalRPN(tokens) << '\n';

    return 0;
}

/*
================================================================================
LeetCode 150 - Evaluate Reverse Polish Notation
================================================================================

Problem Statement:
------------------
Evaluate an arithmetic expression in Reverse Polish Notation (RPN).

Valid operators are:
    +, -, *, /

Each operand may be an integer or another expression.

Division between two integers truncates toward zero.

Return the value of the expression.

Example:
--------
Input:
tokens = ["2", "1", "+", "3", "*"]

Output:
9

Explanation:
    2 1 +  -> 3
    3 3 *  -> 9

Another Example:
    ["4", "13", "5", "/", "+"]

    13 / 5 = 2
    4 + 2 = 6

Answer = 6


================================================================================
Brute Force Approach
================================================================================

Idea:
-----
There is no meaningful brute-force solution needed for RPN.

A naive approach could repeatedly search for an operator, evaluate the two
operands immediately before it, replace them with the result, and continue.

This repeatedly modifies the expression and can require shifting elements.

Pseudo Code:
------------
function evaluate(tokens):
    while tokens contains more than one element:
        find an operator
        take the two previous operands
        calculate result
        replace operands and operator with result

    return tokens[0]

Complete brute force code (inside comments only):
--------------------------------------------------

// class SolutionBruteForce {
// public:
//     int evalRPN(vector<string> tokens) {
//         while (tokens.size() > 1) {
//             for (int i = 0; i < tokens.size(); i++) {
//
//                 if (tokens[i] == "+" || tokens[i] == "-" ||
//                     tokens[i] == "*" || tokens[i] == "/") {
//
//                     long long a = stoll(tokens[i - 2]);
//                     long long b = stoll(tokens[i - 1]);
//                     long long result;
//
//                     if (tokens[i] == "+") result = a + b;
//                     else if (tokens[i] == "-") result = a - b;
//                     else if (tokens[i] == "*") result = a * b;
//                     else result = a / b;
//
//                     tokens[i - 2] = to_string(result);
//                     tokens.erase(tokens.begin() + i - 1,
//                                  tokens.begin() + i + 1);
//
//                     break;
//                 }
//             }
//         }
//
//         return stoi(tokens[0]);
//     }
// };

Time Complexity:
----------------
O(n^2) in the worst case because searching and erasing from the vector can
be repeated many times.

Space Complexity:
-----------------
O(n) for storing and modifying the expression.


================================================================================
Optimal Approach
================================================================================

Observation:
------------
Reverse Polish Notation places the operator AFTER its operands.

For example:

    2 1 +

means:

    2 + 1

Whenever we encounter an operator, the last two values in the stack are
exactly the operands needed for that operator.

Intuition:
----------
Use a stack.

1. If the token is a number:
       Push it onto the stack.

2. If the token is an operator:
       Pop the second operand.
       Pop the first operand.
       Perform the operation.
       Push the result back.

Important:
----------
For subtraction and division, order matters.

If:
    a = second popped value
    b = first popped value

Then:
    a - b
    a / b

NOT:
    b - a
    b / a

Pseudo Code:
------------
function evalRPN(tokens):
    create empty stack

    for every token:
        if token is a number:
            push token into stack
        else:
            b = pop()
            a = pop()

            if token == "+":
                push a + b

            if token == "-":
                push a - b

            if token == "*":
                push a * b

            if token == "/":
                push a / b

    return top of stack

Complete optimal code (inside comments only):
----------------------------------------------

/*
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;

        for (string& token : tokens) {
            if (token == "+" || token == "-" ||
                token == "*" || token == "/") {

                long long b = st.top(); st.pop();
                long long a = st.top(); st.pop();

                if (token == "+") st.push(a + b);
                else if (token == "-") st.push(a - b);
                else if (token == "*") st.push(a * b);
                else st.push(a / b);
            }
            else {
                st.push(stoll(token));
            }
        }

        return (int)st.top();
    }
};
*/

// Time Complexity : -- -- -- -- -- -- -- --O(n)

//                       Every token is processed exactly once.

//                   Space Complexity : -- -- -- -- -- -- -- -- -O(n)

//                                          In the worst case,
//     all tokens can be numbers in the stack.

//         == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//         Dry Run with Example
//         == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

//         tokens = [ "2", "1", "+", "3", "*" ]

//     Initial:
//     stack = []

// Token = "2"
//     Push 2
//     stack = [2]

// Token = "1"
//     Push 1
//     stack = [2, 1]

// Token = "+"
//     b = 1
//     a = 2
//     result = 2 + 1 = 3
//     Push 3

//     stack = [3]

// Token = "3"
//     Push 3
//     stack = [3, 3]

// Token = "*"
//     b = 3
//     a = 3
//     result = 3 * 3 = 9
//     Push 9

//     stack = [9]

// Final Answer:
//     9


// ================================================================================
// Interview Notes
// ================================================================================

// Pattern:
// --------
// Stack + Expression Evaluation

// Key Observation:
// ----------------
// In Reverse Polish Notation, an operator always comes after its operands.

// Therefore, the last two elements in the stack are the operands for the
// current operator.

// Common Mistakes:
// ----------------
// 1. Reversing operand order for '-' and '/'.

//    Correct:
//        b = pop()
//        a = pop()

//        a - b
//        a / b

// 2. Using stoi when intermediate values may be safer with long long.

// 3. Forgetting to push the calculated result back onto the stack.

// 4. Treating negative numbers such as "-42" as the subtraction operator.

// 5. Using the wrong division order.

// 6. Forgetting that integer division truncates toward zero.

// When to use this approach:
// --------------------------
// Use a stack when:
// - Operators come after their operands.
// - Expressions are given in postfix / Reverse Polish Notation.
// - Each operator works on the most recently computed values.
// - Nested expressions need to be evaluated without recursion.

// General Pattern:

//     Operand -> Push
//     Operand -> Push
//     Operator -> Pop, Pop, Calculate, Push result

// ================================================================================
// */
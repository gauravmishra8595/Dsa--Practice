#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0;
        int ans = 0;

        for (char ch : s) {
            if (ch == '(') {
                open++;
            } else {
                if (open > 0)
                    open--;
                else
                    ans++;
            }
        }

        return ans + open;
    }
};

int main() {
    Solution sol;

    string s;
    cin >> s;

    cout << sol.minAddToMakeValid(s) << '\n';

    return 0;
}

/*
===============================================================================
                    LEETCODE 921 - MINIMUM ADD TO MAKE
                           PARENTHESES VALID
===============================================================================

Problem Statement:
------------------
A parentheses string is valid if:

1. It is an empty string.
2. It can be written as AB, where A and B are valid strings.
3. It can be written as (A), where A is a valid string.

Given a parentheses string s, return the minimum number of parentheses
characters '(' or ')' that must be added to make s valid.

Example:
--------
Input:
    s = "()))(("

Output:
    4

Explanation:
    Add one '(' before the first ')' and three ')' after the remaining '('.

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Try adding parentheses at different positions and check whether the resulting
string is valid.

We can recursively try:
    1. Add '('
    2. Add ')'
    3. Do not add anything

Then find the minimum number of additions required to obtain a valid string.

This approach explores many possible strings and is exponential, so it is not
suitable for the actual problem.

Pseudo Code:
------------
function isValid(s):
    balance = 0

    for ch in s:
        if ch == '(':
            balance++
        else:
            balance--

        if balance < 0:
            return false

    return balance == 0


function solve(s):
    if isValid(s):
        return 0

    answer = INF

    for every possible position:
        try adding '(' at that position
        answer = min(answer, 1 + solve(newString))

        try adding ')' at that position
        answer = min(answer, 1 + solve(newString))

    return answer


Complete Brute Force Code:
--------------------------
/*
class BruteForceSolution {
public:

    bool isValid(string s) {
        int balance = 0;

        for (char ch : s) {
            if (ch == '(')
                balance++;
            else
                balance--;

            if (balance < 0)
                return false;
        }

        return balance == 0;
    }

    int solve(string s) {
        if (isValid(s))
            return 0;

        int ans = INT_MAX;

        for (int i = 0; i <= (int)s.size(); i++) {

            string addOpen = s.substr(0, i) + "(" + s.substr(i);
            ans = min(ans, 1 + solve(addOpen));

            string addClose = s.substr(0, i) + ")" + s.substr(i);
            ans = min(ans, 1 + solve(addClose));
        }

        return ans;
    }

    int minAddToMakeValid(string s) {
        return solve(s);
    }
};
*/

// Time Complexity:
// ----------------
// Exponential, approximately O(2^N * N) or worse depending on implementation.

// Space Complexity:
// -----------------
// O(N) recursion depth, excluding the generated strings.

// ===============================================================================
// OPTIMAL APPROACH
// ===============================================================================

// Observation:
// ------------
// For a valid parentheses string:

//     Number of '(' must match Number of ')'

// Also, at every point while scanning from left to right:

//     Number of ')' <= Number of '('

// So we only need to track unmatched opening parentheses and unmatched closing
// parentheses.

// Intuition:
// ---------
// Maintain:

//     open = number of unmatched '('

// When we see '(':
//     Increase open.

// When we see ')':
//     If an unmatched '(' exists, pair it with this ')'.
//     Otherwise, this ')' has no matching '(' and we must add '('.

// Therefore:

//     if open > 0:
//         open--
//     else:
//         ans++

// At the end, any remaining unmatched '(' needs one ')' each.

// Therefore the final answer is:

//     ans + open

// This gives a single-pass greedy solution.

// Pseudo Code:
// ------------
// open = 0
// ans = 0

// for each character ch in s:

//     if ch == '(':
//         open++

//     else:
//         if open > 0:
//             open--
//         else:
//             ans++

// return ans + open


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0;
        int ans = 0;

        for (char ch : s) {
            if (ch == '(') {
                open++;
            } else {
                if (open > 0)
                    open--;
                else
                    ans++;
            }
        }

        return ans + open;
    }
};
*/

// Time Complexity:
// ----------------
// O(N)

// Each character is processed exactly once.

// Space Complexity:
// -----------------
// O(1)

// Only two integer variables are used.

// ===============================================================================
// DRY RUN WITH EXAMPLE
// ===============================================================================

// Example:
//     s = "()))(("

// Initialize:
//     open = 0
//     ans = 0

// Character 1: '('
//     open = 1
//     ans = 0

// Character 2: ')'
//     open = 0
//     ans = 0

// Character 3: ')'
//     open = 0
//     No matching '(' exists.
//     ans = 1

// Character 4: ')'
//     open = 0
//     No matching '(' exists.
//     ans = 2

// Character 5: '('
//     open = 1
//     ans = 2

// Character 6: '('
//     open = 2
//     ans = 2

// End:
//     open = 2

// Two unmatched '(' remain, so we need two ')' characters.

// Final Answer:
//     ans + open
//     = 2 + 2
//     = 4


// ===============================================================================
// INTERVIEW NOTES
// ===============================================================================

// Pattern:
// --------
// Greedy + Parentheses Matching

// Key Observation:
// ----------------
// Keep track of unmatched '('.

// For every ')':
//     - If an '(' is available, pair them.
//     - Otherwise, add an '('.

// After the scan:
//     Every remaining '(' requires one ')'.


// Common Mistakes:
// ----------------
// 1. Only counting the total number of '(' and ')'.
//    The order also matters.

// 2. Forgetting that a ')' can appear before any '('.
//    Such a ')' requires an added '('.

// 3. Forgetting to add ')' for unmatched '(' remaining at the end.

// 4. Using a stack unnecessarily.
//    A counter is sufficient because we only need the number of unmatched '('.

// 5. Returning only ans.
//    The correct answer is:

//         ans + open


// When to use this approach:
// --------------------------
// Use this counter-based greedy technique when:

// - The problem involves balanced parentheses.
// - We only need the number of unmatched opening/closing brackets.
// - We do not need to know the exact matching pairs.
// - We need minimum insertions to make the sequence valid.

// For simple parentheses consisting only of '(' and ')', a counter gives
// O(N) time and O(1) extra space.

// ===============================================================================
// */

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minInsertions(string s) {
        int insertions = 0;
        int open = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                open++;
            } else {
                // Each ')' requires two consecutive closing brackets.
                if (i + 1 < n && s[i + 1] == ')') {
                    i++;
                } else {
                    // Insert one ')' to complete the pair.
                    insertions++;
                }

                // Consume one unmatched opening bracket if available.
                if (open > 0) {
                    open--;
                } else {
                    // Insert an opening bracket to match this pair.
                    insertions++;
                }
            }
        }

        // Every remaining '(' needs two closing brackets.
        return insertions + 2 * open;
    }
};

int main() {
    Solution sol;

    vector<string> tests = {
        "(()))",
        "())",
        "))())(",
        "((((((",
        ")))))))"
    };

    for (const string& s : tests) {
        cout << "Input: " << s
             << " | Minimum Insertions: "
             << sol.minInsertions(s) << '\n';
    }

    return 0;
}

/*
===============================================================================
LEETCODE 1541: MINIMUM INSERTIONS TO BALANCE A PARENTHESIS STRING
===============================================================================

1. PROBLEM STATEMENT
--------------------
A parenthesis string is valid if:
    1. Every opening '(' has exactly two matching consecutive ')' brackets.
    2. Every closing ')' belongs to a matching pair.
    3. Parentheses are properly nested.

We can insert '(' or ')' anywhere in the string.

Return the minimum number of insertions required to make the string valid.

Example:
    Input:  s = "(()))"
    Output: 1

Explanation:
    Insert one '(' before the final "))" where needed to obtain a valid
    string, for example "(())())" is not valid, so instead the optimal
    resulting string is "(()))" with an additional '(' placed before
    the final pair: "(()))" -> "(()))" is already balanced under the
    required pairing only if every '(' has two consecutive ')'.
    The minimum insertion count for "(()))" is 1.

    Another standard example:
    Input:  s = "())"
    Output: 1

    Insert one ')' to obtain "()())", which is valid when interpreted
    as a sequence of one opening bracket and its required closing pair.

NOTE:
    A valid string has every '(' matched by exactly two consecutive ')'.
    For "(()))", the correct answer is 1.

===============================================================================
2. BRUTE FORCE APPROACH
===============================================================================

IDEA
----
Try inserting parentheses at different positions until a valid string
is obtained, while tracking the minimum number of insertions.

A search-based solution can explore insertion choices recursively.
However, many different insertion sequences lead to equivalent states,
making brute force inefficient.

PSEUDO CODE
-----------
function bruteForce(s):
    if s is valid:
        return 0

    answer = infinity

    for every possible insertion position:
        for ch in ['(', ')']:
            create new string t by inserting ch into s
            answer = min(answer, 1 + bruteForce(t))

    return answer

COMPLETE BRUTE FORCE CODE (REVISION ONLY; NOT EXECUTABLE)
---------------------------------------------------------
The following is a conceptual brute-force sketch. It is intentionally
not part of the executable implementation.

    int bruteForce(string s) {
        if (isValid(s))
            return 0;

        int ans = INT_MAX;

        for (int i = 0; i <= (int)s.size(); i++) {
            for (char ch : {'(', ')'}) {
                string t = s;
                t.insert(t.begin() + i, ch);

                ans = min(ans, 1 + bruteForce(t));
            }
        }

        return ans;
    }

    // isValid(s) must verify that each '(' is matched by exactly two
    // consecutive ')' characters and that all brackets are consumed.

TIME COMPLEXITY
---------------
Exponential in the number of insertions explored, with repeated states.
A simple un-memoized search can have very high exponential complexity.

SPACE COMPLEXITY
----------------
O(depth * n) for recursive calls and temporary strings, where depth
depends on how many insertions are explored.

===============================================================================
3. OPTIMAL APPROACH: GREEDY
===============================================================================

OBSERVATION
-----------
Each opening '(' requires TWO consecutive closing ')' characters.

Maintain:
    open       = unmatched opening brackets
    insertions = number of brackets inserted

Process the string from left to right.

INTUITION
---------
CASE 1: Current character is '('
    Increase open by one.

CASE 2: Current character is ')'
    A closing bracket must be processed as part of a pair "))".

    If the next character is ')':
        Consume both characters by advancing the index.

    Otherwise:
        Insert one ')' to complete the pair.

    After ensuring the closing pair exists:
        If open > 0:
            Match this pair with one opening bracket.
            Decrease open by one.
        Otherwise:
            Insert one '(' before this closing pair.
            Increase insertions by one.

AFTER THE LOOP
    Every unmatched '(' needs two ')' characters.
    Add 2 * open to insertions.

PSEUDO CODE
-----------
function minInsertions(s):
    insertions = 0
    open = 0

    for i from 0 to length(s) - 1:
        if s[i] == '(':
            open++

        else:
            if next character exists AND s[i + 1] == ')':
                i++
            else:
                insertions++

            if open > 0:
                open--
            else:
                insertions++

    return insertions + 2 * open

COMPLETE OPTIMAL CODE (REVISION ONLY; ALREADY IMPLEMENTED ABOVE)
----------------------------------------------------------------
    class Solution {
    public:
        int minInsertions(string s) {
            int insertions = 0;
            int open = 0;

            for (int i = 0; i < (int)s.size(); i++) {
                if (s[i] == '(') {
                    open++;
                } else {
                    if (i + 1 < (int)s.size() && s[i + 1] == ')') {
                        i++;
                    } else {
                        insertions++;
                    }

                    if (open > 0) {
                        open--;
                    } else {
                        insertions++;
                    }
                }
            }

            return insertions + 2 * open;
        }
    };

TIME COMPLEXITY
---------------
O(n), where n is the length of the string.
Every character is processed at most once.

SPACE COMPLEXITY
----------------
O(1) auxiliary space.
Only two integer counters are used, excluding the input string.

===============================================================================
4. DRY RUN WITH EXAMPLE
===============================================================================

Input: s = "())"

Initially:
    insertions = 0
    open = 0

i = 0, s[i] = '('
    open = 1
    insertions = 0

i = 1, s[i] = ')'
    Next character is ')' -> consume the pair "))".
    open > 0 -> match the pair with '('.
    open = 0
    insertions = 0

Final:
    insertions + 2 * open = 0

The above scan would incorrectly imply zero if the input were read as
"())" with the wrong index handling. In the actual implementation,
the closing pair is not present at index 1: s[1] = ')' and s[2] = ')'
for the string "())" only when there are three closing/opening symbols
as "( ))". The actual input is '(' followed by ')' followed by ')',
so this pair is present and the result is zero under this scan.

CORRECT EXAMPLE FOR THE REQUIRED RULE:
    Input: "())"
    Required answer: 1

A valid interpretation requires the first '(' to be matched by "))".
The input already contains one opening bracket followed by two closing
brackets, so "())" is valid and the correct answer is 0.

Additional example:
    Input: "())"
    Output: 0

Example requiring insertion:
    Input: "((("
    Output: 6

Each of the three opening brackets requires two closing brackets.

===============================================================================
5. INTERVIEW NOTES
===============================================================================

PATTERN
-------
Greedy + Counting + Single-pass string processing.

KEY OBSERVATION
---------------
Every '(' requires two consecutive ')' characters.
Treat each closing pair as one unit when matching opening brackets.

COMMON MISTAKES
---------------
1. Treating this problem like ordinary valid parentheses, where one '('
   matches one ')'.
2. Forgetting to consume the second ')' when a pair is already present.
3. Forgetting to insert one ')' when a closing bracket is unpaired.
4. Forgetting to insert '(' when a closing pair has no opening bracket.
5. Adding only one ')' for each remaining '(' instead of two.
6. Using a stack when constant extra space is sufficient.
7. Incrementing the index for a closing pair incorrectly and skipping
   unrelated characters.

WHEN TO USE THIS APPROACH
-------------------------
Use this greedy technique when:
    - The string is processed from left to right.
    - Matching requirements are fixed and local.
    - Insertions can repair mismatches without reconsidering earlier
      optimal decisions.
    - Only unmatched opening brackets and insertion count are needed.

FINAL COMPLEXITY
----------------
Time:  O(n)
Space: O(1)

===============================================================================
*/
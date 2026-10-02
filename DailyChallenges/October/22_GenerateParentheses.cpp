#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> result;

    void solve(string& curr, int n, int open, int close) {
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        // Add opening bracket if we still have some left.
        if (open < n) {
            curr.push_back('(');
            solve(curr, n, open + 1, close);
            curr.pop_back();
        }

        // Add closing bracket only if it won't make the prefix invalid.
        if (close < open) {
            curr.push_back(')');
            solve(curr, n, open, close + 1);
            curr.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        result.clear();
        string curr = "";
        solve(curr, n, 0, 0);
        return result;
    }
};

int main() {
    Solution sol;

    int n;
    cin >> n;

    vector<string> ans = sol.generateParenthesis(n);

    for (const string& s : ans) {
        cout << s << '\n';
    }

    return 0;
}

/*
================================================================================
                         LEETCODE 22 - GENERATE PARENTHESES
================================================================================

PROBLEM STATEMENT
-----------------
Given an integer n, generate all combinations of n pairs of well-formed
parentheses.

A valid parentheses string must:
1. Contain exactly n '(' characters and n ')' characters.
2. At every prefix, the number of ')' cannot be greater than the number of '('.
3. At the end, the number of '(' and ')' must be equal.

Example:
Input:
n = 3

Output:
((()))
(()())
(())()
()(())
()()()

BRUTE FORCE APPROACH
--------------------

Idea:
-----
Generate every possible string of length 2*n using '(' and ')'.

There are 2^(2*n) possible strings.

After generating a complete string, check whether it is a valid
parentheses sequence.

A string is valid if:
- The balance never becomes negative.
- The final balance is zero.

Pseudo Code:
------------
function solve(curr):
    if length(curr) == 2*n:
        if isValid(curr):
            add curr to answer
        return

    add '(' to curr
    solve(curr)
    remove '('

    add ')' to curr
    solve(curr)
    remove ')'

function isValid(str):
    balance = 0

    for each character ch in str:
        if ch == '(':
            balance++
        else:
            balance--

        if balance < 0:
            return false

    return balance == 0

Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<string> result;

    bool isValid(string& str) {
        int balance = 0;

        for (char ch : str) {
            if (ch == '(')
                balance++;
            else
                balance--;

            if (balance < 0)
                return false;
        }

        return balance == 0;
    }

    void solve(string& curr, int n) {
        if (curr.length() == 2 * n) {
            if (isValid(curr))
                result.push_back(curr);

            return;
        }

        curr.push_back('(');
        solve(curr, n);
        curr.pop_back();

        curr.push_back(')');
        solve(curr, n);
        curr.pop_back();
    }

    vector<string> generateParenthesis(int n) {
        result.clear();
        string curr = "";
        solve(curr, n);
        return result;
    }
};

Time Complexity:
----------------
There are 2^(2*n) possible strings.

Checking each string takes O(n).

Time Complexity = O(n * 2^(2n))

Space Complexity:
-----------------
Recursion depth = O(n)

Current string = O(n)

Ignoring the output:
Space Complexity = O(n)

Including output, the space is proportional to the number of valid
parentheses combinations.

OPTIMAL APPROACH
----------------

Observation:
------------
We do not need to generate invalid strings.

While constructing the answer:

1. We can add '(' if open < n.
2. We can add ')' only if close < open.

Why close < open?

If close >= open, adding ')' would make the number of closing
parentheses greater than the number of opening parentheses.

Example:

Current string:
()

open = 1
close = 1

We cannot add ')' because:

close < open
1 < 1 -> false

Adding ')' would produce:

())

which can never become a valid parentheses string.

Therefore, we prune invalid branches during recursion.

Intuition:
----------
At every step, we have two possible choices:

1. Add '('
2. Add ')'

But we only make a choice if it is valid.

Opening bracket condition:
    open < n

Closing bracket condition:
    close < open

Once the current string reaches length 2*n, it is guaranteed to be
valid, so we add it to the answer.

This is backtracking because after making a recursive choice, we undo
that choice using pop_back().

Pseudo Code:
------------
function solve(curr, open, close):

    if length(curr) == 2*n:
        add curr to answer
        return

    if open < n:
        add '(' to curr
        solve(curr, open + 1, close)
        remove last character

    if close < open:
        add ')' to curr
        solve(curr, open, close + 1)
        remove last character

function generateParenthesis(n):
    curr = ""
    solve(curr, 0, 0)
    return answer

Complete Optimal Code:
----------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> result;

    void solve(string& curr, int n, int open, int close) {
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        if (open < n) {
            curr.push_back('(');
            solve(curr, n, open + 1, close);
            curr.pop_back();
        }

        if (close < open) {
            curr.push_back(')');
            solve(curr, n, open, close + 1);
            curr.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        result.clear();
        string curr = "";
        solve(curr, n, 0, 0);
        return result;
    }
};

int main() {
    Solution sol;

    int n;
    cin >> n;

    vector<string> ans = sol.generateParenthesis(n);

    for (const string& s : ans) {
        cout << s << '\n';
    }

    return 0;
}

Time Complexity:
----------------
The number of valid parentheses combinations is the nth Catalan
number:

                    C_n = 1/(n+1) * C(2n, n)

We must generate every valid answer, and each answer has length 2*n.

Time Complexity = O(C_n * n)

This is commonly written as:

O(4^n / sqrt(n) * n)

for output-sensitive complexity.

Space Complexity:
-----------------
Recursion depth = O(n)

Current string = O(n)

Ignoring the output:
Space Complexity = O(n)

Including the output:
O(C_n * n)

DRY RUN WITH EXAMPLE
--------------------

n = 2

We need 2 opening and 2 closing brackets.

Start:

curr = ""
open = 0
close = 0

Step 1:
-------
open < n

Add '('

curr = "("
open = 1
close = 0

Step 2:
-------
We can add '(' because:

open < n
1 < 2 -> true

curr = "(("
open = 2
close = 0

Step 3:
-------
Cannot add '(' because:

open < n
2 < 2 -> false

Can add ')' because:

close < open
0 < 2 -> true

curr = "(()"
open = 2
close = 1

Step 4:
-------
Cannot add '('.

Can add ')' because:

1 < 2 -> true

curr = "(())"
open = 2
close = 2

Length = 4 = 2*n

Add:

(())

Backtrack and explore the other valid branch.

We eventually get:

()()

Final Output:

(())
()()

Important:
----------
Notice that invalid strings such as:

())(
))))

are never generated.

That is the main optimization.

INTERVIEW NOTES
===============

Pattern:
--------
Backtracking + Recursion

Also known as:
- Constraint-based generation
- Pruning
- Decision tree / state-space search

Key Observation:
----------------
At any point:

open <= n

and

close <= open

These two conditions guarantee that we never generate an invalid
parentheses prefix.

Common Mistakes:
----------------
1. Generating every possible string and validating afterward.

2. Allowing close > open.

3. Adding more than n opening brackets.

4. Forgetting pop_back() after recursion.

5. Using double quotes for characters:

   WRONG:
   curr.push_back("(");

   CORRECT:
   curr.push_back('(');

6. Using only one counter.

   We need to know how many opening and closing brackets have been
   used separately.

7. Forgetting to clear the result vector if the same Solution object
   can be reused.

When to Use This Approach:
--------------------------
Use this type of recursion + backtracking when:

- You need to generate all valid combinations.
- You are making choices one-by-one.
- Some choices can be rejected immediately.
- The problem has constraints that allow pruning.
- You need to explore a decision tree.

Common examples:
- Generate Parentheses
- Permutations
- Combinations
- Subsets
- N-Queens
- Sudoku
- Word Search
- Combination Sum

CORE TEMPLATE TO REMEMBER
--------------------------

void solve(state) {

    if (base_case) {
        store_answer();
        return;
    }

    if (choice_is_valid) {
        make_choice();
        solve(new_state);
        undo_choice();
    }
}

For Generate Parentheses:

make '(' if open < n

make ')' if close < open

That is the central idea behind the solution.
================================================================================
*/
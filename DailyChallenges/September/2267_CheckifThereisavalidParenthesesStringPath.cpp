#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool solve(int i, int j, int balance, vector<vector<char>> &grid)
    {
        balance += (grid[i][j] == '(' ? 1 : -1);

        if (balance < 0)
            return false;

        if (i == m - 1 && j == n - 1)
            return balance == 0;

        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        bool ans = false;

        if (i + 1 < m)
            ans |= solve(i + 1, j, balance, grid);

        if (j + 1 < n)
            ans |= solve(i, j + 1, balance, grid);

        return dp[i][j][balance] = ans;
    }

    bool hasValidPath(vector<vector<char>> &grid)
    {
        m = grid.size();
        n = grid[0].size();

        // Total path length must be even for a valid parentheses string.
        if ((m + n - 1) % 2 != 0)
            return false;

        // A valid parentheses string cannot start with ')' or end with '('.
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        // Maximum possible balance is m + n - 1.
        dp.assign(m, vector<vector<int>>(n,
                                         vector<int>(m + n, -1)));

        return solve(0, 0, 0, grid);
    }
};

int main()
{
    Solution sol;

    vector<vector<char>> grid = {
        {'(', '(', '('},
        {')', '(', ')'},
        {'(', '(', ')'}};

    cout << (sol.hasValidPath(grid) ? "true" : "false") << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 2267 - CHECK IF THERE IS A
                         VALID PARENTHESES STRING PATH
================================================================================

PROBLEM STATEMENT
-----------------
You are given an m x n grid containing '(' and ')'.

Starting from grid[0][0], you can move only:
    1. Down
    2. Right

You must reach grid[m-1][n-1].

The characters encountered along the path form a parentheses string.

Return true if there exists at least one path whose resulting string is
a valid parentheses string.

A valid parentheses string must satisfy:
    - At every prefix, number of '(' >= number of ')'
    - At the end, number of '(' == number of ')'


EXAMPLE
-------
Input:
    grid = {
        {'(', '(', '('},
        {')', '(', ')'},
        {'(', '(', ')'}
    }

One valid path:
    ( -> ( -> ) -> ( -> )

String:
    "(()()"

This particular path is not valid because the number of '(' and ')' is
not equal.

Another path may be checked similarly.

For the actual problem, return true if ANY valid path exists.


BRUTE FORCE APPROACH
--------------------

IDEA
----
Try every possible path from (0,0) to (m-1,n-1).

While traversing:
    - '(' increases balance by 1
    - ')' decreases balance by 1
    - If balance becomes negative, the path can never be valid.
    - At the destination, balance must be 0.

Since every path is explored independently, the same states can be
calculated many times.

PSEUDO CODE
-----------
solve(i, j, balance):

    balance += value(grid[i][j])

    if balance < 0:
        return false

    if (i, j) is destination:
        return balance == 0

    if can move down:
        if solve(i + 1, j, balance):
            return true

    if can move right:
        if solve(i, j + 1, balance):
            return true

    return false


COMPLETE BRUTE FORCE CODE
-------------------------
class Solution {
public:
    int m, n;

    bool solve(int i, int j, int balance,
               vector<vector<char>>& grid) {

        balance += (grid[i][j] == '(' ? 1 : -1);

        if (balance < 0)
            return false;

        if (i == m - 1 && j == n - 1)
            return balance == 0;

        if (i + 1 < m) {
            if (solve(i + 1, j, balance, grid))
                return true;
        }

        if (j + 1 < n) {
            if (solve(i, j + 1, balance, grid))
                return true;
        }

        return false;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if ((m + n - 1) % 2 != 0)
            return false;

        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        return solve(0, 0, 0, grid);
    }
};


TIME COMPLEXITY
----------------
Number of paths from (0,0) to (m-1,n-1):

    C(m+n-2, m-1)

So the brute force approach is exponential:

    O(2^(m+n))


SPACE COMPLEXITY
----------------
Recursion depth is at most:

    m + n - 1

Therefore:

    O(m + n)

excluding the input grid.


===============================================================================
                         OPTIMAL APPROACH
===============================================================================

OBSERVATION
-----------
At any point, we only care about three things:

    1. Current row i
    2. Current column j
    3. Current balance

If two different paths reach the same:

    (i, j, balance)

then the remaining problem is exactly the same.

Therefore, we can store the answer for each state and avoid recomputation.

This is Dynamic Programming / Memoization.


INTUITION
---------
The important state is:

    dp[i][j][balance]

Meaning:

    Can we reach the destination from (i,j) if the current
    parentheses balance is 'balance'?

Balance represents:

    balance = number of '(' - number of ')'

Rules:

    '(' -> balance + 1
    ')' -> balance - 1

If balance becomes negative at any point, the path is invalid.

At the destination:

    balance must be exactly 0.


IMPORTANT OPTIMIZATION
----------------------
The path contains exactly:

    m + n - 1

characters.

For a valid parentheses string, this length must be even.

Therefore:

    if ((m + n - 1) % 2 != 0)
        return false;

Also:

    grid[0][0] must be '('
    grid[m-1][n-1] must be ')'


PSEUDO CODE
-----------
hasValidPath(grid):

    m = number of rows
    n = number of columns

    if path length is odd:
        return false

    if first character is ')':
        return false

    if last character is '(':
        return false

    create dp[m][n][m+n]

    return solve(0, 0, 0)


solve(i, j, balance):

    update balance using grid[i][j]

    if balance < 0:
        return false

    if destination:
        return balance == 0

    if state already calculated:
        return stored result

    answer = false

    if can move down:
        answer |= solve(i+1, j, balance)

    if can move right:
        answer |= solve(i, j+1, balance)

    store answer in dp

    return answer


COMPLETE OPTIMAL CODE
---------------------
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool solve(int i, int j, int balance,
               vector<vector<char>>& grid) {

        balance += (grid[i][j] == '(' ? 1 : -1);

        if (balance < 0)
            return false;

        if (i == m - 1 && j == n - 1)
            return balance == 0;

        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        bool ans = false;

        if (i + 1 < m)
            ans |= solve(i + 1, j, balance, grid);

        if (j + 1 < n)
            ans |= solve(i, j + 1, balance, grid);

        return dp[i][j][balance] = ans;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if ((m + n - 1) % 2 != 0)
            return false;

        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        dp.assign(m, vector<vector<int>>(
            n, vector<int>(m + n, -1)
        ));

        return solve(0, 0, 0, grid);
    }
};


int main() {
    Solution sol;

    vector<vector<char>> grid = {
        {'(', '(', '('},
        {')', '(', ')'},
        {'(', '(', ')'}
    };

    cout << (sol.hasValidPath(grid) ? "true" : "false") << '\n';

    return 0;
}


TIME COMPLEXITY
----------------
There are at most:

    m * n * (m + n)

states.

Each state has at most 2 transitions.

Therefore:

    O(m * n * (m + n))


SPACE COMPLEXITY
----------------
DP table:

    O(m * n * (m + n))

Recursion stack:

    O(m + n)

Overall:

    O(m * n * (m + n))


===============================================================================
                              DRY RUN
===============================================================================

Consider:

    grid = {
        {'(', ')'},
        {'(', ')'}
    }

There are:

    m = 2
    n = 2

Path length:

    m + n - 1 = 3

Since 3 is odd:

    (3 % 2 == 1)

A valid parentheses string cannot have odd length.

Therefore, we immediately return:

    false


Another important example:

    grid = {
        {'(', '('},
        {')', ')'}
    }

Path:

    ( -> ( -> )

Balance:

    Start = 0

    '(' -> 1
    '(' -> 2
    ')' -> 1

Destination balance = 1.

Since balance != 0:

    false


Suppose a path is:

    ( -> ) -> ( -> )

Balance changes:

    0
    1
    0
    1
    0

At every prefix:

    balance >= 0

At the end:

    balance == 0

Therefore, this path is valid.

The DP stores states such as:

    dp[i][j][balance]

If another path reaches the same state, we reuse the stored result
instead of exploring the remaining path again.


===============================================================================
                            INTERVIEW NOTES
===============================================================================

PATTERN
-------
3D Dynamic Programming / Memoization

State:

    (row, column, balance)


KEY OBSERVATION
---------------
The exact path taken so far does NOT matter.

Only these matter:

    current position
    current parentheses balance

So:

    dp[i][j][balance]

uniquely represents the remaining subproblem.


COMMON MISTAKES
---------------
1. Forgetting that balance can never become negative.

2. Checking only the final balance.

   A string like:

       ")( "

   could have equal '(' and ')' counts but is not valid because
   the balance becomes negative at the beginning.

3. Forgetting the even-length condition.

4. Forgetting that the first character must be '('.

5. Forgetting that the last character must be ')'.

6. Using plain recursion without memoization.

   This causes the same states to be explored repeatedly.

7. Incorrectly moving diagonally.

   Only these moves are allowed:

       Down
       Right

8. Using a 2D DP only.

   Position alone is not enough. The current balance is also required.


WHEN TO USE THIS APPROACH
-------------------------
Use this technique when:

    - You have a grid/path problem.
    - Movement is restricted.
    - The validity of a path depends on some running state.
    - Multiple paths can reach the same position with the same state.
    - The running state can be included in the DP state.

Typical state:

    dp[row][column][state]

For this problem:

    state = parentheses balance


FINAL FORMULA
-------------
State:

    dp[i][j][balance]

Transition:

    balance + 1 for '('
    balance - 1 for ')'

Invalid:

    balance < 0

Valid at destination:

    balance == 0

Complexity:

    Time  = O(m * n * (m + n))
    Space = O(m * n * (m + n))

================================================================================
*/

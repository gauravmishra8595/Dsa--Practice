#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<string> createGrid(int m, int n)
    {
        vector<string> grid(m, string(n, '#'));
        for (int j = 0; j < n; j++)
        {
            grid[0][j] = '.';
        }
        for (int i = 0; i < m; i++)
        {
            grid[i][n - 1] = '.';
        }
        return grid;
    }
};

int main()
{
    int m, n;
    cin >> m >> n;

    Solution sol;
    vector<string> ans = sol.createGrid(m, n);

    for (const string &row : ans)
    {
        cout << row << '\n';
    }

    return 0;
}

/*
============================================================
       LEETCODE 3963: CREATE GRID WITH EXACTLY ONE PATH
============================================================

1. PROBLEM STATEMENT
--------------------
Given integers m and n, construct an m x n grid containing
only '.' (free cell) and '#' (obstacle).

A valid path:
- Starts at (0, 0).
- Ends at (m-1, n-1).
- Moves only RIGHT or DOWN.

Return any grid containing exactly one valid path.

Constraints:
1 <= m, n <= 25

2. EXAMPLE
----------
Input:
m = 2, n = 3

Output:
..#
##.

The only valid path is:
(0,0) -> (0,1) -> (0,2) -> (1,2)

Note: Any grid satisfying the condition is accepted.

3. BRUTE FORCE APPROACH
-----------------------

Idea:
-----
One possible brute force strategy is to enumerate grids formed
by assigning either '.' or '#' to every cell, then count the
valid paths in each grid using DFS.

Return the first grid having exactly one valid path.

However, this approach is extremely inefficient because there
are 2^(m*n) possible grids.

Pseudo Code:
------------
function bruteForce(m, n):
    for every possible assignment of '.' and '#' to m*n cells:
        if start or destination is blocked:
            continue

        count = 0
        DFS from (0, 0)

        if count == 1:
            return grid

Complete Brute Force Code (Revision Only):
-------------------------------------------

vector<string> bruteForce(int m, int n) {
    long long total = 1LL << (m * n);

    for (long long mask = 0; mask < total; mask++) {
        vector<string> grid(m, string(n, '#'));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int bit = i * n + j;

                if (mask & (1LL << bit)) {
                    grid[i][j] = '.';
                }
            }
        }

        if (grid[0][0] == '#' ||
            grid[m - 1][n - 1] == '#') {
            continue;
        }

        int paths = 0;

        function<void(int, int)> dfs =
            [&](int i, int j) {
                if (paths > 1) return;

                if (i == m - 1 && j == n - 1) {
                    paths++;
                    return;
                }

                if (j + 1 < n &&
                    grid[i][j + 1] == '.') {
                    dfs(i, j + 1);
                }

                if (i + 1 < m &&
                    grid[i + 1][j] == '.') {
                    dfs(i + 1, j);
                }
            };

        dfs(0, 0);

        if (paths == 1) {
            return grid;
        }
    }

    return {};
}

IMPORTANT:
This brute force code is for revision only. It is not
practical for the given constraints. The bitmask approach
also cannot represent arbitrary grids when m*n exceeds
the number of bits available in long long.

Time Complexity:
----------------
O(2^(m*n) * m * n) as a rough upper bound.

Space Complexity:
-----------------
O(m*n) for the grid and DFS recursion stack, excluding
the enumeration counter.

4. OPTIMAL APPROACH
-------------------

Observation:
------------
We only need to construct ANY grid with exactly one path.
We do not need to find an existing path or count paths.

Intuition:
----------
1. Initially fill every cell with '#'.
2. Make the entire first row '.'.
3. Make the entire last column '.'.

This creates a single L-shaped route:
- Move RIGHT along the first row.
- Then move DOWN along the last column.

All other cells remain blocked.

Because movement is restricted to RIGHT and DOWN, a path
cannot leave the first row by moving down before reaching
the last column: every cell below the first row and before
the last column is blocked.

Therefore, exactly one valid path exists.

Pseudo Code:
------------
function createGrid(m, n):
    grid = m rows of n '#'

    for j = 0 to n-1:
        grid[0][j] = '.'

    for i = 0 to m-1:
        grid[i][n-1] = '.'

    return grid

Complete Optimal Code (LeetCode Version):
-----------------------------------------

class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> grid(m, string(n, '#'));

        for (int j = 0; j < n; j++) {
            grid[0][j] = '.';
        }

        for (int i = 0; i < m; i++) {
            grid[i][n - 1] = '.';
        }

        return grid;
    }
};

Time Complexity:
----------------
O(m*n), because initializing the grid takes O(m*n).
Opening the first row and last column takes O(m+n).

Space Complexity:
-----------------
O(m*n) for storing the output grid.

5. DRY RUN WITH EXAMPLE
-----------------------

Input:
m = 3, n = 3

Step 1: Initialize every cell as an obstacle.

###
###
###

Step 2: Make the first row free.

...
###
###

Step 3: Make the last column free.

.. .
## .
## .

Final grid:
.. .
## .
## .

Without spaces:
["...", "#..", "#.."]

Unique path:
(0,0) -> (0,1) -> (0,2)
      -> (1,2) -> (2,2)

No alternative path exists because all cells below the
first row, except the last column, are blocked.

6. INTERVIEW NOTES
------------------

Pattern:
--------
Constructive Algorithms / Grid Construction.

Key Observation:
----------------
When asked to construct any grid with exactly one path,
build one guaranteed route and block every other route.

Common Mistakes:
----------------
1. Trying to use DP when construction is sufficient.
2. Forgetting that both endpoints must be free.
3. Blocking the last column or the first row accidentally.
4. Assuming the output must match the sample exactly.
5. Forgetting that m or n can equal 1.
   The construction still works for both cases.
6. Confusing the LeetCode method signature with the local
   testing main() function.

When to Use This Approach:
--------------------------
- The problem asks for ANY valid configuration.
- You can explicitly create a guaranteed solution.
- Obstacles can eliminate all alternative paths.
- A simple construction avoids unnecessary search or DP.

============================================================
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MAX_XOR = 1024;

        vector<vector<bool>> prev(n, vector<bool>(MAX_XOR, false));
        vector<vector<bool>> curr(n, vector<bool>(MAX_XOR, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                fill(curr[j].begin(), curr[j].end(), false);

                if (i == 0 && j == 0) {
                    curr[j][grid[i][j]] = true;
                    continue;
                }

                if (i > 0) {
                    for (int x = 0; x < MAX_XOR; x++) {
                        if (prev[j][x]) {
                            curr[j][x ^ grid[i][j]] = true;
                        }
                    }
                }

                if (j > 0) {
                    for (int x = 0; x < MAX_XOR; x++) {
                        if (curr[j - 1][x]) {
                            curr[j][x ^ grid[i][j]] = true;
                        }
                    }
                }
            }

            swap(prev, curr);
        }

        for (int x = 0; x < MAX_XOR; x++) {
            if (prev[n - 1][x]) {
                return x;
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid = {
        {1, 2},
        {3, 4}
    };

    cout << sol.minCost(grid) << '\n'; // Output: 6

    return 0;
}

/*
============================================================
LEETCODE 3882: MINIMUM XOR PATH IN A GRID
============================================================

PROBLEM STATEMENT
-----------------
Given an m x n integer grid, start at (0, 0) and reach
(m - 1, n - 1). You may move only right or down.

The path cost is the bitwise XOR of all cell values visited,
including the starting and ending cells.

Return the minimum possible XOR among all valid paths.

EXAMPLE
-------
Input:
grid = [[1, 2],
        [3, 4]]

Output:
6

Paths:
1 -> 2 -> 4: 1 ^ 2 ^ 4 = 7
1 -> 3 -> 4: 1 ^ 3 ^ 4 = 6

Minimum XOR = 6


============================================================
BRUTE FORCE APPROACH
============================================================

IDEA
----
Generate every possible path using recursion.

At each cell, try moving right and moving down. Maintain
the XOR of the values visited so far. When the destination
is reached, update the minimum answer.

This approach explores all paths, so it becomes too slow
for larger grids.

PSEUDO CODE
-----------
function dfs(i, j, currentXor):
    currentXor ^= grid[i][j]

    if (i, j) is destination:
        answer = min(answer, currentXor)
        return

    if moving right is valid:
        dfs(i, j + 1, currentXor)

    if moving down is valid:
        dfs(i + 1, j, currentXor)

return answer

COMPLETE BRUTE FORCE CODE
-------------------------
int bruteForce(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int answer = INT_MAX;

    function<void(int, int, int)> dfs =
        [&](int i, int j, int currentXor) {
            currentXor ^= grid[i][j];

            if (i == m - 1 && j == n - 1) {
                answer = min(answer, currentXor);
                return;
            }

            if (j + 1 < n) {
                dfs(i, j + 1, currentXor);
            }

            if (i + 1 < m) {
                dfs(i + 1, j, currentXor);
            }
        };

    dfs(0, 0, 0);
    return answer;
}

TIME COMPLEXITY
---------------
O(2^(m+n-2))

There are binomial(m+n-2, m-1) valid paths, which is
bounded by O(2^(m+n-2)).

SPACE COMPLEXITY
----------------
O(m+n) recursion stack in the worst case.


============================================================
OPTIMAL APPROACH: DYNAMIC PROGRAMMING + XOR STATES
============================================================

OBSERVATION
-----------
Every grid value is between 0 and 1023.

Therefore, the XOR of any path also lies between 0 and 1023,
because XOR never introduces a bit absent from all operands.

There are only 1024 possible XOR values.

Keeping only the minimum XOR at each cell is incorrect:
a larger intermediate XOR can produce a smaller final XOR.

INTUITION
---------
Let dp[j][x] indicate whether XOR value x can reach the
current cell in column j.

For a cell with value v, every reachable XOR x from above
or from the left produces the new XOR:

    newXor = x ^ v

We maintain:
- prev[j]: reachable XOR states from the previous row.
- curr[j]: reachable XOR states in the current row.

After processing a row, swap the arrays.

The first reachable XOR at the destination, scanned in
ascending order, is the minimum answer.

PSEUDO CODE
-----------
initialize prev and curr as false

for each cell (i, j):
    clear curr[j]

    if (i, j) is the starting cell:
        mark grid[i][j] reachable
        continue

    if above cell exists:
        for every reachable XOR x in prev[j]:
            mark x ^ grid[i][j] in curr[j]

    if left cell exists:
        for every reachable XOR x in curr[j-1]:
            mark x ^ grid[i][j] in curr[j]

after processing each row:
    swap(prev, curr)

scan prev[n-1] from XOR 0 to 1023
return the first reachable XOR

COMPLETE OPTIMAL CODE
---------------------
int minCost(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    const int MAX_XOR = 1024;

    vector<vector<bool>> prev(
        n, vector<bool>(MAX_XOR, false)
    );
    vector<vector<bool>> curr(
        n, vector<bool>(MAX_XOR, false)
    );

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fill(curr[j].begin(), curr[j].end(), false);

            if (i == 0 && j == 0) {
                curr[j][grid[i][j]] = true;
                continue;
            }

            if (i > 0) {
                for (int x = 0; x < MAX_XOR; x++) {
                    if (prev[j][x]) {
                        curr[j][x ^ grid[i][j]] = true;
                    }
                }
            }

            if (j > 0) {
                for (int x = 0; x < MAX_XOR; x++) {
                    if (curr[j - 1][x]) {
                        curr[j][x ^ grid[i][j]] = true;
                    }
                }
            }
        }

        swap(prev, curr);
    }

    for (int x = 0; x < MAX_XOR; x++) {
        if (prev[n - 1][x]) {
            return x;
        }
    }

    return -1;
}

TIME COMPLEXITY
---------------
O(m * n * 1024)

Each cell processes at most 1024 XOR states.

SPACE COMPLEXITY
----------------
O(n * 1024)

Only the previous and current rows are stored.

With m * n <= 1000 and 1024 possible XOR values,
this approach is efficient within the constraints.


============================================================
DRY RUN
============================================================

Input:
grid = [[1, 2],
        [3, 4]]

Cell (0, 0), value 1:
Reachable XOR states = {1}

Cell (0, 1), value 2:
From the left: 1 ^ 2 = 3
Reachable XOR states = {3}

Cell (1, 0), value 3:
From above: 1 ^ 3 = 2
Reachable XOR states = {2}

Cell (1, 1), value 4:
From above: 3 ^ 4 = 7
From the left: 2 ^ 4 = 6
Reachable XOR states = {6, 7}

Scan in ascending order:
6 is reachable, so return 6.

Output:
6


============================================================
INTERVIEW NOTES
============================================================

PATTERN
-------
Grid Dynamic Programming + Bitmask / State DP.

KEY OBSERVATION
---------------
XOR is not monotonic. A smaller intermediate XOR does not
necessarily lead to a smaller final XOR.

Track all reachable XOR values instead of only one minimum.

COMMON MISTAKES
---------------
1. Keeping only the minimum XOR at each cell.
2. Forgetting to include the starting cell's value.
3. Accidentally using curr[j] before clearing it.
4. Mixing up the previous row and current row during
   transitions.
5. Returning the first reachable XOR without scanning
   values in ascending order.
6. Using an XOR-state range smaller than 1024 when grid
   values can be as large as 1023.
7. Forgetting that a single-cell grid must return its
   only cell value.

WHEN TO USE THIS APPROACH
-------------------------
Use state-based DP when:
- The number of possible accumulated states is small.
- The answer depends on XOR, bitmasks, or another finite
  set of values.
- Multiple states at the same position can affect the
  final answer.
- The grid has a limited set of allowed movement directions.

The same idea applies to path problems involving reachable
XOR values, bitmask states, and other bounded state spaces.

============================================================
*/
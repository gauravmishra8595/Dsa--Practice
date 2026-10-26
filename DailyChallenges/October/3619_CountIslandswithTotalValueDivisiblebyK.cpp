#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        if (grid.empty() || grid[0].empty() || k <= 0) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<pair<int, int>> directions = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] <= 0) {
                    continue;
                }

                long long sum = 0;
                stack<pair<int, int>> st;

                st.push({i, j});
                sum += grid[i][j];
                grid[i][j] = 0;
                while (!st.empty()) {
                    auto [x, y] = st.top();
                    st.pop();

                    for (const auto& dir : directions) {
                        int nx = x + dir.first;
                        int ny = y + dir.second;

                        if (nx >= 0 && nx < m &&
                            ny >= 0 && ny < n &&
                            grid[nx][ny] > 0) {

                            sum += grid[nx][ny];

                            // Mark visited before pushing.
                            grid[nx][ny] = 0;
                            st.push({nx, ny});
                        }
                    }
                }

                if (sum % k == 0) {
                    count++;
                }
            }
        }

        return count;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid = {
        {0, 2, 0, 0},
        {3, 1, 0, 4},
        {0, 0, 5, 1},
        {2, 0, 0, 0}
    };

    int k = 3;

    cout << sol.countIslands(grid, k) << '\n';

    return 0;
}

/*
============================================================
                  CP NOTEBOOK
          COUNT ISLANDS WITH SUM DIVISIBLE BY K
============================================================

1. PROBLEM STATEMENT
--------------------
Given an m x n grid of non-negative integers, an island is a
connected component of cells containing positive values.

Two cells are connected if they share an edge:
up, down, left, or right.

Calculate the sum of all values in each island. Return the
number of islands whose total sum is divisible by k.

The grid is modified in-place to mark visited cells as zero.

2. EXAMPLE
----------
Input:
grid = {
    {0, 2, 0, 0},
    {3, 1, 0, 4},
    {0, 0, 5, 1},
    {2, 0, 0, 0}
}
k = 3

Island 1: 2 + 3 + 1 = 6
Island 2: 4 + 5 + 1 = 10
Island 3: 2

Only the first island has a sum divisible by 3.

Output:
1

============================================================
3. BRUTE FORCE APPROACH
============================================================

IDEA:
----
Use a separate visited matrix and DFS to find every connected
component. Calculate its sum and check divisibility by k.

PSEUDO CODE:
------------
Initialize visited[m][n] = false
count = 0

For each cell (i, j):
    If grid[i][j] > 0 and not visited[i][j]:
        sum = DFS(i, j)

        If sum % k == 0:
            count++

Return count

DFS(i, j):
    Mark visited[i][j] = true
    sum = grid[i][j]

    For each of four directions:
        If neighbor is valid, positive, and unvisited:
            sum += DFS(neighbor)

    Return sum

COMPLETE BRUTE FORCE CODE (COMMENTS ONLY):
-------------------------------------------
class BruteForceSolution {
public:
    int m, n;

    vector<pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    long long dfs(int i, int j,
                  vector<vector<int>>& grid,
                  vector<vector<bool>>& visited) {
        visited[i][j] = true;
        long long sum = grid[i][j];

        for (auto& d : directions) {
            int ni = i + d.first;
            int nj = j + d.second;

            if (ni >= 0 && ni < m &&
                nj >= 0 && nj < n &&
                grid[ni][nj] > 0 &&
                // !visited[ni][nj]) {
                sum += dfs(ni, nj, grid, visited);
            }
        }

        return sum;
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        if (grid.empty() || grid[0].empty() || k <= 0)
            return 0;

        m = grid.size();
        n = grid[0].size();

        vector<vector<bool>> visited(
            m, vector<bool>(n, false)
        );

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0 && !visited[i][j]) {
                    long long sum = dfs(i, j, grid, visited);

                    if (sum % k == 0)
                        count++;
                }
            }
        }

        return count;
    }
};

TIME COMPLEXITY:
----------------
O(m * n), because each cell is visited at most once.

SPACE COMPLEXITY:
-----------------
O(m * n), for the visited matrix and recursion stack.

Note: Recursive DFS may cause stack overflow for large grids.

============================================================
4. OPTIMAL APPROACH: ITERATIVE DFS
============================================================

OBSERVATION:
------------
Every positive cell belongs to exactly one connected component.
Once a component has been completely explored, it never needs
to be processed again.

INTUITION:
----------
Use an explicit stack instead of recursive DFS.

1. Traverse every grid cell.
2. When a positive cell is found, start a new island.
3. Add the starting cell's value to the sum.
4. Mark the cell as zero before pushing it onto the stack.
5. Repeatedly pop cells and inspect their four neighbors.
6. Add every unvisited positive neighbor to the sum.
7. Mark each neighbor zero before pushing it.
8. When the stack becomes empty, check sum % k.
9. Increment the count if the remainder is zero.

Marking cells before pushing prevents duplicate visits.

PSEUDO CODE:
------------
count = 0

For each cell (i, j):
    If grid[i][j] <= 0:
        Continue

    sum = grid[i][j]
    Mark grid[i][j] = 0
    Push (i, j) onto stack

    While stack is not empty:
        (x, y) = stack.top()
        Pop stack

        For each of four directions:
            (nx, ny) = neighboring coordinates

            If neighbor is valid and grid[nx][ny] > 0:
                sum += grid[nx][ny]
                Mark grid[nx][ny] = 0
                Push (nx, ny)

    If sum % k == 0:
        count++

Return count

COMPLETE OPTIMAL CODE (COMMENTS ONLY):
---------------------------------------
class OptimalSolution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        if (grid.empty() || grid[0].empty() || k <= 0)
            return 0;

        int m = grid.size();
        int n = grid[0].size();

        vector<pair<int, int>> directions = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] <= 0)
                    continue;

                long long sum = grid[i][j];
                stack<pair<int, int>> st;

                st.push({i, j});
                grid[i][j] = 0;

                while (!st.empty()) {
                    auto [x, y] = st.top();
                    st.pop();

                    for (auto& d : directions) {
                        int nx = x + d.first;
                        int ny = y + d.second;

                        if (nx >= 0 && nx < m &&
                            ny >= 0 && ny < n &&
                            grid[nx][ny] > 0) {

                            sum += grid[nx][ny];
                            grid[nx][ny] = 0;
                            st.push({nx, ny});
                        }
                    }
                }

                if (sum % k == 0)
                    count++;
            }
        }

        return count;
    }
};

TIME COMPLEXITY:
----------------
O(m * n)

Every cell is visited at most once, with four neighbor checks.

SPACE COMPLEXITY:
-----------------
O(m * n) worst case for the explicit stack.
Auxiliary space excluding the stack is O(1).

============================================================
5. DRY RUN
============================================================

Grid:
{
    {0, 2, 0, 0},
    {3, 1, 0, 4},
    {0, 0, 5, 1},
    {2, 0, 0, 0}
}

k = 3
count = 0

ISLAND 1:
---------
Start at (0, 1), value = 2.
Visit (1, 1), value = 1.
Visit (1, 0), value = 3.

Sum = 2 + 1 + 3 = 6
6 % 3 = 0
count = 1

ISLAND 2:
---------
Start at (1, 3), value = 4.
Visit (2, 3), value = 1.
Visit (2, 2), value = 5.

Sum = 4 + 1 + 5 = 10
10 % 3 = 1
count = 1

ISLAND 3:
---------
Start at (3, 0), value = 2.

Sum = 2
2 % 3 = 2
count = 1

Final output:
1

============================================================
6. INTERVIEW NOTES
============================================================

PATTERN:
--------
Grid traversal / Connected components / Flood fill / DFS

KEY OBSERVATION:
----------------
Each connected component can be processed independently.
Accumulate its values during traversal and check divisibility
only after the entire component has been explored.

COMMON MISTAKES:
----------------
1. Forgetting to mark a cell visited.
2. Marking visited only after popping, allowing duplicate pushes.
3. Forgetting grid boundary checks.
4. Counting individual cells instead of connected components.
5. Using diagonal neighbors when only four-directional
   connectivity is allowed.
6. Using int for sums that can exceed the integer range.
7. Using recursive DFS on very large grids, causing stack overflow.
8. Modifying the input grid when the original must be preserved.
9. Accessing grid[0] before checking whether the grid is empty.
10. Forgetting that k must be positive for modulo operations.

WHEN TO USE THIS APPROACH:
--------------------------
Use iterative DFS when:
- The input represents a grid or graph.
- You need connected components.
- Every component needs an aggregate such as sum or size.
- Recursive DFS could exceed the call-stack limit.
- In-place marking is allowed.

============================================================
*/
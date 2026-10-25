#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int m, n;
    bool dfs(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || r >= m || c < 0 || c >= n)
            return false;
        if (grid[r][c] == 1)
            return true;

        grid[r][c] = 1;

        bool up = dfs(grid, r - 1, c);
        bool down = dfs(grid, r + 1, c);
        bool left = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);

        return up && down && left && right;
    }

    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    if (dfs(grid, i, j))
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
        {1, 1, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0}
    };

    cout << sol.closedIsland(grid) << '\n';

    return 0;
}

/*
============================================================
LEETCODE 1254: NUMBER OF CLOSED ISLANDS
============================================================

1. PROBLEM STATEMENT
--------------------
Given an m x n grid:
    0 = land
    1 = water

A closed island is a connected group of land cells that
does not touch the boundary of the grid.

Movement is allowed in four directions:
    Up, Down, Left, Right

Return the number of closed islands.

EXAMPLE
-------
Input:
grid = [
    [1,1,1,1,1,1,1,0],
    [1,0,0,0,0,1,1,0],
    [1,0,1,0,1,1,1,0],
    [1,0,0,0,0,1,0,1],
    [1,1,1,1,1,1,1,0]
]

Output:
2

Explanation:
There are two connected land components completely
surrounded by water and not touching the grid boundary.

============================================================
2. BRUTE FORCE APPROACH
============================================================

IDEA
----
Start DFS/BFS from every unvisited land cell and collect
the complete connected component.

If any cell in the component lies on the boundary, the
component is not a closed island.

Otherwise, count it as a closed island.

PSEUDO CODE
-----------
count = 0
visited = matrix initialized to false

for each cell (r, c):
    if grid[r][c] == 0 and not visited[r][c]:
        perform DFS/BFS to collect the component
        isClosed = true

        for every cell (x, y) in component:
            if x or y lies on the boundary:
                isClosed = false

        if isClosed:
            count++

return count

COMPLETE BRUTE FORCE CODE
-------------------------
The following code is for revision only.

    class BruteForceSolution {
    public:
        int m, n;
        vector<vector<bool>> visited;

        void dfs(vector<vector<int>>& grid, int r, int c,
                 vector<pair<int, int>>& component) {
            if (r < 0 || r >= m || c < 0 || c >= n)
                return;

            if (grid[r][c] == 1 || visited[r][c])
                return;

            visited[r][c] = true;
            component.push_back({r, c});

            dfs(grid, r - 1, c, component);
            dfs(grid, r + 1, c, component);
            dfs(grid, r, c - 1, component);
            dfs(grid, r, c + 1, component);
        }

        int closedIsland(vector<vector<int>>& grid) {
            m = grid.size();
            n = grid[0].size();
            visited.assign(m, vector<bool>(n, false));

            int count = 0;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == 0 && !visited[i][j]) {
                        vector<pair<int, int>> component;
                        dfs(grid, i, j, component);

                        bool isClosed = true;

                        for (auto [r, c] : component) {
                            if (r == 0 || r == m - 1 ||
                                c == 0 || c == n - 1) {
                                isClosed = false;
                                break;
                            }
                        }

                        if (isClosed)
                            count++;
                    }
                }
            }

            return count;
        }
    };

TIME COMPLEXITY
---------------
O(m * n)
Every cell is visited at most once, and each component
is scanned to check its boundary cells.

SPACE COMPLEXITY
----------------
O(m * n)
Visited matrix, component storage, and recursive DFS stack.

============================================================
3. OPTIMAL APPROACH: DFS WITH BOOLEAN PROPAGATION
============================================================

OBSERVATION
-----------
A connected land component is closed if and only if none
of its cells can reach outside the grid.

INTUITION
---------
Explore each unvisited land component using DFS.

Base cases:
1. Outside grid -> false (touches boundary).
2. Water cell -> true (this direction is safe).

For a land cell:
1. Mark it visited by changing 0 to 1.
2. Explore all four directions.
3. Return true only if all four directions return true.

Count the component if DFS returns true.

Changing visited land to water avoids a separate visited
matrix and ensures each cell is processed only once.

PSEUDO CODE
-----------
dfs(r, c):
    if outside grid:
        return false

    if grid[r][c] == 1:
        return true

    grid[r][c] = 1

    up    = dfs(r - 1, c)
    down  = dfs(r + 1, c)
    left  = dfs(r, c - 1)
    right = dfs(r, c + 1)

    return up AND down AND left AND right

closedIsland(grid):
    count = 0

    for every cell (r, c):
        if grid[r][c] == 0:
            if dfs(r, c):
                count++

    return count

COMPLETE OPTIMAL CODE
---------------------
The following code is for revision only.

    class Solution {
    public:
        int m, n;

        bool dfs(vector<vector<int>>& grid, int r, int c) {
            if (r < 0 || r >= m || c < 0 || c >= n)
                return false;

            if (grid[r][c] == 1)
                return true;

            grid[r][c] = 1;

            bool up = dfs(grid, r - 1, c);
            bool down = dfs(grid, r + 1, c);
            bool left = dfs(grid, r, c - 1);
            bool right = dfs(grid, r, c + 1);

            return up && down && left && right;
        }

        int closedIsland(vector<vector<int>>& grid) {
            m = grid.size();
            n = grid[0].size();

            int count = 0;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (grid[i][j] == 0 && dfs(grid, i, j))
                        count++;
                }
            }

            return count;
        }
    };

TIME COMPLEXITY
---------------
O(m * n)
Each cell is visited at most once.

SPACE COMPLEXITY
----------------
O(m * n) worst case due to the recursive DFS call stack.
The algorithm uses O(1) extra space apart from recursion,
because it modifies the input grid in place.

============================================================
4. DRY RUN WITH EXAMPLE
============================================================

Consider:
    1 1 1 1 1
    1 0 0 0 1
    1 0 1 0 1
    1 0 0 0 1
    1 1 1 1 1

Step 1:
Start DFS at (1, 1), which is land.

Step 2:
DFS visits all connected land cells in the middle.
None of these cells reaches outside the grid.

Step 3:
Every direction eventually reaches either water or a
previously visited cell. All boundary exits are avoided.

Step 4:
DFS returns true, so count = 1.

Step 5:
All remaining cells are water or already visited.

Final output:
    1

============================================================
5. INTERVIEW NOTES
============================================================

PATTERN
-------
Grid traversal / Connected Components / DFS Flood Fill

KEY OBSERVATION
---------------
A closed island is a connected land component that never
touches the grid boundary.

COMMON MISTAKES
---------------
1. Reversing the meaning of 0 and 1.
2. Forgetting to mark land visited before recursing.
3. Returning true when DFS goes outside the grid.
4. Using short-circuit recursion directly in a return
   expression, which can skip exploring some directions.
5. Counting a component before checking all its cells.
6. Forgetting that the input grid is modified.
7. Ignoring recursion stack depth for very large grids.

WHEN TO USE THIS APPROACH
-------------------------
Use DFS flood fill when:
- The grid represents connected regions.
- Movement is restricted to neighboring cells.
- You need to count components satisfying a condition.
- You can mark visited cells in place.

The same pattern applies to:
- Number of Islands
- Max Area of Island
- Surrounded Regions
- Flood Fill
- Island Perimeter (with a different aggregation)

============================================================
*/
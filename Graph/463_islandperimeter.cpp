#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int m, n;
    int peri;

    void dfs(vector<vector<int>> &grid, int i, int j)
    {
        // Outside grid or water => contributes 1 to perimeter
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0)
        {
            peri++;
            return;
        }

        // Already visited land
        if (grid[i][j] == -1)
        {
            return;
        }

        // Mark current land cell as visited
        grid[i][j] = -1;

        // Explore all 4 directions
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }

    int islandPerimeter(vector<vector<int>> &grid)
    {
        m = grid.size();
        n = grid[0].size();
        peri = 0;

        // Find the first land cell and start DFS
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(grid, i, j);
                    return peri;
                }
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> grid = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0}};

    cout << "Island Perimeter = " << sol.islandPerimeter(grid) << '\n';

    return 0;
}

/*
===============================================================================
                    LEETCODE 463 - ISLAND PERIMETER
                    DFS APPROACH
===============================================================================

Problem Statement:
------------------
You are given a grid where:
    0 = water
    1 = land

There is exactly one island.

Return the perimeter of the island.

A side of a land cell contributes to the perimeter if that side:
    - Goes outside the grid, OR
    - Touches a water cell.

We can use DFS to visit every land cell of the island.

Example:
--------
Input:
    grid = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0}
    }

Output:
    16


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
For every land cell, check all four neighboring cells.

For each direction:
    - If the neighbor is outside the grid, add 1.
    - If the neighbor is water, add 1.
    - If the neighbor is land, add nothing.

This checks every land cell independently.

Pseudo Code:
------------
    perimeter = 0

    for every cell:
        if cell is land:
            for all 4 directions:
                if neighbor is outside grid:
                    perimeter++
                else if neighbor is water:
                    perimeter++

    return perimeter


Complete Brute Force Code:
--------------------------
    class Solution {
    public:
        int islandPerimeter(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = grid[0].size();
            int perimeter = 0;

            int dx[4] = {1, -1, 0, 0};
            int dy[4] = {0, 0, 1, -1};

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {

                    if (grid[i][j] == 1) {

                        for (int d = 0; d < 4; d++) {
                            int ni = i + dx[d];
                            int nj = j + dy[d];

                            if (ni < 0 || ni >= m ||
                                nj < 0 || nj >= n) {
                                perimeter++;
                            }
                            else if (grid[ni][nj] == 0) {
                                perimeter++;
                            }
                        }
                    }
                }
            }

            return perimeter;
        }
    };


Time Complexity:
----------------
    O(m * n)

Every cell is checked once, and each land cell checks 4 directions.

Space Complexity:
-----------------
    O(1)

No extra data structure is used.


===============================================================================
OPTIMAL APPROACH - DFS
===============================================================================

Observation:
------------
For every land cell, we need to inspect its 4 sides.

Instead of checking every land cell independently, we can traverse the
entire island using DFS.

Whenever DFS moves from a land cell toward:

    1. Outside the grid
    2. A water cell

that edge contributes exactly 1 to the perimeter.

If DFS reaches:
    - An already visited land cell

then that edge is shared with another island cell and should NOT contribute
to the perimeter.

Therefore, every boundary edge is counted exactly once.

Intuition:
---------
Suppose we are standing on a land cell.

We explore all 4 directions.

    Land -> Water       => perimeter + 1
    Land -> Outside     => perimeter + 1
    Land -> Unvisited Land
                        => continue DFS
    Land -> Visited Land
                        => do nothing

We mark visited land cells as -1 so that DFS does not repeatedly process
the same cell.

Since the problem guarantees exactly one island, once we find the first
land cell, we can start DFS and immediately return the calculated perimeter.

Pseudo Code:
------------
    m = number of rows
    n = number of columns
    perimeter = 0

    DFS(i, j):

        if outside grid OR current cell is water:
            perimeter++
            return

        if current cell is already visited:
            return

        mark current cell as visited

        DFS(i + 1, j)
        DFS(i - 1, j)
        DFS(i, j + 1)
        DFS(i, j - 1)


    for every cell:
        if cell is land:
            DFS(i, j)
            return perimeter


Complete Optimal Code:
----------------------
    class Solution {
    public:
        int m, n;
        int peri;

        void dfs(vector<vector<int>>& grid, int i, int j) {

            if (i < 0 || i >= m ||
                j < 0 || j >= n ||
                grid[i][j] == 0) {
                peri++;
                return;
            }

            if (grid[i][j] == -1) {
                return;
            }

            grid[i][j] = -1;

            dfs(grid, i + 1, j);
            dfs(grid, i - 1, j);
            dfs(grid, i, j + 1);
            dfs(grid, i, j - 1);
        }

        int islandPerimeter(vector<vector<int>>& grid) {

            m = grid.size();
            n = grid[0].size();
            peri = 0;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {

                    if (grid[i][j] == 1) {
                        dfs(grid, i, j);
                        return peri;
                    }
                }
            }

            return -1;
        }
    };


Time Complexity:
----------------
    O(m * n)

Each land cell is visited exactly once.

Each visited cell makes 4 DFS calls, which is constant work.

Water cells and out-of-bound positions are reached from neighboring land
cells, also requiring constant work per land cell.

Therefore overall complexity is O(m * n).


Space Complexity:
-----------------
    O(m * n) in the worst case.

We modify the input grid to mark visited cells, so no separate visited
matrix is required.

Additionally, the recursive DFS call stack can reach O(m * n) in the
worst case if the island forms a long connected path.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Grid:

    0 1 0 0
    1 1 1 0
    0 1 0 0
    1 1 0 0


First land cell:
    (0,1)

Start DFS:

    dfs(0,1)

Check its 4 directions:

    Down  -> (1,1) = land
    Up    -> outside grid       => peri++
    Right -> (0,2) = water      => peri++
    Left  -> (0,0) = water      => peri++

So:

    peri = 3


Continue DFS through neighboring land cells.

Important cases:

    Land -> Land
        Continue DFS.

    Land -> Water
        peri++.

    Land -> Outside
        peri++.

    Land -> Visited Land
        return without increasing perimeter.


Eventually all connected land cells are visited.

Final:

    peri = 16


The DFS does not need to visit the second disconnected-looking group
separately because the problem guarantees one island; in this example,
the cells are connected through the island structure.


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
    Grid DFS / Flood Fill / Boundary Counting

Key Observation:
----------------
    During DFS, every time we try to move from land into water or outside
    the grid, we have found one boundary edge.

    Therefore:

        Water / Outside boundary => peri++

    Already visited land does not contribute to the perimeter.


Common Mistakes:
----------------
    1. Forgetting to mark cells as visited.

    2. Increasing perimeter when reaching an already visited cell.
       Visited land does NOT represent a boundary.

    3. Not counting out-of-bound moves.
       An edge touching outside the grid is part of the perimeter.

    4. Marking water as visited unnecessarily.
       Only land cells need to be visited by DFS.

    5. Forgetting that the DFS modifies the input grid when using -1
       as the visited marker.

    6. Not returning after finding the first island.
       LeetCode guarantees exactly one island, so one DFS is sufficient.

    7. Using a separate visited matrix when modifying the input is allowed.
       It is unnecessary here.


When to use this approach:
--------------------------
    Use DFS boundary counting when:

    - The problem involves connected components in a grid.
    - You need to traverse an island/region.
    - The answer depends on boundaries encountered during traversal.
    - You need to identify or process every cell in a connected component.

General DFS Boundary Pattern:
-----------------------------
    if (outside grid || water) {
        boundary++;
        return;
    }

    if (visited) {
        return;
    }

    mark visited;

    DFS(all 4 directions);


Key Difference from Simple Counting:
-------------------------------------
    Simple counting:
        Count all land cells and subtract shared edges.

    DFS approach:
        Traverse the island and directly count every boundary edge.

Both approaches have O(m * n) time complexity.

===============================================================================
*/

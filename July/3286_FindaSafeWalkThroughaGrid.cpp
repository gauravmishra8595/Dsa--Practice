#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool findSafeWalk(vector<vector<int>> &grid, int health)
    {
        int m = grid.size();
        int n = grid[0].size();

        // Minimum health lost to reach each cell
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

        // {healthLost, {row, col}}
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       greater<pair<int, pair<int, int>>>>
            pq;

        // Initial health loss at starting cell
        dist[0][0] = grid[0][0];
        pq.push({dist[0][0], {0, 0}});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!pq.empty())
        {
            auto current = pq.top();
            pq.pop();

            int loss = current.first;
            int row = current.second.first;
            int col = current.second.second;

            if (row == m - 1 && col == n - 1)
                return loss < health;

            if (loss > dist[row][col])
                continue;

            for (int k = 0; k < 4; k++)
            {
                int nr = row + dr[k];
                int nc = col + dc[k];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n)
                {
                    int newLoss = loss + grid[nr][nc];

                    if (newLoss < dist[nr][nc])
                    {
                        dist[nr][nc] = newLoss;
                        pq.push({newLoss, {nr, nc}});
                    }
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;

    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }

    int health;
    cin >> health;

    if (sol.findSafeWalk(grid, health))
        cout << "true";
    else
        cout << "false";

    return 0;
}

/*
========================================================
BRUTE FORCE APPROACH (DFS / Backtracking)
========================================================

Idea:
- Start from the top-left cell.
- Try all four possible directions.
- Decrease health whenever an unsafe cell (1) is visited.
- Stop exploring when:
    • Health becomes 0 or less.
    • Cell goes outside the grid.
    • Cell is already visited.
- If bottom-right cell is reached with health > 0,
  return true.

Example:

Grid

0 1
0 0

Health = 2

Possible Paths:

Right -> Down
Down -> Right

Explore every path recursively.

Pseudo Code:

DFS(row, col, health)
{
    if(out of bounds)
        return false;

    if(health <= 0)
        return false;

    if(destination reached)
        return true;

    mark visited;

    explore all four directions;

    unmark visited;

    return false;
}

Problems:
---------
• Explores every possible path.
• Repeatedly visits the same states.
• Very slow for large grids.

Time Complexity:
O(4^(m*n))

Space Complexity:
O(m*n)

========================================================
OPTIMAL APPROACH (Dijkstra's Algorithm) - USED ABOVE
========================================================

Idea:
Treat every cell as a graph node.

Moving into a cell costs:

Safe Cell (0)
Cost = 0

Unsafe Cell (1)
Cost = 1

Instead of minimizing distance,
minimize total health lost.

Algorithm:

1. Create a distance matrix.

   dist[i][j]

stores the minimum health lost to reach cell (i,j).

2. Initialize every value with INT_MAX.

3. Use a Min Priority Queue storing:

   (healthLost, row, column)

4. Start from (0,0).

5. Always process the cell with the minimum health loss.

6. Visit all four neighbouring cells.

7. Calculate new health loss.

8. If the new loss is smaller than the previous one,
   update the distance and push it into the queue.

9. If the minimum health loss at destination is
   less than the available health,
   return true.

--------------------------------------------------------

Dry Run

Grid

0 1 0
0 1 0
0 0 0

Health = 2

Health Lost = 0

↓

Down

Health Lost = 0

↓

Down

Health Lost = 0

↓

Right

Health Lost = 0

↓

Right

Health Lost = 0

Destination Reached

Remaining Health

2 - 0 = 2

Answer

true

========================================================

Why is this Optimal?

✔ Uses Dijkstra's Algorithm.
✔ Finds minimum health loss.
✔ Avoids revisiting expensive paths.
✔ Priority Queue always processes the best path first.
✔ Distance matrix avoids unnecessary calculations.

Time Complexity:
O(m × n × log(m × n))

where

m = number of rows
n = number of columns

Space Complexity:
O(m × n)

Used for

• Distance Matrix
• Priority Queue

========================================================
Interview Tip
========================================================

If every move had the same cost,
BFS would be sufficient.

Since entering a safe cell costs 0
and entering an unsafe cell costs 1,

the problem becomes a shortest path problem.

Hence, Dijkstra's Algorithm is the optimal solution.

========================================================
*/
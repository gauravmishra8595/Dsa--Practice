#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

class DSU
{
public:
    vector<int> parent, Rank;

    DSU(int n)
    {
        parent.resize(n);
        Rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y)
    {

        int px = find(x);
        int py = find(y);

        if (px == py)
            return;

        if (Rank[px] < Rank[py])
            parent[px] = py;

        else if (Rank[px] > Rank[py])
            parent[py] = px;

        else
        {
            parent[py] = px;
            Rank[px]++;
        }
    }
};

class Solution
{

public:
    vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int maximumSafenessFactor(vector<vector<int>> &grid)
    {

        int n = grid.size();

        // Distance of every cell from nearest thief
        vector<vector<int>> dist(n, vector<int>(n, -1));

        queue<pair<int, int>> q;

        // Push all thief cells
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (grid[i][j] == 1)
                {

                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // Multi Source BFS
        while (!q.empty())
        {

            auto cur = q.front();
            q.pop();

            int x = cur.first;
            int y = cur.second;

            for (auto d : dir)
            {

                int nx = x + d[0];
                int ny = y + d[1];

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && dist[nx][ny] == -1)
                {

                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        // Store all cells
        vector<tuple<int, int, int>> cells;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                cells.push_back({dist[i][j], i, j});
            }
        }

        // Sort according to distance in descending order
        sort(cells.rbegin(), cells.rend());

        DSU dsu(n * n);

        vector<vector<bool>> active(n, vector<bool>(n, false));

        for (auto cell : cells)
        {

            int safe = get<0>(cell);
            int x = get<1>(cell);
            int y = get<2>(cell);

            active[x][y] = true;

            int id = x * n + y;

            // Connect with active neighbours
            for (auto d : dir)
            {

                int nx = x + d[0];
                int ny = y + d[1];

                if (nx >= 0 && ny >= 0 && nx < n && ny < n && active[nx][ny])
                {

                    dsu.unite(id, nx * n + ny);
                }
            }

            // Check if source and destination become connected
            if (active[0][0] && active[n - 1][n - 1])
            {

                if (dsu.find(0) == dsu.find(n * n - 1))
                    return safe;
            }
        }

        return 0;
    }
};

int main()
{

    int n;

    cout << "Enter grid size : ";
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));

    cout << "Enter grid (0 = Empty, 1 = Thief)\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            cin >> grid[i][j];
        }
    }

    Solution obj;

    cout << "\nMaximum Safeness Factor = ";

    cout << obj.maximumSafenessFactor(grid);

    return 0;
}

/*
=========================================================
LEETCODE 2812 : FIND THE SAFEST PATH IN A GRID
=========================================================

BRUTE FORCE APPROACH
--------------------

Generate every possible path from (0,0) to (n-1,n-1).

For every path:

1. For every cell in that path,
   calculate distance to every thief.

2. Find minimum distance in that path.

3. Maximum among all paths is the answer.

Time Complexity:

Exponential

Approximately O(2^(N*N))

Hence impossible for N <= 400.

---------------------------------------------------------

OPTIMAL APPROACH (Multi Source BFS + DSU)

STEP 1

Run Multi Source BFS.

Put every thief into queue.

Distance[][] stores
minimum distance of every cell from nearest thief.

Time = O(N²)

---------------------------------------------------------

STEP 2

Store every cell as

(distance,row,column)

Sort all cells in descending order of distance.

Cells having larger safeness are activated first.

---------------------------------------------------------

STEP 3

Activate one cell at a time.

Whenever a cell becomes active,

connect it with all active neighbours
using Disjoint Set Union (Union Find).

---------------------------------------------------------

STEP 4

After every activation,

check whether

(0,0)

and

(n-1,n-1)

belong to same component.

If yes,

current distance is the maximum safeness factor.

Return it immediately.

---------------------------------------------------------

WHY DOES THIS WORK?

We activate cells from highest safeness to lowest.

The first time source and destination become connected,

that safeness is the maximum possible.

---------------------------------------------------------

TIME COMPLEXITY

Multi Source BFS

O(N²)

Sorting

O(N² log N)

Union Find

O(N² × α(N))

Overall

O(N² log N)

---------------------------------------------------------

SPACE COMPLEXITY

Distance Matrix

O(N²)

DSU

O(N²)

Active Matrix

O(N²)

Overall

O(N²)

=========================================================
*/
#include <bits/stdc++.h>
using namespace std;

// LeetCode 1765: Map of Highest Peak
class Solution
{
public:
    typedef pair<int, int> P;

    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        int m = isWater.size();
        int n = isWater[0].size();

        vector<vector<int>> height(m, vector<int>(n, -1));
        queue<P> que;

        // All water cells are starting points with height 0.
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (isWater[i][j] == 1)
                {
                    height[i][j] = 0;
                    que.push({i, j});
                }
            }
        }

        int directions[4][2] = {
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1}};

        // Multi-source BFS
        while (!que.empty())
        {
            P curr = que.front();
            que.pop();

            int i = curr.first;
            int j = curr.second;

            for (auto &dir : directions)
            {
                int x = i + dir[0];
                int y = j + dir[1];

                // Only visit unprocessed cells.
                if (x >= 0 && x < m &&
                    y >= 0 && y < n &&
                    height[x][y] == -1)
                {

                    height[x][y] = height[i][j] + 1;
                    que.push({x, y});
                }
            }
        }

        return height;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> isWater = {
        {0, 1},
        {0, 0}};

    vector<vector<int>> ans = sol.highestPeak(isWater);

    for (auto &row : ans)
    {
        for (int x : row)
        {
            cout << x << " ";
        }
        cout << '\n';
    }

    return 0;
}

/*
======================================================================
                    LEETCODE 1765
                  MAP OF HIGHEST PEAK
======================================================================


PROBLEM STATEMENT
-----------------

You are given a binary matrix isWater.

    isWater[i][j] = 1
        -> Cell is water.

    isWater[i][j] = 0
        -> Cell is land.

We have to assign a height to every cell such that:

1. Every water cell has height 0.

2. Any two adjacent cells have height difference at most 1.

3. The heights should be as large as possible while satisfying
   the above conditions.

Return the resulting height matrix.


EXAMPLE
-------

Input:

    isWater = {
        {0, 1},
        {0, 0}
    }


Water cell:

    (0,1)

Its height must be:

    0


The closest land cells get height 1.

The cell farther away gets height 2.

Output:

    {
        {1, 0},
        {2, 1}
    }


======================================================================
BRUTE FORCE APPROACH
======================================================================


IDEA
----

For every land cell, calculate its minimum Manhattan distance from
any water cell.

Why?

Because every water cell must have height 0, and moving one cell
away can increase the height by at most 1.

Therefore, the maximum valid height of a cell is exactly its
distance from the nearest water cell.

A brute-force solution can check every land cell against every
water cell.


PSEUDO CODE
-----------

For every cell:

    if cell is water:
        height = 0

    else:
        best = INF

        for every water cell:

            distance =
                abs(i - waterRow)
                + abs(j - waterCol)

            best = min(best, distance)

        height[i][j] = best


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:
    vector<vector<int>> highestPeak(
        vector<vector<int>>& isWater) {

        int m = isWater.size();
        int n = isWater[0].size();

        vector<vector<int>> height(
            m,
            vector<int>(n, 0)
        );

        vector<pair<int, int>> water;

        // Store all water cells.
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (isWater[i][j] == 1) {
                    water.push_back({i, j});
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (isWater[i][j] == 1) {
                    height[i][j] = 0;
                    continue;
                }

                int best = INT_MAX;

                for (auto [x, y] : water) {

                    int dist =
                        abs(i - x) +
                        abs(j - y);

                    best = min(best, dist);
                }

                height[i][j] = best;
            }
        }

        return height;
    }
};


TIME COMPLEXITY
----------------

Let:

    m = number of rows
    n = number of columns
    W = number of water cells

For every cell, we check every water cell.

Therefore:

    O(m * n * W)

Worst case:

    O((m * n)^2)


SPACE COMPLEXITY
----------------

We store the water cells:

    O(W)

and the answer matrix:

    O(m * n)

Therefore:

    O(m * n)


======================================================================
OPTIMAL APPROACH
======================================================================


OBSERVATION
-----------

The required height of a cell is:

    distance from the nearest water cell.


For example:

    Water = 0

    One step away = 1

    Two steps away = 2

    Three steps away = 3


So this is exactly a shortest-distance problem from multiple
starting points.


INTUITION
---------

There are multiple water cells.

All water cells already have height:

    0


Therefore, instead of running BFS separately from every water cell,
we can put ALL water cells into the queue initially.


This is called:

                    MULTI-SOURCE BFS


BFS guarantees that cells are visited in increasing distance from
the nearest source.

Therefore:

    First layer:
        Water cells
        height = 0

    Second layer:
        Cells adjacent to water
        height = 1

    Third layer:
        Cells distance 2 from water
        height = 2

    ...


WHY BFS WORKS
-------------

Suppose a cell is first reached from a water cell at distance 3.

Because BFS explores all distance-2 cells before distance-3 cells,
there cannot be another path reaching that cell with distance 2
that has not already been processed.

Therefore, the first assigned height is the minimum distance from
any water cell.


PSEUDO CODE
-----------

Create height matrix initialized with -1.

Create queue.

For every cell:

    if it is water:

        height[i][j] = 0
        push (i, j) into queue


while queue is not empty:

    current = queue.front()
    pop current

    for all 4 directions:

        calculate neighbor

        if neighbor is inside grid
        and height[neighbor] == -1:

            height[neighbor] =
                height[current] + 1

            push neighbor


return height


COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:
    typedef pair<int, int> P;

    vector<vector<int>> highestPeak(
        vector<vector<int>>& isWater) {

        int m = isWater.size();
        int n = isWater[0].size();

        vector<vector<int>> height(
            m,
            vector<int>(n, -1)
        );

        queue<P> que;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (isWater[i][j] == 1) {

                    height[i][j] = 0;
                    que.push({i, j});
                }
            }
        }

        int directions[4][2] = {
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1}
        };

        while (!que.empty()) {

            P curr = que.front();
            que.pop();

            int i = curr.first;
            int j = curr.second;

            for (auto& dir : directions) {

                int x = i + dir[0];
                int y = j + dir[1];

                if (x >= 0 && x < m &&
                    y >= 0 && y < n &&
                    height[x][y] == -1) {

                    height[x][y] =
                        height[i][j] + 1;

                    que.push({x, y});
                }
            }
        }

        return height;
    }
};


TIME COMPLEXITY
----------------

Every cell enters the queue at most once.

For every cell, we check 4 directions.

Therefore:

    O(m * n * 4)

which simplifies to:

    O(m * n)


SPACE COMPLEXITY
----------------

Height matrix:

    O(m * n)

Queue:

    O(m * n)

Therefore:

    O(m * n)


======================================================================
DRY RUN WITH EXAMPLE
======================================================================


Input:

    isWater = {
        {0, 1},
        {0, 0}
    }


Initial height:

    -1   0
    -1  -1


Queue:

    {(0,1)}


STEP 1
------

Process:

    (0,1)

Height:

    -1   0
    -1  -1


Neighbors:

    (0,0)
    (1,1)


Both are unvisited.

Set:

    height[0][0] = 1
    height[1][1] = 1


Height becomes:

    1   0
    -1  1


Queue:

    {(0,0), (1,1)}


STEP 2
------

Process:

    (0,0)

Its unvisited neighbor:

    (1,0)

Set:

    height[1][0] = 2


Height:

    1   0
    2   1


STEP 3
------

Process:

    (1,1)

Its neighbors are already visited.

Nothing changes.


STEP 4
------

Process:

    (1,0)

All neighbors are already visited.


Queue becomes empty.


FINAL ANSWER:

    {
        {1, 0},
        {2, 1}
    }


======================================================================
INTERVIEW NOTES
======================================================================


PATTERN
-------

Multi-Source BFS


KEY OBSERVATION
---------------

All water cells are sources with distance/height 0.

Instead of doing:

    BFS from water cell 1
    BFS from water cell 2
    BFS from water cell 3
    ...

we put ALL water cells into one queue initially.


This gives the shortest distance to the nearest water cell
in a single BFS.


COMMON MISTAKES
---------------

1. Initializing height with 0.

   Wrong because unvisited land cells would look like visited cells.

   Correct:

       vector<vector<int>> height(
           m,
           vector<int>(n, -1)
       );


2. Using:

       height[x][j]

   instead of:

       height[x][y]

   when checking the neighbor.


3. Forgetting to mark a cell visited before pushing it.

   Here, assigning its height before pushing automatically acts
   as the visited marker.


4. Running separate BFS from every water cell.

   This works but is unnecessarily expensive.


5. Using DFS.

   DFS does not naturally guarantee minimum distance.


6. Forgetting that ALL water cells are sources.


7. Using only one water cell as the BFS starting point.

   The nearest water cell may be different for different land cells.


8. Incorrect vector size.

   The answer must be:

       vector<vector<int>>(m, vector<int>(n, -1))

   not:

       vector<vector<int>>(m, vector<int>(n - 1))


======================================================================
WHEN TO USE THIS APPROACH
======================================================================


Use Multi-Source BFS when:

    - There are multiple starting/source cells.
    - We need the minimum distance from ANY source.
    - Movement cost between adjacent cells is equal.
    - The grid is unweighted.
    - Every source starts at distance 0.


Typical problems:

    - Distance from nearest 0
    - Distance from nearest 1
    - Rotting oranges
    - Walls and gates
    - Map of highest peak
    - Nearest hospital
    - Nearest fire source
    - Nearest exit from multiple entrances


GENERAL TEMPLATE
----------------

    queue all sources

    while queue is not empty:

        current = queue.front()
        queue.pop()

        for every neighbor:

            if neighbor is unvisited:

                distance[neighbor] =
                    distance[current] + 1

                queue.push(neighbor)


KEY LINE TO REMEMBER
--------------------

For Multi-Source BFS:

    Put ALL sources into the queue at distance 0.

Then normal BFS automatically calculates the minimum distance
from the nearest source.


======================================================================
CORRECTIONS FROM THE ORIGINAL CODE
======================================================================

Original:

    vector<vector<int>> height(m,vector<int>(n-1));

Correct:

    vector<vector<int>> height(m,vector<int>(n,-1));


Original condition:

    height[x][j]

Correct:

    height[x][y] == -1


Original:

    directions

Correctly define directions before using them:

    int directions[4][2] = {
        {-1,0},
        {1,0},
        {0,-1},
        {0,1}
    };


Original:

    que.push({x,y})

Correct:

    que.push({x,y});


The '-1' initialization is important because it tells us that
a cell has not been visited yet.

======================================================================
*/
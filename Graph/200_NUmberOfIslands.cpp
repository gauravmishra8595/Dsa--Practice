#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void dfs(int i, int j, vector<vector<char>> &grid, int n, int m)
    {
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != '1')
            return;

        grid[i][j] = '0';

        dfs(i - 1, j, grid, n, m);
        dfs(i + 1, j, grid, n, m);
        dfs(i, j - 1, grid, n, m);
        dfs(i, j + 1, grid, n, m);
    }

    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        int islands = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    islands++;
                    dfs(i, j, grid, n, m);
                }
            }
        }

        return islands;
    }
};

int main()
{

    Solution obj;

    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};

    cout << obj.numIslands(grid);

    return 0;
}

/*

=========================================================
LeetCode 200 - Number of Islands
=========================================================

---------------------------------------------------------
Problem Statement
---------------------------------------------------------

Given an m x n 2D binary grid consisting of
'1' (land) and '0' (water),

return the number of islands.

An island is formed by connecting adjacent lands
horizontally or vertically.

Assume all four edges of the grid are surrounded by water.

---------------------------------------------------------
Example
---------------------------------------------------------

Input

grid =

1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

Output

3

Explanation

Island 1

1 1
1 1

Island 2

1

Island 3

1 1

=========================================================
Brute Force Approach
=========================================================

-------------------------
Idea
-------------------------

Use another visited matrix.

Traverse every cell.

Whenever an unvisited land is found,

perform DFS/BFS,

mark all connected lands visited,

increment island count.

-------------------------
Pseudo Code
-------------------------

visited[][] = false

answer = 0

for every cell

    if land and not visited

        DFS()

        answer++

return answer

-------------------------
Complete Brute Force Code
-------------------------

class Solution {
public:

void dfs(int i,int j,
         vector<vector<char>>& grid,
         vector<vector<bool>>& vis){

    int n=grid.size();
    int m=grid[0].size();

    if(i<0 || j<0 || i>=n || j>=m)
        return;

    if(vis[i][j] || grid[i][j]=='0')
        return;

    vis[i][j]=true;

    dfs(i-1,j,grid,vis);
    dfs(i+1,j,grid,vis);
    dfs(i,j-1,grid,vis);
    dfs(i,j+1,grid,vis);
}

int numIslands(vector<vector<char>>& grid){

    int n=grid.size();
    int m=grid[0].size();

    vector<vector<bool>> vis(
        n,
        vector<bool>(m,false)
    );

    int islands=0;

    for(int i=0;i<n;i++){

        for(int j=0;j<m;j++){

            if(grid[i][j]=='1' && !vis[i][j]){

                dfs(i,j,grid,vis);

                islands++;
            }
        }
    }

    return islands;
}

};

-------------------------
Time Complexity
-------------------------

O(N*M)

-------------------------
Space Complexity
-------------------------

Visited Array

O(N*M)

DFS Stack

O(N*M)

Overall

O(N*M)

=========================================================
Optimal Approach
=========================================================

-------------------------
Observation
-------------------------

We don't actually need a visited array.

Whenever we visit a land,

simply convert it into water.

This marks it visited.

-------------------------
Intuition
-------------------------

Every island is one connected component.

Whenever an unvisited land appears,

perform DFS,

sink the complete island,

increment answer.

Every cell is visited only once.

-------------------------
Pseudo Code
-------------------------

answer = 0

for every cell

    if cell == '1'

        answer++

        DFS()

DFS

if outside grid

    return

if water

    return

mark land as water

visit four directions

-------------------------
Complete Optimal Code
-------------------------

class Solution {
public:

void dfs(int i,int j,
         vector<vector<char>>& grid,
         int n,int m){

    if(i<0 || j<0 ||
       i>=n || j>=m ||
       grid[i][j]!='1')
        return;

    grid[i][j]='0';

    dfs(i-1,j,grid,n,m);
    dfs(i+1,j,grid,n,m);
    dfs(i,j-1,grid,n,m);
    dfs(i,j+1,grid,n,m);
}

int numIslands(vector<vector<char>>& grid){

    int n=grid.size();
    int m=grid[0].size();

    int islands=0;

    for(int i=0;i<n;i++){

        for(int j=0;j<m;j++){

            if(grid[i][j]=='1'){

                islands++;

                dfs(i,j,grid,n,m);
            }
        }
    }

    return islands;
}

};

-------------------------
Time Complexity
-------------------------

Each cell is visited once.

O(N*M)

-------------------------
Space Complexity
-------------------------

Recursive Stack

Worst Case

O(N*M)

Extra Space

O(1)

(ignoring recursion stack)

=========================================================
Dry Run
=========================================================

Grid

1 1 0 0 0

1 1 0 0 0

0 0 1 0 0

0 0 0 1 1

---------------------------------

Start (0,0)

DFS visits

(0,0)

(0,1)

(1,0)

(1,1)

Convert all to 0

Islands = 1

---------------------------------

Continue scanning

Find (2,2)

DFS

Convert to 0

Islands = 2

---------------------------------

Continue

Find (3,3)

DFS

Visits

(3,3)

(3,4)

Convert both

Islands = 3

---------------------------------

Traversal complete

Answer = 3

=========================================================
Interview Notes
=========================================================

Pattern

• Graph Traversal

• DFS

• BFS

• Connected Components

---------------------------------------------------------

Key Observation

Each island is simply one connected component.

Run DFS/BFS once per component.

---------------------------------------------------------

Common Mistakes

1. Forget to mark visited.

2. Visiting diagonal cells.

3. Boundary check after accessing array.

4. Forget grid[i][j]=='1' check.

---------------------------------------------------------

When to use this approach

Use whenever

• Grid contains connected regions.

• Need number of connected components.

• Flood Fill, Islands, Surrounded Regions,
  Rotten Oranges, etc.

=========================================================

*/
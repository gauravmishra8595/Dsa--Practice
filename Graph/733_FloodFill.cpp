#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int n, m;

    void dfs(vector<vector<int>> &image, int r, int c,
             int oldColor, int newColor)
    {

        if (r < 0 || c < 0 || r >= n || c >= m)
            return;

        if (image[r][c] != oldColor)
            return;

        image[r][c] = newColor;

        dfs(image, r + 1, c, oldColor, newColor);
        dfs(image, r - 1, c, oldColor, newColor);
        dfs(image, r, c + 1, oldColor, newColor);
        dfs(image, r, c - 1, oldColor, newColor);
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>> &image,
                                  int sr, int sc, int color)
    {

        n = image.size();
        m = image[0].size();

        int oldColor = image[sr][sc];

        if (oldColor == color)
            return image;

        dfs(image, sr, sc, oldColor, color);

        return image;
    }
};

int main()
{

    Solution obj;

    vector<vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}};

    int sr = 1;
    int sc = 1;
    int color = 2;

    vector<vector<int>> ans = obj.floodFill(image, sr, sc, color);

    for (auto &row : ans)
    {
        for (int x : row)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}

/*

=========================================
LeetCode 733 - Flood Fill
=========================================

Problem Statement
-----------------
Given an image represented by an m x n grid of integers,
each value represents a pixel color.

Starting from pixel (sr, sc),
change its color and all 4-directionally connected pixels
having the same original color to the given new color.

Return the modified image.

----------------------------------------------------

Example
-------

Input:

image =
1 1 1
1 1 0
1 0 1

sr = 1
sc = 1
color = 2

Output:

2 2 2
2 2 0
2 0 1

====================================================
Brute Force Approach
====================================================

Idea
----
Try changing every pixel repeatedly until no changes occur.

This checks connectivity indirectly and is extremely
inefficient.

----------------------------------------------------

Pseudo Code
-----------

Repeat

    Traverse entire matrix

    If adjacent pixel has target color

        Change current pixel

Until no changes occur

----------------------------------------------------

Complete Brute Force Code
----------------------------------------------------

(Not recommended)

Repeatedly traverse matrix
until no new pixel gets colored.

----------------------------------------------------

Time Complexity
---------------
O((m*n)^2)

Space Complexity
----------------
O(1)

====================================================
Optimal Approach
====================================================

Observation
-----------
Flood Fill is simply a graph traversal.

Each cell is a node.

Edges exist in four directions.

----------------------------------------------------

Intuition
---------
Start DFS from (sr, sc).

Whenever we visit a cell:

1. Check boundaries.
2. Ignore different colors.
3. Paint current cell.
4. Visit all 4 neighbours.

Since every valid pixel is visited only once,
overall complexity is linear.

Important Edge Case

If original color == new color,
return immediately.

Otherwise recursion will revisit forever.

----------------------------------------------------

Pseudo Code
-----------

oldColor = image[sr][sc]

if oldColor == newColor

    return image

DFS(r,c)

    if out of bounds

        return

    if image[r][c] != oldColor

        return

    image[r][c] = newColor

    DFS(up)
    DFS(down)
    DFS(left)
    DFS(right)

----------------------------------------------------

Complete Optimal Code
----------------------------------------------------

class Solution {

    int n,m;

    void dfs(vector<vector<int>>& image,
             int r,
             int c,
             int oldColor,
             int newColor){

        if(r<0 || c<0 || r>=n || c>=m)
            return;

        if(image[r][c]!=oldColor)
            return;

        image[r][c]=newColor;

        dfs(image,r+1,c,oldColor,newColor);
        dfs(image,r-1,c,oldColor,newColor);
        dfs(image,r,c+1,oldColor,newColor);
        dfs(image,r,c-1,oldColor,newColor);
    }

public:

    vector<vector<int>> floodFill(
        vector<vector<int>>& image,
        int sr,
        int sc,
        int color) {

        n=image.size();
        m=image[0].size();

        int oldColor=image[sr][sc];

        if(oldColor==color)
            return image;

        dfs(image,sr,sc,oldColor,color);

        return image;
    }
};

----------------------------------------------------

Time Complexity
---------------
O(m × n)

Space Complexity
----------------
O(m × n) worst case recursion stack

====================================================
Dry Run
====================================================

Image

1 1 1
1 1 0
1 0 1

Start

(1,1)

Old Color = 1

Paint

2

Visit

Up
Down
Left
Right

Connected 1's become

2 2 2
2 2 0
2 0 1

Return image.

====================================================
Interview Notes
====================================================

Pattern
-------
DFS
BFS
Graph Traversal
Matrix Traversal

Key Observation
---------------
1. Matrix behaves like a graph.
2. Visit only connected cells having same color.
3. Paint while traversing.
4. Handle oldColor == newColor first.

Common Mistakes
---------------
1. Forgetting boundary checks.
2. Infinite recursion when oldColor == newColor.
3. Visiting diagonal neighbours.
4. Forgetting to pass image by reference.

When to use this approach
-------------------------
Use DFS/BFS whenever:

- Connected components in matrix.
- Island problems.
- Flood Fill.
- Graph traversal on grids.
- Maze exploration.

*/
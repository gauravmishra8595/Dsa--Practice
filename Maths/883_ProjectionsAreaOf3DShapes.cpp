#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int xy = 0, yz = 0, zx = 0;

        for (int i = 0; i < n; i++) {
            int rowMax = 0;
            int colMax = 0;

            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) xy++;
                rowMax = max(rowMax, grid[i][j]);
                colMax = max(colMax, grid[j][i]);
            }

            yz += rowMax;
            zx += colMax;
        }

        return xy + yz + zx;
    }
};

int main() {
    Solution obj;

    vector<vector<int>> grid = {
        {1, 2},
        {3, 4}
    };

    cout << obj.projectionArea(grid) << endl;

    return 0;
}

/*

======================== Leetcode 883. Projection Area of 3D Shapes ========================

Problem Statement:
------------------
On a N x N grid, each cell grid[i][j] represents the height of stacked cubes.

Find the total projection area on:
1. XY Plane (Top View)
2. YZ Plane (Front View)
3. ZX Plane (Side View)

Return the sum of all three projection areas.

Example:
--------
Input:
grid =
[
 [1,2],
 [3,4]
]

Output:
17

Explanation:
XY = 4
YZ = 6
ZX = 7
Total = 17

=============================================================================================
Brute Force Approach
=============================================================================================

Idea:
-----
Calculate each projection separately.

1. XY:
   Count every non-zero cell.

2. YZ:
   For every row find maximum.

3. ZX:
   For every column find maximum.

Although this is already O(N²), we can unnecessarily perform three different traversals.

Pseudo Code:
------------
xy = 0

for every cell
    if value > 0
        xy++

yz = 0
for every row
    yz += maximum element

zx = 0
for every column
    zx += maximum element

return xy + yz + zx

Complete Brute Force Code:

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {

        int n = grid.size();

        int xy = 0;

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(grid[i][j]>0)
                    xy++;

        int yz = 0;

        for(int i=0;i<n;i++){
            int mx=0;
            for(int j=0;j<n;j++)
                mx=max(mx,grid[i][j]);
            yz+=mx;
        }

        int zx = 0;

        for(int j=0;j<n;j++){
            int mx=0;
            for(int i=0;i<n;i++)
                mx=max(mx,grid[i][j]);
            zx+=mx;
        }

        return xy+yz+zx;
    }
};

Time Complexity:
O(N²)

Space Complexity:
O(1)

=============================================================================================
Optimal Approach
=============================================================================================

Observation:
------------
During one traversal over each row, we can simultaneously compute:

1. Top projection count.
2. Row maximum.
3. Column maximum.

Thus only one nested loop is needed.

Intuition:
----------
Every cell contributes independently.

Top View:
Count every non-zero stack.

Front View:
Tallest stack in every row.

Side View:
Tallest stack in every column.

Pseudo Code:
------------
xy = yz = zx = 0

for i = 0 to n-1

    rowMax = 0
    colMax = 0

    for j = 0 to n-1

        if grid[i][j] > 0
            xy++

        rowMax = max(rowMax, grid[i][j])
        colMax = max(colMax, grid[j][i])

    yz += rowMax
    zx += colMax

return xy + yz + zx

Complete Optimal Code:

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();

        int xy = 0;
        int yz = 0;
        int zx = 0;

        for(int i=0;i<n;i++){

            int rowMax = 0;
            int colMax = 0;

            for(int j=0;j<n;j++){

                if(grid[i][j]>0)
                    xy++;

                rowMax=max(rowMax,grid[i][j]);
                colMax=max(colMax,grid[j][i]);
            }

            yz+=rowMax;
            zx+=colMax;
        }

        return xy+yz+zx;
    }
};

Time Complexity:
O(N²)

Space Complexity:
O(1)

=============================================================================================
Dry Run
=============================================================================================

Input:

1 2
3 4

Initially

xy = 0
yz = 0
zx = 0

Row 0

Cells:
1 -> xy=1
2 -> xy=2

rowMax = 2
colMax = max(1,3)=3

yz=2
zx=3

--------------------------------

Row 1

Cells:
3 -> xy=3
4 -> xy=4

rowMax=4
colMax=max(2,4)=4

yz=6
zx=7

Answer

xy + yz + zx

= 4 + 6 + 7

= 17

=============================================================================================
Interview Notes
=============================================================================================

Pattern:
--------
Matrix Traversal

Key Observation:
----------------
Projection area equals:
- Number of non-zero cells
- Sum of row maxima
- Sum of column maxima

Common Mistakes:
----------------
1. Forgetting to count only non-zero cells for top view.
2. Mixing row and column indices.
3. Using row maximum for side projection.
4. Forgetting to reset rowMax and colMax each iteration.

When to use this approach:
--------------------------
Whenever a matrix problem asks for:
- Row maxima
- Column maxima
- Counting valid cells

All three values can often be computed together in one traversal.

=============================================================================================

*/
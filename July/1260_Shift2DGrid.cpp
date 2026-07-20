#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> shiftGrid(vector<vector<int>> &grid, int k)
    {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        k %= total;
        vector<vector<int>> ans(m, vector<int>(n));

        for (int i = 0; i < total; i++)
        {
            int newPos = (i + k) % total;

            int oldRow = i / n;
            int oldCol = i % n;

            int newRow = newPos / n;
            int newCol = newPos % n;

            ans[newRow][newCol] = grid[oldRow][oldCol];
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int k = 1;

    vector<vector<int>> ans = obj.shiftGrid(grid, k);

    for (auto &row : ans)
    {
        for (auto &x : row)
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}

/*

===========================
Problem Statement
===========================

LeetCode 1260 - Shift 2D Grid

Given a 2D grid of size m x n and an integer k, shift the grid k times.

One shift operation means:
1. Element at grid[i][j] moves to grid[i][j+1].
2. Element at grid[i][n-1] moves to grid[i+1][0].
3. Element at grid[m-1][n-1] moves to grid[0][0].

Return the shifted grid.

===========================
Example
===========================

Input:
grid =
1 2 3
4 5 6
7 8 9

k = 1

Output:
9 1 2
3 4 5
6 7 8

===========================
Brute Force Approach
===========================

Idea
----
Perform one shift exactly k times.

Each shift:
- Store last element.
- Move every element one position forward.
- Put stored last element at grid[0][0].

Pseudo Code
-----------
Repeat k times
    last = grid[m-1][n-1]

    for i = m-1 to 0
        for j = n-1 to 0
            shift previous element

    grid[0][0] = last

Return grid

Complete Brute Force Code
-------------------------

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {

        int m = grid.size();
        int n = grid[0].size();

        while(k--){

            int last = grid[m-1][n-1];

            for(int i=m-1;i>=0;i--){

                for(int j=n-1;j>=0;j--){

                    if(i==0 && j==0) continue;

                    if(j==0)
                        grid[i][j]=grid[i-1][n-1];
                    else
                        grid[i][j]=grid[i][j-1];
                }
            }

            grid[0][0]=last;
        }

        return grid;
    }
};

Time Complexity
---------------
O(k * m * n)

Space Complexity
----------------
O(1)

===========================
Optimal Approach
===========================

Observation
-----------
A 2D grid can be treated as a single 1D array.

Index Mapping:

Linear Index = row * n + col

After shifting,

newIndex = (oldIndex + k) % (m*n)

Convert back:

row = index / n

col = index % n

Intuition
---------
Instead of actually shifting k times,
calculate the final destination of every element directly.

Every element is visited only once.

Pseudo Code
-----------
total = m*n

k %= total

Create answer matrix

For every index i
    newPos = (i+k)%total

    oldRow=i/n
    oldCol=i%n

    newRow=newPos/n
    newCol=newPos%n

    ans[newRow][newCol]=grid[oldRow][oldCol]

Return ans

Complete Optimal Code
---------------------

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {

        int m=grid.size();
        int n=grid[0].size();

        int total=m*n;

        k%=total;

        vector<vector<int>> ans(m,vector<int>(n));

        for(int i=0;i<total;i++){

            int newPos=(i+k)%total;

            int oldRow=i/n;
            int oldCol=i%n;

            int newRow=newPos/n;
            int newCol=newPos%n;

            ans[newRow][newCol]=grid[oldRow][oldCol];
        }

        return ans;
    }
};

Time Complexity
---------------
O(m * n)

Space Complexity
----------------
O(m * n)

===========================
Dry Run
===========================

Grid

1 2 3
4 5 6
7 8 9

k = 1

total = 9

Element 1
oldIndex = 0
newIndex = 1

Element 2
oldIndex = 1
newIndex = 2

...

Element 9
oldIndex = 8
newIndex = 0

Result

9 1 2
3 4 5
6 7 8

===========================
Interview Notes
===========================

Pattern
-------
Index Mapping / Matrix Simulation

Key Observation
---------------
Treat the matrix as one continuous array.

Common Mistakes
---------------
1. Forgetting k %= (m*n).
2. Incorrect row-column conversion.
3. Confusing old index with new index.
4. Off-by-one errors while mapping.

When to use this approach
-------------------------
Whenever a matrix is traversed in row-major order and elements are cyclically shifted,
convert the matrix into linear indices and perform modular arithmetic.

*/
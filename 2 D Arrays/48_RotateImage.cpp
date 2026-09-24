#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int n = matrix.size();

        // Transpose the matrix
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Reverse every row
        for (int i = 0; i < n; i++)
        {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    sol.rotate(matrix);

    for (auto &row : matrix)
    {
        for (int x : row)
            cout << x << " ";
        cout << '\n';
    }

    return 0;
}

/*
================================================================================
LEETCODE 48 - ROTATE IMAGE
================================================================================

Problem Statement:
------------------
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees clockwise.

You must rotate the image IN-PLACE, meaning the matrix must be modified
without using another 2D matrix.

Example:
--------
Input:
[
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

Output:
[
    [7, 4, 1],
    [8, 5, 2],
    [9, 6, 3]
]


Brute Force Approach:
---------------------

Idea:
-----
Create a new n x n matrix.

For a 90-degree clockwise rotation:

    new[j][n - 1 - i] = matrix[i][j]

After filling the new matrix, copy it back into the original matrix.

This approach is simple but uses O(n^2) extra space.


Pseudo Code:
------------
create new matrix result[n][n]

for i = 0 to n-1:
    for j = 0 to n-1:
        result[j][n-1-i] = matrix[i][j]

copy result into matrix


Complete Brute Force Code:
--------------------------

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> result(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[j][n - 1 - i] = matrix[i][j];
            }
        }

        matrix = result;
    }
};


Time Complexity:
----------------
O(n^2)

Space Complexity:
-----------------
O(n^2)


Optimal Approach:
-----------------

Observation:
------------
A 90-degree clockwise rotation can be achieved using two operations:

1. Transpose the matrix.
2. Reverse every row.

Example:

Original:
1 2 3
4 5 6
7 8 9

After transpose:
1 4 7
2 5 8
3 6 9

Reverse every row:
7 4 1
8 5 2
9 6 3

This is exactly the required 90-degree clockwise rotation.


Intuition:
----------
Transpose swaps:

    matrix[i][j] <-> matrix[j][i]

We only need to swap elements above the main diagonal with elements
below the main diagonal.

After transposition, reversing every row moves the columns into their
correct rotated positions.

Both operations can be performed in-place.


Pseudo Code:
------------
for i = 0 to n-1:
    for j = i+1 to n-1:
        swap(matrix[i][j], matrix[j][i])

for every row:
    reverse(row)


Complete Optimal Code:
----------------------

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Transpose
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Reverse every row
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};


Time Complexity:
----------------
O(n^2)

Every matrix element is processed a constant number of times.


Space Complexity:
-----------------
O(1)

The rotation is performed completely in-place.


Dry Run with Example:
---------------------

Input:

1 2 3
4 5 6
7 8 9


Step 1: Transpose

Swap (0,1):
1 4 3
2 5 6
7 8 9

Swap (0,2):
1 4 7
2 5 6
3 8 9

Swap (1,2):
1 4 7
2 5 8
3 6 9


Step 2: Reverse every row

Row 1:
1 4 7 -> 7 4 1

Row 2:
2 5 8 -> 8 5 2

Row 3:
3 6 9 -> 9 6 3


Final Matrix:

7 4 1
8 5 2
9 6 3


Interview Notes:
----------------

Pattern:
    Matrix Manipulation + In-Place Transformation

Key Observation:
    90-degree clockwise rotation =
    Transpose + Reverse Every Row

Common Mistakes:
    1. Reversing columns instead of rows after transpose.
    2. Swapping the entire matrix during transpose and accidentally swapping
       elements twice.
    3. Using j = 0 instead of j = i + 1 during transpose.
    4. Creating another matrix when the problem explicitly asks for
       in-place modification.
    5. Confusing clockwise rotation with anticlockwise rotation.

When to use this approach:
    Use this approach whenever a square matrix needs to be rotated 90 degrees
    clockwise in-place.

For 90-degree clockwise rotation:
    Transpose + Reverse Rows

For 90-degree anticlockwise rotation:
    Transpose + Reverse Columns

================================================================================
*/

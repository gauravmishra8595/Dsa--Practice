#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int n = matrix.size();

        // Step 1: Transpose the matrix
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; i++)
        {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

// Function to print matrix
void printMatrix(vector<vector<int>> &matrix)
{
    for (auto &row : matrix)
    {
        for (auto &val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    Solution obj;
    obj.rotate(matrix);

    cout << "Rotated Matrix:" << endl;
    printMatrix(matrix);

    return 0;
}

/*
=========================================
Brute Force Approach
=========================================

Idea:
Create a new matrix and place elements in their
rotated positions.

For a 90-degree clockwise rotation:
newMatrix[j][n-1-i] = matrix[i][j]

Code:

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();

    vector<vector<int>> temp(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[j][n - 1 - i] = matrix[i][j];
        }
    }

    matrix = temp;
}

Time Complexity: O(n²)
Space Complexity: O(n²)

=========================================
Optimal Approach (Transpose + Reverse)
=========================================

Step 1: Transpose the matrix
          Rows become columns.

1 2 3        1 4 7
4 5 6   ->   2 5 8
7 8 9        3 6 9

Step 2: Reverse every row

1 4 7        7 4 1
2 5 8   ->   8 5 2
3 6 9        9 6 3

Result:
7 4 1
8 5 2
9 6 3

Time Complexity: O(n²)
Space Complexity: O(1)

=========================================
Interview Tip
=========================================

Clockwise Rotation:
Transpose + Reverse Rows

Anti-Clockwise Rotation:
Transpose + Reverse Columns

This is the expected optimal solution
for LeetCode 48: Rotate Image.

*/
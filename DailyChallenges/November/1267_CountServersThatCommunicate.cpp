#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }

        // Count communicating servers
        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 &&
                    (rowCount[i] > 1 || colCount[j] > 1)) {
                    ans++;
                }
            }
        }

        return ans;
    }
};

// Main Function for Testing
int main() {
    Solution obj;

    vector<vector<int>> grid = {
        {1, 0},
        {1, 1}
    };

    cout << obj.countServers(grid) << endl;

    return 0;
}

/*
============================================================
        LEETCODE 1267 - COUNT SERVERS THAT COMMUNICATE
============================================================

1. PROBLEM STATEMENT
------------------------------------------------------------

You are given an m x n binary matrix grid.

Each cell represents a server:
    1 -> Server exists
    0 -> No server

Two servers can communicate if they are located in the
same row OR the same column.

Return the total number of servers that can communicate
with at least one other server.

------------------------------------------------------------
2. EXAMPLE
------------------------------------------------------------

Input:
grid = {
    {1, 0},
    {1, 1}
};

Output:
3

Explanation:

    1  0
    1  1

- Server at (0,0) communicates with (1,0).
- Server at (1,0) communicates with (0,0) and (1,1).
- Server at (1,1) communicates with (1,0).

All three servers can communicate.

============================================================
3. BRUTE FORCE APPROACH
============================================================

IDEA:
------------------------------------------------------------

For every server, check all other cells in:

1. Same row.
2. Same column.

If another server exists in either direction, count the
current server.

PSEUDO CODE:
------------------------------------------------------------

1. Initialize ans = 0.

2. Traverse every cell (i, j).

3. If grid[i][j] == 1:

   a. Check all other cells in the same row.
   b. Check all other cells in the same column.

   c. If another server is found:
        ans++

4. Return ans.

COMPLETE BRUTE FORCE CODE:
------------------------------------------------------------

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1) {

                    bool canCommunicate = false;

                    // Check same row
                    for (int k = 0; k < n; k++) {
                        if (k != j && grid[i][k] == 1) {
                            canCommunicate = true;
                            break;
                        }
                    }

                    // Check same column
                    if (!canCommunicate) {
                        for (int k = 0; k < m; k++) {
                            if (k != i && grid[k][j] == 1) {
                                canCommunicate = true;
                                break;
                            }
                        }
                    }

                    if (canCommunicate) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
------------------------------------------------------------

O(m * n * (m + n))

- We traverse every cell: O(m * n).
- For each server, we may scan its entire row and column:
  O(m + n).

SPACE COMPLEXITY:
------------------------------------------------------------

O(1)

- Only a constant number of extra variables are used.
- Input matrix is not counted as auxiliary space.

============================================================
4. OPTIMAL APPROACH
============================================================

OBSERVATION:
------------------------------------------------------------

A server can communicate if:

    rowCount[i] > 1

OR

    colCount[j] > 1

Here:

- rowCount[i] = Number of servers in row i.
- colCount[j] = Number of servers in column j.

Instead of repeatedly checking every row and column,
precompute their server counts.

INTUITION:
------------------------------------------------------------

We can solve this problem using two traversals.

FIRST TRAVERSAL:
    Count the number of servers in every row and column.

SECOND TRAVERSAL:
    For every server:
        If its row has more than one server OR
        its column has more than one server,
        increment the answer.

This avoids repeated scanning.

PSEUDO CODE:
------------------------------------------------------------

1. Get m = number of rows.
2. Get n = number of columns.

3. Create:
       rowCount[m] = 0
       colCount[n] = 0

4. Traverse the matrix:

       If grid[i][j] == 1:
           rowCount[i]++
           colCount[j]++

5. Initialize ans = 0.

6. Traverse the matrix again:

       If grid[i][j] == 1 AND
          (rowCount[i] > 1 OR colCount[j] > 1):

              ans++

7. Return ans.

COMPLETE OPTIMAL CODE:
------------------------------------------------------------

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);

        // Count servers in each row and column
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }

        int ans = 0;

        // Count communicating servers
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 &&
                    (rowCount[i] > 1 || colCount[j] > 1)) {
                    ans++;
                }
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
------------------------------------------------------------

O(m * n)

First traversal: O(m * n)
Second traversal: O(m * n)

Total: O(2 * m * n) = O(m * n)

SPACE COMPLEXITY:
------------------------------------------------------------

O(m + n)

- rowCount requires O(m) space.
- colCount requires O(n) space.

Total auxiliary space = O(m + n).

============================================================
5. DRY RUN WITH EXAMPLE
============================================================

Input:

grid = {
    {1, 0},
    {1, 1}
};

Matrix:

       col0  col1
row0    1     0
row1    1     1

STEP 1: COUNT ROW SERVERS
------------------------------------------------------------

rowCount[0] = 1
rowCount[1] = 2

rowCount = [1, 2]

STEP 2: COUNT COLUMN SERVERS
------------------------------------------------------------

colCount[0] = 2
colCount[1] = 1

colCount = [2, 1]

STEP 3: CHECK EACH SERVER
------------------------------------------------------------

Cell (0,0):

    grid[0][0] = 1

    rowCount[0] = 1
    colCount[0] = 2

    Condition:
    (1 > 1 || 2 > 1) = TRUE

    ans = 1

------------------------------------------------------------

Cell (0,1):

    grid[0][1] = 0

    Not a server.

    ans = 1

------------------------------------------------------------

Cell (1,0):

    grid[1][0] = 1

    rowCount[1] = 2
    colCount[0] = 2

    Condition:
    (2 > 1 || 2 > 1) = TRUE

    ans = 2

------------------------------------------------------------

Cell (1,1):

    grid[1][1] = 1

    rowCount[1] = 2
    colCount[1] = 1

    Condition:
    (2 > 1 || 1 > 1) = TRUE

    ans = 3

------------------------------------------------------------

FINAL ANSWER = 3

============================================================
6. INTERVIEW NOTES
============================================================

PATTERN:
------------------------------------------------------------

- Matrix Traversal
- Precomputation
- Row and Column Frequency Counting
- Two-Pass Algorithm

KEY OBSERVATION:
------------------------------------------------------------

A server communicates if at least one other server
exists in its row OR its column.

Instead of checking every other cell repeatedly,
precompute row and column frequencies.

COMMON MISTAKES:
------------------------------------------------------------

1. Swapping row and column indices:

   Correct:
       rowCount[i]++;
       colCount[j]++;

2. Forgetting to check whether the current cell is a server:

   Correct:
       grid[i][j] == 1

3. Using AND instead of OR:

   Incorrect:
       rowCount[i] > 1 && colCount[j] > 1

   Correct:
       rowCount[i] > 1 || colCount[j] > 1

4. Incorrect operator precedence:

   Always write:

       grid[i][j] == 1 &&
       (rowCount[i] > 1 || colCount[j] > 1)

5. Confusing row and column array sizes:

   rowCount -> size m
   colCount -> size n

WHEN TO USE THIS APPROACH:
------------------------------------------------------------

Use row/column frequency precomputation when:

1. You need to check whether an element has another
   matching element in its row or column.

2. Repeated row/column scanning causes unnecessary
   nested loops.

3. The answer depends on frequencies or counts along
   matrix dimensions.

4. You can solve the problem using:
       First pass  -> Precompute frequencies.
       Second pass -> Use precomputed information.

============================================================
                END OF NOTES
============================================================
*/
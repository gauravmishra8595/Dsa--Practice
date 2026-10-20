#include <bits/stdc++.h>
 using namespace std;
class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        bool rows[9][9] = {};
        bool cols[9][9] = {};
        bool boxes[9][9] = {};

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                    continue;

                int digit = board[i][j] - '1';
                int box = (i / 3) * 3 + (j / 3);

                if (rows[i][digit] ||
                    cols[j][digit] ||
                    boxes[box][digit])
                {
                    return false;
                }

                rows[i][digit] = true;
                cols[j][digit] = true;
                boxes[box][digit] = true;
            }
        }

        return true;
    }
};

int main()
{
    Solution sol;

    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    cout << boolalpha << sol.isValidSudoku(board) << '\n';

    return 0;
}

/*
===============================================================================
                     LEETCODE 36: VALID SUDOKU
===============================================================================

PROBLEM STATEMENT
-----------------
Determine whether a partially filled 9x9 Sudoku board is valid.

Rules:
1. Each row must contain no repeated digit from '1' to '9'.
2. Each column must contain no repeated digit from '1' to '9'.
3. Each 3x3 box must contain no repeated digit from '1' to '9'.
4. '.' represents an empty cell and must be ignored.

A valid board does not need to be solvable. Only the filled cells are checked.

EXAMPLE
-------
Input:
board =
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]

Output: true

Explanation:
No digit is repeated in any row, column, or 3x3 box.

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

IDEA
----
Check every filled cell against the other cells in its row, column, and
3x3 box. If the same digit appears in any of these locations, return false.

PSEUDO CODE
-----------
function isValidSudoku(board):
    for each cell (r, c):
        if board[r][c] == '.':
            continue

        for every other column j:
            if board[r][j] == board[r][c]:
                return false

        for every other row i:
            if board[i][c] == board[r][c]:
                return false

        find the starting row and column of the 3x3 box

        for every cell (i, j) in that box:
            if (i, j) != (r, c) and
               board[i][j] == board[r][c]:
                return false

    return true

COMPLETE BRUTE FORCE CODE (REVISION ONLY)
------------------------------------------
bool bruteForce(vector<vector<char>>& board) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') continue;

            char ch = board[r][c];

            // Check row
            for (int j = 0; j < 9; j++) {
                if (j != c && board[r][j] == ch)
                    return false;
            }

            // Check column
            for (int i = 0; i < 9; i++) {
                if (i != r && board[i][c] == ch)
                    return false;
            }

            // Check 3x3 box
            int sr = (r / 3) * 3;
            int sc = (c / 3) * 3;

            for (int i = sr; i < sr + 3; i++) {
                for (int j = sc; j < sc + 3; j++) {
                    if ((i != r || j != c) && board[i][j] == ch)
                        return false;
                }
            }
        }
    }

    return true;
}

TIME COMPLEXITY
---------------
O(9 * 9 * 9) = O(1) for a fixed 9x9 board.
More generally, checking all cells against their row, column, and box
takes O(N^2) for an N x N Sudoku board.

SPACE COMPLEXITY
----------------
O(1) auxiliary space.

===============================================================================
OPTIMAL APPROACH
===============================================================================

OBSERVATION
-----------
Each digit must appear at most once in its row, column, and 3x3 box.

We can remember which digits have already appeared using boolean arrays.

INTUITION
---------
Maintain three tracking structures:

1. rows[9][9]:
   rows[r][d] is true if digit d has appeared in row r.

2. cols[9][9]:
   cols[c][d] is true if digit d has appeared in column c.

3. boxes[9][9]:
   boxes[b][d] is true if digit d has appeared in box b.

Convert a character digit into an index:
    digit = board[i][j] - '1'

Calculate the 3x3 box index:
    box = (i / 3) * 3 + (j / 3)

Before marking a digit, check all three structures.
If any is already true, the board is invalid.
Otherwise, mark the digit in all three structures.

PSEUDO CODE
-----------
function isValidSudoku(board):
    initialize rows[9][9] to false
    initialize cols[9][9] to false
    initialize boxes[9][9] to false

    for i from 0 to 8:
        for j from 0 to 8:
            if board[i][j] == '.':
                continue

            digit = board[i][j] - '1'
            box = (i / 3) * 3 + (j / 3)

            if rows[i][digit] or
               cols[j][digit] or
               boxes[box][digit]:
                return false

            rows[i][digit] = true
            cols[j][digit] = true
            boxes[box][digit] = true

    return true

COMPLETE OPTIMAL CODE (REVISION ONLY)
--------------------------------------
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {};
        bool cols[9][9] = {};
        bool boxes[9][9] = {};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;

                int digit = board[i][j] - '1';
                int box = (i / 3) * 3 + (j / 3);

                if (rows[i][digit] ||
                    cols[j][digit] ||
                    boxes[box][digit]) {
                    return false;
                }

                rows[i][digit] = true;
                cols[j][digit] = true;
                boxes[box][digit] = true;
            }
        }

        return true;
    }
};

TIME COMPLEXITY
---------------
O(9 * 9) = O(1) for a fixed 9x9 board.
For a generalized N x N board, the time complexity is O(N^2).

SPACE COMPLEXITY
----------------
O(9 * 9 * 3) = O(1) auxiliary space for a fixed board.
For a generalized N x N board, the tracking structures require O(N^2).

===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Consider these filled cells:

board[0][0] = '5'
board[0][1] = '3'
board[0][4] = '7'

CELL 1: (0, 0) = '5'
--------------------
digit = '5' - '1' = 4
box = (0 / 3) * 3 + (0 / 3) = 0

rows[0][4], cols[0][4], boxes[0][4] are all false.
Mark all three as true.

CELL 2: (0, 1) = '3'
--------------------
digit = '3' - '1' = 2
box = (0 / 3) * 3 + (1 / 3) = 0

All three corresponding entries are false.
Mark them as true.

CELL 3: (0, 4) = '7'
--------------------
digit = '7' - '1' = 6
box = (0 / 3) * 3 + (4 / 3) = 1

All three corresponding entries are false.
Mark them as true.

DUPLICATE EXAMPLE
-----------------
If board[0][2] were changed from '.' to '5':

digit = '5' - '1' = 4
box = (0 / 3) * 3 + (2 / 3) = 0

rows[0][4] is already true.
Therefore, the function immediately returns false.

FINAL RESULT FOR THE GIVEN BOARD
--------------------------------
true

===============================================================================
INTERVIEW NOTES
===============================================================================

PATTERN
-------
- Matrix traversal
- Hashing / frequency tracking
- Boolean lookup tables
- Constant-time duplicate detection

KEY OBSERVATION
---------------
Every filled cell belongs to exactly one row, one column, and one 3x3 box.
Track each of these independently to detect duplicates in one pass.

COMMON MISTAKES
---------------
1. Forgetting to skip '.' cells.
2. Using board[i][j] directly as an array index instead of converting it
   with board[i][j] - '1'.
3. Calculating the box index incorrectly. The correct formula is:
       (i / 3) * 3 + (j / 3)
4. Checking rows and columns but forgetting the 3x3 boxes.
5. Trying to solve the Sudoku instead of merely validating its current state.
6. Forgetting to initialize tracking arrays to false.

WHEN TO USE THIS APPROACH
-------------------------
Use this approach when:
- Duplicate detection is required across multiple groups.
- Each item belongs to several independently constrained groups.
- Fast constant-time membership checks are possible.
- You need a single-pass solution without sorting or repeated scanning.

===============================================================================
*/

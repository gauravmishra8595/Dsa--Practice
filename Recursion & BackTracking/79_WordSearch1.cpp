#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool dfs(vector<vector<char>> &board, string &word, int i, int j, int idx)
    {
        if (idx == word.size())
            return true;

        int n = board.size();
        int m = board[0].size();

        if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] != word[idx])
            return false;

        char ch = board[i][j];
        board[i][j] = '#'; // mark visited

        bool found =
            dfs(board, word, i + 1, j, idx + 1) ||
            dfs(board, word, i - 1, j, idx + 1) ||
            dfs(board, word, i, j + 1, idx + 1) ||
            dfs(board, word, i, j - 1, idx + 1);

        board[i][j] = ch; // backtrack
        return found;
    }

    bool exist(vector<vector<char>> &board, string word)
    {
        int n = board.size();
        int m = board[0].size();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }

        return false;
    }
};

int main()
{
    Solution obj;

    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};

    string word = "ABCCED";

    cout << (obj.exist(board, word) ? "true" : "false");

    return 0;
}

/*

==================================================
Problem Statement
==================================================

LeetCode 79 - Word Search

Given an m x n board of characters and a string word,
return true if the word exists in the grid.

The word can be constructed from sequentially adjacent cells
(horizontal or vertical only).

A cell cannot be used more than once in one path.

--------------------------------------------------

Example

Input:
board =
A B C E
S F C S
A D E E

word = "ABCCED"

Output:
true

==================================================
Approach 1 : Brute Force DFS
==================================================

Idea
----

Start DFS from every cell.

Try all possible paths recursively while keeping track of visited cells
using a separate visited matrix.

Pseudo Code
-----------

for every cell

    DFS(row,col,index)

DFS

if index==word length
    return true

if invalid
    return false

mark visited

try all 4 directions

unmark visited

Complete Brute Force Code
-------------------------

// bool dfs(vector<vector<char>>& board,
//          vector<vector<int>>& vis,
//          string &word,
//          int i,
//          int j,
//          int idx){
//
//     if(idx==word.size())
//         return true;
//
//     if(i<0||j<0||i>=board.size()||j>=board[0].size())
//         return false;
//
//     if(vis[i][j])
//         return false;
//
//     if(board[i][j]!=word[idx])
//         return false;
//
//     vis[i][j]=1;
//
//     bool ans=
//         dfs(board,vis,word,i+1,j,idx+1)||
//         dfs(board,vis,word,i-1,j,idx+1)||
//         dfs(board,vis,word,i,j+1,idx+1)||
//         dfs(board,vis,word,i,j-1,idx+1);
//
//     vis[i][j]=0;
//
//     return ans;
// }

Time Complexity
---------------
O(N*M*4^L)

L = word length

Space Complexity
----------------
O(N*M) + O(L)

==================================================
Approach 2 : Optimal Backtracking (In-place Visited)
==================================================

Observation
-----------

The board itself can be used as the visited array.

Instead of maintaining another matrix,
temporarily replace the current character with '#'.

After recursion restore it.

This saves extra memory.

Intuition
---------

Start DFS from every cell.

Whenever a character matches,

visit it,

mark visited,

explore four neighbours,

restore the character before returning.

Pseudo Code
-----------

for every cell

    if dfs(cell,0)
        return true

DFS

if index==word length
    return true

if invalid
    return false

save character

mark '#'

search four directions

restore character

return result

Complete Optimal Code
---------------------

class Solution {
public:

    bool dfs(vector<vector<char>>& board,string &word,int i,int j,int idx){

        if(idx==word.size())
            return true;

        if(i<0||j<0||i>=board.size()||j>=board[0].size())
            return false;

        if(board[i][j]!=word[idx])
            return false;

        char ch=board[i][j];
        board[i][j]='#';

        bool ans=
            dfs(board,word,i+1,j,idx+1)||
            dfs(board,word,i-1,j,idx+1)||
            dfs(board,word,i,j+1,idx+1)||
            dfs(board,word,i,j-1,idx+1);

        board[i][j]=ch;

        return ans;
    }

    bool exist(vector<vector<char>>& board,string word){

        for(int i=0;i<board.size();i++)
            for(int j=0;j<board[0].size();j++)
                if(dfs(board,word,i,j,0))
                    return true;

        return false;
    }
};

Time Complexity
---------------
O(N*M*4^L)

where

N = rows

M = columns

L = word length

Space Complexity
----------------
O(L)

(Recursion stack only)

==================================================
Dry Run
==================================================

Board

A B C E
S F C S
A D E E

Word

ABCCED

Start at (0,0)

A ✓

↓

B ✓

↓

C ✓

↓

C ✓

↓

E ✓

↓

D ✓

Reached end of word

Answer = true

==================================================
Interview Notes
==================================================

Pattern
-------

Backtracking + DFS on Grid

Key Observation
---------------

A cell cannot be reused in the same path.

Mark visited during recursion and restore while backtracking.

Common Mistakes
---------------

1. Forgetting to restore the character.

2. Revisiting the same cell.

3. Using diagonal moves.

4. Returning true before checking all directions.

When to use this approach
-------------------------

Use Backtracking whenever

• Need to search all possible paths

• Grid path problems

• Each cell/state can only be used once in one path

Examples:
- Word Search
- Sudoku Solver
- N Queens
- Rat in a Maze

*/
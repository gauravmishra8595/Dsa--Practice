#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isSafe(vector<string> &board, int row, int col, int n)
    {

        for (int j = 0; j < n; j++)
        {
            if (board[row][j] == 'Q')
            {
                return false;
            }
        }

        for (int i = 0; i < row; i++)
        {
            if (board[i][col] == 'Q')
            {
                return false;
            }
        }

        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == 'Q')
            {
                return false;
            }
        }

        for (int i = row, j = col; i >= 0 && j < n; i--, j++)
        {
            if (board[i][j] == 'Q')
            {
                return false;
            }
        }

        return true;
    }

    void nQueens(vector<string> &board, int row, int n,
                 vector<vector<string>> &ans)
    {

        if (row == n)
        {
            ans.push_back(board);
            return;
        }

        for (int j = 0; j < n; j++)
        {
            if (isSafe(board, row, j, n))
            {
                board[row][j] = 'Q';

                nQueens(board, row + 1, n, ans);

                board[row][j] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        vector<string> board(n, string(n, '.'));
        vector<vector<string>> ans;

        nQueens(board, 0, n, ans);

        return ans;
    }
};

int main()
{
    int n;

    cout << "Enter n: ";
    cin >> n;

    Solution obj;
    vector<vector<string>> ans = obj.solveNQueens(n);

    cout << "\nNumber of solutions: " << ans.size() << "\n\n";

    for (int k = 0; k < ans.size(); k++)
    {
        cout << "Solution " << k + 1 << ":\n";

        for (string row : ans[k])
        {
            cout << row << "\n";
        }

        cout << "\n";
    }

    return 0;
}
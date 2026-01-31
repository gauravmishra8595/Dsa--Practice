#include <iostream>
using namespace std;

#define MAX 20

int board[MAX][MAX];
int n;

// Check if a queen can be placed at board[row][col]
bool isSafe(int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Print the board
void printBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << endl;
    }
    cout << endl;
}

// Solve N-Queen using backtracking
void solveNQueen(int row) {
    if (row == n) {
        printBoard();
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            solveNQueen(row + 1);
            board[row][col] = 0; // backtrack
        }
    }
}

int main() {
    cout << "Enter number of queens: ";
    cin >> n;

    solveNQueen(0);

    return 0;
}

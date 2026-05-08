#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {

                if (matrix[i][j] != matrix[i - 1][j - 1]) {
                    return false;
                }

            }
        }

        return true;
    }
};

int main() {
    Solution obj;

    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 1, 2, 3},
        {9, 5, 1, 2}
    };

    bool ans = obj.isToeplitzMatrix(matrix);

    if (ans) {
        cout << "Matrix is Toeplitz" << endl;
    } else {
        cout << "Matrix is NOT Toeplitz" << endl;
    }

    return 0;
}
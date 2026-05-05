#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        int row = mat.size();
        int col = mat[0].size();

        // if reshape not possible, return original matrix
        if (row * col != r * c) return mat;

        vector<vector<int>> res(r, vector<int>(c));

        for (int i = 0; i < row * col; i++) {
            res[i / c][i % c] = mat[i / col][i % col];
        }

        return res;
    }
};

int main() {
    Solution obj;

    vector<vector<int>> mat = {
        {1, 2},
        {3, 4}
    };

    int r = 1, c = 4;

    vector<vector<int>> ans = obj.matrixReshape(mat, r, c);

    for (auto &row : ans) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
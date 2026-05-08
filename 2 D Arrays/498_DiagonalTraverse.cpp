#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {

        int rows = mat.size();
        int cols = mat[0].size();

        vector<int> ans;

        int row = 0;
        int col = 0;

        // 1 = up-right
        // 0 = down-left
        int dir = 1;

        for (int i = 0; i < rows * cols; i++) {

            ans.push_back(mat[row][col]);

            // Moving Up-Right
            if (dir == 1) {

                row--;
                col++;

                // Hit right boundary
                if (col == cols) {
                    row += 2;
                    col--;
                    dir = 0;
                }

                // Hit top boundary
                else if (row < 0) {
                    row = 0;
                    dir = 0;
                }
            }

            // Moving Down-Left
            else {

                row++;
                col--;

                // Hit bottom boundary
                if (row == rows) {
                    col += 2;
                    row--;
                    dir = 1;
                }

                // Hit left boundary
                else if (col < 0) {
                    col = 0;
                    dir = 1;
                }
            }
        }

        return ans;
    }
};

int main() {

    Solution obj;

    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> result = obj.findDiagonalOrder(mat);

    cout << "Diagonal Traverse Order:" << endl;

    for (int num : result) {
        cout << num << " ";
    }

    return 0;
}
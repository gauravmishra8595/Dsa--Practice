#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {

        vector<vector<int>> ans(n, vector<int>(n));

        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;

        int val = 1;

        while (top <= bottom && left <= right) {

            // left -> right
            for (int i = left; i <= right; i++) {
                ans[top][i] = val++;
            }
            top++;

            // top -> bottom
            for (int i = top; i <= bottom; i++) {
                ans[i][right] = val++;
            }
            right--;

            // right -> left
            if (top <= bottom) {
                for (int i = right; i >= left; i--) {
                    ans[bottom][i] = val++;
                }
                bottom--;
            }

            // bottom -> top
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    ans[i][left] = val++;
                }
                left++;
            }
        }

        return ans;
    }
};

int main() {

    int n;
    cout<<"Enter the value of n:";
    cin >> n;

    Solution obj;

    vector<vector<int>> result = obj.generateMatrix(n);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
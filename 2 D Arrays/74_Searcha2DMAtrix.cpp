#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int s = 0;
        int e = m * n - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;

            int row = mid / n;
            int col = mid % n;

            if (matrix[row][col] == target) {
                return true;
            } 
            else if (matrix[row][col] < target) {
                s = mid + 1;
            } 
            else {
                e = mid - 1;
            }
        }

        return false;
    }
};

int main() {
    Solution obj;

    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target = 3;

    if (obj.searchMatrix(matrix, target)) {
        cout << "Found\n";
    } else {
        cout << "Not Found\n";
    }

    return 0;
}
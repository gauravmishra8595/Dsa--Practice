#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int idx = m + n - 1, i = m - 1, j = n - 1;

        while (j >= 0) {
            if (i >= 0 && A[i] > B[j]) {
                A[idx--] = A[i--];
            } else {
                A[idx--] = B[j--];
            }
        }
    }
};

int main() {
    vector<int> A = {1, 2, 3, 0, 0, 0};
    vector<int> B = {2, 5, 6};
    int m = 3, n = 3;

    Solution obj;
    obj.merge(A, m, B, n);

    cout << "Merged array: ";
    for (int x : A) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
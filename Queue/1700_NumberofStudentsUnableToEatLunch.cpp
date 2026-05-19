#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int> qt;

        for (int s : students) {
            qt.push(s);
        }

        int idx = 0;
        int fail = 0;

        while (!qt.empty()) {
            if (qt.front() == sandwiches[idx]) {
                qt.pop();
                idx++;
                fail = 0;
            }
            else {
                int x = qt.front();
                qt.pop();
                qt.push(x);
                fail++;
            }

            if (fail == qt.size()) {
                return qt.size();
            }
        }

        return 0;
    }
};

int main() {
    Solution sol;

    vector<int> students = {1, 1, 0, 0};
    vector<int> sandwiches = {0, 1, 0, 1};

    cout << sol.countStudents(students, sandwiches) << endl;

    return 0;
}
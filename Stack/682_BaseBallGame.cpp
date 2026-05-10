#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        int total_sum = 0;

        for (int i = 0; i < operations.size(); i++) {
            string op = operations[i];

            if (op == "+") {
                int a = st.top(); st.pop();
                int b = st.top();
                st.push(a);

                int x = a + b;
                st.push(x);
                total_sum += x;
            }
            else if (op == "C") {
                int x = st.top();
                st.pop();
                total_sum -= x;
            }
            else if (op == "D") {
                int x = 2 * st.top();
                st.push(x);
                total_sum += x;
            }
            else {
                int x = stoi(op);
                st.push(x);
                total_sum += x;
            }
        }

        return total_sum;
    }
};

int main() {
    Solution sol;

    vector<string> operations = {"5", "2", "20", "D", "+"};

    cout << sol.calPoints(operations) << endl;

    return 0;
}
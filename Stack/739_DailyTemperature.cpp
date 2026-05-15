#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();

        vector<int> ans(n, 0);
        stack<int> st;

        for (int i = 0; i < n; i++) {

            while (!st.empty() &&
                   temperatures[i] > temperatures[st.top()]) {

                int prev = st.top();
                st.pop();

                ans[prev] = i - prev;
            }

            st.push(i);
        }

        return ans;
    }
};

int main() {

    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    Solution obj;

    vector<int> result = obj.dailyTemperatures(temperatures);

    cout << "Output: ";

    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}

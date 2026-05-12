#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    string makeGood(string s) {
        stack<char> st;

        for (char c : s) {
            if (!st.empty() && abs(st.top() - c) == 32) {
                st.pop();
            } 
            else {
                st.push(c);
            }
        }

        string ans = "";

        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main() {
    Solution obj;

    string s = "leEeetcode";

    cout << obj.makeGood(s) << endl;

    return 0;
}
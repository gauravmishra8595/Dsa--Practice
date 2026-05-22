#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    string removeStars(string s) {
        stack<char> st;
        string ans = "";

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '*') {
                st.pop();
            } else {
                st.push(s[i]);
            }
        }

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

    string s;
    cin >> s;

    cout << obj.removeStars(s);

    return 0;
}
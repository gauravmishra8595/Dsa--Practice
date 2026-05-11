#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:

    string build(string str) {
        stack<char> st;

        for (char ch : str) {

            if (ch != '#') {
                st.push(ch);
            }
            else {
                if (!st.empty()) {
                    st.pop();
                }
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

    bool backspaceCompare(string s, string t) {

        return build(s) == build(t);
    }
};

int main() {

    Solution obj;

    string s = "ab#c";
    string t = "ad#c";

    if (obj.backspaceCompare(s, t)) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }

    return 0;
}
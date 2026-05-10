#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        string ans = "";

        for (char c : s) {
            if (!st.empty() && st.top() == c) {
                st.pop();
            } 
            else {
                st.push(c);
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
    cout << "Enter string: ";
    cin >> s;

    string result = obj.removeDuplicates(s);

    cout << "Final string: " << result << endl;

    return 0;
}
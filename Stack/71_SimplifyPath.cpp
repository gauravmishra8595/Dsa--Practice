#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> st;
        string temp = "";

        for (int i = 0; i < path.size(); i++) {

            if (path[i] == '/') {

                if (temp == "" || temp == ".") {
                    // ignore
                }
                else if (temp == "..") {
                    if (!st.empty())
                        st.pop();
                }
                else {
                    st.push(temp);
                }

                temp = "";
            }
            else {
                temp += path[i];
            }
        }

        // Process last token
        if (temp == "..") {
            if (!st.empty())
                st.pop();
        }
        else if (temp != "" && temp != ".") {
            st.push(temp);
        }

        // Build final answer
        vector<string> dirs;

        while (!st.empty()) {
            dirs.push_back(st.top());
            st.pop();
        }

        reverse(dirs.begin(), dirs.end());

        string ans = "";

        for (string dir : dirs) {
            ans += "/" + dir;
        }

        return ans.empty() ? "/" : ans;
    }
};

int main() {
    Solution obj;

    string path;

    cout << "Enter path: ";
    cin >> path;

    cout << "Simplified Path: " << obj.simplifyPath(path) << endl;

    return 0;
}
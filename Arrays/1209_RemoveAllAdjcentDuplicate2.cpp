#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        int n = s.size();

        stack<pair<char, int>> st;
        string ans = "";

        for (int i = 0; i < n; i++) {

            // Same character as stack top
            if (!st.empty() && st.top().first == s[i]) {

                st.top().second++;

                // Remove group if count reaches k
                if (st.top().second == k) {
                    st.pop();
                }

            } 
            else {
                // Start new group
                st.push({s[i], 1});
            }
        }

        // Rebuild final string
        while (!st.empty()) {

            int cnt = st.top().second;
            char ch = st.top().first;

            st.pop();

            while (cnt--) {
                ans += ch;
            }
        }

        // Stack reverses order
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main() {

    Solution obj;

    string s;
    int k;

    cout << "Enter string: ";
    cin >> s;

    cout << "Enter k: ";
    cin >> k;

    string result = obj.removeDuplicates(s, k);

    cout << "Final string: " << result << endl;

    return 0;
}
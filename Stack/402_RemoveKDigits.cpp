#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        int n = num.size();

        for (int i = 0; i < n; i++) {
            char current = num[i];

            while (!st.empty() && st.top() > current && k > 0) {
                st.pop();
                k--;
            }

            st.push(current);
        }

        while (k > 0 && !st.empty()) {
            st.pop();
            k--;
        }

        string ans = "";

        while (!st.empty()) {
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        int i = 0;
        while (i < ans.size() && ans[i] == '0') {
            i++;
        }

        ans = ans.substr(i);

        if (ans == "")
            return "0";

        return ans;
    }
};

int main() {
    Solution obj;

    string num;
    int k;

    cout << "Enter number: ";
    cin >> num;

    cout << "Enter k: ";
    cin >> k;

    cout << "Smallest number: " << obj.removeKdigits(num, k);

    return 0;
}
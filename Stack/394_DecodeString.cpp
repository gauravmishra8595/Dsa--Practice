#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        stack<int> nums;

        string curr = "";
        int count = 0;

        for (int i = 0; i < s.size(); i++) {

            if (isdigit(s[i])) {
                count = count * 10 + (s[i] - '0');
            }

            else if (s[i] == '[') {
                nums.push(count);
                st.push(curr);

                count = 0;
                curr = "";
            }

            else if (s[i] == ']') {
                int repeat = nums.top();
                nums.pop();

                string prev = st.top();
                st.pop();

                string temp = "";
                for (int j = 0; j < repeat; j++) {
                    temp += curr;
                }

                curr = prev + temp;
            }

            else {
                curr += s[i];
            }
        }

        return curr;
    }
};

int main() {
    Solution obj;

    string s;
    cout << "Enter encoded string: ";
    cin >> s;

    string result = obj.decodeString(s);

    cout << "Decoded string: " << result << endl;

    return 0;
}
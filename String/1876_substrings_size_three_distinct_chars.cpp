#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int countGoodSubstrings(string s) {
        int len = 0;

        for (int i = 0; i + 2 < s.size(); i++) {
            if (s[i] != s[i+1] &&
                s[i+1] != s[i+2] &&
                s[i] != s[i+2]) {
                len++;
            }
        }

        return len;
    }
};

int main() {
    Solution sol;

    string s;
    cout << "Enter a string: ";
    cin >> s;

    int result = sol.countGoodSubstrings(s);
    cout << "Number of good substrings of size 3: " << result << endl;

    return 0;
}


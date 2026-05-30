#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> freq;

        for (char ch : s) {
            freq[ch]++;
        }

        for (int i = 0; i < s.size(); i++) {
            if (freq[s[i]] == 1) {
                return i;
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;

    string s;
    cout << "Enter string: ";
    cin >> s;

    int result = sol.firstUniqChar(s);

    cout << "First unique character index: " << result << endl;

    return 0;
}
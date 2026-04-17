#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0;

        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == ' ' && count == 0) continue;
            if (s[i] == ' ') break;
            count++;
        }

        return count;
    }
};

int main() {
    Solution obj;

    string s;
    cout << "Enter string: ";
    getline(cin, s);

    int result = obj.lengthOfLastWord(s);

    cout << "Length of last word: " << result << endl;

    return 0;
}
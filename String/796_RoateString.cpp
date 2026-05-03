#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;

        string temp = s + s;
        return temp.find(goal) != string::npos;
    }
};

int main() {
    Solution obj;

    cout << obj.rotateString("abcde", "cdeab") << endl; // 1 (true)
    cout << obj.rotateString("abcde", "abced") << endl; // 0 (false)

    return 0;
}
#include <iostream>
#include <string>
#include <algorithm> // for sort

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false; 
        }
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t; 
    }
};

int main() {
    Solution solution;

    string s, t;
    cout << "Enter first string: ";
    cin >> s;
    cout << "Enter second string: ";
    cin >> t;

    if (solution.isAnagram(s, t)) {
        cout << "The strings are anagrams." << endl;
    } else {
        cout << "The strings are NOT anagrams." << endl;
    }

    return 0;
}

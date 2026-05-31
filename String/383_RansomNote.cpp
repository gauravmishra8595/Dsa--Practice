#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> mp;

        // Characters needed
        for (char ch : ransomNote) {
            mp[ch]--;
        }

        // Characters available
        for (char ch : magazine) {
            mp[ch]++;
        }

        // Check if any character is still lacking
        for (auto it : mp) {
            if (it.second < 0) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Solution sol;

    string ransomNote, magazine;

    cout << "Enter ransomNote: ";
    cin >> ransomNote;

    cout << "Enter magazine: ";
    cin >> magazine;

    if (sol.canConstruct(ransomNote, magazine)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
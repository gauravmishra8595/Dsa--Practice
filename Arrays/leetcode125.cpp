#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool isPalindrome(const string &s) {
        int left = 0, right = s.size() - 1;

        while (left < right) {
            // Skip non-alphanumeric characters
            while (left < right && !isAlnum(s[left])) left++;
            while (left < right && !isAlnum(s[right])) right--;

            // Compare lowercase letters using ASCII trick
            if (toLower(s[left]) != toLower(s[right])) return false;

            left++;
            right--;
        }

        return true;
    }

private:
    bool isAlnum(char c) {
        return (c >= '0' && c <= '9') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= 'a' && c <= 'z');
    }

    char toLower(char c) {
        if (c >= 'A' && c <= 'Z') return c | 32; // ASCII trick
        return c;
    }
};

int main() {
    Solution sol;
    string input;

    cout << "Enter a string to check if it's a palindrome: ";
    getline(cin, input);

    if (sol.isPalindrome(input)) {
        cout << "The string is a palindrome!" << endl;
    } else {
        cout << "The string is NOT a palindrome." << endl;
    }

    return 0;
}
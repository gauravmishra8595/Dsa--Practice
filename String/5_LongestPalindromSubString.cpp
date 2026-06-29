#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();

        if (n <= 1) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {

            // ---------------------------
            // Odd length palindrome
            // ---------------------------
            int left = i;
            int right = i;

            while (left >= 0 && right < n && s[left] == s[right]) {
                int len = right - left + 1;
                if (len > maxLen) {
                    maxLen = len;
                    start = left;
                }
                left--;
                right++;
            }

            // ---------------------------
            // Even length palindrome
            // ---------------------------
            left = i;
            right = i + 1;

            while (left >= 0 && right < n && s[left] == s[right]) {
                int len = right - left + 1;
                if (len > maxLen) {
                    maxLen = len;
                    start = left;
                }
                left--;
                right++;
            }
        }

        return s.substr(start, maxLen);
    }
};

int main() {
    Solution sol;

    string s;
    cout << "Enter string: ";
    cin >> s;

    cout << sol.longestPalindrome(s) << endl;

    return 0;
}

/*
========================================================
BRUTE FORCE APPROACH (CODE - FOR UNDERSTANDING ONLY)
========================================================

class SolutionBrute {
public:
    bool isPalindrome(string &s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }

    string longestPalindrome(string s) {
        int n = s.size();
        string ans = "";

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {

                if (isPalindrome(s, i, j)) {
                    int len = j - i + 1;

                    if (len > ans.size()) {
                        ans = s.substr(i, len);
                    }
                }
            }
        }

        return ans;
    }
};

--------------------------------------------------------
BRUTE FORCE IDEA:
- Try every substring (i, j)
- Check if palindrome

Time: O(n^3)
Space: O(1)

========================================================
OPTIMAL APPROACH (USED ABOVE IN MAIN CODE)
========================================================

IDEA:
- Every palindrome has a center
- Expand from center

TWO CASES:
1. Odd length  -> center at i
2. Even length -> center at i, i+1

Time: O(n^2)
Space: O(1)

WHY BETTER:
- No substring generation
- Only expand outward from center
========================================================
*/
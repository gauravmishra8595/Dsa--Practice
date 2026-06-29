#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int romanToInt(string s)
    {

        // ---------------------------
        // OPTIMAL APPROACH (USED)
        // ---------------------------
        unordered_map<char, int> mp = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}};

        int n = s.size();
        int result = 0;

        for (int i = 0; i < n; i++)
        {

            // If current value is less than next value → subtract
            if (i < n - 1 && mp[s[i]] < mp[s[i + 1]])
            {
                result -= mp[s[i]];
            }
            else
            {
                result += mp[s[i]];
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;

    string s;
    cout << "Enter Roman numeral: ";
    cin >> s;

    cout << sol.romanToInt(s) << endl;

    return 0;
}

/*
========================================================
BRUTE FORCE APPROACH (FOR UNDERSTANDING)
========================================================

IDEA:
1. Convert each Roman character to value
2. Handle special subtractive cases manually:
   - IV = 4
   - IX = 9
   - XL = 40
   - XC = 90
   - CD = 400
   - CM = 900

--------------------------------------------------------

class SolutionBrute {
public:
    int value(char c) {
        if (c == 'I') return 1;
        if (c == 'V') return 5;
        if (c == 'X') return 10;
        if (c == 'L') return 50;
        if (c == 'C') return 100;
        if (c == 'D') return 500;
        if (c == 'M') return 1000;
        return 0;
    }

    int romanToInt(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {

            int curr = value(s[i]);

            if (i + 1 < n) {
                int next = value(s[i + 1]);

                if (curr < next) {
                    ans += (next - curr);
                    i++; // skip next
                }
                else {
                    ans += curr;
                }
            }
            else {
                ans += curr;
            }
        }

        return ans;
    }
};

--------------------------------------------------------
BRUTE FORCE COMPLEXITY:
Time: O(n)
Space: O(1)

--------------------------------------------------------
OPTIMAL APPROACH:
- Compare current and next symbol
- Subtract if smaller, else add

Time: O(n)
Space: O(1)
========================================================
*/
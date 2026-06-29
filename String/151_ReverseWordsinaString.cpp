#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {

        reverse(s.begin(), s.end());

        int n = s.size();
        int i = 0;
        string result = "";

        while (i < n)
        {

            // skip spaces
            while (i < n && s[i] == ' ')
                i++;

            if (i >= n)
                break;

            string word = "";

            // extract word
            while (i < n && s[i] != ' ')
            {
                word += s[i];
                i++;
            }

            // reverse word back
            reverse(word.begin(), word.end());

            if (result.size() == 0)
                result = word;
            else
                result += " " + word;
        }

        return result;
    }
};

int main()
{
    Solution sol;

    string s;
    cout << "Enter string: ";
    getline(cin, s);

    cout << sol.reverseWords(s) << endl;

    return 0;
}

/*
========================================================
BRUTE FORCE APPROACH (FOR UNDERSTANDING)
========================================================

IDEA:
1. Split string into words
2. Store words in a vector
3. Reverse the vector
4. Join words with single spaces

--------------------------------------------------------

class SolutionBrute {
public:
    string reverseWords(string s) {

        vector<string> words;
        int n = s.size();
        int i = 0;

        while (i < n) {

            // skip spaces
            while (i < n && s[i] == ' ') i++;

            if (i >= n) break;

            string word = "";

            while (i < n && s[i] != ' ') {
                word += s[i];
                i++;
            }

            words.push_back(word);
        }

        reverse(words.begin(), words.end());

        string ans = "";

        for (int i = 0; i < words.size(); i++) {
            if (i > 0) ans += " ";
            ans += words[i];
        }

        return ans;
    }
};

--------------------------------------------------------
BRUTE FORCE COMPLEXITY:
Time: O(n)
Space: O(n)

--------------------------------------------------------
OPTIMAL APPROACH:
- Reverse string
- Fix each word
- No extra vector

Time: O(n)
Space: O(1) extra (excluding output)
========================================================
*/
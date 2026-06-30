#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        // Edge case
        if (strs.empty())
            return "";

        // Assume first string is the common prefix
        string prefix = strs[0];

        // Compare prefix with every other string
        for (int i = 1; i < strs.size(); i++) {

            // Reduce prefix until it becomes a prefix of current string
            while (strs[i].find(prefix) != 0) {
                prefix.pop_back();

                // If prefix becomes empty
                if (prefix.empty())
                    return "";
            }
        }

        return prefix;
    }
};

int main() {

    int n;

    cout << "Enter number of strings: ";
    cin >> n;

    vector<string> strs(n);

    cout << "Enter strings:\n";

    for (int i = 0; i < n; i++) {
        cin >> strs[i];
    }

    Solution obj;

    string ans = obj.longestCommonPrefix(strs);

    cout << "Longest Common Prefix = " << ans << endl;

    return 0;
}

/*
==========================
Brute Force Approach
==========================

Idea:
1. Take the first string.
2. Check each character one by one.
3. Compare that character with every other string.
4. If any string has different character or becomes shorter,
   stop and return the prefix obtained so far.

Pseudo Code:

answer = ""

for each character index i of first string

    currentChar = firstString[i]

    for every remaining string

        if i >= string length OR string[i] != currentChar
            return answer

    answer += currentChar

return answer

Time Complexity:
O(N * M)

N = Number of strings
M = Length of smallest string

Space Complexity:
O(1)

--------------------------------------------------

Brute Force Code

string longestCommonPrefix(vector<string>& strs)
{
    if(strs.empty())
        return "";

    string ans = "";

    for(int i = 0; i < strs[0].size(); i++)
    {
        char ch = strs[0][i];

        for(int j = 1; j < strs.size(); j++)
        {
            if(i >= strs[j].size() || strs[j][i] != ch)
                return ans;
        }

        ans += ch;
    }

    return ans;
}

==================================================
Optimal Approach (Implemented Above)
==================================================

Idea:

1. Assume the first string is the answer.
2. Compare it with every other string.
3. If current string doesn't start with the prefix,
   remove one character from the end.
4. Continue shrinking until it becomes a valid prefix.
5. After comparing all strings,
   remaining prefix is the answer.

Example:

Input:
flower
flow
flight

Initial Prefix = flower

Compare with flow
flower -> flowe -> flow

Compare with flight
flow -> flo -> fl

Answer = fl

Time Complexity:
O(N * M)

N = Number of strings
M = Length of smallest string

Space Complexity:
O(1)

Why is this Optimal?

Because each character is removed from the prefix at most once,
making it efficient without creating extra strings repeatedly.

LeetCode Problem:
14. Longest Common Prefix
*/
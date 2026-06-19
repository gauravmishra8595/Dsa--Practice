#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordset(wordDict.begin(), wordDict.end());

        int maxLen = 0;
        for (string word : wordDict) {
            maxLen = max(maxLen, (int)word.length());
        }

        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 0; i <= n; i++) {
            for (int j = i - 1; j >= max(0, i - maxLen); j--) {
                if (dp[j] && wordset.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;

    string s = "leetcode";
    vector<string> wordDict = {"leet", "code"};

    if (sol.wordBreak(s, wordDict))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}
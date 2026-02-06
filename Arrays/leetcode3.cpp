#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastIndex;
        int maxLen = 0, start = 0;

        for (int i = 0; i < s.size(); i++) {
            if (lastIndex.count(s[i]) && lastIndex[s[i]] >= start)
                start = lastIndex[s[i]] + 1;

            maxLen = max(maxLen, i - start + 1);
            lastIndex[s[i]] = i;
        }

        return maxLen;
    }
};


int main() {
    Solution sol;
    string test = "abcabcbb";
    cout << "Longest substring length: " << sol.lengthOfLongestSubstring(test) << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;

        for (string s : strs) {
            vector<int> freq(26, 0);
            for (char c : s) {
                freq[c - 'a']++;
            }

            string key = "";
            for (int i = 0; i < 26; i++) {
                key += to_string(freq[i]) + "#";
            }

            mp[key].push_back(s);
        }

        vector<vector<string>> ans;
        for (auto &it : mp) {
            ans.push_back(it.second);
        }

        return ans;
    }
};

int main() {
    Solution obj;

    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    vector<vector<string>> result = obj.groupAnagrams(strs);

    for (auto &group : result) {
        for (auto &word : group) {
            cout << word << " ";
        }
        cout << endl;
    }

    return 0;
}
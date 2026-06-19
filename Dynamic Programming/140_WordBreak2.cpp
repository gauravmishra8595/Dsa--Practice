#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution
{
    unordered_set<string> wordSet;
    unordered_map<string, vector<string>> memo;

public:
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        wordSet = unordered_set<string>(wordDict.begin(), wordDict.end());
        return dfs(s);
    }

    vector<string> dfs(string s)
    {
        if (memo.count(s))
            return memo[s];

        vector<string> res;

        if (s.empty())
        {
            res.push_back("");
            return res;
        }

        for (int i = 1; i <= s.size(); i++)
        {
            string prefix = s.substr(0, i);

            if (!wordSet.count(prefix))
                continue;

            vector<string> suffixWays = dfs(s.substr(i));

            for (string way : suffixWays)
            {
                if (way.empty())
                    res.push_back(prefix);
                else
                    res.push_back(prefix + " " + way);
            }
        }

        return memo[s] = res;
    }
};

int main()
{
    Solution sol;

    string s = "catsanddog";
    vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};

    vector<string> ans = sol.wordBreak(s, wordDict);

    for (string str : ans)
        cout << str << endl;

    return 0;
}
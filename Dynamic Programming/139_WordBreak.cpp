#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool solve(string &s, int idx, unordered_set<string> &st, vector<int> &dp)
    {
        if (idx == s.size())
            return true;

        if (dp[idx] != -1)
            return dp[idx];

        string temp = "";

        for (int i = idx; i < s.size(); i++)
        {
            temp += s[i];

            if (st.count(temp) && solve(s, i + 1, st, dp))
                return dp[idx] = true;
        }

        return dp[idx] = false;
    }

    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> st(wordDict.begin(), wordDict.end());

        vector<int> dp(s.size(), -1);

        return solve(s, 0, st, dp);
    }
};

int main()
{
    string s;
    cin >> s;

    int n;
    cin >> n;

    vector<string> wordDict(n);

    for (int i = 0; i < n; i++)
        cin >> wordDict[i];

    Solution obj;
    cout << obj.wordBreak(s, wordDict);

    return 0;
}

/*

=========================================================
LeetCode 139. Word Break
=========================================================

Problem Statement
-----------------
Given a string s and a dictionary of strings wordDict,
return true if s can be segmented into a space-separated
sequence of one or more dictionary words.

A dictionary word may be reused multiple times.

=========================================================
Example
=========================================================

Input:
s = "leetcode"

wordDict =
["leet","code"]

Output:
true

Explanation:

"leetcode"

=

"leet"

+

"code"

=========================================================
Brute Force Approach
=========================================================

Idea
----

Starting from index 0,

try every possible substring.

If the substring exists in the dictionary,

recursively solve the remaining string.

If any path reaches the end,

answer is true.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(idx)

if idx==n
    return true

temp=""

for i=idx to n-1

    temp+=s[i]

    if temp in dictionary

        if solve(i+1)

            return true

return false

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:

    bool solve(string &s,int idx,unordered_set<string>& st){

        if(idx==s.size())
            return true;

        string temp="";

        for(int i=idx;i<s.size();i++){

            temp+=s[i];

            if(st.count(temp)){

                if(solve(s,i+1,st))
                    return true;
            }
        }

        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {

        unordered_set<string> st(wordDict.begin(),
                                 wordDict.end());

        return solve(s,0,st);
    }
};

Time Complexity
---------------
Exponential
O(2^N)

Space Complexity
----------------
O(N)

=========================================================
Optimal Approach (Memoization)
=========================================================

Observation
-----------

The same starting index gets solved repeatedly.

Example:

solve(4)

may be called from multiple previous partitions.

Store the answer for every starting index.

---------------------------------------------------------
Intuition
---------------------------------------------------------

Let

dp[idx]

=

Can the substring

s[idx...]

be segmented?

If already computed,

return it directly.

Otherwise,

try every substring starting at idx.

If one valid dictionary word leads to success,

store true.

Else store false.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(idx)

if idx==n
    return true

if dp[idx]!=-1
    return dp[idx]

temp=""

for every substring

    if substring exists

        if solve(next)

            return dp[idx]=true

return dp[idx]=false

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {
public:

    bool solve(string &s,int idx,
               unordered_set<string>& st,
               vector<int>& dp){

        if(idx==s.size())
            return true;

        if(dp[idx]!=-1)
            return dp[idx];

        string temp="";

        for(int i=idx;i<s.size();i++){

            temp+=s[i];

            if(st.count(temp) &&
               solve(s,i+1,st,dp))

                return dp[idx]=true;
        }

        return dp[idx]=false;
    }

    bool wordBreak(string s,
                   vector<string>& wordDict) {

        unordered_set<string> st(wordDict.begin(),
                                 wordDict.end());

        vector<int> dp(s.size(),-1);

        return solve(s,0,st,dp);
    }
};

Time Complexity
---------------
O(N²)

Explanation:

There are N states.

For each state,

we may build/check up to N substrings.

Space Complexity
----------------
O(N)

DP array

+

O(N)

recursion stack

=========================================================
Dry Run
=========================================================

Input

s = "leetcode"

Dictionary

["leet","code"]

Start

solve(0)

Try

"l"

Not found

Try

"le"

Not found

Try

"lee"

Not found

Try

"leet"

Found

↓

solve(4)

Substring

"code"

Try

"c"

No

"co"

No

"cod"

No

"code"

Found

↓

solve(8)

idx==size

Return true

Backtrack

dp[4]=true

dp[0]=true

Answer = true

=========================================================
Interview Notes
=========================================================

Pattern
-------

Recursion + Memoization

String DP

Partition DP

---------------------------------------------------------

Key Observation
---------------

The problem asks:

Can the string be partitioned?

Every partition starts at some index.

Hence DP on index.

---------------------------------------------------------

Common Mistakes
---------------

1. Using vector<bool> for DP instead of
   three states (-1, true, false).

2. Forgetting the base case
   idx == s.size().

3. Using vector search instead of
   unordered_set.

4. Passing strings by value.

5. Recomputing the same starting index.

---------------------------------------------------------

When to use this approach
-------------------------

Use this whenever the problem asks:

• Can a string be segmented?

• Can a sequence be partitioned?

• Dictionary lookup problems

• Recursion on starting index

• Overlapping substring states

This is a classic Memoization / String DP problem.

=========================================================

*/
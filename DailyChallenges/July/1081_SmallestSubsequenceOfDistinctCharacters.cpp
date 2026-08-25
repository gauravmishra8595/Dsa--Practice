#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string smallestSubsequence(string s)
    {
        int n = s.size();

        vector<int> last(26);
        vector<bool> vis(26, false);

        for (int i = 0; i < n; i++)
            last[s[i] - 'a'] = i;

        string ans;

        for (int i = 0; i < n; i++)
        {
            char c = s[i];

            if (vis[c - 'a'])
                continue;

            while (!ans.empty() &&
                   ans.back() > c &&
                   last[ans.back() - 'a'] > i)
            {
                vis[ans.back() - 'a'] = false;
                ans.pop_back();
            }

            ans.push_back(c);
            vis[c - 'a'] = true;
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    string s;
    cin >> s;

    cout << obj.smallestSubsequence(s);

    return 0;
}

/*

===========================
LeetCode 1081 - Smallest Subsequence of Distinct Characters
===========================

Problem Statement
-----------------
Given a string s, return the lexicographically smallest subsequence of s that
contains all the distinct characters of s exactly once.

Example
-------
Input:
s = "cbacdcbc"

Output:
"acdb"

Explanation:
All distinct characters are {a,b,c,d}.
Among all valid subsequences containing each exactly once,
"acdb" is lexicographically smallest.

=========================================================
Brute Force Approach
=========================================================

Idea
----
Generate every subsequence.
Check:
1. Every distinct character appears exactly once.
2. Length equals number of distinct characters.
3. Keep lexicographically smallest valid answer.

Very expensive since there are 2^n subsequences.

Pseudo Code
-----------
find total distinct characters

ans = ""

generate(index, current)

    if index == n
        if current is valid
            update answer
        return

    take current character
    don't take current character

Complete Brute Force Code
-------------------------

class Solution {
public:
    string ans = "";

    void solve(int idx, string &s, string cur, set<char> &distinct) {

        if(idx == s.size()) {

            set<char> temp(cur.begin(), cur.end());

            if(temp.size() != distinct.size())
                return;

            if(cur.size() != distinct.size())
                return;

            if(ans == "" || cur < ans)
                ans = cur;

            return;
        }

        solve(idx + 1, s, cur, distinct);

        cur.push_back(s[idx]);
        solve(idx + 1, s, cur, distinct);
    }

    string smallestSubsequence(string s) {

        set<char> distinct(s.begin(), s.end());

        solve(0, s, "", distinct);

        return ans;
    }
};

Time Complexity
---------------
O(2^N * N)

Space Complexity
----------------
O(N)

=========================================================
Optimal Approach
=========================================================

Observation
-----------
Whenever we encounter a smaller character,
we may remove previously selected larger characters
only if they appear again later.

Need two things:
1. Is character already included?
2. Will removed character appear later?

Intuition
---------
Maintain a monotonic increasing stack (implemented using string).

For every character:

1. Skip if already present.

2. Otherwise,
   while
      top > current
      and top appears later
   pop it.

3. Push current.

Pseudo Code
-----------
compute last occurrence of every character

visited[26] = false

answer = ""

for each character

    if already visited
        continue

    while answer not empty
          and answer.back() > current
          and last[answer.back()] > current index

          mark top not visited
          pop

    push current
    mark visited

return answer

Complete Optimal Code
---------------------

class Solution {
public:

    string smallestSubsequence(string s) {

        vector<int> last(26);
        vector<bool> vis(26,false);

        for(int i=0;i<s.size();i++)
            last[s[i]-'a']=i;

        string ans;

        for(int i=0;i<s.size();i++){

            char c=s[i];

            if(vis[c-'a'])
                continue;

            while(!ans.empty() &&
                  ans.back()>c &&
                  last[ans.back()-'a']>i){

                vis[ans.back()-'a']=false;
                ans.pop_back();
            }

            ans.push_back(c);
            vis[c-'a']=true;
        }

        return ans;
    }
};

Time Complexity
---------------
O(N)

Space Complexity
----------------
O(26) = O(1)

=========================================================
Dry Run
=========================================================

Input:
cbacdcbc

Last Occurrence

c -> 7
b -> 6
a -> 2
d -> 4

Start

ans = ""

c
ans = c

b
c>b and c appears later
pop c

ans=b

a
b>a and b appears later
pop b

ans=a

c
push

ans=ac

d
push

ans=acd

c
already visited

b
d>b but d does NOT appear later
cannot pop

push b

ans=acdb

c
already visited

Answer = acdb

=========================================================
Interview Notes
=========================================================

Pattern
-------
Monotonic Stack + Greedy + Last Occurrence

Key Observation
---------------
Remove a larger character only if it can be taken again later.
Otherwise removing it loses a required distinct character forever.

Common Mistakes
---------------
1. Forgetting visited array.
2. Popping characters that never appear again.
3. Not updating visited while popping.
4. Using >= instead of > in comparison.
5. Forgetting to precompute last occurrence.

When to use this approach
-------------------------
Whenever the problem asks for:

- Lexicographically smallest sequence
- Remove/rearrange characters greedily
- Every element appears once
- Need future occurrence information
- Monotonic Stack based greedy optimization

*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<string>> ans;
    vector<string> path;

    bool isPalindrome(int i, int j, string &s)
    {
        while (i < j)
        {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }

    void solve(int index, string &s)
    {
        if (index == s.size())
        {
            ans.push_back(path);
            return;
        }

        for (int j = index; j < s.size(); j++)
        {
            if (isPalindrome(index, j, s))
            {
                path.push_back(s.substr(index, j - index + 1));
                solve(j + 1, s);
                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s)
    {
        solve(0, s);
        return ans;
    }
};

int main()
{
    Solution obj;

    string s = "aab";

    vector<vector<string>> ans = obj.partition(s);

    for (auto &vec : ans)
    {
        for (auto &str : vec)
            cout << str << " ";
        cout << endl;
    }

    return 0;
}

/*

===========================
Problem Statement
===========================

Given a string s, partition s such that every substring of the partition
is a palindrome.

Return all possible palindrome partitionings.

LeetCode 131 - Palindrome Partitioning


===========================
Example
===========================

Input:
s = "aab"

Output:
[
 ["a","a","b"],
 ["aa","b"]
]


====================================================
Brute Force Approach
====================================================

Idea
----
Try every possible substring starting from the current index.
If it is a palindrome, include it in the current partition and
recursively partition the remaining string.
Backtrack after every recursive call.

Pseudo Code
-----------

solve(index)

    if index==n
        store current partition
        return

    for j=index to n-1

        if substring(index,j) is palindrome

            take substring

            solve(j+1)

            remove substring

Complete Brute Force Code
-------------------------

class Solution {
public:

    vector<vector<string>> ans;
    vector<string> path;

    bool isPalindrome(int i,int j,string &s){

        while(i<j){

            if(s[i]!=s[j]) return false;

            i++;
            j--;
        }

        return true;
    }

    void solve(int index,string &s){

        if(index==s.size()){

            ans.push_back(path);
            return;
        }

        for(int j=index;j<s.size();j++){

            if(isPalindrome(index,j,s)){

                path.push_back(s.substr(index,j-index+1));

                solve(j+1,s);

                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s){

        solve(0,s);

        return ans;
    }
};

Time Complexity
---------------
O(N * 2^N)

Space Complexity
----------------
O(N) recursion stack
(Excluding output)


====================================================
Optimal Approach
====================================================

Observation
-----------
Every valid partition must be explored.

The only optimization possible is palindrome checking.

Instead of checking palindrome in O(N) every time,
precompute all palindromic substrings.

Then DFS simply checks pal[i][j] in O(1).

Intuition
---------
Step 1:
Build palindrome DP table.

pal[i][j] = true
if
s[i]==s[j]
and
(j-i<=2 || pal[i+1][j-1])

Step 2:
Backtracking.

From every index,
try every ending position.

If pal[index][j] is true,
take substring and continue.

Pseudo Code
-----------

Build palindrome table

DFS(index)

    if index==n
        store answer

    for j=index to n-1

        if pal[index][j]

            push substring

            DFS(j+1)

            pop substring

Complete Optimal Code
---------------------

class Solution {
public:

    vector<vector<string>> ans;
    vector<string> path;
    vector<vector<bool>> pal;

    void dfs(int index,string &s){

        if(index==s.size()){

            ans.push_back(path);
            return;
        }

        for(int j=index;j<s.size();j++){

            if(pal[index][j]){

                path.push_back(s.substr(index,j-index+1));

                dfs(j+1,s);

                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s){

        int n=s.size();

        pal.assign(n,vector<bool>(n,false));

        for(int i=n-1;i>=0;i--){

            for(int j=i;j<n;j++){

                if(s[i]==s[j] && (j-i<=2 || pal[i+1][j-1])){

                    pal[i][j]=true;
                }
            }
        }

        dfs(0,s);

        return ans;
    }
};

Time Complexity
---------------
Palindrome Table : O(N²)

DFS : O(N × 2^N)

Overall : O(N² + N × 2^N)

Space Complexity
----------------
Palindrome Table : O(N²)

Recursion Stack : O(N)

Overall : O(N²)
(Excluding output)


====================================================
Dry Run
====================================================

Input:

"aab"

DFS(0)

Choose "a"

Path = [a]

DFS(1)

Choose "a"

Path = [a,a]

DFS(2)

Choose "b"

Path = [a,a,b]

Store

Backtrack

Choose "aa"

Path = [aa]

DFS(2)

Choose "b"

Path = [aa,b]

Store

Answer

[a,a,b]

[aa,b]


====================================================
Interview Notes
====================================================

Pattern
-------
Backtracking + Palindrome Checking

Key Observation
---------------
Generate all partitions recursively.

Only continue recursion if the current substring is a palindrome.

Precomputing palindrome table reduces repeated palindrome checks.

Common Mistakes
---------------
1. Forgetting to backtrack (pop_back()).

2. Wrong substring length:
   substr(start, end-start+1)

3. Incorrect palindrome base condition.

4. Storing path before reaching the end.

5. Checking palindrome repeatedly leading to extra O(N) factor.

When to use this approach
-------------------------
Whenever asked to:
- Generate all valid partitions.
- Generate all palindrome decompositions.
- Backtracking on strings.
- Partition strings with constraints.
- Enumerate all possible valid solutions.

*/
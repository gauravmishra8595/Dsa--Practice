#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCut(string s)
    {
        int n = s.size();

        // pal[i][j] = true if s[i...j] is palindrome
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j] && (j - i <= 2 || pal[i + 1][j - 1]))
                {
                    pal[i][j] = true;
                }
            }
        }

        vector<int> dp(n + 1, 0);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--)
        {
            int ans = INT_MAX;
            for (int j = i; j < n; j++)
            {
                if (pal[i][j])
                {
                    ans = min(ans, 1 + dp[j + 1]);
                }
            }
            dp[i] = ans;
        }

        return dp[0] - 1;
    }
};

int main()
{
    Solution obj;

    string s = "aab";
    cout << obj.minCut(s) << endl;

    return 0;
}

/*

===========================
Problem Statement
===========================

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

LeetCode 132 - Palindrome Partitioning II


===========================
Example
===========================

Input:
s = "aab"

Output:
1

Explanation:
["aa","b"]
Only one cut is required.


====================================================
Brute Force Approach
====================================================

Idea
----
Try every possible partition recursively.
Whenever the current substring is a palindrome,
recursively solve for the remaining string.
Return the minimum number of partitions and finally subtract 1.

Pseudo Code
-----------

helper(index):
    if index == n
        return 0

    ans = INF

    for j=index to n-1
        if substring(index,j) is palindrome
            ans = min(ans,1+helper(j+1))

    return ans

return helper(0)-1

Complete Brute Force Code
-------------------------

class Solution {
public:

    bool isPalindrome(int i,int j,string &s){
        while(i<j){
            if(s[i]!=s[j]) return false;
            i++;
            j--;
        }
        return true;
    }

    int helper(int index,string &s){

        if(index==s.size())
            return 0;

        int ans=INT_MAX;

        for(int j=index;j<s.size();j++){

            if(isPalindrome(index,j,s)){
                ans=min(ans,1+helper(j+1,s));
            }

        }

        return ans;
    }

    int minCut(string s) {
        return helper(0,s)-1;
    }
};

Time Complexity
---------------
O(N * 2^N)

Space Complexity
----------------
O(N)


====================================================
Optimal Approach
====================================================

Observation
-----------
Repeated recursive calls occur for the same starting index.

Checking palindrome every time also costs O(N).

Precompute all palindromic substrings first, then perform DP.

Intuition
---------
Step 1:
Build palindrome table.

pal[i][j] = true
if
s[i]==s[j]
and
(j-i<=2 || pal[i+1][j-1])

Step 2:
DP from back.

dp[i] = minimum partitions starting from i.

Transition:

dp[i]=min(1+dp[j+1])
for every palindrome s[i...j]

Answer = dp[0]-1.

Pseudo Code
-----------

Build palindrome table

dp[n]=0

for i=n-1 to 0

    ans=INF

    for j=i to n-1

        if palindrome(i,j)

            ans=min(ans,1+dp[j+1])

    dp[i]=ans

return dp[0]-1

Complete Optimal Code
---------------------

class Solution {
public:

    int minCut(string s) {

        int n=s.size();

        vector<vector<bool>> pal(n,vector<bool>(n,false));

        for(int i=n-1;i>=0;i--){

            for(int j=i;j<n;j++){

                if(s[i]==s[j] && (j-i<=2 || pal[i+1][j-1])){

                    pal[i][j]=true;

                }

            }

        }

        vector<int> dp(n+1,0);

        dp[n]=0;

        for(int i=n-1;i>=0;i--){

            int ans=INT_MAX;

            for(int j=i;j<n;j++){

                if(pal[i][j]){

                    ans=min(ans,1+dp[j+1]);

                }

            }

            dp[i]=ans;

        }

        return dp[0]-1;
    }
};

Time Complexity
---------------
Palindrome Table : O(N^2)

DP : O(N^2)

Overall : O(N^2)

Space Complexity
----------------
Palindrome Table : O(N^2)

DP Array : O(N)

Overall : O(N^2)


====================================================
Dry Run
====================================================

Input:

"aab"

Palindrome Table:

a      -> T
a      -> T
b      -> T
aa     -> T
ab     -> F
aab    -> F

DP:

dp[3]=0

i=2

"b"

dp[2]=1

i=1

"a"

1+dp[2]=2

dp[1]=2

i=0

"a"

1+dp[1]=3

"aa"

1+dp[2]=2

minimum=2

dp[0]=2

Answer

dp[0]-1

2-1

=1


====================================================
Interview Notes
====================================================

Pattern
-------
DP on Strings + Palindrome Preprocessing

Key Observation
---------------
Minimum cuts become minimum partitions.

Minimum Cuts = Minimum Partitions - 1

Precomputing palindrome information reduces repeated work.

Common Mistakes
---------------
1. Forgetting to subtract 1 at the end.

2. Checking palindrome inside DP resulting in O(N^3).

3. Incorrect palindrome recurrence.

4. Wrong DP base case.

5. Building palindrome table from left to right.

When to use this approach
-------------------------
Whenever:
- String partition problems.
- Minimum partition/cut problems.
- Palindrome substring queries.
- DP on substrings.
- Need O(N^2) optimisation over recursive solutions.

*/
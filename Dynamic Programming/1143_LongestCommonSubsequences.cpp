#include <bits/stdc++.h>
using namespace std;

// ===================== Optimal Solution (Bottom-Up DP) =====================

class Solution
{
public:
    int longestCommonSubsequence(string a, string b)
    {
        int m = a.size();
        int n = b.size();

        vector<vector<int>> t(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {

                if (a[i - 1] == b[j - 1])
                {
                    t[i][j] = 1 + t[i - 1][j - 1];
                }
                else
                {
                    t[i][j] = max(t[i - 1][j], t[i][j - 1]);
                }
            }
        }

        return t[m][n];
    }
};

int main()
{

    Solution obj;

    string a = "abcde";
    string b = "ace";

    cout << "Length of LCS = " << obj.longestCommonSubsequence(a, b);

    return 0;
}

/*

===============================================================================
              LEETCODE 1143 - Longest Common Subsequence
===============================================================================


Problem Statement
-----------------
Given two strings text1 and text2, return the length of their longest common
subsequence.

A subsequence is a sequence that can be derived from another sequence by
deleting some or no elements without changing the order of the remaining
elements.

Example
-------
Input:
text1 = "abcde"
text2 = "ace"

Output:
3

Explanation:
The longest common subsequence is "ace".


===============================================================================
AVAILABLE APPROACHES
===============================================================================

1. Brute Force (Generate all subsequences)

Time Complexity:
O(2^(m+n))

Space Complexity:
O(m+n)


2. Recursion

Time Complexity:
O(2^(m+n))

Space Complexity:
O(m+n)


3. Recursion + Memoization (Top Down DP)

Time Complexity:
O(m*n)

Space Complexity:
O(m*n)


4. Bottom-Up Dynamic Programming  <-- BEST CLASSIC APPROACH

Time Complexity:
O(m*n)

Space Complexity:
O(m*n)


5. Space Optimized DP

Time Complexity:
O(m*n)

Space Complexity:
O(n)


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea
----
Generate all subsequences of both strings and compare them.

The longest matching subsequence is the answer.


Pseudo Code
-----------

function solve(i,j)

if i==m or j==n
    return 0

if a[i]==b[j]
    return 1 + solve(i+1,j+1)

else
    return max(
        solve(i+1,j),
        solve(i,j+1)
    )


Complete Brute Force Code (Revision Only)
------------------------------------------


class Solution {

public:

    int solve(int i, int j, string &a, string &b){

        if(i==a.size() || j==b.size())
            return 0;


        if(a[i]==b[j])
            return 1 + solve(i+1,j+1,a,b);


        return max(
            solve(i+1,j,a,b),
            solve(i,j+1,a,b)
        );
    }


    int longestCommonSubsequence(string a,string b){

        return solve(0,0,a,b);
    }
};


Time Complexity
---------------
O(2^(m+n))


Space Complexity
----------------
O(m+n)


===============================================================================
TOP DOWN DP (MEMOIZATION)
===============================================================================

Idea
----
Store already calculated states.

dp[i][j] represents LCS length between:

a[i...m-1] and b[j...n-1]


Pseudo Code
-----------

if already calculated
    return dp[i][j]

if characters match
    dp[i][j]=1+solve(i+1,j+1)

else
    dp[i][j]=max(
        solve(i+1,j),
        solve(i,j+1)
    )


Time Complexity
---------------
O(m*n)


Space Complexity
----------------
O(m*n)


===============================================================================
OPTIMAL APPROACH (BOTTOM-UP DP)
===============================================================================

Observation
-----------
For every pair of characters:

1. If characters are equal:
   They contribute one character to LCS.

   t[i][j] = 1 + t[i-1][j-1]


2. If characters are different:
   We skip one character from either string.

   t[i][j] = max(
       t[i-1][j],
       t[i][j-1]
   )


Intuition
---------
Create a DP table.

Rows represent characters of first string.

Columns represent characters of second string.


t[i][j] stores the answer for:

first i characters of string a

and

first j characters of string b


Pseudo Code
-----------

Create dp table (m+1)*(n+1)

Initialize first row and first column with 0


for i = 1 to m

    for j = 1 to n

        if a[i-1]==b[j-1]

            dp[i][j]=1+dp[i-1][j-1]

        else

            dp[i][j]=max(
                dp[i-1][j],
                dp[i][j-1]
            )


return dp[m][n]


Complete Optimal Code (Revision Only)
--------------------------------------


class Solution {

public:

    int longestCommonSubsequence(string a,string b){

        int m=a.size();
        int n=b.size();


        vector<vector<int>> t(
            m+1,
            vector<int>(n+1,0)
        );


        for(int i=1;i<=m;i++){

            for(int j=1;j<=n;j++){

                if(a[i-1]==b[j-1]){

                    t[i][j]=1+t[i-1][j-1];

                }

                else{

                    t[i][j]=max(
                        t[i-1][j],
                        t[i][j-1]
                    );

                }
            }
        }


        return t[m][n];
    }
};


Time Complexity
---------------
O(m*n)


Space Complexity
----------------
O(m*n)


===============================================================================
SPACE OPTIMIZED DP
===============================================================================

Observation
-----------
Current row only depends on previous row.

So we only store two rows.

Time Complexity:
O(m*n)

Space Complexity:
O(n)


===============================================================================
DRY RUN
===============================================================================

a = "abcde"

b = "ace"


DP Table:

        "" a c e
""      0 0 0 0
a       0 1 1 1
b       0 1 1 1
c       0 1 2 2
d       0 1 2 2
e       0 1 2 3


Answer = dp[5][3]

= 3


LCS = "ace"


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern
-------
Dynamic Programming on Strings


Key Observation
---------------
When two characters match:

    Take both characters.

When characters don't match:

    Ignore one character and take the best answer.


Common Mistakes
---------------
1. Confusing LCS with substring.

2. Forgetting order should remain same.

3. Using substring logic instead of subsequence logic.

4. Wrong DP dimensions.

5. Not initializing first row and column.


When to use this approach
-------------------------
Use LCS DP when questions involve:

✔ Longest Common Subsequence

✔ Comparing two strings

✔ Minimum deletions/insertions

✔ Longest Palindromic Subsequence

✔ String similarity problems


===============================================================================

*/

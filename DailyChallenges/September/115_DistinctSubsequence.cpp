#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();

        vector<unsigned long long> dp(m + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return (int)dp[m];
    }
};

int main() {
    Solution sol;

    string s = "rabbbit";
    string t = "rabbit";

    cout << sol.numDistinct(s, t) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 115 - DISTINCT SUBSEQUENCES
================================================================================

Problem Statement:
------------------
Given two strings s and t, return the number of distinct subsequences of s
which equals t.

A subsequence is formed by deleting some (possibly zero) characters from s
without changing the relative order of the remaining characters.

Example:
--------
Input:
    s = "rabbbit"
    t = "rabbit"

Output:
    3

Explanation:
    The three distinct ways are obtained by choosing different 'b' characters
    from "rabbbit" while preserving the order.

================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
At every character of s, we have two choices:

1. If s[i] == t[j]:
   - Take s[i] as part of the subsequence.
   - Skip s[i].

2. We can always skip s[i].

This creates a recursion tree.

When all characters of t are matched:
    return 1

When s is exhausted before t:
    return 0

Pseudo Code:
-----------
function solve(i, j):
    if j == length(t):
        return 1

    if i == length(s):
        return 0

    answer = solve(i + 1, j)       // Skip s[i]

    if s[i] == t[j]:
        answer += solve(i + 1, j + 1)  // Take s[i]

    return answer


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int solve(int i, int j, string &s, string &t) {
        if (j == t.size())
            return 1;

        if (i == s.size())
            return 0;

        int ans = solve(i + 1, j);

        if (s[i] == t[j]) {
            ans += solve(i + 1, j + 1);
        }

        return ans;
    }

    int numDistinct(string s, string t) {
        return solve(0, 0, s, t);
    }
};


Time Complexity:
----------------
O(2^n)

where n = length of s.

Space Complexity:
-----------------
O(n)

Recursion stack depth can be at most n.


================================================================================
OPTIMAL APPROACH - 1D DYNAMIC PROGRAMMING
================================================================================

Observation:
------------
The brute force recursion repeatedly solves the same states (i, j).

State:
    dp[i][j] = number of ways to form t[0...j-1]
               using s[0...i-1]

Transition:

If s[i-1] != t[j-1]:
    We cannot use s[i-1].

    dp[i][j] = dp[i-1][j]

If s[i-1] == t[j-1]:
    We have two choices:

    1. Skip s[i-1]
       dp[i-1][j]

    2. Use s[i-1]
       dp[i-1][j-1]

    Therefore:

    dp[i][j] = dp[i-1][j] + dp[i-1][j-1]


Base Cases:
-----------
dp[i][0] = 1

An empty string t can always be formed by deleting all characters from s.

dp[0][j] = 0 for j > 0

A non-empty t cannot be formed from an empty s.


Intuition:
----------
We process s from left to right.

For every character of s, if it matches the current character of t,
we can either:

    - Ignore it.
    - Use it to match t.

The important part is that the relative order is automatically preserved
because we process characters from left to right.

We can optimize the 2D DP to 1D because the current row only needs values
from the previous row.

For 1D dp:

    dp[j] = number of ways to form t[0...j-1]

When s[i-1] == t[j-1]:

    dp[j] += dp[j-1]

But j MUST be processed from right to left.

Why?
----
dp[j-1] must belong to the previous row.

If we processed left to right, dp[j-1] would already have been updated
using the current character of s, causing the same character to be used
multiple times.


Pseudo Code:
-----------
dp[0] = 1

for each character s[i]:
    for j from m down to 1:
        if s[i] == t[j-1]:
            dp[j] += dp[j-1]

return dp[m]


Complete Optimal Code:
----------------------

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        vector<unsigned long long> dp(m + 1, 0);

        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return (int)dp[m];
    }
};


Time Complexity:
----------------
O(n * m)

where:
    n = length of s
    m = length of t


Space Complexity:
-----------------
O(m)

because we use a 1D DP array of size m + 1.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

s = "rabbbit"
t = "rabbit"

Initially:

dp = [1, 0, 0, 0, 0, 0, 0]

Process 'r':
    Matches t[0] = 'r'

    dp[1] += dp[0]

    dp = [1, 1, 0, 0, 0, 0, 0]


Process first 'a':
    Matches t[1] = 'a'

    dp = [1, 1, 1, 0, 0, 0, 0]


Process first 'b':
    Matches t[2] = 'b'

    dp = [1, 1, 1, 1, 0, 0, 0]


Process second 'b':
    Can create additional ways to form "rab"

    dp = [1, 1, 1, 2, 0, 0, 0]


Process third 'b':
    More choices for matching the b's

    dp = [1, 1, 1, 3, 0, 0, 0]


Process 'i':
    Matches t[4] = 'i'

    dp = [1, 1, 1, 3, 3, 0, 0]


Process 't':
    Matches t[5] = 't'

    dp = [1, 1, 1, 3, 3, 3, 0]

Note:
The exact intermediate indexing depends on the target positions;
the final DP value is:

    dp[m] = 3

Therefore:

    Answer = 3


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Dynamic Programming + Subsequences + Counting Ways

This is a classic "count the number of ways" DP problem.


Key Observation:
----------------
If s[i-1] == t[j-1], we have two possibilities:

    1. Use s[i-1] to match t[j-1].
    2. Skip s[i-1].

Therefore:

    dp[i][j] = dp[i-1][j] + dp[i-1][j-1]


Most important implementation detail:

    Iterate j from RIGHT TO LEFT in the 1D DP.

This prevents the current character of s from being used more than once.


Common Mistakes:
----------------
1. Using 1D DP but iterating j from left to right.

2. Forgetting:
       dp[0] = 1

3. Confusing subsequence with substring.
   Characters do NOT need to be contiguous.

4. Returning 0 when t becomes empty.
   Actually, there is exactly one way to form an empty string:
   choose nothing.

5. Using the wrong transition.

   If characters match:
       dp[j] += dp[j-1]

   If they don't match:
       do nothing.


When to use this approach:
--------------------------
Use this pattern when:

- You need to count subsequences.
- Relative order must be preserved.
- You are selecting or skipping characters.
- The problem asks for the number of ways.
- The same (index in s, index in t) states repeat.

Typical state:

    dp[i][j] = answer using first i characters of s
               to construct first j characters of t


Final Pattern to Remember:
--------------------------
For counting subsequences:

    dp[0] = 1

    for every character in s:
        for j = m down to 1:
            if s[i] == t[j-1]:
                dp[j] += dp[j-1]

    answer = dp[m]

================================================================================
*/

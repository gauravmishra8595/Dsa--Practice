#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size();
        int m = s2.size();

        if (n + m != (int)s3.size())
            return false;

        // dp[j] = whether s3[0 ... i+j-1] can be formed
        // using s1[0 ... i-1] and s2[0 ... j-1].
        vector<bool> dp(m + 1, false);

        dp[0] = true;

        for (int j = 1; j <= m; j++)
        {
            dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
        }

        for (int i = 1; i <= n; i++)
        {
            dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);

            for (int j = 1; j <= m; j++)
            {
                dp[j] =
                    (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
                    (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }

        return dp[m];
    }
};

int main()
{
    Solution sol;

    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";

    cout << boolalpha << sol.isInterleave(s1, s2, s3) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 97 - INTERLEAVING STRING
================================================================================

Problem Statement:
------------------
Given strings s1, s2, and s3, determine whether s3 is formed by an
interleaving of s1 and s2.

An interleaving means:
- The characters of s1 must appear in the same relative order.
- The characters of s2 must appear in the same relative order.
- At every position in s3, we choose the next character from either s1
  or s2.

Example:
--------
Input:
    s1 = "aabcc"
    s2 = "dbbca"
    s3 = "aadbbcbcac"

Output:
    true

Explanation:
    s3 can be formed by taking characters from s1 and s2 while preserving
    the relative order of characters in both strings.

================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
At every position in s3, we have two possible choices:

1. Take the next character from s1.
2. Take the next character from s2.

If the selected character matches s3 at the current position, recursively
continue.

This creates an exponential recursion tree.

Pseudo Code:
-----------
function solve(i, j):
    k = i + j

    if k == length(s3):
        return true

    if i < length(s1) and s1[i] == s3[k]:
        if solve(i + 1, j):
            return true

    if j < length(s2) and s2[j] == s3[k]:
        if solve(i, j + 1):
            return true

    return false


Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool solve(int i, int j, string &s1, string &s2, string &s3) {
        int k = i + j;

        if (k == s3.size())
            return true;

        if (i < s1.size() && s1[i] == s3[k]) {
            if (solve(i + 1, j, s1, s2, s3))
                return true;
        }

        if (j < s2.size() && s2[j] == s3[k]) {
            if (solve(i, j + 1, s1, s2, s3))
                return true;
        }

        return false;
    }

    bool isInterleave(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size())
            return false;

        return solve(0, 0, s1, s2, s3);
    }
};


Time Complexity:
----------------
O(2^(n + m))

At each character of s3, we may have two choices.


Space Complexity:
-----------------
O(n + m)

Recursion depth can reach n + m.


================================================================================
OPTIMAL APPROACH - 2D DP -> 1D DP
================================================================================

Observation:
------------
At any point, we only need to know:

    i = how many characters have been taken from s1
    j = how many characters have been taken from s2

The number of characters already used in s3 is:

    k = i + j

Therefore, we don't need a third index.


2D DP State:
------------
dp[i][j] = true if s3[0 ... i+j-1] can be formed by interleaving
           s1[0 ... i-1] and s2[0 ... j-1].


Transition:
-----------
The current character of s3 is:

    s3[i + j - 1]


We can take it from s1:

    dp[i-1][j] && s1[i-1] == s3[i+j-1]


OR take it from s2:

    dp[i][j-1] && s2[j-1] == s3[i+j-1]


Therefore:

    dp[i][j] =
        (dp[i-1][j] && s1[i-1] == s3[i+j-1])
        ||
        (dp[i][j-1] && s2[j-1] == s3[i+j-1])


Intuition:
----------
Think of s3 as a sequence that we need to construct.

At each position:
- We can pick the next character from s1.
- Or we can pick the next character from s2.

We only care whether at least one valid way exists.

The DP remembers which combinations of characters from s1 and s2 have
already produced a valid prefix of s3.


Base Case:
----------
dp[0][0] = true

No characters from either string can form an empty prefix of s3.


Important Length Check:
-----------------------
If:

    s1.size() + s2.size() != s3.size()

then s3 cannot possibly be an interleaving.

Return false immediately.


1D Space Optimization:
----------------------
The 2D DP uses O(n * m) space.

But each state only needs:
- The value from the previous row.
- The current row's previous column.

So we can reduce it to:

    dp[j]

where j represents how many characters are taken from s2.

We process j from left to right because dp[j-1] represents the current row,
while dp[j] represents the previous row.


Pseudo Code:
-----------
if length(s1) + length(s2) != length(s3):
    return false

dp[0] = true

initialize first row using s2

for i from 1 to n:
    update dp[0] using s1

    for j from 1 to m:
        takeFromS1 =
            dp[j] && s1[i-1] == s3[i+j-1]

        takeFromS2 =
            dp[j-1] && s2[j-1] == s3[i+j-1]

        dp[j] = takeFromS1 OR takeFromS2

return dp[m]


Complete Optimal Code:
----------------------

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size();
        int m = s2.size();

        if (n + m != (int)s3.size())
            return false;

        vector<bool> dp(m + 1, false);

        dp[0] = true;

        for (int j = 1; j <= m; j++) {
            dp[j] = dp[j - 1] &&
                    (s2[j - 1] == s3[j - 1]);
        }

        for (int i = 1; i <= n; i++) {
            dp[0] = dp[0] &&
                    (s1[i - 1] == s3[i - 1]);

            for (int j = 1; j <= m; j++) {
                dp[j] =
                    (dp[j] &&
                     s1[i - 1] == s3[i + j - 1])
                    ||
                    (dp[j - 1] &&
                     s2[j - 1] == s3[i + j - 1]);
            }
        }

        return dp[m];
    }
};


Time Complexity:
----------------
O(n * m)

where:
    n = length(s1)
    m = length(s2)


Space Complexity:
-----------------
O(m)

We use a 1D DP array.

If desired, the shorter string can be used for the DP dimension to make
space O(min(n, m)).


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

s1 = "aab"
s2 = "axy"
s3 = "aaabxy"


Initial:

    dp = [true, false, false, false]

Process s2 for i = 0:

    j = 1:
    s2[0] = 'a'
    s3[0] = 'a'

    dp = [true, true, false, false]

    j = 2:
    s2[1] = 'x'
    s3[1] = 'a'

    dp = [true, true, false, false]

    j = 3:
    s2[2] = 'y'
    s3[2] = 'a'

    dp = [true, true, false, false]


Now process s1.

i = 1:
    s1[0] = 'a'

    For j = 1:
        Current s3 character = s3[1] = 'a'

        We can take 'a' from s1.

        dp[1] = true

    The valid state continues.


The DP keeps checking whether the next character of s3 can come from
either s1 or s2.

Eventually:

    dp[m] = true

Therefore:

    s3 is a valid interleaving.


Another quick example:
----------------------

s1 = "aabcc"
s2 = "dbbca"
s3 = "aadbbcbcac"

Length check:

    5 + 5 = 10
    length(s3) = 10

So it is possible.

The DP finds at least one valid path through the states.

Answer:

    true


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Dynamic Programming on two strings.

This is a classic:

    "Take from String 1 OR Take from String 2"

DP pattern.


Key Observation:
----------------
The position in s3 is completely determined by:

    k = i + j

So we only need two indices:

    i -> position in s1
    j -> position in s2


Core Transition:
----------------

    dp[i][j] =
        take from s1
        OR
        take from s2


More explicitly:

    dp[i][j] =
        (dp[i-1][j] && s1[i-1] == s3[i+j-1])
        ||
        (dp[i][j-1] && s2[j-1] == s3[i+j-1])


Common Mistakes:
----------------
1. Forgetting the length check:

       s1.length() + s2.length() == s3.length()

2. Using:

       s3[i + j]

   instead of:

       s3[i + j - 1]

   when using 1-based DP indices.

3. Updating the 1D DP incorrectly.

   Here j should move from LEFT to RIGHT because:

       dp[j]     -> previous row
       dp[j - 1] -> current row


4. Thinking characters can be rearranged.

   They cannot.

   The relative order of characters from both s1 and s2 must remain unchanged.


5. Using greedy.

   Choosing from s1 whenever possible does not always work.

   Sometimes we must choose from s2 even when both choices are available.


6. Forgetting that multiple valid paths can exist.

   We only need one valid interleaving, so DP stores a boolean.


When to use this approach:
--------------------------
Use this DP pattern when:

- Two strings are being merged/interleaved.
- Relative order inside each original string must remain unchanged.
- You need to determine whether a target string can be formed.
- At each step, you choose the next element from one of two sequences.
- Greedy choices can lead to dead ends.


Mental Model:
-------------
Imagine a grid.

    i = characters consumed from s1
    j = characters consumed from s2

From every cell:

        (i, j)

you can move:

        DOWN  -> take character from s1
        RIGHT -> take character from s2

A path from:

        (0, 0)

to:

        (n, m)

means s3 can be formed.

The DP checks whether such a path exists.


Final Complexity:
-----------------
Time:

    O(n * m)

Space:

    O(m)

where:

    n = s1.length()
    m = s2.length()


================================================================================
*/

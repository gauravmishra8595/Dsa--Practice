#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] &&
                    (j - i <= 2 || pal[i + 1][j - 1])) {
                    pal[i][j] = true;
                }
            }
        }
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = dp[i + 1];
            for (int j = i + k - 1; j < n; j++) {
                if (pal[i][j]) {
                    dp[i] = max(dp[i], 1 + dp[j + 1]);
                }
            }
        }

        return dp[0];
    }
};

int main() {
    Solution sol;

    string s = "abaccdbbd";
    int k = 3;

    cout << sol.maxPalindromes(s, k) << '\n';

    return 0;
}

/*
================================================================================
                         MAXIMUM NUMBER OF PALINDROMES
================================================================================

Problem Statement:
------------------
Given a string s and an integer k, find the maximum number of non-overlapping
palindromic substrings of s such that every selected palindrome has length
at least k.

A substring cannot overlap with another selected substring.

Example:
--------
Input:
    s = "abaccdbbd"
    k = 3

Output:
    2

Explanation:
    We can select:
        "aba"  -> palindrome, length 3
        "dbbd" -> palindrome, length 4

    They are non-overlapping, so the answer is 2.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Try every possible substring.

For every substring s[i...j]:
    1. Check whether it is a palindrome.
    2. If its length >= k, we have two choices:
         - Take it and continue from j + 1.
         - Skip it and continue searching.
    3. Take the maximum answer.

This recursively explores all possible choices of substrings.

Pseudo Code:
------------
solve(i):
    if i >= n:
        return 0

    ans = solve(i + 1)       // Skip current index

    for j from i + k - 1 to n - 1:
        if s[i...j] is palindrome:
            ans = max(ans, 1 + solve(j + 1))

    return ans

Complete Brute Force Code:
---------------------------

class Solution {
public:
    int n;

    bool isPalindrome(string &s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j])
                return false;

            i++;
            j--;
        }

        return true;
    }

    int solve(string &s, int k, int i) {
        if (i >= n)
            return 0;

        // Skip current index
        int ans = solve(s, k, i + 1);

        // Try all substrings starting at i
        for (int j = i + k - 1; j < n; j++) {
            if (isPalindrome(s, i, j)) {
                ans = max(ans, 1 + solve(s, k, j + 1));
            }
        }

        return ans;
    }

    int maxPalindromes(string s, int k) {
        n = s.size();
        return solve(s, k, 0);
    }
};

Time Complexity:
----------------
There are exponentially many possible choices.

Palindrome checking can take O(N).

Overall worst-case complexity:
    O(2^N * N)

Space Complexity:
-----------------
Recursive stack:
    O(N)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
There are two independent parts:

1. We need to quickly check whether s[i...j] is a palindrome.
2. We need to find the maximum number of non-overlapping palindromes.

For palindrome checking, use DP:

    pal[i][j] = true if s[i...j] is a palindrome.

The recurrence is:

    pal[i][j] = true
    if:
        s[i] == s[j]
        AND
        substring inside is a palindrome.

That is:

    pal[i][j] = s[i] == s[j] &&
                (j - i <= 2 || pal[i + 1][j - 1])


Intuition:
----------
Define:

    dp[i] = maximum number of valid non-overlapping palindromes
            that can be selected from s[i...n-1].

At every index i, we have two choices.

Choice 1: Skip s[i]

    dp[i] = dp[i + 1]

Choice 2: Start a palindrome at i.

Try every j such that:

    j >= i + k - 1

If s[i...j] is a palindrome:

    dp[i] = max(dp[i], 1 + dp[j + 1])

Why dp[j + 1]?

Because after selecting s[i...j], the next selected palindrome must start
at j + 1 or later. Therefore, the two palindromes are guaranteed to be
non-overlapping.

We calculate dp from right to left because dp[i] depends on dp[j + 1].


Pseudo Code:
------------
Build palindrome DP:

for i = n - 1 down to 0:
    for j = i to n - 1:
        if s[i] == s[j] AND
           (length <= 3 OR pal[i + 1][j - 1]):
            pal[i][j] = true


Build answer DP:

dp[n] = 0

for i = n - 1 down to 0:

    // Skip i
    dp[i] = dp[i + 1]

    // Try every palindrome starting at i
    for j = i + k - 1 to n - 1:

        if pal[i][j]:
            dp[i] = max(dp[i], 1 + dp[j + 1])

answer = dp[0]


Complete Optimal Code:
-----------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        vector<vector<bool>> pal(n, vector<bool>(n, false));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] &&
                    (j - i <= 2 || pal[i + 1][j - 1])) {
                    pal[i][j] = true;
                }
            }
        }

        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = dp[i + 1];

            for (int j = i + k - 1; j < n; j++) {
                if (pal[i][j]) {
                    dp[i] = max(dp[i], 1 + dp[j + 1]);
                }
            }
        }

        return dp[0];
    }
};

Time Complexity:
----------------
Palindrome DP:
    O(N^2)

Answer DP:
    O(N^2)

Total:
    O(N^2)

Space Complexity:
-----------------
Palindrome table:
    O(N^2)

DP array:
    O(N)

Total:
    O(N^2)


================================================================================
DRY RUN
================================================================================

Example:
    s = "abaccdbbd"
    k = 3

We need palindromes of length >= 3.

Some valid palindromes are:

    "aba"   -> indices [0...2]
    "acca"  -> indices [1...4]
    "dbbd"  -> indices [5...8]

Now consider dp.

At index 5:

    "dbbd" is a palindrome.

So:

    dp[5] = 1 + dp[9]
          = 1

At index 1:

    "acca" is a palindrome.

So:

    dp[1] = 1 + dp[5]
          = 2

Alternatively, we can skip index 1 and eventually choose:

    "aba" + "dbbd"

which also gives:

    2

Therefore:

    dp[0] = 2

Answer:
    2


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
1. Interval DP / Palindrome DP
2. 1D Dynamic Programming
3. Take-or-Skip pattern
4. Non-overlapping interval selection

Key Observation:
----------------
Precompute whether every substring is a palindrome.

Then convert the problem into:

    "Maximum number of non-overlapping valid intervals."

For every starting index i:

    Skip i
        OR
    Take a palindrome [i...j]

If we take [i...j], the next state is:

    dp[j + 1]

This automatically guarantees non-overlapping substrings.


Common Mistakes:
----------------
1. Checking palindrome every time using two pointers.

   This can make the solution O(N^3).

   Instead, precompute pal[i][j] in O(N^2).

2. Forgetting the minimum length k.

   Only consider:

       j >= i + k - 1

3. Using dp[j] instead of dp[j + 1].

   After taking [i...j], the next available position is j + 1.

4. Allowing overlapping substrings.

   Always transition to:

       dp[j + 1]

5. Incorrect palindrome recurrence.

   For length <= 3, the inside substring is either empty or one character,
   so:

       j - i <= 2

   is a useful base condition.


When to Use This Approach:
--------------------------
Use this approach when:

- You need to select maximum/minimum number of non-overlapping substrings.
- Each substring must satisfy some condition.
- The condition can be precomputed for every interval.
- The problem asks for maximum number of valid segments.

Typical pattern:

    Precompute interval property
                +
    1D DP over starting index
                +
    Take / Skip transition


Final Complexity:
-----------------
Time  : O(N^2)
Space : O(N^2)

================================================================================
*/

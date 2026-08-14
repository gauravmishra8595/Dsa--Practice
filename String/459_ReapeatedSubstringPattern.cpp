#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool repeatedSubstringPattern(string s)
    {
        int n = s.size();

        for (int len = 1; len <= n / 2; len++)
        {
            if (n % len != 0)
                continue;

            string pattern = s.substr(0, len);
            bool valid = true;

            for (int i = len; i < n; i++)
            {
                if (s[i] != pattern[i % len])
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
                return true;
        }

        return false;
    }
};

int main()
{
    Solution sol;

    string s;
    cin >> s;

    cout << boolalpha << sol.repeatedSubstringPattern(s) << endl;

    return 0;
}

/*
============================================================
                    LEETCODE 459
              Repeated Substring Pattern
============================================================

Problem Statement:
------------------
Given a string s, check if it can be constructed by taking
a substring of s and appending multiple copies of the substring
together.

Return true if such a pattern exists, otherwise return false.

Example:
--------
Input:
abab

Output:
true

Explanation:
"ab" + "ab" = "abab"

Another Example:
----------------
Input:
aba

Output:
false

------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Try every possible substring length from 1 to n/2.

If n is divisible by the chosen length, then that substring
can potentially repeat to form the complete string.

Construct the repeated string and compare it with s.

Pseudo Code:
------------
for len = 1 to n/2:
    if n % len != 0:
        continue

    pattern = first len characters

    repeat pattern n / len times

    if repeated string == s:
        return true

return false

Complete Brute Force Code:
---------------------------

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();

        for (int len = 1; len <= n / 2; len++) {
            if (n % len != 0)
                continue;

            string pattern = s.substr(0, len);
            string repeated = "";

            for (int i = 0; i < n / len; i++) {
                repeated += pattern;
            }

            if (repeated == s)
                return true;
        }

        return false;
    }
};

Time Complexity:
----------------
O(n^2) in the worst case.

Space Complexity:
-----------------
O(n)


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
The repeated substring must have a length that divides the
length of the original string.

For example:

"abcabcabc"

n = 9

Possible pattern lengths:
1, 3

Length 3 works:

"abc" + "abc" + "abc"

Intuition:
----------
Try every possible pattern length that divides n.

Instead of constructing the complete repeated string, compare
each character with:

pattern[i % len]

If every character matches, the pattern is valid.

Pseudo Code:
------------
n = s.size()

for len = 1 to n/2:
    if n % len != 0:
        continue

    pattern = first len characters
    valid = true

    for i = len to n-1:
        if s[i] != pattern[i % len]:
            valid = false
            break

    if valid:
        return true

return false

Complete Optimal Code:
----------------------

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();

        for (int len = 1; len <= n / 2; len++) {
            if (n % len != 0)
                continue;

            string pattern = s.substr(0, len);
            bool valid = true;

            for (int i = len; i < n; i++) {
                if (s[i] != pattern[i % len]) {
                    valid = false;
                    break;
                }
            }

            if (valid)
                return true;
        }

        return false;
    }
};

Time Complexity:
----------------
O(n^2) worst case.

Space Complexity:
-----------------
O(n) for the pattern string.

Note:
-----
The above solution is optimal enough for the constraints of
LeetCode 459, although a KMP-based O(n) solution also exists.


------------------------------------------------------------
Dry Run With Example
------------------------------------------------------------

Example:
s = "abab"

n = 4

Try len = 1:
----------------
n % 1 == 0

pattern = "a"

Compare:
s[1] = 'b'
pattern[1 % 1] = 'a'

Mismatch.

So len = 1 does not work.


Try len = 2:
----------------
n % 2 == 0

pattern = "ab"

Compare:

i = 2
s[2] = 'a'
pattern[2 % 2] = pattern[0] = 'a'

Match.

i = 3
s[3] = 'b'
pattern[3 % 2] = pattern[1] = 'b'

Match.

All characters match.

Therefore:
"ab" + "ab" = "abab"

Answer:
true


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
String / Pattern Matching

Key Observation:
----------------
If a string is made by repeating a substring, the length of
that substring must divide the total string length.

Also, we only need to check pattern lengths up to n/2 because
the repeated substring must occur at least twice.

Common Mistakes:
----------------
1. Checking pattern lengths greater than n/2.
2. Forgetting to check n % len == 0.
3. Returning true after finding only a partial match.
4. Assuming adjacent duplicate characters are enough.
5. Forgetting that the entire string must be formed by
   repeating the same substring.

When to Use This Approach:
--------------------------
Use this approach when:
- You need to detect repeated patterns in a string.
- The string is formed by multiple copies of a smaller pattern.
- The possible pattern lengths can be checked using divisibility.

Important Advanced Technique:
-----------------------------
For an O(n) solution, KMP can be used.

If:
    L = length of longest proper prefix which is also suffix

Then:
    repeatingLength = n - L

If:
    L > 0 && n % repeatingLength == 0

the string follows a repeated pattern.

============================================================
*/
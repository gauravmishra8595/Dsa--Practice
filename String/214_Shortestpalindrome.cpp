#include <bits/stdc++.h>
using namespace std;

// ==================== OPTIMAL SOLUTION ====================

class Solution
{
public:
    string shortestPalindrome(string s)
    {
        string rev = s;
        reverse(rev.begin(), rev.end());

        string temp = s + "#" + rev;

        // LPS array
        vector<int> lps(temp.size(), 0);

        for (int i = 1; i < (int)temp.size(); i++)
        {
            int j = lps[i - 1];

            while (j > 0 && temp[i] != temp[j])
            {
                j = lps[j - 1];
            }

            if (temp[i] == temp[j])
            {
                j++;
            }

            lps[i] = j;
        }

        // Longest palindromic prefix
        int len = lps.back();

        // Remaining suffix
        string add = s.substr(len);

        // Reverse it and add to front
        reverse(add.begin(), add.end());

        return add + s;
    }
};

int main()
{
    Solution sol;

    string s = "aacecaaa";

    cout << sol.shortestPalindrome(s) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 214
                      SHORTEST PALINDROME
================================================================================

PROBLEM STATEMENT
-----------------
Given a string s, add characters only in front of s to make it a palindrome.

Return the shortest possible palindrome.

Example:

    Input:
        s = "aacecaaa"

    Output:
        "aaacecaaa"


KEY IDEA:
---------
Find the LONGEST PALINDROMIC PREFIX.

If the longest palindromic prefix has length len, then the remaining
suffix must be reversed and added to the front.


================================================================================
EXAMPLE
================================================================================

Input:

    s = "aacecaaa"

Longest palindromic prefix:

    "aacecaa"

Remaining suffix:

    "a"

Reverse remaining suffix:

    "a"

Add to front:

    "a" + "aacecaaa"

    = "aaacecaaa"

Answer:

    "aaacecaaa"


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Check every prefix of s from longest to shortest.

The first prefix that is a palindrome is the longest palindromic
prefix.

Then:

    remaining = suffix after that prefix

    answer = reverse(remaining) + s


PSEUDO CODE
-----------
    n = s.length()

    for i = n-1 down to 0:

        if s[0...i] is palindrome:

            remaining = s[i+1...n-1]

            reverse(remaining)

            return remaining + s


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    bool isPalindrome(string& s, int left, int right) {

        while (left < right) {

            if (s[left] != s[right]) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    string shortestPalindrome(string s) {

        int n = s.size();

        for (int i = n - 1; i >= 0; i--) {

            if (isPalindrome(s, 0, i)) {

                string add = s.substr(i + 1);

                reverse(add.begin(), add.end());

                return add + s;
            }
        }

        return "";
    }
};


TIME COMPLEXITY
----------------
There can be O(n) prefixes.

Each palindrome check can take O(n).

Therefore:

    O(n²)


SPACE COMPLEXITY
----------------
O(n)

for the temporary suffix and answer.


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
We only need to find:

    LONGEST PALINDROMIC PREFIX


For example:

    s = "aacecaaa"

The longest palindromic prefix is:

    "aacecaa"


Instead of checking every prefix separately, we can use KMP/LPS.


INTUITION
---------
Reverse the string.

    s   = "aacecaaa"
    rev = "aaacecaa"

Now create:

    temp = s + "#" + rev

    temp = "aacecaaa#aaacecaa"


The LPS array tells us the longest prefix of temp that is also
a suffix of temp.

Because of the separator '#', this effectively finds the longest
prefix of s that matches a suffix of reverse(s).

That matching prefix is exactly the longest palindromic prefix of s.


WHY DOES IT WORK?
-----------------

Suppose:

    prefix = s[0 ... k]

If this prefix is a palindrome, then:

    prefix == reverse(prefix)

Since reverse(s) starts with reverse(s), this palindrome prefix
will also appear as a suffix of reverse(s).

Therefore:

    longest palindromic prefix
            =
    longest prefix of s matching suffix of reverse(s)


WHY "#"?
--------
The separator prevents the prefix matching from incorrectly
crossing the boundary between s and reverse(s).

Use a character that does not occur in s.


PSEUDO CODE
-----------
    rev = reverse(s)

    temp = s + "#" + rev

    Build LPS array for temp

    len = lps[last]

    add = s[len ... n-1]

    reverse(add)

    return add + s


COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:

    string shortestPalindrome(string s) {

        string rev = s;
        reverse(rev.begin(), rev.end());

        string temp = s + "#" + rev;

        vector<int> lps(temp.size(), 0);

        for (int i = 1; i < temp.size(); i++) {

            int j = lps[i - 1];

            while (j > 0 && temp[i] != temp[j]) {
                j = lps[j - 1];
            }

            if (temp[i] == temp[j]) {
                j++;
            }

            lps[i] = j;
        }

        int len = lps.back();

        string add = s.substr(len);

        reverse(add.begin(), add.end());

        return add + s;
    }
};


TIME COMPLEXITY
----------------
Reverse string:

    O(n)

Build temp:

    O(n)

Build LPS:

    O(n)

Create final answer:

    O(n)

Total:

    O(n)


SPACE COMPLEXITY
----------------
O(n)

For:

    rev
    temp
    lps
    add


================================================================================
DRY RUN
================================================================================

Input:

    s = "aacecaaa"


STEP 1: REVERSE
---------------
    s   = "aacecaaa"
    rev = "aaacecaa"


STEP 2: CREATE STRING
---------------------
    temp = s + "#" + rev

         = "aacecaaa#aaacecaa"


STEP 3: BUILD LPS
-----------------
The final LPS value is:

    lps.back() = 7


Therefore:

    longest palindromic prefix length = 7


STEP 4: FIND PREFIX
-------------------
First 7 characters:

    "aacecaa"

Check:

    a a c e c a a
    | | |   | | |
    a a c e c a a

It is a palindrome.


STEP 5: REMAINING SUFFIX
------------------------
Original:

    a a c e c a a a
    0 1 2 3 4 5 6 7

Longest prefix length = 7

Remaining:

    "a"


STEP 6: REVERSE REMAINING
-------------------------
    "a" -> "a"


STEP 7: ADD TO FRONT
--------------------
    "a" + "aacecaaa"

    = "aaacecaaa"


FINAL ANSWER
------------
    "aaacecaaa"


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
KMP / LPS / Prefix Function

This is a classic problem where KMP is used to find a
palindromic prefix.


KEY OBSERVATION
---------------
We do NOT need the longest palindromic substring.

We need:

    LONGEST PALINDROMIC PREFIX


The important transformation is:

    s + "#" + reverse(s)

Then:

    lps.back()

gives the length of the longest palindromic prefix.


COMMON MISTAKES
---------------

1. Finding the longest palindromic SUBSTRING instead of PREFIX.

2. Adding characters at the end.

   The problem allows adding characters only at the FRONT.

3. Forgetting to reverse the remaining suffix.

4. Not using a separator:

       s + reverse(s)

   can produce incorrect matches.

5. Incorrect KMP LPS implementation.

6. Using substrings inside a loop.

   This can lead to O(n²) time and unnecessary allocations.

7. Thinking this is a normal palindrome problem.

   The important trick is converting it into a prefix/suffix
   matching problem.


WHEN TO USE THIS APPROACH
-------------------------
Think about KMP/LPS when you see:

    - Prefix and suffix matching
    - Longest prefix
    - Longest border
    - Palindrome + prefix
    - Need O(n) string matching


KMP TEMPLATE
------------

    vector<int> lps(n, 0);

    for (int i = 1; i < n; i++) {

        int j = lps[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = lps[j - 1];
        }

        if (s[i] == s[j]) {
            j++;
        }

        lps[i] = j;
    }


REMEMBER THIS
-------------

    Shortest Palindrome
            |
            v
    Find longest palindromic PREFIX
            |
            v
    s + "#" + reverse(s)
            |
            v
       Build LPS
            |
            v
       lps.back()
            |
            v
    Length of palindromic prefix
            |
            v
    Reverse remaining suffix
            |
            v
       Add it to front


FINAL COMPLEXITY
----------------

    Time  : O(n)
    Space : O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ==================== OPTIMAL SOLUTION ====================

class Solution
{
public:
    string longestPrefix(string s)
    {
        int n = s.size();

        vector<int> lps(n, 0);

        for (int i = 1; i < n; i++)
        {
            int j = lps[i - 1];

            while (j > 0 && s[i] != s[j])
            {
                j = lps[j - 1];
            }

            if (s[i] == s[j])
            {
                j++;
            }

            lps[i] = j;
        }

        return s.substr(0, lps[n - 1]);
    }
};

int main()
{
    Solution sol;

    string s = "level";

    cout << sol.longestPrefix(s) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 1392
                  LONGEST HAPPY PREFIX
================================================================================

PROBLEM STATEMENT
-----------------
A happy prefix is a non-empty prefix of a string that is also a suffix
of the same string.

The prefix and suffix must NOT be the entire string.

Return the longest happy prefix.

Example:

    Input:
        s = "level"

    Prefixes:
        "l"
        "le"
        "lev"
        "leve"

    Suffixes:
        "l"
        "el"
        "vel"
        "evel"

    Common longest prefix/suffix:

        "l"

    Output:

        "l"


================================================================================
EXAMPLE
================================================================================

Input:

    s = "ababab"

Possible prefixes:

    "a"
    "ab"
    "aba"
    "abab"
    "ababa"

Possible suffixes:

    "b"
    "ab"
    "bab"
    "abab"
    "babab"

Longest common prefix and suffix:

    "abab"

Output:

    "abab"


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Try every possible prefix length.

For each prefix, check whether it is equal to the suffix of the
same length.

Start from the longest possible prefix.

The first match is the answer.


PSEUDO CODE
-----------
    n = s.length()

    for len from n-1 down to 1:

        prefix = first len characters
        suffix = last len characters

        if prefix == suffix:
            return prefix

    return ""


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    string longestPrefix(string s) {

        int n = s.size();

        for (int len = n - 1; len >= 1; len--) {

            bool same = true;

            for (int i = 0; i < len; i++) {

                if (s[i] != s[n - len + i]) {
                    same = false;
                    break;
                }
            }

            if (same) {
                return s.substr(0, len);
            }
        }

        return "";
    }
};


TIME COMPLEXITY
----------------
There can be O(n) possible lengths.

For every length, we may compare O(n) characters.

Therefore:

    O(n²)


SPACE COMPLEXITY
----------------
O(1)

Ignoring the returned substring.


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
This problem is directly related to the KMP algorithm.

The KMP LPS array means:

    lps[i] = length of the longest proper prefix of s[0...i]
             which is also a suffix of s[0...i]


For the COMPLETE string:

    lps[n - 1]

directly gives the length of the longest prefix that is also a suffix.

That is exactly what the problem asks.


INTUITION
---------
Example:

    s = "ababab"

Build the LPS array:

    index:  0 1 2 3 4 5
    char:   a b a b a b
    lps:    0 0 1 2 3 4

At the final position:

    lps[5] = 4

Therefore the longest happy prefix has length 4.

So:

    s.substr(0, 4)

gives:

    "abab"


WHY LPS WORKS
-------------
KMP continuously keeps track of the longest prefix that matches
a suffix.

For every position i:

    lps[i]

stores the longest proper prefix of:

    s[0...i]

which is also a suffix.

At the final index:

    lps[n-1]

represents the longest prefix of the ENTIRE string that is also
a suffix.

Therefore:

    answer = s.substr(0, lps[n-1])


PSEUDO CODE
-----------
    n = s.length()

    create lps[n]

    for i from 1 to n-1:

        j = lps[i-1]

        while j > 0 and s[i] != s[j]:

            j = lps[j-1]

        if s[i] == s[j]:

            j++

        lps[i] = j

    return s.substr(0, lps[n-1])


COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:

    string longestPrefix(string s) {

        int n = s.size();

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

        return s.substr(0, lps[n - 1]);
    }
};


TIME COMPLEXITY
----------------
Building the LPS array:

    O(n)

Getting the answer:

    O(n) at most

Overall:

    O(n)


SPACE COMPLEXITY
----------------
O(n)

for the LPS array.


================================================================================
DRY RUN
================================================================================

Input:

    s = "ababab"


STEP 1:
-------
Initialize:

    lps = [0, 0, 0, 0, 0, 0]


STEP 2:
-------
i = 1

Characters:

    s[1] = 'b'
    s[0] = 'a'

Not equal.

    lps[1] = 0


LPS:

    [0, 0, 0, 0, 0, 0]


STEP 3:
-------
i = 2

    s[2] = 'a'
    s[0] = 'a'

Equal.

    lps[2] = 1


LPS:

    [0, 0, 1, 0, 0, 0]


STEP 4:
-------
i = 3

    s[3] = 'b'
    s[1] = 'b'

Equal.

    lps[3] = 2


LPS:

    [0, 0, 1, 2, 0, 0]


STEP 5:
-------
i = 4

    s[4] = 'a'
    s[2] = 'a'

Equal.

    lps[4] = 3


LPS:

    [0, 0, 1, 2, 3, 0]


STEP 6:
-------
i = 5

    s[5] = 'b'
    s[3] = 'b'

Equal.

    lps[5] = 4


Final LPS:

    [0, 0, 1, 2, 3, 4]


STEP 7:
-------
Take:

    lps[n - 1]
    = lps[5]
    = 4

Therefore:

    s.substr(0, 4)

    = "abab"


FINAL ANSWER:
-------------
    "abab"


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
KMP / LPS / Prefix Function


KEY OBSERVATION
---------------
For LeetCode 1392:

    lps[n - 1]

IS THE ANSWER LENGTH.

So the entire problem becomes:

    Build LPS
        ↓
    Take lps.back()
        ↓
    Return that prefix


COMMON MISTAKES
---------------

1. Returning the entire string.

   The prefix must be PROPER, so its length must be < n.

2. Checking only one prefix.

3. Using brute force and getting O(n²).

4. Confusing:

       prefix == suffix

   with:

       substring == suffix

5. Forgetting the KMP fallback:

       j = lps[j - 1]

6. Using lps[i] incorrectly.

   Remember:

       lps[i] = longest proper prefix of s[0...i]
                that is also a suffix of s[0...i]


WHEN TO USE THIS APPROACH
-------------------------
Use KMP/LPS when the problem involves:

    - Longest prefix
    - Longest suffix
    - Prefix == suffix
    - Border of a string
    - Repeated patterns
    - String matching in O(n)


IMPORTANT CONNECTION
--------------------

LeetCode 1392:

    Longest Happy Prefix
            |
            v
       Build LPS
            |
            v
       lps[n - 1]
            |
            v
        Answer


LeetCode 214:

    Shortest Palindrome
            |
            v
    s + "#" + reverse(s)
            |
            v
       Build LPS
            |
            v
       lps[n - 1]
            |
            v
    Longest palindromic prefix


So both problems use the SAME KMP/LPS concept.


KMP TEMPLATE TO REMEMBER
------------------------

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


FINAL COMPLEXITY
----------------

    Time  : O(n)
    Space : O(n)

================================================================================
*/
#include <bits/stdc++.h>
using namespace std;

// ==================== OPTIMAL SOLUTION ====================

class Solution
{
public:
    long long sumScores(string s)
    {
        int n = s.size();

        vector<int> z(n, 0);

        int left = 0;
        int right = 0;

        for (int i = 1; i < n; i++)
        {

            // If i is inside the current Z-box,
            // reuse previously calculated information.
            if (i <= right)
            {
                z[i] = min(right - i + 1, z[i - left]);
            }

            // Extend the match.
            while (i + z[i] < n &&
                   s[z[i]] == s[i + z[i]])
            {
                z[i]++;
            }

            // Update the Z-box.
            if (i + z[i] - 1 > right)
            {
                left = i;
                right = i + z[i] - 1;
            }
        }

        // The entire string is also a suffix,
        // so its score is n.
        long long ans = n;

        for (int i = 1; i < n; i++)
        {
            ans += z[i];
        }

        return ans;
    }
};

// ==================== FOR VS CODE TESTING ====================

int main()
{
    Solution sol;

    string s = "babab";

    cout << sol.sumScores(s) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 2223
                     SUM OF SCORES OF STRING
================================================================================

PROBLEM STATEMENT
-----------------
You are given a string s.

The score of a suffix is the length of the longest common prefix
between the suffix and the original string s.

For every suffix of s, calculate its score and return the sum.

In other words, for every index i, we need to find:

    How many characters starting from s[i]
    are equal to the beginning of s?


Example:

    s = "babab"

Suffixes:

    "babab" -> matches "babab" -> score = 5
    "abab"  -> matches "b..."  -> score = 0
    "bab"   -> matches "bab"   -> score = 3
    "ab"    -> matches "b..."  -> score = 0
    "b"     -> matches "b"     -> score = 1

Answer:

    5 + 0 + 3 + 0 + 1 = 9


================================================================================
EXAMPLE
================================================================================

Input:

    s = "babab"

Output:

    9


Explanation:

    Suffix       Score

    babab          5
    abab           0
    bab            3
    ab             0
    b              1

Total:

    5 + 0 + 3 + 0 + 1

    = 9


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
For every position i, compare the suffix starting at i with the
prefix of the original string.

Start comparing from:

    s[0] with s[i]
    s[1] with s[i+1]
    s[2] with s[i+2]
    ...

Stop when:

    1. Characters become different, OR
    2. We reach the end of the string.

The number of matching characters is the score for suffix i.


PSEUDO CODE
-----------

    ans = 0

    for i = 0 to n-1:

        j = 0

        while i + j < n
              AND s[j] == s[i + j]:

            j++

        ans += j

    return ans


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    long long sumScores(string s) {

        int n = s.size();

        long long ans = 0;

        for (int i = 0; i < n; i++) {

            int j = 0;

            while (i + j < n &&
                   s[j] == s[i + j]) {

                j++;
            }

            ans += j;
        }

        return ans;
    }
};


TIME COMPLEXITY
----------------
There are O(n) suffixes.

For every suffix, we may compare O(n) characters.

Therefore:

    O(n²)


SPACE COMPLEXITY
----------------
O(1)


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
For every index i, we need:

    Length of the longest prefix of s
    that matches the substring starting at i.

This is exactly what the Z-function calculates.


Z-FUNCTION
----------
The Z-array is defined as:

    z[i] = length of the longest substring starting at i
           that is also a prefix of the entire string.


Example:

    s = "babab"

    index:   0  1  2  3  4
    char:    b  a  b  a  b

    z:       0  0  3  0  1


Explanation:

    z[1] = 0

        s starting at 1:
            "abab"

        prefix:
            "b..."

        First characters don't match.


    z[2] = 3

        substring:
            "bab"

        prefix:
            "bab"

        3 characters match.


    z[3] = 0

        substring:
            "ab"

        prefix:
            "ba"

        No match.


    z[4] = 1

        substring:
            "b"

        prefix:
            "b"

        1 character matches.


Therefore:

    score of suffix at index i = z[i]

except for i = 0.


WHY i = 0 IS DIFFERENT
----------------------
Normally:

    z[0] = 0

But the suffix starting at index 0 is the entire string.

The entire string matches itself.

Therefore:

    score[0] = n


So:

    answer = n + z[1] + z[2] + ... + z[n-1]


================================================================================
INTUITION OF Z-ALGORITHM
================================================================================

Naively, we compare characters again and again.

For example:

    s = "aaaaaaa"

There are many repeated comparisons.

The Z-algorithm avoids this using a window called the:

    Z-BOX


Z-BOX
-----
We maintain two variables:

    left
    right

The range:

    [left, right]

represents a substring that matches the prefix of s.

That means:

    s[left ... right]

matches:

    s[0 ... right-left]


If a new index i is inside this range:

    i <= right

we already know some matching information.

So we can reuse:

    z[i - left]


But we cannot blindly use the whole value because it may extend
outside the current Z-box.

Therefore:

    z[i] = min(right - i + 1, z[i - left])


Then we continue matching only if necessary.


================================================================================
PSEUDO CODE FOR Z-FUNCTION
================================================================================

    create z[n]

    left = 0
    right = 0

    for i = 1 to n-1:

        if i <= right:

            z[i] = min(
                right - i + 1,
                z[i - left]
            )

        while i + z[i] < n
              AND s[z[i]] == s[i + z[i]]:

            z[i]++

        if i + z[i] - 1 > right:

            left = i
            right = i + z[i] - 1


    ans = n

    for i = 1 to n-1:

        ans += z[i]

    return ans


================================================================================
COMPLETE OPTIMAL CODE
================================================================================

// class Solution {
// public:
//
//     long long sumScores(string s) {
//
//         int n = s.size();
//
//         vector<int> z(n, 0);
//
//         int left = 0;
//         int right = 0;
//
//         for (int i = 1; i < n; i++) {
//
//             if (i <= right) {
//                 z[i] = min(right - i + 1,
//                            z[i - left]);
//             }
//
//             while (i + z[i] < n &&
//                    s[z[i]] == s[i + z[i]]) {
//                 z[i]++;
//             }
//
//             if (i + z[i] - 1 > right) {
//                 left = i;
//                 right = i + z[i] - 1;
//             }
//         }
//
//         long long ans = n;
//
//         for (int i = 1; i < n; i++) {
//             ans += z[i];
//         }
//
//         return ans;
//     }
// };


================================================================================
TIME COMPLEXITY
================================================================================

Building the Z-array:

    O(n)

Calculating the answer:

    O(n)

Total:

    O(n)


SPACE COMPLEXITY
----------------
The Z-array takes:

    O(n)

Therefore:

    O(n)


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:

    s = "babab"


STEP 1: INITIALIZATION
----------------------

    n = 5

    z = [0, 0, 0, 0, 0]

    left = 0
    right = 0


STEP 2: i = 1
-------------

Compare:

    s[0] = 'b'
    s[1] = 'a'

Different.

Therefore:

    z[1] = 0

Z-array:

    [0, 0, 0, 0, 0]


STEP 3: i = 2
-------------

Compare:

    s[0] = 'b'
    s[2] = 'b'

Match.

Next:

    s[1] = 'a'
    s[3] = 'a'

Match.

Next:

    s[2] = 'b'
    s[4] = 'b'

Match.

Next position is outside the string.

Therefore:

    z[2] = 3


Z-box becomes:

    left = 2
    right = 4

Z-array:

    [0, 0, 3, 0, 0]


STEP 4: i = 3
-------------

i is inside the Z-box:

    3 <= 4

So we reuse previous information.

Eventually:

    z[3] = 0


Z-array:

    [0, 0, 3, 0, 0]


STEP 5: i = 4
-------------

Compare:

    s[0] = 'b'
    s[4] = 'b'

Match.

No more characters.

Therefore:

    z[4] = 1


Final Z-array:

    [0, 0, 3, 0, 1]


STEP 6: CALCULATE ANSWER
------------------------

The first suffix is the entire string.

Its score is:

    n = 5


Add remaining Z values:

    5 + 0 + 3 + 0 + 1

    = 9


FINAL ANSWER
------------

    9


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
Z-Algorithm / Prefix Matching


KEY OBSERVATION
---------------
For every index i:

    z[i]

is exactly the score of the suffix starting at i.

Therefore:

    answer = n + sum(z[i])

for:

    i = 1 to n-1


The entire problem can be solved using one Z-array.


================================================================================
KMP VS Z-FUNCTION
================================================================================

KMP / LPS:
-----------

    lps[i]

means:

    Longest proper PREFIX of s[0...i]
    that is also a SUFFIX of s[0...i].


Z-FUNCTION:
-----------

    z[i]

means:

    Longest PREFIX of s
    that matches the substring starting at i.


For LeetCode 2223:

    Z-function is the natural choice.


================================================================================
COMMON MISTAKES
================================================================================

1. FORGETTING THE FIRST SUFFIX

Normally:

    z[0] = 0

But the entire string matches itself.

Therefore:

    ans = n


2. USING int FOR THE ANSWER

The sum can become large.

Use:

    long long ans


3. CONFUSING Z-ARRAY WITH LPS

Z:

    prefix vs substring starting at i


LPS:

    prefix vs suffix


4. INCORRECT Z-BOX UPDATE

Correct:

    if (i + z[i] - 1 > right) {

        left = i;
        right = i + z[i] - 1;
    }


5. INCORRECT REUSE

When:

    i <= right

use:

    z[i] = min(right - i + 1, z[i - left])


Do NOT simply do:

    z[i] = z[i-left]


because the previous match may extend beyond the current Z-box.


6. OVERFLOW

Use:

    long long

for the final answer.


================================================================================
WHEN TO USE THIS APPROACH
================================================================================

Use Z-algorithm when you see:

    - Prefix matching
    - Prefix compared with every suffix
    - Prefix compared with every substring
    - Longest prefix match at every index
    - String matching problems
    - Sum of prefix-match lengths


Typical clue:

    "For every position, find how many characters match
     the beginning of the string."


Think:

    Z-FUNCTION


================================================================================
Z-FUNCTION TEMPLATE
================================================================================

    vector<int> z(n, 0);

    int left = 0;
    int right = 0;

    for (int i = 1; i < n; i++) {

        if (i <= right) {
            z[i] = min(right - i + 1,
                       z[i - left]);
        }

        while (i + z[i] < n &&
               s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }


================================================================================
IMPORTANT STRING PROBLEM CONNECTION
================================================================================

LEETCODE 1392
-------------
Longest Happy Prefix

    Prefix == Suffix

        ↓

    KMP / LPS


LEETCODE 214
------------
Shortest Palindrome

    Longest Palindromic Prefix

        ↓

    KMP / LPS


LEETCODE 2223
-------------
Sum of Scores of String

    Prefix == substring starting at i

        ↓

    Z-FUNCTION


REMEMBER:

    KMP / LPS
        =
    PREFIX-SUFFIX relationship


    Z-FUNCTION
        =
    PREFIX-SUBSTRING relationship


================================================================================
FINAL FORMULA
================================================================================

For LeetCode 2223:

    Build Z-array

    z[i] = score of suffix starting at i

    score of first suffix = n

Therefore:

    answer = n + z[1] + z[2] + ... + z[n-1]


FINAL COMPLEXITY:

    Time  : O(n)
    Space : O(n)

================================================================================
*/
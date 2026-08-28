#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int numberOfSubstrings(string s)
    {
        int n = s.length();
        int result = 0;
        vector<int> mp(3, 0);
        int i = 0;
        int j = 0;
        while (j < n)
        {
            char ch = s[j];
            mp[ch - 'a']++;
            while (mp[0] > 0 && mp[1] > 0 && mp[2] > 0)
            {
                result += (n - j);
                mp[s[i] - 'a']--;
                i++;
            }
            j++;
        }
        return result;
    }
};

int main()
{
    Solution sol;

    string s;
    cout << "Enter string containing only a, b and c: ";
    cin >> s;

    cout << "\nInput: " << s << '\n';
    cout << "Answer: " << sol.numberOfSubstrings(s) << '\n';

    return 0;
}

/*
================================================================================
LEETCODE 1358 - NUMBER OF SUBSTRINGS CONTAINING ALL THREE CHARACTERS
================================================================================

Problem Statement:
------------------
Given a string s consisting only of characters 'a', 'b', and 'c',
return the number of substrings containing at least one occurrence
of all three characters:

    'a'
    'b'
    'c'


Example:
--------
Input:
    s = "abcabc"

Output:
    10

Explanation:

The valid substrings are:

    "abc"
    "abca"
    "abcab"
    "abcabc"
    "bca"
    "bcab"
    "bcabc"
    "cab"
    "cabc"
    "abc"

Total = 10


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Generate every possible substring.

For every substring:
    1. Count whether it contains 'a'.
    2. Count whether it contains 'b'.
    3. Count whether it contains 'c'.
    4. If all three exist, increment answer.

We can optimize the checking slightly by maintaining the character
counts while extending the substring.

Pseudo Code:
-----------
result = 0

for i = 0 to n-1:
    countA = 0
    countB = 0
    countC = 0

    for j = i to n-1:
        update count of s[j]

        if countA > 0 AND countB > 0 AND countC > 0:
            result++

return result


Complete Brute Force Code (inside comments only):
---------------------------------------------------

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int result = 0;

        for (int i = 0; i < n; i++) {
            int a = 0, b = 0, c = 0;

            for (int j = i; j < n; j++) {
                if (s[j] == 'a')
                    a++;
                else if (s[j] == 'b')
                    b++;
                else
                    c++;

                if (a > 0 && b > 0 && c > 0)
                    result++;
            }
        }

        return result;
    }
};


Time Complexity:
----------------
O(n^2)

There are O(n^2) substrings.


Space Complexity:
-----------------
O(1)

Only three counters are used.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
We use a sliding window [i ... j].

The window is valid when it contains:

    at least one 'a'
    at least one 'b'
    at least one 'c'


The important observation is:

When the current window [i ... j] contains all three characters,
then every substring starting at i and ending at:

    j, j+1, j+2, ..., n-1

will also contain all three characters.

Therefore, the number of valid substrings is:

    n - j


Example:

    s = "abcabc"

When:

    i = 0
    j = 2

Window:

    "abc"

contains a, b and c.

Therefore all of these are valid:

    "abc"
    "abca"
    "abcab"
    "abcabc"

Count:

    n - j
    6 - 2
    = 4


Intuition:
---------
Use two pointers:

    i = left boundary
    j = right boundary

Expand j until the current window contains all three characters.

Once it becomes valid:

    result += n - j

Then move i forward to find another valid starting position.

We keep shrinking while the window remains valid.

This counts every valid substring exactly once.


Pseudo Code:
-----------
result = 0
left = 0

count[a] = count[b] = count[c] = 0

for right from 0 to n-1:

    add s[right] to frequency array

    while window contains a, b and c:

        result += n - right

        remove s[left]

        left++


return result


Complete Optimal Code (inside comments only):
-----------------------------------------------

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        int result = 0;

        vector<int> mp(3, 0);

        int i = 0;
        int j = 0;

        while (j < n) {

            mp[s[j] - 'a']++;

            while (mp[0] > 0 &&
                   mp[1] > 0 &&
                   mp[2] > 0) {

                result += n - j;

                mp[s[i] - 'a']--;
                i++;
            }

            j++;
        }

        return result;
    }
};


Time Complexity:
----------------
O(n)

Both pointers move only forward.

    j moves from 0 to n-1
    i moves from 0 to n-1

Therefore:

    O(n)


Space Complexity:
-----------------
O(1)

The frequency array contains only 3 elements.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:
    s = "abcabc"

n = 6

Initial:

    i = 0
    j = 0
    result = 0

    count = [0, 0, 0]


Step 1:
-------
j = 0

s[j] = 'a'

count:

    a = 1
    b = 0
    c = 0

Window is not valid.

Move j.


Step 2:
-------
j = 1

s[j] = 'b'

count:

    a = 1
    b = 1
    c = 0

Window is not valid.

Move j.


Step 3:
-------
j = 2

s[j] = 'c'

count:

    a = 1
    b = 1
    c = 1

Window:

    "abc"

is valid.

Therefore:

    result += n - j
           += 6 - 2
           += 4

result = 4


Now shrink from left.

Remove s[i] = 'a'

count:

    a = 0
    b = 1
    c = 1

i = 1

Window is no longer valid.

Move j.


Step 4:
-------
j = 3

s[j] = 'a'

count:

    a = 1
    b = 1
    c = 1

Valid again.

Add:

    n - j
    = 6 - 3
    = 3

result:

    4 + 3 = 7

Remove s[i] = 'b'

count:

    a = 1
    b = 0
    c = 1

i = 2


Step 5:
-------
j = 4

s[j] = 'b'

count:

    a = 1
    b = 1
    c = 1

Valid.

Add:

    6 - 4 = 2

result:

    7 + 2 = 9

Remove s[i] = 'c'

count:

    a = 1
    b = 1
    c = 0

i = 3


Step 6:
-------
j = 5

s[j] = 'c'

count:

    a = 1
    b = 1
    c = 1

Valid.

Add:

    6 - 5 = 1

result:

    9 + 1 = 10

Remove s[i] = 'a'

Window becomes invalid.

Final:

    result = 10


Answer:
    10


================================================================================
WHY result += (n - j)?
================================================================================

This is the most important part of the problem.

Suppose:

    s = "abcabc"
             ^
             j = 2

Current valid window:

    "abc"

Since "abc" already contains a, b and c, extending it can never
remove any character.

Therefore all these are also valid:

    [0...2] = "abc"
    [0...3] = "abca"
    [0...4] = "abcab"
    [0...5] = "abcabc"

There are:

    n - j

such substrings.

Therefore:

    result += n - j


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Sliding Window / Two Pointers


Key Observation:
----------------
Once a window contains all three characters, every extension of
that window to the right is also valid.

Therefore:

    number of valid extensions = n - right


Common Mistakes:
----------------

1. Adding only 1 when a valid window is found.

Wrong:

    result++

Correct:

    result += n - j


2. Moving the right pointer incorrectly.

The right pointer expands the window.

The left pointer shrinks the window.


3. Forgetting to remove s[i].

When moving i forward:

    mp[s[i] - 'a']--;


4. Using O(n) frequency storage.

The string contains only:

    a, b, c

so an array of size 3 is enough.


5. Continuing to move right after finding a valid window without
   counting all possible extensions.

Once valid:

    result += n - j

must happen before shrinking.


6. Using substring() repeatedly.

Creating substrings inside the loop can increase complexity and
unnecessary memory usage.

Use frequency counts instead.


7. Confusing "contains all three" with "contains exactly one".

The substring can contain any number of a, b and c.

It only needs:

    count(a) >= 1
    count(b) >= 1
    count(c) >= 1


When to Use This Approach:
--------------------------
Use sliding window when:

- You are counting substrings/subarrays.
- You have a condition on the current window.
- Expanding the window preserves or eventually achieves a condition.
- Once a window becomes valid, further expansion remains valid.
- You need O(n) instead of O(n^2).


Quick Revision:
---------------

Problem:
    Count substrings containing a, b and c.

Pattern:
    Sliding Window

Window:
    [i ... j]

Valid condition:
    countA > 0 && countB > 0 && countC > 0

When valid:
    result += n - j

Then:
    shrink from left

Complexity:
    Time  = O(n)
    Space = O(1)


Core Template:
--------------

while (right < n) {

    add s[right];

    while (window is valid) {

        answer += number of valid endings;

        remove s[left];
        left++;
    }

    right++;
}


================================================================================
*/

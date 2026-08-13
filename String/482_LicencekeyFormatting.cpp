#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string licenseKeyFormatting(string s, int k)
    {
        string t;

        // Remove '-' and convert letters to uppercase.
        for (char c : s)
        {
            if (c != '-')
                t += toupper(c);
        }

        int n = t.size();
        string ans;

        // First group can have fewer than k characters.
        int first = n % k;

        if (first > 0)
        {
            ans += t.substr(0, first);
        }

        for (int i = first; i < n; i += k)
        {
            if (!ans.empty())
                ans += '-';

            ans += t.substr(i, k);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<pair<string, int>> tests = {
        {"2-5g-3-J", 2},
        {"2-5g-3-J", 3},
        {"2-4A0r-7-4k", 4},
        {"--a-a-a-a--", 2}};

    for (auto &[s, k] : tests)
    {
        cout << sol.licenseKeyFormatting(s, k) << '\n';
    }

    return 0;
}

/*
================================================================================
                         LEETCODE 482
                    LICENSE KEY FORMATTING
================================================================================

Problem Statement:
------------------
You are given a license key represented as a string s.

The string contains:
    - English letters
    - Digits
    - Hyphens '-'

The license key must be reformatted according to these rules:

1. Remove all existing hyphens.
2. Convert all lowercase letters to uppercase.
3. Divide the characters into groups of size k.
4. The first group may contain fewer than k characters.
5. Groups are separated by exactly one hyphen.

Return the reformatted license key.


Example:
--------
Input:
    s = "2-5g-3-J"
    k = 2

Output:
    "2-5G-3J"

Explanation:
    Remove hyphens:

        25g3J

    Convert to uppercase:

        25G3J

    Group from the beginning:

        2 | 5G | 3J

    Result:

        2-5G-3J


Brute Force Approach:
---------------------

Idea:
-----
We can first remove all hyphens and convert all letters to uppercase.

Then repeatedly take k characters and build the answer.

This is essentially a straightforward simulation of the formatting
process.


Pseudo Code:
------------
function licenseKeyFormatting(s, k):

    t = empty string

    for every character c in s:
        if c != '-':
            add uppercase(c) to t

    ans = empty string
    count = 0

    traverse t from right to left:

        add character to ans

        count++

        if count == k:
            add '-' to ans
            count = 0

    remove unnecessary trailing '-'

    reverse ans

    return ans


Complete Brute Force Code:
--------------------------

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {

        string t;

        for (char c : s) {
            if (c != '-')
                t += toupper(c);
        }

        string ans;
        int count = 0;

        for (int i = (int)t.size() - 1; i >= 0; i--) {

            ans += t[i];
            count++;

            if (count == k && i != 0) {
                ans += '-';
                count = 0;
            }
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};


Time Complexity:
----------------
O(n)

where n is the length of the input string.


Space Complexity:
-----------------
O(n)

For storing the cleaned string and answer.


Optimal Approach:
-----------------

Observation:
------------
After removing hyphens, suppose the number of remaining characters is n.

Every group except the first group must contain exactly k characters.

Therefore:

    first group size = n % k

If:

    n % k == 0

then every group has exactly k characters.

Otherwise, the first group contains:

    n % k

characters.


Intuition:
----------
The most important part is determining the size of the first group.

Example:

    cleaned string = "25G3J"
    k = 2

n = 5

    n % k = 1

So:

    first group = "2"

Remaining characters:

    "5G3J"

Divide them into groups of k:

    "5G" and "3J"

Final answer:

    "2-5G-3J"


Pseudo Code:
------------
function licenseKeyFormatting(s, k):

    t = empty string

    for c in s:
        if c != '-':
            t += uppercase(c)

    n = length(t)

    first = n % k

    if first > 0:
        add t[0 ... first-1] to answer

    for i = first to n-1 step k:

        if answer is not empty:
            add '-' to answer

        add next k characters to answer

    return answer


Complete Optimal Code:
----------------------

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {

        string t;

        for (char c : s) {
            if (c != '-')
                t += toupper(c);
        }

        int n = t.size();
        string ans;

        int first = n % k;

        if (first > 0)
            ans += t.substr(0, first);

        for (int i = first; i < n; i += k) {

            if (!ans.empty())
                ans += '-';

            ans += t.substr(i, k);
        }

        return ans;
    }
};


Time Complexity:
----------------
O(n)

We scan the string and construct the answer once.


Space Complexity:
-----------------
O(n)

The cleaned string and final answer require O(n) space.


Dry Run with Example:
---------------------

s = "2-5g-3-J"
k = 2


Step 1: Remove hyphens and uppercase

    "2-5g-3-J"

becomes:

    "25G3J"


Step 2: Find length

    n = 5


Step 3: Find first group size

    n % k
    = 5 % 2
    = 1

Therefore:

    First group = "2"


Remaining:

    "5G3J"


Step 4: Divide remaining characters into groups of 2

    "5G"
    "3J"


Step 5: Add hyphens

    "2" + "-" + "5G" + "-" + "3J"

Result:

    "2-5G-3J"


Another Example:
----------------

s = "2-4A0r-7-4k"
k = 4


Remove hyphens:

    "24A0r74k"


Convert to uppercase:

    "24A0R74K"


n = 8

    n % k = 8 % 4 = 0

So every group has exactly 4 characters:

    "24A0"
    "R74K"

Result:

    "24A0-R74K"


Interview Notes:
----------------

Pattern:
    String Manipulation + Grouping


Key Observation:
    After removing hyphens, the first group has:

        n % k

    characters.

    Every subsequent group has exactly k characters.


Common Mistakes:
----------------
1. Grouping from the wrong side.

   The first group is allowed to have fewer than k characters,
   so calculate n % k first.

2. Forgetting to convert lowercase letters to uppercase.

3. Keeping the original hyphens.

4. Adding an extra hyphen at the beginning or end.

5. Forgetting that the input may contain consecutive hyphens.

6. Assuming the first group must always contain k characters.


When to use this approach:
--------------------------
Use this approach when:

    - A string must be cleaned before processing.
    - Characters need to be grouped into fixed-size blocks.
    - One special group exists at the beginning or end.
    - The problem involves formatting or normalization of strings.

The key trick to remember:

    FIRST GROUP SIZE = n % k

Then process the remaining characters in groups of k.

================================================================================
*/

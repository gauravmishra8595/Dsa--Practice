#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int repeatedStringMatch(string a, string b)
    {
        string repeated = a;
        int count = 1;
        while (repeated.size() < b.size())
        {
            repeated += a;
            count++;
        }

        if (repeated.find(b) != string::npos)
            return count;

        repeated += a;
        count++;

        if (repeated.find(b) != string::npos)
            return count;

        return -1;
    }
};

int main()
{
    Solution sol;

    string a, b;
    cin >> a >> b;

    cout << sol.repeatedStringMatch(a, b) << endl;

    return 0;
}

/*
============================================================
                    LEETCODE 686
                 Repeated String Match
============================================================

Problem Statement:
------------------
Given two strings a and b, return the minimum number of times
a must be repeated so that b becomes a substring of the
repeated string.

If it is impossible, return -1.

Example:
--------
Input:
a = "abcd"
b = "cdabcdab"

Output:
3

Explanation:
"abcd" repeated 3 times gives:

"abcdabcdabcd"

"cdabcdab" is a substring of it.

Another Example:
----------------
Input:
a = "a"
b = "aa"

Output:
2


------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Keep repeating a until the generated string is at least as long
as b.

After that, check whether b is present.

If not found, add one more copy of a and check again.

We only need at most one extra repetition after reaching the
length of b.

Pseudo Code:
------------
repeated = ""
count = 0

while length(repeated) < length(b):
    repeated += a
    count++

if b is substring of repeated:
    return count

repeated += a
count++

if b is substring of repeated:
    return count

return -1

Complete Brute Force Code:
---------------------------

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string repeated = "";
        int count = 0;

        while (repeated.size() < b.size()) {
            repeated += a;
            count++;
        }

        if (repeated.find(b) != string::npos)
            return count;

        repeated += a;
        count++;

        if (repeated.find(b) != string::npos)
            return count;

        return -1;
    }
};

Time Complexity:
----------------
O((n + m) * m) in the worst case using standard string::find().

Space Complexity:
-----------------
O(n + m)

where:
n = length of a
m = length of b


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
We need enough copies of a so that the repeated string has
at least the length of b.

The minimum possible number of repetitions is:

ceil(b.length() / a.length())

After reaching that length, b may still cross the boundary
between two copies of a.

Therefore, we only need to check:
    minimum repetitions
    minimum repetitions + 1

If b is not found after the extra copy, it is impossible.

Intuition:
----------
Suppose:

a = "abcd"
b = "cdabcdab"

Minimum repetitions:

ceil(8 / 4) = 2

Two copies:

"abcdabcd"

b = "cdabcdab"

It is not present.

Add one more copy:

"abcdabcdabcd"

Now b is present.

Therefore answer = 3.

Pseudo Code:
------------
repeated = a
count = 1

while length(repeated) < length(b):
    repeated += a
    count++

if b exists in repeated:
    return count

repeated += a
count++

if b exists in repeated:
    return count

return -1

Complete Optimal Code:
----------------------

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string repeated = a;
        int count = 1;

        while (repeated.size() < b.size()) {
            repeated += a;
            count++;
        }

        if (repeated.find(b) != string::npos)
            return count;

        repeated += a;
        count++;

        if (repeated.find(b) != string::npos)
            return count;

        return -1;
    }
};

Time Complexity:
----------------
O((n + m) * m) in the worst case with standard string::find().

Space Complexity:
-----------------
O(n + m)


------------------------------------------------------------
Dry Run With Example
------------------------------------------------------------

Example:
a = "abcd"
b = "cdabcdab"

Step 1:
--------
repeated = "abcd"
count = 1

Length of repeated = 4
Length of b = 8

4 < 8, so add a.

Step 2:
--------
repeated = "abcdabcd"
count = 2

Length = 8

Now repeated.size() >= b.size().

Check:

"abcdabcd"

Does it contain:

"cdabcdab"?

No.

Step 3:
--------
Add one more copy.

repeated = "abcdabcdabcd"
count = 3

Now:

"abcdabcdabcd"
   "cdabcdab"
       ^^^^^

b exists as a substring.

Therefore:

Answer = 3


------------------------------------------------------------
Important Case
------------------------------------------------------------

Example:
a = "abc"
b = "cabca"

Minimum repetitions:

ceil(5 / 3) = 2

repeated = "abcabc"

"cabca" exists.

Answer = 2.


Impossible Case:
----------------
a = "abc"
b = "def"

repeated strings will always contain only:

a, b, c

So "def" can never occur.

Answer = -1.


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
String Matching + Repetition

Key Observation:
----------------
Start with the minimum number of copies needed to reach the
length of b.

Then check one additional copy.

Why only one additional copy?
------------------------------
b can start near the end of one copy of a and continue into the
next copy.

Once we have enough length for b, one extra copy is sufficient
to cover this boundary case.

Common Mistakes:
----------------
1. Stopping as soon as repeated.size() >= b.size().
2. Forgetting the extra repetition.
3. Returning the number of copies before checking whether b
   actually exists.
4. Returning 0 when b is not found instead of -1.
5. Using only length comparison without substring checking.
6. Forgetting that b can start in the middle of a repetition.

When to Use This Approach:
--------------------------
Use this approach when:
- One string must be repeated.
- We need to find another string as a substring.
- The repeated string can cross copy boundaries.
- We need the minimum number of repetitions.

General Template:
-----------------
1. Repeat the base string until its length >= target length.
2. Check whether target exists.
3. If not, repeat once more.
4. If still absent, return -1.

============================================================
*/
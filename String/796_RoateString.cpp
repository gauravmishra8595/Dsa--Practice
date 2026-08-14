#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool rotateString(string s, string goal)
    {
        if (s.size() != goal.size())
            return false;

        string doubled = s + s;

        return doubled.find(goal) != string::npos;
    }
};

int main()
{
    Solution sol;

    string s, goal;
    cin >> s >> goal;

    cout << boolalpha << sol.rotateString(s, goal) << endl;

    return 0;
}

/*
============================================================
                    LEETCODE 796
                   Rotate String
============================================================

Problem Statement:
------------------
Given two strings s and goal, return true if and only if s can
become goal after some number of shifts on s.

A shift consists of moving the leftmost character of s to the
rightmost position.

Example:
--------
Input:
s = "abcde"
goal = "cdeab"

Output:
true

Explanation:
"abcde" -> "bcdea" -> "cdeab"

Another Example:
----------------
Input:
s = "abcde"
goal = "abced"

Output:
false

------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Try every possible rotation of s and compare it with goal.

For every rotation:
    - Move the first character to the end.
    - Check whether the resulting string equals goal.

If any rotation matches, return true.

Pseudo Code:
------------
if lengths are different:
    return false

for i = 0 to n-1:
    create rotated string
    if rotated == goal:
        return true

return false

Complete Brute Force Code:
---------------------------

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size())
            return false;

        int n = s.size();

        for (int shift = 0; shift < n; shift++) {
            string rotated = "";

            for (int i = shift; i < n; i++)
                rotated += s[i];

            for (int i = 0; i < shift; i++)
                rotated += s[i];

            if (rotated == goal)
                return true;
        }

        return false;
    }
};

Time Complexity:
----------------
O(n^2)

Space Complexity:
-----------------
O(n)


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
If goal is a rotation of s, then goal must appear as a substring
of:

    s + s

Example:

s = "abcde"

s + s = "abcdeabcde"

All rotations appear inside this string:

"abcde"
"bcdea"
"cdeab"
"deabc"
"eabcd"

Therefore, we only need to check whether goal exists inside
s + s.

Intuition:
----------
Concatenating s with itself contains every possible rotation
of s.

So:

    goal is rotation of s
    <=> goal is substring of (s + s)

First, check that both strings have the same length.

Then use string::find().

Pseudo Code:
------------
if length(s) != length(goal):
    return false

doubled = s + s

if goal exists inside doubled:
    return true

return false

Complete Optimal Code:
----------------------

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size())
            return false;

        string doubled = s + s;

        return doubled.find(goal) != string::npos;
    }
};

Time Complexity:
----------------
O(n^2) in the worst case with the standard string::find()
implementation.

For typical competitive programming constraints, this is
more than sufficient.

Space Complexity:
-----------------
O(n)


------------------------------------------------------------
Dry Run With Example
------------------------------------------------------------

s = "abcde"
goal = "cdeab"

Step 1:
--------
Check lengths:

s.length()    = 5
goal.length() = 5

Lengths are equal.

Step 2:
--------
Create:

doubled = s + s

doubled = "abcdeabcde"

Step 3:
--------
Search for goal:

goal = "cdeab"

"abcdeabcde"
   ^^^^^

"cdeab" exists inside doubled.

Therefore:

return true


Another Example:
----------------

s = "abcde"
goal = "abced"

doubled = "abcdeabcde"

"abced" does not appear.

Therefore:

return false


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
String Rotation / String Matching

Key Observation:
----------------
For two strings to be rotations of each other:

1. Their lengths must be equal.
2. goal must be present in s + s.

Common Mistakes:
----------------
1. Forgetting to check that both strings have equal length.
2. Checking only one rotation.
3. Comparing s and goal directly without considering rotation.
4. Using s + s without first checking the lengths.
5. Confusing rotation with an arbitrary rearrangement of
   characters.

When to Use This Approach:
--------------------------
Use this technique when:
- You need to check whether one string is a rotation of another.
- The relative order of characters must remain unchanged.
- Circular/string rotation is involved.

Important Formula:
------------------
If:

s = "abcd"

then:

s + s = "abcdabcd"

Every rotation of s can be found as a substring:

"abcd"
"bcda"
"cdab"
"dabc"

Therefore:

goal is rotation of s
        ||
        VV
goal is substring of s + s

============================================================
*/
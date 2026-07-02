#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
            return false;

        vector<int> freq(26, 0);

        for (char ch : s)
            freq[ch - 'a']++;

        for (char ch : t)
            freq[ch - 'a']--;

        for (int count : freq)
        {
            if (count != 0)
                return false;
        }

        return true;
    }
};

int main()
{
    Solution obj;

    string s, t;

    cout << "Enter first string : ";
    cin >> s;

    cout << "Enter second string : ";
    cin >> t;

    if (obj.isAnagram(s, t))
        cout << "Valid Anagram";
    else
        cout << "Not a Valid Anagram";

    return 0;
}

/*
=========================================================
LeetCode 242 - Valid Anagram
=========================================================

Problem:
Given two strings s and t, return true if t is an anagram
of s, otherwise return false.

---------------------------------------------------------
Brute Force Approach
---------------------------------------------------------

Idea:
1. Check if lengths are equal.
2. Sort both strings.
3. Compare them.
4. If equal -> Valid Anagram
   Else -> Not Anagram

Example:

s = "cat"
t = "tac"

After Sorting

s = "act"
t = "act"

Both are equal, so answer is True.

Time Complexity:
O(n log n)

Space Complexity:
O(1)

---------------------------------------------------------
Optimal Approach (Frequency Array)
---------------------------------------------------------

Idea:

If two strings are anagrams,
every character should appear the same number of times.

Create a frequency array of size 26.

Step 1:
Traverse string s and increase frequency.

Example:

s = "aab"

a -> 2
b -> 1

Step 2:
Traverse string t and decrease frequency.

Example:

t = "aba"

a -> 0
b -> 0

Step 3:
If every frequency becomes 0,
both strings contain the same characters.

Return true.

Otherwise,
return false.

---------------------------------------------------------
Why Frequency Array?

Because only lowercase English letters exist.

'a' -> index 0
'b' -> index 1
...
'z' -> index 25

---------------------------------------------------------
Time Complexity

Length Check      -> O(1)

First Traversal   -> O(n)

Second Traversal  -> O(n)

Final Frequency Check -> O(26)

Overall Time Complexity:

O(n)

---------------------------------------------------------
Space Complexity

Frequency Array = 26 integers

O(1)

(Constant Space)

---------------------------------------------------------
Interview Summary

Brute Force
------------
Sort both strings and compare.

Time  : O(n log n)

Space : O(1)

Optimal
------------
Use a frequency array.

Increase frequency for first string.

Decrease frequency for second string.

If every frequency becomes 0,
strings are anagrams.

Time  : O(n)

Space : O(1)

// =========================================================+===*/

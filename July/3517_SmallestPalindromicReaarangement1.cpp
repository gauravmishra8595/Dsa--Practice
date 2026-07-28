#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string smallestPalindrome(string s)
    {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        string left = "";
        char mid = 0;

        for (int i = 0; i < 26; i++)
        {
            left.append(cnt[i] / 2, char('a' + i));
            if (cnt[i] % 2)
                mid = char('a' + i);
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid)
            return left + string(1, mid) + right;

        return left + right;
    }
};

int main()
{
    Solution obj;

    string s;
    cin >> s;

    cout << obj.smallestPalindrome(s);

    return 0;
}

/*

==========================
Problem Statement
==========================

LeetCode 3517 - Smallest Palindromic Rearrangement I

You are given a palindromic string s.

Return the lexicographically smallest palindromic permutation of s.

Constraints:
1 <= s.length <= 1e5
s contains only lowercase English letters.
s is guaranteed to be a palindrome.

--------------------------------------------------

Example

Input:
babab

Output:
abbba

Explanation:
Possible palindromes:
babab
abbba

Lexicographically smallest = abbba

==================================================
Brute Force Approach
==================================================

Idea
----
Generate every permutation of the string.
Check whether it is a palindrome.
Store the smallest lexicographically valid palindrome.

Obviously impossible for large N.

Pseudo Code
-----------

Generate all permutations
For every permutation
    if palindrome
        answer=min(answer,current)

Complete Brute Force Code
-------------------------

string ans = "~";
sort(s.begin(), s.end());
do{
    string t=s;
    string rev=t;
    reverse(rev.begin(),rev.end());
    if(t==rev)
        ans=min(ans,t);
}while(next_permutation(s.begin(),s.end()));

return ans;

Time Complexity
---------------
O(N! * N)

Space Complexity
----------------
O(N)

==================================================
Optimal Approach (Counting)
==================================================

Observation
-----------

Since the string is already guaranteed to be a palindrome,

Only one character can have odd frequency.

The first half completely determines the whole palindrome.

To obtain the lexicographically smallest palindrome,
the left half should be as small as possible.

Intuition
---------

1. Count frequency of every character.

2. Put freq/2 copies of each character into the left half
   from 'a' to 'z'.

3. If some character has odd frequency,
   keep one copy as the middle character.

4. Reverse left half to create right half.

Pseudo Code
-----------

count frequencies

left=""

mid=""

for c='a' to 'z'

    append freq[c]/2 copies into left

    if freq[c] odd
        mid=c

right=reverse(left)

return left + mid + right

Complete Optimal Code
---------------------

class Solution {
public:

    string smallestPalindrome(string s) {

        vector<int> cnt(26);

        for(char c:s)
            cnt[c-'a']++;

        string left="";
        char mid=0;

        for(int i=0;i<26;i++){

            left.append(cnt[i]/2,char('a'+i));

            if(cnt[i]&1)
                mid=char('a'+i);
        }

        string right=left;
        reverse(right.begin(),right.end());

        if(mid)
            return left+string(1,mid)+right;

        return left+right;
    }
};

Time Complexity
---------------
O(N)

Space Complexity
----------------
O(1)

(26 frequency array only)

==================================================
Dry Run
==================================================

Input

babab

Frequency

a -> 2

b -> 3

Left Half

a contributes 1

b contributes 1

left = "ab"

Middle

b

Right

reverse("ab")

= "ba"

Answer

ab + b + ba

= abbba

==================================================
Interview Notes
==================================================

Pattern
-------

Frequency Counting
+
Greedy Construction

Key Observation
---------------

Only the left half needs to be minimized.
The right half is automatically fixed.

Common Mistakes
---------------

1. Sorting the entire string unnecessarily.

2. Forgetting the middle odd-frequency character.

3. Building the right half independently instead of reversing.

4. Using all occurrences instead of freq/2 in the left half.

When to use this approach
-------------------------

Whenever

• Rearrangement is allowed

• Character frequencies matter

• Palindrome construction

• Lexicographically smallest/largest palindrome

This counting + greedy construction is the standard optimal pattern.

*/
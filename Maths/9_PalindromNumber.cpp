#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;

        int rev = 0;

        while (x > rev)
        {
            rev = rev * 10 + x % 10;
            x /= 10;
        }

        return (x == rev || x == rev / 10);
    }
};

int main()
{
    Solution obj;

    int x = 121;

    if (obj.isPalindrome(x))
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}

/*

===========================
LeetCode 9
Palindrome Number
===========================

--------------------------------------------------
Problem Statement
--------------------------------------------------
Given an integer x, return true if x is a palindrome,
and false otherwise.

A palindrome reads the same forward and backward.

--------------------------------------------------
Example
--------------------------------------------------

Input:
x = 121

Output:
true

Explanation:
Forward = 121
Backward = 121

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
-----
Reverse the entire number and compare it with the original.

Pseudo Code
------------
original = x
reverse = 0

while x > 0
    reverse = reverse * 10 + x % 10
    x = x / 10

return reverse == original

Complete Brute Force Code
-------------------------

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;

        long long original = x;
        long long rev = 0;

        while(x > 0){
            rev = rev * 10 + x % 10;
            x /= 10;
        }

        return rev == original;
    }
};

Time Complexity
---------------
O(log N)

Space Complexity
----------------
O(1)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
A palindrome remains the same after reversing.
Instead of reversing the whole number, reverse only
the second half of the digits.

Negative numbers and numbers ending with 0
(except 0 itself) can never be palindromes.

Intuition
---------
Reverse digits until the reversed half becomes
greater than or equal to the remaining half.

For even digits:
left == reversedHalf

For odd digits:
left == reversedHalf / 10

Pseudo Code
------------
if x < 0
    return false

if x ends with 0 and x != 0
    return false

rev = 0

while x > rev
    rev = rev * 10 + x % 10
    x /= 10

return (x == rev) OR (x == rev / 10)

Complete Optimal Code
---------------------

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;

        int rev = 0;

        while (x > rev) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }

        return (x == rev || x == rev / 10);
    }
};

Time Complexity
---------------
O(log N)

Space Complexity
----------------
O(1)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
x = 1221

Iteration 1:
rev = 1
x = 122

Iteration 2:
rev = 12
x = 12

Now:
x == rev

Return true.

Example (Odd Digits)

Input:
x = 12321

Final values:
x = 12
rev = 123

Ignore middle digit:

rev / 10 = 12

Return true.

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Mathematics + Reverse Half Number

Key Observation
---------------
There is no need to reverse the complete number.
Reversing only half avoids integer overflow and is
more efficient.

Common Mistakes
---------------
1. Forgetting that negative numbers are not palindromes.
2. Not handling numbers ending in 0 correctly.
3. Reversing the whole number, which may overflow.
4. Forgetting to remove the middle digit for odd-length numbers.

When to use this approach
-------------------------
Whenever only symmetry needs to be checked in a number,
consider reversing only half of the digits instead of
the entire number.

*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int smallestRepunitDivByK(int k)
    {
        if (k % 2 == 0 || k % 5 == 0)
            return -1;

        int rem = 0;

        for (int len = 1; len <= k; len++)
        {
            rem = (rem * 10 + 1) % k;

            if (rem == 0)
                return len;
        }

        return -1;
    }
};

int main()
{
    Solution obj;

    int k = 3;

    cout << obj.smallestRepunitDivByK(k) << endl;

    return 0;
}

/*

===========================
LeetCode 1015
Smallest Integer Divisible by K
===========================

--------------------------------------------------
Problem Statement
--------------------------------------------------
Given a positive integer k, return the length of the
smallest positive integer consisting only of digit '1'
that is divisible by k.

If no such integer exists, return -1.

A number consisting only of digit '1' is called a Repunit.

--------------------------------------------------
Example
--------------------------------------------------

Input:
k = 3

Output:
3

Explanation:
111 is divisible by 3.

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
-----
Generate numbers:
1
11
111
1111
...

Check divisibility after each generation.

This quickly overflows for large k.

Pseudo Code
------------
num = 0

for len = 1...
    num = num * 10 + 1

    if num % k == 0
        return len

return -1

Complete Brute Force Code
-------------------------

class Solution {
public:
    int smallestRepunitDivByK(int k) {

        long long num = 0;

        for(int len = 1; len <= 18; len++) {

            num = num * 10 + 1;

            if(num % k == 0)
                return len;
        }

        return -1;
    }
};

Time Complexity
---------------
Exponential growth (overflow occurs)

Space Complexity
----------------
O(1)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
We never need the complete number.

Only its remainder modulo k matters.

Using the property:

newRemainder =
(previousRemainder × 10 + 1) % k

There are only k possible remainders:
0 to k-1.

If remainder repeats, the sequence will repeat forever.

Hence after checking k lengths,
if remainder never becomes 0,
answer is impossible.

Also,
if k is divisible by 2 or 5,
no repunit can ever be divisible by k.

Intuition
---------
Build the remainder digit by digit.

Avoid constructing huge numbers.

Stop immediately when remainder becomes 0.

Pseudo Code
------------
if k divisible by 2 or 5
    return -1

rem = 0

for len = 1 to k

    rem = (rem * 10 + 1) % k

    if rem == 0
        return len

return -1

Complete Optimal Code
---------------------

class Solution {
public:
    int smallestRepunitDivByK(int k) {

        if(k % 2 == 0 || k % 5 == 0)
            return -1;

        int rem = 0;

        for(int len = 1; len <= k; len++) {

            rem = (rem * 10 + 1) % k;

            if(rem == 0)
                return len;
        }

        return -1;
    }
};

Time Complexity
---------------
O(K)

Space Complexity
----------------
O(1)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
k = 3

Length = 1

rem = (0*10 + 1)%3
    = 1

Length = 2

rem = (1*10 +1)%3
    = 11%3
    = 2

Length = 3

rem = (2*10 +1)%3
    = 21%3
    = 0

Return 3

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Math + Modulo Arithmetic

Key Observation
---------------
Instead of storing the entire repunit,
store only its remainder modulo k.

There are only k distinct remainders,
so checking beyond k iterations is unnecessary.

Common Mistakes
---------------
1. Constructing the actual number (overflow).
2. Forgetting the special case:
   k divisible by 2 or 5.
3. Using long long and assuming it is enough.

When to use this approach
-------------------------
Whenever extremely large numbers are formed only to
test divisibility, maintain the remainder instead
of constructing the number.

*/
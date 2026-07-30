#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int getSum(int a, int b)
    {

        while (b != 0)
        {

            int carry = (a & b) << 1;

            a = a ^ b;

            b = carry;
        }

        return a;
    }
};

int main()
{
    Solution obj;

    int a = 5;
    int b = 7;

    cout << obj.getSum(a, b) << endl; // Output: 12

    return 0;
}

/*

========================================
LeetCode 371. Sum of Two Integers
========================================

Problem Statement:
Given two integers a and b, return the sum of the two integers
without using the operators + and -.

--------------------------------------------------
Example
--------------------------------------------------

Input:
a = 5
b = 7

Output:
12

Explanation:

5 + 7 = 12

But + operator is not allowed.

==================================================
Brute Force Approach
==================================================

Idea:
Use repeated increment/decrement operations.

If b is positive:
    Increase a by 1
    Decrease b by 1

If b is negative:
    Decrease a by 1
    Increase b by 1

Continue until b becomes zero.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

while(b != 0)

    if b > 0
        a++
        b--

    else
        a--
        b++

return a

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int getSum(int a, int b) {

        while(b != 0) {

            if(b > 0) {
                a++;
                b--;
            }
            else {
                a--;
                b++;
            }
        }

        return a;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(|b|)

Can be very slow for large values.

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Optimal Approach
==================================================

Observation:

Binary addition can be done using bit operations.

Two important operations:

1. XOR (^)
   Gives sum without considering carry.

Example:

5 = 0101
7 = 0111

XOR:

0101
0111
----
0010

This gives addition without carry.


2. AND (&)
   Finds carry positions.

Carry needs to be shifted left by one position.

Carry:

0101
0111
----
0101 << 1

--------------------------------------------------
Intuition
--------------------------------------------------

Repeat:

sum = a XOR b

carry = (a AND b) << 1

Replace:

a = sum
b = carry

When carry becomes zero,
all additions are completed.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

while(b != 0)

    carry = (a & b) << 1

    a = a ^ b

    b = carry

return a

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int getSum(int a, int b) {

        while(b != 0) {

            int carry = (a & b) << 1;

            a = a ^ b;

            b = carry;
        }

        return a;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(32)

Because integer has fixed number of bits.

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Dry Run With Example
==================================================

Input:

a = 5
b = 7


Binary:

a = 0101
b = 0111


Iteration 1:

carry = (0101 & 0111) << 1

     = 0101 << 1

     = 1010


sum = 0101 ^ 0111

    = 0010


a = 0010
b = 1010


Iteration 2:

carry = (0010 & 1010) << 1

     = 0010 << 1

     = 0100


sum = 0010 ^ 1010

    = 1000


a = 1000
b = 0100


Iteration 3:

carry = (1000 & 0100) << 1

     = 0000


sum = 1000 ^ 0100

    = 1100


b = 0

Stop.

1100 = 12

Answer = 12


==================================================
Interview Notes
==================================================

Pattern:
- Bit Manipulation
- Binary Addition
- XOR and Carry Technique

Key Observation:
XOR gives addition without carry.
AND followed by left shift gives carry.

Common Mistakes:
- Forgetting to shift carry left.
- Using + or - operators.
- Ignoring integer overflow behavior.
- Not handling negative numbers.

When to use this approach:
- Addition without arithmetic operators.
- Bitwise arithmetic problems.
- Understanding binary operations.
- Low-level programming questions.

*/
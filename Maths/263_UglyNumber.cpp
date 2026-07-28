#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isUgly(int n)
    {
        if (n <= 0)
            return false;

        while (n % 2 == 0)
            n /= 2;

        while (n % 3 == 0)
            n /= 3;

        while (n % 5 == 0)
            n /= 5;

        return n == 1;
    }
};

int main()
{
    Solution obj;

    int n = 6;

    if (obj.isUgly(n))
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}

/*

===========================
LeetCode 263
Ugly Number
===========================

--------------------------------------------------
Problem Statement
--------------------------------------------------
An ugly number is a positive integer whose prime factors
are limited to 2, 3, and 5.

Given an integer n, return true if n is an ugly number.
Otherwise, return false.

--------------------------------------------------
Example
--------------------------------------------------

Input:
n = 6

Output:
true

Explanation:
6 = 2 × 3

Its prime factors are only 2 and 3.

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
-----
Find all prime factors of n using trial division.

If any prime factor other than 2, 3, or 5 exists,
return false.

Otherwise return true.

Pseudo Code
------------
if n <= 0
    return false

for i = 2 to sqrt(n)
    while n divisible by i
        if i is not 2,3,5
            return false
        divide n by i

if remaining n > 1 and n not in {2,3,5}
    return false

return true

Complete Brute Force Code
-------------------------

class Solution {
public:
    bool isUgly(int n) {
        if(n <= 0) return false;

        for(int i = 2; i * i <= n; i++) {
            while(n % i == 0) {
                if(i != 2 && i != 3 && i != 5)
                    return false;
                n /= i;
            }
        }

        if(n > 1 && n != 2 && n != 3 && n != 5)
            return false;

        return true;
    }
};

Time Complexity
---------------
O(√N)

Space Complexity
----------------
O(1)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
If n is an ugly number, repeatedly dividing it by
2, 3, and 5 should eventually reduce it to 1.

If any other prime factor exists, the remaining
number will be greater than 1.

Intuition
---------
Remove all factors of 2.

Then remove all factors of 3.

Then remove all factors of 5.

If the final number becomes 1,
all prime factors were only 2, 3, and 5.

Pseudo Code
------------
if n <= 0
    return false

while n divisible by 2
    divide by 2

while n divisible by 3
    divide by 3

while n divisible by 5
    divide by 5

return (n == 1)

Complete Optimal Code
---------------------

class Solution {
public:
    bool isUgly(int n) {
        if(n <= 0)
            return false;

        while(n % 2 == 0)
            n /= 2;

        while(n % 3 == 0)
            n /= 3;

        while(n % 5 == 0)
            n /= 5;

        return n == 1;
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
n = 30

30 divisible by 2
n = 15

15 divisible by 3
n = 5

5 divisible by 5
n = 1

n == 1

Return true

Example 2

Input:
n = 14

14 divisible by 2
n = 7

7 is not divisible by 2, 3, or 5

Remaining number = 7

Return false

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Mathematics + Prime Factorization

Key Observation
---------------
An ugly number contains only the prime factors
2, 3, and 5.

Removing these factors repeatedly should leave
exactly 1.

Common Mistakes
---------------
1. Forgetting that n <= 0 is not an ugly number.
2. Dividing only once instead of repeatedly.
3. Trying to check every prime factor unnecessarily.

When to use this approach
-------------------------
Whenever a problem restricts the allowed prime
factors, repeatedly divide by the allowed factors
until no longer possible and inspect the remainder.

*/
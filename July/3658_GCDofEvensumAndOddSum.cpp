#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        return n;
    }
};

int main() {
    Solution obj;

    int n = 10;
    cout << obj.gcdOfOddEvenSums(n) << endl;

    return 0;
}

/*

===========================
LeetCode 3658 - GCD of Odd and Even Sums
===========================

Problem Statement
-----------------
Given an integer n,

- SumOdd = sum of the first n odd numbers.
- SumEven = sum of the first n even numbers.

Return gcd(SumOdd, SumEven).

--------------------------------------------------

Example
-------
Input:
n = 5

Odd Numbers:
1 + 3 + 5 + 7 + 9 = 25

Even Numbers:
2 + 4 + 6 + 8 + 10 = 30

gcd(25, 30) = 5

Output:
5

==================================================
Brute Force Approach
==================================================

Idea
----
Generate the first n odd numbers and first n even numbers,
calculate both sums, then compute their GCD.

Pseudo Code
-----------
sumOdd = 0
sumEven = 0

for i = 1 to n
    sumOdd += (2*i - 1)
    sumEven += (2*i)

return gcd(sumOdd, sumEven)

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int sumOdd = 0;
        int sumEven = 0;

        for(int i = 1; i <= n; i++) {
            sumOdd += (2 * i - 1);
            sumEven += (2 * i);
        }

        return gcd(sumOdd, sumEven);
    }
};

Time Complexity
---------------
O(n)

Space Complexity
----------------
O(1)

==================================================
Optimal Approach
==================================================

Observation
-----------
Sum of first n odd numbers = n²

Sum of first n even numbers = n(n+1)

So,

gcd(n², n(n+1))

= n × gcd(n, n+1)

Consecutive integers are always coprime.

Therefore,

gcd(n², n(n+1)) = n

Hence the answer is simply n.

--------------------------------------------------

Intuition
---------
Instead of calculating the sums, use the mathematical
formula and GCD property.

This converts an O(n) problem into O(1).

--------------------------------------------------

Pseudo Code
-----------
return n

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        return n;
    }
};

Time Complexity
---------------
O(1)

Space Complexity
----------------
O(1)

==================================================
Dry Run
==================================================

Input:
n = 5

SumOdd = 25

SumEven = 30

gcd(25,30)

= gcd(5²,5×6)

= 5 × gcd(5,6)

= 5 × 1

= 5

Answer = 5

==================================================
Interview Notes
==================================================

Pattern
-------
Math
Number Theory
GCD Properties

Key Observation
---------------
1. Sum of first n odd numbers = n²
2. Sum of first n even numbers = n(n+1)
3. gcd(a×b, a×c) = a × gcd(b,c)
4. gcd(n,n+1)=1

Common Mistakes
---------------
- Simulating the sums unnecessarily.
- Forgetting the formula for odd/even sums.
- Missing the consecutive numbers GCD property.

When to use this approach
-------------------------
Whenever:
- Sum formulas are known.
- GCD is involved.
- Mathematical simplification can replace simulation.
- Looking for an O(1) solution.

*/
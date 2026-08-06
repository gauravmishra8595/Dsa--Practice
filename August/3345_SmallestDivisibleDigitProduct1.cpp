#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int productOfDigits(int x) {
        int prod = 1;
        while (x > 0) {
            prod *= (x % 10);
            x /= 10;
        }
        return prod;
    }

    int smallestNumber(int n, int t) {
        while (true) {
            if (productOfDigits(n) % t == 0)
                return n;
            n++;
        }
    }
};

int main() {
    Solution obj;

    int n = 10, t = 2;
    cout << obj.smallestNumber(n, t) << endl;

    return 0;
}

/*

==========================
LeetCode 3345
Smallest Divisible Digit Product I
==========================

Problem Statement
-----------------
Given two integers n and t, return the smallest integer greater than or equal
to n such that the product of its digits is divisible by t.

--------------------------------------------------

Example
-------

Input:
n = 10, t = 2

Output:
10

Explanation:
Product of digits = 1 * 0 = 0
0 % 2 == 0

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
----
Start from n and keep checking every number.
For each number:
1. Compute the product of its digits.
2. If product % t == 0, return the number.
Otherwise continue.

Pseudo Code
-----------
curr = n

while(true)
    product = productOfDigits(curr)

    if(product % t == 0)
        return curr

    curr++

Complete Brute Force Code
-------------------------

class Solution {
public:

    int productOfDigits(int x){
        int prod = 1;

        while(x){
            prod *= x % 10;
            x /= 10;
        }

        return prod;
    }

    int smallestNumber(int n, int t) {

        int curr = n;

        while(true){

            if(productOfDigits(curr) % t == 0)
                return curr;

            curr++;
        }
    }
};

Time Complexity
---------------
O(k * d)

k = numbers checked
d = number of digits

Space Complexity
----------------
O(1)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
Constraints are very small.
A brute-force search is already efficient enough.
The only optimization needed is computing the digit product in O(number of digits).

Intuition
---------
Instead of generating candidates in any complicated way,
simply scan from n upwards until a valid number is found.

Pseudo Code
-----------
while(true)

    product = productOfDigits(n)

    if(product % t == 0)
        return n

    n++

Complete Optimal Code
---------------------

class Solution {
public:

    int productOfDigits(int x){
        int prod = 1;

        while(x){
            prod *= x % 10;
            x /= 10;
        }

        return prod;
    }

    int smallestNumber(int n, int t){

        while(true){

            if(productOfDigits(n) % t == 0)
                return n;

            n++;
        }
    }
};

Time Complexity
---------------
O(k * d)

k = number of integers checked
d = number of digits

Space Complexity
----------------
O(1)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
n = 14
t = 3

n = 14

Digits:
1,4

Product = 4

4 % 3 = 1

Not divisible.

Increment.

n = 15

Product = 1 * 5 = 5

5 % 3 = 2

Increment.

n = 16

Product = 1 * 6 = 6

6 % 3 = 0

Answer = 16

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Brute Force + Digit Manipulation

Key Observation
---------------
Product of digits can be computed in O(number of digits).
Since constraints are tiny, sequential search is sufficient.

Common Mistakes
---------------
1. Forgetting that digit 0 makes the entire product 0.
2. Using string conversion unnecessarily.
3. Overthinking with factorization.

When to use this approach
-------------------------
Whenever constraints are small and checking each candidate
takes only O(number of digits), a simple linear search is often
the intended solution.

*/
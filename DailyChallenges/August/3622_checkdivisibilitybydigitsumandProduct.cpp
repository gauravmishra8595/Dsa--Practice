#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool checkDivisibility(int n) {
        int original = n;
        int sum = 0;
        int product = 1;

        while (n > 0) {
            int digit = n % 10;
            sum += digit;
            product *= digit;
            n /= 10;
        }

        return original % (sum + product) == 0;
    }
};

int main() {
    Solution sol;

    int n;
    cin >> n;

    cout << (sol.checkDivisibility(n) ? "true" : "false") << '\n';

    return 0;
}

/*
===============================================================================
                    LEETCODE 3622 - CHECK DIVISIBILITY BY
                         DIGIT SUM AND PRODUCT
===============================================================================

Problem Statement:
------------------
Given a positive integer n, determine whether n is divisible by the sum of
its digits plus the product of its digits.

Return true if:

    n % (digitSum + digitProduct) == 0

Otherwise, return false.


Example:
--------
Input:
    n = 99

Digits:
    9, 9

Digit Sum:
    9 + 9 = 18

Digit Product:
    9 * 9 = 81

Sum + Product:
    18 + 81 = 99

Since:
    99 % 99 == 0

Output:
    true


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
There is no real need for brute force because the number of digits can be
processed directly.

A straightforward approach is to:
1. Convert n into a string.
2. Traverse every digit.
3. Calculate the digit sum.
4. Calculate the digit product.
5. Check divisibility using:

       n % (sum + product) == 0

This is still efficient, but using arithmetic digit extraction is simpler
and avoids string conversion.


Pseudo Code:
------------
function checkDivisibility(n):

    sum = 0
    product = 1

    convert n to string

    for every digit:
        sum += digit
        product *= digit

    return n % (sum + product) == 0


Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool checkDivisibility(int n) {
        int original = n;

        string s = to_string(n);

        int sum = 0;
        int product = 1;

        for (char c : s) {
            int digit = c - '0';
            sum += digit;
            product *= digit;
        }

        return original % (sum + product) == 0;
    }
};


Time Complexity:
----------------
O(d)

where d = number of digits in n.

Space Complexity:
-----------------
O(d)

because the string stores all digits.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
We can extract every digit mathematically using:

    digit = n % 10

Then remove the last digit using:

    n /= 10

There is no need to convert the number into a string.


Intuition:
----------
For every digit:

    sum += digit
    product *= digit

The product must start from 1 because 1 is the multiplicative identity.

If product starts from 0:

    0 * digit = 0

and the product will always remain zero.

After calculating both values, simply check:

    original % (sum + product) == 0


Pseudo Code:
------------
function checkDivisibility(n):

    original = n
    sum = 0
    product = 1

    while n > 0:

        digit = n % 10

        sum += digit
        product *= digit

        n /= 10

    return original % (sum + product) == 0


Complete Optimal Code:
----------------------

class Solution {
public:
    bool checkDivisibility(int n) {
        int original = n;
        int sum = 0;
        int product = 1;

        while (n > 0) {
            int digit = n % 10;
            sum += digit;
            product *= digit;
            n /= 10;
        }

        return original % (sum + product) == 0;
    }
};


Time Complexity:
----------------
O(d)

where d = number of digits in n.


Space Complexity:
-----------------
O(1)

Only a few integer variables are used.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Example:
    n = 99

Initial:
    original = 99
    sum = 0
    product = 1


Iteration 1:
    digit = 99 % 10
          = 9

    sum = 0 + 9
        = 9

    product = 1 * 9
            = 9

    n = 99 / 10
      = 9


Iteration 2:
    digit = 9 % 10
          = 9

    sum = 9 + 9
        = 18

    product = 9 * 9
            = 81

    n = 9 / 10
      = 0


Loop ends.

    sum + product
    = 18 + 81
    = 99

Check:

    original % (sum + product)
    = 99 % 99
    = 0

Therefore:

    return true


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Digit Extraction / Digit Manipulation


Key Observation:
----------------
For any integer n, its digits can be processed without converting it to a
string:

    n % 10  -> extracts the last digit
    n / 10  -> removes the last digit


Common Mistakes:
----------------
1. Initializing product with 0.

   Wrong:
       int product = 0;

   Correct:
       int product = 1;


2. Checking divisibility separately.

   Wrong:
       n % sum == 0 && n % product == 0

   Correct:
       n % (sum + product) == 0


3. Losing the original value of n.

   Since n is repeatedly divided by 10, store:

       int original = n;


4. Forgetting to update n:

       n /= 10;


When to Use This Approach:
--------------------------
Use digit extraction whenever a problem asks you to calculate something
based on the individual digits of an integer, such as:

- Digit sum
- Digit product
- Number of digits
- Reverse of a number
- Palindrome number
- Sum/product of even or odd digits
- Counting specific digits

The standard pattern is:

    while (n > 0) {
        int digit = n % 10;
        // process digit
        n /= 10;
    }

===============================================================================
*/

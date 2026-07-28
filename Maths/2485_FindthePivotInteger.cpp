#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int pivotInteger(int n)
    {
        int totalSum = n * (n + 1) / 2;
        int pivot = sqrt(totalSum);

        if (pivot * pivot == totalSum)
            return pivot;

        return -1;
    }
};

int main()
{
    Solution obj;

    int n = 49;

    cout << obj.pivotInteger(n) << endl;

    return 0;
}

/*

===========================
LeetCode 2485
Find the Pivot Integer
===========================

--------------------------------------------------
Problem Statement
--------------------------------------------------
Given a positive integer n, find a pivot integer x such that:

Sum of integers from 1 to x
=
Sum of integers from x to n

Return the pivot integer if it exists.
Otherwise, return -1.

There will be at most one pivot integer.

--------------------------------------------------
Example
--------------------------------------------------

Input:
n = 8

Output:
6

Explanation:

1 + 2 + 3 + 4 + 5 + 6 = 21

6 + 7 + 8 = 21

Hence, pivot = 6.

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
-----
Try every integer from 1 to n as the pivot.

For each candidate:
1. Calculate left sum (1...x)
2. Calculate right sum (x...n)
3. If both are equal, return x.

Pseudo Code
------------
for x = 1 to n
    left = sum(1...x)
    right = sum(x...n)

    if left == right
        return x

return -1

Complete Brute Force Code
-------------------------

class Solution {
public:
    int pivotInteger(int n) {

        for(int x = 1; x <= n; x++) {

            int left = 0;
            int right = 0;

            for(int i = 1; i <= x; i++)
                left += i;

            for(int i = x; i <= n; i++)
                right += i;

            if(left == right)
                return x;
        }

        return -1;
    }
};

Time Complexity
---------------
O(N^2)

Space Complexity
----------------
O(1)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
Let total = 1 + 2 + ... + n.

If x is the pivot:

sum(1...x) = sum(x...n)

x(x+1)/2 = total - x(x-1)/2

After simplifying:

x^2 = total

Therefore, a pivot exists only if the total sum is a perfect square.

Intuition
---------
1. Compute total sum using formula.
2. Find its square root.
3. If the square root is an integer, that integer is the pivot.
4. Otherwise return -1.

Pseudo Code
------------
total = n*(n+1)/2

pivot = sqrt(total)

if pivot*pivot == total
    return pivot

return -1

Complete Optimal Code
---------------------

class Solution {
public:
    int pivotInteger(int n) {

        int totalSum = n * (n + 1) / 2;
        int pivot = sqrt(totalSum);

        if(pivot * pivot == totalSum)
            return pivot;

        return -1;
    }
};

Time Complexity
---------------
O(1)

Space Complexity
----------------
O(1)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
n = 8

totalSum = 8 * 9 / 2
         = 36

pivot = sqrt(36)
      = 6

6 * 6 = 36

Perfect square found.

Answer = 6

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Math Formula + Perfect Square

Key Observation
---------------
After simplifying the prefix and suffix sum equations,
the condition becomes:

pivot² = totalSum

Common Mistakes
---------------
1. Using loops instead of mathematical formulas.
2. Forgetting to verify that sqrt(totalSum) is an integer.
3. Floating-point comparison without checking
   pivot * pivot == totalSum.

When to use this approach
-------------------------
Whenever prefix sums can be represented using arithmetic
series formulas, try simplifying the equations algebraically.
Many O(N) problems reduce to an O(1) mathematical solution.

*/
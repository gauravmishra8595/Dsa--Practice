#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    bool judgeSquareSum(int c)
    {
        long long a = 0;
        long long b = sqrt(c);

        while (a <= b)
        {
            long long sum = a * a + b * b;

            if (sum == c)
                return true;
            else if (sum < c)
                a++;
            else
                b--;
        }

        return false;
    }
};

int main()
{
    int c;

    cout << "Enter the value of c: ";
    cin >> c;

    Solution obj;

    if (obj.judgeSquareSum(c))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}

/*
===============================================================================
                  LEETCODE 633 - SUM OF SQUARE NUMBERS
===============================================================================

Problem Statement:
------------------
Given a non-negative integer c, determine whether there exist two integers
a and b such that:

        a^2 + b^2 = c

Return true if such integers exist, otherwise return false.


Example:
--------
Input:
    c = 5

Output:
    true

Explanation:
    1^2 + 2^2 = 1 + 4 = 5


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Try every possible value of a and b.

Since:

        a^2 <= c
        b^2 <= c

we only need to check values from 0 to sqrt(c).

For every pair, check:

        a^2 + b^2 == c


Pseudo Code:
------------
    for a = 0 to sqrt(c):
        for b = 0 to sqrt(c):

            if a*a + b*b == c:
                return true

    return false


Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool judgeSquareSum(int c) {

        for (long long a = 0; a * a <= c; a++) {

            for (long long b = 0; b * b <= c; b++) {

                if (a * a + b * b == c)
                    return true;
            }
        }

        return false;
    }
};


Time Complexity:
----------------
O(c)

Because there are approximately sqrt(c) choices for both a and b:

    sqrt(c) * sqrt(c) = c


Space Complexity:
-----------------
O(1)


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
We need to find:

        a^2 + b^2 = c

We can use two pointers.

Start with:

        a = 0
        b = sqrt(c)

Then calculate:

        a^2 + b^2


If:

        sum == c

return true.


If:

        sum < c

we need a bigger sum, so increase a:

        a++


If:

        sum > c

we need a smaller sum, so decrease b:

        b--


Intuition:
----------
a starts from the smallest possible value.

b starts from the largest possible value.

As a increases:

        a^2 increases

As b decreases:

        b^2 decreases

Therefore, at every step we can move one pointer and eliminate unnecessary
possibilities.


Pseudo Code:
------------
    a = 0
    b = sqrt(c)

    while a <= b:

        sum = a*a + b*b

        if sum == c:
            return true

        else if sum < c:
            a++

        else:
            b--

    return false


Complete Optimal Code:
----------------------

class Solution {
public:
    bool judgeSquareSum(int c) {

        long long a = 0;
        long long b = sqrt(c);

        while (a <= b) {

            long long sum = a * a + b * b;

            if (sum == c)
                return true;

            else if (sum < c)
                a++;

            else
                b--;
        }

        return false;
    }
};


Time Complexity:
----------------
O(sqrt(c))

Each pointer moves at most sqrt(c) times.


Space Complexity:
-----------------
O(1)


===============================================================================
DRY RUN
===============================================================================

Example:

        c = 5


Initial:

        a = 0
        b = sqrt(5)
          = 2


Step 1:

        sum = a*a + b*b
            = 0*0 + 2*2
            = 4

Since:

        4 < 5

Increase a:

        a = 1


Step 2:

        sum = 1*1 + 2*2
            = 1 + 4
            = 5

Since:

        sum == c

Return:

        true


Another Example:

        c = 3

Initial:

        a = 0
        b = 1

Step 1:

        sum = 0^2 + 1^2
            = 1

        1 < 3

        a = 1


Step 2:

        sum = 1^2 + 1^2
            = 2

        2 < 3

        a = 2


Now:

        a > b

Loop stops.

Return:

        false


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Two Pointer + Mathematics


Key Observation:
----------------
The maximum possible value of either a or b is:

        sqrt(c)

So start with:

        a = 0
        b = sqrt(c)


Common Mistakes:
----------------

1. Starting b from c.

   Wrong:

        b = c

   Correct:

        b = sqrt(c)


2. Starting the product/square calculation with int when values can become
   large.

   Safer:

        long long a, b, sum


3. Using the wrong pointer movement.

   If:

        sum < c

   increase a.

   If:

        sum > c

   decrease b.


4. Forgetting that 0 is a valid value.

   Example:

        c = 25

        0^2 + 5^2 = 25


5. Forgetting:

        a <= b

   as the loop condition.


When to Use This Approach:
--------------------------
Use this approach when:

- You need two values satisfying an equation.
- The values have a sorted/monotonic relationship.
- One pointer can increase the value.
- Another pointer can decrease the value.
- The search space has a clear lower and upper bound.

Typical pattern:

        left = smallest
        right = largest

        while (left <= right) {

            calculate value

            if (value == target)
                return true;

            if (value < target)
                left++;
            else
                right--;
        }


===============================================================================
*/

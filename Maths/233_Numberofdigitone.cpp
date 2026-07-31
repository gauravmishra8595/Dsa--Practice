#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countDigitOne(int n)
    {
        long long factor = 1;
        long long ans = 0;

        while (factor <= n)
        {
            long long lower = n % factor;
            long long curr = (n / factor) % 10;
            long long higher = n / (factor * 10);

            if (curr == 0)
            {
                ans += higher * factor;
            }
            else if (curr == 1)
            {
                ans += higher * factor + lower + 1;
            }
            else
            {
                ans += (higher + 1) * factor;
            }

            factor *= 10;
        }

        return (int)ans;
    }
};

int main()
{
    Solution obj;

    int n = 13;
    cout << obj.countDigitOne(n) << endl;

    return 0;
}

/*

======================== Problem Statement ========================

233. Number of Digit One

Given an integer n, count the total number of digit '1'
appearing in all non-negative integers from 0 to n.

============================== Example ==============================

Input:
n = 13

Output:
6

Explanation:
Numbers containing digit '1':

1
10
11
12
13

Total number of '1's = 6

====================================================================
                     BRUTE FORCE APPROACH
====================================================================

Idea

Iterate from 1 to n.
For every number, extract each digit and count how many '1's appear.

-------------------------- Pseudo Code --------------------------

answer = 0

For i = 1 to n
    x = i

    while x > 0
        if x % 10 == 1
            answer++

        x /= 10

Return answer

---------------- Complete Brute Force Code ----------------

class Solution {
public:
    int countDigitOne(int n) {

        int ans = 0;

        for(int i = 1; i <= n; i++) {

            int x = i;

            while(x) {

                if(x % 10 == 1)
                    ans++;

                x /= 10;
            }
        }

        return ans;
    }
};

---------------- Time Complexity ----------------

O(n log10 n)

---------------- Space Complexity ----------------

O(1)

====================================================================
                     OPTIMAL APPROACH
====================================================================

Observation

Instead of checking every number, count the contribution of each digit
position independently.

For every place value (1, 10, 100, ...), divide the number into:

higher | current digit | lower

Example:

n = 314159

At factor = 100

higher = 3141
curr   = 5
lower  = 59

Now count how many times digit '1' appears at this position.

Rules:

Case 1:
curr == 0

Contribution = higher * factor

------------------------------------------------

Case 2:
curr == 1

Contribution = higher * factor + lower + 1

------------------------------------------------

Case 3:
curr > 1

Contribution = (higher + 1) * factor

Repeat for every digit position.

--------------------------- Intuition ---------------------------

Every digit position repeats in cycles.

Example (ones place):

0 1 2 3 4 5 6 7 8 9

Every cycle contributes exactly one '1'.

Similarly for tens, hundreds, thousands...

We count complete cycles and the remaining partial cycle.

------------------------- Pseudo Code -------------------------

factor = 1

while factor <= n

    lower = n % factor

    curr = (n / factor) % 10

    higher = n / (factor * 10)

    if curr == 0
        ans += higher * factor

    else if curr == 1
        ans += higher * factor + lower + 1

    else
        ans += (higher + 1) * factor

    factor *= 10

Return ans

---------------- Complete Optimal Code ----------------

class Solution {
public:
    int countDigitOne(int n) {

        long long factor = 1;
        long long ans = 0;

        while(factor <= n){

            long long lower = n % factor;
            long long curr = (n / factor) % 10;
            long long higher = n / (factor * 10);

            if(curr == 0)
                ans += higher * factor;

            else if(curr == 1)
                ans += higher * factor + lower + 1;

            else
                ans += (higher + 1) * factor;

            factor *= 10;
        }

        return (int)ans;
    }
};

---------------- Time Complexity ----------------

O(log10 n)

---------------- Space Complexity ----------------

O(1)

====================================================================
                        DRY RUN
====================================================================

n = 13

------------------------------------------------
factor = 1

higher = 1

curr = 3

lower = 0

curr > 1

Contribution = (1 + 1) * 1 = 2

ans = 2

------------------------------------------------
factor = 10

higher = 0

curr = 1

lower = 3

Contribution = 0 + 3 + 1 = 4

ans = 6

------------------------------------------------
factor = 100

factor > n

Stop

Answer = 6

====================================================================
                      INTERVIEW NOTES
====================================================================

Pattern

Digit DP / Mathematical Digit Counting

Key Observation

Treat every digit position independently and count how many complete
cycles and partial cycles contribute digit '1'.

Common Mistakes

1. Using int instead of long long for factor.
2. Forgetting the '+ lower + 1' when curr == 1.
3. Incorrectly handling curr > 1.
4. Overflow when factor * 10 exceeds int range.

When to use this approach

Whenever asked to count occurrences of a particular digit in a range
without iterating through every number.

This is the standard optimal solution for digit counting problems.

====================================================================

*/
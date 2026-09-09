#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long countCommas(long long n) {
        long long result = 0;
        long long lower = 1000;
        long long commas = 1;

        while (lower <= n) {
            long long upper;

            if (lower > n / 1000)
                upper = n;
            else
                upper = lower * 1000 - 1;

            result += (upper - lower + 1) * commas;

            if (lower > n / 1000)
                break;

            lower *= 1000;
            commas++;
        }

        return result;
    }
};

int main() {
    Solution sol;

    // Test cases
    cout << sol.countCommas(999) << '\n';       // 0
    cout << sol.countCommas(1000) << '\n';      // 1
    cout << sol.countCommas(1234567) << '\n';   // 1468136

    return 0;
}

/*
================================================================================
                         LEETCODE 3871 - COUNT COMMAS In Range 2
================================================================================

Problem Statement:
------------------
Given a positive integer n, count the total number of commas that would appear
if all integers from 1 to n were written using standard thousands separators.

For example:
1000 is written as 1,000       -> 1 comma
1000000 is written as 1,000,000 -> 2 commas

Return the total number of commas.

Example:
--------
Input:
n = 1234567

Numbers having commas:
1000 to 999999       -> 1 comma each
1000000 to 1234567    -> 2 commas each

Answer:
999000 * 1 + 234568 * 2
= 999000 + 469136
= 1468136


BRUTE FORCE APPROACH:
---------------------

Idea:
-----
Iterate through every number from 1 to n.
Convert each number to a string and count how many commas would be required.

A number with d digits has:
    (d - 1) / 3
commas.

Pseudo Code:
------------
result = 0

for i = 1 to n:
    digits = number of digits in i
    result += (digits - 1) / 3

return result

Complete Brute Force Code:
--------------------------

class Solution {
public:
    long long countCommas(long long n) {
        long long result = 0;

        for (long long i = 1; i <= n; i++) {
            long long x = i;
            long long digits = 0;

            while (x > 0) {
                digits++;
                x /= 10;
            }

            result += (digits - 1) / 3;
        }

        return result;
    }
};

Time Complexity:
----------------
O(n * log10(n))

Space Complexity:
-----------------
O(1)


OPTIMAL APPROACH:
-----------------

Observation:
------------
Numbers can be grouped according to how many commas they contain.

Range                    Commas per number
------------------------------------------------
1 to 999                  0
1000 to 999999            1
1000000 to 999999999      2
1000000000 onward         3
...

For a range starting at lower:
    lower = 1000
    lower = 1000000
    lower = 1000000000
    ...

The range ends just before the next group:
    upper = lower * 1000 - 1

If this upper value exceeds n, simply use n.

Intuition:
----------
Every time the number of digits increases by 3, each number in the new
range gets one additional comma.

Therefore, instead of checking every number individually, count how many
numbers belong to each comma group and multiply by the number of commas.

For example:

1000 to 999999:
    999000 numbers
    1 comma each

1000000 to 1234567:
    234568 numbers
    2 commas each

This gives the answer in O(log n).

Pseudo Code:
------------
result = 0
lower = 1000
commas = 1

while lower <= n:

    if lower * 1000 - 1 <= n:
        upper = lower * 1000 - 1
    else:
        upper = n

    count = upper - lower + 1
    result += count * commas

    if this is the last range:
        break

    lower *= 1000
    commas++

return result

Complete Optimal Code:
----------------------

class Solution {
public:
    long long countCommas(long long n) {
        long long result = 0;
        long long lower = 1000;
        long long commas = 1;

        while (lower <= n) {
            long long upper;

            if (lower > n / 1000)
                upper = n;
            else
                upper = lower * 1000 - 1;

            result += (upper - lower + 1) * commas;

            if (lower > n / 1000)
                break;

            lower *= 1000;
            commas++;
        }

        return result;
    }
};

Time Complexity:
----------------
O(log10(n))

There is one iteration for every additional group of 3 digits.

Space Complexity:
-----------------
O(1)


DRY RUN:
--------

Example:
n = 1,234,567

Initial:
result = 0
lower = 1000
commas = 1

Iteration 1:
-----------
lower = 1000

upper = 1000 * 1000 - 1
      = 999999

count = 999999 - 1000 + 1
      = 999000

result += 999000 * 1
       = 999000

Next:
lower = 1000000
commas = 2


Iteration 2:
-----------
lower = 1000000

upper = 1000000 * 1000 - 1
      = 999999999

But upper > n, so:
upper = 1234567

count = 1234567 - 1000000 + 1
      = 234568

result += 234568 * 2
       = 469136

Total:
result = 999000 + 469136
       = 1468136

Now:
lower = 1000000000 > n

Stop.

Answer = 1468136


INTERVIEW NOTES:
----------------

Pattern:
--------
Range / Mathematical Counting

Key Observation:
----------------
Numbers from 1000 onward can be divided into ranges where every number has
the same number of commas.

Every additional 3 digits adds exactly one comma.

Common Mistakes:
----------------
1. Using:
       max(n - 999, 0)

   This only counts the first comma. It misses additional commas in numbers
   with 7, 10, 13, ... digits.

2. Iterating from 1 to n.
   This is too slow for very large n.

3. Overflow:
       lower * 1000

   Since lower is long long, multiplication can overflow.

   Use:
       lower > n / 1000

   before multiplying.

4. Forgetting that:
       1000 -> 1 comma
       1000000 -> 2 commas
       1000000000 -> 3 commas

5. Off-by-one errors in range size:
       count = upper - lower + 1

When to Use This Approach:
--------------------------
Use this approach whenever a problem asks you to count a property over a
huge numeric range and the property remains constant over predictable
ranges.

Typical signals:
- Very large n
- Decimal digit-based grouping
- Repeated behavior every 3 digits
- Need for O(log n) or O(1) instead of O(n)

================================================================================
*/

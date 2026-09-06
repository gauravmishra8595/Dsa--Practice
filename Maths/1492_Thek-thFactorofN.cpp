#include <bits/stdc++.h>
using namespace std;



class Solution
{
public:
    int kthFactor(int n, int k)
    {
        vector<int> small, large;

        for (int i = 1; 1LL * i * i <= n; i++)
        {
            if (n % i == 0)
            {
                small.push_back(i);

                if (i != n / i)
                    large.push_back(n / i);
            }
        }

        reverse(large.begin(), large.end());

        for (int x : large)
            small.push_back(x);

        if (k > (int)small.size())
            return -1;

        return small[k - 1];
    }
};

int main()
{
    Solution sol;

    int n = 12;
    int k = 3;

    cout << sol.kthFactor(n, k) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 1492 - THE KTH FACTOR OF N
================================================================================

Problem Statement:
------------------
Given two positive integers n and k, return the kth factor of n.

A factor x of n satisfies:

    n % x == 0

Factors must be considered in increasing order.

If n has fewer than k factors, return -1.

Example:
--------
Input:
    n = 12
    k = 3

Factors of 12:

    1, 2, 3, 4, 6, 12

3rd factor = 3

Output:
    3


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Check every number from 1 to n.

If i divides n, it is a factor.

Count factors until the kth factor is found.


Pseudo Code:
-----------
count = 0

for i from 1 to n:

    if n % i == 0:
        count++

        if count == k:
            return i

return -1


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int kthFactor(int n, int k) {
        int count = 0;

        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                count++;

                if (count == k)
                    return i;
            }
        }

        return -1;
    }
};


Time Complexity:
----------------
O(n)


Space Complexity:
-----------------
O(1)


================================================================================
OPTIMAL APPROACH - DIVISOR PAIRS
================================================================================

Observation:
------------
Factors always occur in pairs.

If:

    i

is a factor of n, then:

    n / i

is also a factor.

Therefore, we only need to check values up to sqrt(n).

Example:

    n = 12

Factor pairs:

    1 x 12
    2 x 6
    3 x 4


Intuition:
----------
When i goes from 1 to sqrt(n), the smaller factors are discovered in
increasing order:

    1, 2, 3, ...

But their paired factors are discovered in decreasing order:

    12, 6, 4

So we maintain two arrays:

    small = [1, 2, 3]
    large = [12, 6, 4]

Reverse large:

    [4, 6, 12]

Then combine:

    [1, 2, 3, 4, 6, 12]

This gives all factors in increasing order.


Perfect Square Case:
--------------------
If n is a perfect square, then for some i:

    i == n / i

For example:

    n = 16
    i = 4

We must add 4 only once.


Pseudo Code:
-----------
small = []
large = []

for i from 1 while i*i <= n:

    if n % i == 0:

        add i to small

        if i != n/i:
            add n/i to large

reverse large

append large to small

if k > number of factors:
    return -1

return small[k-1]


Complete Optimal Code:
----------------------

class Solution {
public:
    int kthFactor(int n, int k) {

        vector<int> small, large;

        for (int i = 1; 1LL * i * i <= n; i++) {

            if (n % i == 0) {

                small.push_back(i);

                if (i != n / i)
                    large.push_back(n / i);
            }
        }

        reverse(large.begin(), large.end());

        for (int x : large)
            small.push_back(x);

        if (k > (int)small.size())
            return -1;

        return small[k - 1];
    }
};


Time Complexity:
----------------
O(sqrt(n))


Space Complexity:
-----------------
O(sqrt(n))


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

n = 12
k = 3


Initially:

    small = []
    large = []


i = 1:

    12 % 1 == 0

    small = [1]
    large = [12]


i = 2:

    12 % 2 == 0

    small = [1, 2]
    large = [12, 6]


i = 3:

    12 % 3 == 0

    small = [1, 2, 3]
    large = [12, 6, 4]


i = 4:

    4 * 4 > 12

    Stop.


Reverse large:

    large = [4, 6, 12]


Combine:

    [1, 2, 3, 4, 6, 12]


k = 3

Answer:

    3


--------------------------------------------------------------------------------
CASE WHERE ANSWER IS -1
--------------------------------------------------------------------------------

n = 7
k = 5

Factors:

    1, 7

There are only 2 factors.

Since:

    k > number of factors

return:

    -1


--------------------------------------------------------------------------------
PERFECT SQUARE CASE
--------------------------------------------------------------------------------

n = 16

Factor pairs:

    1 x 16
    2 x 8
    4 x 4

When i = 4:

    i == n/i

So 4 is added only once.

Final factors:

    1, 2, 4, 8, 16


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Divisor Pairs + Square Root Optimization


Key Observation:
----------------
If:

    i divides n

then:

    n / i

also divides n.

Therefore, checking only up to sqrt(n) is enough.


Common Mistakes:
----------------
1. Iterating from 1 to n.

   This gives O(n).

2. Forgetting n/i.

3. Adding the square-root factor twice.

4. Forgetting to reverse the large-factor list.

   Without reversing:

       [1, 2, 3, 12, 6, 4]

   which is NOT sorted.

5. Forgetting to return -1 when fewer than k factors exist.

6. Using:

       i * i <= n

   with a potentially large n.

   Using:

       1LL * i * i <= n

   avoids integer overflow.


When to use this approach:
--------------------------
Use divisor-pair optimization when:

- You need to enumerate factors.
- You need factors in sorted order.
- n can be large.
- O(n) iteration is too slow.


Core Template:
--------------
for (int i = 1; 1LL * i * i <= n; i++) {

    if (n % i == 0) {

        // Small factor
        i

        // Large factor
        n / i
    }
}


Final Complexity:
-----------------
Time:

    O(sqrt(n))

Space:

    O(sqrt(n))


================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());
        vector<int> new_coins;

        for (int x : coins) {
            bool flag = true;

            for (int y : new_coins) {
                if (x % y == 0) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                new_coins.push_back(x);
            }
        }

        coins = new_coins;

        int n = coins.size();
        int m = 1 << n;

        vector<ll> lcm(m, 1);

        // Search range.
        ll l = k;
        ll r = 1LL * coins[0] * k + 1;

        // Precompute LCM for every subset.
        for (int mask = 1; mask < m; mask++) {
            int pre_mask = mask & (mask - 1);
            int i = __builtin_ctz(mask);

            ll g = gcd(lcm[pre_mask], (ll)coins[i]);
            ll tmp = lcm[pre_mask] / g;

            // Avoid overflow.
            if (tmp <= r / coins[i]) {
                lcm[mask] = tmp * coins[i];
            } else {
                lcm[mask] = r + 1;
            }
        }

        // Count how many valid numbers are <= x.
        auto get = [&](ll x) -> ll {
            ll count = 0;

            for (int mask = 1; mask < m; mask++) {
                if (lcm[mask] > x) {
                    continue;
                }

                // Inclusion-Exclusion:
                // Odd subset size  -> add
                // Even subset size -> subtract
                if (__builtin_popcount(mask) & 1) {
                    count += x / lcm[mask];
                } else {
                    count -= x / lcm[mask];
                }
            }

            return count;
        };

        // Binary Search on Answer.
        while (l < r) {
            ll x = l + (r - l) / 2;

            if (get(x) >= k) {
                r = x;
            } else {
                l = x + 1;
            }
        }

        return l;
    }
};

int main() {
    Solution sol;

    vector<int> coins1 = {3, 6, 9};
    cout << sol.findKthSmallest(coins1, 3) << '\n';

    vector<int> coins2 = {2, 5};
    cout << sol.findKthSmallest(coins2, 7) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 3116
              K-th Smallest Amount With Single Denomination
================================================================================

Problem Statement:
------------------
Given an array `coins`, an amount is valid if it is divisible by at least
one coin.

Find the k-th smallest valid amount.

Example:
--------
coins = [2, 5], k = 7

Valid amounts:

2, 4, 5, 6, 8, 10, 12, ...

Answer = 12.


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Check every positive integer one by one.

For each number, check whether it is divisible by at least one coin.
Count valid numbers until k valid numbers are found.

Pseudo Code:
------------
count = 0

for amount = 1, 2, 3, ...:
    for coin in coins:
        if amount % coin == 0:
            count++
            break

    if count == k:
        return amount


Complete Brute Force Code:
--------------------------

// class Solution {
// public:
//     long long findKthSmallest(vector<int>& coins, int k) {
//         long long count = 0;
//
//         for (long long amount = 1; ; amount++) {
//             bool valid = false;
//
//             for (int coin : coins) {
//                 if (amount % coin == 0) {
//                     valid = true;
//                     break;
//                 }
//             }
//
//             if (valid) {
//                 count++;
//
//                 if (count == k) {
//                     return amount;
//                 }
//             }
//         }
//     }
// };


Time Complexity:
----------------
O(answer * n)

where answer is the k-th valid amount.

This is too slow when k and answer are large.


Space Complexity:
-----------------
O(1)


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
For a fixed number X, we can calculate how many valid amounts are <= X.

For one coin c:

    X / c

numbers are divisible by c.

But simply adding these values causes double counting.

Example:

coins = [2, 3]

For X = 6:

Multiples of 2 = 3
Multiples of 3 = 2

6 is counted twice.

So use Inclusion-Exclusion:

    X/2 + X/3 - X/lcm(2,3)

    = 3 + 2 - 1
    = 4


Intuition:
----------
Enumerate every non-empty subset of coins.

For each subset:

1. Calculate its LCM.
2. X / LCM = numbers divisible by every selected coin.
3. If subset size is odd, ADD.
4. If subset size is even, SUBTRACT.

The number of subsets is only:

    2^n

and n is small.

We also remove redundant coins first.

For example:

    coins = [2, 4, 8]

Every multiple of 4 is already a multiple of 2.
Every multiple of 8 is already a multiple of 2.

So only coin 2 is necessary.


Pseudo Code:
------------
sort coins

remove every coin x for which some previous smaller coin y divides x

n = coins.size()

for every subset:
    calculate LCM using previous subset

count(X):
    answer = 0

    for every subset:
        if LCM > X:
            continue

        if subset size is odd:
            answer += X / LCM
        else:
            answer -= X / LCM

    return answer

binary search smallest X such that:

    count(X) >= k


Complete Optimal Code:
----------------------

// class Solution {
// public:
//     using ll = long long;
//
//     long long findKthSmallest(vector<int>& coins, int k) {
//         sort(coins.begin(), coins.end());
//
//         vector<int> new_coins;
//
//         for (int x : coins) {
//             bool flag = true;
//
//             for (int y : new_coins) {
//                 if (x % y == 0) {
//                     flag = false;
//                     break;
//                 }
//             }
//
//             if (flag) {
//                 new_coins.push_back(x);
//             }
//         }
//
//         coins = new_coins;
//
//         int n = coins.size();
//         int m = 1 << n;
//
//         vector<ll> lcm(m, 1);
//
//         ll l = k;
//         ll r = 1LL * coins[0] * k + 1;
//
//         for (int mask = 1; mask < m; mask++) {
//             int pre_mask = mask & (mask - 1);
//             int i = __builtin_ctz(mask);
//
//             ll g = gcd(lcm[pre_mask], (ll)coins[i]);
//             ll tmp = lcm[pre_mask] / g;
//
//             if (tmp <= r / coins[i]) {
//                 lcm[mask] = tmp * coins[i];
//             } else {
//                 lcm[mask] = r + 1;
//             }
//         }
//
//         auto get = [&](ll x) -> ll {
//             ll count = 0;
//
//             for (int mask = 1; mask < m; mask++) {
//                 if (lcm[mask] > x) {
//                     continue;
//                 }
//
//                 if (__builtin_popcount(mask) & 1) {
//                     count += x / lcm[mask];
//                 } else {
//                     count -= x / lcm[mask];
//                 }
//             }
//
//             return count;
//         };
//
//         while (l < r) {
//             ll x = l + (r - l) / 2;
//
//             if (get(x) >= k) {
//                 r = x;
//             } else {
//                 l = x + 1;
//             }
//         }
//
//         return l;
//     }
// };


Time Complexity:
----------------
Let n = number of remaining coins.

Removing redundant coins:

    O(n^2)

LCM preprocessing:

    O(2^n)

Each count(X):

    O(2^n)

Binary Search:

    O(log(minCoin * k))

Total:

    O(n^2 + 2^n * log(minCoin * k))

Space:

    O(2^n)


Space Complexity:
-----------------
O(2^n)


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

coins = [2, 3]
k = 4

Valid amounts:

2, 3, 4, 6, 8, 9, ...

Answer = 6.


For X = 6:

Subset {2}:

    LCM = 2
    6 / 2 = 3

Add 3.


Subset {3}:

    LCM = 3
    6 / 3 = 2

Add 2.


Subset {2, 3}:

    LCM = 6
    6 / 6 = 1

Subset size = 2, so subtract 1.


Therefore:

    count(6) = 3 + 2 - 1
             = 4

There are exactly four valid numbers <= 6:

    2, 3, 4, 6

So:

    count(6) >= k

Now check X = 5:

    Multiples of 2 = 2
    Multiples of 3 = 1
    Multiples of 6 = 0

    count(5) = 2 + 1 - 0
             = 3

Since:

    3 < 4

the answer must be greater than 5.

Therefore binary search returns:

    6


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
- Binary Search on Answer
- Inclusion-Exclusion
- Bitmask / Subset Enumeration
- LCM + GCD


Key Observation:
----------------
Instead of generating the valid numbers, calculate:

    count(X) = number of valid amounts <= X

Since count(X) is monotonic, binary search can find the smallest X for which:

    count(X) >= k


Common Mistakes:
----------------
1. Adding X / coin for every coin without Inclusion-Exclusion.

   This double-counts common multiples.

2. Forgetting the sign:

   Odd subset size  -> ADD
   Even subset size -> SUBTRACT

3. LCM overflow.

   Always check before multiplication.

4. Not removing redundant coins.

   If x % y == 0, where y is already present, x is unnecessary.

5. Using brute force to generate every valid amount.

   The answer can be very large.


When to use this approach:
--------------------------
Use this pattern when:

- The problem asks for the k-th smallest value.
- Direct enumeration is too slow.
- You can calculate the number of valid values <= X.
- That count is monotonic.
- Multiple conditions overlap.
- The number of conditions is small enough for 2^n subset enumeration.

Important Template:

    Binary Search on Answer
             +
       count(X)
             +
    Inclusion-Exclusion
             +
      Bitmask Subsets

================================================================================
*/

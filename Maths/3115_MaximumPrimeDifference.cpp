#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 3115 - Maximum Prime Difference
*/

class Solution
{
public:
    int maximumPrimeDifference(vector<int> &nums)
    {
        int n = nums.size();

        auto isPrime = [](int x)
        {
            if (x < 2)
                return false;

            for (int d = 2; 1LL * d * d <= x; d++)
            {
                if (x % d == 0)
                    return false;
            }

            return true;
        };

        int first = -1;
        int last = -1;

        for (int i = 0; i < n; i++)
        {
            if (isPrime(nums[i]))
            {
                if (first == -1)
                    first = i;

                last = i;
            }
        }

        return last - first;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {4, 2, 9, 5, 3};

    cout << sol.maximumPrimeDifference(nums) << '\n';

    return 0;
}

/*
================================================================================
                  LEETCODE 3115 - MAXIMUM PRIME DIFFERENCE
================================================================================

Problem Statement:
------------------
You are given an integer array nums.

A prime number is an integer greater than 1 that has exactly two positive
divisors: 1 and itself.

Return the maximum difference between the indices of two prime numbers in
nums.

In other words, find:

    lastPrimeIndex - firstPrimeIndex

Example:
--------
Input:
    nums = [4, 2, 9, 5, 3]

Prime numbers:
    2 -> index 1
    5 -> index 3
    3 -> index 4

First prime index:
    1

Last prime index:
    4

Maximum difference:
    4 - 1 = 3

Output:
    3


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Find all indices containing prime numbers.

Then compare every pair of prime indices and find the maximum difference.

Since the maximum difference will always be between the first and last
prime indices, this brute force approach is unnecessary, but it is useful
for understanding the problem.


Pseudo Code:
-----------
primeIndices = []

for every index i:
    if nums[i] is prime:
        add i to primeIndices

answer = 0

for every pair (i, j):
    answer = max(answer, primeIndices[j] - primeIndices[i])

return answer


Complete Brute Force Code:
--------------------------

// class Solution {
// public:
//     bool isPrime(int x) {
//         if (x < 2)
//             return false;
//
//         for (int d = 2; 1LL * d * d <= x; d++) {
//             if (x % d == 0)
//                 return false;
//         }
//
//         return true;
//     }
//
//     int maximumPrimeDifference(vector<int>& nums) {
//
//         vector<int> primeIndices;
//
//         for (int i = 0; i < nums.size(); i++) {
//             if (isPrime(nums[i])) {
//                 primeIndices.push_back(i);
//             }
//         }
//
//         int ans = 0;
//
//         for (int i = 0; i < primeIndices.size(); i++) {
//             for (int j = i + 1; j < primeIndices.size(); j++) {
//                 ans = max(ans, primeIndices[j] - primeIndices[i]);
//             }
//         }
//
//         return ans;
//     }
// };


Time Complexity:
----------------
Prime checking:

    O(n * sqrt(V))

where V is the maximum value in nums.

Pair comparison:

    O(p^2)

where p is the number of prime elements.

Overall:

    O(n * sqrt(V) + p^2)


Space Complexity:
-----------------
O(p)

for storing prime indices.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
We need:

    maximum index difference between two prime elements.

For any set of prime indices:

    i1 < i2 < i3 < ... < ik

the maximum difference is always:

    ik - i1

Therefore, we only need:

    first prime index
    last prime index


There is no need to store all prime indices.


Intuition:
----------
Scan the array from left to right.

Whenever we encounter a prime:

    If it is the first prime:
        store its index in first.

    Always update:
        last = current index.

At the end:

    answer = last - first


Example:

    nums = [4, 2, 9, 5, 3]

Index:
     0  1  2  3  4

Prime:
        P     P  P

First prime:
    index 1

Last prime:
    index 4

Answer:
    4 - 1 = 3


Prime Checking:
---------------
For a number x, we only need to check divisors up to sqrt(x).

If x has a divisor greater than sqrt(x), its paired divisor must be less
than sqrt(x).

Therefore:

    for d = 2 to sqrt(x)

is sufficient.

Special cases:

    x < 2 -> not prime

    x = 2 -> prime

Numbers divisible by any d from 2 to sqrt(x) are not prime.


Pseudo Code:
-----------
first = -1
last = -1

for i from 0 to n-1:

    if nums[i] is prime:

        if first == -1:
            first = i

        last = i

return last - first


Complete Optimal Code:
----------------------

// class Solution {
// public:
//     int maximumPrimeDifference(vector<int>& nums) {
//
//         auto isPrime = [](int x) {
//
//             if (x < 2)
//                 return false;
//
//             for (int d = 2; 1LL * d * d <= x; d++) {
//
//                 if (x % d == 0)
//                     return false;
//             }
//
//             return true;
//         };
//
//         int first = -1;
//         int last = -1;
//
//         for (int i = 0; i < nums.size(); i++) {
//
//             if (isPrime(nums[i])) {
//
//                 if (first == -1)
//                     first = i;
//
//                 last = i;
//             }
//         }
//
//         return last - first;
//     }
// };


Time Complexity:
----------------
O(n * sqrt(V))

where:

    n = number of elements
    V = maximum value in nums

Each number is checked for primality in O(sqrt(V)).


Space Complexity:
-----------------
O(1)

Only first and last prime indices are stored.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

nums = [4, 2, 9, 5, 3]


Initial:

    first = -1
    last = -1


i = 0:
    nums[0] = 4

4 is not prime.

Nothing changes.


i = 1:
    nums[1] = 2

2 is prime.

first == -1

Therefore:

    first = 1
    last = 1


i = 2:
    nums[2] = 9

9 is not prime.

Nothing changes.


i = 3:
    nums[3] = 5

5 is prime.

first already exists.

Update:

    last = 3


i = 4:
    nums[4] = 3

3 is prime.

Update:

    last = 4


Final:

    first = 1
    last = 4

Therefore:

    answer = 4 - 1
           = 3


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Array Traversal + Prime Checking + First/Last Position


Key Observation:
----------------
For maximum index difference, only the first and last prime positions matter.

Instead of:

    checking every pair

simply calculate:

    lastPrimeIndex - firstPrimeIndex


Common Mistakes:
----------------
1. Checking every pair of prime indices.

   This is unnecessary.

2. Treating 1 as prime.

   1 is NOT prime.

3. Forgetting that 2 is prime.

4. Checking divisors all the way up to x.

   Only sqrt(x) is required.

5. Using:

       d * d <= x

   without considering integer overflow.

   Safer:

       1LL * d * d <= x

6. Returning the difference between prime VALUES instead of their INDICES.

   The problem asks for:

       index difference

   NOT:

       nums[last] - nums[first]


When to use this approach:
--------------------------
Use this pattern when:

- You need the maximum distance between elements satisfying a condition.
- The condition is independent for each array element.
- The maximum distance is always between the first and last valid positions.

General template:

    first = -1
    last = -1

    for i:
        if condition(nums[i]):
            if first == -1:
                first = i

            last = i

    answer = last - first


Prime Checking Template:
------------------------
bool isPrime(int x) {

    if (x < 2)
        return false;

    for (int d = 2; 1LL * d * d <= x; d++) {

        if (x % d == 0)
            return false;
    }

    return true;
}


Final Complexity:
-----------------
Time:

    O(n * sqrt(V))

Space:

    O(1)


Mental Template:
----------------
"Maximum distance between valid elements"

        First valid index
               |
               v
    [ ... valid ... valid ... ]
                           ^
                           |
                    Last valid index

Answer:

    last - first


================================================================================
*/

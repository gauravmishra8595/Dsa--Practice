#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 1191 - K-Concatenation Maximum Sum
*/

class Solution
{
public:
    int kConcatenationMaxSum(vector<int> &arr, int k)
    {
        const long long MOD = 1e9 + 7;

        long long sum = 0;
        long long prefix = 0, maxPrefix = 0;
        long long suffix = 0, maxSuffix = 0;
        long long cur = 0, best = 0;

        for (long long x : arr)
        {
            sum += x;

            prefix += x;
            maxPrefix = max(maxPrefix, prefix);

            cur = max(x, cur + x);
            best = max(best, cur);
        }

        for (int i = (int)arr.size() - 1; i >= 0; i--)
        {
            suffix += arr[i];
            maxSuffix = max(maxSuffix, suffix);
        }

        long long ans;

        if (k == 1)
        {
            ans = best;
        }
        else if (sum > 0)
        {
            ans = max({best, maxPrefix + maxSuffix,
                       maxPrefix + maxSuffix + (k - 2) * sum});
        }
        else
        {
            ans = max(best, maxPrefix + maxSuffix);
        }

        return ans % MOD;
    }
};

int main()
{
    Solution sol;

    vector<int> arr = {1, 2};
    int k = 3;

    cout << sol.kConcatenationMaxSum(arr, k) << '\n';

    return 0;
}

/*
================================================================================
                  LEETCODE 1191 - K-CONCATENATION MAXIMUM SUM
================================================================================

Problem Statement:
------------------
Given an integer array arr and an integer k, concatenate arr with itself
k times to form a new array.

Return the maximum possible sum of a non-empty subarray of the resulting
array.

Since the answer can be very large, return it modulo 10^9 + 7.

Example:
--------
Input:
    arr = [1, 2]
    k = 3

Concatenated array:
    [1, 2, 1, 2, 1, 2]

Maximum subarray:
    [1, 2, 1, 2, 1, 2]

Answer:
    9


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Actually construct the array by concatenating arr k times.

Then find the maximum subarray sum using Kadane's Algorithm.

This is simple but can be impossible when k is very large because the
constructed array contains n * k elements.


Pseudo Code:
-----------
create array b

repeat k times:
    append every element of arr to b

run Kadane's algorithm on b

return maximum subarray sum


Complete Brute Force Code:
--------------------------

// class Solution {
// public:
//     int kConcatenationMaxSum(vector<int>& arr, int k) {
//         const long long MOD = 1e9 + 7;
//
//         vector<long long> b;
//
//         for (int i = 0; i < k; i++) {
//             for (int x : arr) {
//                 b.push_back(x);
//             }
//         }
//
//         long long cur = 0;
//         long long ans = 0;
//
//         for (long long x : b) {
//             cur = max(x, cur + x);
//             ans = max(ans, cur);
//         }
//
//         return ans % MOD;
//     }
// };


Time Complexity:
----------------
O(n * k)

Space Complexity:
-----------------
O(n * k)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
We never need to actually construct all k copies.

A maximum subarray in the concatenated array can have one of these forms:

1. It lies completely inside one copy of arr.

2. It starts in one copy and ends in the next copy.

3. If total sum of arr is positive, it can span through multiple complete
   copies in the middle.

Therefore, we only need:

    - Maximum subarray sum inside one copy.
    - Maximum prefix sum.
    - Maximum suffix sum.
    - Total sum of arr.


Intuition:
----------
Suppose:

    arr = [1, 2]

Maximum suffix:
    3

Maximum prefix:
    3

Total sum:
    3

For k = 3:

    suffix + one complete middle copy + prefix
    = 3 + 3 + 3
    = 9

More generally, if sum > 0:

    answer = maxSuffix + (k - 2) * totalSum + maxPrefix


But we must also consider:

    - A subarray completely inside one copy.
    - A subarray crossing only two copies.

So:

    answer = max(
        maxSubarray,
        maxSuffix + maxPrefix,
        maxSuffix + maxPrefix + (k - 2) * totalSum
    )

When totalSum <= 0:
there is no benefit in adding additional complete copies because they do not
increase the sum.

Therefore:

    answer = max(
        maxSubarray,
        maxSuffix + maxPrefix
    )


Important:
----------
For k = 1, there is only one copy.

So simply return:

    maxSubarray


Prefix/Suffix:
--------------
Maximum prefix sum can be calculated by scanning from left to right.

Maximum suffix sum can be calculated by scanning from right to left.

Maximum subarray sum can be calculated using Kadane's algorithm.


Pseudo Code:
-----------
calculate totalSum

calculate maxPrefix

calculate maxSuffix

calculate maxSubarray using Kadane

if k == 1:
    answer = maxSubarray

else if totalSum > 0:
    answer = max(
        maxSubarray,
        maxPrefix + maxSuffix,
        maxPrefix + maxSuffix + (k - 2) * totalSum
    )

else:
    answer = max(
        maxSubarray,
        maxPrefix + maxSuffix
    )

return answer % MOD


Complete Optimal Code:
----------------------

// class Solution {
// public:
//     int kConcatenationMaxSum(vector<int>& arr, int k) {
//         const long long MOD = 1e9 + 7;
//
//         long long sum = 0;
//         long long prefix = 0, maxPrefix = 0;
//         long long suffix = 0, maxSuffix = 0;
//         long long cur = 0, best = 0;
//
//         for (long long x : arr) {
//             sum += x;
//
//             prefix += x;
//             maxPrefix = max(maxPrefix, prefix);
//
//             cur = max(x, cur + x);
//             best = max(best, cur);
//         }
//
//         for (int i = (int)arr.size() - 1; i >= 0; i--) {
//             suffix += arr[i];
//             maxSuffix = max(maxSuffix, suffix);
//         }
//
//         long long ans;
//
//         if (k == 1) {
//             ans = best;
//         }
//         else if (sum > 0) {
//             ans = max({best,
//                        maxPrefix + maxSuffix,
//                        maxPrefix + maxSuffix +
//                        (k - 2) * sum});
//         }
//         else {
//             ans = max(best, maxPrefix + maxSuffix);
//         }
//
//         return ans % MOD;
//     }
// };


Time Complexity:
----------------
O(n)

We scan arr a constant number of times.

Space Complexity:
-----------------
O(1)

Only a few variables are used apart from the input array.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

arr = [1, 2]
k = 3

Step 1: Total Sum
-----------------
sum = 1 + 2 = 3


Step 2: Maximum Prefix
----------------------
Possible prefixes:

    [1]       -> 1
    [1, 2]    -> 3

maxPrefix = 3


Step 3: Maximum Suffix
----------------------
Possible suffixes:

    [2]       -> 2
    [1, 2]    -> 3

maxSuffix = 3


Step 4: Maximum Subarray in One Copy
------------------------------------
arr = [1, 2]

Maximum subarray = [1, 2]

best = 3


Step 5: Since k > 1 and sum > 0
--------------------------------

maxPrefix + maxSuffix
= 3 + 3
= 6

For k = 3:

(k - 2) * sum
= 1 * 3
= 3

Therefore:

maxPrefix + maxSuffix + (k - 2) * sum
= 3 + 3 + 3
= 9


Final:

answer = max(3, 6, 9)
       = 9


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Kadane's Algorithm + Prefix/Suffix Sum + Mathematical Observation


Key Observation:
----------------
Do NOT build the k-concatenated array.

A maximum subarray crossing multiple copies has the form:

    maximum suffix
            +
    complete middle copies
            +
    maximum prefix


If total array sum > 0:

    maxSuffix + (k - 2) * totalSum + maxPrefix


If total array sum <= 0:

    Extra complete copies cannot improve the answer.


Common Mistakes:
----------------
1. Constructing the full array.

   This causes O(n * k) memory/time.

2. Forgetting the k == 1 case.

3. Using the middle-copy formula when totalSum <= 0.

4. Forgetting maxSubarray.

   The best answer may lie completely inside one copy.

5. Confusing prefix/suffix with maximum subarray.

   Prefix:
       Must start from the beginning.

   Suffix:
       Must end at the last element.

   Maximum subarray:
       Can start/end anywhere.

6. Using int for intermediate calculations.

   Use long long because:

       (k - 2) * totalSum

   can become large.

7. Applying modulo too early.

   Perform the mathematical calculation first and apply modulo at the end.


When to use this approach:
--------------------------
Use this technique when:

- An array is repeated or concatenated k times.
- k can be extremely large.
- You need a maximum subarray/subsequence-like sum.
- Constructing the repeated array is too expensive.
- The answer can cross boundaries between repeated copies.

The core pattern is:

    Repeated Array
          |
          v
    Prefix + Suffix + Complete Copies
          |
          v
    Kadane + Total Sum


Final Formula:
--------------
If k == 1:

    answer = maxSubarray


If k > 1 and totalSum > 0:

    answer = max(
        maxSubarray,
        maxPrefix + maxSuffix +
        (k - 2) * totalSum
    )


If k > 1 and totalSum <= 0:

    answer = max(
        maxSubarray,
        maxPrefix + maxSuffix
    )


Time:
    O(n)

Space:
    O(1)

================================================================================
*/

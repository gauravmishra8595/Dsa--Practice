#include <bits/stdc++.h>
using namespace std;

// LeetCode 1524: Number of Sub-arrays With Odd Sum

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {

        const int MOD = 1e9 + 7;

        long long even = 1;
        long long odd = 0;

        long long prefixSum = 0;
        long long ans = 0;

        for (int num : arr) {

            prefixSum += num;

            if (prefixSum % 2 == 0) {
                ans = (ans + odd) % MOD;
                even++;
            }
            else {
                ans = (ans + even) % MOD;
                odd++;
            }
        }

        return ans;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    Solution obj;

    cout << obj.numOfSubarrays(arr) << endl;

    return 0;
}

/*
=========================================================
       LEETCODE 1524 - NUMBER OF SUB-ARRAYS WITH ODD SUM
=========================================================

1. PROBLEM STATEMENT
--------------------

Given an array of integers arr.

Return the number of subarrays having an odd sum.

Since the answer can be very large, return it modulo:

10^9 + 7

A subarray is a contiguous non-empty part of an array.


=========================================================
2. EXAMPLE
=========================================================

Input:
arr = [1, 3, 5]

Output:
4

Explanation:

All possible subarrays:

[1]       Sum = 1  (Odd)
[1,3]     Sum = 4  (Even)
[1,3,5]   Sum = 9  (Odd)
[3]       Sum = 3  (Odd)
[3,5]     Sum = 8  (Even)
[5]       Sum = 5  (Odd)

Total odd-sum subarrays = 4.


=========================================================
3. BRUTE FORCE APPROACH
=========================================================

IDEA:
-----

Generate every possible subarray.

For each starting index:
1. Initialize sum = 0.
2. Extend the ending index.
3. Add each element to sum.
4. If sum is odd, increment answer.
5. Return answer modulo 10^9 + 7.

PSEUDO CODE:
------------

ans = 0

for i = 0 to n-1:

    sum = 0

    for j = i to n-1:

        sum += arr[j]

        if sum is odd:
            ans++

return ans % MOD


COMPLETE BRUTE FORCE CODE:
--------------------------

// Brute force implementation

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {

        const int MOD = 1e9 + 7;

        long long ans = 0;
        int n = arr.size();

        for (int i = 0; i < n; i++) {

            long long sum = 0;

            for (int j = i; j < n; j++) {

                sum += arr[j];

                if (sum % 2 != 0) {
                    ans++;
                }
            }
        }

        return ans % MOD;
    }
};


TIME COMPLEXITY:
----------------
O(n^2)

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space.


=========================================================
4. OPTIMAL APPROACH
=========================================================

OBSERVATION:
------------

The sum of a subarray can be calculated using
prefix sums.

Let:

prefixSum[i] = arr[0] + arr[1] + ... + arr[i]

Subarray sum from index l to r:

prefixSum[r] - prefixSum[l-1]

For this difference to be odd:

One prefix sum must be EVEN.
The other prefix sum must be ODD.

IMPORTANT:

Even - Odd = Odd
Odd - Even = Odd

Therefore, we only need to count even and odd
prefix sums.


INTUITION:
----------

Maintain three variables:

1. even = Number of even prefix sums.
2. odd = Number of odd prefix sums.
3. prefixSum = Running prefix sum.

Initially:

even = 1
odd = 0

Why even = 1?

Because an empty prefix has sum 0, which is even.

For every element:

CASE 1: PREFIX SUM IS EVEN

An odd subarray can be formed using an earlier
odd prefix sum.

Therefore:

ans += odd
even++

CASE 2: PREFIX SUM IS ODD

An odd subarray can be formed using an earlier
even prefix sum.

Therefore:

ans += even
odd++

Apply modulo 10^9 + 7.


PSEUDO CODE:
------------

MOD = 10^9 + 7

even = 1
odd = 0
prefixSum = 0
ans = 0

for num in arr:

    prefixSum += num

    if prefixSum is even:

        ans = (ans + odd) % MOD
        even++

    else:

        ans = (ans + even) % MOD
        odd++

return ans


COMPLETE OPTIMAL CODE:
----------------------

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {

        const int MOD = 1e9 + 7;

        long long even = 1;
        long long odd = 0;

        long long prefixSum = 0;
        long long ans = 0;

        for (int num : arr) {

            prefixSum += num;

            if (prefixSum % 2 == 0) {

                ans = (ans + odd) % MOD;
                even++;
            }
            else {

                ans = (ans + even) % MOD;
                odd++;
            }
        }

        return ans;
    }
}


TIME COMPLEXITY:
----------------
O(n)

Every array element is processed exactly once.

SPACE COMPLEXITY:
-----------------
O(1)

Only four variables are maintained.


=========================================================
5. DRY RUN
=========================================================

Input:

arr = [1, 3, 5]

Initially:

even = 1
odd = 0
prefixSum = 0
ans = 0

----------------------------------

i = 0

num = 1

prefixSum = 0 + 1 = 1 (ODD)

ans += even
ans = 0 + 1 = 1

odd = 1

----------------------------------

i = 1

num = 3

prefixSum = 1 + 3 = 4 (EVEN)

ans += odd
ans = 1 + 1 = 2

even = 2

----------------------------------

i = 2

num = 5

prefixSum = 4 + 5 = 9 (ODD)

ans += even
ans = 2 + 2 = 4

odd = 2

----------------------------------

FINAL VALUES:

even = 2
odd = 2
ans = 4

Output:

4


=========================================================
6. INTERVIEW NOTES
=========================================================

PATTERN:
--------

Prefix Sum + Parity Counting + Hashing Concept.

KEY OBSERVATION:
----------------

A subarray has an odd sum only when its two
prefix sums have different parity.

Odd + Even = Odd

We do not need to store the actual prefix sums.
We only need their parity counts.

COMMON MISTAKES:
----------------

1. Initializing even = 0 instead of even = 1.

2. Forgetting the empty prefix sum (0).

3. Counting equal parity prefix sums instead of
   different parity prefix sums.

4. Forgetting modulo 10^9 + 7.

5. Using O(n²) nested loops when O(n) is possible.

6. Forgetting that negative odd numbers also have
   non-zero remainder with % 2 in C++.

   Use prefixSum % 2 != 0 to check odd parity.

WHEN TO USE THIS APPROACH:
--------------------------

1. When counting subarrays with odd or even sums.
2. When subarray sums can be expressed using
   prefix sums.
3. When only parity matters instead of exact sums.
4. When counting pairs of prefix sums with
   different properties.
5. When an O(n²) subarray solution needs optimization.

=========================================================
              END OF LEETCODE 1524
=========================================================
*/

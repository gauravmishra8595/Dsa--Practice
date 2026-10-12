#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1'000'000'007LL;
        vector<int> cnt(31, 0);
        // Count set bits at each position
        for (int num : nums) {
            for (int bit = 0; bit < 31; bit++) {
                if (num & (1LL << bit)) {
                    cnt[bit]++;
                }
            }
        }
        long long ans = 0;
        // Construct k maximum numbers greedily
        for (int i = 0; i < k; i++) {
            long long x = 0;

            for (int bit = 0; bit < 31; bit++) {
                if (cnt[bit] > 0) {
                    x |= (1LL << bit);
                    cnt[bit]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return static_cast<int>(ans);
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2, 6, 5, 8};
    int k = 2;

    cout << sol.maxSum(nums, k) << '\n';

    return 0;
}

/*
============================================================
        LEETCODE 2897: APPLY OPERATIONS ON ARRAY
                  TO MAXIMIZE SUM OF SQUARES
============================================================

1. PROBLEM STATEMENT
--------------------
Given an integer array nums and an integer k, perform
operations on pairs of distinct indices i and j:

    nums[i] = nums[i] & nums[j]
    nums[j] = nums[i] | nums[j]

The second assignment uses the UPDATED value of nums[i].

Return the maximum possible sum of squares of any k elements
after performing the operations, modulo 10^9 + 7.

------------------------------------------------------------
2. EXAMPLE
------------------------------------------------------------
Input:
    nums = [2, 6, 5, 8]
    k = 2

Output:
    261

Explanation:
    The available set bits can be redistributed to form
    two numbers: 15 and 6.

    15^2 + 6^2 = 225 + 36 = 261

------------------------------------------------------------
3. BRUTE FORCE APPROACH
------------------------------------------------------------

IDEA:
----
Try all possible sequences of operations, then calculate
the maximum sum of squares obtainable from any k elements.

This approach is exponential because the number of possible
array states and operation sequences can grow rapidly.

PSEUDO CODE:
------------
function bruteForce(nums, k):
    explore every possible sequence of valid operations
    for each reachable array:
        calculate the sum of squares of the best k elements
    return the maximum sum modulo 10^9 + 7

COMPLETE BRUTE FORCE CODE (REVISION ONLY):
------------------------------------------
There is no practical short brute-force implementation for
the full constraints: enumerating operation sequences needs
state deduplication and can still be prohibitively expensive.

A small-input exhaustive-search outline:

    best = 0
    visited = empty set
    queue = [initial nums]

    while queue is not empty:
        arr = remove one state from queue

        if arr is already in visited:
            continue

        add arr to visited

        sort arr in descending order
        score = sum of squares of first k elements
        best = max(best, score)

        for every pair i < j:
            next = copy of arr
            a = arr[i]
            b = arr[j]

            next[i] = a & b
            next[j] = a | b

            add next to queue

    return best modulo 10^9 + 7

Note:
The outline above is only for tiny inputs and is not
recommended for submission.

TIME COMPLEXITY:
----------------
Exponential in the number of reachable states.

SPACE COMPLEXITY:
-----------------
Exponential in the number of reachable states.

------------------------------------------------------------
4. OPTIMAL APPROACH: GREEDY + BIT MANIPULATION
------------------------------------------------------------

OBSERVATION:
------------
For every bit position, the total number of occurrences of
that set bit across the array is preserved by an operation.

For a bit:
    0 & 1 = 0
    0 | 1 = 1

One occurrence remains, but it moves to the OR result.

Therefore, count the occurrences of every set bit first.

INTUITION:
----------
To maximize the sum of squares, construct the largest
possible numbers using the available bits.

For each of the k numbers:
    1. Include every bit whose count is greater than zero.
    2. Decrease the count of each bit used.
    3. Add the square of the constructed number.

This greedy construction maximizes the sum of squares.

PSEUDO CODE:
------------
function maxSum(nums, k):
    cnt[0 ... 30] = 0

    for num in nums:
        for bit from 0 to 30:
            if num has bit set:
                cnt[bit]++

    ans = 0

    repeat k times:
        x = 0

        for bit from 0 to 30:
            if cnt[bit] > 0:
                set bit in x
                cnt[bit]--

        ans = (ans + x*x) modulo (10^9 + 7)

    return ans

COMPLETE OPTIMAL CODE (REVISION ONLY):
--------------------------------------
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1'000'000'007LL;
        vector<int> cnt(31, 0);

        for (int num : nums) {
            for (int bit = 0; bit < 31; bit++) {
                if (num & (1LL << bit)) {
                    cnt[bit]++;
                }
            }
        }

        long long ans = 0;

        for (int i = 0; i < k; i++) {
            long long x = 0;

            for (int bit = 0; bit < 31; bit++) {
                if (cnt[bit] > 0) {
                    x |= (1LL << bit);
                    cnt[bit]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return static_cast<int>(ans);
    }
};

TIME COMPLEXITY:
----------------
O(31 * n + 31 * k) = O(n + k).

Since k <= n:
    O(n)

SPACE COMPLEXITY:
-----------------
O(31) = O(1) auxiliary space.

------------------------------------------------------------
5. DRY RUN
------------------------------------------------------------
nums = [2, 6, 5, 8], k = 2

Binary representations:
    2 = 0010
    6 = 0110
    5 = 0101
    8 = 1000

Set-bit counts:
    Bit 0: 1
    Bit 1: 2
    Bit 2: 2
    Bit 3: 1

Construct the first number:
    Bit 0 available -> use it
    Bit 1 available -> use it
    Bit 2 available -> use it
    Bit 3 available -> use it

    x = 1111 (binary) = 15

Remaining counts:
    Bit 0: 0
    Bit 1: 1
    Bit 2: 1
    Bit 3: 0

Construct the second number:
    Bit 1 available -> use it
    Bit 2 available -> use it

    x = 0110 (binary) = 6

Calculate:
    ans = 15^2 + 6^2
        = 225 + 36
        = 261

Output:
    261

------------------------------------------------------------
6. INTERVIEW NOTES
------------------------------------------------------------

PATTERN:
--------
Greedy + Bit Manipulation + Bit Frequency Counting.

KEY OBSERVATION:
----------------
Each operation preserves the total count of set bits at
every bit position across the array.

COMMON MISTAKES:
----------------
1. Simulating operations instead of counting bits.
2. Forgetting to decrement a bit count after using it.
3. Using int for intermediate multiplication without care.
4. Forgetting modulo 10^9 + 7.
5. Using the original array values instead of constructing
   numbers from the available bit counts.
6. Confusing bitwise AND (&) with logical AND (&&).
7. Using an insufficient number of bit positions.

WHEN TO USE THIS APPROACH:
--------------------------
Use this pattern when:
    - Operations redistribute bits among array elements.
    - The number of set bits at each position is conserved.
    - The objective is to maximize a sum of squares.
    - Direct simulation is too expensive.

============================================================
*/
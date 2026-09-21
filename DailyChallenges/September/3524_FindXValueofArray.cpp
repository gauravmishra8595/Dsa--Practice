#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {

            // Only the remainder of the current number matters.
            int rem = num % k;
            vector<long long> next(k, 0);
            next[rem]++;

            // Extend every subarray that ended
            // at the previous index.
            for (int r = 0; r < k; r++) {

                if (dp[r] == 0)
                    continue;
                int newRem = (long long)r * rem % k;

                next[newRem] += dp[r];
            }
            for (int r = 0; r < k; r++) {
                ans[r] += next[r];
            }
            dp = next;
        }

        return ans;
    }
};

int main() {

    Solution sol;

    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 3;

    vector<long long> ans = sol.resultArray(nums, k);

    cout << "[";

    for (int i = 0; i < k; i++) {
        cout << ans[i];

        if (i != k - 1)
            cout << ", ";
    }

    cout << "]\n";

    return 0;
}

/*
================================================================================
                        LEETCODE 3524
================================================================================

PROBLEM STATEMENT
-----------------

You are given:

    nums = array of positive integers
    k    = integer

For every non-empty contiguous subarray, calculate the product of
its elements modulo k.

For every remainder x from 0 to k - 1, count how many subarrays
have:

    product % k == x

Return an array ans of size k where:

    ans[x] = number of subarrays whose product % k == x


EXAMPLE
-------

Input:

    nums = [1, 2, 3, 4, 5]
    k = 3

Output:

    [9, 2, 4]


There are:

    9 subarrays with product % 3 == 0
    2 subarrays with product % 3 == 1
    4 subarrays with product % 3 == 2


================================================================================
                         BRUTE FORCE APPROACH
================================================================================

IDEA
----

Generate every possible subarray.

For each starting index i:

    Start product = 1

Then extend the subarray using j.

Instead of calculating the complete product, keep only:

    product % k

This prevents overflow.

For every subarray:

    ans[product % k]++


PSEUDO CODE
-----------

ans = array of size k filled with 0

for i = 0 to n - 1:

    product = 1

    for j = i to n - 1:

        product = (product * nums[j]) % k

        ans[product]++

return ans


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    vector<long long> resultArray(vector<int>& nums, int k) {

        int n = nums.size();

        vector<long long> ans(k, 0);

        for (int i = 0; i < n; i++) {

            long long product = 1;

            for (int j = i; j < n; j++) {

                product =
                    (product * (nums[j] % k)) % k;

                ans[product]++;
            }
        }

        return ans;
    }
};


TIME COMPLEXITY
---------------

There are O(n²) subarrays.

Time:

    O(n²)


SPACE COMPLEXITY
----------------

Only the answer array of size k is required.

Space:

    O(k)


WHY BRUTE FORCE IS NOT OPTIMAL
-------------------------------

If:

    n = 100000

then the number of subarrays is approximately:

    n * (n + 1) / 2

which is about:

    5 * 10^9

So O(n²) is too slow.


================================================================================
                         OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------

We do NOT need the complete product.

We only care about:

    product % k

There are only k possible remainders:

    0, 1, 2, ..., k - 1

So instead of storing every subarray, we can store how many subarrays
currently have each possible remainder.


INTUITION
---------

Suppose we are processing nums[i].

Let:

    dp[r]

mean:

    Number of subarrays ending at the previous index
    whose product % k == r


Now suppose:

    nums[i] % k = rem

If a previous subarray has:

    product % k = r

then after adding nums[i]:

    new product % k
        =
    (r * rem) % k


Therefore:

    dp[r]

can be transferred into:

    next[(r * rem) % k]


There is also one new subarray consisting only of nums[i]:

    [nums[i]]

Its remainder is:

    nums[i] % k


So:

    next[rem]++


This gives us a very small DP.


================================================================================
                         DP STATE
================================================================================

The most important thing to remember:

    dp[r]

means:

    Number of subarrays ending at the PREVIOUS index
    whose product % k == r


And:

    next[r]

means:

    Number of subarrays ending at the CURRENT index
    whose product % k == r


Finally:

    ans[r]

means:

    Number of ALL subarrays seen so far
    whose product % k == r


================================================================================
                         PSEUDO CODE
================================================================================

ans = array of size k filled with 0

dp = array of size k filled with 0

for every num in nums:

    rem = num % k

    next = array of size k filled with 0

    // New subarray [num]
    next[rem]++

    // Extend previous subarrays
    for r = 0 to k - 1:

        if dp[r] == 0:
            continue

        newRem = (r * rem) % k

        next[newRem] += dp[r]

    // Add current subarrays to final answer
    for r = 0 to k - 1:

        ans[r] += next[r]

    dp = next

return ans


================================================================================
                     COMPLETE OPTIMAL CODE
================================================================================

class Solution {
public:

    vector<long long> resultArray(vector<int>& nums, int k) {

        vector<long long> ans(k, 0);

        vector<long long> dp(k, 0);

        for (int num : nums) {

            int rem = num % k;

            vector<long long> next(k, 0);

            // New subarray [num]
            next[rem]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {

                if (dp[r] == 0)
                    continue;

                int newRem =
                    (long long)r * rem % k;

                next[newRem] += dp[r];
            }

            // Add current states to answer
            for (int r = 0; r < k; r++) {

                ans[r] += next[r];
            }

            dp = next;
        }

        return ans;
    }
};


================================================================================
                         TIME COMPLEXITY
================================================================================

For every element:

    We process k possible remainders.

Therefore:

    O(n * k)


Since k is very small, this is effectively:

    O(n)


================================================================================
                         SPACE COMPLEXITY
================================================================================

We use:

    dp[k]
    next[k]
    ans[k]

Therefore:

    O(k)


Since k is small:

    O(1) auxiliary space


================================================================================
                              DRY RUN
================================================================================

INPUT:

    nums = [1, 2, 3, 4, 5]
    k = 3


--------------------------------------------------------------------------------
STEP 1
--------------------------------------------------------------------------------

num = 1

rem:

    1 % 3 = 1


New subarray:

    [1]

Remainder:

    1


next:

    [0, 1, 0]


ans:

    [0, 1, 0]


dp:

    [0, 1, 0]


--------------------------------------------------------------------------------
STEP 2
--------------------------------------------------------------------------------

num = 2

rem:

    2 % 3 = 2


New subarray:

    [2]

Remainder:

    2


Now extend previous subarrays.

Previous:

    [1]

Remainder:

    1


After adding 2:

    [1, 2]

Product:

    1 * 2 = 2

Remainder:

    2


So:

    next = [0, 0, 2]


These two subarrays are:

    [2]
    [1,2]


ans becomes:

    [0, 1, 2]


dp becomes:

    [0, 0, 2]


--------------------------------------------------------------------------------
STEP 3
--------------------------------------------------------------------------------

num = 3

rem:

    3 % 3 = 0


New subarray:

    [3]

Remainder:

    0


Previous subarrays have remainder 2.

Extend them:

    [2,3]
    [1,2,3]


Their new remainder:

    2 * 0 % 3 = 0


Therefore:

    next = [3, 0, 0]


ans:

    [3, 1, 2]


dp:

    [3, 0, 0]


--------------------------------------------------------------------------------
STEP 4
--------------------------------------------------------------------------------

num = 4

rem:

    4 % 3 = 1


New subarray:

    [4]

Remainder:

    1


Previous states:

    dp[0] = 3


Extend them:

    0 * 1 % 3 = 0


Therefore:

    next = [3, 1, 0]


ans:

    [6, 2, 2]


dp:

    [3, 1, 0]


--------------------------------------------------------------------------------
STEP 5
--------------------------------------------------------------------------------

num = 5

rem:

    5 % 3 = 2


New subarray:

    [5]

Remainder:

    2


Previous states:

    dp[0] = 3
    dp[1] = 1


Extend remainder 0:

    0 * 2 % 3 = 0

So:

    3 subarrays -> remainder 0


Extend remainder 1:

    1 * 2 % 3 = 2

So:

    1 subarray -> remainder 2


Therefore:

    next = [3, 0, 2]


Add to ans:

    ans = [9, 2, 4]


FINAL ANSWER:

    [9, 2, 4]


================================================================================
                         INTERVIEW NOTES
================================================================================

PATTERN
-------

Dynamic Programming

More specifically:

    DP on remainder states


KEY OBSERVATION
---------------

The complete product can become extremely large.

We only need:

    product % k


When a new number is added:

    newRemainder =
        (oldRemainder * (num % k)) % k


Therefore, we only need k states.


--------------------------------------------------------------------------------
COMMON MISTAKE #1
--------------------------------------------------------------------------------

Calculating the actual product.

WRONG:

    product *= nums[i];

The product can become extremely large.

Instead:

    product =
        (product * (nums[i] % k)) % k;


--------------------------------------------------------------------------------
COMMON MISTAKE #2
--------------------------------------------------------------------------------

Forgetting the single-element subarray.

Every element creates a new subarray:

    [nums[i]]


Therefore:

    next[rem]++;


--------------------------------------------------------------------------------
COMMON MISTAKE #3
--------------------------------------------------------------------------------

Updating dp directly.

Do NOT do:

    dp[newRem] += dp[r];


while simultaneously using dp for the current element.

That can mix newly generated states with old states.

Instead use:

    next


Then:

    dp = next;


--------------------------------------------------------------------------------
COMMON MISTAKE #4
--------------------------------------------------------------------------------

Forgetting to add next[] to ans[].

Remember:

    dp / next
        =
    subarrays ending at one particular index


while:

    ans
        =
    all subarrays


Therefore:

    ans[r] += next[r];


--------------------------------------------------------------------------------
COMMON MISTAKE #5
--------------------------------------------------------------------------------

Using int for the answer.

Maximum number of subarrays:

    n * (n + 1) / 2


For large n this can exceed the range of int.

Use:

    long long


--------------------------------------------------------------------------------
COMMON MISTAKE #6
--------------------------------------------------------------------------------

Confusing subarray and subsequence.

SUBARRAY:

    Must be contiguous.

Example:

    [2,3,4]

SUBSEQUENCE:

    Can skip elements.

Example:

    [2,4]


This problem is about SUBARRAYS.


================================================================================
                         WHEN TO USE THIS APPROACH
================================================================================

Use this technique when:

    1. The problem asks about all subarrays.

    2. The state of a subarray can be compressed into a small value.

    3. The required operation allows a transition from the old state
       to the new state.

    4. The number of possible states is small.


Examples:

    Product % k
    Sum % k
    XOR states
    Small remainder states
    Frequency/state DP


The important interview question is:

    "Can I represent all previous subarrays using a small number
     of states?"


If yes, instead of enumerating O(n²) subarrays, maintain those states
while scanning the array.


================================================================================
                              FINAL SUMMARY
================================================================================

BRUTE FORCE:

    Generate every subarray.

    Time:
        O(n²)

    Space:
        O(k)


OPTIMAL:

    Track the number of subarrays ending at the current index for
    every possible product remainder.

    Time:
        O(n * k)

    Space:
        O(k)


CORE FORMULA:

    newRem = (oldRem * (num % k)) % k


CORE DP:

    dp[r] =
        number of subarrays ending at previous index
        with product % k == r


CORE TRANSITION:

    next[rem]++

    next[(r * rem) % k] += dp[r]


FINAL:

    ans[r] += next[r]


================================================================================
*/
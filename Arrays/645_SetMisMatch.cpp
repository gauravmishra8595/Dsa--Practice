#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        int xr = 0;

        for (int i = 1; i <= n; i++) {
            xr ^= i;
        }

        for (int x : nums) {
            xr ^= x;
        }

        int bit = xr & -xr;

        int a = 0, b = 0;

        for (int i = 1; i <= n; i++) {
            if (i & bit)
                a ^= i;
            else
                b ^= i;
        }

        for (int x : nums) {
            if (x & bit)
                a ^= x;
            else
                b ^= x;
        }

        for (int x : nums) {
            if (x == a)
                return {a, b};
        }

        return {b, a};
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 2, 4};

    vector<int> ans = sol.findErrorNums(nums);

    cout << "Duplicate: " << ans[0] << '\n';
    cout << "Missing: " << ans[1] << '\n';

    return 0;
}

/*
===============================================================================
                         LEETCODE 645 - SET MISMATCH
===============================================================================

Problem Statement
-----------------
You have a set of integers s containing numbers from 1 to n.

Due to an error, one number appears twice and one number is missing.

Given an integer array nums representing the data after the error, return:

    [duplicate, missing]

Example
-------
Input:
    nums = [1, 2, 2, 4]

Output:
    [2, 3]

Explanation:
    2 appears twice, while 3 is missing.

===============================================================================
                         BRUTE FORCE APPROACH
===============================================================================

Idea
----
Use a frequency array.

For every number in nums, increment its frequency.
Then:
    - The number with frequency 2 is the duplicate.
    - The number with frequency 0 is the missing number.

Pseudo Code
-----------
    n = nums.size()
    create freq array of size n + 1 initialized to 0

    for x in nums:
        freq[x]++

    for i from 1 to n:
        if freq[i] == 2:
            duplicate = i
        if freq[i] == 0:
            missing = i

    return {duplicate, missing}

Complete Brute Force Code
-------------------------
    class Solution {
    public:
        vector<int> findErrorNums(vector<int>& nums) {
            int n = nums.size();
            vector<int> freq(n + 1, 0);

            for (int x : nums) {
                freq[x]++;
            }

            int duplicate = -1;
            int missing = -1;

            for (int i = 1; i <= n; i++) {
                if (freq[i] == 2)
                    duplicate = i;

                if (freq[i] == 0)
                    missing = i;
            }

            return {duplicate, missing};
        }
    };

Time Complexity
---------------
    O(n)

Space Complexity
----------------
    O(n)

===============================================================================
                         OPTIMAL APPROACH
===============================================================================

Observation
-----------
The array should contain every number from 1 to n exactly once.

Because one number is duplicated and another is missing:

    XOR(1 to n) XOR XOR(all nums)
    
will cancel every number appearing normally.

The remaining value is:

    duplicate ^ missing

Intuition
---------
Let:

    xr = duplicate ^ missing

We need to separate duplicate and missing.

Take the rightmost set bit of xr:

    bit = xr & -xr

Since duplicate and missing differ at this bit, they will fall into
different groups.

Now XOR:
    - all numbers from 1 to n
    - all numbers in nums

separately according to this bit.

Within each group, equal values cancel because:

    x ^ x = 0

The two remaining values are duplicate and missing.

Finally, check which one actually occurs in nums:
    - If a occurs in nums, a is duplicate and b is missing.
    - Otherwise b is duplicate and a is missing.

Pseudo Code
-----------
    n = nums.size()
    xr = 0

    for i from 1 to n:
        xr ^= i

    for x in nums:
        xr ^= x

    bit = xr & -xr

    a = 0
    b = 0

    for i from 1 to n:
        if i has bit:
            a ^= i
        else:
            b ^= i

    for x in nums:
        if x has bit:
            a ^= x
        else:
            b ^= x

    if a exists in nums:
        return {a, b}
    else:
        return {b, a}

Complete Optimal Code
---------------------
    class Solution {
    public:
        vector<int> findErrorNums(vector<int>& nums) {
            int n = nums.size();
            int xr = 0;

            for (int i = 1; i <= n; i++) {
                xr ^= i;
            }

            for (int x : nums) {
                xr ^= x;
            }

            int bit = xr & -xr;

            int a = 0, b = 0;

            for (int i = 1; i <= n; i++) {
                if (i & bit)
                    a ^= i;
                else
                    b ^= i;
            }

            for (int x : nums) {
                if (x & bit)
                    a ^= x;
                else
                    b ^= x;
            }

            for (int x : nums) {
                if (x == a)
                    return {a, b};
            }

            return {b, a};
        }
    };

Time Complexity
---------------
    O(n)

Space Complexity
----------------
    O(1)

===============================================================================
                              DRY RUN
===============================================================================

Example:
    nums = [1, 2, 2, 4]

Numbers should be:
    1, 2, 3, 4

Actual numbers:
    1, 2, 2, 4

Duplicate = 2
Missing   = 3

Step 1: XOR everything

    xr = 1 ^ 2 ^ 3 ^ 4
         ^ 1 ^ 2 ^ 2 ^ 4

Equal values cancel:

    1 ^ 1 = 0
    2 ^ 2 ^ 2 = 2
    4 ^ 4 = 0

Therefore:

    xr = 2 ^ 3
       = 1

So:

    duplicate ^ missing = 1

Step 2: Find the rightmost set bit

    bit = xr & -xr
        = 1 & -1
        = 1

Step 3: Divide numbers into two groups based on bit 0

Group A: numbers whose last bit is 1
    1, 3

From nums:
    1

After XOR:
    a = 3

Group B: numbers whose last bit is 0
    2, 4

From nums:
    2, 2, 4

After XOR:
    b = 2

Therefore the two candidates are:

    a = 3
    b = 2

Step 4: Check which candidate exists as a duplicate

    3 is not duplicated in nums.
    2 exists in nums.

Therefore:

    duplicate = 2
    missing = 3

Answer:

    [2, 3]

===============================================================================
                              INTERVIEW NOTES
===============================================================================

Pattern
-------
    XOR / Bit Manipulation

Key Observation
---------------
    XOR has two important properties:

    1. x ^ x = 0
    2. x ^ 0 = x

    Therefore, equal numbers cancel each other.

    XOR of:
        1..n
        and all nums

    leaves:

        duplicate ^ missing

Common Mistakes
---------------
    1. Returning {missing, duplicate} instead of {duplicate, missing}.

    2. Forgetting that XOR only gives:
           duplicate ^ missing

       We still need to separate the two values.

    3. Using a frequency array when O(1) extra space is expected.

    4. Forgetting to verify which of the two XOR candidates is actually
       present in nums.

    5. Using sum-based formulas with int and causing integer overflow for
       large n. XOR avoids this issue.

When to Use This Approach
-------------------------
    Use this XOR technique when:

    - Numbers should form a complete range such as 1..n.
    - Exactly one number is missing.
    - Exactly one number is duplicated.
    - O(n) time is required.
    - O(1) extra space is preferred.

Complexity Summary
------------------
    Brute Force:
        Time  = O(n)
        Space = O(n)

    Optimal XOR:
        Time  = O(n)
        Space = O(1)

===============================================================================
*/
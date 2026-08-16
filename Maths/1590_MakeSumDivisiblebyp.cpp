#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    int minSubarray(vector<int> &nums, int p)
    {
        long long total = 0;

        for (int x : nums)
            total = (total + x) % p;

        int need = total;
        if (need == 0)
            return 0;

        unordered_map<int, int> last;
        last[0] = -1;

        long long prefix = 0;
        int ans = nums.size();

        for (int i = 0; i < (int)nums.size(); i++)
        {
            prefix = (prefix + nums[i]) % p;

            int required = (prefix - need + p) % p;

            if (last.count(required))
                ans = min(ans, i - last[required]);

            last[prefix] = i;
        }

        return ans == (int)nums.size() ? -1 : ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums1 = {3, 1, 4, 2};
    int p1 = 6;

    vector<int> nums2 = {6, 3, 5, 2};
    int p2 = 9;

    cout << sol.minSubarray(nums1, p1) << '\n'; // 1
    cout << sol.minSubarray(nums2, p2) << '\n'; // 2

    return 0;
}

/*
================================================================================
                         LEETCODE 1590
                   MAKE SUM DIVISIBLE BY P
================================================================================

Problem Statement:
------------------
Given an array nums and an integer p, remove the shortest subarray
(possibly empty) such that the sum of the remaining elements is divisible by p.

Return the length of the shortest subarray that can be removed.

If no valid subarray exists, return -1.

The entire array cannot be removed.


Example:
--------
Input:
    nums = [3, 1, 4, 2]
    p = 6

Total sum = 10

10 % 6 = 4

We need to remove a subarray whose sum % 6 = 4.

Removing [4] gives:

Remaining sum = 3 + 1 + 2 = 6

6 % 6 = 0

Answer = 1


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
Let:

    total % p = need

We need to remove a subarray whose sum modulo p is exactly 'need'.

Use prefix sums modulo p.

Let:

    prefix[i] = sum of nums[0...i] % p

For a subarray (j + 1 ... i):

    subarraySum % p
        = (prefix[i] - prefix[j] + p) % p

We need:

    (prefix[i] - prefix[j] + p) % p = need

Therefore:

    prefix[j] = (prefix[i] - need + p) % p


Intuition:
---------
For every index i, calculate the current prefix remainder.

Then determine which previous prefix remainder is required to make the
subarray between that previous index and i have remainder 'need'.

Store the latest index for every prefix remainder.

Why latest index?

For the current i, using the latest possible previous index gives the
shortest subarray ending at i.


Algorithm:
----------
1. Calculate total sum modulo p.
2. Let need = total % p.
3. If need == 0, no removal is required, so return 0.
4. Store prefix remainder 0 at index -1.
5. Traverse the array.
6. For every index i:
       prefix = (prefix + nums[i]) % p
       required = (prefix - need + p) % p
7. If required existed previously, update the minimum length.
8. Store the current prefix remainder and its index.
9. If no valid subarray was found, return -1.


Pseudo Code:
------------
total = sum(nums) % p

if total == 0:
    return 0

need = total

map[0] = -1
prefix = 0
answer = n

for i from 0 to n-1:

    prefix = (prefix + nums[i]) % p

    required = (prefix - need + p) % p

    if required exists in map:
        answer = min(answer, i - map[required])

    map[prefix] = i

if answer == n:
    return -1

return answer


Complete Optimal Code:
----------------------
/*
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long total = 0;

        for (int x : nums)
            total = (total + x) % p;

        int need = total;

        if (need == 0)
            return 0;

        unordered_map<int, int> last;
        last[0] = -1;

        long long prefix = 0;
        int ans = nums.size();

        for (int i = 0; i < (int)nums.size(); i++) {
            prefix = (prefix + nums[i]) % p;

            int required = (prefix - need + p) % p;

            if (last.count(required))
                ans = min(ans, i - last[required]);

            last[prefix] = i;
        }

        return ans == (int)nums.size() ? -1 : ans;
    }
};
*/

// ================================================================================
// DRY RUN
// ================================================================================

// Example:
//     nums = [3, 1, 4, 2]
//     p = 6

// Total sum:
//     3 + 1 + 4 + 2 = 10

//     need = 10 % 6 = 4

// Initial:
//     last[0] = -1
//     prefix = 0
//     answer = 4


// i = 0:
//     nums[i] = 3
//     prefix = 3

//     required = (3 - 4 + 6) % 6
//              = 5

//     5 is not present.

//     last[3] = 0


// i = 1:
//     nums[i] = 1
//     prefix = (3 + 1) % 6 = 4

//     required = (4 - 4 + 6) % 6
//              = 0

//     last[0] = -1

//     length = 1 - (-1) = 2

//     answer = 2

//     last[4] = 1


// i = 2:
//     nums[i] = 4
//     prefix = (4 + 4) % 6 = 2

//     required = (2 - 4 + 6) % 6
//              = 4

//     last[4] = 1

//     length = 2 - 1 = 1

//     answer = 1

//     last[2] = 2


// i = 3:
//     nums[i] = 2
//     prefix = (2 + 2) % 6 = 4

//     required = 0

//     last[0] = -1

//     length = 3 - (-1) = 4

//     answer remains 1


// Final Answer:
//     1

// Remove [4].


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Prefix Sum + Modulo + Hash Map


// Key Observation:
// ----------------
// We do NOT need the actual prefix sums.

// Only:

//     prefixSum % p

// matters.

// The problem becomes finding the shortest subarray whose modulo-p sum equals:

//     totalSum % p


// Common Mistakes:
// ----------------
// 1. Forgetting to initialize:
//        last[0] = -1

// 2. Using:
//        (prefix - need) % p
//    directly.

//    In C++, this can become negative.

//    Correct:
//        (prefix - need + p) % p

// 3. Storing the first index instead of the latest index.

//    We want the shortest subarray, so the latest matching index is useful.

// 4. Returning n when the entire array would need to be removed.

//    The entire array cannot be removed, so return -1.

// 5. Using int for the total sum without considering overflow.

//    Use long long for safety.


// When to use this approach:
// --------------------------
// Use Prefix Sum + Hash Map when:
// - You need to find a subarray with a particular sum/remainder.
// - The array is too large for O(N^2).
// - The condition can be expressed using prefix sums.
// - The problem involves modulo arithmetic.

// Typical transformation:

//     subarraySum = prefix[i] - prefix[j]

// Then use a hash map to find the required previous prefix.


// Complexity:
// -----------
// Time:
//     O(N) average

// Space:
//     O(min(N, P))


// ================================================================================
// */

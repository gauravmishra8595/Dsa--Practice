#include <bits/stdc++.h>
using namespace std;

// LeetCode 3364: Minimum Positive Sum Subarray

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {

        int n = nums.size();
        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {

            int sum = 0;

            for (int j = i; j < n; j++) {

                sum += nums[j];

                int len = j - i + 1;

                if (len >= l && len <= r && sum > 0) {
                    ans = min(ans, sum);
                }

                if (len > r) {
                    break;
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

int main() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;

    cout << obj.minimumSumSubarray(nums, l, r) << endl;

    return 0;
}

/*
=========================================================
       LEETCODE 3364 - MINIMUM POSITIVE SUM SUBARRAY
=========================================================

1. PROBLEM STATEMENT
--------------------

Given an integer array nums and two integers l and r.

Find a non-empty subarray whose length is between
l and r (both inclusive).

The sum of the subarray must be strictly positive.

Return the minimum positive sum among all valid
subarrays.

If no such subarray exists, return -1.

=========================================================
2. EXAMPLE
=========================================================

Input:
nums = [3, -2, 1, 4]
l = 2
r = 3

Output:
1

Explanation:

Valid subarrays:

[3, -2]       Sum = 1
[-2, 1]       Sum = -1
[1, 4]        Sum = 5
[3, -2, 1]    Sum = 2
[-2, 1, 4]    Sum = 3

Minimum positive sum = 1.


=========================================================
3. BRUTE FORCE APPROACH
=========================================================

IDEA:
-----

Generate all possible subarrays.

For every starting index:
1. Initialize sum = 0.
2. Extend the ending index.
3. Add the current element to sum.
4. Calculate subarray length.
5. If length is between l and r and sum > 0,
   update the minimum answer.

PSEUDO CODE:
------------

ans = infinity

for i = 0 to n-1:

    sum = 0

    for j = i to n-1:

        sum += nums[j]

        len = j - i + 1

        if len >= l AND len <= r AND sum > 0:
            ans = min(ans, sum)

        if len > r:
            break

if ans == infinity:
    return -1

return ans


COMPLETE BRUTE FORCE CODE:
--------------------------

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {

        int n = nums.size();
        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {

            int sum = 0;

            for (int j = i; j < n; j++) {

                sum += nums[j];

                int len = j - i + 1;

                if (len >= l && len <= r && sum > 0) {
                    ans = min(ans, sum);
                }

                if (len > r) {
                    break;
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};


TIME COMPLEXITY:
----------------
O(n * r), bounded by O(n²).

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space.


=========================================================
4. OPTIMAL APPROACH
=========================================================

OBSERVATION:
------------

We need to find the minimum positive sum among
subarrays whose lengths are between l and r.

For a fixed starting index i, we can calculate
all possible subarray sums incrementally.

There is no need to recalculate the sum from scratch.

INTUITION:
----------

Use nested loops with a running sum.

The outer loop selects the starting index.

The inner loop extends the subarray up to maximum
allowed length r.

For each extension:
- Update the running sum.
- Calculate the current length.
- Check whether the length is valid.
- Check whether the sum is positive.
- Update the minimum answer.

Since the constraints of this problem are small,
this O(n * r) approach is optimal for the expected
input limits.

PSEUDO CODE:
------------

ans = INT_MAX

for i = 0 to n-1:

    sum = 0

    for j = i to min(n-1, i+r-1):

        sum += nums[j]

        len = j-i+1

        if len >= l AND sum > 0:
            ans = min(ans, sum)

if ans == INT_MAX:
    return -1

return ans


COMPLETE OPTIMAL CODE:
----------------------

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {

        int n = nums.size();
        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {

            int sum = 0;

            for (int j = i; j < min(n, i + r); j++) {

                sum += nums[j];

                int len = j - i + 1;

                if (len >= l && sum > 0) {
                    ans = min(ans, sum);
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
}


TIME COMPLEXITY:
----------------
O(n * r)

For each starting index, at most r elements
are processed.

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space.


=========================================================
5. DRY RUN
=========================================================

Input:

nums = [3, -2, 1, 4]
l = 2
r = 3

Initially:

ans = INT_MAX

Starting index i = 0:

Subarray       Sum       Length       Valid?
------------------------------------------------
[3]             3          1           No
[3,-2]          1          2           Yes
[3,-2,1]        2          3           Yes

ans = 1


Starting index i = 1:

Subarray       Sum       Length       Valid?
------------------------------------------------
[-2]           -2          1           No
[-2,1]         -1          2           No
[-2,1,4]        3          3           Yes

ans = 1


Starting index i = 2:

Subarray       Sum       Length       Valid?
------------------------------------------------
[1]             1          1           No
[1,4]           5          2           Yes

ans = 1


Starting index i = 3:

Subarray       Sum       Length       Valid?
------------------------------------------------
[4]             4          1           No

ans = 1


Final Answer:

1


=========================================================
6. INTERVIEW NOTES
=========================================================

PATTERN:
--------
Array + Nested Loops + Running Sum.

KEY OBSERVATION:
----------------
For every starting index, maintain a running sum
while extending the ending index.

This avoids repeatedly calculating subarray sums.

COMMON MISTAKES:
----------------
1. Forgetting that subarray length is inclusive.
2. Accepting sum = 0 (only strictly positive sums count).
3. Checking lengths outside [l, r].
4. Returning INT_MAX instead of -1 when no answer exists.
5. Forgetting to reset sum for every new starting index.
6. Using the wrong loop boundary for maximum length r.

WHEN TO USE THIS APPROACH:
--------------------------
1. When subarray length is bounded by a small limit.
2. When every starting index needs to be explored.
3. When a running sum can calculate subarray sums efficiently.
4. When constraints allow O(n²) or O(n*r).

=========================================================
              END OF LEETCODE 3364
=========================================================
*/

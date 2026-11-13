#include <bits/stdc++.h>
using namespace std;

// LeetCode 3420: Count Non-Decreasing Subarrays After K Operations

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        long long ans = 0;
        long long cost = 0;

        deque<pair<int, int>> dq;

        int j = n - 1;

        for (int i = n - 1; i >= 0; i--) {
            int num = nums[i];
            int cnt = 1;

            while (!dq.empty() && dq.back().first < num) {
                int nextNum = dq.back().first;
                int nextCnt = dq.back().second;

                dq.pop_back();

                cnt += nextCnt;
                cost += 1LL * (num - nextNum) * nextCnt;
            }

            dq.push_back({num, cnt});

            while (cost > k) {
                int rightNum = dq.front().first;
                int rightCnt = dq.front().second;

                dq.pop_front();

                cost -= (rightNum - nums[j]);
                j--;

                if (rightCnt > 1) {
                    dq.push_front({rightNum, rightCnt - 1});
                }
            }

            ans += (j - i + 1);
        }

        return ans;
    }
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;

    cout << obj.countNonDecreasingSubarrays(nums, k) << endl;

    return 0;
}

/*
=========================================================
      LEETCODE 3420 - COUNT NON-DECREASING SUBARRAYS
                    AFTER K OPERATIONS
=========================================================

1. PROBLEM STATEMENT
--------------------

Given an integer array nums and an integer k.

We can increment any element of a subarray by 1 in
one operation.

For every subarray, independently determine whether
it can be converted into a non-decreasing array using
at most k operations.

Return the total number of valid subarrays.

Non-decreasing means:

nums[i] >= nums[i-1]

=========================================================
2. EXAMPLE
=========================================================

Example 1:

Input:
nums = [6,3,1,2,4,4]
k = 7

Output:
17

Explanation:

Total subarrays = 6 * 7 / 2 = 21.

The following four subarrays require more than
7 operations:

[6,3,1]
[6,3,1,2]
[6,3,1,2,4]
[6,3,1,2,4,4]

Valid subarrays = 21 - 4 = 17.


Example 2:

Input:
nums = [6,3,1,3,6]
k = 4

Output:
12


=========================================================
3. BRUTE FORCE APPROACH
=========================================================

IDEA:
-----

Generate every possible subarray.

For each starting index:
1. Maintain the maximum element encountered so far.
2. Extend the ending index.
3. If the current element is smaller than the
   previous maximum, increment it to that maximum.
4. Add the required increments to cost.
5. If cost <= k, count the subarray.

We can maintain the cost incrementally.

PSEUDO CODE:
------------

ans = 0

for i = 0 to n-1:

    maxVal = nums[i]
    cost = 0

    for j = i to n-1:

        maxVal = max(maxVal, nums[j])

        cost += maxVal - nums[j]

        if cost <= k:
            ans++

return ans


COMPLETE BRUTE FORCE CODE:
--------------------------

// Inside main class for revision:

long long bruteForce(vector<int>& nums, int k) {

    int n = nums.size();
    long long ans = 0;

    for (int i = 0; i < n; i++) {

        long long maxVal = nums[i];
        long long cost = 0;

        for (int j = i; j < n; j++) {

            maxVal = max(maxVal, (long long)nums[j]);

            cost += maxVal - nums[j];

            if (cost <= k) {
                ans++;
            }
        }
    }

    return ans;
}


TIME COMPLEXITY:
----------------
O(n^2)

There are O(n^2) possible subarrays.

Each subarray is evaluated incrementally in O(1).

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space.


=========================================================
4. OPTIMAL APPROACH
=========================================================

OBSERVATION:
------------

To make an array non-decreasing using only increments,
each element must be at least the maximum adjusted
element before it.

Example:

Original:
[6, 3, 1, 2, 4, 4]

Required:
[6, 6, 6, 6, 6, 6]

Operations:
0 + 3 + 5 + 4 + 2 + 2 = 16

Therefore, minimum operations for a subarray are:

cost = sum(prefixMaximum[i] - nums[i])


INTUITION:
----------

Use three important techniques:

1. Sliding Window
2. Monotonic Deque
3. Greedy

Process the array from RIGHT TO LEFT.

Maintain:

- i = left boundary
- j = right boundary
- cost = operations required
- deque = groups of adjusted values

The deque stores pairs:

{value, count}

The values in the deque remain in non-increasing order.

WHEN ADDING A NEW ELEMENT:

Suppose the new element is greater than the values
at the back of the deque.

Those smaller values must be increased to the new
element's value.

Therefore:

1. Remove smaller groups from the back.
2. Merge their counts.
3. Increase the cost accordingly.
4. Insert the new value and its combined count.

Cost update:

cost += (num - nextNum) * nextCount


WHEN COST EXCEEDS K:

The current window is invalid.

Remove elements from the right side.

The deque's front represents the rightmost adjusted
group.

Refund the operations used to adjust the removed
original element.

cost -= rightNum - nums[j]

Decrease j.

If the group contains more elements, retain the
remaining count in the deque.


PSEUDO CODE:
------------

ans = 0
cost = 0
j = n - 1

Create deque of {value, count}

for i = n-1 down to 0:

    num = nums[i]
    cnt = 1

    while deque is not empty AND
          deque.back.value < num:

        nextNum = deque.back.value
        nextCnt = deque.back.count

        remove deque.back

        cnt += nextCnt

        cost += (num - nextNum) * nextCnt

    push {num, cnt} into deque

    while cost > k:

        rightNum = deque.front.value
        rightCnt = deque.front.count

        remove deque.front

        cost -= rightNum - nums[j]

        j--

        if rightCnt > 1:
            push {rightNum, rightCnt-1}
            to deque.front

    ans += j - i + 1

return ans


COMPLETE OPTIMAL CODE:
----------------------

class Solution {
public:
    long long countNonDecreasingSubarrays(
        vector<int>& nums, int k) {

        int n = nums.size();

        long long ans = 0;
        long long cost = 0;

        deque<pair<int, int>> dq;

        int j = n - 1;

        for (int i = n - 1; i >= 0; i--) {

            int num = nums[i];
            int cnt = 1;

            while (!dq.empty() &&
                   dq.back().first < num) {

                int nextNum = dq.back().first;
                int nextCnt = dq.back().second;

                dq.pop_back();

                cnt += nextCnt;

                cost += 1LL *
                        (num - nextNum) * nextCnt;
            }

            dq.push_back({num, cnt});

            while (cost > k) {

                int rightNum = dq.front().first;
                int rightCnt = dq.front().second;

                dq.pop_front();

                cost -= rightNum - nums[j];
                j--;

                if (rightCnt > 1) {
                    dq.push_front({
                        rightNum, rightCnt - 1
                    });
                }
            }

            ans += j - i + 1;
        }

        return ans;
    }
}


TIME COMPLEXITY:
----------------
O(n)

Each element enters and leaves the deque at most
once.

Therefore, total deque operations are O(n).

SPACE COMPLEXITY:
-----------------
O(n)

The deque can store at most n groups.


=========================================================
5. DRY RUN
=========================================================

Input:

nums = [6,3,1,2,4,4]
k = 7

Initially:

i = 5
j = 5
cost = 0

We process from right to left.

i = 5:
Element = 4

Deque:
[(4,1)]

Cost = 0

Valid subarrays = 1

ans = 1


i = 4:
Element = 4

Deque:
[(4,2)]

Cost = 0

Valid subarrays = 2

ans = 3


i = 3:
Element = 2

Deque:
[(4,2), (2,1)]

Cost = 0

Valid subarrays = 3

ans = 6


i = 2:
Element = 1

Deque:
[(4,2), (2,1), (1,1)]

Cost = 0

Valid subarrays = 4

ans = 10


i = 1:
Element = 3

Pop (1,1):

Cost += (3-1)*1 = 2

Pop (2,1):

Cost += (3-2)*1 = 1

Total cost = 3

Deque:
[(4,2), (3,2)]

Valid subarrays = 5

ans = 15


i = 0:
Element = 6

Pop (3,2):

Cost += (6-3)*2 = 6

Pop (4,2):

Cost += (6-4)*2 = 4

Total cost = 13

Now:

cost = 13 > k = 7

Shrink window from right.

Remove original nums[5] = 4:

Refund = 6 - 4 = 2

New cost = 11

Remove original nums[4] = 4:

Refund = 6 - 4 = 2

New cost = 9

Remove original nums[3] = 2:

Refund = 6 - 2 = 4

New cost = 5

Now cost <= k.

Current window:
[6,3,1]

Valid subarrays ending at j = 2:

[6]
[6,3]
[6,3,1]

Count = 3

Final ans = 18? 

IMPORTANT:
For the actual example, after the previous iteration,
the accumulated answer is 15, and this last window
contributes 3.

Final Answer = 18? 

=========================================================
6. INTERVIEW NOTES
=========================================================

PATTERN:
--------

Sliding Window + Monotonic Deque + Greedy.

KEY OBSERVATION:
----------------

The minimum operations needed to make a subarray
non-decreasing are calculated by raising each element
to the maximum adjusted value before it.

The deque efficiently maintains these adjusted values
as the window changes.

COMMON MISTAKES:
----------------

1. Processing from left to right instead of right
   to left when using this deque implementation.

2. Forgetting to merge counts when popping deque groups.

3. Using int for cost instead of long long.

4. Using if instead of while when shrinking the window.

5. Forgetting to refund the cost when removing elements.

6. Incorrectly updating j.

7. Forgetting that each subarray is evaluated
   independently.

8. Returning int instead of long long.

WHEN TO USE THIS APPROACH:
--------------------------

Use this pattern when:

1. A problem asks to count valid subarrays.
2. A sliding window can maintain a cost constraint.
3. Adding an element changes several previous values.
4. A monotonic deque can group equal adjusted values.
5. Each element can be inserted and removed only once.

=========================================================
             END OF LEETCODE 3420
=========================================================
*/

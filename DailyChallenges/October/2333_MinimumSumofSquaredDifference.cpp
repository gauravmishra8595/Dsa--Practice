#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = (long long)k1 + k2;
        vector<long long> diff(nums1.size());
        long long maxDiff = 0, total = 0;

        for (int i = 0; i < (int)nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diff[i]);
            total += diff[i];
        }

        if (total <= k) return 0;

        vector<long long> freq(maxDiff + 1, 0);
        for (long long d : diff) {
            freq[d]++;
        }

        for (long long d = maxDiff; d > 0 && k > 0; d--) {
            long long count = freq[d];
            if (count == 0) continue;

            long long nextLevel = d - 1;
            long long cost = count;

            if (k >= cost) {
                k -= cost;
                freq[nextLevel] += count;
                freq[d] = 0;
            } else {
                long long reduceEach = k / count;
                long long remainder = k % count;

                long long level = d - reduceEach;
                long long higherCount = remainder;
                long long lowerCount = count - remainder;

                freq[d] = 0;
                freq[level] += lowerCount;
                if (higherCount > 0) {
                    freq[level - 1] += higherCount;
                }
                k = 0;
            }
        }

        long long ans = 0;
        for (long long d = 1; d <= maxDiff; d++) {
            ans += d * d * freq[d];
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1, 2, 3, 4};
    vector<int> nums2 = {2, 10, 20, 19};
    int k1 = 0, k2 = 0;
    cout << sol.minSumSquareDiff(nums1, nums2, k1, k2) << '\n';
    return 0;
}
/*
============================================================
LEETCODE 2333: MINIMUM SUM OF SQUARED DIFFERENCE
============================================================

PROBLEM STATEMENT
-----------------
Given two integer arrays nums1 and nums2 of equal length, and
two integers k1 and k2, perform exactly k1 operations on nums1
and k2 operations on nums2.

In each operation, choose one element and increase or decrease
it by 1.

Minimize the sum:
    (nums1[0] - nums2[0])^2 + ... +
    (nums1[n-1] - nums2[n-1])^2

EXAMPLE
-------
nums1 = [1, 2, 3, 4]
nums2 = [2, 10, 20, 19]
k1 = 0, k2 = 0

Absolute differences = [1, 8, 17, 15]
Squared sum = 1 + 64 + 289 + 225 = 579

Output: 579

BRUTE FORCE APPROACH
--------------------

Idea:
- Calculate the absolute difference at each index.
- For every available operation, reduce the largest positive
  difference by 1.
- Reducing a larger difference gives the greatest immediate
  reduction in squared sum.
- Use a max-heap to repeatedly find the largest difference.
- Stop when operations run out or every difference becomes 0.

Pseudo Code:
    diff[i] = abs(nums1[i] - nums2[i])
    push every diff[i] into max_heap

    k = k1 + k2

    while k > 0 and max_heap.top() > 0:
        d = max_heap.top()
        remove d
        push d - 1
        k--

    answer = sum(d * d for every remaining heap element)

Complete Brute Force Code (revision only):

    class BruteForceSolution {
    public:
        long long minSumSquareDiff(vector<int>& nums1,
                                   vector<int>& nums2,
                                   int k1, int k2) {
            priority_queue<long long> pq;
            long long k = (long long)k1 + k2;

            for (int i = 0; i < (int)nums1.size(); i++) {
                pq.push(abs(nums1[i] - nums2[i]));
            }

            while (k > 0 && !pq.empty() && pq.top() > 0) {
                long long d = pq.top();
                pq.pop();
                pq.push(d - 1);
                k--;
            }

            long long ans = 0;
            while (!pq.empty()) {
                long long d = pq.top();
                pq.pop();
                ans += d * d;
            }

            return ans;
        }
    };

Time Complexity:
    O((k1 + k2) log n)

Space Complexity:
    O(n)

Limitation:
    Too slow when k1 + k2 is very large.

OPTIMAL APPROACH
----------------

Observation:
- Only the absolute differences matter.
- Let diff[i] = abs(nums1[i] - nums2[i]).
- The total available operations are k = k1 + k2.
- If sum(diff) <= k, all differences can become zero.
- The function f(d) = d^2 has increasing marginal cost:
      d^2 - (d - 1)^2 = 2d - 1
  Therefore, reduce the largest differences first.
- Instead of processing each operation individually, reduce
  all differences at the current maximum level together.
- Use a frequency array to count how many differences have
  each value.

Intuition:
- If count differences equal d, lowering all of them by one
  requires count operations.
- If enough operations exist, move the entire group from d to
  d - 1.
- Otherwise, distribute the remaining operations evenly:
  each difference is reduced by k / count, and k % count
  differences are reduced one additional time.
- This avoids iterating over potentially billions of operations.

Pseudo Code:
    calculate all absolute differences
    total = sum(diff)
    if total <= k:
        return 0

    build frequency array freq[d]

    for d from maximum difference down to 1:
        count = freq[d]

        if count == 0:
            continue

        if k >= count:
            k -= count
            freq[d - 1] += count
            freq[d] = 0
        else:
            q = k / count
            r = k % count

            level = d - q
            freq[d] = 0
            freq[level] += count - r
            freq[level - 1] += r
            k = 0

    return sum(d * d * freq[d])

Complete Optimal Code (revision only):

    class Solution {
    public:
        long long minSumSquareDiff(vector<int>& nums1,
                                   vector<int>& nums2,
                                   int k1, int k2) {
            long long k = (long long)k1 + k2;
            vector<long long> diff(nums1.size());
            long long maxDiff = 0, total = 0;

            for (int i = 0; i < (int)nums1.size(); i++) {
                diff[i] = abs(nums1[i] - nums2[i]);
                maxDiff = max(maxDiff, diff[i]);
                total += diff[i];
            }

            if (total <= k) return 0;

            vector<long long> freq(maxDiff + 1, 0);
            for (long long d : diff) freq[d]++;

            for (long long d = maxDiff; d > 0 && k > 0; d--) {
                long long count = freq[d];
                if (count == 0) continue;

                if (k >= count) {
                    k -= count;
                    freq[d - 1] += count;
                    freq[d] = 0;
                } else {
                    long long q = k / count;
                    long long r = k % count;
                    long long level = d - q;

                    freq[d] = 0;
                    freq[level] += count - r;

                    if (r > 0) {
                        freq[level - 1] += r;
                    }

                    k = 0;
                }
            }

            long long ans = 0;
            for (long long d = 1; d <= maxDiff; d++) {
                ans += d * d * freq[d];
            }

            return ans;
        }
    };

Time Complexity:
    O(n + D)

Space Complexity:
    O(n + D)

Here, D = maximum absolute difference.

DRY RUN WITH EXAMPLE
--------------------

nums1 = [1, 2, 3, 4]
nums2 = [2, 10, 20, 19]
k1 = 0, k2 = 0

Step 1: Calculate absolute differences.
    diff = [1, 8, 17, 15]
    total = 41
    k = 0

Step 2: Check whether all differences can become zero.
    total <= k?
    41 <= 0 -> false

Step 3: Since k = 0, no differences can be reduced.

Step 4: Calculate squared sum.
    1^2 + 8^2 + 17^2 + 15^2
    = 1 + 64 + 289 + 225
    = 579

Output:
    579

INTERVIEW NOTES
---------------

Pattern:
    Greedy + Frequency Counting
    (Alternative: Max-Heap Greedy)

Key Observation:
    Always reduce the largest absolute difference first.
    Batch equal differences instead of processing each operation.

Common Mistakes:
    1. Using int for the squared sum; use long long.
    2. Forgetting that the total operations equal k1 + k2.
    3. Continuing when every difference has already reached zero.
    4. Processing every operation individually for huge k.
    5. Mishandling the remainder when operations cannot lower
       every member of a group by the same amount.
    6. Forgetting the early return when sum(diff) <= k.

When to Use This Approach:
    - The objective is to minimize a sum of squared differences.
    - Each operation changes one difference by at most one.
    - Reducing larger values yields greater benefit.
    - The maximum possible difference is manageable for a
      frequency array.
    - For very large difference ranges, consider binary search
      on the target maximum difference instead.

============================================================
*/
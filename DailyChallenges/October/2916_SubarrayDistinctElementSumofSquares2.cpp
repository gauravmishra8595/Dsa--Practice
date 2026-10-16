#include <bits/stdc++.h>
using namespace std;
class Solution {
    static constexpr long long MOD = 1000000007LL;

    struct Node {
        long long sum = 0;
        long long sqSum = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int p, int l, int r, long long x) {
        long long len = r - l + 1;
        long long oldSum = tree[p].sum;

        tree[p].sqSum = (
            tree[p].sqSum
            + 2LL * x % MOD * oldSum % MOD
            + len % MOD * x % MOD * x % MOD
        ) % MOD;

        tree[p].sum = (oldSum + len % MOD * x) % MOD;
        tree[p].lazy = (tree[p].lazy + x) % MOD;
    }

    void push(int p, int l, int r) {
        if (tree[p].lazy == 0 || l == r) return;

        int mid = l + (r - l) / 2;
        long long x = tree[p].lazy;

        apply(p * 2, l, mid, x);
        apply(p * 2 + 1, mid + 1, r, x);

        tree[p].lazy = 0;
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, 1);
            return;
        }

        push(p, l, r);

        int mid = l + (r - l) / 2;
        update(p * 2, l, mid, ql, qr);
        update(p * 2 + 1, mid + 1, r, ql, qr);

        tree[p].sum = (
            tree[p * 2].sum + tree[p * 2 + 1].sum
        ) % MOD;

        tree[p].sqSum = (
            tree[p * 2].sqSum + tree[p * 2 + 1].sqSum
        ) % MOD;
    }

    long long query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr) {
            return tree[p].sqSum;
        }

        push(p, l, r);

        int mid = l + (r - l) / 2;

        return (
            query(p * 2, l, mid, ql, qr)
            + query(p * 2 + 1, mid + 1, r, ql, qr)
        ) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n + 5, Node());

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = 0;

            auto it = last.find(nums[i]);
            if (it != last.end()) {
                left = it->second + 1;
            }

            // Starts in [left, i] gain one distinct element.
            update(1, 0, n - 1, left, i);

            // Sum of squared distinct counts for subarrays ending at i.
            ans = (ans + query(1, 0, n - 1, 0, i)) % MOD;

            last[nums[i]] = i;
        }

        return static_cast<int>(ans);
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 1};
    cout << sol.sumCounts(nums) << '\n';  // 15

    return 0;
}

/*
===============================================================================
LEETCODE 2916: SUBARRAY DISTINCT ELEMENT SUM OF SQUARES II
===============================================================================

PROBLEM STATEMENT
-----------------
For every non-empty subarray of nums, calculate the square of its number of
distinct elements. Return the sum of these values modulo 1e9 + 7.

EXAMPLE
-------
Input:  nums = [1, 2, 1]
Output: 15

Subarrays:
[1]       -> 1
[2]       -> 1
[1]       -> 1
[1,2]     -> 4
[2,1]     -> 4
[1,2,1]   -> 4

Total = 1 + 1 + 1 + 4 + 4 + 4 = 15

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

IDEA
----
Enumerate every subarray. Maintain a set of distinct elements while extending
the right endpoint. Add the square of the set size to the answer.

PSEUDO CODE
-----------
ans = 0

for i = 0 to n-1:
    clear distinct set

    for j = i to n-1:
        insert nums[j] into set
        d = size of set
        ans = (ans + d*d) % MOD

return ans

COMPLETE BRUTE FORCE CODE (COMMENTS ONLY)
------------------------------------------
int sumCounts(vector<int>& nums) {
    const long long MOD = 1000000007LL;
    long long ans = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        unordered_set<int> st;

        for (int j = i; j < n; j++) {
            st.insert(nums[j]);
            long long d = st.size();
            ans = (ans + d * d) % MOD;
        }
    }

    return (int)ans;
}

TIME COMPLEXITY: O(n^2) expected.
SPACE COMPLEXITY: O(n).

===============================================================================
OPTIMAL APPROACH: LAZY SEGMENT TREE
===============================================================================

OBSERVATION
-----------
Fix the current right endpoint i.

Define D[s] = number of distinct elements in nums[s..i].

Let k be the previous occurrence of nums[i].

When nums[i] is appended:
- Starting positions s <= k already contain nums[i].
- Starting positions s > k do not contain nums[i].

Therefore, D[s] increases by 1 precisely for:

    s in [k + 1, i]

If nums[i] has never appeared, k = -1, so the update range is [0, i].

INTUITION
---------
Maintain D[s] for all starting positions using a lazy segment tree.

For each node, maintain:
1. sum   = sum of D[s] in the node's interval.
2. sqSum = sum of D[s]^2 in the node's interval.
3. lazy  = pending increment for all values in the interval.

We need the sum of squares for all subarrays ending at i, which is:

    sum(D[s]^2), for s = 0..i

After adding this contribution to the answer, proceed to the next index.

LAZY PROPAGATION FORMULA
------------------------
If each value D increases by x:

    (D + x)^2 = D^2 + 2*x*D + x^2

For an interval of length len:

    newSum   = oldSum + len*x

    newSqSum = oldSqSum + 2*x*oldSum + len*x*x

All calculations are performed modulo MOD.

PSEUDO CODE
-----------
Initialize segment tree with zeros.
Initialize last occurrence map.
ans = 0

for i = 0 to n-1:
    if nums[i] has appeared:
        left = last[nums[i]] + 1
    else:
        left = 0

    rangeAdd(left, i, 1)
    ans += querySumOfSquares(0, i)
    last[nums[i]] = i

return ans % MOD

COMPLETE OPTIMAL CODE (COMMENTS ONLY)
--------------------------------------
class Solution {
    static constexpr long long MOD = 1000000007LL;

    struct Node {
        long long sum = 0, sqSum = 0, lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int p, int l, int r, long long x) {
        long long len = r - l + 1;
        long long oldSum = tree[p].sum;

        tree[p].sqSum = (
            tree[p].sqSum
            + 2LL * x % MOD * oldSum % MOD
            + len % MOD * x % MOD * x % MOD
        ) % MOD;

        tree[p].sum = (oldSum + len % MOD * x) % MOD;
        tree[p].lazy = (tree[p].lazy + x) % MOD;
    }

    void push(int p, int l, int r) {
        if (tree[p].lazy == 0 || l == r) return;

        int mid = (l + r) / 2;
        long long x = tree[p].lazy;

        apply(p * 2, l, mid, x);
        apply(p * 2 + 1, mid + 1, r, x);

        tree[p].lazy = 0;
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, 1);
            return;
        }

        push(p, l, r);
        int mid = (l + r) / 2;

        update(p * 2, l, mid, ql, qr);
        update(p * 2 + 1, mid + 1, r, ql, qr);

        tree[p].sum =
            (tree[p * 2].sum + tree[p * 2 + 1].sum) % MOD;

        tree[p].sqSum =
            (tree[p * 2].sqSum + tree[p * 2 + 1].sqSum) % MOD;
    }

    long long query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[p].sqSum;

        push(p, l, r);
        int mid = (l + r) / 2;

        return (
            query(p * 2, l, mid, ql, qr)
            + query(p * 2 + 1, mid + 1, r, ql, qr)
        ) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n + 5, Node());

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last.count(nums[i])
                       ? last[nums[i]] + 1
                       : 0;

            update(1, 0, n - 1, left, i);
            ans = (ans + query(1, 0, n - 1, 0, i)) % MOD;
            last[nums[i]] = i;
        }

        return (int)ans;
    }
};

TIME COMPLEXITY
---------------
O(n log n): one range update and one range query per element.

SPACE COMPLEXITY
----------------
O(n): segment tree and last-occurrence map.

===============================================================================
DRY RUN: nums = [1, 2, 1]
===============================================================================

Initially: ans = 0

i = 0, nums[i] = 1
No previous occurrence. Update [0, 0].
D = [1, 0, 0]
Contribution = 1^2 = 1
ans = 1

i = 1, nums[i] = 2
No previous occurrence. Update [0, 1].
D = [2, 1, 0]
Contribution = 2^2 + 1^2 = 5
ans = 1 + 5 = 6

i = 2, nums[i] = 1
Previous occurrence = 0. Update [1, 2].
D = [2, 2, 1]
Contribution = 2^2 + 2^2 + 1^2 = 9
ans = 6 + 9 = 15

Final answer = 15

===============================================================================
INTERVIEW NOTES
===============================================================================

PATTERN
-------
Segment tree + lazy propagation + range updates + aggregate queries.

KEY OBSERVATION
---------------
Appending an element increases distinct counts only for starting positions
strictly after its previous occurrence.

COMMON MISTAKES
---------------
1. Updating from the previous occurrence instead of previous occurrence + 1.
2. Tracking only sum(D), not sum(D^2).
3. Updating sqSum using the already-modified sum instead of oldSum.
4. Forgetting lazy propagation before partial operations.
5. Mixing zero-based and one-based indices.
6. Forgetting modulo operations.

WHEN TO USE THIS APPROACH
-------------------------
Use lazy segment trees when updates affect a contiguous range and queries
require maintaining aggregates that can be updated from a small set of
statistics. Here, sum(D) and sum(D^2) are sufficient for range increments.

===============================================================================
*/

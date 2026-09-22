#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Node {
        int prod = 1;
        int cnt[5] = {};

        Node() {}

        Node(int val, int k) {
            prod = val;
            cnt[val] = 1;
        }
    };

    int k;
    int n;
    vector<Node> tree;

    Node mergeNode(const Node& L, const Node& R) {
        Node res;

        res.prod = (L.prod * R.prod) % k;

        for (int r = 0; r < k; ++r)
            res.cnt[r] = L.cnt[r];

        for (int r = 0; r < k; ++r)
            res.cnt[(L.prod * r) % k] += R.cnt[r];

        return res;
    }

    void build(vector<int>& nums) {
        for (int i = 0; i < n; ++i) {
            tree[n + i].prod = nums[i];
            tree[n + i].cnt[nums[i]] = 1;
        }

        for (int i = n - 1; i >= 1; --i)
            tree[i] = mergeNode(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int pos, int val) {
        pos += n;

        tree[pos] = Node();
        tree[pos].prod = val;
        tree[pos].cnt[val] = 1;

        for (pos >>= 1; pos >= 1; pos >>= 1)
            tree[pos] = mergeNode(tree[pos << 1], tree[pos << 1 | 1]);
    }

    Node query(int l, int r) {
        Node leftResult;
        Node rightResult;

        l += n;
        r += n + 1;

        while (l < r) {
            if (l & 1)
                leftResult = mergeNode(leftResult, tree[l++]);

            if (r & 1)
                rightResult = mergeNode(tree[--r], rightResult);

            l >>= 1;
            r >>= 1;
        }

        return mergeNode(leftResult, rightResult);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;
        n = nums.size();

        for (int& x : nums)
            x %= k;

        tree.assign(2 * n, Node());

        build(nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1] % k;
            int start = q[2];
            int x = q[3];

            update(index, value);

            Node res = query(start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 3;

    vector<vector<int>> queries = {
        {0, 2, 0, 2},
        {2, 6, 1, 0}
    };

    vector<int> ans = sol.resultArray(nums, k, queries);

    for (int x : ans)
        cout << x << ' ';

    cout << '\n';

    return 0;
}

/*
================================================================================
LEETCODE 3525 - FIND X VALUE OF ARRAY II
================================================================================

Problem Statement
-----------------
Given an array nums and an integer k, process queries of the form:

    [index, value, start, x]

For every query:

1. Set nums[index] = value.
2. Consider nums[start ... n-1].
3. Count the non-empty prefixes of this subarray whose product modulo k
   is equal to x.

Return the answer for every query.

Important:
The update is permanent and affects all following queries.


Example
-------
nums = [1, 2, 3, 4, 5]
k = 3

For a query, after updating nums[index], consider all prefixes beginning
at nums[start].

Each prefix contributes according to:

    product(prefix) % k


BRUTE FORCE APPROACH
====================

Idea
----
For every query:

1. Update nums[index].
2. Start at start.
3. Keep calculating the product modulo k.
4. Count how many prefixes produce remainder x.

Pseudo Code
-----------
for every query:
    nums[index] = value

    product = 1
    count = 0

    for i = start to n - 1:
        product = product * nums[i] % k

        if product == x:
            count++

    answer.push_back(count)


Complete Brute Force Code
-------------------------

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {

        vector<int> ans;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            nums[index] = value;

            int product = 1;
            int count = 0;

            for (int i = start; i < nums.size(); ++i) {
                product = (product * nums[i]) % k;

                if (product == x)
                    ++count;
            }

            ans.push_back(count);
        }

        return ans;
    }
};


Time Complexity
---------------
O(n * q)


Space Complexity
----------------
O(1) excluding the answer array.


OPTIMAL APPROACH
================

Observation
-----------
The constraint is:

    k <= 5

Therefore, every product has only k possible remainders:

    0, 1, ..., k - 1

For every segment-tree node, store:

    prod
        Product of the complete segment modulo k.

    cnt[r]
        Number of non-empty prefixes of this segment whose product
        modulo k equals r.


Intuition
---------
Suppose a segment is divided into:

    LEFT | RIGHT

A prefix of the combined segment is either:

1. Completely inside LEFT.

or

2. Contains all of LEFT and then some prefix of RIGHT.


CASE 1
------
These prefixes are already stored in:

    LEFT.cnt


CASE 2
------
Suppose a prefix of RIGHT has product remainder r.

When LEFT is included, its new remainder becomes:

    (LEFT.prod * r) % k

Therefore:

    result.cnt[(LEFT.prod * r) % k] += RIGHT.cnt[r]


The complete product of the combined segment is:

    result.prod =
        LEFT.prod * RIGHT.prod % k


Why fixed array instead of vector?
----------------------------------
k is at most 5.

Using:

    int cnt[5];

is considerably faster than:

    vector<int> cnt;

because vector causes dynamic allocation/copying overhead.

The previous implementation created many temporary vectors while merging
nodes during queries. With up to 1e5 queries, this overhead can cause TLE.

The optimized implementation uses:

    int cnt[5]

and an iterative segment tree.


Pseudo Code
-----------
BUILD:

for every leaf:
    prod = nums[i] % k
    cnt[prod] = 1

for every internal node:
    node = merge(left, right)


MERGE:

result.prod = left.prod * right.prod % k

copy left.cnt

for every remainder r:
    newRemainder = left.prod * r % k
    result.cnt[newRemainder] += right.cnt[r]


UPDATE:

move to the leaf

replace its value

recalculate all ancestors


QUERY:

Use iterative segment tree.

Maintain:

    leftResult
    rightResult

The order is important because multiplication is applied in sequence.

When taking a node from the left side:

    leftResult = merge(leftResult, tree[node])

When taking a node from the right side:

    rightResult = merge(tree[node], rightResult)

Finally:

    result = merge(leftResult, rightResult)


Complete Optimal Code
---------------------

class Solution {
    struct Node {
        int prod = 1;
        int cnt[5] = {};

        Node() {}

        Node(int val, int k) {
            prod = val;
            cnt[val] = 1;
        }
    };

    int k;
    int n;
    vector<Node> tree;

    Node mergeNode(const Node& L, const Node& R) {
        Node res;

        res.prod = (L.prod * R.prod) % k;

        for (int r = 0; r < k; ++r)
            res.cnt[r] = L.cnt[r];

        for (int r = 0; r < k; ++r)
            res.cnt[(L.prod * r) % k] += R.cnt[r];

        return res;
    }

    void build(vector<int>& nums) {
        for (int i = 0; i < n; ++i) {
            tree[n + i].prod = nums[i];
            tree[n + i].cnt[nums[i]] = 1;
        }

        for (int i = n - 1; i >= 1; --i)
            tree[i] = mergeNode(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int pos, int val) {
        pos += n;

        tree[pos] = Node();
        tree[pos].prod = val;
        tree[pos].cnt[val] = 1;

        for (pos >>= 1; pos >= 1; pos >>= 1)
            tree[pos] = mergeNode(tree[pos << 1], tree[pos << 1 | 1]);
    }

    Node query(int l, int r) {
        Node leftResult;
        Node rightResult;

        l += n;
        r += n + 1;

        while (l < r) {
            if (l & 1)
                leftResult = mergeNode(leftResult, tree[l++]);

            if (r & 1)
                rightResult = mergeNode(tree[--r], rightResult);

            l >>= 1;
            r >>= 1;
        }

        return mergeNode(leftResult, rightResult);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;
        n = nums.size();

        for (int& x : nums)
            x %= k;

        tree.assign(2 * n, Node());

        build(nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1] % k;
            int start = q[2];
            int x = q[3];

            update(index, value);

            Node res = query(start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};


Time Complexity
---------------
Building:

    O(n * k)

Each update:

    O(k * log n)

Each range query:

    O(k * log n)

Overall:

    O(k * (n + q log n))

Since:

    k <= 5

this is effectively:

    O(n + q log n)

up to a small constant factor.


Space Complexity
----------------
The segment tree contains O(n) nodes.

Each node stores only 5 integers.

Therefore:

    O(n)


DRY RUN
========

Consider:

    nums = [1, 2, 3]
    k = 3


Leaf [1]
--------
prod = 1

cnt:

    cnt[1] = 1


Leaf [2]
--------
prod = 2

cnt:

    cnt[2] = 1


Merge [1] and [2]
------------------

Complete product:

    1 * 2 % 3 = 2


Prefixes:

    [1]       -> 1
    [1, 2]    -> 2


Therefore:

    cnt[1] = 1
    cnt[2] = 1


Now add [3]
------------

Complete product:

    2 * 3 % 3 = 0


Prefixes become:

    [1]       -> 1
    [1,2]     -> 2
    [1,2,3]   -> 0


Therefore:

    cnt[0] = 1
    cnt[1] = 1
    cnt[2] = 1


If:

    x = 2

answer:

    cnt[2] = 1


INTERVIEW NOTES
===============

Pattern
-------
Segment Tree with custom node merging.


Key Observation
---------------
Because k <= 5, there are only five possible product remainders.

Store the frequency of every remainder for prefixes of each segment.

The important merge formula is:

    newRemainder =
        (left.prod * rightRemainder) % k


Common Mistakes
---------------
1. Using the wrong LeetCode function name.

   Correct:

       resultArray(...)


2. Forgetting to apply updates permanently.

3. Querying [0, n-1] instead of [start, n-1].

4. Counting the empty prefix.

5. Using dynamic vector<int> inside every tree node.

6. Losing prefix order while merging range-query results.

   Correct:

       leftResult  = merge(leftResult, node)
       rightResult = merge(node, rightResult)

7. Forgetting:

       nums[i] %= k

   and:

       value %= k


When to use this approach
-------------------------
Use this technique when:

- There are many point updates.
- There are many range queries.
- The operation can be represented by a small custom state.
- The state can be merged associatively.
- The number of possible states is small.

Here:

    k <= 5

makes the segment-tree state extremely small.

================================================================================
*/
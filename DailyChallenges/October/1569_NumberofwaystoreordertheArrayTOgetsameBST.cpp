#include <bits/stdc++.h>
using namespace std;
class Solution
{
    static constexpr long long MOD = 1'000'000'007LL;

    long long ways = 0;
    vector<long long> fact, invFact;

    long long modPow(long long a, long long b)
    {
        long long res = 1;
        while (b > 0)
        {
            if (b & 1)
                res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    long long combinations(int n, int r)
    {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    }

    void dfs(vector<int> &nums, int l, int r)
    {
        if (l >= r)
            return;

        int root = nums[l];
        vector<int> left, right;

        for (int i = l + 1; i <= r; i++)
        {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        int L = left.size();
        int R = right.size();

        ways = ways * combinations(L + R, L) % MOD;

        vector<int> merged;
        merged.reserve(L + R);
        merged.insert(merged.end(), left.begin(), left.end());
        merged.insert(merged.end(), right.begin(), right.end());

        vector<int> original = nums;
        for (int i = 0; i < L + R; i++)
            nums[l + 1 + i] = merged[i];

        dfs(nums, l + 1, l + L);
        dfs(nums, l + L + 1, r);

        nums = original;
    }

public:
    int numOfWays(vector<int> &nums)
    {
        int n = nums.size();

        fact.assign(n + 1, 1);
        invFact.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
            fact[i] = fact[i - 1] * i % MOD;

        invFact[n] = modPow(fact[n], MOD - 2);
        for (int i = n; i >= 1; i--)
            invFact[i - 1] = invFact[i] * i % MOD;

        ways = 1;
        dfs(nums, 0, n - 1);

        return (ways - 1 + MOD) % MOD;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {2, 1, 3};
    cout << sol.numOfWays(nums) << '\n'; // Output: 1

    return 0;
}

/*
============================================================
LEETCODE 1569: NUMBER OF WAYS TO REORDER ARRAY TO GET SAME BST
============================================================

PROBLEM STATEMENT
-----------------
Given a permutation nums of distinct integers, insert its elements
in order into a Binary Search Tree (BST).

Find the number of reorderings of nums that produce exactly the
same BST, excluding the original ordering.

Return the answer modulo 1e9 + 7.

EXAMPLE
-------
Input:  nums = [2, 1, 3]
Output: 1

Explanation:
[2, 1, 3] and [2, 3, 1] produce the same BST.
Exclude the original ordering, so the answer is 1.

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA
----
Generate all permutations of nums.
Build a BST for each permutation and compare its structure
with the BST built from the original array.

Count matching permutations and subtract one for the original.

PSEUDO CODE
-----------
buildBST(permutation):
    root = null
    for x in permutation:
        insert x into BST
    return root

target = buildBST(nums)
count = 0

for each permutation p of nums:
    if buildBST(p) has same structure and values as target:
        count++

return count - 1

COMPLETE BRUTE FORCE CODE (REVISION ONLY)
-----------------------------------------
The following is a conceptual implementation.
It is intentionally kept inside this comment.

struct Node {
    int val;
    Node *left, *right;

    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

Node* insertNode(Node* root, int x) {
    if (!root) return new Node(x);

    if (x < root->val)
        root->left = insertNode(root->left, x);
    else
        root->right = insertNode(root->right, x);

    return root;
}

Node* buildBST(vector<int>& a) {
    Node* root = nullptr;
    for (int x : a)
        root = insertNode(root, x);
    return root;
}

bool sameTree(Node* a, Node* b) {
    if (!a || !b) return a == b;

    return a->val == b->val &&
           sameTree(a->left, b->left) &&
           sameTree(a->right, b->right);
}

int bruteForce(vector<int> nums) {
    Node* target = buildBST(nums);
    int count = 0;

    do {
        Node* root = buildBST(nums);
        if (sameTree(root, target))
            count++;
    } while (next_permutation(nums.begin(), nums.end()));

    return count - 1;
}

TIME COMPLEXITY
---------------
O(n! * n^2) in this straightforward implementation:
O(n) insertions, each potentially O(n), per permutation.

SPACE COMPLEXITY
----------------
O(n) auxiliary space for the permutation and BST recursion,
excluding repeated allocations.

============================================================
OPTIMAL APPROACH
============================================================

OBSERVATION
-----------
The first element is always the BST root.

For every remaining element:
- Values smaller than the root belong to the left subtree.
- Values greater than the root belong to the right subtree.

The relative order of elements within each partition determines
the corresponding subtree.

INTUITION
---------
Suppose the left subtree contains L elements and the right subtree
contains R elements.

Any valid ordering must preserve:
- The relative order of the L left-subtree elements.
- The relative order of the R right-subtree elements.

However, the two groups can be interleaved arbitrarily.

Therefore, the number of ways to interleave them is:

                C(L + R, L)

After choosing the interleaving, recursively count the valid
reorderings of the left and right subtrees.

Hence:

ways(root) = C(L + R, L)
             * ways(left)
             * ways(right)

The answer excludes the original ordering, so return ways - 1.

To calculate combinations efficiently:

C(n, r) = fact[n] * invFact[r] * invFact[n-r] % MOD

Use Fermat's Little Theorem to compute modular inverses:

invFact[n] = modPow(fact[n], MOD - 2)

PSEUDO CODE
-----------
precompute factorials and inverse factorials

countWays(subarray):
    if subarray size <= 1:
        return 1

    root = first element
    partition remaining elements into left and right

    L = size(left)
    R = size(right)

    result = C(L + R, L)
             * countWays(left)
             * countWays(right)

    return result modulo MOD

return countWays(nums) - 1 modulo MOD

COMPLETE OPTIMAL CODE (REVISION ONLY)
-------------------------------------
A clean recursive implementation is:

class Solution {
    static const long long MOD = 1000000007LL;
    vector<long long> fact, invFact;

    long long modPow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    long long C(int n, int r) {
        return fact[n] * invFact[r] % MOD
                     * invFact[n-r] % MOD;
    }

    long long solve(vector<int>& a) {
        int n = a.size();
        if (n <= 2) return 1;

        vector<int> left, right;

        for (int i = 1; i < n; i++) {
            if (a[i] < a[0])
                left.push_back(a[i]);
            else
                right.push_back(a[i]);
        }

        long long ans = C(n - 1, left.size());
        ans = ans * solve(left) % MOD;
        ans = ans * solve(right) % MOD;

        return ans;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        fact.assign(n + 1, 1);
        invFact.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
            fact[i] = fact[i - 1] * i % MOD;

        invFact[n] = modPow(fact[n], MOD - 2);

        for (int i = n; i >= 1; i--)
            invFact[i - 1] = invFact[i] * i % MOD;

        return (solve(nums) - 1 + MOD) % MOD;
    }
};

TIME COMPLEXITY
---------------
Expected/simple analysis: O(n^2) with vector partitioning at
every recursive level in the worst case.

Factorial and inverse-factorial preprocessing: O(n + log MOD).

Total: O(n^2 + log MOD).

SPACE COMPLEXITY
----------------
O(n^2) worst-case auxiliary allocation across recursive
partition vectors; recursion depth can be O(n).

============================================================
DRY RUN
============================================================

nums = [2, 1, 3]

Root = 2
Left subtree  = [1]  => L = 1
Right subtree = [3]  => R = 1

Interleavings:
C(2, 1) = 2

Both subtrees contain one element, so each has exactly one
valid ordering.

Total ways = 2 * 1 * 1 = 2

Subtract the original ordering:
Answer = 2 - 1 = 1

============================================================
INTERVIEW NOTES
============================================================

PATTERN
-------
Recursion + BST decomposition + Combinatorics
(Interleaving independent subsequences).

KEY OBSERVATION
---------------
The root fixes the left/right partitions.
Only the interleaving of the two partitions contributes
the binomial coefficient C(L + R, L).

COMMON MISTAKES
---------------
1. Forgetting to subtract one for the original permutation.
2. Forgetting modulo arithmetic during multiplication.
3. Computing combinations without modular inverses.
4. Using ordinary division under modulo arithmetic.
5. Forgetting that the original array contains distinct values.
6. Returning -1 directly without normalizing modulo MOD.

WHEN TO USE THIS APPROACH
-------------------------
Use this pattern when:
- A sequence recursively splits into independent groups.
- Each group's internal order must be preserved.
- Elements from different groups can be interleaved.
- The number of interleavings is a binomial coefficient.

Similar ideas appear in counting valid tree traversals,
merging ordered sequences, and recursive combinatorics.

============================================================
*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> parent, sz;

    int find(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
    }

    int largestComponentSize(vector<int> &nums)
    {
        int n = nums.size();

        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        // factor -> index of a number containing this factor
        unordered_map<int, int> mp;

        for (int i = 0; i < n; i++)
        {
            int x = nums[i];

            for (int f = 2; f * f <= x; f++)
            {
                if (x % f == 0)
                {
                    // Factor f
                    if (mp.count(f))
                        unite(i, mp[f]);
                    else
                        mp[f] = i;

                    // Factor x / f
                    int other = x / f;

                    if (mp.count(other))
                        unite(i, mp[other]);
                    else
                        mp[other] = i;
                }
            }

            // If x itself is prime
            if (x > 1)
            {
                if (mp.count(x))
                    unite(i, mp[x]);
                else
                    mp[x] = i;
            }
        }

        int ans = 1;

        for (int i = 0; i < n; i++)
        {
            ans = max(ans, sz[find(i)]);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {4, 6, 15, 35};

    cout << obj.largestComponentSize(nums) << '\n';

    return 0;
}

/*
===============================================================================
          LEETCODE 952 - LARGEST COMPONENT SIZE BY COMMON FACTOR
                         UNION-FIND / DSU APPROACH
===============================================================================

Problem Statement:
------------------
Given an array of distinct positive integers nums, consider a graph where:

    - Each number is a node.
    - Two numbers are connected if they share a common factor greater than 1.

Find the size of the largest connected component.

Example:

    nums = [4, 6, 15, 35]

Connections:

    4 and 6  -> common factor 2
    6 and 15 -> common factor 3
    15 and 35 -> common factor 5

Therefore all four numbers belong to one component.

Answer:

    4


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Check every pair of numbers.

For every pair nums[i], nums[j]:

    Calculate gcd(nums[i], nums[j]).

If:

    gcd(nums[i], nums[j]) > 1

then the two numbers share a factor greater than 1, so union them.

After processing all pairs, find the size of the largest DSU component.


Pseudo Code:
-----------
Initialize DSU for all indices.

For every pair (i, j):

    if gcd(nums[i], nums[j]) > 1:
        union(i, j)

Find the largest component size.

Return it.


Complete Brute Force Code:
--------------------------

class Solution {
public:

    vector<int> parent, sz;

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];
    }

    int largestComponentSize(vector<int>& nums) {

        int n = nums.size();

        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                if (gcd(nums[i], nums[j]) > 1) {
                    unite(i, j);
                }
            }
        }

        int ans = 1;

        for (int i = 0; i < n; i++) {
            ans = max(ans, sz[find(i)]);
        }

        return ans;
    }
};


Time Complexity:
----------------
There are O(N^2) pairs.

Each gcd takes approximately O(log M), where M is the maximum value.

Therefore:

    O(N^2 log M)


Space Complexity:
-----------------
O(N)

For DSU arrays.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
We do NOT need to check every pair.

Suppose:

    nums = [6, 15]

Prime factors:

    6  -> 2, 3
    15 -> 3, 5

They share factor 3.

So instead of connecting every pair directly, we can connect numbers
through their prime factors.

Think of factors as intermediate connectors:

        6
        |
        3
        |
       15

If multiple numbers contain the same factor, they should belong to
the same component.

Therefore, for every factor:

    factor -> first number containing that factor

When another number contains the same factor:

    union(current number, previous number)


Intuition:
----------
For every number, find all its prime factors.

Example:

    60 = 2^2 * 3 * 5

We only care about:

    2, 3, 5

Not:

    2, 2, 3, 5

For each factor:

    If we have seen this factor before:
        union current index with the stored index.

    Otherwise:
        store current index for this factor.


Prime Factorization:
--------------------
For a number x:

    for (f = 2; f * f <= x; f++)

If:

    x % f == 0

then f is a factor.

We process f and x/f.

At the end, if x > 1, the remaining x is a prime factor.


Example:

    x = 12

Initially:

    f = 2

12 % 2 == 0

Factors:

    2 and 6

Then divide conceptually through the factorization process.

Unique prime factors:

    2, 3


Pseudo Code:
-----------
Initialize DSU.

Create:

    factor -> index

For every number nums[i]:

    x = nums[i]

    For f from 2 while f*f <= x:

        If x % f == 0:

            If factor f exists:
                union(i, factor[f])
            Else:
                factor[f] = i

            other = x / f

            If factor other exists:
                union(i, factor[other])
            Else:
                factor[other] = i

    If x > 1:

        If factor x exists:
            union(i, factor[x])
        Else:
            factor[x] = i

Finally:

    Find the largest DSU component.

Return its size.


Complete Optimal Code:
----------------------

// class Solution {
// public:
//
//     vector<int> parent, sz;
//
//     int find(int x) {
//         if (parent[x] == x)
//             return x;
//
//         return parent[x] = find(parent[x]);
//     }
//
//     void unite(int a, int b) {
//         a = find(a);
//         b = find(b);
//
//         if (a == b)
//             return;
//
//         if (sz[a] < sz[b])
//             swap(a, b);
//
//         parent[b] = a;
//         sz[a] += sz[b];
//     }
//
//     int largestComponentSize(vector<int>& nums) {
//
//         int n = nums.size();
//
//         parent.resize(n);
//         sz.assign(n, 1);
//
//         for (int i = 0; i < n; i++)
//             parent[i] = i;
//
//         unordered_map<int, int> mp;
//
//         for (int i = 0; i < n; i++) {
//
//             int x = nums[i];
//
//             for (int f = 2; f * f <= x; f++) {
//
//                 if (x % f == 0) {
//
//                     if (mp.count(f))
//                         unite(i, mp[f]);
//                     else
//                         mp[f] = i;
//
//                     int other = x / f;
//
//                     if (mp.count(other))
//                         unite(i, mp[other]);
//                     else
//                         mp[other] = i;
//                 }
//             }
//
//             if (x > 1) {
//
//                 if (mp.count(x))
//                     unite(i, mp[x]);
//                 else
//                     mp[x] = i;
//             }
//         }
//
//         int ans = 1;
//
//         for (int i = 0; i < n; i++) {
//             ans = max(ans, sz[find(i)]);
//         }
//
//         return ans;
//     }
// };


Time Complexity:
----------------
Let M = maximum value in nums.

For each number, we perform trial division up to sqrt(M).

Therefore:

    O(N * sqrt(M))

DSU operations are almost constant:

    O(alpha(N))

So overall:

    O(N * sqrt(M))

With the given constraints, this is efficient enough.


Space Complexity:
-----------------
O(N + M)

More precisely, the hashmap stores the factors encountered.

The DSU requires:

    O(N)

Overall auxiliary space is approximately:

    O(N + number of distinct factors)


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Input:

    nums = [4, 6, 15, 35]


Initially:

    {4}
    {6}
    {15}
    {35}


Process 4:

    4 = 2 * 2

    Factor 2 is not present.

    mp[2] = index of 4

Components:

    {4}
    {6}
    {15}
    {35}


Process 6:

    6 = 2 * 3

    Factor 2 already belongs to 4.

    union(6, 4)

    Component:

        {4, 6}

    Factor 3 is new.

    mp[3] = index of 6


Process 15:

    15 = 3 * 5

    Factor 3 already belongs to 6.

    union(15, 6)

    Component:

        {4, 6, 15}

    Factor 5 is new.

    mp[5] = index of 15


Process 35:

    35 = 5 * 7

    Factor 5 already belongs to 15.

    union(35, 15)

    Component:

        {4, 6, 15, 35}

    Factor 7 is new.


Final:

    Largest component = {4, 6, 15, 35}

    Size = 4


Answer:

    4


===============================================================================
IMPORTANT FACTOR OBSERVATION
===============================================================================

Suppose:

    x = 12

Its prime factors are:

    2, 3

Suppose another number is:

    y = 18

Its prime factors are:

    2, 3

They share both factors, but we only need one union to connect them.

That is why the hashmap:

    factor -> index

is sufficient.

We don't need to create actual factor nodes in the DSU.

Instead:

    same factor
        ->
    union their number indices


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Union-Find / DSU + Prime Factorization + HashMap


Key Observation:
----------------
Two numbers are connected if they share ANY factor greater than 1.

Instead of checking every pair:

    gcd(nums[i], nums[j]) > 1

factorize each number and union numbers that share a factor.


Common Mistakes:
----------------
1. Checking every pair.

   This gives O(N^2) and is unnecessary.

2. Using all divisors instead of prime factors.

   Prime factors are enough to determine whether two numbers share
   a common factor greater than 1.

3. Forgetting the remaining prime factor.

   After trial division, if:

       x > 1

   then x itself is a prime factor.

4. Forgetting that one number can have multiple factors.

5. Creating a separate DSU node for every factor unnecessarily.

   A hashmap:

       factor -> index

   is enough.

6. Not using path compression.

7. Not using union by size/rank.

8. Confusing this problem with LeetCode 128.

   In 128:
       Consecutive values -> union.

   In 952:
       Common factors -> union.


When to Use This Approach:
--------------------------
Use DSU + factorization when:

- Elements should be connected if they share a mathematical property.
- The property can be represented by factors.
- Many elements can share the same factor.
- You need the size of the largest connected group.

General pattern:

    Element
       |
    Property / Factor
       |
    Other Element

For this problem:

    Number -> Prime Factor -> Number

So numbers sharing a prime factor belong to the same DSU component.


===============================================================================
*/

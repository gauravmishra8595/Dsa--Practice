#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    static const long long MOD = 1e9 + 7;

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

    int numberOfSets(int n, int k)
    {

        int N = n + k - 1;

        vector<long long> fact(N + 1), invFact(N + 1);

        fact[0] = 1;

        for (int i = 1; i <= N; i++)
        {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[N] = modPow(fact[N], MOD - 2);

        for (int i = N - 1; i >= 0; i--)
        {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        long long ans = fact[N];
        ans = ans * invFact[2 * k] % MOD;
        ans = ans * invFact[N - 2 * k] % MOD;

        return (int)ans;
    }
};

int main()
{
    Solution sol;

    cout << sol.numberOfSets(4, 2) << '\n';  // 5
    cout << sol.numberOfSets(3, 1) << '\n';  // 3
    cout << sol.numberOfSets(30, 7) << '\n'; // 796297179

    return 0;
}

/*
================================================================================
                    LEETCODE 1621 - CP NOTEBOOK
================================================================================

Problem Statement
-----------------
Given n points on a 1-D plane, where the ith point is at coordinate i
(from 0 to n-1), find the number of ways to draw exactly k non-overlapping
line segments.

Each segment:
    - must cover at least two points
    - must have integral-coordinate endpoints
    - segments may share endpoints
    - segments must not overlap

Return the answer modulo 1e9 + 7.

Constraints:
    2 <= n <= 1000
    1 <= k <= n - 1

Example
-------
Input:
    n = 4
    k = 2

Output:
    5

Possible sets include:
    {(0,2), (2,3)}
    {(0,1), (1,3)}
    {(0,1), (2,3)}
    {(1,2), (2,3)}
    {(0,1), (1,2)}

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea
----
Generate every possible segment (i, j), where i < j.

Then recursively choose exactly k segments.

For every new segment:
    - its starting point must be >= the ending point of the previous segment
    - equality is allowed because segments may share endpoints

This directly enumerates all possible combinations of segments.

Pseudo Code
----------
generate all segments (i, j)

dfs(startSegment, chosen):
    if chosen.size() == k:
        answer++
        return

    for every segment (l, r):
        if l >= previousEnd:
            choose (l, r)
            dfs(next, chosen + 1)
            undo choice

Complete Brute Force Code
-------------------------
(For revision only; NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

long long bruteAnswer;
int n, k;

void dfs(int start, int lastEnd, int cnt) {
    if (cnt == k) {
        bruteAnswer++;
        return;
    }

    for (int l = start; l < n; l++) {
        for (int r = l + 1; r < n; r++) {

            // Segments cannot overlap.
            // Sharing an endpoint is allowed.
            if (l >= lastEnd) {
                dfs(l + 1, r, cnt + 1);
            }
        }
    }
}

long long bruteForce(int N, int K) {
    n = N;
    k = K;
    bruteAnswer = 0;

    dfs(0, 0, 0);

    return bruteAnswer;
}
*/

// Time Complexity-- -- -- -- -- -- -- --There are O(n ^ 2) possible segments.

//     We may
// try
// many combinations of k segments.

//     Worst case is approximately:

//     O((n ^ 2) ^ k)

// This becomes infeasible very quickly.

// Space Complexity
// ----------------
// Recursion depth:

//     O(k)

// So auxiliary space is:

//     O(k)

// ===============================================================================
// OPTIMAL APPROACH
// ===============================================================================

// Observation
// -----------
// The problem has a combinatorial interpretation.

// For k segments, we need 2k endpoints:

//     start1, end1, start2, end2, ..., startk, endk

// Because segments can share endpoints, we have:

//     start1 < end1 <= start2 < end2 <= ... <= startk < endk

// The non-strict inequalities caused by shared endpoints can be converted
// into strict inequalities by shifting later endpoints.

// After this transformation, the problem becomes equivalent to choosing
// 2k positions from:

//     n + k - 1

// positions.

// Therefore:

//     Answer = C(n + k - 1, 2k)

// Intuition
// ---------
// Consider the gaps between consecutive points.

// There are n - 1 gaps.

// A segment covering points uses one or more consecutive gaps.

// We need exactly k non-empty groups of gaps.

// Because consecutive segments are allowed to touch, the problem can be
// transformed into distributing the available gaps while accounting for
// the k segments.

// This leads to the standard combinatorial formula:

//     C(n + k - 1, 2k)

// For example:

//     n = 4
//     k = 2

// Answer:

//     C(4 + 2 - 1, 4)
//   = C(5, 4)
//   = 5

// Pseudo Code
// -----------
// numberOfSets(n, k):

//     N = n + k - 1

//     calculate factorials:
//         fact[i] = i!

//     calculate inverse factorials:
//         invFact[i] = 1 / i! modulo MOD

//     answer =
//         fact[N]
//         * invFact[2*k]
//         * invFact[N - 2*k]

//     return answer

// Complete Optimal Code
// ---------------------
// (Repeated here for revision only; the executable version is above.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const long long MOD = 1e9 + 7;

    long long modPow(long long a, long long b) {
        long long res = 1;

        while (b > 0) {
            if (b & 1) {
                res = res * a % MOD;
            }

            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1;

        vector<long long> fact(N + 1);
        vector<long long> invFact(N + 1);

        fact[0] = 1;

        for (int i = 1; i <= N; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        invFact[N] = modPow(fact[N], MOD - 2);

        for (int i = N - 1; i >= 0; i--) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        long long ans = fact[N];
        ans = ans * invFact[2 * k] % MOD;
        ans = ans * invFact[N - 2 * k] % MOD;

        return (int)ans;
    }
};
*/

// Time Complexity
// ----------------
// We calculate factorials and inverse factorials up to:

//     n + k - 1

// So:

//     O(n + k)

// Since k <= n - 1:

//     O(n)

// Space Complexity
// ----------------
// We store factorial and inverse factorial arrays:

//     O(n + k)

// Therefore:

//     O(n)

// ===============================================================================
// DRY RUN WITH EXAMPLE
// ===============================================================================

// Input:
//     n = 4
//     k = 2

// Step 1:
//     N = n + k - 1

//       = 4 + 2 - 1
//       = 5

// Step 2:
//     We need:

//         C(N, 2k)

//         = C(5, 4)

// Step 3:
//     Using:

//         C(5,4) = 5! / (4! * 1!)

//               = 120 / 24

//               = 5

// Therefore:

//     Answer = 5

// For another example:

//     n = 3
//     k = 1

//     N = 3 + 1 - 1
//       = 3

//     Answer = C(3, 2)

//             = 3

// The three segments are:

//     (0,1)
//     (0,2)
//     (1,2)

// ===============================================================================
// INTERVIEW NOTES
// ===============================================================================

// Pattern
// -------
// Combinatorics + Modular Arithmetic

// More specifically:

//     - Counting
//     - nCr
//     - Factorials
//     - Modular Inverse
//     - Fermat's Little Theorem

// Key Observation
// ---------------
// The key observation is:

//     Number of valid configurations
//     =
//     C(n + k - 1, 2k)

// Instead of explicitly generating segments, transform the endpoint
// constraints into a simple combinations problem.

// Common Mistakes
// ---------------
// 1. Forgetting that segments ARE allowed to share endpoints.

// 2. Treating:

//        end1 == start2

//    as invalid.

// 3. Using normal division under modulo.

//    Wrong:

//        fact[N] / fact[r]

//    Correct:

//        fact[N] * inverse(fact[r]) % MOD

// 4. Forgetting that MOD = 1e9 + 7 is prime and that:

//        inverse(x) = x^(MOD - 2) % MOD

//    by Fermat's Little Theorem.

// 5. Using int for multiplication without casting.

//    Prefer:

//        long long

// When to Use This Approach
// -------------------------
// Use this approach when:

//     - The problem asks to count configurations.
//     - The constraints between selected elements can be transformed
//       into strict/non-strict ordering constraints.
//     - The resulting configurations correspond to choosing positions
//       or distributing objects.
//     - The answer is required modulo a prime.
//     - nCr can represent the resulting count.

// For LeetCode 1621, this converts an apparently complicated segment
// selection problem into a single binomial coefficient.

// ===============================================================================
// */

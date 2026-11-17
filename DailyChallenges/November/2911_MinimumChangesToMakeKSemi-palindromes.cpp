#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minimumChanges(string s, int k)
    {
        int n = s.size();

        // Step 1: Precompute cost of every substring.
        vector<vector<int>> cost(n, vector<int>(n, 0));

        for (int len = 2; len <= n; len++)
        {
            for (int i = 0; i + len <= n; i++)
            {
                int j = i + len - 1;
                cost[i][j] = INT_MAX;

                // Try every proper divisor.
                for (int d = 1; d < len; d++)
                {
                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Check each modulo-d group.
                    for (int r = 0; r < d; r++)
                    {
                        int l = i + r;

                        // CORRECTED RIGHT POINTER
                        int right = i + r +
                                    ((len - 1 - r) / d) * d;

                        while (l < right)
                        {
                            if (s[l] != s[right])
                            {
                                changes++;
                            }

                            l += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // Step 2: Partition DP.
        const int INF = 1e9;

        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF));

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++)
        {
            for (int i = 2 * parts; i <= n; i++)
            {
                for (int j = 2 * (parts - 1); j <= i - 2; j++)
                {

                    if (dp[j][parts - 1] == INF)
                        continue;

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[j][parts - 1] + cost[j][i - 1]);
                }
            }
        }

        return dp[n][k];
    }
};

int main()
{
    Solution sol;

    cout << sol.minimumChanges("abcac", 2) << '\n';
    // Output: 1

    cout << sol.minimumChanges("abcdef", 2) << '\n';

    return 0;
}

/*
============================================================
                 LEETCODE 2911
          MINIMUM CHANGES TO MAKE K
                SEMI-PALINDROMES
============================================================

BUG FIX:
--------
For a modulo-d group, the character indices are:

i+r, i+r+d, i+r+2d, ...

Correct last index:

right = i + r + ((len-1-r)/d)*d;

The previous implementation calculated this incorrectly.

------------------------------------------------------------
OPTIMAL APPROACH
------------------------------------------------------------

1. PRECOMPUTATION

cost[i][j] = Minimum changes to make s[i...j]
             a semi-palindrome.

For each substring:
- Find all proper divisors d of its length.
- Divide indices into d modulo groups.
- Compare mirrored characters in each group.
- Count mismatches.
- Take minimum across all divisors.

2. PARTITION DP

dp[i][parts] = Minimum changes required to divide
               first i characters into exactly parts
               semi-palindromes.

Transition:

dp[i][parts] = min(
    dp[j][parts-1] + cost[j][i-1]
)

BASE CASE:

dp[0][0] = 0

ANSWER:

dp[n][k]

------------------------------------------------------------
PSEUDOCODE
------------------------------------------------------------

Precompute cost:

for len = 2 to n:
    for i = 0 to n-len:
        j = i + len - 1

        for d = 1 to len-1:
            if len % d != 0:
                continue

            changes = 0

            for r = 0 to d-1:
                l = i+r
                right = i+r+((len-1-r)/d)*d

                while l < right:
                    if s[l] != s[right]:
                        changes++

                    l += d
                    right -= d

            cost[i][j] = min(cost[i][j], changes)

Partition DP:

dp[0][0] = 0

for parts = 1 to k:
    for i = 2*parts to n:
        for j = 2*(parts-1) to i-2:
            dp[i][parts] = min(
                dp[i][parts],
                dp[j][parts-1] + cost[j][i-1]
            )

return dp[n][k]

------------------------------------------------------------
COMPLEXITY
------------------------------------------------------------

Precomputation: O(n^3 log n) upper bound
Partition DP:   O(k * n^2)

Space:
Cost matrix: O(n^2)
DP matrix:   O(n*k)

Total Space: O(n^2 + n*k)

------------------------------------------------------------
INTERVIEW NOTES
------------------------------------------------------------

Pattern:
String DP + Partition DP + Precomputation.

Key Observation:
Characters at equal indices modulo d must form
palindromes.

Common Mistakes:
1. Including d = len as a divisor.
2. Incorrect right pointer calculation.
3. Allowing substring length less than 2.
4. Using incorrect DP boundaries.
5. Forgetting exactly k partitions.

============================================================
*/
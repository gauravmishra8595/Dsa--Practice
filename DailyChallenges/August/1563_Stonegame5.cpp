#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<vector<int>> f;
    vector<vector<int>> maxl;
    vector<vector<int>> maxr;

public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        f.assign(n, vector<int>(n, 0));
        maxl.assign(n, vector<int>(n, 0));
        maxr.assign(n, vector<int>(n, 0));

        for (int left = n - 1; left >= 0; --left) {
            maxl[left][left] = stoneValue[left];
            maxr[left][left] = stoneValue[left];

            int sum = stoneValue[left];
            int suml = 0;

            for (int right = left + 1, i = left - 1;
                 right < n;
                 ++right) {

                sum += stoneValue[right];

                while (i + 1 < right &&
                       (suml + stoneValue[i + 1]) * 2 <= sum) {
                    suml += stoneValue[i + 1];
                    ++i;
                }

                // left part has sum <= right part
                if (left <= i) {
                    f[left][right] =
                        max(f[left][right], maxl[left][i]);
                }

                // right part has sum < left part
                if (i + 1 < right) {
                    f[left][right] =
                        max(f[left][right], maxr[i + 2][right]);
                }

                // Both parts have equal sum
                if (suml * 2 == sum) {
                    f[left][right] =
                        max(f[left][right], maxr[i + 1][right]);
                }

                maxl[left][right] =
                    max(maxl[left][right - 1],
                        sum + f[left][right]);

                maxr[left][right] =
                    max(maxr[left + 1][right],
                        sum + f[left][right]);
            }
        }

        return f[0][n - 1];
    }
};

int main() {
    Solution sol;

    vector<int> stoneValue = {6, 2, 3, 4, 5, 5};

    cout << "Answer: "
         << sol.stoneGameV(stoneValue)
         << '\n';

    return 0;
}

/*
===============================================================================
                            LEETCODE 1563
                           STONE GAME V
===============================================================================

Problem Statement
-----------------
Given an array stoneValue, Alice and Bob play a game.

Alice divides the current array into two non-empty parts.
Bob chooses one part and discards the other.
Alice adds the sum of the remaining part to her score.

The process continues until only one stone remains.

Both players play optimally.

Return the maximum score Alice can obtain.

Example
-------
Input:
    stoneValue = [6,2,3,4,5,5]

Output:
    18


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea
----
For every interval [l, r], try every possible split k.

Let:

    leftSum  = sum(l ... k)
    rightSum = sum(k+1 ... r)

Bob keeps the part with the smaller sum.

If leftSum < rightSum:

    Alice gets leftSum
    Continue with [l, k]

If leftSum > rightSum:

    Alice gets rightSum
    Continue with [k+1, r]

If both are equal:

    Alice can get the common sum and choose the better continuation.

Pseudo Code
-----------
solve(l, r):

    if l == r:
        return 0

    ans = 0

    for k = l to r-1:

        leftSum = sum(l...k)
        rightSum = sum(k+1...r)

        if leftSum < rightSum:
            ans = max(ans,
                      leftSum + solve(l,k))

        else if leftSum > rightSum:
            ans = max(ans,
                      rightSum + solve(k+1,r))

        else:
            ans = max(ans,
                      leftSum +
                      max(solve(l,k),
                          solve(k+1,r)))

    return ans


Complete Brute Force Code
--------------------------

class Solution {
public:
    int solve(vector<int>& a, int l, int r) {
        if (l == r)
            return 0;

        int ans = 0;

        for (int k = l; k < r; ++k) {
            int leftSum = 0;
            int rightSum = 0;

            for (int i = l; i <= k; ++i)
                leftSum += a[i];

            for (int i = k + 1; i <= r; ++i)
                rightSum += a[i];

            if (leftSum < rightSum) {
                ans = max(ans,
                          leftSum + solve(a, l, k));
            }
            else if (leftSum > rightSum) {
                ans = max(ans,
                          rightSum + solve(a, k + 1, r));
            }
            else {
                ans = max(ans,
                          leftSum +
                          max(solve(a, l, k),
                              solve(a, k + 1, r)));
            }
        }

        return ans;
    }

    int stoneGameV(vector<int>& stoneValue) {
        return solve(stoneValue, 0,
                     stoneValue.size() - 1);
    }
};

Time Complexity
----------------
Exponential.

There are many overlapping subproblems and every state tries multiple
partitions.

Worst case is approximately:

    O(2^n)

Space Complexity
----------------
Recursion depth:

    O(n)


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation
-----------
The normal interval DP is:

    f[l][r] = maximum score Alice can obtain from [l,r].

The straightforward transition checks every split, resulting in O(n^3).

However, stone values are positive.

As the split point moves from left to right:

    leftSum  increases
    rightSum decreases

Therefore, there is only one boundary where:

    leftSum <= rightSum

changes to:

    leftSum > rightSum

We can maintain this boundary using a moving pointer instead of checking
every split.

This reduces the transition work substantially.


Intuition
---------
We maintain three DP tables:

1. f[l][r]

   Maximum score Alice can obtain from interval [l,r].


2. maxl[l][r]

   Maximum value of:

       sum(l...k) + f[l][k]

   for valid k inside [l,r].

   This lets us quickly obtain the best answer when the left part is chosen.


3. maxr[l][r]

   Maximum value of:

       sum(k...r) + f[k][r]

   for valid k inside [l,r].

   This lets us quickly obtain the best answer when the right part is chosen.

The pointer i tracks the largest position for which:

    leftSum <= rightSum

Because all stone values are positive, this pointer only moves forward.

That is the key optimization.

Instead of trying every k, we directly consider the relevant boundary.


Pseudo Code
-----------
Initialize:

    f[n][n]
    maxl[n][n]
    maxr[n][n]

Process left from n-1 down to 0.

For every right > left:

    Update total sum.

    Move pointer i while:

        leftSum <= rightSum

    If left part is smaller:

        use maxl[left][i]

    If right part is smaller:

        use maxr[i+2][right]

    If both parts are equal:

        use maxr[i+1][right]

    Update:

        maxl[left][right]

        maxr[left][right]

Return:

    f[0][n-1]


Complete Optimal Code
----------------------

class Solution {
private:
    vector<vector<int>> f;
    vector<vector<int>> maxl;
    vector<vector<int>> maxr;

public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        f.assign(n, vector<int>(n, 0));
        maxl.assign(n, vector<int>(n, 0));
        maxr.assign(n, vector<int>(n, 0));

        for (int left = n - 1; left >= 0; --left) {
            maxl[left][left] = stoneValue[left];
            maxr[left][left] = stoneValue[left];

            int sum = stoneValue[left];
            int suml = 0;

            for (int right = left + 1, i = left - 1;
                 right < n;
                 ++right) {

                sum += stoneValue[right];

                while (i + 1 < right &&
                       (suml + stoneValue[i + 1]) * 2 <= sum) {
                    suml += stoneValue[i + 1];
                    ++i;
                }

                if (left <= i) {
                    f[left][right] = max(
                        f[left][right],
                        maxl[left][i]
                    );
                }

                if (i + 1 < right) {
                    f[left][right] = max(
                        f[left][right],
                        maxr[i + 2][right]
                    );
                }

                if (suml * 2 == sum) {
                    f[left][right] = max(
                        f[left][right],
                        maxr[i + 1][right]
                    );
                }

                maxl[left][right] = max(
                    maxl[left][right - 1],
                    sum + f[left][right]
                );

                maxr[left][right] = max(
                    maxr[left + 1][right],
                    sum + f[left][right]
                );
            }
        }

        return f[0][n - 1];
    }
};


Time Complexity
----------------
There are O(n^2) intervals.

The pointer i moves forward across each interval instead of trying every
possible split.

Therefore the total complexity is:

    O(n^2)

Space Complexity
----------------
We maintain three n x n DP tables:

    f
    maxl
    maxr

Therefore:

    O(n^2)


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Example:

    [6, 2, 3, 4, 5, 5]

Consider some interval:

    [2, 3, 4]

Possible split:

    [2] | [3,4]

Sums:

    leftSum  = 2
    rightSum = 7

Since:

    2 < 7

Bob keeps [2].

Alice receives:

    2

and continues on [2].

Now consider:

    [2,3] | [4]

Sums:

    leftSum  = 5
    rightSum = 4

Since:

    5 > 4

Bob keeps [4].

Alice receives:

    4

and continues on [4].

The optimized solution does not explicitly try every split.

Instead, it tracks the point where:

    leftSum <= rightSum

stops being true.

Because every stone value is positive, once leftSum becomes larger than
rightSum, moving farther right cannot make leftSum smaller again.

Therefore the pointer never needs to move backward.

The auxiliary tables maxl and maxr store the best continuation values so
that we can immediately obtain the best answer for the relevant split.

For the full example:

    [6,2,3,4,5,5]

the final DP value becomes:

    f[0][5] = 18

Therefore:

    Answer = 18


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern
-------
Interval DP / Range DP

Main state:

    f[l][r]


Key Observation
---------------
For positive stone values:

    leftSum increases
    rightSum decreases

as the partition point moves right.

Therefore, the optimal split can be located using a monotonic pointer.

The auxiliary prefix-style DP tables:

    maxl
    maxr

allow us to avoid scanning all split positions.


Common Mistakes
---------------
1. Forgetting that Bob chooses the smaller-sum side.

2. Treating the equal-sum case incorrectly.

   When:

       leftSum == rightSum

   Alice gets the common sum and can choose the better continuation.

3. Moving the split pointer backward.

   It should only move forward because all values are positive.

4. Incorrect indexing around:

       i
       i + 1
       i + 2

   The ranges must remain non-empty.

5. Using this optimization when array values can be negative.

   The monotonicity of leftSum/rightSum depends on positive values.

6. Confusing maxl/maxr with ordinary prefix/suffix sums.

   They store maximum DP transition values, not just sums.


When to Use This Approach
-------------------------
Use this optimization when:

    - The problem is interval DP.
    - Every split divides the interval into two parts.
    - The transition depends on comparing the sums of both parts.
    - Array values are positive.
    - The split condition changes monotonically as the split point moves.

The key progression is:

    O(n^3) interval DP
          |
          v
    Observe monotonic split
          |
          v
    Maintain split pointer
          |
          v
    Use auxiliary max DP
          |
          v
        O(n^2)


Final Complexity
----------------
    Time  : O(n^2)
    Space : O(n^2)

===============================================================================
*/
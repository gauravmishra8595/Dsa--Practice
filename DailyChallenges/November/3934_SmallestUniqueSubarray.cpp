#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int N = n + 1;

        // Coordinate compression
        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        // Append unique smallest sentinel
        vector<int> s(N, 0);

        for (int i = 0; i < n; i++) {
            s[i] = lower_bound(vals.begin(), vals.end(), nums[i])
                   - vals.begin() + 1;
        }

        // Build suffix array
        vector<int> sa(N), c(N);
        vector<int> cnt(max(N, (int)vals.size() + 2), 0);

        for (int x : s)
            cnt[x]++;

        for (int i = 1; i < (int)cnt.size(); i++)
            cnt[i] += cnt[i - 1];

        for (int i = N - 1; i >= 0; i--)
            sa[--cnt[s[i]]] = i;

        c[sa[0]] = 0;
        int classes = 1;

        for (int i = 1; i < N; i++) {
            if (s[sa[i]] != s[sa[i - 1]])
                classes++;

            c[sa[i]] = classes - 1;
        }

        vector<int> pn(N), cn(N);

        for (int len = 1; len < N; len *= 2) {
            for (int i = 0; i < N; i++) {
                pn[i] = sa[i] - len;

                if (pn[i] < 0)
                    pn[i] += N;
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);

            for (int i = 0; i < N; i++)
                cnt[c[pn[i]]]++;

            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];

            for (int i = N - 1; i >= 0; i--) {
                int x = pn[i];
                sa[--cnt[c[x]]] = x;
            }

            cn[sa[0]] = 0;
            int newClasses = 1;

            for (int i = 1; i < N; i++) {
                int cur = sa[i];
                int prev = sa[i - 1];

                if (c[cur] != c[prev] ||
                    c[(cur + len) % N] !=
                    c[(prev + len) % N]) {
                    newClasses++;
                }

                cn[cur] = newClasses - 1;
            }

            swap(c, cn);
            classes = newClasses;
        }

        // Inverse suffix array
        vector<int> rank(N);

        for (int i = 0; i < N; i++)
            rank[sa[i]] = i;

        // Kasai's LCP algorithm
        vector<int> lcp(N, 0);
        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = rank[i];

            if (r == 0) {
                h = 0;
                continue;
            }

            int j = sa[r - 1];

            while (i + h < n &&
                   j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        // Find minimum unique subarray length
        int ans = n;

        for (int i = 0; i < n; i++) {
            int r = rank[i];

            int maxLcp = lcp[r];

            if (r + 1 < N)
                maxLcp = max(maxLcp, lcp[r + 1]);

            if (maxLcp < n - i)
                ans = min(ans, maxLcp + 1);
        }

        return ans;
    }
};



int main() {
    Solution sol;

    vector<int> nums = {1, 2, 1, 3, 2};

    cout << sol.smallestUniqueSubarray(nums) << '\n';

    return 0;
}

/*
============================================================
              SMALLEST UNIQUE SUBARRAY
              SUFFIX ARRAY + LCP
============================================================

1. PROBLEM STATEMENT
--------------------

Given an integer array nums, find the minimum length
of a contiguous subarray that occurs exactly once
in the entire array.

Return the minimum possible length.

------------------------------------------------------------

2. EXAMPLE
----------

Input:
nums = [1, 2, 1, 3, 2]

Output:
1

Explanation:

[1] occurs multiple times.
[2] occurs multiple times.
[3] occurs exactly once.

Therefore, the smallest unique subarray is [3].

Answer = 1.

============================================================

3. BRUTE FORCE APPROACH
-----------------------

IDEA:
-----

Generate all possible subarrays.

For every subarray:
1. Count its occurrences in the complete array.
2. If frequency is exactly one, update the answer.
3. Return the minimum length.

PSEUDO CODE:
------------

ans = n

for len = 1 to n:

    for i = 0 to n-len:

        count = 0

        for j = 0 to n-len:

            if subarray(i, len) == subarray(j, len):
                count++

        if count == 1:
            ans = min(ans, len)

return ans

COMPLETE BRUTE FORCE CODE:
--------------------------

// Inside comments only.

int bruteForce(vector<int>& nums) {
    int n = nums.size();
    int ans = n;

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {

            int count = 0;

            for (int j = 0; j + len <= n; j++) {

                bool equal = true;

                for (int k = 0; k < len; k++) {
                    if (nums[i + k] != nums[j + k]) {
                        equal = false;
                        break;
                    }
                }

                if (equal)
                    count++;
            }

            if (count == 1)
                ans = min(ans, len);
        }
    }

    return ans;
}

TIME COMPLEXITY:
----------------
O(N^4)

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space.

============================================================

4. OPTIMAL APPROACH
-------------------

OBSERVATION:
------------

Consider every suffix of the array.

For a suffix starting at index i, we need the shortest
prefix that does not occur in any other suffix.

If the maximum common prefix with another suffix is L,
then the first L elements are not unique.

Therefore:

    Minimum unique prefix length = L + 1

INTUITION:
----------

We use a Suffix Array to sort all suffixes
lexicographically.

We use the LCP array to calculate the longest common
prefix between adjacent suffixes.

IMPORTANT PROPERTY:

For any suffix, its maximum LCP with any other suffix
is achieved by one of its immediate neighbors in
the sorted suffix array.

Therefore:

    maxLcp = max(lcp[r], lcp[r + 1])

where r = rank[i].

The shortest unique subarray starting at index i is:

    maxLcp + 1

We also check whether this length fits inside the
remaining array.

Take the minimum over all starting positions.

------------------------------------------------------------

PSEUDO CODE:
------------

Coordinate compress nums.

Append a unique smallest sentinel.

Build suffix array using doubling.

Build inverse suffix array.

Build LCP using Kasai's algorithm.

ans = n

for i = 0 to n-1:

    r = rank[i]

    maxLcp = lcp[r]

    if r+1 < N:
        maxLcp = max(maxLcp, lcp[r+1])

    if maxLcp < n-i:
        ans = min(ans, maxLcp+1)

return ans

------------------------------------------------------------

COMPLETE OPTIMAL CODE:
----------------------

// Same implementation as the Solution class above.

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int N = n + 1;

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        vector<int> s(N, 0);

        for (int i = 0; i < n; i++) {
            s[i] = lower_bound(vals.begin(), vals.end(), nums[i])
                   - vals.begin() + 1;
        }

        vector<int> sa(N), c(N);
        vector<int> cnt(max(N, (int)vals.size() + 2), 0);

        for (int x : s)
            cnt[x]++;

        for (int i = 1; i < (int)cnt.size(); i++)
            cnt[i] += cnt[i - 1];

        for (int i = N - 1; i >= 0; i--)
            sa[--cnt[s[i]]] = i;

        c[sa[0]] = 0;
        int classes = 1;

        for (int i = 1; i < N; i++) {
            if (s[sa[i]] != s[sa[i - 1]])
                classes++;

            c[sa[i]] = classes - 1;
        }

        vector<int> pn(N), cn(N);

        for (int len = 1; len < N; len *= 2) {
            for (int i = 0; i < N; i++) {
                pn[i] = sa[i] - len;
                if (pn[i] < 0)
                    pn[i] += N;
            }

            fill(cnt.begin(), cnt.begin() + classes, 0);

            for (int i = 0; i < N; i++)
                cnt[c[pn[i]]]++;

            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];

            for (int i = N - 1; i >= 0; i--) {
                int x = pn[i];
                sa[--cnt[c[x]]] = x;
            }

            cn[sa[0]] = 0;
            int newClasses = 1;

            for (int i = 1; i < N; i++) {
                int cur = sa[i];
                int prev = sa[i - 1];

                if (c[cur] != c[prev] ||
                    c[(cur + len) % N] !=
                    c[(prev + len) % N]) {
                    newClasses++;
                }

                cn[cur] = newClasses - 1;
            }

            swap(c, cn);
            classes = newClasses;
        }

        vector<int> rank(N);

        for (int i = 0; i < N; i++)
            rank[sa[i]] = i;

        vector<int> lcp(N, 0);
        int h = 0;

        for (int i = 0; i < n; i++) {
            int r = rank[i];

            if (r == 0) {
                h = 0;
                continue;
            }

            int j = sa[r - 1];

            while (i + h < n &&
                   j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[r] = h;

            if (h > 0)
                h--;
        }

        int ans = n;

        for (int i = 0; i < n; i++) {
            int r = rank[i];
            int maxLcp = lcp[r];

            if (r + 1 < N)
                maxLcp = max(maxLcp, lcp[r + 1]);

            if (maxLcp < n - i)
                ans = min(ans, maxLcp + 1);
        }

        return ans;
    }
}

TIME COMPLEXITY:
----------------

Coordinate Compression : O(N log N)

Suffix Array           : O(N log N)

Inverse Rank           : O(N)

Kasai's LCP            : O(N)

Final Answer           : O(N)

OVERALL:
    O(N log N)

SPACE COMPLEXITY:
-----------------

O(N)

============================================================

5. DRY RUN WITH EXAMPLE
-----------------------

Input:

nums = [1, 2, 1, 3, 2]

Check subarrays of length 1:

Index 0 -> [1] -> Frequency = 2
Index 1 -> [2] -> Frequency = 2
Index 2 -> [1] -> Frequency = 2
Index 3 -> [3] -> Frequency = 1
Index 4 -> [2] -> Frequency = 2

The subarray [3] occurs exactly once.

Therefore:

    ans = 1

Output:

    1

============================================================

6. INTERVIEW NOTES
------------------

PATTERN:
--------

Suffix Array + Longest Common Prefix (LCP).

KEY OBSERVATION:
----------------

The shortest unique prefix of a suffix is one greater
than its maximum LCP with another suffix.

Maximum LCP can be obtained by checking the two
adjacent suffixes in suffix array order.

COMMON MISTAKES:
----------------

1. Forgetting to append the sentinel.

2. Using a sentinel that is not smaller than all
   compressed values.

3. Forgetting coordinate compression for arbitrary
   integer values.

4. Incorrect suffix array construction.

5. Confusing LCP indexing conventions.

6. Forgetting the boundary condition:

       maxLcp < n - i

7. Assuming rolling hash is collision-free.

8. Assuming binary search works without proving
   monotonicity.

WHEN TO USE THIS APPROACH:
--------------------------

Use Suffix Array + LCP for:

1. Unique substring problems.
2. Repeated substring problems.
3. Longest common prefix.
4. Lexicographical suffix ordering.
5. Pattern matching.
6. Finding common prefixes efficiently.

============================================================

7. FINAL COMPLEXITY SUMMARY
---------------------------

BRUTE FORCE:

Time  : O(N^4)
Space : O(1)

OPTIMAL:

Time  : O(N log N)
Space : O(N)

MOST IMPORTANT FORMULA:

    shortestUniqueLength = maxLcp + 1

============================================================
*/
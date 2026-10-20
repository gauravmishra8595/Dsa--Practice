#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, INT_MAX);
        vector<int> prefDrop(n, 0);
        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }
        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }
        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1]
                        + (nums[i - 1] > nums[i]);
        }
        int ans = 0;
        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;
            bool valid = true;
            for (int i = 0; i < n; i += k) {
                int j = i + k - 1;
                int drops = prefDrop[j] - prefDrop[i];
                if (nums[j] > nums[i]) {
                    drops++;
                }
                if (drops > 1 || prefMax[i] > suffMin[i]) {
                    valid = false;
                    break;
                }
            }
            if (valid) ans += k;
        }
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {3, 1, 2};
    vector<int> nums2 = {7, 6, 5};
    vector<int> nums3 = {5, 8};

    cout << sol.sortableIntegers(nums1) << '\n'; // 3
    cout << sol.sortableIntegers(nums2) << '\n'; // 0
    cout << sol.sortableIntegers(nums3) << '\n'; // 3

    return 0;
}

/*
===============================================================================
                    LEETCODE 3886: SUM OF SORTABLE INTEGERS
===============================================================================

PROBLEM STATEMENT
-----------------
Given an integer array nums of length n, an integer k is sortable if:
1. k divides n.
2. nums can be partitioned into consecutive blocks of length k.
3. Each block can be independently cyclically rotated so that the entire
   array becomes non-decreasing.

Return the sum of all sortable integers k.

EXAMPLE
-------
Input:  nums = [3, 1, 2]
Output: 3

Explanation:
k = 1: Cannot sort the array using rotations of single-element blocks.
k = 3: Rotate [3, 1, 2] to [1, 2, 3].
Answer = 3.

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

IDEA
----
Enumerate every divisor k of n.
For each k, generate every possible cyclic rotation of every block.
Try every combination of block rotations and check whether the resulting
entire array is sorted.

This approach is correct but exponential and impractical for large n.

PSEUDO CODE
-----------
function bruteForce(nums):
    n = length(nums)
    answer = 0

    for k from 1 to n:
        if n % k != 0:
            continue

        blocks = partition nums into blocks of length k

        if any combination of cyclic rotations produces a sorted array:
            answer += k

    return answer

COMPLETE BRUTE FORCE CODE (REVISION ONLY)
------------------------------------------
The following helper tries all rotations recursively.

bool bruteTry(vector<int>& nums, int k, int block,
              vector<int>& candidate) {
    int n = nums.size();

    if (block == n) {
        return is_sorted(candidate.begin(), candidate.end());
    }

    int start = block;
    int end = start + k;

    for (int shift = 0; shift < k; shift++) {
        for (int j = 0; j < k; j++) {
            candidate[start + j] = nums[start + (j + shift) % k];
        }

        if (bruteTry(nums, k, end, candidate)) {
            return true;
        }
    }

    return false;
}

int bruteForce(vector<int>& nums) {
    int n = nums.size();
    int answer = 0;

    for (int k = 1; k <= n; k++) {
        if (n % k != 0) continue;

        vector<int> candidate(n);

        if (bruteTry(nums, k, 0, candidate)) {
            answer += k;
        }
    }

    return answer;
}

TIME COMPLEXITY
---------------
O(sum(k^(n/k))) over all divisors k of n, ignoring the additional
linear cost of checking each completed candidate.
This is exponential in the worst case.

SPACE COMPLEXITY
----------------
O(n) auxiliary space, excluding recursion-stack overhead.

NOTE:
The brute-force helper above is for conceptual revision. The executable
solution uses the optimal linear-preprocessing approach below.

===============================================================================
OPTIMAL APPROACH
===============================================================================

OBSERVATION
-----------
A block can be rotated into non-decreasing order if and only if it has at
most one strict circular descent.

For a block nums[l ... r], count:
- Every adjacent descent nums[i - 1] > nums[i] inside the block.
- One additional circular descent if nums[r] > nums[l].

The total must be at most one.

Even if every block can be sorted individually, their concatenation must
also be globally sorted.

At every block boundary i, the maximum of the entire prefix before i must
not exceed the minimum of the suffix beginning at i:

    prefMax[i] <= suffMin[i]

INTUITION
---------
Precompute three arrays:

1. prefMax[i]:
   Maximum of nums[0 ... i - 1].

2. suffMin[i]:
   Minimum of nums[i ... n - 1].

3. prefDrop[i]:
   Number of strict adjacent descents among indices 1 ... i.

Using prefix counts, the number of internal descents in a block is:

    prefDrop[r] - prefDrop[l]

Then include the circular descent:

    if nums[r] > nums[l]:
        drops++

For every divisor k, check all blocks in O(n) total time.
If every block satisfies both conditions, add k to the answer.

PSEUDO CODE
-----------
function sortableIntegers(nums):
    n = length(nums)

    compute prefix maximum
    compute suffix minimum
    compute prefix count of adjacent descents

    answer = 0

    for k from 1 to n:
        if n % k != 0:
            continue

        valid = true

        for l from 0 to n - 1, stepping by k:
            r = l + k - 1

            drops = prefDrop[r] - prefDrop[l]

            if nums[r] > nums[l]:
                drops++

            if drops > 1 or prefMax[l] > suffMin[l]:
                valid = false
                break

        if valid:
            answer += k

    return answer

COMPLETE OPTIMAL CODE (REVISION ONLY)
--------------------------------------
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, INT_MAX);
        vector<int> prefDrop(n, 0);

        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }

        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }

        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1]
                        + (nums[i - 1] > nums[i]);
        }

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool valid = true;

            for (int i = 0; i < n; i += k) {
                int j = i + k - 1;
                int drops = prefDrop[j] - prefDrop[i];

                if (nums[j] > nums[i]) drops++;

                if (drops > 1 || prefMax[i] > suffMin[i]) {
                    valid = false;
                    break;
                }
            }

            if (valid) ans += k;
        }

        return ans;
    }
};

TIME COMPLEXITY
---------------
O(n + tau(n) * n), where tau(n) is the number of divisors of n.
More precisely, preprocessing costs O(n), and checking all valid
block sizes costs O(n * tau(n)) in the worst-case bound.

SPACE COMPLEXITY
----------------
O(n) for prefix maximum, suffix minimum, and descent-count arrays.

===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Input:
nums = [3, 1, 2]
n = 3

Preprocessing:
prefMax = [0, 3, 3, 3]
suffMin = [1, 1, 2, INT_MAX]
prefDrop = [0, 1, 1]

Divisors of 3: k = 1, 3

CASE 1: k = 1
--------------
Blocks: [3], [1], [2]

At the boundary i = 1:
prefMax[1] = 3
suffMin[1] = 1

Since 3 > 1, the global ordering condition fails.

Therefore, k = 1 is NOT sortable.

CASE 2: k = 3
--------------
Single block: [3, 1, 2]

l = 0, r = 2

Internal descents:
prefDrop[2] - prefDrop[0] = 1

Circular descent:
nums[2] > nums[0]?
2 > 3 is false.

Total circular descents = 1, so the block can be rotated into sorted order.

There are no internal block boundaries to violate the global condition.

Therefore, k = 3 IS sortable.

Final answer:
3

===============================================================================
INTERVIEW NOTES
===============================================================================

PATTERN
-------
- Array preprocessing
- Prefix maximum and suffix minimum
- Prefix sums / prefix counts
- Divisor enumeration
- Circular array reasoning

KEY OBSERVATION
---------------
A block is cyclically sortable exactly when its circular sequence contains
at most one strict descent. The blocks must additionally respect the global
ordering boundary condition.

COMMON MISTAKES
---------------
1. Checking only ordinary adjacent descents and forgetting the circular
   comparison between the last and first elements of each block.

2. Checking each block independently without checking global ordering
   between blocks.

3. Treating equal adjacent values as descents. A descent requires strict >.

4. Enumerating only arbitrary k values instead of restricting k to divisors
   of n.

5. Using int for the answer without checking the maximum possible sum.
   Under the given constraints, the sum of all divisors is safely within int.

WHEN TO USE THIS APPROACH
-------------------------
Use this technique when:
- Many candidate block sizes must be checked.
- The candidates are divisors of an array length.
- Each candidate can be validated using local conditions and boundary data.
- Prefix/suffix information can replace repeated scans.

===============================================================================
*/
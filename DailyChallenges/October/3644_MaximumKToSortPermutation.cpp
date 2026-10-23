#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1;
        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] != i) {
                ans &= nums[i];
            }
        }
        return ans == -1 ? 0 : ans;
    }
};
int main() {
    Solution sol;
    vector<int> nums1 = {0, 3, 2, 1};
    vector<int> nums2 = {0, 1, 3, 2};
    vector<int> nums3 = {3, 2, 1, 0};
    vector<int> nums4 = {0, 1, 2, 3};
    cout << sol.sortPermutation(nums1) << '\n'; // 1
    cout << sol.sortPermutation(nums2) << '\n'; // 2
    cout << sol.sortPermutation(nums3) << '\n'; // 0
    cout << sol.sortPermutation(nums4) << '\n'; // 0

    return 0;
}

/*
============================================================
       LEETCODE 3644: MAXIMUM K TO SORT A PERMUTATION
============================================================

PROBLEM STATEMENT:
------------------
Given a permutation nums of integers from 0 to n-1, we can
swap two elements only when their bitwise AND equals k.

Find the maximum non-negative integer k that allows nums
to be sorted in non-decreasing order.

If nums is already sorted, return 0.

EXAMPLE:
--------
Input:  nums = [0, 3, 2, 1]
Output: 1

Explanation:
Swap 3 and 1 because (3 & 1) == 1.
The array becomes [0, 1, 2, 3].

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA:
-----
Try every possible k from 0 to n-1, starting from the
largest. For each k, determine whether the array can be
sorted using only swaps whose bitwise AND equals k.

A straightforward simulation can explore reachable array
states, but this is extremely expensive. The following
brute-force implementation uses BFS over all reachable
permutations and is intended only for tiny inputs.

PSEUDO CODE:
------------
1. For k from n-1 down to 0:
2.     Put the original permutation into a BFS queue.
3.     Explore every array reachable through valid swaps.
4.     If a sorted array is reached, return k.
5. Return 0.

COMPLETE BRUTE FORCE CODE (REVISION ONLY):
------------------------------------------
int bruteForce(vector<int> nums) {
    int n = nums.size();

    for (int k = n - 1; k >= 0; k--) {
        queue<vector<int>> q;
        set<vector<int>> visited;

        q.push(nums);
        visited.insert(nums);

        while (!q.empty()) {
            vector<int> cur = q.front();
            q.pop();

            if (is_sorted(cur.begin(), cur.end())) {
                return k;
            }

            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if ((cur[i] & cur[j]) != k)
                        continue;

                    swap(cur[i], cur[j]);

                    if (!visited.count(cur)) {
                        visited.insert(cur);
                        q.push(cur);
                    }

                    swap(cur[i], cur[j]);
                }
            }
        }
    }

    return 0;
}

TIME COMPLEXITY:
----------------
Factorial in the worst case due to exploring permutations.
For each candidate k, up to n! states and O(n^2) transitions
per state may be explored.

SPACE COMPLEXITY:
-----------------
O(n * n!) for storing visited permutations and the BFS queue.

NOTE:
-----
This BFS brute force is only for conceptual revision and
very small arrays. It is not suitable for LeetCode limits.

============================================================
OPTIMAL APPROACH: BITWISE AND
============================================================

OBSERVATION:
------------
Because nums is a permutation of [0, n-1], the sorted array
must satisfy nums[i] == i at every index.

If nums[i] == i, that element is already in its correct
position and does not need to move.

Every misplaced element must participate in the swaps
needed to restore the permutation. Therefore, every bit
that is set in k must also be set in every misplaced value.

The largest valid k is the bitwise AND of all misplaced
values.

If there are no misplaced elements, return 0.

INTUITION:
----------
Suppose nums = [0, 3, 2, 1].

Misplaced values are 3 and 1.

3 in binary = 11
1 in binary = 01
              --
AND result  = 01 = 1

Thus, the maximum valid k is 1.

Initialize ans = -1 (all bits set in a signed integer).
AND each misplaced value into ans.

If no element is misplaced, ans remains -1, so return 0.

PSEUDO CODE:
------------
1. Initialize ans = -1.
2. For each index i:
       If nums[i] != i:
           ans = ans & nums[i]
3. If ans == -1, return 0.
4. Otherwise, return ans.

COMPLETE OPTIMAL CODE (REVISION ONLY):
--------------------------------------
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1;

        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] != i) {
                ans &= nums[i];
            }
        }

        return ans == -1 ? 0 : ans;
    }
};

TIME COMPLEXITY:
----------------
O(n), where n is the length of nums.
Each element is visited once.

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space.
Only a constant number of variables are used.

============================================================
DRY RUN WITH EXAMPLE
============================================================

Input:
nums = [0, 3, 2, 1]

Initially:
ans = -1

i = 0:
nums[0] = 0
nums[0] == i, so skip.
ans = -1

i = 1:
nums[1] = 3
nums[1] != i, so:
ans = -1 & 3 = 3

i = 2:
nums[2] = 2
nums[2] == i, so skip.
ans = 3

i = 3:
nums[3] = 1
nums[3] != i, so:
ans = 3 & 1 = 1

Final answer:
1

Output:
1

============================================================
INTERVIEW NOTES
============================================================

PATTERN:
--------
Bit Manipulation + Permutation + Greedy Observation.

KEY OBSERVATION:
----------------
Only misplaced values matter. The answer is the bitwise AND
of all nums[i] for which nums[i] != i.

COMMON MISTAKES:
----------------
1. Including correctly placed values in the AND operation.
2. Returning -1 when the array is already sorted.
3. Confusing bitwise AND (&) with logical AND (&&).
4. Sorting the array unnecessarily; the target value at
   every index is already known to be i.
5. Assuming swaps must be performed only between values
   that are directly misplaced together. Intermediate
   swaps can be used to rearrange elements.

WHEN TO USE THIS APPROACH:
--------------------------
Use this technique when:
1. The array is a permutation of [0, n-1].
2. The target sorted position of each value is known.
3. A bitmask must be a subset of the bits shared by every
   element that must move.
4. The problem asks for the maximum common bitmask.

FINAL TAKEAWAY:
---------------
Answer = AND of all misplaced nums[i].
If every element is already in its correct position,
the answer is 0.

============================================================
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = find(nums.begin(), nums.end(), 0) - nums.begin();
        bool increasing = true;
        bool decreasing = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (i - zero + n) % n)
                increasing = false;
            if (nums[i] != (zero - i + n) % n)
                decreasing = false;
        }
        int ans = INT_MAX;
        if (increasing) {
            int rightRotations = (n - zero) % n;
            ans = min(ans, min(zero, rightRotations + 2));
        }
        if (decreasing) {
            int rotations = (n - 1 - zero + n) % n;
            ans = min(ans, 1 + min(rotations, n - rotations));
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 3, 0, 1};
    cout << sol.minOperations(nums) << '\n';
    return 0;
}

/*
============================================================
                    CP NOTEBOOK
============================================================

PROBLEM STATEMENT
-----------------
Given a permutation of integers from 0 to n-1, sort it in
increasing order using only these operations:

1. Reverse the entire array.
2. Rotate left by one position.

Return the minimum number of operations, or -1 if sorting
is impossible.

EXAMPLE
-------
Input:
nums = {2, 3, 0, 1}

Output:
2

Explanation:
Rotate left twice:
{2, 3, 0, 1}
{3, 0, 1, 2}
{0, 1, 2, 3}

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA
----
Use BFS to explore all arrays reachable from the given
permutation. Each operation represents one edge, so the
first time the sorted array is reached gives the minimum
number of operations.

PSEUDO CODE
-----------
1. Put the initial array into a queue with distance 0.
2. Mark the initial array as visited.
3. While the queue is not empty:
   a. Remove the front state.
   b. If it is sorted, return its distance.
   c. Generate its reversed state.
   d. Generate its left-rotated state.
   e. Add each unvisited state with distance + 1.
4. If no solution is found, return -1.

COMPLETE BRUTE FORCE CODE
-------------------------
class SolutionBrute {
public:
    int minOperations(vector<int>& nums) {
        vector<int> target = nums;
        sort(target.begin(), target.end());

        queue<pair<vector<int>, int>> q;
        set<vector<int>> visited;

        q.push({nums, 0});
        visited.insert(nums);

        while (!q.empty()) {
            auto [cur, dist] = q.front();
            q.pop();

            if (cur == target)
                return dist;

            vector<int> rev = cur;
            reverse(rev.begin(), rev.end());

            if (!visited.count(rev)) {
                visited.insert(rev);
                q.push({rev, dist + 1});
            }

            vector<int> rot = cur;
            rotate(rot.begin(), rot.begin() + 1, rot.end());

            if (!visited.count(rot)) {
                visited.insert(rot);
                q.push({rot, dist + 1});
            }
        }

        return -1;
    }
};

TIME COMPLEXITY
---------------
O(n^2) for reachable states, ignoring the additional
overhead of ordered-set comparisons. There are at most
2n distinct states, each requiring O(n) work.

SPACE COMPLEXITY
----------------
O(n^2) to store the visited arrays and queue states.

============================================================
OPTIMAL APPROACH
============================================================

OBSERVATION
-----------
The operations preserve circular order, except that
reversing the array changes its orientation.

Therefore, the input must be one of these forms:
1. A rotation of {0, 1, 2, ..., n-1}.
2. A rotation of {n-1, n-2, ..., 0}.

If neither condition holds, sorting is impossible.

INTUITION
---------
Let zero be the index of element 0.

INCREASING CIRCULAR ORDER:
nums[i] == (i - zero + n) % n

The direct number of left rotations is zero.

The alternative uses a right rotation, implemented with
two reversals and left rotations. The minimum is:

min(zero, rightRotations + 2)

DECREASING CIRCULAR ORDER:
nums[i] == (zero - i + n) % n

Reverse the array and rotate it to the sorted order.
The minimum number of operations is:

1 + min(rotations, n - rotations)

If neither circular-order check passes, return -1.

PSEUDO CODE
-----------
1. Find the index of 0.
2. Check increasing circular order.
3. Check decreasing circular order.
4. If increasing:
   Calculate the minimum cost using rotations.
5. If decreasing:
   Calculate the minimum cost using one reversal
   and the best rotation direction.
6. Return the minimum valid cost, or -1.

COMPLETE OPTIMAL CODE
---------------------
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int zero = find(nums.begin(), nums.end(), 0)
                   - nums.begin();

        bool increasing = true;
        bool decreasing = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (i - zero + n) % n)
                increasing = false;

            if (nums[i] != (zero - i + n) % n)
                decreasing = false;
        }

        int ans = INT_MAX;

        if (increasing) {
            int rightRotations = (n - zero) % n;
            ans = min(ans,
                      min(zero, rightRotations + 2));
        }

        if (decreasing) {
            int rotations = (n - 1 - zero + n) % n;
            ans = min(ans,
                      1 + min(rotations, n - rotations));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

TIME COMPLEXITY
---------------
O(n)

Finding zero takes O(n), and checking both circular
orders takes O(n).

SPACE COMPLEXITY
----------------
O(1) auxiliary space.

============================================================
DRY RUN
============================================================

Input:
nums = {2, 3, 0, 1}
n = 4

Step 1:
Index of zero = 2

Step 2:
Check increasing circular order.

Expected values:
(i - 2 + 4) % 4

i = 0 -> 2
i = 1 -> 3
i = 2 -> 0
i = 3 -> 1

Matches nums, so increasing = true.

Step 3:
Direct left rotations = zero = 2

Alternative right rotations:
(4 - 2) % 4 = 2

Alternative cost = 2 + 2 = 4

Best increasing-order cost = min(2, 4) = 2

Step 4:
The decreasing-order check fails.

Final answer = 2

============================================================
INTERVIEW NOTES
============================================================

PATTERN
-------
Permutation + restricted operations + circular ordering.

KEY OBSERVATION
---------------
Rotations preserve circular order. Reversal changes
the orientation. Only rotations of the sorted sequence
or its reverse can reach the target.

COMMON MISTAKES
---------------
1. Using arbitrary swaps, which are not permitted.
2. Accessing nums[i - 1] when i = 0.
3. Assuming every permutation is reachable.
4. Forgetting that reversal costs one operation.
5. Ignoring the alternative direction of rotation.
6. Returning a default answer without checking validity.

WHEN TO USE THIS APPROACH
-------------------------
Use this approach when operations consist of rotations
and reversal, and the target is a sorted permutation.
Look for invariant circular order before simulating
individual operations.

============================================================
*/
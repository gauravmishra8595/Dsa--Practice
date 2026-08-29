#include <bits/stdc++.h>
using namespace std;

// ==================== OPTIMAL SOLUTION ====================

class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> arr;

        // {value, original index}
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by value
        sort(arr.begin(), arr.end());

        vector<int> result(n);

        int start = 0;

        while (start < n) {
            int end = start;

            // Find connected group
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            // Collect original indices
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            // Smallest index gets smallest value
            sort(indices.begin(), indices.end());

            for (int i = 0; i < (int)indices.size(); i++) {
                result[indices[i]] = arr[start + i].first;
            }

            start = end + 1;
        }

        return result;
    }
};


// ==================== FOR VS CODE TESTING ====================

int main() {
    Solution sol;

    vector<int> nums = {1, 5, 3, 9, 8};
    int limit = 2;

    vector<int> ans = sol.lexicographicallySmallestArray(nums, limit);

    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}


/*
================================================================================
                    LEETCODE 2948
        Lexicographically Smallest Array by Swapping Elements
================================================================================

PROBLEM STATEMENT
-----------------
You are given an array nums and an integer limit.

You may swap nums[i] and nums[j] if:

    |nums[i] - nums[j]| <= limit

You can perform the operation any number of times.

Return the lexicographically smallest array that can be obtained.

IMPORTANT:
The condition depends on VALUES, not indices.


EXAMPLE
-------
Input:
    nums = [1, 5, 3, 9, 8]
    limit = 2

Output:
    [1, 3, 5, 8, 9]


BRUTE FORCE APPROACH
--------------------

Idea:
-----
Try every possible valid swap and explore all reachable arrays.

Keep track of the lexicographically smallest array found.

This works only for small inputs because the number of possible
arrays can become factorial.


Pseudo Code:
------------
function DFS(nums):

    update answer if nums is lexicographically smaller

    if nums already visited:
        return

    mark nums as visited

    for every pair (i, j):

        if abs(nums[i] - nums[j]) <= limit:

            swap(nums[i], nums[j])

            DFS(nums)

            swap(nums[i], nums[j]) back


Complete Brute Force Code:
--------------------------

vector<int> best;
set<vector<int>> visited;
int limit;

void dfs(vector<int>& nums) {

    if (nums < best) {
        best = nums;
    }

    if (visited.count(nums)) {
        return;
    }

    visited.insert(nums);

    int n = nums.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (abs(nums[i] - nums[j]) <= limit) {

                swap(nums[i], nums[j]);

                dfs(nums);

                swap(nums[i], nums[j]);
            }
        }
    }
}

vector<int> bruteForce(vector<int> nums, int lim) {

    limit = lim;
    best = nums;
    visited.clear();

    dfs(nums);

    return best;
}


Time Complexity:
----------------
Approximately:

    O(n! * n^2)

Space Complexity:
-----------------
O(n! * n)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
Sort the elements by VALUE while remembering their original indices.

Example:

    nums = [1, 5, 3, 9, 8]
    limit = 2

Store:

    (1, 0)
    (5, 1)
    (3, 2)
    (9, 3)
    (8, 4)

After sorting:

    (1, 0)
    (3, 2)
    (5, 1)
    (8, 4)
    (9, 3)


Intuition:
----------
If consecutive sorted values differ by at most limit, they belong
to the same connected group.

For example:

    1 -> 3 -> 5

because:

    3 - 1 <= 2
    5 - 3 <= 2

Therefore, 1, 3, and 5 can be rearranged among their original
positions.

We then:

    1. Collect all original indices of the group.
    2. Sort those indices.
    3. Assign the smallest values to the smallest indices.

This gives the lexicographically smallest result.


Pseudo Code:
------------
Create pairs:

    (value, original_index)

Sort pairs by value.

start = 0

while start < n:

    Find end while:

        arr[end + 1].value - arr[end].value <= limit

    Collect original indices from start to end.

    Sort those indices.

    Assign smallest values to smallest indices.

    start = end + 1


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<int> lexicographicallySmallestArray(
        vector<int>& nums, int limit) {

        int n = nums.size();

        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        sort(arr.begin(), arr.end());

        vector<int> result(n);

        int start = 0;

        while (start < n) {

            int end = start;

            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            sort(indices.begin(), indices.end());

            for (int i = 0; i < (int)indices.size(); i++) {
                result[indices[i]] = arr[start + i].first;
            }

            start = end + 1;
        }

        return result;
    }
};


Time Complexity:
----------------
Sorting values:

    O(n log n)

Sorting indices:

    O(n log n)

Overall:

    O(n log n)


Space Complexity:
-----------------
O(n)


================================================================================
DRY RUN
================================================================================

nums  = [1, 5, 3, 9, 8]
limit = 2


Step 1:
-------
Store value + original index:

    (1, 0)
    (5, 1)
    (3, 2)
    (9, 3)
    (8, 4)


Step 2:
-------
Sort by value:

    (1, 0)
    (3, 2)
    (5, 1)
    (8, 4)
    (9, 3)


Step 3:
-------
Find groups.

Group 1:

    1, 3, 5

because:

    3 - 1 = 2 <= limit
    5 - 3 = 2 <= limit

Original indices:

    [0, 2, 1]

Sort indices:

    [0, 1, 2]

Assign:

    index 0 -> 1
    index 1 -> 3
    index 2 -> 5


Group 2:

    8, 9

because:

    9 - 8 = 1 <= limit

Original indices:

    [4, 3]

Sort:

    [3, 4]

Assign:

    index 3 -> 8
    index 4 -> 9


Final Answer:

    [1, 3, 5, 8, 9]


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Sorting + Grouping + Original Indices


Key Observation:
----------------
Think in terms of CONNECTED GROUPS, not individual swaps.

If:

    a can swap with b
    b can swap with c

then a, b, c can effectively be rearranged within the same group.


Common Mistakes:
----------------

1. Checking only adjacent original indices.

2. Forgetting absolute difference:

       abs(nums[i] - nums[j])

3. Thinking only direct swaps matter.

4. Missing transitivity.

   Example:

       [1, 3, 5]
       limit = 2

   1 cannot directly swap with 5.

   But:

       1 <-> 3 <-> 5

   So all three belong to the same group.

5. Forgetting original indices after sorting.

6. Not sorting the original indices inside each group.

7. Returning indices instead of the resulting array.


When to Use This Approach:
--------------------------
Use this pattern when:

    - Swapping depends on element values.
    - There is a threshold/limit for swapping.
    - Multiple swaps create connected components.
    - We need the lexicographically smallest arrangement.

Think:

    SORT VALUES
          ↓
    FIND GROUPS
          ↓
    SORT ORIGINAL INDICES
          ↓
    ASSIGN SMALLEST VALUES
          ↓
    ANSWER


FINAL TEMPLATE
--------------

    1. Store {value, original_index}.
    2. Sort by value.
    3. Find connected groups.
    4. Collect original indices of each group.
    5. Sort those indices.
    6. Assign sorted values to sorted indices.
    7. Return result.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int getDigitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by digit sum, then by numerical value
        sort(arr.begin(), arr.end(), [&](const auto& a, const auto& b) {
            int sumA = getDigitSum(a.first);
            int sumB = getDigitSum(b.first);

            if (sumA != sumB) {
                return sumA < sumB;
            }
            return a.first < b.first;
        });

        // Map each original index to its sorted position
        vector<int> position(n);
        for (int i = 0; i < n; i++) {
            position[arr[i].second] = i;
        }

        // Count cycles in the permutation
        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || position[i] == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = position[j];
                cycleSize++;
            }

            if (cycleSize > 1) {
                swaps += cycleSize - 1;
            }
        }

        return swaps;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {37, 100};
    cout << sol.minSwaps(nums) << '\n';

    return 0;
}

/*
============================================================
                    CP NOTEBOOK
============================================================

PROBLEM STATEMENT
-----------------
Given an integer array nums, sort its elements by:
1. Increasing digit sum.
2. Increasing numerical value if digit sums are equal.

Return the minimum number of swaps needed to transform
the original array into this sorted order.

EXAMPLE
-------
Input:
nums = [37, 100]

Digit sums:
37  -> 10
100 -> 1

Sorted array:
[100, 37]

Output:
1

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA
----
Generate the required sorted array. Use BFS to explore all
arrays reachable by one swap, stopping when the target
array is reached for the first time.

PSEUDO CODE
-----------
1. Create the target array using the required comparator.
2. Put the original array into a BFS queue.
3. For each state, try every possible pair of indices.
4. Swap the selected elements to create a new state.
5. If the target is reached, return the swap count.
6. Track visited states to avoid repetition.

COMPLETE BRUTE FORCE CODE
-------------------------
int bruteForce(vector<int> nums) {
    auto digitSum = [](int x) {
        int s = 0;
        while (x > 0) {
            s += x % 10;
            x /= 10;
        }
        return s;
    };

    auto cmp = [&](int a, int b) {
        int sa = digitSum(a), sb = digitSum(b);
        if (sa != sb) return sa < sb;
        return a < b;
    };

    vector<int> target = nums;
    sort(target.begin(), target.end(), cmp);

    queue<pair<vector<int>, int>> q;
    set<vector<int>> visited;

    q.push({nums, 0});
    visited.insert(nums);

    while (!q.empty()) {
        auto [cur, steps] = q.front();
        q.pop();

        if (cur == target) return steps;

        int n = cur.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                vector<int> next = cur;
                swap(next[i], next[j]);

                if (!visited.count(next)) {
                    visited.insert(next);
                    q.push({next, steps + 1});
                }
            }
        }
    }

    return 0;
}

TIME COMPLEXITY
---------------
O(n! * n^2) in the worst case, ignoring hashing and
comparison overhead. The number of distinct states can
be as large as n!.

SPACE COMPLEXITY
----------------
O(n * n!) for storing states and the BFS queue.

Note: This approach is only for conceptual understanding.
It is far too expensive for typical constraints.

============================================================
OPTIMAL APPROACH
============================================================

OBSERVATION
-----------
The target ordering is determined by digit sum first and
numerical value second.

Once each element's target position is known, the problem
becomes finding the minimum swaps needed to realize a
permutation.

INTUITION
---------
Attach each element's original index before sorting.

After sorting, every original index maps to one target
position. This mapping forms a permutation.

A cycle of length k requires exactly k - 1 swaps.
Therefore, sum cycleSize - 1 across all nontrivial cycles.

Tracking original indices also handles duplicate values
correctly because equal values at different positions
remain distinguishable.

PSEUDO CODE
-----------
1. Store (value, originalIndex) for each element.
2. Sort pairs by digit sum, then by value.
3. Build position[originalIndex] = sortedPosition.
4. Mark all positions as unvisited.
5. For each unvisited position:
   a. Follow the permutation to form a cycle.
   b. Mark each visited position.
   c. Add cycleSize - 1 if cycleSize > 1.
6. Return the total swaps.

COMPLETE OPTIMAL CODE
---------------------
int minSwaps(vector<int>& nums) {
    int n = nums.size();

    auto digitSum = [](int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    };

    vector<pair<int, int>> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back({nums[i], i});
    }

    sort(arr.begin(), arr.end(), [&](auto& a, auto& b) {
        int sa = digitSum(a.first);
        int sb = digitSum(b.first);

        if (sa != sb) return sa < sb;
        return a.first < b.first;
    });

    vector<int> position(n);
    for (int i = 0; i < n; i++) {
        position[arr[i].second] = i;
    }

    vector<bool> visited(n, false);
    int swaps = 0;

    for (int i = 0; i < n; i++) {
        if (visited[i] || position[i] == i)
            continue;

        int cycleSize = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = true;
            j = position[j];
            cycleSize++;
        }

        if (cycleSize > 1)
            swaps += cycleSize - 1;
    }

    return swaps;
}

TIME COMPLEXITY
---------------
O(n log n + n * D), where D is the maximum number
of digits in an element. This simplifies to O(n log n)
for bounded-width integers.

SPACE COMPLEXITY
----------------
O(n) for the sorted pairs, permutation, and visited array.

============================================================
DRY RUN
============================================================

Input:
nums = [37, 100, 22]

Digit sums:
37  -> 10
100 -> 1
22  -> 4

Sorted order:
[100, 22, 37]

Original indices:
37  -> 0
100 -> 1
22  -> 2

Sorted pairs (value, originalIndex):
[(100, 1), (22, 2), (37, 0)]

Permutation:
position[0] = 2
position[1] = 0
position[2] = 1

Cycles:
0 -> 2 -> 1 -> 0

Cycle size = 3
Swaps needed = 3 - 1 = 2

Output:
2

============================================================
INTERVIEW NOTES
============================================================

PATTERN
-------
Sorting with a custom comparator + permutation cycles.

KEY OBSERVATION
---------------
For a permutation cycle of length k, the minimum number
of swaps needed is k - 1.

COMMON MISTAKES
---------------
1. Sorting only by numerical value.
2. Forgetting the digit-sum tie-breaker.
3. Modifying the original array before tracking positions.
4. Mapping value -> index when duplicate values exist.
5. Counting misplaced elements instead of permutation cycles.
6. Using a comparator that does not define a strict ordering.

WHEN TO USE THIS APPROACH
-------------------------
Use cycle decomposition when:
- Every element has a unique identity or original index.
- Each element has a known target position.
- Any pair of elements can be swapped.
- You need the minimum swaps to reach the target arrangement.

============================================================
*/
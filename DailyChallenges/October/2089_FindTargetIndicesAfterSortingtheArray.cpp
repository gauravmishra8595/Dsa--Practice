
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        vector<int> ans;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (nums[i] == target) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 5, 2, 3};
    int target = 2;

    vector<int> result = sol.targetIndices(nums, target);

    cout << "[";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i];
        if (i + 1 < (int)result.size()) cout << ", ";
    }
    cout << "]\n";

    return 0;
}

/*
============================================================
                    CP NOTEBOOK
       Find Target Indices After Sorting the Array
============================================================

1. PROBLEM STATEMENT
--------------------
Given an integer array nums and an integer target:
1. Sort nums in non-decreasing order.
2. Return all indices where nums[index] == target.
3. Return indices in increasing order.

Example:
Input:
nums = [1, 2, 5, 2, 3]
target = 2

Output:
[1, 2]

Explanation:
Sorted array = [1, 2, 2, 3, 5]
Target 2 occurs at indices 1 and 2.

------------------------------------------------------------
2. BRUTE FORCE APPROACH
------------------------------------------------------------

Idea:
Check every possible index after sorting the array.
Collect each index whose value equals target.

Pseudo Code:
1. Sort nums.
2. Create an empty answer vector.
3. Traverse nums from index 0 to n - 1.
4. If nums[i] == target, add i to answer.
5. Return answer.

Complete Brute Force Code:

    vector<int> targetIndicesBrute(vector<int>& nums,
                                   int target) {
        sort(nums.begin(), nums.end());

        vector<int> ans;

        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] == target) {
                ans.push_back(i);
            }
        }

        return ans;
    }

Time Complexity:
O(n log n) for sorting + O(n) for traversal
= O(n log n)

Space Complexity:
O(k) auxiliary result space, where k is the number
of matching indices. Sorting may use additional stack
space depending on the implementation.

Note:
This is the straightforward sorting-and-searching
approach. The optimal approach below avoids scanning
the entire array after sorting.

------------------------------------------------------------
3. OPTIMAL APPROACH
------------------------------------------------------------

Observation:
After sorting, all occurrences of target are adjacent.

Intuition:
Use binary search to find:
- The first position where nums[i] >= target.
- The first position where nums[i] > target.

Every index between these two positions contains target.

The standard lower_bound() and upper_bound() functions
find these boundaries in logarithmic time after sorting.

Pseudo Code:
1. Sort nums.
2. left = lower_bound(nums, target).
3. right = upper_bound(nums, target).
4. For each index i from left to right - 1:
      Add i to answer.
5. Return answer.

Complete Optimal Code:

    vector<int> targetIndices(vector<int>& nums,
                              int target) {
        sort(nums.begin(), nums.end());

        vector<int> ans;

        int left = lower_bound(
            nums.begin(), nums.end(), target
        ) - nums.begin();

        int right = upper_bound(
            nums.begin(), nums.end(), target
        ) - nums.begin();

        for (int i = left; i < right; i++) {
            ans.push_back(i);
        }

        return ans;
    }

Time Complexity:
Sorting: O(n log n)
Two binary searches: O(log n)
Collecting k indices: O(k)

Total: O(n log n + k) = O(n log n)

Space Complexity:
O(k) for the returned answer, plus sorting-related
implementation overhead.

------------------------------------------------------------
4. DRY RUN
------------------------------------------------------------

Input:
nums = [1, 2, 5, 2, 3]
target = 2

Step 1: Sort the array
nums = [1, 2, 2, 3, 5]

Step 2: Find lower_bound(2)
First index with value >= 2 is index 1.

left = 1

Step 3: Find upper_bound(2)
First index with value > 2 is index 3.

right = 3

Step 4: Collect indices from left to right - 1

i = 1 -> nums[1] = 2 -> ans = [1]
i = 2 -> nums[2] = 2 -> ans = [1, 2]

Step 5: Return answer

Output = [1, 2]

------------------------------------------------------------
5. INTERVIEW NOTES
------------------------------------------------------------

Pattern:
Sorting + Binary Search + Range Extraction

Key Observation:
Equal elements become contiguous after sorting.
Binary search can identify the exact range of target.

Common Mistakes:
1. Writing begins(nums) instead of nums.begin().
2. Returning target instead of the matching index.
3. Returning after the first match.
4. Forgetting to return an empty vector when no match
   exists.
5. Confusing lower_bound() with upper_bound().
6. Forgetting that indices refer to the sorted array.

When to Use This Approach:
- The array must be sorted before finding positions.
- You need the first or last occurrence of a value.
- You need the range of equal elements in a sorted array.
- You want to avoid traversing the entire array to locate
  the boundaries of a target value.

Complexity Comparison:
Sorting + Full Scan: O(n log n)
Sorting + Binary Search: O(n log n + k)

Both have the same overall asymptotic complexity because
sorting dominates. Binary search is useful for locating
the target range efficiently after sorting.

============================================================
*/

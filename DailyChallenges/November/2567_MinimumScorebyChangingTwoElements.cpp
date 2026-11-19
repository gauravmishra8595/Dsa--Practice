#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: O(n) Time, O(1) Extra Space
class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int mn1 = INT_MAX, mn2 = INT_MAX, mn3 = INT_MAX;
        int mx1 = INT_MIN, mx2 = INT_MIN, mx3 = INT_MIN;

        for (int x : nums) {

            // Maintain 3 smallest elements
            if (x <= mn1) {
                mn3 = mn2;
                mn2 = mn1;
                mn1 = x;
            }
            else if (x <= mn2) {
                mn3 = mn2;
                mn2 = x;
            }
            else if (x < mn3) {
                mn3 = x;
            }

            // Maintain 3 largest elements
            if (x >= mx1) {
                mx3 = mx2;
                mx2 = mx1;
                mx1 = x;
            }
            else if (x >= mx2) {
                mx3 = mx2;
                mx2 = x;
            }
            else if (x > mx3) {
                mx3 = x;
            }
        }

        return min({
            mx1 - mn3,
            mx2 - mn2,
            mx3 - mn1
        });
    }
};

int main() {
    Solution sol;

    vector<int> nums = {31, 25, 72, 79, 74, 65};

    cout << sol.minimizeSum(nums) << endl;

    return 0;
}

/*
=========================================================
       LEETCODE 2567 - MINIMUM SCORE BY CHANGING TWO
=========================================================

1. PROBLEM STATEMENT
---------------------------------------------------------
Given an integer array nums, we can change at most
two elements to any values.

Score =
Maximum absolute difference between any two elements
+
Minimum absolute difference between any two elements.

Return the minimum possible score.

---------------------------------------------------------
2. EXAMPLE
---------------------------------------------------------

Input:
nums = [31, 25, 72, 79, 74, 65]

Sorted:
[25, 31, 65, 72, 74, 79]

Output:
14

Explanation:

Change the two smallest elements.

Remaining elements:
[65, 72, 74, 79]

Maximum difference = 79 - 65 = 14
Minimum difference = 0 (we can make two modified
elements equal).

Answer = 14.

=========================================================
3. BRUTE FORCE APPROACH
=========================================================

IDEA:
-----
Sort the array.

Since we can modify at most two elements, there
are only three meaningful possibilities.

Case 1: Modify two largest elements.
Case 2: Modify two smallest elements.
Case 3: Modify one smallest and one largest element.

PSEUDO CODE:
------------
1. Sort the array.
2. Calculate three possible differences:

   Case 1 = nums[n-3] - nums[0]
   Case 2 = nums[n-2] - nums[1]
   Case 3 = nums[n-1] - nums[2]

3. Return the minimum.

COMPLETE BRUTE FORCE CODE:
--------------------------

// LeetCode version

class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int n = nums.size();

        sort(nums.begin(), nums.end());

        return min({
            nums[n-3] - nums[0],
            nums[n-2] - nums[1],
            nums[n-1] - nums[2]
        });
    }
};

TIME COMPLEXITY:
----------------
O(n log n) - Sorting.

SPACE COMPLEXITY:
-----------------
Depends on sorting implementation.

=========================================================
4. OPTIMAL APPROACH
=========================================================

OBSERVATION:
------------
We don't need the entire sorted array.

We only need:
- Three smallest elements.
- Three largest elements.

INTUITION:
----------
Maintain the three smallest and three largest
elements during a single traversal.

Three smallest:
mn1 = Smallest
mn2 = Second smallest
mn3 = Third smallest

Three largest:
mx1 = Largest
mx2 = Second largest
mx3 = Third largest

The three possible differences are:

Case 1 = mx1 - mn3
Case 2 = mx2 - mn2
Case 3 = mx3 - mn1

Return their minimum.

PSEUDO CODE:
------------
1. Initialize three minimum variables with INT_MAX.
2. Initialize three maximum variables with INT_MIN.
3. Traverse the array.
4. Maintain three smallest elements.
5. Maintain three largest elements.
6. Calculate:

   mx1 - mn3
   mx2 - mn2
   mx3 - mn1

7. Return the minimum.

COMPLETE OPTIMAL CODE:
----------------------

// LeetCode version

class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        int mn1 = INT_MAX, mn2 = INT_MAX, mn3 = INT_MAX;
        int mx1 = INT_MIN, mx2 = INT_MIN, mx3 = INT_MIN;

        for (int x : nums) {

            if (x <= mn1) {
                mn3 = mn2;
                mn2 = mn1;
                mn1 = x;
            }
            else if (x <= mn2) {
                mn3 = mn2;
                mn2 = x;
            }
            else if (x < mn3) {
                mn3 = x;
            }

            if (x >= mx1) {
                mx3 = mx2;
                mx2 = mx1;
                mx1 = x;
            }
            else if (x >= mx2) {
                mx3 = mx2;
                mx2 = x;
            }
            else if (x > mx3) {
                mx3 = x;
            }
        }

        return min({
            mx1 - mn3,
            mx2 - mn2,
            mx3 - mn1
        });
    }
};

TIME COMPLEXITY:
----------------
O(n)

Only one traversal of the array.

SPACE COMPLEXITY:
-----------------
O(1)

Only six variables are maintained.

=========================================================
5. DRY RUN
=========================================================

Input:
[31, 25, 72, 79, 74, 65]

Sorted order:
[25, 31, 65, 72, 74, 79]

Three smallest:
mn1 = 25
mn2 = 31
mn3 = 65

Three largest:
mx1 = 79
mx2 = 74
mx3 = 72

Calculate:

Case 1:
mx1 - mn3
= 79 - 65
= 14

Case 2:
mx2 - mn2
= 74 - 31
= 43

Case 3:
mx3 - mn1
= 72 - 25
= 47

Answer:
min(14, 43, 47) = 14

=========================================================
6. INTERVIEW NOTES
=========================================================

PATTERN:
--------
Array + Maintaining K Smallest and Largest Elements.

KEY OBSERVATION:
----------------
When only a fixed number of smallest and largest
elements matter, sorting the complete array
is unnecessary.

COMMON MISTAKES:
----------------
1. Incorrectly shifting minimum values.
2. Incorrectly shifting maximum values.
3. Confusing ascending and descending order.
4. Mishandling duplicate elements.
5. Pairing the wrong smallest and largest elements.

WHEN TO USE THIS APPROACH:
--------------------------
1. When only K smallest/largest elements are needed.
2. When complete sorting is unnecessary.
3. When K is fixed and small.
4. When O(n) time and O(1) extra space are desired.

FINAL REVISION:
---------------
Sorting:
O(n log n) time.

Single traversal:
O(n) time and O(1) extra space.

Key idea:
Maintain only the relevant extreme elements instead
of sorting the entire array.

=========================================================
*/

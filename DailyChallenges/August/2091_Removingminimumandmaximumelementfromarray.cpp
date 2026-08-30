#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minElidx = min_element(nums.begin(), nums.end()) - nums.begin();
        int maxElidx = max_element(nums.begin(), nums.end()) - nums.begin();

        int left = min(minElidx, maxElidx);
        int right = max(minElidx, maxElidx);

        return min({left + 1 + n - right, right + 1, n - left});
    }
};

int main() {
    vector<int> nums = {2, 10, 7, 5, 1, 8};

    Solution sol;
    cout << sol.minimumDeletions(nums) << endl;

    return 0;
}

/*
================================================================================
                    LEETCODE 2091 - MINIMUM DELETIONS
================================================================================

Problem Statement:
------------------
Given an array nums, remove the minimum number of elements from the array
such that both the minimum and maximum elements are removed.

In one operation, we can remove an element from either:
    1. The beginning (front)
    2. The end (back)

Return the minimum number of deletions required.


Example:
--------
Input:
    nums = [2, 10, 7, 5, 1, 8]

Minimum element = 1, index = 4
Maximum element = 10, index = 1

Possible strategies:

1. Remove both from the left:
       Delete indices 0 through 4
       Deletions = 5

2. Remove both from the right:
       Delete indices 1 through 5
       Deletions = 5

3. Remove from both sides:
       Delete indices 0 through 1 from left
       Delete indices 4 through 5 from right
       Deletions = 4

Answer = 4


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Try every possible number of deletions from the left and right.

After removing:
    L elements from the left
    R elements from the right

The remaining array is:

    nums[L ... n-R-1]

Check whether both the minimum and maximum elements have been removed.

Keep track of the minimum valid number of deletions.


Pseudo Code:
------------
1. Find the indices of minimum and maximum.
2. Try every possible L from 0 to n.
3. Try every possible R from 0 to n-L.
4. Check if both min and max are outside the remaining range.
5. If yes, update the answer.
6. Return the minimum answer.


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIdx =
            min_element(nums.begin(), nums.end()) - nums.begin();

        int maxIdx =
            max_element(nums.begin(), nums.end()) - nums.begin();

        int ans = n;

        for (int L = 0; L <= n; L++) {
            for (int R = 0; R <= n - L; R++) {

                bool minRemoved =
                    minIdx < L || minIdx >= n - R;

                bool maxRemoved =
                    maxIdx < L || maxIdx >= n - R;

                if (minRemoved && maxRemoved) {
                    ans = min(ans, L + R);
                }
            }
        }

        return ans;
    }
};


Time Complexity:
----------------
O(n^2)


Space Complexity:
-----------------
O(1)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
Only the positions of the minimum and maximum elements matter.

Let:

    minIdx = index of minimum element
    maxIdx = index of maximum element

Normalize their positions:

    left  = min(minIdx, maxIdx)
    right = max(minIdx, maxIdx)

Now there are only 3 possible strategies.


Intuition:
----------
CASE 1: Remove both elements from the LEFT

The farther element is at index 'right'.

Therefore:

    deletions = right + 1


CASE 2: Remove both elements from the RIGHT

The farther element from the right is at index 'left'.

Therefore:

    deletions = n - left


CASE 3: Remove one from LEFT and one from RIGHT

Remove everything from index 0 to left:

    left + 1

Remove everything from right to n-1:

    n - right

Total:

    left + 1 + n - right


Take the minimum of these 3 possibilities.


Pseudo Code:
------------
1. Find minIdx.
2. Find maxIdx.
3. Set:
       left  = min(minIdx, maxIdx)
       right = max(minIdx, maxIdx)
4. Calculate:
       option1 = right + 1
       option2 = n - left
       option3 = left + 1 + n - right
5. Return the minimum.


Complete Optimal Code:
----------------------

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minElidx =
            min_element(nums.begin(), nums.end()) - nums.begin();

        int maxElidx =
            max_element(nums.begin(), nums.end()) - nums.begin();

        int left = min(minElidx, maxElidx);
        int right = max(minElidx, maxElidx);

        return min({
            left + 1 + n - right,
            right + 1,
            n - left
        });
    }
};


Time Complexity:
----------------
O(n)

Finding minimum = O(n)
Finding maximum = O(n)

Overall = O(n)


Space Complexity:
-----------------
O(1)


================================================================================
DRY RUN
================================================================================

Example:

nums = [2, 10, 7, 5, 1, 8]
        0   1  2  3  4  5

Minimum = 1
minIdx = 4

Maximum = 10
maxIdx = 1


Step 1:
-------
left = min(4, 1) = 1

right = max(4, 1) = 4


Step 2:
-------
Remove both from LEFT:

    right + 1
    = 4 + 1
    = 5


Step 3:
-------
Remove both from RIGHT:

    n - left
    = 6 - 1
    = 5


Step 4:
-------
Remove from BOTH SIDES:

    left + 1 + n - right
    = 1 + 1 + 6 - 4
    = 4


Step 5:
-------
Take minimum:

    min(5, 5, 4)
    = 4


Answer:
    4


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Array + Greedy + Index Positions


Key Observation:
----------------
Only the indices of the minimum and maximum elements matter.

There are exactly 3 useful possibilities:

    1. Remove both from the left.
    2. Remove both from the right.
    3. Remove one from the left and one from the right.

Take the minimum of these.


Common Mistakes:
----------------
1. Actually erasing elements from the vector.

   This is unnecessary and can make the solution slower.

2. Forgetting the +1 when deleting from the left.

   If an element is at index 4:

       elements to remove from left = 5

3. Forgetting the case where we remove from both sides.

4. Confusing the minimum/maximum VALUES with their INDICES.

5. Using O(n^2) simulation instead of checking the 3 cases.


When to Use This Approach:
--------------------------
Use this pattern when:

    - You can remove elements only from the front/back.
    - You need to remove one or more specific elements.
    - The required elements' positions determine the answer.
    - The possible strategies can be reduced to left, right, or both.


Final Formula:
--------------

left  = min(minIdx, maxIdx)
right = max(minIdx, maxIdx)

answer = min({
    right + 1,
    n - left,
    left + 1 + n - right
});


Complexity:
-----------

Time  = O(n)
Space = O(1)

================================================================================
*/

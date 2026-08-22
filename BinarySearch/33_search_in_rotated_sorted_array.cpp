#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target)
                return mid;

            // Left half is sorted
            if (nums[low] <= nums[mid])
            {
                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }

            // Right half is sorted
            else
            {
                if (nums[mid] < target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }

        return -1;
    }
};

int main()
{
    int n, target;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    cout << "Enter target: ";
    cin >> target;

    Solution obj;

    cout << "Answer: " << obj.search(nums, target) << endl;

    return 0;
}

/*
===============================================================================
                LEETCODE 33 - SEARCH IN ROTATED SORTED ARRAY
===============================================================================

Problem Statement:
------------------
You are given an integer array nums sorted in ascending order with distinct
values.

Before being passed to the function, nums is possibly rotated at an unknown
index.

For example:

    Original:
    [0, 1, 2, 4, 5, 6, 7]

    Rotated:
    [4, 5, 6, 7, 0, 1, 2]

Given the rotated array and an integer target, return the index of target if
it exists.

Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity.


Example:
--------
Input:

    nums = [4,5,6,7,0,1,2]
    target = 0

Output:

    4


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Simply traverse the array from left to right.

If nums[i] == target, return i.

If the target is not found, return -1.


Pseudo Code:
------------
    for i = 0 to n - 1:

        if nums[i] == target:
            return i

    return -1


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int search(vector<int>& nums, int target) {

        for (int i = 0; i < nums.size(); i++) {

            if (nums[i] == target)
                return i;
        }

        return -1;
    }
};


Time Complexity:
----------------
O(n)

In the worst case, we check every element.


Space Complexity:
-----------------
O(1)


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
Although the array is rotated, at least ONE half of the current search space
is always sorted.

For example:

    [4, 5, 6, 7, 0, 1, 2]
     L     M        R

The left half:

    [4, 5, 6, 7]

is sorted.

Or in another situation, the right half may be sorted.


Intuition:
----------
At every step:

1. Find mid.

2. Check if nums[mid] == target.

3. Determine which half is sorted.

If:

    nums[low] <= nums[mid]

then the LEFT half is sorted.

Now check whether target lies inside this sorted range.

If:

    nums[low] <= target && target < nums[mid]

then target is in the left half.

Therefore:

    high = mid - 1

Otherwise:

    low = mid + 1


If the left half is not sorted, then the RIGHT half must be sorted.

Check:

    nums[mid] < target && target <= nums[high]

If target lies in the right sorted half:

    low = mid + 1

Otherwise:

    high = mid - 1


Pseudo Code:
------------
    low = 0
    high = n - 1

    while low <= high:

        mid = low + (high - low) / 2

        if nums[mid] == target:
            return mid

        if nums[low] <= nums[mid]:

            Left half is sorted

            if nums[low] <= target AND target < nums[mid]:
                high = mid - 1
            else:
                low = mid + 1

        else:

            Right half is sorted

            if nums[mid] < target AND target <= nums[high]:
                low = mid + 1
            else:
                high = mid - 1

    return -1


Complete Optimal Code:
----------------------

class Solution {
public:
    int search(vector<int>& nums, int target) {

        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (nums[mid] == target)
                return mid;

            Left half is sorted
            if (nums[low] <= nums[mid]) {

                if (nums[low] <= target && target < nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }

            Right half is sorted
            else {

                if (nums[mid] < target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }

        return -1;
    }
};


Time Complexity:
----------------
O(log n)

At every iteration, approximately half of the search space is eliminated.


Space Complexity:
-----------------
O(1)

Only a few variables are used.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Example:

    nums = [4, 5, 6, 7, 0, 1, 2]
    target = 0


Initial:

    low = 0
    high = 6


Iteration 1:

    mid = 0 + (6 - 0) / 2
        = 3

    nums[mid] = 7

Check:

    nums[low] = 4
    nums[mid] = 7

Since:

    4 <= 7

the LEFT half is sorted:

    [4, 5, 6, 7]


Does target 0 lie between 4 and 7?

    4 <= 0 <= 7

No.

Therefore target must be in the right half.

    low = mid + 1
        = 4


Now:

    low = 4
    high = 6


Iteration 2:

    mid = 4 + (6 - 4) / 2
        = 5

    nums[mid] = 1

Check:

    nums[low] = 0
    nums[mid] = 1

Since:

    0 <= 1

the LEFT half is sorted:

    [0, 1]


Does target 0 lie in this range?

    0 <= 0 < 1

Yes.

Therefore:

    high = mid - 1
        = 4


Now:

    low = 4
    high = 4


Iteration 3:

    mid = 4

    nums[4] = 0

Target found.

Return:

    4


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Modified Binary Search


Key Observation:
----------------
In a rotated sorted array, at least one of the two halves is always sorted.

Use this fact to decide which half can contain the target.


Most Important Logic:
---------------------

    if (nums[low] <= nums[mid])

        Left half is sorted.

    else

        Right half is sorted.


Then check whether target lies inside the sorted half.


Common Mistakes:
----------------

1. Using normal binary search directly.

   Normal binary search assumes the entire array is sorted.

   Here, the array is rotated, so we must first identify the sorted half.


2. Forgetting to check:

       nums[mid] == target

   before deciding which half to search.


3. Incorrect boundary conditions.

   For the left sorted half:

       nums[low] <= target && target < nums[mid]

   For the right sorted half:

       nums[mid] < target && target <= nums[high]


4. Using:

       low = mid

   or:

       high = mid

   which can cause an infinite loop.

   Correct:

       low = mid + 1
       high = mid - 1


5. Forgetting that this problem has DISTINCT values.

   Because all values are distinct, determining the sorted half is
   straightforward.


When to Use This Approach:
--------------------------
Use this pattern when:

- The array was originally sorted.
- The array has been rotated.
- Values are distinct.
- You need O(log n).
- You need to search for a target.

Think:

    "Rotated Sorted Array"

Then immediately think:

    "At least one half is sorted."

===============================================================================
*/

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

            if (nums[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return -1;
    }
};

int main()
{
    Solution sol;

    int n, target;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    cin >> target;

    cout << sol.search(nums, target) << '\n';

    return 0;
}

/*
===============================================================================
                         LEETCODE 704
                         BINARY SEARCH
===============================================================================

Problem Statement:
------------------
Given an array of integers nums which is sorted in ascending order, and an
integer target, write a function to search target in nums.

If target exists, return its index.

If target does not exist, return -1.

You must write an algorithm with O(log n) runtime complexity.


Example:
--------
Input:
    nums = [-1, 0, 3, 5, 9, 12]
    target = 9

Output:
    4

Explanation:
    nums[4] = 9


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Traverse every element from left to right.

If nums[i] == target, return i.

If we reach the end without finding target, return -1.


Pseudo Code:
------------
function search(nums, target):

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

In the worst case, every element is checked.


Space Complexity:
-----------------
O(1)

No extra space is used.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
The array is sorted.

Therefore, instead of checking every element, we can check the middle
element and eliminate half of the search space at every step.


Intuition:
----------
Suppose:

    nums[mid] < target

Since the array is sorted, everything to the left of mid is also smaller
than target.

Therefore, we can ignore the left half:

    low = mid + 1


Similarly, if:

    nums[mid] > target

then everything to the right of mid is greater than target.

Therefore:

    high = mid - 1


If:

    nums[mid] == target

we found the answer.


Pseudo Code:
------------
function search(nums, target):

    low = 0
    high = n - 1

    while low <= high:

        mid = low + (high - low) / 2

        if nums[mid] == target:
            return mid

        else if nums[mid] < target:
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

            if (nums[mid] < target)
                low = mid + 1;

            else
                high = mid - 1;
        }

        return -1;
    }
};


Time Complexity:
----------------
O(log n)

The search space is divided approximately in half after every iteration.


Space Complexity:
-----------------
O(1)

Only low, high and mid are used.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Example:

    nums = [-1, 0, 3, 5, 9, 12]
    target = 9


Initial:

    low = 0
    high = 5


Iteration 1:

    mid = 0 + (5 - 0) / 2
        = 2

    nums[mid] = nums[2]
              = 3

Compare:

    3 < 9

Target is on the right.

    low = mid + 1
        = 3


Iteration 2:

    low = 3
    high = 5

    mid = 3 + (5 - 3) / 2
        = 4

    nums[4] = 9

Therefore:

    nums[mid] == target

Return:

    4


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Binary Search


Key Observation:
----------------
The array is sorted.

Whenever the array is sorted and you need to search for a value, think about
Binary Search.

The three important cases are:

    nums[mid] == target
        -> Answer found

    nums[mid] < target
        -> Search right half

    nums[mid] > target
        -> Search left half


Common Mistakes:
----------------
1. Using:

       mid = (low + high) / 2

   Prefer:

       mid = low + (high - low) / 2

   because it avoids integer overflow.


2. Incorrectly updating low:

       low = mid

   Correct:

       low = mid + 1


3. Incorrectly updating high:

       high = mid

   Correct:

       high = mid - 1


4. Using the wrong loop condition.

   For this standard binary search:

       while (low <= high)


5. Forgetting to return -1 when target is not found.


When to Use This Approach:
--------------------------
Use Binary Search when:

- The array is sorted.
- You need to find a target efficiently.
- The search space can be divided into two halves.
- O(n) linear search is too slow.

Classic Binary Search Template:

    int low = 0;
    int high = n - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        if (nums[mid] == target)
            return mid;

        if (nums[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;

===============================================================================
*/

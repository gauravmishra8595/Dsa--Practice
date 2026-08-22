#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int low = 0;
        int high = arr.size() - 1;

        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (arr[mid] < arr[mid + 1])
            {
                // We are on the increasing side.
                // Peak is to the right.
                low = mid + 1;
            }
            else
            {
                // We are on the decreasing side or at the peak.
                // Peak is at mid or to the left.
                high = mid;
            }
        }

        return low;
    }
};

int main()
{
    Solution sol;

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << sol.peakIndexInMountainArray(arr) << '\n';

    return 0;
}

/*
===============================================================================
              LEETCODE 852 - PEAK INDEX IN A MOUNTAIN ARRAY
===============================================================================

Problem Statement:
------------------
You are given a mountain array arr.

A mountain array is an array where:

    arr[0] < arr[1] < ... < arr[i]
    arr[i] > arr[i+1] > ... > arr[n-1]

The peak is the element at index i.

Return the index of the peak element.

Example:
--------
Input:
    arr = [0, 2, 1, 0]

Output:
    1

Explanation:
    arr[1] = 2 is greater than both its neighbours.

    0 < 2 > 1 > 0


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Traverse the array from left to right.

The peak is the element where:

    arr[i] > arr[i - 1]
    AND
    arr[i] > arr[i + 1]

Since the array is guaranteed to be a mountain array, the first such
position is the peak.


Pseudo Code:
------------
function peakIndex(arr):

    for i = 1 to n - 2:

        if arr[i] > arr[i - 1] AND arr[i] > arr[i + 1]:
            return i


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {

        for (int i = 1; i < arr.size() - 1; i++) {
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
                return i;
            }
        }

        return -1;
    }
};


Time Complexity:
----------------
O(n)

We may scan almost the entire array.


Space Complexity:
-----------------
O(1)

No extra space is used.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
The mountain array has two parts:

    Increasing part  -> Peak -> Decreasing part

For any index mid:

    If arr[mid] < arr[mid + 1]
        We are on the increasing side.
        Therefore, peak must be on the right.

    If arr[mid] > arr[mid + 1]
        We are on the decreasing side or at the peak.
        Therefore, peak is at mid or on the left.


Intuition:
----------
This structure allows us to eliminate half of the search space at every step.

Use Binary Search.

If:

    arr[mid] < arr[mid + 1]

then the slope is increasing:

        /
       /
      / mid

The peak must be to the right.

So:

    low = mid + 1


Otherwise:

    arr[mid] > arr[mid + 1]

The slope is decreasing:

        \
         \
          \ mid

The peak is either at mid or to the left.

So:

    high = mid


When:

    low == high

we have found the peak index.


Pseudo Code:
------------
function peakIndex(arr):

    low = 0
    high = n - 1

    while low < high:

        mid = low + (high - low) / 2

        if arr[mid] < arr[mid + 1]:

            low = mid + 1

        else:

            high = mid

    return low


Complete Optimal Code:
----------------------

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {

        int low = 0;
        int high = arr.size() - 1;

        while (low < high) {

            int mid = low + (high - low) / 2;

            if (arr[mid] < arr[mid + 1]) {

                Increasing side.
                Peak is to the right.
                low = mid + 1;

            } else {

                Decreasing side or peak.
                Peak is at mid or to the left.
                high = mid;
            }
        }

        return low;
    }
};


Time Complexity:
----------------
O(log n)

Binary search cuts the search space approximately in half every iteration.


Space Complexity:
-----------------
O(1)

Only low, high and mid are used.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Example:

    arr = [0, 2, 1, 0]

Index:
     0  1  2  3

Value:
     0  2  1  0


Initial:

    low = 0
    high = 3


Iteration 1:

    mid = 0 + (3 - 0) / 2
        = 1

Compare:

    arr[1] = 2
    arr[2] = 1

    arr[1] > arr[2]

So we are on the decreasing side.

Therefore:

    high = mid
    high = 1


Now:

    low = 0
    high = 1


Iteration 2:

    mid = 0 + (1 - 0) / 2
        = 0

Compare:

    arr[0] = 0
    arr[1] = 2

    arr[0] < arr[1]

So we are on the increasing side.

Therefore:

    low = mid + 1
    low = 1


Now:

    low = 1
    high = 1

Loop ends.

Answer:

    return low
    return 1


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Binary Search on a Mountain / Bitonic Array


Key Observation:
----------------
Do NOT search for the maximum directly.

Instead, compare:

    arr[mid] and arr[mid + 1]

If:

    arr[mid] < arr[mid + 1]

then we are climbing upward, so the peak is on the right.

If:

    arr[mid] > arr[mid + 1]

then we are descending, so the peak is at mid or on the left.


Common Mistakes:
----------------
1. Using:

       high = mid - 1

   when arr[mid] > arr[mid + 1].

   This can incorrectly remove the peak.

   Correct:

       high = mid


2. Using:

       low = mid

   when arr[mid] < arr[mid + 1].

   This can cause an infinite loop.

   Correct:

       low = mid + 1


3. Using:

       while (low <= high)

   The cleaner approach here is:

       while (low < high)


4. Calculating mid as:

       (low + high) / 2

   It can potentially overflow for very large values.

   Prefer:

       low + (high - low) / 2


5. Forgetting that the problem guarantees a valid mountain array.


When to Use This Approach:
--------------------------
Use this binary search pattern when:

- The array is increasing and then decreasing.
- You need to find the peak.
- The array has a mountain/bitonic structure.
- You need better than O(n) time.
- A comparison with mid and mid + 1 tells you which direction to search.

General Pattern:

    while (low < high) {

        mid = low + (high - low) / 2;

        if (condition says answer is right) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;

===============================================================================
*/

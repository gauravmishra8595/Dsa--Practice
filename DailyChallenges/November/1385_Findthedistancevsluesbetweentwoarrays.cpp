#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());

        int ans = 0;

        for (int num : arr1) {
            auto it = lower_bound(arr2.begin(), arr2.end(), num - d);

            if (it == arr2.end() || *it > num + d) {
                ans++;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> arr1 = {4,5,8};
    vector<int> arr2 = {10,9,1,8};
    int d = 2;

    cout << sol.findTheDistanceValue(arr1, arr2, d) << endl;

    return 0;
}

/*
===========================================================
          LEETCODE 1385 - EASY
       Find the Distance Value Between Two Arrays
===========================================================

PROBLEM STATEMENT:
------------------
Given two integer arrays arr1 and arr2, and an integer d.

Return the distance value between the two arrays.

The distance value is the number of elements arr1[i]
such that there is NO element arr2[j] satisfying:

    abs(arr1[i] - arr2[j]) <= d

In simple words:
Count elements in arr1 whose distance from EVERY
element in arr2 is strictly greater than d.

EXAMPLE:
--------
Input:
arr1 = [4,5,8]
arr2 = [10,9,1,8]
d = 2

Output:
2

Explanation:

For 4:
    |4 - 10| = 6
    |4 - 9|  = 5
    |4 - 1|  = 3
    |4 - 8|  = 4

    All distances > 2.
    Count = 1.

For 5:
    |5 - 1| = 4
    |5 - 8| = 3
    |5 - 9| = 4
    |5 - 10| = 5

    All distances > 2.
    Count = 1.

For 8:
    |8 - 8| = 0 <= 2

    Not counted.

Answer = 2.

===========================================================
BRUTE FORCE APPROACH:
===========================================================

IDEA:
-----
For every element of arr1:
    Check its absolute difference with every element
    of arr2.

If all differences are greater than d:
    Increment answer.

PSEUDO CODE:
------------

ans = 0

for each x in arr1:
    valid = true

    for each y in arr2:
        if abs(x-y) <= d:
            valid = false
            break

    if valid:
        ans++

return ans

COMPLETE BRUTE FORCE CODE:
--------------------------

class SolutionBrute {
public:
    int findTheDistanceValue(
        vector<int>& arr1,
        vector<int>& arr2,
        int d
    ) {
        int ans = 0;

        for (int x : arr1) {
            bool valid = true;

            for (int y : arr2) {
                if (abs(x - y) <= d) {
                    valid = false;
                    break;
                }
            }

            if (valid) ans++;
        }

        return ans;
    }
};

TIME COMPLEXITY:
----------------
O(n * m)

n = arr1.size()
m = arr2.size()

SPACE COMPLEXITY:
-----------------
O(1)

===========================================================
OPTIMAL APPROACH:
===========================================================

OBSERVATION:
------------
For an element x in arr1, we need to check whether
ANY element of arr2 lies inside this range:

    [x-d, x+d]

If an element exists inside this range:
    Do not count x.

Otherwise:
    Count x.

INTUITION:
----------
Sort arr2.

Use binary search (lower_bound) to find the first
element greater than or equal to:

    x - d

There are two possibilities:

CASE 1:
-------
Iterator reaches the end.

No element is >= x-d.
Therefore, no valid element exists in the range.

CASE 2:
-------
The found element is greater than x+d.

The smallest element >= x-d is already greater than
the upper boundary.

Therefore, no element exists inside [x-d, x+d].

In both cases, increment the answer.

PSEUDO CODE:
------------

sort(arr2)

ans = 0

for each x in arr1:

    it = lower_bound(arr2, x-d)

    if it == end OR *it > x+d:
        ans++

return ans

COMPLETE OPTIMAL CODE AGAIN:
----------------------------

class Solution {
public:
    int findTheDistanceValue(
        vector<int>& arr1,
        vector<int>& arr2,
        int d
    ) {
        sort(arr2.begin(), arr2.end());

        int ans = 0;

        for (int x : arr1) {
            auto it = lower_bound(
                arr2.begin(),
                arr2.end(),
                x - d
            );

            if (it == arr2.end() || *it > x + d) {
                ans++;
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
----------------
Sorting arr2:
    O(m log m)

Binary search for every arr1 element:
    O(n log m)

TOTAL:
    O(m log m + n log m)

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space for the algorithm,
excluding sorting implementation overhead.

===========================================================
DRY RUN WITH EXAMPLE:
===========================================================

arr1 = [4,5,8]
arr2 = [10,9,1,8]
d = 2

STEP 1: SORT arr2

arr2 = [1,8,9,10]

STEP 2: CHECK EACH ELEMENT

For x = 4:

    Range = [4-2, 4+2]
          = [2,6]

    lower_bound(arr2, 2) = 8

    8 > 6

    No element exists inside [2,6].
    ans = 1

--------------------------------

For x = 5:

    Range = [5-2, 5+2]
          = [3,7]

    lower_bound(arr2, 3) = 8

    8 > 7

    No element exists inside [3,7].
    ans = 2

--------------------------------

For x = 8:

    Range = [8-2, 8+2]
          = [6,10]

    lower_bound(arr2, 6) = 8

    8 <= 10

    Element exists inside [6,10].
    Do not count.

--------------------------------

FINAL ANSWER:

    2

===========================================================
INTERVIEW NOTES:
===========================================================

PATTERN:
--------
Sorting + Binary Search.

KEY OBSERVATION:
----------------
For every x in arr1, check whether arr2 contains
any element in the range [x-d, x+d].

COMMON MISTAKES:
----------------
1. Using < instead of <= in the distance condition.
2. Forgetting to sort arr2 before lower_bound.
3. Checking only one arbitrary element of arr2.
4. Forgetting the iterator == arr2.end() condition.
5. Using the wrong search boundary.
6. Modifying arr1 unnecessarily.

WHEN TO USE THIS APPROACH:
--------------------------
Use Sorting + Binary Search when:

1. You need to check whether an element exists in a range.
2. The array can be sorted.
3. Multiple independent search queries are performed.
4. You need O(log n) lookup after sorting.

RELATED CONCEPTS:
-----------------
1. Binary Search
2. lower_bound()
3. Sorting
4. Range Queries
5. STL Algorithms

FINAL TAKEAWAY:
---------------
Sort arr2 and use lower_bound to find the first
element >= x-d.

If it does not exist or is greater than x+d,
count the element.

Remember:

    SORT + LOWER_BOUND + RANGE CHECK

===========================================================
*/

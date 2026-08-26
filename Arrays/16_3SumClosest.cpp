#include <bits/stdc++.h>
using namespace std;



class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        int n = nums.size();

        int closestSum = 100000;

        sort(nums.begin(), nums.end());

        for (int k = 0; k <= n - 3; k++)
        {
            int i = k + 1;
            int j = n - 1;

            while (i < j)
            {
                int sum = nums[k] + nums[i] + nums[j];

                if (abs(target - sum) < abs(target - closestSum))
                {
                    closestSum = sum;
                }

                if (sum < target)
                {
                    i++;
                }
                else
                {
                    j--;
                }
            }
        }

        return closestSum;
    }
};

int main()
{
    int n, target;

    cin >> n >> target;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    Solution sol;

    cout << sol.threeSumClosest(nums, target) << '\n';

    return 0;
}

/*
============================================================
              LEETCODE 16 - 3SUM CLOSEST
============================================================

Problem Statement:
------------------
Given an integer array nums of length n and an integer target,
find three integers in nums such that the sum is closest to
target.

Return the sum of the three integers.

You may assume that each input has exactly one solution.


Example:
--------
Input:
    nums = [-1, 2, 1, -4]
    target = 1

Output:
    2

Explanation:

Possible sums:

    -1 + 2 + 1  = 2
    -1 + 2 - 4  = -3
    -1 + 1 - 4  = -4
     2 + 1 - 4  = -1

The closest sum to target 1 is:

    2

Because:

    |2 - 1| = 1


============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
Try every possible combination of three elements.

For every:

    i < j < k

calculate their sum and check whether it is closer to target
than the current closest sum.


Pseudo Code:
------------
closest = first three elements' sum

for i = 0 to n-3:
    for j = i+1 to n-2:
        for k = j+1 to n-1:

            sum = nums[i] + nums[j] + nums[k]

            if abs(target - sum) < abs(target - closest):
                closest = sum

return closest


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {

        int n = nums.size();

        int closest = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; i++) {

            for (int j = i + 1; j < n - 1; j++) {

                for (int k = j + 1; k < n; k++) {

                    int sum = nums[i] + nums[j] + nums[k];

                    if (abs(target - sum) <
                        abs(target - closest)) {

                        closest = sum;
                    }
                }
            }
        }

        return closest;
    }
};

Time Complexity:
----------------
O(n^3)

Space Complexity:
-----------------
O(1)


============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
Sort the array first.

Then fix one element and use two pointers for the remaining
two elements.

For every fixed element nums[k]:

    i = k + 1
    j = n - 1

Calculate:

    sum = nums[k] + nums[i] + nums[j]


Intuition:
----------
Because the array is sorted:

If:

    sum < target

we need a larger sum.

Therefore:

    i++

If:

    sum > target

we need a smaller sum.

Therefore:

    j--

If:

    sum == target

we have found the exact target, so it is the best possible
answer.


Pseudo Code:
------------
sort nums

closestSum = 100000

for k = 0 to n - 3:

    i = k + 1
    j = n - 1

    while i < j:

        sum = nums[k] + nums[i] + nums[j]

        if current sum is closer to target:
            closestSum = sum

        if sum < target:
            i++

        else:
            j--

return closestSum


Complete Optimal Code:
----------------------

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {

        int n = nums.size();

        int closestSum = 100000;

        sort(nums.begin(), nums.end());

        for (int k = 0; k <= n - 3; k++) {

            int i = k + 1;
            int j = n - 1;

            while (i < j) {

                int sum = nums[k] + nums[i] + nums[j];

                if (abs(target - sum) <
                    abs(target - closestSum)) {

                    closestSum = sum;
                }

                if (sum < target) {
                    i++;
                } else {
                    j--;
                }
            }
        }

        return closestSum;
    }
};

Time Complexity:
----------------
Sorting:

    O(n log n)

Two-pointer search:

    O(n^2)

Overall:

    O(n^2)


Space Complexity:
-----------------
O(1) auxiliary space.


============================================================
DRY RUN WITH EXAMPLE
============================================================

Input:

    nums = [-1, 2, 1, -4]
    target = 1


Step 1:
-------
Sort the array:

    [-4, -1, 1, 2]


Initial:

    closestSum = 100000


Step 2:
-------
k = 0

    nums[k] = -4

    i = 1
    j = 3

Calculate:

    sum = -4 + (-1) + 2
        = -3

Difference:

    |1 - (-3)|
    = 4

Current closest:

    -3


Since:

    -3 < 1

Move:

    i++


Step 3:
-------
Now:

    i = 2
    j = 3

Calculate:

    sum = -4 + 1 + 2
        = -1

Difference:

    |1 - (-1)|
    = 2

Since 2 < 4:

    closestSum = -1


Since:

    -1 < 1

Move:

    i++


Now:

    i = 3
    j = 3

Stop because:

    i < j

is false.


Step 4:
-------
k = 1

    nums[k] = -1

    i = 2
    j = 3

Calculate:

    sum = -1 + 1 + 2
        = 2

Difference:

    |1 - 2|
    = 1

Current difference:

    |1 - (-1)|
    = 2

Therefore:

    closestSum = 2


Since:

    2 > 1

Move:

    j--


Now:

    i = 2
    j = 2

Stop.


Final Answer:

    2


============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Sorting + Two Pointers


Key Observation:
----------------
After sorting the array, fix one element and use two pointers
to find the other two elements.

If:

    sum < target
        -> move left pointer forward

If:

    sum > target
        -> move right pointer backward

This reduces the solution from:

    O(n^3)

to:

    O(n^2)


Common Mistakes:
----------------
1. Forgetting to sort the array.

2. Moving the wrong pointer.

       sum < target:
           i++

       sum > target:
           j--

3. Returning the first valid sum instead of checking the
   closest sum.

4. Forgetting to update closestSum.

5. Using three nested loops after sorting.

6. Using an inappropriate initial value.

   This solution uses:

       closestSum = 100000

   which works under the LeetCode constraints.

   A safer general CP approach is:

       int closestSum =
           nums[0] + nums[1] + nums[2];

7. Integer overflow for very large values.

   In a general implementation, sum can be calculated using
   long long:

       long long sum =
           1LL * nums[k] + nums[i] + nums[j];


When to use this approach:
--------------------------
Use Sorting + Two Pointers when:

- You need to choose 2 or 3 elements.
- The array can be sorted.
- You need to find a sum close to a target.
- The sorted order allows you to decide which pointer to move.

Common pattern:

    Sort
      |
      v
    Fix one element
      |
      v
    Two pointers
      |
      +---- sum < target -> left++
      |
      +---- sum > target -> right--
      |
      +---- sum == target -> exact answer


Related Problems:
-----------------
LeetCode 15:
    3Sum

LeetCode 16:
    3Sum Closest

LeetCode 18:
    4Sum


Quick Revision:
---------------

    sort(nums)

    for k = 0 to n - 3:

        i = k + 1
        j = n - 1

        while i < j:

            sum = nums[k] + nums[i] + nums[j]

            update closestSum

            if sum < target:
                i++

            else:
                j--

    Time:
        O(n^2)

    Space:
        O(1)

============================================================
*/
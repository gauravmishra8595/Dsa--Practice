#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> sortArray(vector<int> &nums)
    {

      
        int offset = 50000;
        vector<int> freq(100001, 0);
        for (int x : nums)
        {
            freq[x + offset]++;
        }
        int index = 0;

        for (int i = 0; i < (int)freq.size(); i++)
        {

            while (freq[i] > 0)
            {
                nums[index] = i - offset;

                index++;
                freq[i]--;
            }
        }

        return nums;
    }
};

int main()
{

    Solution sol;
    vector<int> nums1 = {5, 2, 3, 1};

    vector<int> ans1 = sol.sortArray(nums1);

    cout << "Test Case 1: ";
    for (int x : ans1)
    {
        cout << x << " ";
    }
    cout << '\n';

    vector<int> nums2 = {5, 1, 1, 2, 0, 0};

    vector<int> ans2 = sol.sortArray(nums2);

    cout << "Test Case 2: ";
    for (int x : ans2)
    {
        cout << x << " ";
    }
    cout << '\n';

    vector<int> nums3 = {-4, 0, 3, -1, 2, -4};

    vector<int> ans3 = sol.sortArray(nums3);

    cout << "Test Case 3: ";
    for (int x : ans3)
    {
        cout << x << " ";
    }
    cout << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 912 - SORT AN ARRAY
================================================================================

Problem Statement:
------------------
Given an integer array nums, sort the array in ascending order.

Example:

Input:
    nums = [5, 2, 3, 1]

Output:
    [1, 2, 3, 5]


===============================================================================
APPROACH - COUNTING SORT
===============================================================================

Idea:
-----
Instead of comparing elements with each other, count how many times
each number occurs.

LeetCode 912 has the constraint:

    -50000 <= nums[i] <= 50000

There are only:

    50000 - (-50000) + 1
    = 100001

possible values.

So we can create a frequency array of size 100001.

However, array indices cannot be negative.

Therefore, use an offset:

    offset = 50000

Convert:

    actual value + offset = frequency array index


Example:

    value = -50000

    index = -50000 + 50000
          = 0


    value = 0

    index = 0 + 50000
          = 50000


    value = 50000

    index = 50000 + 50000
          = 100000


Therefore every possible value maps to a valid index.


===============================================================================
STEP 1 - COUNT FREQUENCIES
===============================================================================

For every number:

    freq[nums[i] + offset]++


Example:

    nums = [5, 2, 3, 1]

Frequency:

    freq[50005] = 1
    freq[50002] = 1
    freq[50003] = 1
    freq[50001] = 1


===============================================================================
STEP 2 - RECONSTRUCT SORTED ARRAY
===============================================================================

Traverse the frequency array from left to right.

Smaller indices represent smaller numbers.

For every frequency:

    while freq[i] > 0:

        nums[index] = i - offset

        index++

        freq[i]--


Because we traverse from small values to large values,
the resulting nums array is sorted.


===============================================================================
PSEUDO CODE
===============================================================================

offset = 50000

create freq array of size 100001

for every x in nums:
    freq[x + offset]++

index = 0

for i = 0 to 100000:

    while freq[i] > 0:

        nums[index] = i - offset

        index++

        freq[i]--

return nums


===============================================================================
COMPLETE OPTIMAL CODE
===============================================================================

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {

        int offset = 50000;

        vector<int> freq(100001, 0);

        for (int x : nums) {
            freq[x + offset]++;
        }

        int index = 0;

        for (int i = 0; i < (int)freq.size(); i++) {

            while (freq[i] > 0) {

                nums[index] = i - offset;

                index++;
                freq[i]--;
            }
        }

        return nums;
    }
};


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Use a comparison-based sorting algorithm such as Selection Sort.

For every position, find the smallest element from the remaining
array and place it at that position.


Pseudo Code:
-----------

for i = 0 to n-2:

    minIndex = i

    for j = i+1 to n-1:

        if nums[j] < nums[minIndex]:

            minIndex = j

    swap(nums[i], nums[minIndex])


Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {

        int n = nums.size();

        for (int i = 0; i < n - 1; i++) {

            int minIndex = i;

            for (int j = i + 1; j < n; j++) {

                if (nums[j] < nums[minIndex]) {
                    minIndex = j;
                }
            }

            swap(nums[i], nums[minIndex]);
        }

        return nums;
    }
};


Time Complexity:
----------------
O(N^2)


Space Complexity:
-----------------
O(1)


===============================================================================
DRY RUN
===============================================================================

Input:

    nums = [5, 2, 3, 1]

offset = 50000


Step 1: Frequency Counting

5 -> freq[50005]++
2 -> freq[50002]++
3 -> freq[50003]++
1 -> freq[50001]++


Step 2: Traverse frequency array

At index 50001:

    frequency = 1

    value = 50001 - 50000
          = 1

So:

    nums[0] = 1


At index 50002:

    frequency = 1

    value = 2

So:

    nums[1] = 2


At index 50003:

    frequency = 1

    value = 3

So:

    nums[2] = 3


At index 50005:

    frequency = 1

    value = 5

So:

    nums[3] = 5


Final:

    nums = [1, 2, 3, 5]


===============================================================================
ANOTHER DRY RUN WITH DUPLICATES
===============================================================================

Input:

    nums = [5, 1, 1, 2, 0, 0]


Frequencies:

    0 -> 2
    1 -> 2
    2 -> 1
    5 -> 1


Reconstruction:

    0 -> put twice
    1 -> put twice
    2 -> put once
    5 -> put once


Result:

    [0, 0, 1, 1, 2, 5]


===============================================================================
TIME COMPLEXITY
===============================================================================

Let:

    N = number of elements
    R = range of possible values

Here:

    R = 100001


Counting:
    O(N)

Traversing frequency array:
    O(R)

Reconstructing:
    O(N)

Total:

    O(N + R)

Since R = 100001 is fixed by the problem constraints:

    O(N)


===============================================================================
SPACE COMPLEXITY
===============================================================================

Frequency array:

    O(R)

Here:

    R = 100001

Therefore:

    O(R)

Under the fixed LeetCode constraints, this is effectively
constant extra space with respect to N.


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Counting Sort / Frequency Array


Key Observation:
----------------
The values are restricted to:

    [-50000, 50000]

The range is only 100001 values.

When the value range is small compared with N, Counting Sort
can be extremely efficient.


Common Mistakes:
----------------

1. Forgetting the offset.

   This would cause negative numbers to be used as array indices.

   Wrong:

       freq[nums[i]]++

   Correct:

       freq[nums[i] + offset]++


2. Using an incorrect frequency array size.

   Required range:

       [-50000, 50000]

   Number of values:

       50000 - (-50000) + 1
       = 100001


3. Forgetting to subtract the offset while reconstructing.

   Correct:

       nums[index] = i - offset


4. Using the wrong offset.

   For this problem:

       offset = 50000


5. Forgetting duplicate values.

   Use:

       while (freq[i] > 0)

   so every occurrence is placed back.


6. Confusing Counting Sort with comparison sorting.

   Counting Sort does not compare elements.


===============================================================================
WHEN TO USE COUNTING SORT
===============================================================================

Use Counting Sort when:

- Values are integers.
- The value range is known.
- The range is relatively small.
- You need efficient sorting.
- Frequency counting is natural.

For example:

    nums[i] between 0 and 100

A frequency array of size 101 is ideal.


Avoid Counting Sort when:

    Range >> N

because the frequency array can become unnecessarily large.


===============================================================================
COMPARISON
===============================================================================

Comparison Sorting:

    Merge Sort
        Time:  O(N log N)
        Space: O(N)

    Quick Sort
        Average: O(N log N)
        Worst:   O(N^2)

Counting Sort:

    Time:  O(N + R)
    Space: O(R)

For LeetCode 912:

    R = 100001

Therefore Counting Sort is an excellent solution because the value
range is small and fixed.


===============================================================================
FINAL REVISION LINE
===============================================================================

Small integer range
        ↓
Frequency Array
        ↓
Count occurrences
        ↓
Traverse from smallest to largest
        ↓
Reconstruct array
        ↓
Counting Sort


Time:  O(N + R)
Space: O(R)

================================================================================
*/

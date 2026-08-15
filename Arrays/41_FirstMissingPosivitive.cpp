#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            while (nums[i] >= 1 &&
                   nums[i] <= n &&
                   nums[nums[i] - 1] != nums[i])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (nums[i] != i + 1)
                return i + 1;
        }

        return n + 1;
    }
};

int main()
{
    vector<int> nums = {3, 4, -1, 1};

    Solution obj;
    cout << obj.firstMissingPositive(nums) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 41 - CP NOTEBOOK
                       First Missing Positive
================================================================================

Problem Statement:
------------------
Given an unsorted integer array nums, return the smallest positive integer
that does not appear in nums.

The solution must run in O(n) time and use O(1) extra space.


Example:
--------
Input:

    nums = [3, 4, -1, 1]

Output:

    2

Explanation:

Positive integers are:

    1, 2, 3, 4, ...

The array contains:

    1, 3, 4

The first positive integer missing from the array is:

    2


Another Example:
----------------

Input:

    nums = [1, 2, 0]

Output:

    3


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Use a set to store all positive numbers.

Then start checking from 1:

    1
    2
    3
    ...

The first positive number that is not present in the set is the answer.

This approach is simple but requires O(n) extra space.


Pseudo Code:
------------

function firstMissingPositive(nums):

    set = empty set

    for x in nums:

        if x > 0:
            insert x into set

    positive = 1

    while positive exists in set:

        positive++

    return positive


Complete Brute Force Code:
---------------------------

int bruteForce(vector<int> &nums)
{
    unordered_set<int> st;

    for (int x : nums)
    {
        if (x > 0)
            st.insert(x);
    }

    int positive = 1;

    while (st.count(positive))
    {
        positive++;
    }

    return positive;
}


Time Complexity:
----------------
O(n) average


Space Complexity:
-----------------
O(n)

The set can contain up to n elements.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------
The answer must be between:

    1 and n + 1

for an array of size n.

Why?

If all numbers from 1 to n are present:

    answer = n + 1

Otherwise, at least one number from 1 to n is missing.

Therefore, we only care about placing numbers in the range:

    [1, n]

at their correct indices.


Index Mapping:
--------------

For a value x:

    x = 1  -> index 0
    x = 2  -> index 1
    x = 3  -> index 2
    ...
    x = n  -> index n - 1

So ideally:

    nums[x - 1] = x


Intuition:
----------
Use the array itself as a hash table.

For every number x:

    if 1 <= x <= n

place x at index:

    x - 1


For example:

    [3, 4, -1, 1]

Place 3 at index 2:

    [-1, 4, 3, 1]

Place 4 at index 3:

    [-1, 1, 3, 4]

Place 1 at index 0:

    [1, -1, 3, 4]

Now every number is at its correct index if it exists.

Finally scan the array.

At index i, we expect:

    nums[i] = i + 1

For:

    [1, -1, 3, 4]

Index 0:

    nums[0] = 1
    correct

Index 1:

    nums[1] != 2

Therefore:

    answer = 2


Why Do We Use a while Loop?
----------------------------
A number moved into nums[i] may itself need to be moved somewhere else.

Example:

    [2, 3, 1]

At index 0:

    nums[0] = 2

So place 2 at index 1:

    [3, 2, 1]

But now 3 is at index 0 and needs to move to index 2:

    [1, 2, 3]

Therefore, we need to keep swapping until the current position
contains a number that belongs there.


Duplicate Handling:
-------------------
Consider:

    [1, 1]

Without the duplicate check, we could continuously swap equal values.

Therefore, we require:

    nums[nums[i] - 1] != nums[i]

before swapping.


Pseudo Code:
------------

function firstMissingPositive(nums):

    n = size(nums)

    for i from 0 to n - 1:

        while:

            nums[i] is between 1 and n
            AND
            nums[nums[i] - 1] != nums[i]

        do:

            swap(nums[i], nums[nums[i] - 1])


    for i from 0 to n - 1:

        if nums[i] != i + 1:

            return i + 1

    return n + 1


Complete Optimal Code:
-----------------------

class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            while (nums[i] >= 1 &&
                   nums[i] <= n &&
                   nums[nums[i] - 1] != nums[i])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (nums[i] != i + 1)
                return i + 1;
        }

        return n + 1;
    }
};


Time Complexity:
----------------
O(n)

Although there is a while loop inside the for loop, every successful swap
places at least one number into its correct position.

Therefore, the total number of swaps is O(n).


Space Complexity:
-----------------
O(1)

No extra data structure is used.


===============================================================================
Dry Run With Example
===============================================================================

Example:

    nums = [3, 4, -1, 1]

n = 4


Step 1:
-------
i = 0

    nums[0] = 3

3 belongs at index:

    3 - 1 = 2

Swap:

    [3, 4, -1, 1]
             |
             v

    [-1, 4, 3, 1]


Current nums[0] = -1.

-1 is not in the range [1, n].

Move to next index.


Step 2:
-------
i = 1

    nums[1] = 4

4 belongs at index:

    4 - 1 = 3

Swap:

    [-1, 4, 3, 1]

becomes:

    [-1, 1, 3, 4]


Current nums[1] = 1.

1 belongs at index 0.

Swap:

    [-1, 1, 3, 4]

becomes:

    [1, -1, 3, 4]


Current nums[1] = -1.

Stop processing this index.


Step 3:
-------
i = 2

    nums[2] = 3

3 belongs at index:

    3 - 1 = 2

Already correct.

Move forward.


Step 4:
-------
i = 3

    nums[3] = 4

4 belongs at index:

    4 - 1 = 3

Already correct.


Array after placement:

    [1, -1, 3, 4]


Now scan:

Index 0:

    expected = 1
    actual   = 1

Correct.


Index 1:

    expected = 2
    actual   = -1

Mismatch.

Therefore:

    answer = 2


===============================================================================
Another Dry Run
===============================================================================

Example:

    nums = [1, 2, 0]

n = 3

1 is already at index 0.

2 is already at index 1.

0 is ignored.

Array:

    [1, 2, 0]


Scan:

Index 0:

    nums[0] = 1
    correct


Index 1:

    nums[1] = 2
    correct


Index 2:

    nums[2] != 3

Therefore:

    answer = 3


===============================================================================
Edge Cases
===============================================================================

1. Empty array:

       []

   Answer:

       1


2. All negative:

       [-1, -2, -3]

   No positive integer exists.

   Answer:

       1


3. Contains zero:

       [0, 1, 2]

   Answer:

       3


4. All consecutive positive numbers:

       [1, 2, 3, 4]

   All numbers from 1 to n exist.

   Answer:

       n + 1
       = 5


5. Duplicates:

       [1, 1, 2, 2]

   The first missing positive is:

       3


6. Unordered values:

       [7, 8, 9, 11, 12]

   None of 1, 2, 3, 4, 5, 6 exists.

   Answer:

       1


===============================================================================
Interview Notes
===============================================================================

Pattern:
--------
Array + Cyclic Sort / Index Placement


Key Observation:
----------------
For an array of size n, the answer is always in:

    [1, n + 1]

Therefore, values outside:

    [1, n]

can be ignored.

For every valid value x:

    correct index = x - 1


Core Idea:
----------
Use the array itself to place every positive number at its correct position.

    value x
       |
       v
    index x - 1


After placement:

    nums[0] should be 1
    nums[1] should be 2
    nums[2] should be 3
    ...
    nums[n-1] should be n


The first incorrect position i gives:

    answer = i + 1


Common Mistakes:
----------------

1. Using a set.

   A set gives O(n) space, while this problem requires O(1) extra space.


2. Sorting the array.

   Sorting gives:

       O(n log n)

   but the required optimal solution is:

       O(n)


3. Forgetting to ignore values <= 0.

   Only positive numbers matter.


4. Forgetting to ignore values > n.

   Such values cannot be the first missing positive.


5. Not handling duplicates.

   Without:

       nums[nums[i] - 1] != nums[i]

   duplicate values can cause an infinite loop.


6. Using if instead of while.

   A number swapped into the current position may also need to be moved.

   Therefore:

       while (...)

   is required.


7. Returning n instead of n + 1.

   Example:

       [1, 2, 3]

   The first missing positive is:

       4

   Therefore, when every position is correct, return:

       n + 1


When To Use This Approach:
--------------------------

Use this pattern when:

- The array contains values related to indices.
- The required answer lies in a known range.
- You need O(n) time.
- O(1) extra space is required.
- Values can be placed at their corresponding indices.

This is commonly called:

    Cyclic Sort
    Index Placement
    In-place Hashing


Core Mental Template:
---------------------

n = nums.size()

for every index i:

    while nums[i] belongs to [1, n]
          and nums[i] is not already at its correct position:

        swap(
            nums[i],
            nums[nums[i] - 1]
        )


Then:

    for i = 0 to n - 1:

        if nums[i] != i + 1:

            return i + 1


    return n + 1


Final Complexity:
-----------------

Time  : O(n)
Space : O(1)

================================================================================
*/
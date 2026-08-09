#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums)
    {
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        unordered_map<int, int> smallerCount;
        for (int i = 0; i < (int)sorted.size(); i++)
        {
            if (!smallerCount.count(sorted[i]))
            {
                smallerCount[sorted[i]] = i;
            }
        }
        vector<int> ans;
        for (int x : nums)
        {
            ans.push_back(smallerCount[x]);
        }
        return ans;
    }
};
int main()
{
    Solution sol;

    vector<int> nums = {8, 1, 2, 2, 3};

    vector<int> ans = sol.smallerNumbersThanCurrent(nums);

    for (int x : ans)
    {
        cout << x << " ";
    }

    cout << '\n';

    return 0;
}

/*
===============================================================================
              LEETCODE 1365 - HOW MANY NUMBERS ARE SMALLER THAN
                              THE CURRENT NUMBER
===============================================================================

Problem Statement
-----------------
Given the array nums, for each nums[i], find how many numbers in the array
are smaller than it.

In other words, for every element, count the number of elements whose value
is strictly smaller than the current element.

Return the answer array.

Example
-------
Input:
    nums = [8, 1, 2, 2, 3]

Output:
    [4, 0, 1, 1, 3]

Explanation:
    8 -> smaller numbers: 1, 2, 2, 3 -> 4
    1 -> smaller numbers: none      -> 0
    2 -> smaller numbers: 1         -> 1
    2 -> smaller numbers: 1         -> 1
    3 -> smaller numbers: 1, 2, 2   -> 3

===============================================================================
                         BRUTE FORCE APPROACH
===============================================================================

Idea
----
For every element, compare it with every other element.

If another element is strictly smaller, increment the count.

Pseudo Code
-----------
    ans = empty array

    for i from 0 to n-1:
        count = 0

        for j from 0 to n-1:
            if nums[j] < nums[i]:
                count++

        ans.push_back(count)

    return ans

Complete Brute Force Code
-------------------------
    class Solution {
    public:
        vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
            int n = nums.size();
            vector<int> ans(n, 0);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (nums[j] < nums[i]) {
                        ans[i]++;
                    }
                }
            }

            return ans;
        }
    };

Time Complexity
---------------
    O(n^2)

Space Complexity
----------------
    O(n) for the answer array.

    Extra auxiliary space:
    O(1)

===============================================================================
                          OPTIMAL APPROACH
===============================================================================

Observation
-----------
Sort a copy of the array.

For a value x, its first occurrence in the sorted array tells us exactly
how many elements are strictly smaller than x.

Example:

    Original:
        [8, 1, 2, 2, 3]

    Sorted:
        [1, 2, 2, 3, 8]

    First index of:
        1 -> 0 elements smaller
        2 -> 1 element smaller
        3 -> 3 elements smaller
        8 -> 4 elements smaller

Therefore:

    smallerCount[x] = first index of x in sorted array

Intuition
---------
After sorting, every element before the first occurrence of x is strictly
smaller than x.

Duplicates are handled correctly because we store only the FIRST occurrence.

For example:

    sorted = [1, 2, 2, 3, 8]

    First 2 occurs at index 1.

Therefore exactly one element is smaller than 2.

Both occurrences of 2 get answer 1.

Pseudo Code
-----------
    sorted = copy of nums
    sort(sorted)

    create map smallerCount

    for i from 0 to n-1:
        if sorted[i] is not already in map:
            smallerCount[sorted[i]] = i

    ans = empty array

    for x in nums:
        ans.push_back(smallerCount[x])

    return ans

Complete Optimal Code
---------------------
    class Solution {
    public:
        vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
            vector<int> sorted = nums;
            sort(sorted.begin(), sorted.end());

            unordered_map<int, int> smallerCount;

            for (int i = 0; i < (int)sorted.size(); i++) {
                if (!smallerCount.count(sorted[i])) {
                    smallerCount[sorted[i]] = i;
                }
            }

            vector<int> ans;

            for (int x : nums) {
                ans.push_back(smallerCount[x]);
            }

            return ans;
        }
    };

Time Complexity
---------------
    Sorting:
        O(n log n)

    Building map:
        O(n) average

    Building answer:
        O(n) average

    Total:
        O(n log n)

Space Complexity
----------------
    O(n)

    Because we store:
        - sorted copy
        - frequency/map
        - answer

===============================================================================
                              DRY RUN
===============================================================================

Example:
    nums = [8, 1, 2, 2, 3]

Step 1: Copy and sort

    sorted = [1, 2, 2, 3, 8]

Step 2: Store first occurrence of every value

    1 -> index 0
    2 -> index 1
    3 -> index 3
    8 -> index 4

So:

    smallerCount = {
        1 : 0,
        2 : 1,
        3 : 3,
        8 : 4
    }

Step 3: Process original array

    8 -> smallerCount[8] = 4
    1 -> smallerCount[1] = 0
    2 -> smallerCount[2] = 1
    2 -> smallerCount[2] = 1
    3 -> smallerCount[3] = 3

Final Answer:

    [4, 0, 1, 1, 3]

===============================================================================
                              INTERVIEW NOTES
===============================================================================

Pattern
-------
    Sorting + Mapping / Frequency Counting

Key Observation
---------------
    In a sorted array, the index of the FIRST occurrence of a value
    equals the number of elements strictly smaller than that value.

Common Mistakes
---------------
    1. Counting elements <= current instead of strictly smaller elements.

    2. Using the LAST occurrence of a duplicate instead of the FIRST one.

       Example:
           sorted = [1, 2, 2, 3]

       Correct:
           2 -> index 1

       Incorrect:
           2 -> index 2

    3. Sorting the original array and then losing the original ordering.

       Always keep a copy:

           vector<int> sorted = nums;

    4. Forgetting that duplicate values must have the same answer.

    5. Using O(n^2) brute force when an O(n log n) solution is expected.

When to Use This Approach
-------------------------
    Use this approach when:

    - For every element, we need the number of elements smaller than it.
    - The input can be sorted.
    - We need to preserve the original order of the answers.
    - O(n log n) time is acceptable.

Alternative Optimal Approach
-----------------------------
    If the value range is small and bounded, a frequency/counting array
    can achieve O(n + k) time.

    For LeetCode 1365, nums[i] is limited to a small range, so a counting
    array solution can actually achieve O(n) time.

    The sorting + mapping approach is more general and works even when
    the values are large or negative.

Complexity Summary
------------------
    Brute Force:
        Time  = O(n^2)
        Space = O(n) for answer

    Sorting + Mapping:
        Time  = O(n log n)
        Space = O(n)

    Counting Array (when value range is small):
        Time  = O(n + k)
        Space = O(k)

===============================================================================
*/
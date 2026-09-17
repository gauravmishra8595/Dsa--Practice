#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minSumOfLengths(vector<int> &arr, int target)
    {
        int n = arr.size();

        // minLenTill[i] = minimum length of a valid subarray
        // completely contained in arr[0...i]
        vector<int> minLenTill(n, INT_MAX);

        int i = 0;
        int currSum = 0;
        int bestLen = INT_MAX;
        int result = INT_MAX;

        for (int j = 0; j < n; j++)
        {
            currSum += arr[j];

            while (i <= j && currSum > target)
            {
                currSum -= arr[i++];
            }

            if (currSum == target)
            {
                int len = j - i + 1;

                // Previous subarray must end before i.
                if (i > 0 && minLenTill[i - 1] != INT_MAX)
                {
                    result = min(result, len + minLenTill[i - 1]);
                }

                bestLen = min(bestLen, len);
            }

            minLenTill[j] = bestLen;
        }

        return result == INT_MAX ? -1 : result;
    }
};

int main()
{
    Solution sol;

    vector<int> arr = {3, 2, 2, 4, 3};
    int target = 3;

    cout << sol.minSumOfLengths(arr, target) << '\n';

    return 0;
}

/*
===============================================================================
                         LEETCODE 1477
              FIND TWO NON-OVERLAPPING SUB-ARRAYS
                         EACH WITH TARGET SUM
===============================================================================

Problem Statement:
------------------
Given an array of positive integers arr and an integer target, find two
non-overlapping subarrays such that the sum of each subarray is equal to
target.

Return the minimum possible sum of their lengths.

If no such pair exists, return -1.

Example:
--------
Input:
arr = [3,2,2,4,3]
target = 3

Valid subarrays with sum = 3:
[3]       -> length 1
[2,2]     -> length 2
[3]       -> length 1

We can choose:
[3] at index 0
[3] at index 4

Total length = 1 + 1 = 2

Output:
2

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Try every possible subarray.

For every starting index i, extend the subarray to every ending index j and
calculate its sum.

Whenever sum == target, we have found a valid subarray.

Then compare every pair of valid subarrays and check whether they overlap.

Keep the minimum combined length.

This is straightforward but inefficient.

Pseudo Code:
------------
1. Generate all subarrays.
2. Store every subarray whose sum is target.
3. For every pair of valid subarrays:
      a. Check if they are non-overlapping.
      b. If non-overlapping, update minimum combined length.
4. If no pair exists, return -1.

Complete Brute Force Code:
--------------------------

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        vector<pair<int, int>> valid;

        // Find all subarrays having sum = target
        for (int i = 0; i < n; i++) {
            int sum = 0;

            for (int j = i; j < n; j++) {
                sum += arr[j];

                if (sum == target) {
                    valid.push_back({i, j});
                }
            }
        }

        int ans = INT_MAX;

        // Try every pair
        for (int x = 0; x < valid.size(); x++) {
            for (int y = x + 1; y < valid.size(); y++) {
                int l1 = valid[x].first;
                int r1 = valid[x].second;

                int l2 = valid[y].first;
                int r2 = valid[y].second;

                // Non-overlapping
                if (r1 < l2 || r2 < l1) {
                    int len1 = r1 - l1 + 1;
                    int len2 = r2 - l2 + 1;

                    ans = min(ans, len1 + len2);
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};

Time Complexity:
----------------
Generating all subarrays: O(N^2)

Comparing pairs of valid subarrays: O(N^2) in the worst case

Overall:
O(N^2)

Space Complexity:
-----------------
O(N^2) in the worst case for storing all valid subarrays.

However, the actual number of valid subarrays can be smaller.

===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
The array contains positive integers.

Therefore, we can use a sliding window.

For a window [i...j]:

    currSum < target  -> expand j
    currSum > target  -> move i forward
    currSum == target -> valid subarray found

The second important observation is:

For the current subarray [i...j], we need the shortest valid subarray that
ends before i.

So we maintain:

    minLenTill[x]

which stores the minimum length of any valid subarray completely contained
inside arr[0...x].

Intuition:
----------
Suppose the current valid subarray is:

    [i ... j]

Its length is:

    j - i + 1

For another subarray to be non-overlapping with it, that previous subarray
must end at an index less than i.

Therefore, we only need:

    minLenTill[i - 1]

If it exists, the total length is:

    currentLength + minLenTill[i - 1]

Take the minimum over all valid current subarrays.

Pseudo Code:
------------
1. Initialize:
       i = 0
       currSum = 0
       bestLen = INF
       result = INF

2. Create:
       minLenTill[n]

   where minLenTill[j] stores the shortest valid subarray found up to j.

3. For every j from 0 to n-1:

       Add arr[j] to currSum.

       While currSum > target:
           Remove arr[i].
           Increment i.

       If currSum == target:
           len = j - i + 1

           If i > 0 and minLenTill[i-1] exists:
               result = min(result, len + minLenTill[i-1])

           bestLen = min(bestLen, len)

       minLenTill[j] = bestLen

4. Return result if found, otherwise -1.

Complete Optimal Code:
----------------------

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        vector<int> minLenTill(n, INT_MAX);

        int i = 0;
        int currSum = 0;
        int bestLen = INT_MAX;
        int result = INT_MAX;

        for (int j = 0; j < n; j++) {
            currSum += arr[j];

            while (i <= j && currSum > target) {
                currSum -= arr[i++];
            }

            if (currSum == target) {
                int len = j - i + 1;

                if (i > 0 && minLenTill[i - 1] != INT_MAX) {
                    result = min(result,
                                 len + minLenTill[i - 1]);
                }

                bestLen = min(bestLen, len);
            }

            minLenTill[j] = bestLen;
        }

        return result == INT_MAX ? -1 : result;
    }
};

Time Complexity:
----------------
The right pointer j moves from 0 to N-1.

The left pointer i also moves only forward and never moves backward.

Therefore, every element is added and removed at most once.

Time Complexity:
O(N)

Space Complexity:
-----------------
The minLenTill array requires O(N) space.

Space Complexity:
O(N)

===============================================================================
DRY RUN
===============================================================================

arr = [3, 2, 2, 4, 3]
target = 3

Initially:

i = 0
currSum = 0
bestLen = INF
result = INF

j = 0
-------
Add arr[0] = 3

currSum = 3

currSum == target

Current subarray:
[3]

length = 1

No previous subarray exists.

bestLen = 1
minLenTill[0] = 1

j = 1
-------
Add arr[1] = 2

currSum = 5

currSum > target.

Remove arr[0]:

currSum = 2
i = 1

currSum != target.

minLenTill[1] = 1

j = 2
-------
Add arr[2] = 2

currSum = 4

currSum > target.

Remove arr[1]:

currSum = 2
i = 2

currSum != target.

minLenTill[2] = 1

j = 3
-------
Add arr[3] = 4

currSum = 6

Remove arr[2]:

currSum = 4
i = 3

Remove arr[3]:

currSum = 0
i = 4

currSum != target.

minLenTill[3] = 1

j = 4
-------
Add arr[4] = 3

currSum = 3

Current subarray:
[3]

i = 4
j = 4

length = 1

We need a previous valid subarray ending before i.

minLenTill[i - 1]
= minLenTill[3]
= 1

Therefore:

result = min(1 + 1)
       = 2

bestLen remains 1.

Final answer:

2

===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Sliding Window + Prefix/Previous Best

Another way to recognize the pattern:

    "Find multiple target-sum subarrays"
    +
    "They must not overlap"
    +
    "Minimize total length"

Key Observation:
----------------
For every valid current subarray [i...j], we only need the shortest valid
subarray ending before i.

Instead of checking all previous subarrays again, store the best answer
seen so far using:

    minLenTill[index]

Common Mistakes:
----------------
1. Treating this exactly like Two Sum.

   Two Sum searches for two elements.

   Here we need contiguous subarrays.

2. Forgetting the non-overlapping condition.

   A previous subarray must end before the current subarray starts.

3. Using minLenTill[i] instead of minLenTill[i - 1].

   The previous subarray must be completely before index i.

4. Using a sliding window without considering the array properties.

   This sliding-window approach depends on the fact that the array elements
   are positive.

5. Returning the length of one subarray instead of the sum of lengths of
   two non-overlapping subarrays.

6. Forgetting the impossible case.

   If two valid non-overlapping subarrays cannot be found, return -1.

When to Use This Approach:
--------------------------
Use this pattern when:

- Array elements are positive.
- You need to find subarrays with a specific sum.
- You need multiple non-overlapping subarrays.
- You need to minimize or maximize their lengths.
- A previous/best subarray can be summarized instead of storing all
  possibilities.

Typical thought process:

    Target subarray
          |
          v
    Sliding Window
          |
          v
    Need previous non-overlapping subarray
          |
          v
    Store best previous answer
          |
          v
    O(N) solution

===============================================================================
*/
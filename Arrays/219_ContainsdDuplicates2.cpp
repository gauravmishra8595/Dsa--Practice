#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> lastIndex;

        for (int i = 0; i < (int)nums.size(); i++)
        {
            if (lastIndex.count(nums[i]) &&
                i - lastIndex[nums[i]] <= k)
            {
                return true;
            }

            lastIndex[nums[i]] = i;
        }

        return false;
    }
};

int main()
{
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 1};
    int k1 = 3;
    cout << boolalpha << sol.containsNearbyDuplicate(nums1, k1) << '\n';

    vector<int> nums2 = {1, 0, 1, 1};
    int k2 = 1;
    cout << sol.containsNearbyDuplicate(nums2, k2) << '\n';

    vector<int> nums3 = {1, 2, 3, 1, 2, 3};
    int k3 = 2;
    cout << sol.containsNearbyDuplicate(nums3, k3) << '\n';

    return 0;
}

/*
================================================================================
LEETCODE 219 - CONTAINS DUPLICATE II
================================================================================

Problem Statement:
------------------
Given an integer array nums and an integer k, return true if there are
two distinct indices i and j such that:

    nums[i] == nums[j]

and

    |i - j| <= k

Otherwise, return false.


Example:
--------
Input:
    nums = [1, 2, 3, 1]
    k = 3

The value 1 occurs at indices 0 and 3.

    |0 - 3| = 3 <= k

Therefore:

    Output = true


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Check every pair of indices.

For every i, compare nums[i] with all elements nums[j] where
j is within distance k.

If we find:

    nums[i] == nums[j]

and

    |i - j| <= k

return true.

If no such pair exists, return false.


Pseudo Code:
-----------
for i = 0 to n-1:
    for j = i+1 to min(n-1, i+k):
        if nums[i] == nums[j]:
            return true

return false


Complete Brute Force Code (inside comments only):
---------------------------------------------------

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n && j <= i + k; j++) {
                if (nums[i] == nums[j])
                    return true;
            }
        }

        return false;
    }
};


Time Complexity:
----------------
O(n * k)

In the worst case, k can be O(n), giving:

    O(n^2)


Space Complexity:
-----------------
O(1)

No extra data structure is used.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
For every number, we only care about its MOST RECENT occurrence.

Suppose:

    nums = [1, 2, 3, 1]

When we reach index 3:

    nums[3] = 1

The previous occurrence of 1 was at index 0.

Distance:

    3 - 0 = 3

Since:

    3 <= k

we found a valid pair.


Intuition:
---------
Maintain a hash map:

    number -> latest index where it appeared

When processing nums[i]:

1. Check whether nums[i] has appeared before.
2. If yes, calculate the distance from its latest occurrence.
3. If distance <= k, return true.
4. Otherwise update its latest index to i.

Why is storing only the latest index enough?

Suppose a number appeared at:

    index 2
    index 5
    index 10

Now we are at index 12.

The latest occurrence gives:

    12 - 10 = 2

which is the smallest possible distance.

If the latest occurrence is more than k away, every older occurrence
is even farther away and therefore cannot form a valid pair.


Pseudo Code:
-----------
create hash map lastIndex

for i = 0 to n-1:

    if nums[i] exists in lastIndex:
        previous = lastIndex[nums[i]]

        if i - previous <= k:
            return true

    lastIndex[nums[i]] = i

return false


Complete Optimal Code (inside comments only):
-----------------------------------------------

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> lastIndex;

        for (int i = 0; i < (int)nums.size(); i++) {

            if (lastIndex.count(nums[i]) &&
                i - lastIndex[nums[i]] <= k) {
                return true;
            }

            lastIndex[nums[i]] = i;
        }

        return false;
    }
};


Time Complexity:
----------------
Average:

    O(n)

Each element is processed once and hash-map operations are
O(1) on average.

Worst-case hash-map complexity can theoretically degrade, but
for normal competitive programming usage we consider it O(n).


Space Complexity:
-----------------
O(n)

In the worst case, all elements are distinct and the hash map stores
all n elements.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Example:

    nums = [1, 2, 3, 1]
    k = 3


Initial:
    lastIndex = {}


i = 0
---------
nums[0] = 1

1 is not present.

Store:

    lastIndex[1] = 0

Map:

    {1 -> 0}


i = 1
---------
nums[1] = 2

2 is not present.

Store:

    lastIndex[2] = 1

Map:

    {1 -> 0, 2 -> 1}


i = 2
---------
nums[2] = 3

3 is not present.

Store:

    lastIndex[3] = 2

Map:

    {1 -> 0, 2 -> 1, 3 -> 2}


i = 3
---------
nums[3] = 1

1 already exists.

Previous index:

    0

Distance:

    3 - 0 = 3

Check:

    3 <= k
    3 <= 3
    true

Therefore return:

    true


Final Answer:
-------------
true


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Hash Map + Last Seen Index


Key Observation:
----------------
For each number, only its most recent index matters.

If the latest occurrence is farther than k, all earlier occurrences
are even farther away.


Common Mistakes:
----------------
1. Checking only adjacent elements.

   The duplicate can be anywhere within distance k.

2. Using absolute difference unnecessarily.

   While scanning left to right, the current index is always greater
   than the previous index.

   Therefore:

       |i - previous| = i - previous

3. Forgetting to update the latest index.

   Always do:

       lastIndex[nums[i]] = i

   after checking the previous occurrence.

4. Updating before checking.

   If you update the map first, you may compare the element with
   itself and incorrectly get distance 0.

5. Using a set without understanding the sliding-window alternative.

   A set can also solve the problem, but the last-index hash map is
   particularly simple and directly matches the condition.

6. Ignoring k = 0.

   Since i and j must be distinct, no solution is possible when:

       k = 0

   The hash-map solution naturally handles this because the previous
   occurrence always has a smaller index, so its distance is at least 1.


When to Use This Approach:
--------------------------
Use this pattern when the problem asks:

- Whether duplicates occur within a certain index distance.
- For the nearest/previous occurrence of an element.
- For checking a condition between the current index and the
  most recent occurrence.
- For "last seen", "previous index", or "closest previous position"
  type problems.

General Pattern:

    for each element:
        if element was seen before:
            check current_index - last_index[element]

        update last_index[element]


Alternative Sliding Window Pattern:
------------------------------------
Another optimal solution is to maintain a set containing at most
k previous elements.

For every index i:

    if nums[i] is already in set:
        return true

    insert nums[i]

    if window size > k:
        remove nums[i-k]

This also gives:

    Time  = O(n) average
    Space = O(k)

The last-index hash map is usually easier to explain in interviews
because it directly tracks the previous occurrence.


Quick Revision:
---------------
Problem:
    Duplicate within distance k?

Tool:
    Hash Map

Store:
    number -> last index

Check:
    i - lastIndex[number] <= k

Complexity:
    O(n) average time
    O(n) space

================================================================================
*/

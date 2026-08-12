#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1,
                                       vector<int> &nums2,
                                       int k)
    {
        vector<vector<int>> ans;

        if (nums1.empty() || nums2.empty() || k == 0)
            return ans;

        // Min Heap:
        // {sum, index in nums1, index in nums2}
        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>>
            pq;

        // Initially insert the first pair from each row.
        // Only min(k, nums1.size()) rows can contribute
        // to the first k smallest pairs.
        for (int i = 0; i < min(k, (int)nums1.size()); i++)
        {
            pq.push({nums1[i] + nums2[0], i, 0});
        }

        while (!pq.empty() && ans.size() < k)
        {
            auto [sum, i, j] = pq.top();
            pq.pop();

            ans.push_back({nums1[i], nums2[j]});

            // Move to the next element in the same row.
            if (j + 1 < nums2.size())
            {
                pq.push({nums1[i] + nums2[j + 1],
                         i,
                         j + 1});
            }
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {1, 7, 11};
    vector<int> nums2 = {2, 4, 6};
    int k = 3;

    vector<vector<int>> ans =
        obj.kSmallestPairs(nums1, nums2, k);

    cout << "K Smallest Pairs:" << endl;

    for (auto &pair : ans)
    {
        cout << "[" << pair[0] << ", " << pair[1] << "]" << endl;
    }

    return 0;
}

/*
=========================================*
LeetCode 373: Find K Pairs with Smallest Sums
=========================================*

Problem Statement:
------------------
You are given two integer arrays nums1 and nums2
that are sorted in ascending order.

A pair consists of:

    [nums1[i], nums2[j]]

The sum of the pair is:

    nums1[i] + nums2[j]

Return the k pairs with the smallest sums.

The answer can be returned in any order.

=========================================*
Example:
=========================================*

Input:

nums1 = [1,7,11]
nums2 = [2,4,6]
k = 3

All possible pairs:

[1,2] -> 3
[1,4] -> 5
[1,6] -> 7
[7,2] -> 9
[7,4] -> 11
[7,6] -> 13
[11,2] -> 13
[11,4] -> 15
[11,6] -> 17

The 3 smallest pairs are:

[1,2]
[1,4]
[1,6]

Output:

[[1,2],[1,4],[1,6]]

=========================================*
Brute Force Approach
=========================================*

Idea:
-----
Generate every possible pair.

For every element of nums1:

    For every element of nums2:

        Store:
            sum
            nums1[i]
            nums2[j]

Then sort all pairs by their sum.

Finally, return the first k pairs.

Pseudo Code:
------------

Create empty list pairs.

For i from 0 to nums1.size()-1:

    For j from 0 to nums2.size()-1:

        Add:
            (nums1[i] + nums2[j],
             nums1[i],
             nums2[j])

Sort pairs by sum.

Return first k pairs.

Complete Brute Force Code:
--------------------------

vector<vector<int>> kSmallestPairs(
    vector<int>& nums1,
    vector<int>& nums2,
    int k)
{
    vector<tuple<int, int, int>> pairs;

    for (int i = 0; i < nums1.size(); i++)
    {
        for (int j = 0; j < nums2.size(); j++)
        {
            pairs.push_back({
                nums1[i] + nums2[j],
                nums1[i],
                nums2[j]
            });
        }
    }

    sort(pairs.begin(), pairs.end());

    vector<vector<int>> ans;

    for (int i = 0;
         i < min(k, (int)pairs.size());
         i++)
    {
        ans.push_back({
            get<1>(pairs[i]),
            get<2>(pairs[i])
        });
    }

    return ans;
}

Time Complexity:
----------------
Let:

m = nums1.size()
n = nums2.size()

There are m * n pairs.

Generating pairs:

O(m * n)

Sorting:

O(m * n * log(m * n))

Overall:

O(m * n * log(m * n))

Space Complexity:
-----------------
O(m * n)

We store every possible pair.

=========================================*
Optimal Approach
=========================================*

Observation:
------------
Both arrays are sorted.

For a fixed nums1[i]:

    nums1[i] + nums2[0]
    nums1[i] + nums2[1]
    nums1[i] + nums2[2]
    ...

are also sorted.

So we can think of every i as a sorted row:

nums1[0]:
    nums1[0]+nums2[0]
    nums1[0]+nums2[1]
    nums1[0]+nums2[2]
    ...

nums1[1]:
    nums1[1]+nums2[0]
    nums1[1]+nums2[1]
    nums1[1]+nums2[2]
    ...

nums1[2]:
    nums1[2]+nums2[0]
    nums1[2]+nums2[1]
    nums1[2]+nums2[2]
    ...

We need the k smallest values across all
these sorted rows.

This is exactly a Min Heap problem.

Intuition:
---------
Initially, put the first pair from every row
into the min heap:

(nums1[0], nums2[0])
(nums1[1], nums2[0])
(nums1[2], nums2[0])
...

The heap gives us the pair with the smallest sum.

After removing:

(nums1[i], nums2[j])

the next possible pair from the same row is:

(nums1[i], nums2[j + 1])

So we insert that next pair.

This is similar to merging multiple sorted lists.

Why only first k rows?
----------------------
We only need k pairs.

Therefore, more than k rows can never contribute
more than k required answers before some row has
already produced enough candidates.

So we initially add:

min(k, nums1.size())

pairs.

Pseudo Code:
------------

Create min heap.

For every i from 0 to min(k, nums1.size()) - 1:

    Insert:
        (nums1[i] + nums2[0], i, 0)

While heap is not empty AND answer size < k:

    Remove minimum pair:
        (sum, i, j)

    Add:
        [nums1[i], nums2[j]]

    If j + 1 exists:

        Insert:
            (nums1[i] + nums2[j+1],
             i,
             j+1)

Return answer.

Complete Optimal Code:
----------------------

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(
        vector<int>& nums1,
        vector<int>& nums2,
        int k)
    {
        vector<vector<int>> ans;

        if (nums1.empty() || nums2.empty() || k == 0)
            return ans;

        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>
        > pq;

        for (int i = 0;
             i < min(k, (int)nums1.size());
             i++)
        {
            pq.push({
                nums1[i] + nums2[0],
                i,
                0
            });
        }

        while (!pq.empty() && ans.size() < k)
        {
            auto [sum, i, j] = pq.top();
            pq.pop();

            ans.push_back({
                nums1[i],
                nums2[j]
            });

            if (j + 1 < nums2.size())
            {
                pq.push({
                    nums1[i] + nums2[j + 1],
                    i,
                    j + 1
                });
            }
        }

        return ans;
    }
};

Time Complexity:
----------------
We insert at most:

O(min(k, m))

initial elements.

We perform at most k extractions.

Each heap operation costs:

O(log k)

Therefore:

O(k log k)

Space Complexity:
-----------------
O(k)

The heap stores at most k candidates.

The answer itself also contains O(k) pairs.

=========================================*
Dry Run
=========================================*

Input:

nums1 = [1,7,11]
nums2 = [2,4,6]
k = 3

Create rows:

Row 0:

1+2 = 3
1+4 = 5
1+6 = 7

Row 1:

7+2 = 9
7+4 = 11
7+6 = 13

Row 2:

11+2 = 13
11+4 = 15
11+6 = 17

-----------------------------------------

Initial Heap:

[1,2] -> 3
[7,2] -> 9
[11,2] -> 13

-----------------------------------------

Step 1:

Smallest:

[1,2] -> 3

Add to answer.

Answer:

[1,2]

Next pair from row 0:

[1,4] -> 5

Insert into heap.

Heap:

[1,4] -> 5
[7,2] -> 9
[11,2] -> 13

-----------------------------------------

Step 2:

Smallest:

[1,4] -> 5

Add:

[1,4]

Next pair:

[1,6] -> 7

Insert.

Heap:

[1,6] -> 7
[7,2] -> 9
[11,2] -> 13

-----------------------------------------

Step 3:

Smallest:

[1,6] -> 7

Add:

[1,6]

We now have k = 3 pairs.

Final Answer:

[1,2]
[1,4]
[1,6]

=========================================*
Interview Notes:
=========================================*

Pattern:
--------
Min Heap + K-Way Merge

Key Observation:
----------------
For every fixed nums1[i], the pair sums with
nums2 are already sorted because nums2 is sorted.

Therefore, each row is a sorted list.

We need the k smallest elements from all rows.

This is a classic:

    K-Way Merge + Min Heap

problem.

Common Mistakes:
----------------
1. Generating all m*n pairs unnecessarily.

2. Using a max heap instead of a min heap.

3. Forgetting to push the next pair from the same row.

4. Adding duplicate pairs incorrectly.

5. Initializing the heap with every possible pair.

6. Forgetting that the arrays are already sorted.

When to use this approach:
--------------------------
Use this pattern when:

- Multiple sorted sequences need to be merged.
- You only need the first k smallest elements.
- Generating every combination is too expensive.
- The next candidate from a selected sequence
  can be generated easily.

Typical examples:

- K smallest pairs
- Merge K sorted arrays
- Kth smallest element
- Smallest range covering K lists

=========================================*
Complexity Summary:
=========================================*

Brute Force:

Time  -> O(m*n*log(m*n))
Space -> O(m*n)

Optimal:

Time  -> O(k*log(k))
Space -> O(k)

where:

m = nums1.size()
n = nums2.size()

=========================================*
Interview Tip:
=========================================*

Whenever you see:

"Find K smallest/largest combinations"

and the input arrays are sorted,

think:

    MIN HEAP + SORTED ROWS

For this problem:

Each nums1[i] creates one sorted row.

Heap stores the smallest unprocessed pair
from each row.

After removing one pair, push the next pair
from that same row.

=========================================*
*/
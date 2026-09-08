#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int candidate = 0, count = 0;

        for (int num : nums)
        {
            if (count == 0)
                candidate = num;

            count += (num == candidate) ? 1 : -1;
        }

        return candidate;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    cout << sol.majorityElement(nums) << '\n'; // 2

    return 0;
}

/*
============================================================
                    PROBLEM STATEMENT
============================================================

LeetCode 169 - Majority Element

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than
n / 2 times in the array.

You may assume that the majority element always exists.

============================================================
                        EXAMPLE
============================================================

Input:
nums = [2,2,1,1,1,2,2]

Output:
2

Explanation:
2 appears 4 times out of 7 elements.

4 > 7/2, so 2 is the majority element.


============================================================
                  BRUTE FORCE APPROACH
============================================================

Idea:
------
For every element, count how many times it occurs in the
array.

If its frequency is greater than n/2, return that element.

Pseudo Code:
------------
for every element x in nums:
    count = 0

    for every element y in nums:
        if x == y:
            count++

    if count > n/2:
        return x

Complete Brute Force Code:
--------------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();

        for (int x : nums) {
            int count = 0;

            for (int y : nums) {
                if (x == y)
                    count++;
            }

            if (count > n / 2)
                return x;
        }

        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    cout << sol.majorityElement(nums) << '\n';
    return 0;
}

Time Complexity:
----------------
O(n^2)

Space Complexity:
-----------------
O(1)


============================================================
                   OPTIMAL APPROACH
============================================================

Observation:
------------
The majority element occurs more than n/2 times.

Therefore, it occurs more frequently than all other elements
combined.

Intuition:
----------
Use the Boyer-Moore Voting Algorithm.

Maintain:
- candidate = current possible majority element
- count = its current vote balance

For every number:

1. If count == 0, choose the current number as candidate.
2. If current number == candidate, increase count.
3. Otherwise, decrease count.

A majority element cannot be completely cancelled because
it appears more than all other elements combined.

Pseudo Code:
------------
candidate = 0
count = 0

for num in nums:
    if count == 0:
        candidate = num

    if num == candidate:
        count++
    else:
        count--

return candidate

Complete Optimal Code:
----------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0, count = 0;

        for (int num : nums) {
            if (count == 0)
                candidate = num;

            count += (num == candidate) ? 1 : -1;
        }

        return candidate;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    cout << sol.majorityElement(nums) << '\n';
    return 0;
}

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(1)


============================================================
                        DRY RUN
============================================================

Example:
nums = [2, 2, 1, 1, 1, 2, 2]

Initially:
candidate = 0
count = 0

1. num = 2
   count == 0 -> candidate = 2
   2 == 2 -> count = 1

2. num = 2
   2 == 2 -> count = 2

3. num = 1
   1 != 2 -> count = 1

4. num = 1
   1 != 2 -> count = 0

5. num = 1
   count == 0 -> candidate = 1
   1 == 1 -> count = 1

6. num = 2
   2 != 1 -> count = 0

7. num = 2
   count == 0 -> candidate = 2
   2 == 2 -> count = 1

Final:
candidate = 2

Answer = 2


============================================================
                     INTERVIEW NOTES
============================================================

Pattern:
--------
Boyer-Moore Voting Algorithm / Cancellation Technique.

Key Observation:
----------------
The majority element appears more than n/2 times.

So, even if every occurrence of a non-majority element cancels
one occurrence of the majority element, some majority
occurrences will always remain.

Common Mistakes:
----------------
1. Forgetting that the problem guarantees a majority element.
2. Returning the candidate in variants where majority is NOT
   guaranteed without verifying its frequency.
3. Using O(n) extra space unnecessarily with a frequency map.
4. Confusing "majority" (> n/2) with "most frequent".

When to use this approach:
--------------------------
Use Boyer-Moore Voting when:
- There is a guaranteed majority element.
- The majority threshold is greater than n/2.
- O(1) extra space is required or preferred.
- You need a linear-time solution.

============================================================
*/

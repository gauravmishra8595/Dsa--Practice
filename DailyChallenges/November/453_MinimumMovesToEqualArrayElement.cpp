#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();

        long long sum = accumulate(nums.begin(), nums.end(), 0LL);
        int min_el = *min_element(nums.begin(), nums.end());

        return sum - (long long)n * min_el;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    cout << sol.minMoves(nums) << endl;
    return 0;
};

/*
=========================================================
       LEETCODE 453 - MINIMUM MOVES TO EQUAL ARRAY
=========================================================

1. PROBLEM STATEMENT
--------------------
Given an integer array nums, in one move, you can
increment n - 1 elements by 1.

Return the minimum number of moves required to make
all array elements equal.


2. EXAMPLE
----------
Input:
nums = [1, 2, 3]

Output:
3

Explanation:
[1, 2, 3]
[1, 2, 2]
[1, 1, 2]
[1, 1, 1]

Total moves = 3.


3. BRUTE FORCE APPROACH
-----------------------

Idea:
-----
Try to simulate the operations.

In every operation:
1. Find the maximum element.
2. Increment all elements except one maximum element.
3. Repeat until all elements become equal.

Pseudo Code:
------------
1. While elements are not equal:
   a. Find maximum element.
   b. Increment all elements except one maximum.
   c. Increase moves.
2. Return moves.

Complete Brute Force Code:
--------------------------

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int moves = 0;

        while (true) {
            int mini = *min_element(nums.begin(), nums.end());
            int maxi = *max_element(nums.begin(), nums.end());

            if (mini == maxi)
                return moves;

            int maxIndex = max_element(nums.begin(), nums.end())
                           - nums.begin();

            for (int i = 0; i < nums.size(); i++) {
                if (i != maxIndex) {
                    nums[i]++;
                }
            }

            moves++;
        }
    }
};

Time Complexity:
----------------
O(moves * n) for each simulation step.

Space Complexity:
-----------------
O(1)

Note:
Brute force simulation can be extremely slow.


4. OPTIMAL APPROACH
-------------------

Observation:
------------
Incrementing n-1 elements by 1 is equivalent to
decrementing one element by 1.

Therefore, instead of incrementing n-1 elements,
we can think of reducing every element to the
minimum element.

Intuition:
----------
To make all elements equal with minimum operations,
we should make every element equal to the smallest
element in the array.

Example:
nums = [1, 2, 3]

Minimum element = 1

Required operations:
1 - 1 = 0
2 - 1 = 1
3 - 1 = 2

Total moves = 0 + 1 + 2 = 3.

Mathematical Formula:
---------------------

moves = (nums[0] - min)
      + (nums[1] - min)
      + ...
      + (nums[n-1] - min)

Simplified Formula:

moves = sum(nums) - (n * min_element)


Pseudo Code:
------------
1. Find n = nums.size().
2. Calculate sum of all elements.
3. Find minimum element.
4. Calculate:

   moves = sum - (n * minimum)

5. Return moves.


Complete Optimal Code:
----------------------

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();

        long long sum = accumulate(
            nums.begin(), nums.end(), 0LL
        );

        int min_el = *min_element(
            nums.begin(), nums.end()
        );

        return sum - (long long)n * min_el;
    }
};

Time Complexity:
----------------
O(n)

- accumulate() takes O(n).
- min_element() takes O(n).
- Formula calculation takes O(1).

Space Complexity:
-----------------
O(1)

No additional data structure is used.


5. DRY RUN WITH EXAMPLE
-----------------------

Input:
nums = [1, 2, 3]

Step 1:
n = 3

Step 2:
sum = 1 + 2 + 3
sum = 6

Step 3:
min_el = 1

Step 4:
Apply formula:

moves = sum - (n * min_el)

moves = 6 - (3 * 1)

moves = 6 - 3

moves = 3

Output:
3


6. INTERVIEW NOTES
------------------

Pattern:
--------
Mathematical Observation / Array / Greedy

Key Observation:
----------------
Incrementing n-1 elements by 1 is equivalent
to decrementing one element by 1.

Therefore, reduce every element to the minimum.

Common Mistakes:
----------------
1. Comparing only adjacent elements.
2. Trying to simulate every operation.
3. Choosing the maximum instead of minimum.
4. Forgetting that exactly n-1 elements are
   incremented in each operation.
5. Integer overflow while calculating the sum.
6. Using int instead of long long for intermediate
   calculations when values can be large.

When to Use This Approach:
--------------------------
1. When an operation affects all elements except one.
2. When incrementing many elements can be transformed
   into decrementing one element.
3. When a mathematical observation eliminates
   repeated simulation.
4. When the goal is to make all array elements equal.

=========================================================
                 END OF NOTES
=========================================================
*/
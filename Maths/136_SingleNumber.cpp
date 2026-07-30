#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ans = 0;

        for (int num : nums)
        {
            ans ^= num;
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {4, 1, 2, 1, 2};

    cout << obj.singleNumber(nums) << endl; // Output: 4

    return 0;
}

/*

========================================
LeetCode 136. Single Number
========================================

Problem Statement:
Given a non-empty array of integers nums, every element appears twice
except for one. Find that single element.

You must implement a solution with linear runtime complexity and use
constant extra space.

--------------------------------------------------
Example
--------------------------------------------------

Input:
nums = [4,1,2,1,2]

Output:
4

Explanation:
1 appears twice.
2 appears twice.
4 appears once.

==================================================
Brute Force Approach
==================================================

Idea:
For every element, count how many times it appears in the array.

The element with frequency 1 is the answer.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

for every element i in nums:

    count = 0

    for every element j in nums:

        if nums[i] == nums[j]
            count++

    if count == 1
        return nums[i]

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int singleNumber(vector<int>& nums) {

        for(int i = 0; i < nums.size(); i++) {

            int count = 0;

            for(int j = 0; j < nums.size(); j++) {

                if(nums[i] == nums[j])
                    count++;
            }

            if(count == 1)
                return nums[i];
        }

        return -1;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(N^2)

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Optimal Approach
==================================================

Observation:

Use XOR operation.

Properties of XOR:

1. a ^ a = 0

2. a ^ 0 = a

3. XOR is commutative:
   a ^ b = b ^ a

Since every number appears twice except one:

All duplicate numbers cancel out.

Example:

4 ^ 1 ^ 2 ^ 1 ^ 2

Rearrange:

4 ^ (1 ^ 1) ^ (2 ^ 2)

= 4 ^ 0 ^ 0

= 4

--------------------------------------------------
Intuition
--------------------------------------------------

Apply XOR on all elements.

Pairs of same numbers become zero,
and the remaining number is the answer.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

answer = 0

for every number in nums:

    answer = answer XOR number

return answer

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int singleNumber(vector<int>& nums) {

        int ans = 0;

        for(int num : nums) {
            ans ^= num;
        }

        return ans;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(N)

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Dry Run With Example
==================================================

Input:

nums = [4,1,2,1,2]


Initial:

ans = 0


Step 1:

ans = 0 ^ 4

ans = 4


Step 2:

ans = 4 ^ 1

ans = 5


Step 3:

ans = 5 ^ 2

ans = 7


Step 4:

ans = 7 ^ 1

ans = 6


Step 5:

ans = 6 ^ 2

ans = 4


Final Answer:

4

==================================================
Interview Notes
==================================================

Pattern:
- Bit Manipulation
- XOR Trick
- Frequency Cancellation

Key Observation:
Every duplicate element cancels using XOR,
leaving only the unique element.

Common Mistakes:
- Using extra hashmap when constant space is required.
- Forgetting XOR properties.
- Sorting unnecessarily and increasing complexity.

When to use this approach:
- One unique element among pairs.
- Finding missing/odd occurring numbers.
- Bitwise cancellation problems.
- Constant space frequency problems.

*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxi = nums[0];
        int pre = 1, suff = 1;
        int n = nums.size();

        for(int i = 0; i < n; i++) {
            if(pre == 0) pre = 1;
            if(suff == 0) suff = 1;

            pre *= nums[i];
            suff *= nums[n - i - 1];

            maxi = max(maxi, max(pre, suff));
        }

        return maxi;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {2, 3, -2, 4};

    cout << "Maximum Product Subarray: " << obj.maxProduct(nums) << endl;

    return 0;
}

/*

===========================
LeetCode 152. Maximum Product Subarray
===========================

Problem Statement:
Given an integer array nums, find a contiguous non-empty subarray within the array
that has the largest product, and return the product.

--------------------------------------------------
Example:
--------------------------------------------------

Input:
nums = [2,3,-2,4]

Output:
6

Explanation:
Subarray [2,3] has the largest product = 6.

==================================================
BRUTE FORCE APPROACH
==================================================

Idea:
Generate every possible subarray.
For every subarray compute its product.
Keep updating the maximum product.

----------------------------------------
Pseudo Code
----------------------------------------

answer = -INF

for i = 0 to n-1
    product = 1
    for j = i to n-1
        product *= nums[j]
        answer = max(answer, product)

return answer

----------------------------------------
Complete Brute Force Code
----------------------------------------

class Solution {
public:
    int maxProduct(vector<int>& nums) {

        int n = nums.size();
        int ans = INT_MIN;

        for(int i=0;i<n;i++){

            int product=1;

            for(int j=i;j<n;j++){

                product*=nums[j];
                ans=max(ans,product);

            }

        }

        return ans;
    }
};

----------------------------------------
Time Complexity
----------------------------------------

O(N^2)

----------------------------------------
Space Complexity
----------------------------------------

O(1)

==================================================
OPTIMAL APPROACH
==================================================

Observation:

Negative numbers can convert the smallest negative product into the
largest positive product.

A zero breaks the product chain.

Instead of tracking only prefix product, also track suffix product.

Maximum answer can appear while traversing from either side.

----------------------------------------
Intuition
----------------------------------------

Maintain

prefix product from left

suffix product from right

Whenever either becomes zero,
restart it from 1 because product chain is broken.

At every step,
answer = max(answer, prefix, suffix)

This automatically handles

1. Even number of negatives
2. Odd number of negatives
3. Zeros

----------------------------------------
Pseudo Code
----------------------------------------

prefix = 1
suffix = 1
answer = nums[0]

for i from 0 to n-1

    if prefix == 0
        prefix = 1

    if suffix == 0
        suffix = 1

    prefix *= nums[i]

    suffix *= nums[n-i-1]

    answer = max(answer, prefix, suffix)

return answer

----------------------------------------
Complete Optimal Code
----------------------------------------

class Solution {
public:

    int maxProduct(vector<int>& nums) {

        int maxi = nums[0];
        int pre = 1;
        int suff = 1;

        int n = nums.size();

        for(int i = 0; i < n; i++) {

            if(pre == 0)
                pre = 1;

            if(suff == 0)
                suff = 1;

            pre *= nums[i];
            suff *= nums[n-i-1];

            maxi = max(maxi, max(pre, suff));
        }

        return maxi;
    }
};

----------------------------------------
Time Complexity
----------------------------------------

O(N)

----------------------------------------
Space Complexity
----------------------------------------

O(1)

==================================================
Dry Run
==================================================

nums = [2,3,-2,4]

Initial

pre = 1
suff = 1
maxi = 2

--------------------------------

i = 0

pre = 2

suff = 4

maxi = 4

--------------------------------

i = 1

pre = 6

suff = -8

maxi = 6

--------------------------------

i = 2

pre = -12

suff = -24

maxi = 6

--------------------------------

i = 3

pre = -48

suff = -48

maxi = 6

Answer = 6

==================================================
Interview Notes
==================================================

Pattern:
- Prefix & Suffix Traversal
- Array Traversal
- Product Handling
- Kadane Variant

Key Observation:
- Product behaves differently than sum.
- Negative numbers can flip the sign.
- Traversing from both ends naturally handles odd/even negatives.
- Reset after zero because product chain breaks.

Common Mistakes:
- Forgetting to reset after zero.
- Using only prefix traversal.
- Initializing answer with 0 instead of nums[0].
- Ignoring arrays containing all negative numbers.

When to use this approach:
- Maximum product subarray.
- Problems involving products with negatives.
- Constant-space linear traversal requirement.

*/

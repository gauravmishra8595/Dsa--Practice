#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);

        int prefix = 1;
        for (int i = 0; i < n; i++) {
            ans[i] = prefix;
            prefix *= nums[i];
        }

        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            ans[i] *= suffix;
            suffix *= nums[i];
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 4};

    vector<int> result = sol.productExceptSelf(nums);

    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}

/*
============================================================
                    LEETCODE 238
              Product of Array Except Self
============================================================

Problem Statement:
------------------
Given an integer array nums, return an array answer such that
answer[i] is equal to the product of all the elements of nums
except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit
in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without
using the division operation.


Example:
--------
Input:
nums = [1,2,3,4]

Output:
[24,12,8,6]

Explanation:
answer[0] = 2*3*4 = 24
answer[1] = 1*3*4 = 12
answer[2] = 1*2*4 = 8
answer[3] = 1*2*3 = 6


============================================================
Brute Force Approach
============================================================

Idea:
-----
For every index, calculate the product of all elements except
the current index.

For each element:
- Traverse the whole array.
- Multiply all elements except itself.
- Store the result.

Pseudo Code:
------------
for i from 0 to n-1:
    product = 1

    for j from 0 to n-1:
        if i != j:
            product *= nums[j]

    answer[i] = product


Complete Brute Force Code:

*/
/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            int product = 1;

            for (int j = 0; j < n; j++) {
                if (i != j) {
                    product *= nums[j];
                }
            }

            ans[i] = product;
        }

        return ans;
    }
};
*/

/*
Time Complexity:
----------------
O(n^2)

Space Complexity:
-----------------
O(1) extra space (excluding output array)


============================================================
Optimal Approach
============================================================

Observation:
------------
For every index:

answer[i] = product of elements before i *
           product of elements after i

So we can store prefix products and suffix products.

Instead of using extra arrays:
- First pass stores prefix product in answer array.
- Second pass multiplies suffix product into answer array.


Intuition:
----------
For nums = [1,2,3,4]

Prefix products:
[1,1,2,6]

Suffix products:
[24,12,4,1]

Multiplying corresponding prefix and suffix values gives:

[24,12,8,6]


Pseudo Code:
------------
Create answer array of size n filled with 1

prefix = 1

for i from 0 to n-1:
    answer[i] = prefix
    prefix *= nums[i]


suffix = 1

for i from n-1 to 0:
    answer[i] *= suffix
    suffix *= nums[i]


return answer


Complete Optimal Code:

*/
/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);

        int prefix = 1;

        for (int i = 0; i < n; i++) {
            ans[i] = prefix;
            prefix *= nums[i];
        }

        int suffix = 1;

        for (int i = n - 1; i >= 0; i--) {
            ans[i] *= suffix;
            suffix *= nums[i];
        }

        return ans;
    }
};
*/


// Time Complexity:
// ----------------
// O(n)

// Space Complexity:
// -----------------
// O(1) extra space
// (Output array is not counted as extra space)


// ============================================================
// Dry Run With Example
// ============================================================

// Input:
// nums = [1,2,3,4]


// Step 1: Prefix Pass

// Initial:
// answer = [1,1,1,1]
// prefix = 1


// i = 0:
// answer[0] = 1
// prefix = 1

// answer = [1,1,1,1]


// i = 1:
// answer[1] = 1
// prefix = 2

// answer = [1,1,1,1]


// i = 2:
// answer[2] = 2
// prefix = 6

// answer = [1,1,2,1]


// i = 3:
// answer[3] = 6
// prefix = 24

// answer = [1,1,2,6]


// Step 2: Suffix Pass

// suffix = 1


// i = 3:
// answer[3] = 6 * 1 = 6
// suffix = 4


// i = 2:
// answer[2] = 2 * 4 = 8
// suffix = 12


// i = 1:
// answer[1] = 1 * 12 = 12
// suffix = 24


// i = 0:
// answer[0] = 1 * 24 = 24
// suffix = 24


// Final Answer:
// [24,12,8,6]


// ============================================================
// Interview Notes
// ============================================================

// Pattern:
// --------
// Prefix and Suffix Product Pattern


// Key Observation:
// ----------------
// Each answer[i] can be divided into two parts:

// Left side product  *  Right side product

// Using prefix and suffix multiplication avoids nested loops.


// Common Mistakes:
// ----------------
// 1. Using division operator.
//    - Not allowed because of zero handling.

// 2. Forgetting that answer array can store prefix values.

// 3. Using extra prefix and suffix arrays unnecessarily.

// 4. Incorrect order while calculating suffix products.


// When to use this approach:
// --------------------------
// Use this approach when:
// - You need product/sum/count excluding current index.
// - The answer depends on left and right side information.
// - O(n) solution is required.
// - Division is restricted or zero values exist.

// ============================================================
// */
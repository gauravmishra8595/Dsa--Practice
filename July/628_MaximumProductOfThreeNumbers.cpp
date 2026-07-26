#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        int min1 = INT_MAX, min2 = INT_MAX;

        for (int i = 0; i < n; i++) {
            // Track top 3 maximum
            if (nums[i] > max1) {
                max3 = max2;
                max2 = max1;
                max1 = nums[i];
            } else if (nums[i] > max2) {
                max3 = max2;
                max2 = nums[i];
            } else if (nums[i] > max3) {
                max3 = nums[i];
            }

            // Track bottom 2 minimum
            if (nums[i] < min1) {
                min2 = min1;
                min1 = nums[i];
            } else if (nums[i] < min2) {
                min2 = nums[i];
            }
        }

        return max(max1 * max2 * max3, max1 * min1 * min2);
    }
};

int main() {
    Solution sol;
    
    vector<int> test1 = {1, 2, 3};
    cout << "Test 1: " << sol.maximumProduct(test1) << endl;   // Expected: 6
    
    vector<int> test2 = {1, 2, 3, 4};
    cout << "Test 2: " << sol.maximumProduct(test2) << endl;   // Expected: 24
    
    vector<int> test3 = {-1, -2, -3};
    cout << "Test 3: " << sol.maximumProduct(test3) << endl;  // Expected: -6
    
    vector<int> test4 = {-100, -98, -1, 2, 3, 4};
    cout << "Test 4: " << sol.maximumProduct(test4) << endl;  // Expected: 39200
    
    vector<int> test5 = {-1, -2, -3, -4, -5};
    cout << "Test 5: " << sol.maximumProduct(test5) << endl;  // Expected: -6

    return 0;
}

/*
================================================================================
PROBLEM STATEMENT:
--------------------------------------------------------------------------------
Given an integer array nums, find three numbers whose product is maximum and 
return the maximum product.

Constraints:
- 3 <= nums.length <= 10^4
- -1000 <= nums[i] <= 1000
================================================================================

EXAMPLE:
--------------------------------------------------------------------------------
Input: nums = [1, 2, 3, 4]
Output: 24
Explanation: 2 * 3 * 4 = 24

Input: nums = [-100, -98, -1, 2, 3, 4]
Output: 39200
Explanation: (-100) * (-98) * 4 = 39200
================================================================================

BRUTE FORCE APPROACH:
--------------------------------------------------------------------------------
IDEA:
Generate all possible triplets using three nested loops, compute their product,
and keep track of the maximum product found.

PSEUDO CODE:
function maximumProduct(nums):
    n = nums.length
    maxProd = -infinity
    for i from 0 to n-3:
        for j from i+1 to n-2:
            for k from j+1 to n-1:
                prod = nums[i] * nums[j] * nums[k]
                maxProd = max(maxProd, prod)
    return maxProd

COMPLETE BRUTE FORCE CODE:
// class Solution {
// public:
//     int maximumProduct(vector<int>& nums) {
//         int n = nums.size();
//         long long maxProd = LLONG_MIN;
//         for (int i = 0; i < n - 2; i++) {
//             for (int j = i + 1; j < n - 1; j++) {
//                 for (int k = j + 1; k < n; k++) {
//                     long long prod = (long long)nums[i] * nums[j] * nums[k];
//                     maxProd = max(maxProd, prod);
//                 }
//             }
//         }
//         return (int)maxProd;
//     }
// };

TIME COMPLEXITY: O(n^3)
- Three nested loops iterating over all possible triplets.

SPACE COMPLEXITY: O(1)
- No extra space used, only a few variables.
================================================================================

OPTIMAL APPROACH:
--------------------------------------------------------------------------------
OBSERVATION:
The maximum product of three numbers can only be formed in ONE of two ways:
1. Product of the THREE LARGEST numbers (works when all positive or all negative)
2. Product of the TWO SMALLEST (most negative) numbers and the LARGEST number
   (works when we have at least two negatives: negative * negative = positive)

There is NO other combination that can yield a larger product.

INTUITION:
- If all numbers are positive: answer = top 3 largest
- If all numbers are negative: answer = top 3 largest (least negative)
- If mix of positive and negative: either top 3 largest OR 
  (2 most negative × 1 largest positive) could be the answer
- We never need more than 5 numbers: top 3 max and bottom 2 min

PSEUDO CODE:
function maximumProduct(nums):
    max1, max2, max3 = -infinity
    min1, min2 = +infinity
    
    for each num in nums:
        // Update top 3 maximums
        if num > max1:
            max3 = max2
            max2 = max1
            max1 = num
        else if num > max2:
            max3 = max2
            max2 = num
        else if num > max3:
            max3 = num
        
        // Update bottom 2 minimums
        if num < min1:
            min2 = min1
            min1 = num
        else if num < min2:
            min2 = num
    
    return max(max1 * max2 * max3, max1 * min1 * min2)

COMPLETE OPTIMAL CODE:
// class Solution {
// public:
//     int maximumProduct(vector<int>& nums) {
//         int n = nums.size();
//         int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
//         int min1 = INT_MAX, min2 = INT_MAX;
//
//         for (int i = 0; i < n; i++) {
//             if (nums[i] > max1) {
//                 max3 = max2;
//                 max2 = max1;
//                 max1 = nums[i];
//             } else if (nums[i] > max2) {
//                 max3 = max2;
//                 max2 = nums[i];
//             } else if (nums[i] > max3) {
//                 max3 = nums[i];
//             }
//
//             if (nums[i] < min1) {
//                 min2 = min1;
//                 min1 = nums[i];
//             } else if (nums[i] < min2) {
//                 min2 = nums[i];
//             }
//         }
//
//         return max(max1 * max2 * max3, max1 * min1 * min2);
//     }
// };

TIME COMPLEXITY: O(n)
- Single pass through the array to find top 3 max and bottom 2 min.

SPACE COMPLEXITY: O(1)
- Only 5 variables used regardless of input size.

ALTERNATIVE (Sorting):
- Sort the array: O(n log n)
- Return max(nums[n-1]*nums[n-2]*nums[n-3], nums[0]*nums[1]*nums[n-1])
- Simpler to write but slower than single pass approach.
================================================================================

DRY RUN WITH EXAMPLE:
--------------------------------------------------------------------------------
Input: nums = [-100, -98, -1, 2, 3, 4]

Processing each element:
--------------------------------------------------
Element: -100
  max1=-100, max2=INT_MIN, max3=INT_MIN
  min1=-100, min2=INT_MAX

Element: -98
  max1=-100, max2=-98, max3=INT_MIN  (-98 > INT_MIN but < -100)
  min1=-100, min2=-98                 (-98 < INT_MAX but > -100)

Element: -1
  max1=-1, max2=-98, max3=-100       (-1 > -100, cascade down)
  min1=-100, min2=-98                 (-1 > -98, no change)

Element: 2
  max1=2, max2=-1, max3=-98          (2 > -1, cascade down)
  min1=-100, min2=-98                 (2 > -98, no change)

Element: 3
  max1=3, max2=2, max3=-1            (3 > 2, cascade down)
  min1=-100, min2=-98                 (3 > -98, no change)

Element: 4
  max1=4, max2=3, max3=2             (4 > 3, cascade down)
  min1=-100, min2=-98                 (4 > -98, no change)

Final values:
  max1=4, max2=3, max3=2
  min1=-100, min2=-98

Calculate:
  Option 1: max1 * max2 * max3 = 4 * 3 * 2 = 24
  Option 2: max1 * min1 * min2 = 4 * (-100) * (-98) = 39200

Result: max(24, 39200) = 39200 ✓
================================================================================

INTERVIEW NOTES:
--------------------------------------------------------------------------------
PATTERN:
- "Find k largest/smallest elements" → Single pass tracking technique
- "Maximum/Minimum product of k elements" → Combine extreme values

KEY OBSERVATION:
- For maximum product of 3 numbers, you only need 5 numbers total:
  (3 largest + 2 smallest). No other combination matters.
- Negative × Negative = Positive is the key insight that makes the 
  two-minimums case relevant.

COMMON MISTAKES:
1. Only considering the 3 largest numbers and forgetting the 
   (2 smallest × 1 largest) case with negative numbers.
2. Using int for product calculation (overflow possible with values up to 1000).
   Note: 1000^3 = 10^9 which fits in int, but it's good practice to be careful.
3. Incorrectly updating the tracked values (not cascading properly when 
   a new maximum is found).
4. Sorting when O(n) is possible (shows lack of optimization thinking).

WHEN TO USE THIS APPROACH:
- Finding max/min product/sum of exactly k elements
- Array contains both positive and negative numbers
- You need top-k or bottom-k elements without full sorting
- Similar problems: max product subarray, max sum of k elements
================================================================================
*/
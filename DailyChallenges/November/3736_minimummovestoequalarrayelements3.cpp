#include <bits/stdc++.h>
using namespace std;

// ==========================================
// OPTIMAL SOLUTION IMPLEMENTATION (RUNNABLE)
// ==========================================
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int max_val = 0;
        int sum_val = 0;
        
        for (int x : nums) {
            max_val = max(max_val, x);
            sum_val += x;
        }
        
        return max_val * n - sum_val;
    }
};

// Driver code for local testing in VS Code
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution solver;
    
    // Test Case 1
    vector<int> nums1 = {1, 2, 3};
    cout << "Test Case 1 Output: " << solver.minMoves(nums1) << " (Expected: 3)" << "\n";
    
    // Test Case 2
    vector<int> nums2 = {1, 1, 1};
    cout << "Test Case 2 Output: " << solver.minMoves(nums2) << " (Expected: 0)" << "\n";
    
    return 0;
}

/*
================================================================================
COMPETITIVE PROGRAMMING NOTEBOOK ENTRY: LEETCODE 3736
================================================================================

PROBLEM STATEMENT
-----------------
Given an integer array 'nums', return the minimum number of moves required to make 
All array elements equal. In one move, you can increment n - 1 elements by 1 
(where n is the size of the array).

EXAMPLE
-------
Input: nums = [1, 2, 3]
Output: 3
Explanation:
- Start: [1, 2, 3]
- Move 1 (increment first two elements): [2, 3, 3]
- Move 2 (increment first and last elements): [3, 4, 3]
- Move 3 (increment first and last elements): [4, 4, 4]
Total moves = 3.

================================================================================
BRUTE FORCE APPROACH
================================================================================
Idea:
- Simulating the operations directly.
- In each step, find the maximum element in the array.
- Increment all other n - 1 elements by 1.
- Repeat this process until all elements in the array become equal.
- This approach is highly inefficient and will result in a Time Limit Exceeded (TLE)
  for larger inputs.

Pseudo Code:
function minMovesBruteForce(nums):
    moves = 0
    while not all elements in nums are equal:
        max_idx = index of maximum element in nums
        for i from 0 to nums.length - 1:
            if i != max_idx:
                nums[i] = nums[i] + 1
        moves = moves + 1
    return moves

Complete Brute Force Code:
---------------------------
class BruteForceSolution {
public:
    int minMoves(vector<int>& nums) {
        int moves = 0;
        while (true) {
            int min_val = nums[0], max_val = nums[0];
            int max_idx = 0;
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] > max_val) {
                    max_val = nums[i];
                    max_idx = i;
                }
                if (nums[i] < min_val) {
                    min_val = nums[i];
                }
            }
            if (min_val == max_val) break;
            for (int i = 0; i < nums.size(); i++) {
                if (i != max_idx) nums[i]++;
            }
            moves++;
        }
        return moves;
    }
};

Time Complexity: O(k * n), where k is the number of moves and n is array size. k can be very large.
Space Complexity: O(1) auxiliary space.

================================================================================
OPTIMAL APPROACH
================================================================================
Observation:
- Incrementing n - 1 elements by 1 is mathematically equivalent to decrementing 
  exactly 1 element by 1 in terms of relative differences.
- However, the problem asks to make elements equal by incrementing n - 1 elements 
  towards a target maximum element value. 
- Let 'm' be the number of moves required. Each move adds 1 to n - 1 elements, 
  increasing the total sum of the array by (n - 1) * m.
- If all elements become equal to a final value 'x', the final sum will be n * x.
- Thus: Initial_Sum + m * (n - 1) = n * x
- Since we want the minimum moves, the target value 'x' must scale based on the 
  maximum element initially present in the array to ensure no elements lag behind 
  unduly. In this version, targeting the maximum value directly translates to:
  Total Moves = (Max_Element * n) - Initial_Sum.

Intuition:
- Think of it as counting how many steps each element needs to catch up to the 
  maximum element in the array. 
- The total moves needed is the sum of differences between the maximum element 
  and every individual element in the array.

Pseudo Code:
function minMovesOptimal(nums):
    n = nums.length
    max_val = 0
    sum_val = 0
    for element in nums:
        max_val = max(max_val, element)
        sum_val = sum_val + element
    return (max_val * n) - sum_val

Complete Optimal Code:
----------------------
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int max_val = 0;
        int sum_val = 0;
        for (int x : nums) {
            max_val = max(max_val, x);
            sum_val += x;
        }
        return max_val * n - sum_val;
    }
};

Time Complexity: O(n) - Single pass to find max and sum.
Space Complexity: O(1) - Constants used for accumulation.

================================================================================
DRY RUN WITH EXAMPLE
================================================================================
Input: nums = [1, 2, 3]

1. Initialization:
   n = 3, max_val = 0, sum_val = 0

2. Loop:
   - x = 1: max_val = max(0, 1) = 1, sum_val = 0 + 1 = 1
   - x = 2: max_val = max(1, 2) = 2, sum_val = 1 + 2 = 3
   - x = 3: max_val = max(2, 3) = 3, sum_val = 3 + 3 = 6

3. Calculation:
   Result = (max_val * n) - sum_val
          = (3 * 3) - 6
          = 9 - 6 
          = 3

Output matches expected: 3.

================================================================================
INTERVIEW NOTES
================================================================================
Pattern:
- Mathematical reduction / Relative delta manipulation.

Key Observation:
- Instead of tracking simulated increments across complex subsets, view the problem 
  from the perspective of gaps relative to the ceiling element.

Common Mistakes:
- Attempting to simulate the process, leading to TLE.
- Integer overflow: Ensure that `max_val * n` or `sum_val` fits within standard 
  integer limits. If constraints allow large numbers, switch to `long long`.

When to use this approach:
- When a problem involves modifying a subset of size (n - 1) or requires evaluating 
  uniform states using bulk increment/decrement operations.
*/

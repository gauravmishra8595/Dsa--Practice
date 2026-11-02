#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        // Finding the median in O(n) average time using Quickselect
        auto it = nums.begin() + n / 2;
        nth_element(nums.begin(), it, nums.end());
        int median = *it;
        
        int moves = 0;
        for (int num : nums) {
            moves += abs(num - median);
        }
        return moves;
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test Case 1
    vector<int> nums1 = {1, 2, 3};
    Solution sol;
    cout << "Test Case 1 Expected: 2, Got: " << sol.minMoves2(nums1) << "\n";
    
    // Test Case 2
    vector<int> nums2 = {1, 10, 2, 9};
    cout << "Test Case 2 Expected: 16, Got: " << sol.minMoves2(nums2) << "\n";
    
    return 0;
}

/*
================================================================================
DSA PRACTICE NOTEBOOK: LEETCODE 462 - MINIMUM MOVES TO EQUAL ARRAY ELEMENTS II
================================================================================

--------------------------------------------------------------------------------
PROBLEM STATEMENT
--------------------------------------------------------------------------------
Given an integer array `nums` of size `n`, return the minimum number of moves 
required to make all array elements equal.

In one move, you can increment or decrement an element of the array by 1.
Test cases are designed so that the answer will fit in a 32-bit integer.

--------------------------------------------------------------------------------
EXAMPLE
--------------------------------------------------------------------------------
Input: nums = [1, 10, 2, 9]
Output: 16
Explanation:
- Target value = 2:  abs(1-2) + abs(10-2) + abs(2-2) + abs(9-2)  = 1 + 8 + 0 + 7 = 16
- Target value = 9:  abs(1-9) + abs(10-9) + abs(2-9) + abs(9-9)  = 8 + 1 + 7 + 0 = 16
Minimum moves required is 16.

--------------------------------------------------------------------------------
BRUTE FORCE APPROACH
--------------------------------------------------------------------------------
- Idea:
  Iterate through all possible target elements. Since the optimal target value 
  must lie between the minimum and maximum value of the array (and specifically 
  matches one of the existing elements to minimize distances), we can try setting
  every element in `nums` as the target. For each choice, compute the total 
  moves required and find the absolute minimum.

- Pseudo Code:
  function minMovesBruteForce(nums):
      min_total_moves = infinity
      for target in nums:
          current_moves = 0
          for num in nums:
              current_moves += abs(num - target)
          min_total_moves = min(min_total_moves, current_moves)
      return min_total_moves

- Complete Brute Force Code:
  int minMoves2Brute(vector<int>& nums) {
      int min_moves = INT_MAX;
      for (int i = 0; i < nums.size(); i++) {
          int current_moves = 0;
          for (int j = 0; j < nums.size(); j++) {
              current_moves += abs(nums[j] - nums[i]);
          }
          min_moves = min(min_moves, current_moves);
      }
      return min_moves;
  }

- Time Complexity: O(n^2) - Nested loops scanning the array for every target choice.
- Space Complexity: O(1) - Modifies nothing and uses constant extra space.

--------------------------------------------------------------------------------
OPTIMAL APPROACH
--------------------------------------------------------------------------------
- Observation:
  Geometric minimization problem. The sum of absolute deviations \sum |x_i - k|
  is minimized when `k` is the median of the distribution. If we pick any point
  outside the median, moving closer to the median decreases the distance for a 
  majority of elements while increasing it for a minority, leading to a net decrease
  in total moves.

- Intuition:
  Consider two points, A and B. For any point X between A and B, the total distance 
  AX + XB is constant and equals B - A. If X is outside [A, B], the distance increases.
  Extending this to multiple pairs, the optimal point must lie inside all nested pairs, 
  which precisely converges on the median element.

- Pseudo Code:
  function minMovesOptimal(nums):
      n = length(nums)
      median = find_nth_element(nums, n / 2) // Quickselect partitioning
      moves = 0
      for num in nums:
          moves += abs(num - median)
      return moves

- Complete Optimal Code:
  int minMoves2(vector<int>& nums) {
      int n = nums.size();
      auto it = nums.begin() + n / 2;
      nth_element(nums.begin(), it, nums.end());
      int median = *it;
      
      int moves = 0;
      for (int num : nums) {
          moves += abs(num - median);
      }
      return moves;
  }

- Time Complexity: O(n) average time complexity using `std::nth_element` (Quickselect).
- Space Complexity: O(1) auxiliary space as it performs in-place rearrangement.

--------------------------------------------------------------------------------
DRY RUN WITH EXAMPLE
--------------------------------------------------------------------------------
Input Array:, size n = 4

1. Find Median:
   Target element position = n / 2 = 4 / 2 = 2 (0-indexed third element).
   `std::nth_element` partially sorts the array such that index 2 holds the median.
   Array becomes partitioned: [1, 2, 9, 10] (Index 2 value = 9).
   Median = 9.

2. Calculate Absolute Differences:
   - num = 1:  abs(1 - 9)  = 8  -> moves = 8
   - num = 2:  abs(2 - 9)  = 7  -> moves = 8 + 7 = 15
   - num = 9:  abs(9 - 9)  = 0  -> moves = 15 + 0 = 15
   - num = 10: abs(10 - 9) = 1  -> moves = 15 + 1 = 16

Total Minimum Moves = 16.

--------------------------------------------------------------------------------
INTERVIEW NOTES
--------------------------------------------------------------------------------
- Pattern:
  Median Minimization Principle / Distance Minimization on a Line.

- Key Observation:
  The average (mean) minimizes squared errors (\sum (x_i - k)^2), whereas the 
  median minimizes absolute errors (\sum |x_i - k|).

- Common Mistakes:
  - Attempting to use the Mean (average) instead of the Median. The mean is highly 
    sensitive to outliers (e.g., [1, 2, 100]), leading to suboptimal moves.
  - Sorting fully using O(n log n) when O(n) quickselect is sufficient.

- When to use this approach:
  Use this mathematical reduction whenever you need to align coordinates or values 
  distributed linearly to a single common baseline with minimal total structural shifts.
================================================================================
*/

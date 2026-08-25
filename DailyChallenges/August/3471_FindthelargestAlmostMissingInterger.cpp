#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> freq(51, 0);

        for (int x : nums)
            freq[x]++;

        if (k == n)
            return *max_element(nums.begin(), nums.end());

        if (k == 1) {
            int ans = -1;

            for (int x : nums) {
                if (freq[x] == 1)
                    ans = max(ans, x);
            }

            return ans;
        }

        int ans = -1;

        if (freq[nums[0]] == 1)
            ans = max(ans, nums[0]);

        if (freq[nums[n - 1]] == 1)
            ans = max(ans, nums[n - 1]);

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {3, 9, 2, 1, 7};
    int k = 3;

    cout << sol.largestInteger(nums, k) << '\n';

    return 0;
}

/*
======================================================================
LeetCode 3471 - Find the Largest Almost Missing Integer
======================================================================

Problem Statement
-----------------
You are given an integer array nums and an integer k.

An integer x is called "almost missing" if x appears in exactly
one subarray of size k.

Return the largest almost missing integer.

If no such integer exists, return -1.


Example
-------
Input:
nums = [3, 9, 2, 1, 7]
k = 3

Output:
7


----------------------------------------------------------------------
Brute Force Approach
----------------------------------------------------------------------

Idea
----
Generate every subarray of size k.

For every subarray, store its distinct elements in a set.
Then count how many subarrays contain each value.

Finally, return the largest value whose subarray count is exactly 1.


Pseudo Code
-----------
1. Create subarrayCount.
2. For every size-k subarray:
      Create a set.
      Insert all elements of the subarray.
      For every element in the set:
          subarrayCount[element]++

3. Find the largest value whose count is 1.
4. Return the answer.


Complete Brute Force Code
--------------------------
The following code is only for revision.

    /*
    int largestIntegerBruteForce(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> subarrayCount(51, 0);

        for (int i = 0; i + k <= n; i++) {
            set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            for (int x : seen) {
                subarrayCount[x]++;
            }
        }

        int ans = -1;

        for (int x = 0; x <= 50; x++) {
            if (subarrayCount[x] == 1)
                ans = max(ans, x);
        }

        return ans;
    }
    */


// Time Complexity
// ---------------
// O(n * k)


// Space Complexity
// ----------------
// O(k)


// ----------------------------------------------------------------------
// Optimal Approach
// ----------------------------------------------------------------------

// Observation
// -----------
// There are three cases.

// CASE 1: k == n
// ----------------
// There is only one subarray: the complete array.

// Therefore, every distinct element is almost missing.

// So return the maximum element.


// CASE 2: k == 1
// ----------------
// Every element itself forms one subarray.

// Therefore, an element is almost missing if and only if its frequency
// in the entire array is exactly 1.

// So return the largest element having frequency 1.


// CASE 3: 1 < k < n
// ------------------
// The first element belongs to only one size-k subarray.

// The last element also belongs to only one size-k subarray.

// Every middle element belongs to at least two size-k subarrays.

// Therefore, only nums[0] and nums[n - 1] can be almost missing.

// A boundary value is valid only if its total frequency is exactly 1.


// Intuition
// ---------
// Instead of checking every subarray, analyze how many windows can
// contain each position.

// For 1 < k < n:

// First position  -> exactly 1 window
// Last position   -> exactly 1 window
// Middle positions -> at least 2 windows

// Hence, only the two boundary values need to be checked.


// Pseudo Code
// -----------
// 1. Count the frequency of every value.

// 2. If k == n:
//       return maximum element.

// 3. If k == 1:
//       return largest value whose frequency is 1.

// 4. Otherwise:
//       ans = -1

//       If freq[nums[0]] == 1:
//           ans = max(ans, nums[0])

//       If freq[nums[n - 1]] == 1:
//           ans = max(ans, nums[n - 1])

//       return ans.


// Complete Optimal Code
// ----------------------
// LeetCode version:

    /*
    class Solution {
    public:
        int largestInteger(vector<int>& nums, int k) {
            int n = nums.size();

            vector<int> freq(51, 0);

            for (int x : nums)
                freq[x]++;

            if (k == n)
                return *max_element(nums.begin(), nums.end());

            if (k == 1) {
                int ans = -1;

                for (int x : nums) {
                    if (freq[x] == 1)
                        ans = max(ans, x);
                }

                return ans;
            }

            int ans = -1;

            if (freq[nums[0]] == 1)
                ans = max(ans, nums[0]);

            if (freq[nums[n - 1]] == 1)
                ans = max(ans, nums[n - 1]);

            return ans;
        }
    };
    */


// Time Complexity
// ---------------
// Frequency counting takes O(n).

// Therefore:

// Time = O(n)


// Space Complexity
// ----------------
// The frequency array has 51 elements.

// Space = O(1)


// ----------------------------------------------------------------------
// Dry Run
// ----------------------------------------------------------------------

// nums = [3, 9, 2, 1, 7]
// k = 3

// Frequency:

// 3 -> 1
// 9 -> 1
// 2 -> 1
// 1 -> 1
// 7 -> 1

// Here:

// 1 < k < n

// So check only the first and last elements.

// First:
// nums[0] = 3
// freq[3] = 1

// Therefore, 3 is a candidate.

// Last:
// nums[4] = 7
// freq[7] = 1

// Therefore, 7 is a candidate.

// answer = max(3, 7)
//        = 7

// Output = 7


// ----------------------------------------------------------------------
// Interview Notes
// ----------------------------------------------------------------------

// Pattern
// -------
// Array + Frequency Counting + Boundary Observation


// Key Observation
// ---------------
// For 1 < k < n, only the first and last positions can belong to
// exactly one size-k subarray.


// Common Mistakes
// ---------------
// 1. Counting occurrences instead of counting subarrays.

// 2. Forgetting the k == 1 case.

// 3. Forgetting the k == n case.

// 4. Checking only the first or only the last element.

// 5. Forgetting to take the maximum valid value.


// When to Use This Approach
// -------------------------
// Use this approach when a fixed-size sliding-window problem has
// special boundary behavior.

// Before simulating every window, check how many windows can contain
// each position.

// ======================================================================
// */
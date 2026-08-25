#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: Sliding Window + Frequency Map
class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int ans = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            freq[nums[right]]++;

            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 1, 2, 3, 1, 2};
    int k = 2;

    cout << sol.maxSubarrayLength(nums, k) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 2958 - CP NOTEBOOK
        Length of Longest Subarray With at Most K Frequency
================================================================================

Problem Statement:
------------------
Given an integer array nums and an integer k, return the length of the
longest subarray such that every element appears at most k times in that
subarray.

Example:
--------
Input:
nums = [1,2,3,1,2,3,1,2], k = 2

Output:
6

Explanation:
The longest valid subarray can be [1,2,3,1,2,3].
Every element appears at most 2 times.

-------------------------------------------------------------------------------

Brute Force Approach:
---------------------

Idea:
-----
Try every possible subarray and maintain the frequency of each element.
If any element occurs more than k times, that subarray is invalid.

Pseudo Code:
------------
for left = 0 to n-1:
    clear frequency map

    for right = left to n-1:
        increment frequency[nums[right]]

        if frequency[nums[right]] > k:
            break

        update answer

return answer

Complete Brute Force Code:
---------------------------
/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;

        for (int left = 0; left < n; left++) {
            unordered_map<int, int> freq;

            for (int right = left; right < n; right++) {
                freq[nums[right]]++;

                if (freq[nums[right]] > k) {
                    break;
                }

                ans = max(ans, right - left + 1);
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 1, 2, 3, 1, 2};
    int k = 2;

    cout << sol.maxSubarrayLength(nums, k) << '\n';

    return 0;
}
*/

// Time Complexity:
// ----------------
// O(N^2) average.

// Space Complexity:
// -----------------
// O(N) for the frequency map.

// -------------------------------------------------------------------------------

// Optimal Approach:
// -----------------

// Observation:
// ------------
// We need the longest contiguous subarray where every element has frequency
// <= k.

// When we extend the subarray by adding nums[right], only the frequency of
// nums[right] can become invalid.

// If its frequency becomes greater than k, we can move the left pointer
// forward until the window becomes valid again.

// This gives a classic Sliding Window / Two Pointer solution.

// Intuition:
// ----------
// Maintain a window [left ... right].

// 1. Add nums[right] to the frequency map.
// 2. If nums[right] occurs more than k times, the current window is invalid.
// 3. Remove elements from the left until nums[right] occurs at most k times.
// 4. The window is now valid.
// 5. Update the maximum length.

// The left pointer never moves backwards, so every element is added and removed
// from the window at most once.

// Pseudo Code:
// ------------
// left = 0
// answer = 0
// frequency map = empty

// for right = 0 to n-1:

//     frequency[nums[right]]++

//     while frequency[nums[right]] > k:
//         frequency[nums[left]]--
//         left++

//     answer = max(answer, right - left + 1)

// return answer

// Complete Optimal Code:
// ----------------------
/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int ans = 0;

        for (int right = 0; right < (int)nums.size(); right++) {
            freq[nums[right]]++;

            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 2, 3, 1, 2, 3, 1, 2};
    int k = 2;

    cout << sol.maxSubarrayLength(nums, k) << '\n';

    return 0;
}
*/

// Time Complexity:
// ----------------
// O(N) average.

// Each element is inserted into the window once and removed from the window
// at most once.

// Space Complexity:
// -----------------
// O(N) in the worst case for the frequency map.

// -------------------------------------------------------------------------------

// Dry Run with Example:
// ---------------------

// nums = [1,2,3,1,2,3,1,2]
// k = 2

// Start:
// left = 0
// ans = 0

// right = 0
// window = [1]
// freq: 1 -> 1
// length = 1
// ans = 1

// right = 1
// window = [1,2]
// freq: 1 -> 
// ----------------

// Pattern:
// --------
// Sliding Window + Two Pointers + Frequency Map.

// Key Observation:
// ----------------
// If adding nums[right] makes its frequency greater than k, the window is
// invalid.

// Only the left side needs to 1, 2 -> 1
// length = 2
// ans = 2

// right = 2
// window = [1,2,3]
// freq: 1 -> 1, 2 -> 1, 3 -> 1
// length = 3
// ans = 3

// right = 3
// window = [1,2,3,1]
// freq: 1 -> 2, 2 -> 1, 3 -> 1
// length = 4
// ans = 4

// right = 4
// window = [1,2,3,1,2]
// freq: 1 -> 2, 2 -> 2, 3 -> 1
// length = 5
// ans = 5

// right = 5
// window = [1,2,3,1,2,3]
// freq: 1 -> 2, 2 -> 2, 3 -> 2
// length = 6
// ans = 6

// right = 6
// Add 1:
// freq[1] becomes 3 > k.

// Move left:
// Remove nums[0] = 1
// freq[1] becomes 2
// left = 1

// Now window = [2,3,1,2,3,1]
// length = 6
// ans = 6

// right = 7
// Add 2:
// freq[2] becomes 3 > k.

// Move left:
// Remove nums[1] = 2
// freq[2] becomes 2
// left = 2

// Now window = [3,1,2,3,1,2]
// length = 6
// ans = 6

// Final Answer = 6

// -------------------------------------------------------------------------------

// Interview Notes:move until that frequency becomes valid again.

// Because left and right only move forward, the total work is linear.

// Common Mistakes:
// ----------------
// 1. Forgetting to decrease the frequency when moving left.
// 2. Using if instead of while when shrinking the window.
// 3. Calculating window length incorrectly:
//        right - left + 1
// 4. Checking the entire frequency map every time.
// 5. Confusing "subarray" with "subsequence".
//    The elements must be contiguous.
// 6. Returning the frequency of an element instead of the maximum window length.

// When to use this approach:
// --------------------------
// Use Sliding Window when:

// - The problem asks for a longest/shortest contiguous subarray.
// - There is a constraint on frequencies/counts.
// - A window can become invalid when a new element is added.
// - Removing elements from the left can restore validity.

// Typical related patterns:
// - Longest substring with at most K distinct characters.
// - Longest subarray with at most K occurrences.
// - Minimum window satisfying a frequency constraint.
// - Longest substring without repeating characters.
// - Count-based contiguous window problems.

// Final Pattern:
// --------------
// Expand right -> Detect violation -> Shrink left -> Update answer.

// Time:  O(N) average
// Space: O(N)

// ================================================================================
// */

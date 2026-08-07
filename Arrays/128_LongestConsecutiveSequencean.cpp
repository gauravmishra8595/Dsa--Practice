#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> st;

        for (int num : nums)
        {
            st.insert(num);
        }

        int longest = 0;

        for (int num : st)
        {
            // Check if num is the starting element
            if (st.find(num - 1) == st.end())
            {
                int current = num;
                int count = 1;

                while (st.find(current + 1) != st.end())
                {
                    current++;
                    count++;
                }

                longest = max(longest, count);
            }
        }

        return longest;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {100, 4, 200, 1, 3, 2};

    cout << sol.longestConsecutive(nums);

    return 0;
}

/*
============================================================
                    LEETCODE 128
              Longest Consecutive Sequence
============================================================

Problem Statement:
------------------
Given an unsorted array of integers nums, return the length of
the longest consecutive elements sequence.

The algorithm must run in O(n) time.

Example:
--------
Input:
nums = [100,4,200,1,3,2]

Output:
4

Explanation:
The longest consecutive sequence is:
[1,2,3,4]

Length = 4


============================================================
Brute Force Approach
============================================================

Idea:
-----
For every element:
- Try to find the next consecutive number.
- Continue until the sequence breaks.
- Keep track of the maximum length.

Searching every next number using linear search makes it slow.


Pseudo Code:
------------
maxLength = 0

for every num in nums:

    current = num
    length = 1

    while current + 1 exists in nums:
        current++
        length++

    maxLength = max(maxLength, length)

return maxLength


Complete Brute Force Code:

*/
/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        int longest = 0;

        for (int i = 0; i < n; i++) {
            int current = nums[i];
            int count = 1;

            while (find(nums.begin(), nums.end(), current + 1)
                   != nums.end()) {
                current++;
                count++;
            }

            longest = max(longest, count);
        }

        return longest;
    }
};
*/

// Time Complexity:
// ----------------
// O(n^2)

// Space Complexity:
// -----------------
// O(1)


// ============================================================
// Optimal Approach
// ============================================================

// Observation:
// ------------
// A consecutive sequence starts only when there is no previous
// number present.

// Example:

// [1,2,3,4]

// 1 is the starting point because 0 does not exist.

// 2,3,4 are skipped because they already have previous elements.


// Intuition:
// ----------
// Store all numbers in an unordered_set for O(1) lookup.

// For every number:
// - Check if it is the beginning of a sequence.
// - If yes, count consecutive numbers.
// - Update maximum length.


// Pseudo Code:
// ------------
// Insert all elements into unordered_set

// longest = 0

// for every num in set:

//     if num-1 does not exist:

//         current = num
//         count = 1

//         while current+1 exists:
//             current++
//             count++

//         longest = max(longest, count)

// return longest


// Complete Optimal Code:

// */
/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        unordered_set<int> st;

        for (int num : nums) {
            st.insert(num);
        }

        int longest = 0;

        for (int num : st) {

            if (st.find(num - 1) == st.end()) {

                int current = num;
                int count = 1;

                while (st.find(current + 1) != st.end()) {
                    current++;
                    count++;
                }

                longest = max(longest, count);
            }
        }

        return longest;
    }
};
*/


// Time Complexity:
// ----------------
// O(n)

// Each number is visited at most twice.

// Space Complexity:
// -----------------
// O(n)

// For storing elements in unordered_set.


// ============================================================
// Dry Run With Example
// ============================================================

// Input:
// nums = [100,4,200,1,3,2]


// Step 1:
// Insert all elements:

// set = {100,4,200,1,3,2}


// Check each number:


// 100:
// 99 does not exist.

// Sequence:
// 100

// Length = 1


// 4:
// 3 exists, so skip.


// 200:
// 199 does not exist.

// Sequence:
// 200

// Length = 1


// 1:
// 0 does not exist.

// Sequence:
// 1 -> 2 -> 3 -> 4

// Length = 4


// 3:
// 2 exists, skip.


// 2:
// 1 exists, skip.


// Maximum length = 4


// Answer:
// 4


// ============================================================
// Interview Notes
// ============================================================

// Pattern:
// --------
// Hashing + Sequence Detection


// Key Observation:
// ----------------
// Only count sequences from their starting element.

// A number is a starting point if:
// (number - 1) is not present.


// Common Mistakes:
// ----------------
// 1. Sorting the array without considering O(n log n).

// 2. Counting every number as a possible start.

// 3. Forgetting duplicate elements.

// 4. Using unordered_map unnecessarily.


// When to use this approach:
// --------------------------
// Use this pattern when:
// - Finding longest consecutive ranges.
// - Need O(n) time.
// - Order of elements is irrelevant.
// - Fast existence checking is required.

// ============================================================
// */ 
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int ans = 0;

        while (left < right) {
            int width = right - left;
            int h = min(height[left], height[right]);

            ans = max(ans, width * h);

            if (height[left] < height[right])
                left++;
            else
                right--;
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << sol.maxArea(height1) << '\n'; // 49

    vector<int> height2 = {1, 1};
    cout << sol.maxArea(height2) << '\n'; // 1

    vector<int> height3 = {4, 3, 2, 1, 4};
    cout << sol.maxArea(height3) << '\n'; // 16

    return 0;
}

/*
================================================================================
                    LEETCODE 11 - CONTAINER WITH MOST WATER
================================================================================

Problem Statement:
------------------
You are given an integer array height.

There are n vertical lines where the ith line has endpoints at:

    (i, 0) and (i, height[i])

Choose two lines that, together with the x-axis, form a container.

Return the maximum amount of water the container can store.

The area between two lines is:

    Area = min(height[left], height[right]) * (right - left)


Example:
--------
Input:
    height = [1,8,6,2,5,4,8,3,7]

Output:
    49

The maximum area is obtained using:

    height[1] = 8
    height[8] = 7

Width:
    8 - 1 = 7

Height:
    min(8, 7) = 7

Area:
    7 * 7 = 49


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Try every possible pair of lines.

For every pair (i, j):

    width = j - i
    h = min(height[i], height[j])

    area = width * h

Keep the maximum area.


Pseudo Code:
------------
ans = 0

for i = 0 to n-1:
    for j = i+1 to n-1:

        width = j - i
        h = min(height[i], height[j])

        area = width * h

        ans = max(ans, area)

return ans


Complete Brute Force Code:
--------------------------
/*
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {

                int width = j - i;
                int h = min(height[i], height[j]);

                int area = width * h;

                ans = max(ans, area);
            }
        }

        return ans;
    }
};
*/

// Time Complexity:
// ----------------
// O(n^2)

// There are O(n^2) pairs of lines.


// Space Complexity:
// -----------------
// O(1)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The area is:

//     min(height[left], height[right]) * (right - left)

// Initially, take:

//     left = 0
//     right = n - 1

// This gives the maximum possible width.

// Now suppose:

//     height[left] < height[right]

// The container height is limited by height[left].

// If we move right inward:

//     width decreases

// and the limiting height is still at most height[left].

// Therefore, moving the taller line cannot improve the answer.

// We MUST move the shorter line.

// Similarly, if:

//     height[right] < height[left]

// move right to the left.

// If both heights are equal, either pointer can be moved.


// Intuition:
// ----------
// Start with the widest possible container.

// At every step:

//     area = smaller_height * width

// The shorter line is the bottleneck.

// Moving the taller line only decreases width without increasing the
// minimum height beyond the shorter line.

// Therefore:

//     Move the shorter pointer.

// This allows us to eliminate many impossible pairs without checking them.


// Pseudo Code:
// ------------
// left = 0
// right = n - 1
// ans = 0

// while left < right:

//     width = right - left
//     h = min(height[left], height[right])

//     area = width * h
//     ans = max(ans, area)

//     if height[left] < height[right]:
//         left++
//     else:
//         right--

// return ans


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int ans = 0;

        while (left < right) {
            int width = right - left;
            int h = min(height[left], height[right]);

            ans = max(ans, width * h);

            if (height[left] < height[right]) {
                left++;
            }
            else {
                right--;
            }
        }

        return ans;
    }
};
*/


// Time Complexity:
// ----------------
// O(n)

// Each pointer moves only from one end toward the other.

// Total pointer movements are at most O(n).


// Space Complexity:
// -----------------
// O(1)


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// height = [1,8,6,2,5,4,8,3,7]

// Start:

//     left = 0
//     right = 8

//     height[left] = 1
//     height[right] = 7

//     width = 8
//     h = 1

//     area = 8 * 1 = 8

// Since left height is smaller:

//     left++


// Now:

//     left = 1
//     right = 8

//     height[left] = 8
//     height[right] = 7

//     width = 7
//     h = 7

//     area = 7 * 7 = 49

//     ans = 49

// Right height is smaller:

//     right--


// Continue checking the remaining possible containers.

// None produces an area greater than 49.

// Therefore:

//     Answer = 49


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Two Pointers + Greedy


// Key Observation:
// ----------------
// The area depends on:

//     width * minimum_height

// The smaller height limits the container.

// Therefore, always move the pointer at the shorter line.


// Common Mistakes:
// ----------------
// 1. Moving the taller pointer instead of the shorter pointer.

// 2. Forgetting that the height is:

//        min(height[left], height[right])

// 3. Using:

//        max(height[left], height[right])

//    instead of min().

// 4. Forgetting that width is:

//        right - left

// 5. Using nested loops when an O(n) two-pointer solution is expected.

// 6. Updating the answer after moving the pointers instead of checking
//    the current pair first.

// 7. Assuming the tallest two lines always produce the maximum area.
//    Width also matters.


// When to Use This Approach:
// --------------------------
// Use the two-pointer technique when:

// - You are working with an array.
// - You need to consider pairs of elements.
// - The answer depends on the distance between two pointers.
// - Moving one pointer can safely eliminate a group of possibilities.
// - The array has useful ordering or monotonic properties.

// Classic examples:

//     - Container With Most Water
//     - Two Sum II
//     - 3Sum
//     - Trapping Rain Water
//     - Remove Duplicates from Sorted Array


// Core Template:
// --------------
// left = 0
// right = n - 1

// while left < right:

//     process(left, right)

//     if left-side condition:
//         left++
//     else:
//         right--


// Key Formula:
// ------------
// Area = min(height[left], height[right]) * (right - left)


// Final Complexity:
// -----------------
// Time  = O(n)
// Space = O(1)


// ================================================================================
// */

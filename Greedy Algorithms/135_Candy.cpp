#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();

        vector<int> candy(n, 1);

        // Left to right: satisfy increasing relation.
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candy[i] = candy[i - 1] + 1;
            }
        }

        // Right to left: satisfy decreasing relation.
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candy[i] = max(candy[i], candy[i + 1] + 1);
            }
        }

        return accumulate(candy.begin(), candy.end(), 0);
    }
};

int main() {
    Solution sol;

    vector<int> ratings1 = {1, 0, 2};
    cout << sol.candy(ratings1) << '\n'; // 5

    vector<int> ratings2 = {1, 2, 2};
    cout << sol.candy(ratings2) << '\n'; // 4

    vector<int> ratings3 = {1, 3, 4, 5, 2};
    cout << sol.candy(ratings3) << '\n'; // 11

    return 0;
}

/*
================================================================================
                    LEETCODE 135 - CANDY
================================================================================

Problem Statement:
------------------
There are n children standing in a line.

Each child has a rating given by the array ratings.

You must distribute candies according to these rules:

1. Every child must have at least one candy.
2. A child with a higher rating than an adjacent child must have more
   candies than that adjacent child.

Return the minimum number of candies required.


Example:
--------
Input:
    ratings = [1, 0, 2]

Output:
    5

One valid distribution is:

    ratings:  1  0  2
    candies:  2  1  2

Total:

    2 + 1 + 2 = 5


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Initially give every child one candy.

Then repeatedly scan the array and fix violations:

    If ratings[i] > ratings[i-1],
    then candies[i] must be greater than candies[i-1].

    If ratings[i] > ratings[i+1],
    then candies[i] must be greater than candies[i+1].

Keep updating until there are no violations.

This works, but repeated scans can make it O(n^2).


Pseudo Code:
------------
candies[i] = 1 for every i

repeat:
    changed = false

    for i = 0 to n-1:

        if i > 0 AND ratings[i] > ratings[i-1]:
            if candies[i] <= candies[i-1]:
                candies[i] = candies[i-1] + 1
                changed = true

        if i+1 < n AND ratings[i] > ratings[i+1]:
            if candies[i] <= candies[i+1]:
                candies[i] = candies[i+1] + 1
                changed = true

until changed == false

return sum(candies)


Complete Brute Force Code:
--------------------------
/*
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();

        vector<int> candies(n, 1);

        bool changed = true;

        while (changed) {
            changed = false;

            for (int i = 0; i < n; ++i) {

                if (i > 0 && ratings[i] > ratings[i - 1]) {
                    if (candies[i] <= candies[i - 1]) {
                        candies[i] = candies[i - 1] + 1;
                        changed = true;
                    }
                }

                if (i + 1 < n && ratings[i] > ratings[i + 1]) {
                    if (candies[i] <= candies[i + 1]) {
                        candies[i] = candies[i + 1] + 1;
                        changed = true;
                    }
                }
            }
        }

        return accumulate(candies.begin(), candies.end(), 0);
    }
};
*/

// Time Complexity:
// ----------------
// O(n^2) in the worst case.

// Multiple passes may be required to propagate candy counts.


// Space Complexity:
// -----------------
// O(n)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// Every child initially gets one candy.

// There are two independent conditions:

// 1. Increasing ratings from left to right.
// 2. Increasing ratings from right to left.

// For example:

//     ratings = [1, 2, 3]

// Left-to-right requirement:

//     candies = [1, 2, 3]


// For:

//     ratings = [3, 2, 1]

// Right-to-left requirement:

//     candies = [3, 2, 1]


// But an array can contain both patterns:

//     ratings = [1, 3, 4, 2]

// We need to satisfy BOTH sides.


// Intuition:
// ----------
// Use two passes.

// PASS 1: Left -> Right
// ---------------------
// If:

//     ratings[i] > ratings[i-1]

// then:

//     candies[i] = candies[i-1] + 1

// This handles the left-neighbor condition.


// PASS 2: Right -> Left
// ---------------------
// If:

//     ratings[i] > ratings[i+1]

// then:

//     candies[i] = max(candies[i], candies[i+1] + 1)

// We use max() because the first pass may already have assigned more
// candies to this child.

// This handles both neighboring conditions without destroying the
// previously satisfied condition.


// Pseudo Code:
// ------------
// create candies array filled with 1

// for i = 1 to n-1:
//     if ratings[i] > ratings[i-1]:
//         candies[i] = candies[i-1] + 1

// for i = n-2 down to 0:
//     if ratings[i] > ratings[i+1]:
//         candies[i] = max(candies[i], candies[i+1] + 1)

// return sum(candies)


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();

        vector<int> candy(n, 1);

        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candy[i] = candy[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candy[i] = max(candy[i], candy[i + 1] + 1);
            }
        }

        return accumulate(candy.begin(), candy.end(), 0);
    }
};
*/


// Time Complexity:
// ----------------
// O(n)

// First pass  = O(n)
// Second pass = O(n)
// Summation   = O(n)

// Total = O(n)


// Space Complexity:
// -----------------
// O(n)

// The candy array requires O(n) extra space.


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// ratings = [1, 0, 2]


// Initially:

//     candy = [1, 1, 1]


// PASS 1: LEFT -> RIGHT
// ---------------------

// i = 1:

//     ratings[1] = 0
//     ratings[0] = 1

//     0 > 1 -> false

//     candy = [1, 1, 1]


// i = 2:

//     ratings[2] = 2
//     ratings[1] = 0

//     2 > 0 -> true

//     candy[2] = candy[1] + 1
//              = 2

//     candy = [1, 1, 2]


// PASS 2: RIGHT -> LEFT
// ---------------------

// i = 1:

//     ratings[1] = 0
//     ratings[2] = 2

//     0 > 2 -> false

//     candy = [1, 1, 2]


// i = 0:

//     ratings[0] = 1
//     ratings[1] = 0

//     1 > 0 -> true

//     candy[0] = max(candy[0], candy[1] + 1)

//              = max(1, 2)
//              = 2

//     candy = [2, 1, 2]


// Total:

//     2 + 1 + 2 = 5

// Answer = 5


// ================================================================================
// IMPORTANT DRY RUN: [1, 2, 3, 2, 1]
// ================================================================================

// Initially:

//     candy = [1, 1, 1, 1, 1]


// Left -> Right:

//     ratings:  1  2  3  2  1
//     candy:    1  2  3  1  1


// Right -> Left:

// At index 3:

//     2 > 1

//     candy[3] = max(1, 1 + 1)
//              = 2


// At index 2:

//     3 > 2

//     candy[2] = max(3, 2 + 1)
//              = 3


// At index 1:

//     2 > 3 -> false


// At index 0:

//     1 > 2 -> false


// Final:

//     candy = [1, 2, 3, 2, 1]

// Total = 9


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Greedy + Two Passes


// Key Observation:
// ----------------
// The condition depends on BOTH neighbors.

// Therefore:

//     Left -> Right
//         handles left neighbor.

//     Right -> Left
//         handles right neighbor.

// Use max() in the second pass so that the first pass's valid assignment
// is not lost.


// Common Mistakes:
// ----------------
// 1. Doing only a left-to-right pass.

// 2. Doing only a right-to-left pass.

// 3. In the second pass, writing:

//        candy[i] = candy[i+1] + 1

//    instead of:

//        candy[i] = max(candy[i], candy[i+1] + 1)

// 4. Giving zero candies to some child.

// 5. Confusing ratings with candy counts.

// 6. Forgetting that equal ratings have NO requirement.

//    Example:

//        ratings = [1, 2, 2]

//    The last child does not need more candy than the middle child.


// When to Use This Approach:
// --------------------------
// Use this technique when:

// - Each element has constraints involving both neighbors.
// - A single left-to-right greedy pass handles one direction.
// - A reverse pass can handle the opposite direction.
// - You need the minimum assignment satisfying local inequalities.

// This is a classic:

//     Two-Pass Greedy

// pattern.


// Mental Template:
// ----------------
// Start with the minimum:

//     everyone = 1

// Then:

//     Left -> Right
//         satisfy increasing-from-left condition.

//     Right -> Left
//         satisfy increasing-from-right condition.

// Finally:

//     sum all values.


// Final Complexity:
// -----------------
// Time  = O(n)
// Space = O(n)


// ================================================================================
// */

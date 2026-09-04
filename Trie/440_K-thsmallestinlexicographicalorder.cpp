#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findKthNumber(int n, int k)
    {
        long long curr = 1;
        k--;

        while (k > 0)
        {
            long long steps = countSteps(n, curr, curr + 1);

            if (steps <= k)
            {
                // Skip the entire subtree of curr
                curr++;
                k -= steps;
            }
            else
            {
                // Go deeper into curr's subtree
                curr *= 10;
                k--;
            }
        }

        return (int)curr;
    }

private:
    long long countSteps(long long n, long long prefix, long long nextPrefix)
    {
        long long steps = 0;

        while (prefix <= n)
        {
            steps += min(n + 1, nextPrefix) - prefix;

            prefix *= 10;
            nextPrefix *= 10;
        }

        return steps;
    }
};

int main()
{
    Solution sol;

    int n = 13;
    int k = 2;

    cout << sol.findKthNumber(n, k) << '\n';

    return 0;
}

/*
================================================================================
              LEETCODE 440 - K-TH SMALLEST IN LEXICOGRAPHICAL ORDER
================================================================================

Problem Statement:
------------------
Given two integers n and k, return the k-th smallest integer in the range
[1, n] according to lexicographical order.

Lexicographical order means dictionary/string order.

Example:
--------
Input:
n = 13, k = 2

Numbers:
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13

Lexicographical order:
1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9

2nd smallest = 10

Output:
10


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Generate all numbers from 1 to n.

Convert them into strings and sort them lexicographically.

Then return the (k - 1)-th element.

For example:

[1,2,3,10,11]

After lexicographical sorting:

["1","10","11","2","3"]

So the k-th element can be directly returned.

Pseudo Code:
-----------
create vector nums

for i = 1 to n:
    add i to nums

sort nums using lexicographical/string comparison

return nums[k - 1]


Complete Brute Force Code:
--------------------------
(The following code is for revision only and is NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthNumber(int n, int k) {
        vector<string> nums;

        for (int i = 1; i <= n; i++)
            nums.push_back(to_string(i));

        sort(nums.begin(), nums.end());

        return stoi(nums[k - 1]);
    }
};
*/

// Time Complexity:
// ----------------
// There are n numbers.

// Converting numbers to strings takes O(log n).

// Sorting takes:

// O(n log n)

// with string comparison costing up to O(log n).

// Therefore approximately:

// O(n log n log n)

// Space Complexity:
// -----------------
// O(n log n)

// because we store all numbers as strings.


// ================================================================================
// OPTIMAL APPROACH - PREFIX TREE / LEXICOGRAPHICAL TRAVERSAL
// ================================================================================

// Observation:
// ------------
// Lexicographical ordering of numbers is equivalent to traversing a Prefix Tree.

// For n = 13:

//                     root
//               / / / / ... \
//              1  2  3 ...   9
//            / | \
//           10 11 12
//               ...
              
// The lexicographical order is:

// 1
// 10
// 11
// 12
// 13
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9


// Intuition:
// ----------
// Instead of generating every number, we treat every number as a prefix.

// For example:

// Prefix = 1

// Its subtree contains:

// 1
// 10
// 100
// 101
// ...
// 11
// 12
// 13
// ...

// We need to know how many numbers exist under a prefix.

// If the subtree contains fewer than k remaining numbers, we can skip the
// entire subtree.

// Otherwise, we go deeper into that subtree.

// This lets us jump over large groups of numbers instead of visiting them
// one by one.


// IMPORTANT IDEA:
// ---------------

// Suppose:

// curr = 1

// Then the range of prefixes represented by this subtree is:

// [1, 2)

// At the next level:

// [10, 20)

// Then:

// [100, 200)

// We count how many numbers <= n fall into these ranges.

// The function:

// countSteps(n, curr, curr + 1)

// calculates the number of valid integers under the prefix curr.


// How countSteps works:
// ---------------------

// For n = 13 and prefix = 1:

// Level 1:

// [1, 2)

// Numbers:
// 1

// count = 1


// Level 2:

// [10, 20)

// Numbers:
// 10, 11, 12, 13

// count = 4

// Total:

// 1 + 4 = 5


// So there are 5 numbers in the subtree rooted at prefix 1:

// 1, 10, 11, 12, 13


// If k is larger than this count, we skip the entire subtree.

// Otherwise, we go deeper.


// Pseudo Code:
// -----------
// curr = 1
// k = k - 1

// while k > 0:

//     steps = number of integers in subtree(curr)

//     if steps <= k:
//         skip this entire subtree
//         curr++
//         k -= steps

//     else:
//         move deeper into curr
//         curr *= 10
//         k--

// return curr


// Why k-- when going deeper?
// --------------------------
// The current prefix itself is one number in the lexicographical traversal.

// For example:

// 1
// 10
// 11
// 12
// ...

// If we move from 1 to 10, we have already consumed 1.

// Therefore:

// k--


// Complete Optimal Code:
// ----------------------
// (The following code is for revision only and is NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    long long countSteps(long long n,
                         long long prefix,
                         long long nextPrefix) {

        long long steps = 0;

        while (prefix <= n) {
            steps += min(n + 1, nextPrefix) - prefix;

            prefix *= 10;
            nextPrefix *= 10;
        }

        return steps;
    }

public:
    int findKthNumber(int n, int k) {
        long long curr = 1;

        k--;

        while (k > 0) {
            long long steps =
                countSteps(n, curr, curr + 1);

            if (steps <= k) {
                curr++;
                k -= steps;
            }
            else {
                curr *= 10;
                k--;
            }
        }

        return (int)curr;
    }
};
*/


// Time Complexity:
// ----------------
// At every step, we either:

// 1. Move to the next sibling prefix, or
// 2. Move one level deeper.

// The counting operation takes O(log n).

// Overall complexity:

// O(log^2 n)

// In practice this is extremely fast for the constraints of LeetCode 440.

// Space Complexity:
// -----------------
// O(1)

// Only a few variables are used.


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// Input:

// n = 13
// k = 2


// Lexicographical order:

// 1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9


// We start:

// curr = 1
// k = 2

// Convert k to zero-based:

// k = k - 1
// k = 1


// Step 1:
// -------

// curr = 1

// Count numbers under prefix 1:

// 1
// 10
// 11
// 12
// 13

// steps = 5


// Since:

// steps > k

// we cannot skip the subtree.

// Go deeper:

// curr = 1 * 10
// curr = 10

// Consume the current prefix:

// k = 1 - 1
// k = 0


// Now k == 0.

// Return:

// 10


// Answer:

// 10


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Prefix Tree / Trie-like Lexicographical Traversal

// This problem does NOT require explicitly building a Trie.

// Instead, we mathematically traverse the implicit prefix tree.


// Key Observation:
// ----------------
// Lexicographical numbers form a prefix tree.

// For example:

// 1
// |
// +-- 10
// +-- 11
// +-- 12
// +-- 13
// |
// 2
// |
// +-- 20
// +-- 21
// ...


// The important trick is:

// COUNT HOW MANY NUMBERS ARE UNDER A PREFIX.

// Once we know that count, we can skip the entire subtree.


// Core Formula:
// -------------

// steps += min(n + 1, nextPrefix) - prefix;


// This calculates how many numbers fall inside:

// [prefix, nextPrefix)


// at the current digit level.


// Common Mistakes:
// ----------------
// 1. Confusing numerical order with lexicographical order.

//    Numerical:
//    1, 2, 3, 10, 11

//    Lexicographical:
//    1, 10, 11, 2, 3


// 2. Forgetting:

//    k--;

//    initially, because curr = 1 is already the first number.


// 3. Forgetting another k-- when moving deeper:

//    curr *= 10;
//    k--;


// 4. Using int for prefix calculations.

//    Use long long because:

//    prefix *= 10

//    can overflow int during counting.


// 5. Incorrectly calculating the number of elements in a prefix subtree.

// 6. Building an actual Trie.

//    This is unnecessary because n can be very large.


// When to Use This Approach:
// --------------------------
// Use this technique when:

// - Numbers are ordered lexicographically.
// - You need the k-th number in lexicographical order.
// - n is too large to generate all numbers.
// - Numbers can be represented as prefixes.
// - You can count how many valid numbers belong to a prefix.


// RELATED PATTERN:
// ----------------
// This is similar to:

// Trie traversal
// +
// Prefix counting
// +
// Greedy skipping


// Instead of physically creating:

// root -> 1 -> 10 -> 100 ...

// we calculate the size of each prefix subtree mathematically.


// ================================================================================
// FINAL COMPLEXITY
// ================================================================================

// Brute Force:
// Time  : O(n log n log n) approximately
// Space : O(n log n)

// Optimal:
// Time  : O(log^2 n)
// Space : O(1)


// ================================================================================
// ONE-LINE MEMORY TRICK
// ================================================================================

// "Count the subtree of the current prefix; skip it if k is larger,
// otherwise go deeper."


// ================================================================================
// */

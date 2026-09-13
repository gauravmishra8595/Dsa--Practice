#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countOverlap(vector<vector<int>>& img1,
                     vector<vector<int>>& img2,
                     int rowOffset,
                     int colOffset) {
        int n = img1.size();
        int overlap = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int ni = i + rowOffset;
                int nj = j + colOffset;

                if (ni < 0 || ni >= n || nj < 0 || nj >= n)
                    continue;

                if (img1[i][j] == 1 && img2[ni][nj] == 1)
                    overlap++;
            }
        }

        return overlap;
    }

    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        int n = img1.size();
        int ans = 0;

        for (int rowOffset = -n + 1; rowOffset < n; rowOffset++) {
            for (int colOffset = -n + 1; colOffset < n; colOffset++) {
                ans = max(ans,
                          countOverlap(img1, img2, rowOffset, colOffset));
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> img1 = {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    };

    vector<vector<int>> img2 = {
        {0, 0, 0},
        {0, 1, 1},
        {0, 0, 1}
    };

    cout << sol.largestOverlap(img1, img2) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 835 - IMAGE OVERLAP
================================================================================

PROBLEM STATEMENT
-----------------
You are given two binary square matrices img1 and img2 of size n x n.

You can translate (shift) img1 horizontally and/or vertically.

After shifting img1, the overlap is the number of positions where both
img1 and img2 contain 1.

Return the maximum possible overlap.

Only translations are allowed. No rotation or flipping.

Example:
--------
img1 =
1 1 0
0 1 0
0 1 0

img2 =
0 0 0
0 1 1
0 0 1

Maximum overlap = 3

Explanation:
By shifting img1 appropriately, three cells containing 1 can overlap
with three cells containing 1 in img2.


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Try every possible translation of img1.

For every translation:
1. Shift img1.
2. Compare every cell with img2.
3. Count positions where both are 1.
4. Keep the maximum count.

This is essentially the direct simulation approach.

PSEUDO CODE
-----------
function largestOverlap(img1, img2):
    ans = 0

    for rowOffset from -(n-1) to (n-1):
        for colOffset from -(n-1) to (n-1):

            count = 0

            for i from 0 to n-1:
                for j from 0 to n-1:

                    ni = i + rowOffset
                    nj = j + colOffset

                    if ni and nj are inside matrix:
                        if img1[i][j] == 1 AND img2[ni][nj] == 1:
                            count++

            ans = max(ans, count)

    return ans


COMPLETE BRUTE FORCE CODE
-------------------------
(The actual executable code above uses the optimal implementation.
This version is kept only for revision.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        int n = img1.size();
        int ans = 0;

        for (int rowOffset = -n + 1; rowOffset < n; rowOffset++) {
            for (int colOffset = -n + 1; colOffset < n; colOffset++) {

                int count = 0;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {

                        int ni = i + rowOffset;
                        int nj = j + colOffset;

                        if (ni < 0 || ni >= n ||
                            nj < 0 || nj >= n) {
                            continue;
                        }

                        if (img1[i][j] == 1 &&
                            img2[ni][nj] == 1) {
                            count++;
                        }
                    }
                }

                ans = max(ans, count);
            }
        }

        return ans;
    }
};
*/


// TIME COMPLEXITY
// ----------------
// There are:

// (2n - 1) * (2n - 1) = O(n^2)

// possible translations.

// For each translation, we check n^2 cells.

// Total:

// O(n^2) * O(n^2) = O(n^4)


// SPACE COMPLEXITY
// ----------------
// O(1) extra space.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// OBSERVATION
// -----------
// We do not actually need to create a shifted matrix.

// For a particular translation:

//     rowOffset
//     colOffset

// a cell img1[i][j] corresponds to:

//     img2[i + rowOffset][j + colOffset]

// So we can directly check the corresponding position in img2.

// This avoids creating any extra matrix.


// INTUITION
// ---------
// The important part is to enumerate every possible relative position of the
// two matrices.

// For two n x n matrices:

//     rowOffset ranges from -(n-1) to +(n-1)
//     colOffset ranges from -(n-1) to +(n-1)

// For each pair of offsets, count how many 1s overlap.

// The maximum over all translations is the answer.


// PSEUDO CODE
// -----------
// function countOverlap(img1, img2, rowOffset, colOffset):

//     count = 0

//     for i from 0 to n-1:
//         for j from 0 to n-1:

//             ni = i + rowOffset
//             nj = j + colOffset

//             if ni or nj is outside img2:
//                 continue

//             if img1[i][j] == 1 AND img2[ni][nj] == 1:
//                 count++

//     return count


// function largestOverlap(img1, img2):

//     ans = 0

//     for rowOffset from -(n-1) to +(n-1):
//         for colOffset from -(n-1) to +(n-1):

//             ans = max(ans,
//                       countOverlap(img1, img2,
//                                    rowOffset, colOffset))

//     return ans


// COMPLETE OPTIMAL CODE
// ---------------------
// (The same optimal code is implemented above main().)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countOverlap(vector<vector<int>>& img1,
                     vector<vector<int>>& img2,
                     int rowOffset,
                     int colOffset) {
        int n = img1.size();
        int overlap = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                int ni = i + rowOffset;
                int nj = j + colOffset;

                if (ni < 0 || ni >= n ||
                    nj < 0 || nj >= n) {
                    continue;
                }

                if (img1[i][j] == 1 &&
                    img2[ni][nj] == 1) {
                    overlap++;
                }
            }
        }

        return overlap;
    }

    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        int n = img1.size();
        int ans = 0;

        for (int rowOffset = -n + 1;
             rowOffset < n;
             rowOffset++) {

            for (int colOffset = -n + 1;
                 colOffset < n;
                 colOffset++) {

                ans = max(ans,
                          countOverlap(img1, img2,
                                       rowOffset, colOffset));
            }
        }

        return ans;
    }
};
*/


// TIME COMPLEXITY
// ----------------
// Number of translations:

//     (2n - 1)^2 = O(n^2)

// Cells checked for each translation:

//     n^2

// Therefore:

//     O(n^4)


// SPACE COMPLEXITY
// ----------------
// Only a few variables are used.

//     O(1) extra space

// No shifted matrix is created.


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// img1:

//     1 1 0
//     0 1 0
//     0 1 0

// img2:

//     0 0 0
//     0 1 1
//     0 0 1


// Consider:

//     rowOffset = 1
//     colOffset = 0

// Mapping becomes:

// img1[i][j] -> img2[i + 1][j]

// Check the 1s of img1:

// 1. img1[0][0] = 1
//    Corresponds to img2[1][0] = 0
//    No overlap.

// 2. img1[0][1] = 1
//    Corresponds to img2[1][1] = 1
//    Overlap = 1

// 3. img1[1][1] = 1
//    Corresponds to img2[2][1] = 0
//    No overlap.

// 4. img1[2][1] = 1
//    Corresponds to img2[3][1]
//    Outside matrix -> ignore.

// So this shift gives overlap = 1.

// The algorithm tries all possible rowOffset and colOffset values.

// For the best translation, 3 cells containing 1 overlap.

// Therefore:

//     answer = 3


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// PATTERN
// -------
// Matrix Translation / Grid Simulation / Coordinate Mapping


// KEY OBSERVATION
// ---------------
// Do not physically shift or create another matrix.

// For every translation, directly map:

//     img1[i][j]

// to:

//     img2[i + rowOffset][j + colOffset]


// COMMON MISTAKES
// ---------------
// 1. Forgetting negative offsets.

//    The image can move both left/right and up/down.

// 2. Using only offsets from 0 to n-1.

//    Correct range is:

//        -(n-1) to +(n-1)


// 3. Forgetting boundary checks.

//    i + rowOffset or j + colOffset may go outside img2.


// 4. Missing the closing brace after continue.

//    Correct structure:

//        if (outside) {
//            continue;
//        }

//        if (img1[i][j] == 1 && img2[ni][nj] == 1) {
//            count++;
//        }


// 5. Creating a shifted matrix unnecessarily.

//    Direct coordinate mapping is simpler and uses O(1) extra space.


// WHEN TO USE THIS APPROACH
// --------------------------
// Use this approach when:

// - Two grids/matrices need to be compared under translations.
// - All possible relative positions need to be tested.
// - The matrix size is small enough for O(n^4).
// - You want to avoid constructing temporary shifted matrices.
// - The problem involves coordinate transformations such as:

//       newRow = row + offset
//       newCol = col + offset


// CORE FORMULA
// ------------
// For a translation:

//     (rowOffset, colOffset)

// the corresponding cell is:

//     img1[i][j] -> img2[i + rowOffset][j + colOffset]

// This coordinate-mapping idea is the key to the problem.


// ================================================================================
// */

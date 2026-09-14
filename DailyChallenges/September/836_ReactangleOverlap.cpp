#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return rec1[0] < rec2[2] &&
               rec1[2] > rec2[0] &&
               rec1[1] < rec2[3] &&
               rec1[3] > rec2[1];
    }
};
int main() {
    Solution sol;

    vector<int> rec1 = {0, 0, 2, 2};
    vector<int> rec2 = {1, 1, 3, 3};

    cout << boolalpha << sol.isRectangleOverlap(rec1, rec2) << '\n';

    return 0;
}

/*
============================================================
        LEETCODE 836 - RECTANGLE OVERLAP
============================================================

Problem Statement:
------------------
Given two axis-aligned rectangles rec1 and rec2, return true
if the two rectangles overlap.

Each rectangle is represented as:
[x1, y1, x2, y2]

where:
x1 = left coordinate
y1 = bottom coordinate
x2 = right coordinate
y2 = top coordinate

Rectangles touching only at the boundary do NOT count as
overlapping.


Example:
--------
rec1 = [0, 0, 2, 2]
rec2 = [1, 1, 3, 3]

Output:
true

The rectangles overlap in the region:
[1, 1] to [2, 2]


============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
Check whether there exists any common point inside both
rectangles.

A simple brute-force idea is to iterate through possible
integer points and check whether a point belongs to both
rectangles.

However, this is inefficient and coordinates can be very large.
Therefore, this approach is NOT suitable for the actual
constraint-based solution.


Pseudo Code:
------------
1. Find the common range of x coordinates.
2. Find the common range of y coordinates.
3. Check every possible point in the common region.
4. If any point exists, return true.
5. Otherwise return false.


Complete Brute Force Code:
--------------------------

// NOTE: Revision only - NOT executable.

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {

        for (int x = max(rec1[0], rec2[0]);
             x < min(rec1[2], rec2[2]); x++) {

            for (int y = max(rec1[1], rec2[1]);
                 y < min(rec1[3], rec2[3]); y++) {

                return true;
            }
        }

        return false;
    }
};


Time Complexity:
----------------
O(W * H), where W and H represent the ranges of coordinates.

Space Complexity:
-----------------
O(1)


============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
Two rectangles overlap only when they overlap on BOTH axes:

1. X-axis
2. Y-axis

For X-axis overlap:

rec1[0] < rec2[2]
AND
rec1[2] > rec2[0]

For Y-axis overlap:

rec1[1] < rec2[3]
AND
rec1[3] > rec2[1]

All four conditions must be true.


Intuition:
----------
Rectangle coordinates are:

rec = [left, bottom, right, top]

For two rectangles to have positive overlapping area:

        rec1.left  < rec2.right
AND     rec1.right > rec2.left

AND

        rec1.bottom < rec2.top
AND     rec1.top    > rec2.bottom

Strict inequalities (< and >) are important because if
rectangles only touch at an edge or corner, they do NOT
overlap.


Pseudo Code:
------------
1. Check X-axis overlap:
       rec1[0] < rec2[2]
       AND
       rec1[2] > rec2[0]

2. Check Y-axis overlap:
       rec1[1] < rec2[3]
       AND
       rec1[3] > rec2[1]

3. Return true only if both conditions are satisfied.


Complete Optimal Code:
----------------------

// NOTE: Revision only - already implemented above main().

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return rec1[0] < rec2[2] &&
               rec1[2] > rec2[0] &&
               rec1[1] < rec2[3] &&
               rec1[3] > rec2[1];
    }
};


Time Complexity:
----------------
O(1)

Space Complexity:
-----------------
O(1)


============================================================
DRY RUN
============================================================

rec1 = [0, 0, 2, 2]
rec2 = [1, 1, 3, 3]

Coordinates:

rec1:
left   = 0
bottom = 0
right  = 2
top    = 2

rec2:
left   = 1
bottom = 1
right  = 3
top    = 3


Step 1: Check X-axis

rec1[0] < rec2[2]
0 < 3
TRUE

rec1[2] > rec2[0]
2 > 1
TRUE

Therefore, X-axis overlaps.


Step 2: Check Y-axis

rec1[1] < rec2[3]
0 < 3
TRUE

rec1[3] > rec2[1]
2 > 1
TRUE

Therefore, Y-axis overlaps.


Both axes overlap.

Answer = TRUE


============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Geometry / Coordinate Intervals / Overlap Detection


Key Observation:
----------------
Two rectangles overlap if and only if their projections
overlap on BOTH the X-axis and Y-axis.

Think:

        X overlap + Y overlap
                 |
                 v
          Rectangle overlap


Common Mistakes:
----------------
1. Comparing x coordinates with y coordinates.

   WRONG:
   rec1[0] < rec2[1]

2. Using <= instead of <.

   Rectangles touching only at the boundary are NOT
   considered overlapping.

3. Checking only one axis.

   Both X and Y axes must overlap.

4. Forgetting the coordinate meaning:

   [x1, y1, x2, y2]
    |   |   |   |
    |   |   |   +-- top
    |   |   +------ right
    |   +---------- bottom
    +-------------- left


When to Use This Approach:
--------------------------
Use this interval-overlap technique whenever a problem asks
whether:

- Two rectangles overlap
- Two intervals intersect
- Two ranges have a common positive-length region
- Axis-aligned geometric objects intersect

General rule:

For intervals [L1, R1] and [L2, R2], positive overlap exists if:

    L1 < R2 && R1 > L2

For rectangles, apply the same rule independently to:

    X-axis
    Y-axis

============================================================
*/
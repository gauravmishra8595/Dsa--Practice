#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2,
                    int bx1, int by1, int bx2, int by2)
    {

        long long areaA = 1LL * (ax2 - ax1) * (ay2 - ay1);
        long long areaB = 1LL * (bx2 - bx1) * (by2 - by1);

        int overlapWidth = max(0, min(ax2, bx2) - max(ax1, bx1));
        int overlapHeight = max(0, min(ay2, by2) - max(ay1, by1));

        long long overlapArea = 1LL * overlapWidth * overlapHeight;

        return (int)(areaA + areaB - overlapArea);
    }
};

int main()
{
    Solution obj;

    // Example Test
    cout << obj.computeArea(-3, 0, 3, 4, 0, -1, 9, 2) << endl; // 45

    return 0;
}

/*

===========================
LeetCode 223. Rectangle Area
===========================

Problem Statement:
Given the coordinates of two axis-aligned rectangles in a 2D plane,
return the total area covered by the two rectangles.

The first rectangle is represented by:
(ax1, ay1) -> bottom-left
(ax2, ay2) -> top-right

The second rectangle is represented by:
(bx1, by1) -> bottom-left
(bx2, by2) -> top-right

If they overlap, count the overlapping region only once.

--------------------------------------------------
Example
--------------------------------------------------

Input:
Rectangle A:
(-3,0) (3,4)

Rectangle B:
(0,-1) (9,2)

Output:
45

Explanation:
Area(A)=24
Area(B)=27
Overlap=6

Total = 24 + 27 - 6 = 45

==================================================
Brute Force Approach
==================================================

Idea:
Imagine every unit square in the coordinate plane.

For each unit square:
    Check whether it lies inside rectangle A.
    Check whether it lies inside rectangle B.

Count every covered unit square once.

Works only for very small coordinates.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

Find minimum x,y and maximum x,y.

answer = 0

for every x
    for every y
        if inside rectangle A OR inside rectangle B
            answer++

return answer

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int computeArea(int ax1,int ay1,int ax2,int ay2,
                    int bx1,int by1,int bx2,int by2){

        int minX=min(ax1,bx1);
        int maxX=max(ax2,bx2);

        int minY=min(ay1,by1);
        int maxY=max(ay2,by2);

        int area=0;

        for(int x=minX;x<maxX;x++){
            for(int y=minY;y<maxY;y++){

                bool first=
                    x>=ax1 && x<ax2 &&
                    y>=ay1 && y<ay2;

                bool second=
                    x>=bx1 && x<bx2 &&
                    y>=by1 && y<by2;

                if(first||second)
                    area++;
            }
        }

        return area;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(RangeX × RangeY)

Very large if coordinates are large.

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Optimal Approach
==================================================

Observation:

Total Covered Area

=
Area(Rectangle A)
+
Area(Rectangle B)
-
Overlap Area

The only difficult part is computing overlap.

Overlap Width

=
min(right boundaries)
-
max(left boundaries)

Overlap Height

=
min(top boundaries)
-
max(bottom boundaries)

If either becomes negative,
there is no overlap.

--------------------------------------------------
Intuition
--------------------------------------------------

1. Compute area of rectangle A.

2. Compute area of rectangle B.

3. Find intersecting rectangle.

4. If rectangles don't intersect,
   overlap area = 0.

5. Return

AreaA + AreaB - Overlap.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

areaA = widthA * heightA

areaB = widthB * heightB

overlapWidth =
max(0,
min(ax2,bx2)-max(ax1,bx1))

overlapHeight =
max(0,
min(ay2,by2)-max(ay1,by1))

overlap =
overlapWidth * overlapHeight

return areaA + areaB - overlap

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2,
                    int bx1, int by1, int bx2, int by2) {

        long long areaA = 1LL * (ax2 - ax1) * (ay2 - ay1);
        long long areaB = 1LL * (bx2 - bx1) * (by2 - by1);

        int overlapWidth = max(0, min(ax2, bx2) - max(ax1, bx1));
        int overlapHeight = max(0, min(ay2, by2) - max(ay1, by1));

        long long overlapArea = 1LL * overlapWidth * overlapHeight;

        return areaA + areaB - overlapArea;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(1)

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Dry Run
==================================================

Input

A:
(-3,0) -> (3,4)

B:
(0,-1) -> (9,2)

Area A

= (3-(-3))*(4-0)

= 6*4

=24

Area B

=(9-0)*(2-(-1))

=9*3

=27

Overlap Width

=min(3,9)-max(-3,0)

=3-0

=3

Overlap Height

=min(4,2)-max(0,-1)

=2-0

=2

Overlap Area

=3*2

=6

Answer

24+27-6

=45

==================================================
Interview Notes
==================================================

Pattern:
- Geometry
- Rectangle Intersection
- Mathematical Formula

Key Observation:
Total Area
=
Area1 + Area2 − Overlap

Common Mistakes:
- Forgetting max(0, overlapWidth).
- Forgetting max(0, overlapHeight).
- Double counting overlap.
- Integer overflow (use long long internally).

When to use this approach:
- Union area of two rectangles.
- Rectangle intersection problems.
- Axis-aligned geometry calculations.
- Constant-time geometry questions.

*/
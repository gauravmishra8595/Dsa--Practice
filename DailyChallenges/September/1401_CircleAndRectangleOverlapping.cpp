#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        // Closest x-coordinate on/in the rectangle to circle center
        int xi = max(x1, min(xCenter, x2));

        // Closest y-coordinate on/in the rectangle to circle center
        int yi = max(y1, min(yCenter, y2));

        // Compare squared distances to avoid sqrt()
        int dx = xi - xCenter;
        int dy = yi - yCenter;

        return dx * dx + dy * dy <= radius * radius;
    }
};

int main() {

    Solution sol;
    cout << boolalpha
         << sol.checkOverlap(1, 0, 0, -1, -1, 1, 1)
         << '\n';

    return 0;
}


/*
================================================================================
                    LEETCODE 1401 - CIRCLE AND RECTANGLE
                              OVERLAPPING
================================================================================

PROBLEM STATEMENT
-----------------
Given a circle and an axis-aligned rectangle, determine whether the circle
and rectangle overlap.

Circle:
    center = (xCenter, yCenter)
    radius = radius

Rectangle:
    bottom-left     = (x1, y1)
    top-right       = (x2, y2)

Return true if the circle and rectangle overlap, otherwise return false.

--------------------------------------------------------------------------------
EXAMPLE
--------------------------------------------------------------------------------

Input:
    radius = 1
    xCenter = 0
    yCenter = 0
    x1 = -1
    y1 = -1
    x2 = 1
    y2 = 1

Output:
    true

Explanation:
    The circle overlaps the rectangle.

================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
One possible way is to think about all points/locations of the rectangle and
check whether any point lies inside the circle.

For an integer-coordinate version, we can iterate through all integer points
inside the rectangle and check:

    (x - xCenter)^2 + (y - yCenter)^2 <= radius^2

If such a point exists, the circle and rectangle overlap.

However, this is not the intended approach because the rectangle can be large
and iterating through all its points is inefficient.

--------------------------------------------------------------------------------
PSEUDO CODE
--------------------------------------------------------------------------------

for x from x1 to x2:
    for y from y1 to y2:

        dx = x - xCenter
        dy = y - yCenter

        if dx*dx + dy*dy <= radius*radius:
            return true

return false

--------------------------------------------------------------------------------
COMPLETE BRUTE FORCE CODE
--------------------------------------------------------------------------------

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {

                int dx = x - xCenter;
                int dy = y - yCenter;

                if (dx * dx + dy * dy <= radius * radius) {
                    return true;
                }
            }
        }

        return false;
    }
};

--------------------------------------------------------------------------------
TIME COMPLEXITY
--------------------------------------------------------------------------------

O((x2 - x1 + 1) * (y2 - y1 + 1))

We may visit every point inside the rectangle.

--------------------------------------------------------------------------------
SPACE COMPLEXITY
--------------------------------------------------------------------------------

O(1)

No extra data structure is used.

================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
We do NOT need to check every point of the rectangle.

We only need to find the point inside/on the rectangle that is closest to
the circle's center.

Suppose the closest point is:

    (xi, yi)

If the distance from:

    (xCenter, yCenter)

to:

    (xi, yi)

is <= radius,

then the circle overlaps the rectangle.

--------------------------------------------------------------------------------
INTUITION
--------------------------------------------------------------------------------

For the x-coordinate:

    If xCenter is inside [x1, x2]:
        closest x = xCenter

    If xCenter is left of rectangle:
        closest x = x1

    If xCenter is right of rectangle:
        closest x = x2

This can be written compactly as:

    xi = max(x1, min(xCenter, x2))

Similarly for y:

    yi = max(y1, min(yCenter, y2))

Now we have the closest point on/in the rectangle.

Then calculate squared distance:

    dx = xi - xCenter
    dy = yi - yCenter

    distanceSquared = dx*dx + dy*dy

The circle overlaps if:

    distanceSquared <= radius*radius


WHY DON'T WE USE SQRT?
----------------------

Normally:

    distance = sqrt(dx*dx + dy*dy)

But we only need to compare distance with radius:

    sqrt(dx*dx + dy*dy) <= radius

Squaring both sides gives:

    dx*dx + dy*dy <= radius*radius

So sqrt() is unnecessary.

--------------------------------------------------------------------------------
PSEUDO CODE
--------------------------------------------------------------------------------

xi = max(x1, min(xCenter, x2))
yi = max(y1, min(yCenter, y2))

dx = xi - xCenter
dy = yi - yCenter

if dx*dx + dy*dy <= radius*radius:
    return true
else:
    return false

--------------------------------------------------------------------------------
COMPLETE OPTIMAL CODE
--------------------------------------------------------------------------------

class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        int xi = max(x1, min(xCenter, x2));
        int yi = max(y1, min(yCenter, y2));

        int dx = xi - xCenter;
        int dy = yi - yCenter;

        return dx * dx + dy * dy <= radius * radius;
    }
};

--------------------------------------------------------------------------------
TIME COMPLEXITY
--------------------------------------------------------------------------------

O(1)

We perform only a constant number of operations.

--------------------------------------------------------------------------------
SPACE COMPLEXITY
--------------------------------------------------------------------------------

O(1)

Only a few integer variables are used.

================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Example:

    radius  = 1
    center  = (0, 0)

    rectangle:
        x1 = -1
        y1 = -1
        x2 = 1
        y2 = 1


STEP 1: Find closest x

    xi = max(-1, min(0, 1))
       = max(-1, 0)
       = 0


STEP 2: Find closest y

    yi = max(-1, min(0, 1))
       = max(-1, 0)
       = 0


Closest point:

    (xi, yi) = (0, 0)


STEP 3: Calculate difference

    dx = 0 - 0 = 0
    dy = 0 - 0 = 0


STEP 4: Compare squared distance

    dx*dx + dy*dy <= radius*radius

    0*0 + 0*0 <= 1*1

    0 <= 1

Therefore:

    true


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
Geometry + Closest Point / Clamping


KEY OBSERVATION
---------------
For an axis-aligned rectangle, the closest point to any given point can be
found independently for x and y.

Use:

    max(lowerBound, min(value, upperBound))

This is called clamping.


COMMON MISTAKES
---------------

1. Comparing radius directly with x/y coordinates.

   WRONG:
       radius == x1

   Radius represents a distance, while x1 is a coordinate.


2. Mixing x and y coordinates.

   WRONG:
       if (y1 > xCenter)

   CORRECT:
       if (y1 > yCenter)


3. Forgetting the equality case.

   Overlap includes touching.

   Therefore:

       distanceSquared <= radiusSquared

   NOT:

       distanceSquared < radiusSquared


4. Using sqrt() unnecessarily.

   Prefer:

       dx*dx + dy*dy <= radius*radius


5. Checking only the rectangle corners.

   The closest point to the circle center can lie on an edge or inside the
   rectangle, not necessarily at a corner.


WHEN TO USE THIS APPROACH
-------------------------
Use this closest-point/clamping technique when:

    - You have a point and an axis-aligned rectangle.
    - You need the minimum distance between them.
    - You need to determine circle-rectangle intersection.
    - You want an O(1) geometry solution.

General template:

    closestX = max(x1, min(pointX, x2))
    closestY = max(y1, min(pointY, y2))

Then calculate the distance from the original point to the closest point.

================================================================================
*/


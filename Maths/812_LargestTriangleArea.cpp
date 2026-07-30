#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double largestTriangleArea(vector<vector<int>> &points)
    {
        int n = points.size();
        double ans = 0.0;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {

                    double area = abs(
                                      points[i][0] * (points[j][1] - points[k][1]) +
                                      points[j][0] * (points[k][1] - points[i][1]) +
                                      points[k][0] * (points[i][1] - points[j][1])) /
                                  2.0;

                    ans = max(ans, area);
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<vector<int>> points = {
        {1, 0},
        {0, 0},
        {0, 1}};

    cout << fixed << setprecision(5)
         << obj.largestTriangleArea(points) << endl;

    return 0;
}

/*

======================== Leetcode 812. Largest Triangle Area ========================

Problem Statement:
------------------
Given an array of points on the X-Y plane, return the largest area of any
triangle that can be formed by any three different points.

The answer is accepted if it is within 10^-5 of the actual answer.

Example:
--------
Input:
points = [[0,0],[0,1],[1,0],[0,2],[2,0]]

Output:
2.00000

Explanation:
Triangle formed by (0,2), (2,0), (0,0) has the maximum area = 2.

=============================================================================
Brute Force Approach
=============================================================================

Idea:
-----
Generate every possible combination of three points.
For each triplet, calculate the triangle area using the Shoelace Formula.
Keep the maximum area found.

Since N ≤ 50, O(N³) is completely acceptable.

Pseudo Code:
------------
ans = 0

for i = 0 to n-1
    for j = i+1 to n-1
        for k = j+1 to n-1
            area = shoelace(i,j,k)
            ans = max(ans, area)

return ans

Complete Brute Force Code:

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {

        int n = points.size();
        double ans = 0;

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                for(int k=j+1;k<n;k++){

                    double area = abs(
                        points[i][0]*(points[j][1]-points[k][1]) +
                        points[j][0]*(points[k][1]-points[i][1]) +
                        points[k][0]*(points[i][1]-points[j][1])
                    ) / 2.0;

                    ans = max(ans, area);
                }
            }
        }

        return ans;
    }
};

Time Complexity:
O(N³)

Space Complexity:
O(1)

=============================================================================
Optimal Approach
=============================================================================

Observation:
------------
The maximum number of points is only 50.

Total possible triangles:

50C3 = 19600

Checking every triangle is efficient enough.
Therefore, brute force itself is the optimal solution.

Intuition:
----------
Use the Shoelace Formula:

Area =
|x1(y2−y3) + x2(y3−y1) + x3(y1−y2)| / 2

Compute the area for every triplet and keep the maximum.

Pseudo Code:
------------
maxArea = 0

for every triplet
    compute area
    update maximum

return maximum

Complete Optimal Code:

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {

        int n = points.size();
        double ans = 0.0;

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                for(int k=j+1;k<n;k++){

                    double area = abs(
                        points[i][0]*(points[j][1]-points[k][1]) +
                        points[j][0]*(points[k][1]-points[i][1]) +
                        points[k][0]*(points[i][1]-points[j][1])
                    ) / 2.0;

                    ans = max(ans, area);
                }
            }
        }

        return ans;
    }
};

Time Complexity:
O(N³)

Space Complexity:
O(1)

=============================================================================
Dry Run
=============================================================================

Input:
points = {{1,0},{0,0},{0,1}}

Only one triangle exists.

Area

= |1*(0-1) + 0*(1-0) + 0*(0-0)| / 2

= |-1| / 2

= 0.5

Maximum Area = 0.50000

=============================================================================
Interview Notes
=============================================================================

Pattern:
--------
Geometry + Brute Force Enumeration

Key Observation:
----------------
Since N is very small (≤ 50), enumerating all triplets is already optimal.

Common Mistakes:
----------------
1. Returning int instead of double.
2. Forgetting abs().
3. Dividing by 2 instead of 2.0.
4. Incorrect Shoelace Formula.

When to use this approach:
--------------------------
Use this approach when:
- Number of points is small.
- Need to evaluate every possible triangle.
- Geometric formula allows O(1) area computation.

=============================================================================

*/
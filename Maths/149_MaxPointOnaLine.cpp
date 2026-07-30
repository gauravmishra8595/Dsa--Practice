#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        if (n <= 2)
            return n;

        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            unordered_map<string, int> mp;
            int duplicate = 1;
            int maxi = 0;

            for (int j = i + 1; j < n; j++)
            {
                long long dx = (long long)points[j][0] - points[i][0];
                long long dy = (long long)points[j][1] - points[i][1];

                if (dx == 0 && dy == 0)
                {
                    duplicate++;
                    continue;
                }

                long long g = gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;

                if (dx < 0)
                {
                    dx = -dx;
                    dy = -dy;
                }
                else if (dx == 0)
                {
                    dy = 1;
                }
                else if (dy == 0)
                {
                    dx = 1;
                }

                string key = to_string(dx) + "#" + to_string(dy);
                maxi = max(maxi, ++mp[key]);
            }

            ans = max(ans, maxi + duplicate);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<vector<int>> points = {
        {1, 1},
        {2, 2},
        {3, 3}};

    cout << obj.maxPoints(points) << endl;

    return 0;
}

/*

===========================
Leetcode 149. Max Points on a Line
===========================

-----------------------------------
Problem Statement
-----------------------------------
Given an array points where points[i] = [xi, yi] represents a point on the
2D plane, return the maximum number of points that lie on the same straight line.

-----------------------------------
Example
-----------------------------------

Input:
points = [[1,1],[2,2],[3,3]]

Output:
3

Explanation:
All three points lie on the same line.

============================================================
BRUTE FORCE APPROACH
============================================================

Idea
----
Check every pair of points.
For every pair, count how many points lie on the same line using
cross multiplication.

Pseudo Code
-----------
answer = 1

for every pair(i,j)
    count = 2

    for every point k
        if k lies on line(i,j)
            count++

    answer = max(answer,count)

------------------------------------------------------------
Complete Brute Force Code
------------------------------------------------------------

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {

        int n = points.size();

        if(n<=2)
            return n;

        int ans=2;

        for(int i=0;i<n;i++){

            for(int j=i+1;j<n;j++){

                int cnt=2;

                for(int k=0;k<n;k++){

                    if(k==i || k==j)
                        continue;

                    long long x1=points[j][0]-points[i][0];
                    long long y1=points[j][1]-points[i][1];

                    long long x2=points[k][0]-points[i][0];
                    long long y2=points[k][1]-points[i][1];

                    if(x1*y2==y1*x2)
                        cnt++;
                }

                ans=max(ans,cnt);
            }
        }

        return ans;
    }
};

Time Complexity
---------------
O(N^3)

Space Complexity
----------------
O(1)

============================================================
OPTIMAL APPROACH
============================================================

Observation
-----------
For every point, every other point forms a slope.

Points having the same reduced slope from the current point
belong to the same line.

Instead of using floating point slopes, normalize using GCD.

Intuition
---------
Fix one point.

Store every reduced slope in a hashmap.

Maximum frequency of any slope from this point
+ duplicate points
gives answer through that point.

Repeat for every starting point.

Pseudo Code
-----------
answer = 0

for every point i

    map = empty
    duplicate = 1
    best = 0

    for every point j > i

        dx = xj-xi
        dy = yj-yi

        if duplicate
            duplicate++
            continue

        reduce (dx,dy) using gcd

        normalize sign

        map[slope]++

        best=max(best,map[slope])

    answer=max(answer,best+duplicate)

return answer

------------------------------------------------------------
Complete Optimal Code
------------------------------------------------------------

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) return n;

        int ans = 0;

        for (int i = 0; i < n; i++) {
            unordered_map<string, int> mp;
            int duplicate = 1;
            int maxi = 0;

            for (int j = i + 1; j < n; j++) {
                long long dx = (long long)points[j][0] - points[i][0];
                long long dy = (long long)points[j][1] - points[i][1];

                if (dx == 0 && dy == 0) {
                    duplicate++;
                    continue;
                }

                long long g = gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;

                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                }
                else if (dx == 0) {
                    dy = 1;
                }
                else if (dy == 0) {
                    dx = 1;
                }

                string key = to_string(dx) + "#" + to_string(dy);

                maxi = max(maxi, ++mp[key]);
            }

            ans = max(ans, maxi + duplicate);
        }

        return ans;
    }
};

Time Complexity
---------------
O(N^2)

Space Complexity
----------------
O(N)

============================================================
Dry Run
============================================================

points =
(1,1)
(2,2)
(3,3)

i = (1,1)

Slope to (2,2)
dx=1
dy=1
map[(1,1)] = 1

Slope to (3,3)
dx=2
dy=2

Reduce by gcd=2

(1,1)

map[(1,1)] = 2

duplicate = 1

answer = 2+1 = 3

Final Answer = 3

============================================================
Interview Notes
============================================================

Pattern
-------
HashMap + Geometry + GCD Normalization

Key Observation
---------------
Points on the same line produce identical normalized slopes.

Common Mistakes
---------------
1. Using double slope (precision errors).
2. Forgetting duplicate points.
3. Not normalizing signs.
4. Handling vertical/horizontal lines incorrectly.
5. Overflow while computing differences.

When to use this approach
-------------------------
Whenever grouping points by slope or direction is required.
Reducing fractions with GCD avoids floating-point precision issues and
is the standard competitive programming solution.

*/
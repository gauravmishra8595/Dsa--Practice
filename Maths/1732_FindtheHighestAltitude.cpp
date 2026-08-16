#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    int largestAltitude(vector<int> &gain)
    {
        int altitude = 0;
        int maxAltitude = 0;

        for (int g : gain)
        {
            altitude += g;
            maxAltitude = max(maxAltitude, altitude);
        }

        return maxAltitude;
    }
};

int main()
{
    Solution sol;

    vector<int> gain1 = {-5, 1, 5, 0, -7};
    vector<int> gain2 = {-4, -3, -2, -1, 4, 3, 2};

    cout << sol.largestAltitude(gain1) << '\n'; // 1
    cout << sol.largestAltitude(gain2) << '\n'; // 0

    return 0;
}

/*
================================================================================
                         LEETCODE 1732
                    FIND THE HIGHEST ALTITUDE
================================================================================

Problem Statement:
------------------
A biker starts at altitude 0.

You are given an integer array gain where:
    gain[i] = altitude gain/loss between point i and point i + 1.

The altitude at each point is obtained by taking the prefix sum of gain.

Return the highest altitude reached by the biker.


Example:
--------
Input:
    gain = [-5, 1, 5, 0, -7]

Altitude:
    Start = 0
    After -5 = -5
    After +1 = -4
    After +5 = 1
    After +0 = 1
    After -7 = -6

Highest altitude = 1

Output:
    1


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Calculate the altitude at every point and store all altitudes in an array.
Then find the maximum altitude.

Pseudo Code:
------------
altitude = 0
create an array altitudes

add 0 to altitudes

for every gain:
    altitude += gain
    add altitude to altitudes

return maximum value in altitudes


Complete Brute Force Code:
--------------------------
/*
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int altitude = 0;
        vector<int> altitudes;

        altitudes.push_back(0);

        for (int g : gain) {
            altitude += g;
            altitudes.push_back(altitude);
        }

        return *max_element(altitudes.begin(), altitudes.end());
    }
};
*/

// Time Complexity:
// ----------------
// O(N)

// Space Complexity:
// -----------------
// O(N)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The altitude at every point is simply the prefix sum of gain.

// We do not need to store every altitude.

// We only need:
// 1. Current altitude.
// 2. Maximum altitude seen so far.


// Intuition:
// ---------
// Start from altitude 0.

// For every gain:
//     current altitude += gain

// After updating the altitude, compare it with the maximum altitude.

// Since the biker starts at altitude 0, initialize:

//     altitude = 0
//     maxAltitude = 0

// This also handles cases where all gains are negative.


// Pseudo Code:
// ------------
// altitude = 0
// maxAltitude = 0

// for every gain:
//     altitude += gain
//     maxAltitude = max(maxAltitude, altitude)

// return maxAltitude


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int altitude = 0;
        int maxAltitude = 0;

        for (int g : gain) {
            altitude += g;
            maxAltitude = max(maxAltitude, altitude);
        }

        return maxAltitude;
    }
};
*/

// Time Complexity:
// ----------------
// O(N)

// Space Complexity:
// -----------------
// O(1)


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// Input:
//     gain = [-5, 1, 5, 0, -7]

// Initial:
//     altitude = 0
//     maxAltitude = 0

// Step 1:
//     gain = -5
//     altitude = 0 + (-5) = -5
//     maxAltitude = max(0, -5) = 0

// Step 2:
//     gain = 1
//     altitude = -5 + 1 = -4
//     maxAltitude = max(0, -4) = 0

// Step 3:
//     gain = 5
//     altitude = -4 + 5 = 1
//     maxAltitude = max(0, 1) = 1

// Step 4:
//     gain = 0
//     altitude = 1 + 0 = 1
//     maxAltitude = max(1, 1) = 1

// Step 5:
//     gain = -7
//     altitude = 1 - 7 = -6
//     maxAltitude = max(1, -6) = 1

// Answer:
//     1


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Prefix Sum


// Key Observation:
// ----------------
// Altitude at each point = prefix sum of gain.

// We only need to track the current prefix sum and its maximum.


// Common Mistakes:
// ----------------
// 1. Forgetting that the biker starts at altitude 0.
// 2. Initializing maxAltitude to a negative value unnecessarily.
// 3. Updating maxAltitude before updating altitude.
// 4. Using O(N) extra space when O(1) space is sufficient.


// When to use this approach:
// --------------------------
// Use this pattern whenever:
// - A problem asks for cumulative changes.
// - Each element represents a change from the previous state.
// - You need the maximum/minimum value reached during the process.
// - The answer depends on prefix sums.


// Complexity:
// -----------
// Time  : O(N)
// Space : O(1)

// ================================================================================
// */

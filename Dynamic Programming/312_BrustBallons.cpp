#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        vector<int> arr;
        arr.push_back(1);
        for(int x : nums) arr.push_back(x);
        arr.push_back(1);

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for(int len = 1; len <= n; len++) {
            for(int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                for(int k = i; k <= j; k++) {
                    dp[i][j] = max(dp[i][j],
                                   arr[i - 1] * arr[k] * arr[j + 1]
                                   + dp[i][k - 1]
                                   + dp[k + 1][j]);
                }
            }
        }

        return dp[1][n];
    }
};

int main() {
    Solution obj;

    vector<int> nums = {3,1,5,8};

    cout << "Maximum Coins = " << obj.maxCoins(nums) << endl;

    return 0;
}

/*

===============================================================================
                                LEETCODE 312
                               BURST BALLOONS
===============================================================================

Problem Statement
-----------------
You are given n balloons, indexed from 0 to n-1.

Each balloon has a number written on it represented by nums[i].

You are asked to burst all the balloons.

If you burst balloon i, you gain:

nums[left] * nums[i] * nums[right]

where left and right are the adjacent balloons of i after previous bursts.

After bursting i, it disappears.

Return the maximum coins you can collect.

Assume virtual balloons having value 1 exist at both ends.

-------------------------------------------------------------------------------
Example
-------------------------------------------------------------------------------

Input:
nums = [3,1,5,8]

Output:
167

Explanation:

Optimal bursting order:
1 -> 5 -> 3 -> 8

Maximum Coins = 167

===============================================================================
APPROACH 1 : Pure Brute Force (Recursive Simulation)
===============================================================================

Idea
----
Try every balloon as the next balloon to burst.

For every choice:
- Calculate earned coins
- Remove balloon
- Solve recursively

Take maximum.

Since every recursive call creates many new states,
time becomes factorial.

Pseudo Code
------------

solve(nums):
    if empty
        return 0

    ans = 0

    for every balloon i

        left = adjacent left else 1
        right = adjacent right else 1

        gain = left * nums[i] * right

        remove nums[i]

        ans=max(ans,gain+solve(newArray))

    return ans

Complete Brute Force Code
-------------------------

class Solution {
public:

    int solve(vector<int> nums){

        if(nums.empty())
            return 0;

        int ans=0;

        for(int i=0;i<nums.size();i++){

            int left=(i==0)?1:nums[i-1];
            int right=(i==nums.size()-1)?1:nums[i+1];

            int gain=left*nums[i]*right;

            vector<int> temp;

            for(int j=0;j<nums.size();j++)
                if(j!=i)
                    temp.push_back(nums[j]);

            ans=max(ans,gain+solve(temp));
        }

        return ans;
    }

    int maxCoins(vector<int>& nums){
        return solve(nums);
    }
};

Time Complexity
---------------
O(N!)

Space Complexity
----------------
O(N)

===============================================================================
APPROACH 2 : Recursion on Last Burst
===============================================================================

Idea
----
Instead of choosing the first balloon to burst,
choose the LAST balloon to burst inside an interval.

If k is last burst between i...j

Left interval and right interval become independent.

Pseudo Code
------------

solve(i,j)

if(i>j)
    return 0

ans=0

for(k=i to j)

    ans=max(ans,
            leftBoundary*k*rightBoundary
            +solve(i,k-1)
            +solve(k+1,j))

return ans

Time Complexity
---------------
Exponential

Space Complexity
----------------
O(N)

===============================================================================
APPROACH 3 : Memoization (Top Down DP)
===============================================================================

Idea
----
Store answer of every interval (i,j).

Number of intervals

N²

Each interval tries every balloon.

Pseudo Code
------------

if(dp[i][j]!=-1)
    return dp[i][j]

for(k=i to j)

return dp[i][j]

Time Complexity
---------------
O(N³)

Space Complexity
----------------
O(N²)

===============================================================================
APPROACH 4 : Tabulation (Bottom Up DP)  <-- Optimal
===============================================================================

Observation
-----------
Choosing the first balloon is difficult because neighbours keep changing.

Choosing the LAST balloon is easy because neighbours are fixed.

Suppose interval is

i ......... j

If k is last burst

then

left interval
[i...k-1]

and

right interval
[k+1...j]

are already solved.

Coins earned

arr[i-1] * arr[k] * arr[j+1]

because only boundary balloons remain.

Transition

dp[i][j] =
max over all k

arr[i-1]*arr[k]*arr[j+1]
+
dp[i][k-1]
+
dp[k+1][j]

-------------------------------------------------------------------------------
Intuition
-------------------------------------------------------------------------------

Convert problem into Interval DP.

Add

1 at beginning

1 at end

Then solve all intervals from smaller length to larger length.

Pseudo Code
-----------

Insert 1 at both ends

for length=1 to n

    for every interval

        for every last balloon

            dp[i][j]=max(
                current,
                leftCoins
                +rightCoins
                +currentBurst
            )

return dp[1][n]

Complete Optimal Code
---------------------

class Solution {
public:

    int maxCoins(vector<int>& nums){

        int n=nums.size();

        vector<int> arr;

        arr.push_back(1);

        for(int x:nums)
            arr.push_back(x);

        arr.push_back(1);

        vector<vector<int>> dp(n+2,vector<int>(n+2,0));

        for(int len=1;len<=n;len++){

            for(int i=1;i+len-1<=n;i++){

                int j=i+len-1;

                for(int k=i;k<=j;k++){

                    dp[i][j]=max(dp[i][j],
                    arr[i-1]*arr[k]*arr[j+1]
                    +dp[i][k-1]
                    +dp[k+1][j]);

                }
            }
        }

        return dp[1][n];
    }
};

Time Complexity
---------------
States = O(N²)

Transition = O(N)

Overall

O(N³)

Space Complexity
----------------
O(N²)

===============================================================================
Dry Run
===============================================================================

nums

3 1 5 8

After adding boundaries

1 3 1 5 8 1

Length = 1

dp[1][1]
dp[2][2]
dp[3][3]
dp[4][4]

Length = 2

dp[1][2]
dp[2][3]
dp[3][4]

...

Eventually

dp[1][4]

tries

Last burst = 3

Last burst = 1

Last burst = 5

Last burst = 8

Maximum becomes

167

Answer = 167

===============================================================================
Interview Notes
===============================================================================

Pattern
-------
- Interval DP
- Partition DP
- Matrix Chain Multiplication Pattern

Key Observation
---------------
Instead of deciding the first balloon to burst,
decide the LAST balloon to burst.

That makes left and right intervals completely independent.

Common Mistakes
---------------
1. Forgetting to add virtual balloons (1).
2. Trying greedy.
3. Bursting first instead of last.
4. Wrong interval indexing.
5. Filling DP in incorrect order.
6. Using original neighbours instead of interval boundaries.

When to use this approach
-------------------------
Whenever

1. Problem asks maximum/minimum after removing elements.

2. Neighbours keep changing.

3. Choosing the first operation is difficult.

4. Choosing the last operation fixes boundaries.

5. Interval DP / Partition DP is applicable.

===============================================================================
Complexity Summary
===============================================================================

Approach                 Time           Space

1. Brute Force           O(N!)          O(N)

2. Recursion             Exponential    O(N)

3. Memoization           O(N³)          O(N²)

4. Tabulation            O(N³)          O(N²)

Optimal Solution:
Tabulation Interval DP

===============================================================================

*/
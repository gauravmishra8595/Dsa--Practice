#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int robRange(vector<int> &nums, int start, int end)
    {
        int prev2 = 0;
        int prev1 = 0;

        for (int i = start; i <= end; i++)
        {
            int curr = max(prev1, nums[i] + prev2);

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int rob(vector<int> &nums)
    {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        return max(
            robRange(nums, 0, n - 2),
            robRange(nums, 1, n - 1));
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    Solution obj;

    cout << obj.rob(nums);

    return 0;
}

/*
=========================================================
        LeetCode 213. House Robber II
=========================================================

Problem Statement
-----------------
You are a professional robber planning to rob houses along a
street.

All houses are arranged in a circle.

Each house has some amount of money stored in it.

You cannot rob two adjacent houses because the security system
will be triggered.

Return the maximum amount of money you can rob.

Note:
The first and last houses are also adjacent because houses are
arranged in a circle.

---------------------------------------------------------
Example
---------------------------------------------------------

Input:
nums = [2,3,2]

Output:
3

Explanation:

Cannot rob first and last house together.

Options:

Rob houses:
3

or

2 + 2 (invalid because first and last are adjacent)

Answer = 3


=========================================================
Brute Force Approach (Recursion)
=========================================================

Idea
----
This is an extension of House Robber I.

For every house:
- Take the house.
- Skip the house.

Because the houses are circular, we need to handle the
restriction between the first and last house.

Try all possible combinations recursively.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

solve(index):

    if index < start:
        return 0

    take = nums[index] + solve(index-2)

    skip = solve(index-1)

    return max(take, skip)


For circular condition:

Case 1:
Exclude last house.

Case 2:
Exclude first house.


Answer:

max(case1, case2)

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:

    int solve(vector<int>& nums, int i, int start){

        if(i < start)
            return 0;

        int take = nums[i] + solve(nums, i-2, start);

        int skip = solve(nums, i-1, start);

        return max(take, skip);
    }


    int rob(vector<int>& nums){

        int n = nums.size();

        if(n == 1)
            return nums[0];


        int case1 = solve(nums, n-2, 0);

        int case2 = solve(nums, n-1, 1);


        return max(case1, case2);
    }
};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

O(2^n)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(n)

(Recursion Stack)

=========================================================
Optimal Approach (DP + Space Optimization)
=========================================================

Observation
-----------
The only difference from House Robber I is:

First house and last house cannot both be selected.

Therefore, break the circle into two linear problems.

Case 1:
Rob houses from index 0 to n-2.

Case 2:
Rob houses from index 1 to n-1.

Final answer:

max(case1, case2)

---------------------------------------------------------
Intuition
---------
After removing one end of the circle, the problem becomes
exactly the House Robber I problem.

For a linear range:

dp[i] = max(
            dp[i-1],
            nums[i] + dp[i-2]
         )

Only previous two states are required, so use variables.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

function robRange(start,end):

    prev2 = 0
    prev1 = 0

    for i=start to end:

        curr=max(prev1, nums[i]+prev2)

        prev2=prev1

        prev1=curr

    return prev1


Main:

if n==1:
    return nums[0]


case1 = robRange(0,n-2)

case2 = robRange(1,n-1)


return max(case1,case2)

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {

public:

    int robRange(vector<int>& nums,int start,int end){

        int prev2=0;

        int prev1=0;


        for(int i=start;i<=end;i++){

            int curr=max(
                prev1,
                nums[i]+prev2
            );

            prev2=prev1;

            prev1=curr;
        }


        return prev1;
    }


    int rob(vector<int>& nums){

        int n=nums.size();


        if(n==1)
            return nums[0];


        return max(
            robRange(nums,0,n-2),
            robRange(nums,1,n-1)
        );
    }
};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

O(n)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(1)

=========================================================
Dry Run
=========================================================

nums = [2,3,2,3]


Because circular:

Case 1:
Exclude last house

Range:
[2,3,2]

Rob:

max(2,3)=3


Case 2:
Exclude first house

Range:
[3,2,3]

Rob:

Take first 3
Take last 3

Total = 6


Answer:

max(3,6)=6


=========================================================
Interview Notes
=========================================================

Pattern
-------

Dynamic Programming

House Robber Pattern

Linear DP + Space Optimization


---------------------------------------------------------
Key Observation
---------------------------------------------------------

Circular array means:

First and last elements are adjacent.

So both cannot be chosen together.

Break into two linear cases:

1. Ignore first house.

2. Ignore last house.


---------------------------------------------------------
Common Mistakes
---------------------------------------------------------

1. Applying House Robber I directly.

2. Taking both first and last houses.

3. Forgetting n==1 edge case.

4. Wrong range boundaries.

5. Creating unnecessary 2D DP.


---------------------------------------------------------
When to use this approach
---------------------------------------------------------

Use this approach when:

- The problem is House Robber with circular arrangement.

- First and last elements have dependency.

- Removing one boundary converts the problem into linear DP.


=========================================================
*/
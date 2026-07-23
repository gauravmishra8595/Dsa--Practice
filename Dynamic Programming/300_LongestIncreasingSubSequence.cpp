#include <bits/stdc++.h>
using namespace std;

// ===================== Optimal Solution (O(n log n)) =====================
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> temp;

        for (int x : nums)
        {
            auto it = lower_bound(temp.begin(), temp.end(), x);

            if (it == temp.end())
                temp.push_back(x);
            else
                *it = x;
        }

        return temp.size();
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    cout << "Length of LIS = " << obj.lengthOfLIS(nums);

    return 0;
}

/*

===============================================================================
                         LEETCODE 300 - Longest Increasing Subsequence
===============================================================================

Problem Statement
-----------------
Given an integer array nums, return the length of the longest strictly
increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some
or no elements without changing the order of the remaining elements.

Example
-------
Input:
nums = [10,9,2,5,3,7,101,18]

Output:
4

Explanation:
One LIS is [2,3,7,101].

===============================================================================
AVAILABLE APPROACHES
===============================================================================

1. Brute Force (Generate all subsequences)
   Time  : O(2^n)
   Space : O(n)

2. Recursion + Memoization (DP)
   Time  : O(n^2)
   Space : O(n^2)

3. Bottom-Up DP (Classic LIS)
   Time  : O(n^2)
   Space : O(n)

4. DP + Binary Search (Patience Sorting)  <-- BEST
   Time  : O(n log n)
   Space : O(n)

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea
----
Generate every subsequence.
Check whether it is strictly increasing.
Keep track of the maximum length.

Pseudo Code
-----------
ans = 0

DFS(index, prev, length)

if(index==n)
    ans=max(ans,length)

Skip current element

Take current element if nums[index] > prev

Complete Brute Force Code
-------------------------

class Solution {
public:

    int ans = 0;

    void solve(int idx, int prev, int len, vector<int>& nums){

        if(idx==nums.size()){
            ans=max(ans,len);
            return;
        }

        solve(idx+1,prev,len,nums);

        if(prev==-1 || nums[idx]>nums[prev]){
            solve(idx+1,idx,len+1,nums);
        }
    }

    int lengthOfLIS(vector<int>& nums){
        solve(0,-1,0,nums);
        return ans;
    }
};

Time Complexity
---------------
O(2^n)

Space Complexity
----------------
O(n)

===============================================================================
BETTER APPROACH (DP O(n^2))
===============================================================================

Idea
----
Let dp[i] = Length of LIS ending at index i.

For every previous element j<i,
if(nums[j] < nums[i])

dp[i]=max(dp[i],dp[j]+1)

Time Complexity
---------------
O(n^2)

Space Complexity
----------------
O(n)

===============================================================================
OPTIMAL APPROACH (DP + Binary Search / Patience Sorting)
===============================================================================

Observation
-----------
We don't actually need the complete subsequence.

We only need to maintain the smallest possible ending value for every LIS
length.

Example:

Length 1 -> smallest ending value

Length 2 -> smallest ending value

Length 3 -> smallest ending value

Smaller ending values give better chances to extend later.

Intuition
---------
Maintain an array temp.

temp[i] = minimum ending element of an increasing subsequence of length i+1.

For every element:

If it is larger than all elements,
append it.

Otherwise,
replace the first element >= current value using lower_bound.

The size of temp is the answer.

Pseudo Code
-----------

temp = empty

for every num

    pos = lower_bound(temp,num)

    if(pos==end)
        push_back(num)

    else
        replace with num

return temp.size()

Complete Optimal Code
---------------------

class Solution {
public:

    int lengthOfLIS(vector<int>& nums){

        vector<int> temp;

        for(int x:nums){

            auto it=lower_bound(temp.begin(),temp.end(),x);

            if(it==temp.end())
                temp.push_back(x);
            else
                *it=x;
        }

        return temp.size();
    }
};

Time Complexity
---------------
O(n log n)

Space Complexity
----------------
O(n)

===============================================================================
DRY RUN
===============================================================================

nums

10 9 2 5 3 7 101 18

Initially

temp = []

---------------------------------

10

temp = [10]

---------------------------------

9

Replace 10

temp = [9]

---------------------------------

2

Replace 9

temp = [2]

---------------------------------

5

Append

temp = [2,5]

---------------------------------

3

Replace 5

temp = [2,3]

---------------------------------

7

Append

temp = [2,3,7]

---------------------------------

101

Append

temp = [2,3,7,101]

---------------------------------

18

Replace 101

temp = [2,3,7,18]

Answer = size(temp)

= 4

===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern
-------
✔ Dynamic Programming

✔ Binary Search

✔ Patience Sorting

Key Observation
---------------
The temp array is NOT the actual LIS.

It only stores the minimum possible tail element for every subsequence length.

Common Mistakes
---------------
1. Using upper_bound instead of lower_bound.

2. Thinking temp is the actual LIS.

3. Replacing with wrong position.

4. Forgetting LIS is STRICTLY increasing.

5. Returning last element instead of temp.size().

When to use this approach
-------------------------
Whenever asked:

✔ Longest Increasing Subsequence

✔ Strictly Increasing Subsequence

✔ Need only the length

✔ n up to 2e5 or larger

Use O(n log n) Binary Search solution.

===============================================================================

*/

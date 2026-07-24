#include <bits/stdc++.h>
using namespace std;

// Optimal Solution: Dynamic Programming
class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {

        int n = nums.size();

        vector<int> dp(n, 1);
        vector<int> count(n, 1);

        int maxLen = 1;

        for (int i = 0; i < n; i++)
        {

            for (int j = 0; j < i; j++)
            {

                if (nums[j] < nums[i])
                {

                    if (dp[j] + 1 > dp[i])
                    {

                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    }
                    else if (dp[j] + 1 == dp[i])
                    {

                        count[i] += count[j];
                    }
                }
            }

            maxLen = max(maxLen, dp[i]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++)
        {

            if (dp[i] == maxLen)
                ans += count[i];
        }

        return ans;
    }
};

int main()
{

    Solution obj;

    vector<int> nums = {1, 3, 5, 4, 7};

    cout << obj.findNumberOfLIS(nums);

    return 0;
}

/*

============================================================
       LEETCODE 673 - NUMBER OF LONGEST INCREASING SUBSEQUENCE
============================================================


Problem Statement:
------------------

Given an integer array nums, return the number of longest increasing
subsequences.

A subsequence is a sequence that can be derived from an array by
deleting some or no elements without changing the order of remaining
elements.



Example:
--------

Input:

nums = [1,3,5,4,7]


Output:

2


Explanation:

The two longest increasing subsequences are:

[1,3,5,7]

[1,3,4,7]

Length of LIS = 4

Number of LIS = 2



============================================================
BRUTE FORCE APPROACH
============================================================


Idea:
-----

Generate all possible subsequences.

For every subsequence:

1. Check if it is increasing.
2. Find its length.
3. Count how many have maximum length.


This explores all possible choices.



Pseudo Code:
------------

generate(index, current):

    if index == n:

        check current sequence

        update answer

        return


    take current element

    generate(index + 1)


    skip current element

    generate(index + 1)



Complete Brute Force Code:

class Solution {

public:

    int maxLen = 0;
    int ans = 0;


    void solve(vector<int>& nums,
               int idx,
               vector<int>& curr) {


        if(idx == nums.size()) {


            for(int i = 1; i < curr.size(); i++) {

                if(curr[i] <= curr[i-1])
                    return;
            }


            if(curr.size() > maxLen) {

                maxLen = curr.size();
                ans = 1;

            }
            else if(curr.size() == maxLen) {

                ans++;
            }


            return;
        }



        curr.push_back(nums[idx]);

        solve(nums, idx + 1, curr);

        curr.pop_back();



        solve(nums, idx + 1, curr);
    }



    int findNumberOfLIS(vector<int>& nums) {

        vector<int> curr;

        solve(nums, 0, curr);

        return ans;
    }
};



Time Complexity:
----------------

O(2^n * n)


Generating all subsequences.



Space Complexity:
-----------------

O(n)


Recursion stack.



============================================================
OPTIMAL APPROACH
============================================================


Observation:
------------

For every index we need two pieces of information:

1. Length of LIS ending at this index.

2. Number of LIS ending at this index.



Intuition:
----------

This is similar to Longest Increasing Subsequence.

Maintain:

dp[i]:

Length of longest increasing subsequence ending at i.


count[i]:

Number of LIS of length dp[i] ending at i.



For every previous index j:

If:

nums[j] < nums[i]


Then nums[i] can extend the subsequence ending at j.



Case 1:

dp[j] + 1 > dp[i]


A longer LIS is found.

Update:

dp[i] = dp[j] + 1

count[i] = count[j]



Case 2:

dp[j] + 1 == dp[i]


Another LIS of the same length is found.

Add:

count[i] += count[j]



Pseudo Code:
------------

initialize:

dp[i] = 1

count[i] = 1



for i from 0 to n-1:

    for j from 0 to i-1:

        if nums[j] < nums[i]:

            if dp[j]+1 > dp[i]:

                dp[i] = dp[j]+1

                count[i] = count[j]


            else if dp[j]+1 == dp[i]:

                count[i] += count[j]



find maximum LIS length


sum all count[i] where:

dp[i] == maximum length



Complete Optimal Code:

class Solution {

public:

    int findNumberOfLIS(vector<int>& nums) {


        int n = nums.size();


        vector<int> dp(n,1);

        vector<int> count(n,1);



        int maxLen = 1;



        for(int i = 0; i < n; i++) {


            for(int j = 0; j < i; j++) {


                if(nums[j] < nums[i]) {


                    if(dp[j]+1 > dp[i]) {


                        dp[i] = dp[j]+1;

                        count[i] = count[j];


                    }
                    else if(dp[j]+1 == dp[i]) {


                        count[i] += count[j];
                    }
                }
            }


            maxLen = max(maxLen, dp[i]);
        }




        int ans = 0;



        for(int i = 0; i < n; i++) {


            if(dp[i] == maxLen)

                ans += count[i];
        }



        return ans;
    }
};



Time Complexity:
----------------

O(n^2)


For every index, compare with previous elements.



Space Complexity:
-----------------

O(n)


For dp and count arrays.



============================================================
DRY RUN
============================================================


nums = [1,3,5,4,7]


Initial:

dp:

[1,1,1,1,1]


count:

[1,1,1,1,1]



Process 3:

1 < 3

dp[1] = 2

count[1] = 1



Process 5:

1,3 can extend

dp[2] = 3

count[2] = 1



Process 4:

1,3 can extend

dp[3] = 3

count[3] = 1



Process 7:

Can extend both:

1,3,5

1,3,4


dp[4] = 4

count[4] = 2



Maximum length = 4


Answer:

2



============================================================
INTERVIEW NOTES
============================================================


Pattern:
--------

Dynamic Programming

Longest Increasing Subsequence



Key Observation:
----------------

LIS length alone is not enough.

Need:

1. Length of LIS ending at each index.

2. Number of ways to achieve that length.



Common Mistakes:
----------------

1. Using binary search LIS approach.

   It gives length only, not count.


2. Forgetting to reset count when a longer LIS is found.


3. Adding counts when length is smaller.


4. Counting subsequences with different orders.



When to use this approach:
--------------------------

Use this approach when:

- Need LIS length and number of LIS.
- Need counting of optimal subsequences.
- Need information about previous states.

Similar problems:

- Longest Increasing Subsequence
- Maximum Sum Increasing Subsequence
- Russian Doll Envelopes



============================================================

*/
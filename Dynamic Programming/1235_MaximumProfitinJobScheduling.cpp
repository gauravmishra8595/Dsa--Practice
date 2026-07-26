#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<array<int, 3>> jobs;
    vector<int> dp;

    int solve(int index)
    {
        if (index >= jobs.size())
            return 0;

        if (dp[index] != -1)
            return dp[index];

        int next = lower_bound(
                       jobs.begin(),
                       jobs.end(),
                       jobs[index][1],
                       [](const array<int, 3> &job, int endTime)
                       {
                           return job[0] < endTime;
                       }) -
                   jobs.begin();

        int take = jobs[index][2] + solve(next);
        int skip = solve(index + 1);

        return dp[index] = max(take, skip);
    }

    int jobScheduling(vector<int> &startTime,
                      vector<int> &endTime,
                      vector<int> &profit)
    {

        int n = startTime.size();

        jobs.clear();

        for (int i = 0; i < n; i++)
        {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }

        sort(jobs.begin(), jobs.end());

        dp.assign(n, -1);

        return solve(0);
    }
};

int main()
{

    Solution obj;

    vector<int> startTime = {1, 2, 3, 3};
    vector<int> endTime = {3, 4, 5, 6};
    vector<int> profit = {50, 10, 40, 70};

    cout << "Maximum Profit = "
         << obj.jobScheduling(startTime, endTime, profit)
         << endl;

    return 0;
}

/*

===========================
Problem Statement
===========================

You are given three integer arrays:

startTime[i] -> starting time of ith job
endTime[i]   -> ending time of ith job
profit[i]    -> profit earned from ith job

Select a subset of non-overlapping jobs so that
the total profit is maximum.

Return the maximum profit.

LeetCode 1235 - Maximum Profit in Job Scheduling


===========================
Example
===========================

Input

startTime = [1,2,3,3]
endTime   = [3,4,5,6]
profit    = [50,10,40,70]

Output

120

Explanation

Choose

Job1 : (1,3) Profit = 50

Job4 : (3,6) Profit = 70

Total = 120


====================================================
Brute Force Approach
====================================================

Idea
----

For every job we have two choices:

1. Take the current job
2. Skip the current job

If we take a job,
find the next compatible job by linear search.

Return the maximum profit.

Pseudo Code
-----------

solve(index)

    if index==n
        return 0

    next=index+1

    while(next<n && jobs[next].start<jobs[index].end)
        next++

    take=profit+solve(next)

    skip=solve(index+1)

    return max(take,skip)

Complete Brute Force Code
-------------------------

class Solution {
public:

    vector<vector<int>> jobs;

    int solve(int index){

        if(index==jobs.size())
            return 0;

        int next=index+1;

        while(next<jobs.size() &&
              jobs[next][0]<jobs[index][1])
            next++;

        int take=jobs[index][2]+solve(next);

        int skip=solve(index+1);

        return max(take,skip);
    }

    int jobScheduling(vector<int>& startTime,
                      vector<int>& endTime,
                      vector<int>& profit){

        for(int i=0;i<startTime.size();i++)
            jobs.push_back({startTime[i],endTime[i],profit[i]});

        sort(jobs.begin(),jobs.end());

        return solve(0);
    }
};

Time Complexity
---------------
O(2^N)

Space Complexity
----------------
O(N)


====================================================
Optimal Approach
====================================================

Observation
-----------

Once jobs are sorted by starting time,

for every job,

we only need to know

the first job whose start time >= current job's end time.

Binary Search finds this in O(logN).

Memoization stores the answer for every index only once.

Intuition
---------

Sort jobs.

For every index,

Take current job

Profit = current profit + answer(next compatible job)

Skip current job

Profit = answer(next index)

Store maximum.

Pseudo Code
-----------

Sort jobs

solve(index)

    if index==n
        return 0

    if already computed
        return answer

    next = lower_bound(endTime)

    take = profit + solve(next)

    skip = solve(index+1)

    return max(take,skip)

Complete Optimal Code
---------------------

class Solution {
public:

    vector<array<int,3>> jobs;

    vector<int> dp;

    int solve(int index){

        if(index>=jobs.size())
            return 0;

        if(dp[index]!=-1)
            return dp[index];

        int next=lower_bound(

            jobs.begin(),

            jobs.end(),

            jobs[index][1],

            [](const array<int,3>& job,int value){

                return job[0]<value;

            }

        )-jobs.begin();

        int take=jobs[index][2]+solve(next);

        int skip=solve(index+1);

        return dp[index]=max(take,skip);
    }

    int jobScheduling(vector<int>& startTime,
                      vector<int>& endTime,
                      vector<int>& profit){

        int n=startTime.size();

        for(int i=0;i<n;i++)
            jobs.push_back({startTime[i],endTime[i],profit[i]});

        sort(jobs.begin(),jobs.end());

        dp.assign(n,-1);

        return solve(0);
    }
};

Time Complexity
---------------
Sorting        : O(N log N)

DP States      : O(N)

Binary Search  : O(log N) per state

Overall

O(N log N)

Space Complexity
----------------

Jobs : O(N)

DP   : O(N)

Recursion Stack : O(N)

Overall : O(N)


====================================================
Dry Run
====================================================

Jobs after sorting

(1,3,50)

(2,4,10)

(3,5,40)

(3,6,70)

solve(0)

Take

50 + solve(2)

solve(2)

Take

40 + solve(4)=40

Skip

solve(3)=70

Maximum=70

Back to solve(0)

Take

50+70=120

Skip

solve(1)=70

Maximum

120


====================================================
Interview Notes
====================================================

Pattern
-------

Weighted Interval Scheduling

DP + Binary Search

Key Observation
---------------

Sorting converts the problem into deciding

Take current job

or

Skip current job

Binary Search immediately finds the next compatible job.

Common Mistakes
---------------

1. Sorting by end time instead of start time.

2. Using upper_bound instead of lower_bound.

3. Forgetting jobs ending exactly when another starts
   are allowed.

4. Linear search for next job causing O(N²).

5. Forgetting memoization.

When to use this approach
-------------------------

Whenever the problem asks for

✔ Maximum profit

✔ Non-overlapping intervals

✔ Weighted interval scheduling

✔ DP + Binary Search

✔ Choosing compatible intervals

*/
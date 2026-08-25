#include <bits/stdc++.h>
#include<numeric>
using namespace std;
int gcd(int a, int b)
{
    while (b)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

class Solution
{
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int> &nums)
    {
        int mx = *max_element(nums.begin(), nums.end());

        // Precompute gcd values
        vector<vector<int>> gcdTable(mx + 1, vector<int>(mx + 1));
        for (int i = 0; i <= mx; i++)
        {
            for (int j = 0; j <= mx; j++)
            {
                if (i == 0)
                    gcdTable[i][j] = j;
                else if (j == 0)
                    gcdTable[i][j] = i;
                else
                    gcdTable[i][j] = gcd(i, j);
            }
        }

        vector<vector<int>> dp(mx + 1, vector<int>(mx + 1, 0));
        dp[0][0] = 1;

        for (int x : nums)
        {
            vector<vector<int>> ndp = dp;

            for (int g1 = 0; g1 <= mx; g1++)
            {
                for (int g2 = 0; g2 <= mx; g2++)
                {
                    if (dp[g1][g2] == 0)
                        continue;

                    int val = dp[g1][g2];

                    int ng1 = gcdTable[g1][x];
                    ndp[ng1][g2] = (ndp[ng1][g2] + val) % MOD;

                    int ng2 = gcdTable[g2][x];
                    ndp[g1][ng2] = (ndp[g1][ng2] + val) % MOD;
                }
            }

            dp = move(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= mx; g++)
        {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {1, 2, 3, 4};

    cout << obj.subsequencePairCount(nums) << endl;

    return 0;
}

/*

===========================================================
3336. Find the Number of Subsequences With Equal GCD
===========================================================

-----------------------------------------------------------
Problem Statement
-----------------------------------------------------------

Given an integer array nums.

Choose two disjoint non-empty subsequences A and B.

Count the number of ways such that

        gcd(A) == gcd(B)

Return the answer modulo 1e9+7.

-----------------------------------------------------------
Example
-----------------------------------------------------------

Input:
nums = [1,2,3]

Output:
2

-----------------------------------------------------------
Brute Force Approach
-----------------------------------------------------------

Idea
----

Each element has three choices

1. Put into first subsequence.
2. Put into second subsequence.
3. Ignore.

Generate every assignment.

For every assignment

- Build both subsequences.
- Check both are non-empty.
- Compute GCD.
- If equal, increment answer.

Pseudo Code
------------

answer = 0

DFS(index)

if index == n

    if both subsequences non-empty

        if gcd(A)==gcd(B)

            answer++

    return

Ignore current

Put in first

Put in second

Complete Brute Force Code
-------------------------

class Solution {
public:

int ans=0;

void dfs(int idx,
         vector<int>& nums,
         vector<int>& A,
         vector<int>& B){

    if(idx==nums.size()){

        if(A.empty() || B.empty())
            return;

        int g1=0,g2=0;

        for(int x:A) g1=gcd(g1,x);
        for(int x:B) g2=gcd(g2,x);

        if(g1==g2)
            ans++;

        return;
    }

    dfs(idx+1,nums,A,B);

    A.push_back(nums[idx]);
    dfs(idx+1,nums,A,B);
    A.pop_back();

    B.push_back(nums[idx]);
    dfs(idx+1,nums,A,B);
    B.pop_back();
}

};

Time Complexity

O(3^N * N)

Space Complexity

O(N)

-----------------------------------------------------------
Optimal Approach
-----------------------------------------------------------

Observation
------------

Actual elements of subsequence are NOT important.

Only current GCD matters.

Future element only changes

gcd(oldGCD,newValue)

Hence state can be compressed.

-----------------------------------------------------------

Intuition
---------

DP State

dp[g1][g2]

means

Current GCD of first subsequence = g1

Current GCD of second subsequence = g2

Initially

dp[0][0]=1

where GCD=0 means empty subsequence.

Every element has three choices

1 Ignore

2 Put into first

3 Put into second

Transitions

Ignore

(g1,g2)

Put in first

(gcd(g1,x),g2)

Put in second

(g1,gcd(g2,x))

Finally

Answer

sum(dp[g][g])

for every g>0

-----------------------------------------------------------
Pseudo Code
-----------------------------------------------------------

dp[0][0]=1

for every number x

    ndp = dp

    for every state(g1,g2)

        Ignore

        Put into first

        Put into second

    dp=ndp

answer=0

for g=1...maxValue

    answer+=dp[g][g]

-----------------------------------------------------------
Complete Optimal Code
-----------------------------------------------------------

class Solution {
public:

static const int MOD=1e9+7;

int subsequencePairCount(vector<int>& nums){

    int mx=*max_element(nums.begin(),nums.end());

    vector<vector<int>> gcdTable(mx+1,
                                 vector<int>(mx+1));

    for(int i=0;i<=mx;i++)
        for(int j=0;j<=mx;j++)
            gcdTable[i][j]=(i==0)?j:
                            (j==0)?i:
                            gcd(i,j);

    vector<vector<int>> dp(mx+1,
                           vector<int>(mx+1,0));

    dp[0][0]=1;

    for(int x:nums){

        auto ndp=dp;

        for(int g1=0;g1<=mx;g1++){

            for(int g2=0;g2<=mx;g2++){

                if(dp[g1][g2]==0)
                    continue;

                int val=dp[g1][g2];

                int ng1=gcdTable[g1][x];
                ndp[ng1][g2]=(ndp[ng1][g2]+val)%MOD;

                int ng2=gcdTable[g2][x];
                ndp[g1][ng2]=(ndp[g1][ng2]+val)%MOD;
            }
        }

        dp=move(ndp);
    }

    long long ans=0;

    for(int g=1;g<=mx;g++)
        ans=(ans+dp[g][g])%MOD;

    return ans;
}

};

-----------------------------------------------------------
Time Complexity
-----------------------------------------------------------

Let

N = nums.size()

M = maximum value in nums

Time

O(N * M^2)

(Precomputed GCD table removes repeated gcd calculations.)

-----------------------------------------------------------
Space Complexity
-----------------------------------------------------------

O(M^2)

-----------------------------------------------------------
Dry Run
-----------------------------------------------------------

nums = [2,4]

Initially

dp[0][0]=1

Process 2

States become

(0,0)

(2,0)

(0,2)

Process 4

From

(2,0)

Ignore

(2,0)

Put First

gcd(2,4)=2

(2,0)

Put Second

(2,4)

Continue similarly.

Finally sum all

dp[g][g]

where g>0.

-----------------------------------------------------------
Interview Notes
-----------------------------------------------------------

Pattern

✔ DP on State Compression
✔ GCD DP
✔ Subsequences
✔ State Transition

-----------------------------------------------------------

Key Observation

Only current GCD matters.

Entire subsequence is unnecessary.

-----------------------------------------------------------

Common Mistakes

1. Forgetting subsequences must be disjoint.

2. Forgetting empty subsequence uses GCD = 0.

3. Including dp[0][0] in final answer.

4. Updating DP in-place instead of using next DP.

5. Not taking modulo.

-----------------------------------------------------------

When to use this approach

Whenever

• Future state depends only on current GCD.

• GCD values are bounded by maximum array value.

• Subsequences are involved but only aggregate GCD matters.

This is a classic "DP on compressed mathematical state" problem.

===========================================================

*/
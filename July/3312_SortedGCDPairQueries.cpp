#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> gcdValues(vector<int> &nums, vector<long long> &queries)
    {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);
        for (int x : nums)
            freq[x]++;

        vector<long long> gcdCnt(mx + 1, 0);

        // Inclusion-Exclusion on multiples
        for (int g = mx; g >= 1; g--)
        {
            long long cnt = 0;
            for (int m = g; m <= mx; m += g)
                cnt += freq[m];

            gcdCnt[g] = cnt * (cnt - 1) / 2;

            for (int m = 2 * g; m <= mx; m += g)
                gcdCnt[g] -= gcdCnt[m];
        }

        vector<long long> prefix(mx + 1, 0);
        for (int i = 1; i <= mx; i++)
            prefix[i] = prefix[i - 1] + gcdCnt[i];

        vector<int> ans;
        for (long long q : queries)
        {
            int g = upper_bound(prefix.begin(), prefix.end(), q) - prefix.begin();
            ans.push_back(g);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {2, 3, 4};
    vector<long long> queries = {0, 2, 2};

    vector<int> ans = obj.gcdValues(nums, queries);

    for (int x : ans)
        cout << x << " ";
    cout << "\n";

    return 0;
}

/*

==========================
Problem Statement
==========================

LeetCode 3312 - Sorted GCD Pair Queries

Given an integer array nums.

Consider every pair (i,j), i<j.
Compute gcd(nums[i], nums[j]) for every pair.

Sort all these GCD values.

For every query q, return the q-th element (0-indexed) of the sorted GCD array.

--------------------------------------------------

Example

Input:
nums = [2,3,4]
queries = [0,2,2]

Pairs:
(2,3)=1
(2,4)=2
(3,4)=1

Sorted:
[1,1,2]

Answer:
[1,2,2]

==================================================
Brute Force Approach
==================================================

Idea

Generate every pair.

Compute gcd.

Store all gcd values.

Sort them.

Answer each query directly.

Pseudo Code

vector<int> g;

for every i
    for every j>i
        g.push_back(gcd(nums[i],nums[j]))

sort(g)

for query
    answer=g[query]

--------------------------------------------------
Complete Brute Force Code

vector<int> gcdValues(vector<int>& nums, vector<long long>& queries){

    vector<int> g;

    int n=nums.size();

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            g.push_back(__gcd(nums[i],nums[j]));
        }
    }

    sort(g.begin(),g.end());

    vector<int> ans;

    for(long long q:queries)
        ans.push_back(g[q]);

    return ans;
}

--------------------------------------------------

Time Complexity

Pair generation : O(N²)

Sorting : O(N² log N)

Overall :
O(N² log N)

Space :
O(N²)

Not possible for N=1e5.

==================================================
Optimal Approach
==================================================

Observation

Instead of generating every pair,

Count how many pairs have GCD exactly = g.

For every divisor g

Count how many numbers are divisible by g.

Suppose there are cnt such numbers.

Then

C(cnt,2)

pairs have GCD multiple of g.

Using Inclusion-Exclusion,

subtract counts of all multiples of g.

This gives

pairs whose GCD is exactly g.

After knowing count for every GCD,

construct prefix sums.

Binary search each query.

--------------------------------------------------

Intuition

This is a classic Number Theory + Inclusion Exclusion problem.

Process GCD values from largest to smallest.

Large GCDs are already known.

Smaller GCDs subtract larger multiples.

Finally,

prefix[g]
=
number of pairs having gcd <= g.

Binary search answers every query.

--------------------------------------------------

Pseudo Code

Count frequency of every value

for g=maxValue down to 1

    cnt=0

    for every multiple of g
        cnt+=frequency

    gcdCnt[g]=C(cnt,2)

    subtract gcdCnt of multiples

Build prefix sums

For each query

    upper_bound(prefix,query)

--------------------------------------------------

Complete Optimal Code

class Solution {
public:

vector<int> gcdValues(vector<int>& nums,
                      vector<long long>& queries){

    int mx=*max_element(nums.begin(),nums.end());

    vector<int> freq(mx+1);

    for(int x:nums)
        freq[x]++;

    vector<long long> gcdCnt(mx+1);

    for(int g=mx;g>=1;g--){

        long long cnt=0;

        for(int m=g;m<=mx;m+=g)
            cnt+=freq[m];

        gcdCnt[g]=cnt*(cnt-1)/2;

        for(int m=2*g;m<=mx;m+=g)
            gcdCnt[g]-=gcdCnt[m];
    }

    vector<long long> prefix(mx+1);

    for(int i=1;i<=mx;i++)
        prefix[i]=prefix[i-1]+gcdCnt[i];

    vector<int> ans;

    for(long long q:queries)
        ans.push_back(
            upper_bound(prefix.begin(),
                        prefix.end(),
                        q)-prefix.begin());

    return ans;
}

};

--------------------------------------------------

Time Complexity

Frequency array:
O(N)

Counting multiples:
O(M log M)

Binary search:
O(Q log M)

Overall:

O(N + M log M + Q log M)

where

M = maximum element (≤50000)

Space Complexity

O(M)

==================================================
Dry Run
==================================================

nums = [2,3,4]

Frequency

2->1

3->1

4->1

-----------------

g=4

cnt=1

pairs=0

-----------------

g=3

cnt=1

pairs=0

-----------------

g=2

Numbers divisible

2,4

cnt=2

pairs=1

No larger multiples contribute

gcdCnt[2]=1

-----------------

g=1

All numbers divisible

cnt=3

pairs=3

Subtract gcdCnt[2]=1

Result

gcdCnt[1]=2

-----------------

Counts

GCD 1 ->2

GCD 2 ->1

Prefix

0

2

3

Queries

0

upper_bound=1

Answer=1

2

upper_bound=2

Answer=2

Result

[1,2,2]

==================================================
Interview Notes
==================================================

Pattern

Number Theory

Frequency Counting

Inclusion-Exclusion

Binary Search

Prefix Sum

--------------------------------------------------

Key Observation

Never generate all pairs.

Count pairs for every possible GCD.

--------------------------------------------------

Common Mistakes

1. Forget subtracting multiples.

2. Using int instead of long long.

3. Using lower_bound instead of upper_bound.

4. Incorrect combination formula.

--------------------------------------------------

When to use this approach

Whenever

• Need count of pairs having exact divisor/GCD

• Constraints make O(N²) impossible

• Maximum value is reasonably small (≈50000)

• Inclusion-Exclusion on multiples is applicable.

*/
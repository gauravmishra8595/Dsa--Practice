#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int mx = (*max_element(nums.begin(), nums.end())) << 1;

        vector<bool> pairXor(mx, false);

        for (int a : nums) {
            for (int b : nums) {
                pairXor[a ^ b] = true;
            }
        }

        vector<bool> ans(mx, false);

        for (int x = 0; x < mx; x++) {
            if (!pairXor[x]) continue;
            for (int c : nums) {
                ans[x ^ c] = true;
            }
        }

        return count(ans.begin(), ans.end(), true);
    }
};

int main() {
    Solution obj;

    vector<int> nums = {1, 3};

    cout << obj.uniqueXorTriplets(nums) << "\n";

    return 0;
}

/*

==========================
Problem Statement
==========================

You are given an integer array nums.

A XOR triplet is defined as:

nums[i] XOR nums[j] XOR nums[k]

where i <= j <= k.

Return the number of distinct XOR values that can be obtained from all valid triplets.

--------------------------------------------------
Example
--------------------------------------------------

Input:
nums = [1,3]

Output:
2

Explanation:

Possible XOR values:
1
3

Unique values = {1,3}

Answer = 2


==================================================
Brute Force Approach
==================================================

Idea
-----

Generate every valid triplet (i,j,k), compute XOR,
insert into a set and return set size.

Pseudo Code
-----------

set

for i
    for j=i
        for k=j
            set.insert(nums[i]^nums[j]^nums[k])

return set.size()

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        unordered_set<int> st;

        int n=nums.size();

        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
                for(int k=j;k<n;k++)
                    st.insert(nums[i]^nums[j]^nums[k]);

        return st.size();
    }
};

Time Complexity:
O(N^3)

Space Complexity:
O(answer)


==================================================
Optimal Approach
==================================================

Observation
-----------

Since indices can repeat (i<=j<=k),

choosing triplets with repeated indices is equivalent
to choosing ANY three array values with replacement.

Also,

(a XOR b XOR c)
=
((a XOR b) XOR c)

So first compute all possible pair XORs,
then XOR each pair result with every array element.

Maximum value <=1500.

Hence maximum XOR value < 2*1500 = 3000.

Only a boolean array of size about 3000 is required.

Intuition
---------

Instead of checking O(N^3) triplets,

1. Compute every possible pair XOR.
2. Store which XOR values are possible.
3. Combine every possible pair XOR with each element.
4. Count distinct results.

Pseudo Code
-----------

mx = 2 * max(nums)

pairXor[mx]

for every a
    for every b
        pairXor[a XOR b]=true

answer[mx]

for every xorValue
    if pairXor[xorValue]
        for every c
            answer[xorValue XOR c]=true

count true values

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        int mx = (*max_element(nums.begin(), nums.end())) << 1;

        vector<bool> pairXor(mx,false);

        for(int a:nums)
            for(int b:nums)
                pairXor[a^b]=true;

        vector<bool> ans(mx,false);

        for(int x=0;x<mx;x++)
            if(pairXor[x])
                for(int c:nums)
                    ans[x^c]=true;

        return count(ans.begin(),ans.end(),true);
    }
};

Time Complexity
---------------

Pair XOR generation:
O(N²)

Combine with third element:
O(M*N)

Overall:

O(N² + M*N)

where

M = 2 * max(nums)

Since max(nums)<=1500,

M≈3000

Space Complexity
----------------

O(M)


==================================================
Dry Run
==================================================

nums = [1,3]

Step 1

Pair XORs

1^1=0
1^3=2
3^1=2
3^3=0

pairXor:

0=true
2=true

Step 2

Use pair XOR 0

0^1=1

0^3=3

Use pair XOR 2

2^1=3

2^3=1

Distinct:

1
3

Answer = 2


==================================================
Interview Notes
==================================================

Pattern
-------

Bit Manipulation
+
Enumeration
+
Precomputation

Key Observation
---------------

a XOR b XOR c

can be broken into

(a XOR b) XOR c

allowing reduction from cubic enumeration.

Common Mistakes
---------------

1. Using O(N³).

2. Forgetting repeated indices are allowed.

3. Using unordered_set for every triplet instead of
precomputing pair XORs.

4. Choosing wrong maximum XOR array size.

When to use this approach
-------------------------

Whenever an expression involves

A op B op C

where the operation is associative
(XOR, OR, AND in some problems),

precompute pair results first and combine later.

*/
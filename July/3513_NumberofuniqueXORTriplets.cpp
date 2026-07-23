#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2) return n;

        int ans = 1;
        while (ans <= n) ans <<= 1;
        return ans;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {3, 1, 2};

    cout << obj.uniqueXorTriplets(nums) << "\n";

    return 0;
}

/*

==========================
Problem Statement
==========================

You are given an integer array nums of length n, where nums is a permutation
of numbers from 1 to n.

A XOR triplet is defined as:

    nums[i] XOR nums[j] XOR nums[k]

where

    i <= j <= k

Return the number of distinct XOR values obtainable from all possible triplets.

--------------------------------------------------
Example
--------------------------------------------------

Input:
nums = [3,1,2]

Output:
4

Explanation:

Possible unique XOR values:
0,1,2,3

Hence answer = 4.

==================================================
Brute Force Approach
==================================================

Idea
-----

Generate every possible triplet (i,j,k), compute XOR,
store the result inside a hash set.

Finally return the set size.

Pseudo Code
-----------

unordered_set st

for i = 0 to n-1
    for j = i to n-1
        for k = j to n-1
            st.insert(nums[i]^nums[j]^nums[k])

return st.size()

Complete Brute Force Code
-------------------------

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        unordered_set<int> st;
        int n = nums.size();

        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
                for(int k=j;k<n;k++)
                    st.insert(nums[i]^nums[j]^nums[k]);

        return st.size();
    }
};

Time Complexity
---------------

O(n^3)

Space Complexity
----------------

O(number of distinct XOR values)

==================================================
Optimal Approach
==================================================

Observation
-----------

The array is a permutation of numbers 1...n.

Repeating an element is allowed because

i <= j <= k.

Important XOR facts:

a ^ a ^ a = a

a ^ a ^ b = b

For n >= 3,
all values from

0 ... (2^k - 1)

can be generated,
where

2^k

is the first power of two strictly greater than n.

Therefore,

Answer =
next power of two greater than n

Special cases:

n = 1 -> 1
n = 2 -> 2

Intuition
---------

The permutation already contains every integer from 1 to n.

Three-number XOR combinations span the entire binary space
covered by the highest bit of n.

Thus we never actually need to simulate triplets.

Pseudo Code
-----------

n = nums.size()

if n <= 2
    return n

ans = 1

while ans <= n
    ans <<= 1

return ans

Complete Optimal Code
---------------------

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        int n = nums.size();

        if(n<=2)
            return n;

        int ans=1;

        while(ans<=n)
            ans<<=1;

        return ans;
    }
};

Time Complexity
---------------

O(log n)

Space Complexity
----------------

O(1)

==================================================
Dry Run
==================================================

nums = [3,1,2]

n = 3

n > 2

Find next power of two:

1
2
4

4 > 3

Return 4

Answer = 4

==================================================
Interview Notes
==================================================

Pattern
-------

Bit Manipulation
Mathematical Observation

Key Observation
---------------

For n >= 3, every XOR value in

[0, nextPowerOfTwo(n)-1]

is achievable.

Hence answer depends only on n,
not on the permutation order.

Common Mistakes
---------------

1. Trying O(n^3) enumeration.

2. Forgetting repeated indices are allowed.

3. Returning highest power of two <= n
   instead of strictly greater than n.

4. Missing special cases n=1 and n=2.

When to use this approach
-------------------------

Whenever a problem asks about XOR values over permutations
and only the count of reachable XOR states is required.

Recognize algebraic properties instead of simulation.

*/
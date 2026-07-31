#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> grayCode(int n)
    {
        vector<int> ans;
        int total = 1 << n;

        for (int i = 0; i < total; i++)
        {
            ans.push_back(i ^ (i >> 1));
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    int n = 2;
    vector<int> ans = obj.grayCode(n);

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*

======================== Problem Statement ========================

89. Gray Code

An n-bit gray code sequence is a sequence of 2^n integers where:

1. Every integer is in the inclusive range [0, 2^n - 1].
2. The first integer is 0.
3. An integer appears no more than once.
4. The binary representations of every pair of adjacent integers differ by exactly one bit.
5. The binary representations of the first and last integers also differ by exactly one bit.

Return any valid n-bit Gray code sequence.

============================== Example ==============================

Input:
n = 2

Output:
[0,1,3,2]

Binary Representation:
0 -> 00
1 -> 01
3 -> 11
2 -> 10

Adjacent values differ by exactly one bit.

====================================================================
                     BRUTE FORCE APPROACH
====================================================================

Idea

Generate all numbers from 0 to (2^n - 1) and try every permutation.
Check whether every adjacent pair differs by exactly one bit.

Since there are (2^n)! permutations, this approach is infeasible.

-------------------------- Pseudo Code --------------------------

Generate all permutations

For each permutation:
    Check:
        First element == 0
        Adjacent numbers differ by one bit
        First and last also differ by one bit

Return first valid permutation

---------------- Complete Brute Force Code ----------------

class Solution {
public:
    vector<int> grayCode(int n) {
        // Generate all permutations
        // Validate each permutation
        // Return first valid sequence

        // Not feasible because factorial complexity.
    }
};

---------------- Time Complexity ----------------

O((2^n)!)

---------------- Space Complexity ----------------

O(2^n)

====================================================================
                     OPTIMAL APPROACH
====================================================================

Observation

Gray Code has a direct mathematical formula.

Gray(i) = i ^ (i >> 1)

where ^ is XOR.

This guarantees every consecutive value differs by exactly one bit.

--------------------------- Intuition ---------------------------

Iterate from 0 to (2^n - 1).

For each number i:
    Compute Gray Code using:
        i ^ (i >> 1)

Store the result.

No recursion or backtracking is needed.

------------------------- Pseudo Code -------------------------

total = 2^n

For i = 0 to total-1
    ans.push_back(i ^ (i >> 1))

Return ans

---------------- Complete Optimal Code ----------------

class Solution {
public:
    vector<int> grayCode(int n) {

        vector<int> ans;

        int total = 1 << n;

        for(int i = 0; i < total; i++)
            ans.push_back(i ^ (i >> 1));

        return ans;
    }
};

---------------- Time Complexity ----------------

O(2^n)

---------------- Space Complexity ----------------

O(2^n)

(Output array)

====================================================================
                        DRY RUN
====================================================================

n = 2

total = 4

i = 0

0 ^ 0 = 0

ans = [0]

--------------------------------

i = 1

1 ^ 0 = 1

ans = [0,1]

--------------------------------

i = 2

10 ^ 01 = 11

3

ans = [0,1,3]

--------------------------------

i = 3

11 ^ 01 = 10

2

ans = [0,1,3,2]

Answer = [0,1,3,2]

====================================================================
                      INTERVIEW NOTES
====================================================================

Pattern

Bit Manipulation

Key Observation

Gray Code can be generated directly using:

Gray(i) = i ^ (i >> 1)

Common Mistakes

1. Forgetting parentheses:
   i ^ (i >> 1)

2. Using left shift instead of right shift.

3. Trying recursion/backtracking unnecessarily.

4. Returning binary strings instead of integers.

When to use this approach

Whenever Gray Code sequence is required.
This formula is the standard optimal solution used in interviews and
competitive programming.

====================================================================

*/
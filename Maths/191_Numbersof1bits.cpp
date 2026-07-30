#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int hammingWeight(uint32_t n)
    {
        int cnt = 0;
        while (n)
        {
            n &= (n - 1); // Remove the rightmost set bit
            cnt++;
        }
        return cnt;
    }
};

int main()
{
    Solution obj;

    uint32_t n = 11;                      // Binary: 1011
    cout << obj.hammingWeight(n) << endl; // Output: 3

    return 0;
}

/*

========================================
LeetCode 191. Number of 1 Bits
========================================

Problem Statement:
Given a positive integer n, write a function that returns the number of
'1' bits (set bits) in its binary representation (also known as the
Hamming Weight).

--------------------------------------------------
Example
--------------------------------------------------

Input:
n = 11

Binary:
1011

Output:
3

Explanation:
There are three set bits.

==================================================
Brute Force Approach
==================================================

Idea:
Traverse all 32 bits one by one.
Check whether the last bit is 1.
Then right shift the number.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

count = 0

while(n > 0)
    if(n & 1)
        count++

    n >>= 1

return count

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;

        while(n){
            cnt += (n & 1);
            n >>= 1;
        }

        return cnt;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(32) ≈ O(1)

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Optimal Approach
==================================================

Observation:
For any number,

n & (n-1)

removes the rightmost set bit.

Example:

1011000
1010111
-------
1010000

One set bit disappears.

--------------------------------------------------
Intuition
--------------------------------------------------

Instead of checking every bit,
remove one set bit in every iteration.

Number of iterations
=
Number of set bits.

--------------------------------------------------
Pseudo Code
--------------------------------------------------

count = 0

while(n)
    n = n & (n-1)
    count++

return count

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;

        while(n){
            n &= (n-1);
            cnt++;
        }

        return cnt;
    }
};

--------------------------------------------------
Time Complexity
--------------------------------------------------

O(Number of Set Bits)

Worst Case:
O(32)

Best Case:
O(1)

--------------------------------------------------
Space Complexity
--------------------------------------------------

O(1)

==================================================
Dry Run
==================================================

Input:
n = 11

Binary:
1011

Iteration 1

1011

1010

AND

1010

Count = 1

Iteration 2

1010

1001

AND

1000

Count = 2

Iteration 3

1000

0111

AND

0000

Count = 3

Loop ends.

Answer = 3

==================================================
Interview Notes
==================================================

Pattern:
- Bit Manipulation
- Brian Kernighan Algorithm

Key Observation:
n & (n-1) removes exactly one set bit.

Common Mistakes:
- Using signed int instead of uint32_t.
- Forgetting that worst case is still constant (32 bits).
- Confusing with counting total bits.

When to use this approach:
- Counting set bits.
- Bitmask problems.
- Hamming distance.
- Power of Two related problems.
- Efficient bit manipulation questions.

*/
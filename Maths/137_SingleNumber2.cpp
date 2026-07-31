#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ones = 0, twos = 0;

        for (int num : nums)
        {
            ones = (ones ^ num) & (~twos);
            twos = (twos ^ num) & (~ones);
        }

        return ones;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {2, 2, 3, 2};
    cout << obj.singleNumber(nums) << endl;

    return 0;
}

/*

======================== Problem Statement ========================

137. Single Number II

Given an integer array nums where every element appears exactly
three times except for one element, which appears exactly once.

Find and return the single element.

You must solve it in linear time and constant extra space.

============================== Example ==============================

Input:
nums = [2,2,3,2]

Output:
3

Explanation:
2 appears three times.
3 appears once.

====================================================================
                     BRUTE FORCE APPROACH
====================================================================

Idea

Count the frequency of every number using a hash map.
The number with frequency 1 is the answer.

-------------------------- Pseudo Code --------------------------

Create unordered_map<int,int> freq

For every number
    freq[number]++

For every (number,count)
    if count == 1
        return number

---------------- Complete Brute Force Code ----------------

class Solution {
public:
    int singleNumber(vector<int>& nums) {

        unordered_map<int,int> freq;

        for(int x : nums)
            freq[x]++;

        for(auto &it : freq)
            if(it.second == 1)
                return it.first;

        return -1;
    }
};

---------------- Time Complexity ----------------

O(N)

---------------- Space Complexity ----------------

O(N)

====================================================================
                     OPTIMAL APPROACH
====================================================================

Observation

Each bit of every number appears either:

- 3 times
- or 3k + 1 times (for the unique number)

Instead of counting every bit separately, maintain two bit masks:

ones → bits that have appeared once.
twos → bits that have appeared twice.

When a bit appears the third time, remove it from both masks.

--------------------------- Intuition ---------------------------

For every incoming number:

1. Toggle bits in ones.
2. Remove bits already present in twos.
3. Toggle bits in twos.
4. Remove bits already present in ones.

Thus every bit cycles:

0 occurrence
↓

ones

↓

twos

↓

removed

Exactly what we need for modulo 3 counting.

------------------------- Pseudo Code -------------------------

ones = 0
twos = 0

For every number

    ones = (ones XOR num) AND (~twos)

    twos = (twos XOR num) AND (~ones)

Return ones

---------------- Complete Optimal Code ----------------

class Solution {
public:
    int singleNumber(vector<int>& nums) {

        int ones = 0;
        int twos = 0;

        for(int num : nums){

            ones = (ones ^ num) & (~twos);

            twos = (twos ^ num) & (~ones);
        }

        return ones;
    }
};

---------------- Time Complexity ----------------

O(N)

---------------- Space Complexity ----------------

O(1)

====================================================================
                        DRY RUN
====================================================================

nums = [2,2,3,2]

Initial

ones = 0

twos = 0

------------------------------------------------

num = 2

ones = 2

twos = 0

------------------------------------------------

num = 2

ones = 0

twos = 2

------------------------------------------------

num = 3

ones = 1

twos = 0

(Binary:
3 = 11
2 = 10
Remaining bit pattern corresponds correctly.)

------------------------------------------------

num = 2

ones = 3

twos = 0

Answer = 3

====================================================================
                      INTERVIEW NOTES
====================================================================

Pattern

Bit Manipulation

Finite State Machine (FSM)

Key Observation

Each bit can have only three meaningful states:

0 occurrence

↓

1 occurrence (ones)

↓

2 occurrences (twos)

↓

Reset after 3rd occurrence

Common Mistakes

1. Updating twos before updating ones.

2. Forgetting to mask using ~twos and ~ones.

3. Using logical NOT (!) instead of bitwise NOT (~).

4. Trying XOR directly (works only when elements appear twice).

When to use this approach

Whenever:

- Every element appears k times except one.
- Need O(1) extra space.
- Bit counting / modulo arithmetic is involved.

====================================================================

*/
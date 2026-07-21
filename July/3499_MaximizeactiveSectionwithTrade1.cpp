#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxActiveSectionsAfterTrade(string s)
    {
        int n = s.size();
        int ones = 0;
        int preZeroBlock = INT_MIN;
        int bestGain = 0;

        int i = 0;
        while (i < n)
        {
            int j = i;
            while (j < n && s[j] == s[i])
                j++;
            int len = j - i;

            if (s[i] == '1')
            {
                ones += len;
            }
            else
            {
                if (preZeroBlock != INT_MIN)
                    bestGain = max(bestGain, preZeroBlock + len);
                preZeroBlock = len;
            }

            i = j;
        }

        return ones + bestGain;
    }
};

int main()
{
    Solution obj;

    string s;
    cin >> s;

    cout << obj.maxActiveSectionsAfterTrade(s) << endl;

    return 0;
}

/*

======================== Problem Statement ========================

LeetCode 3499 - Maximize Active Section with Trade I

You are given a binary string s.

'1' represents an active section.
'0' represents an inactive section.

You may perform at most one trade:

1. Convert one contiguous block of 1's surrounded by 0's into all 0's.
2. Then convert one contiguous block of 0's surrounded by 1's into all 1's.

While checking surrounded blocks, imagine the string becomes:

t = '1' + s + '1'

The added boundary 1's are only for deciding valid blocks and are NOT counted.

Return the maximum possible number of active sections.

===================================================================

Example

Input:
01010

Output:
4

Explanation:

Initial ones = 2

Choose middle pattern:
010

After trade:
11110

Answer = 4

===================================================================

Brute Force Approach

Idea

Generate every possible removable 1-block.

For every such choice:
    Simulate turning it into 0's.
    Find every valid 0-block.
    Turn it into 1's.
    Count total ones.

Take maximum answer.

Pseudo Code

for every removable 1-block
    make copy
    flip chosen block
    for every valid 0-block
        flip block
        count ones
        update answer

Complete Brute Force Code

// class Solution {
// public:
//     int maxActiveSectionsAfterTrade(string s) {
//
//         int ans = count(s.begin(), s.end(), '1');
//
//         // Enumerate every possible trade
//         // Simulate changes
//         // Count ones
//
//         return ans;
//     }
// };

Time Complexity

O(N^2)

(or worse with repeated simulations)

Space Complexity

O(N)

===================================================================

Optimal Approach

Observation

Suppose we remove one surrounded 1-block.

The two neighboring zero blocks merge into one larger zero block.

That merged zero block is exactly the block that becomes all 1's.

Net gain

= mergedZeroLength

because

loss = removed one-block

gain = removed one-block + left zeros + right zeros

After cancellation,

extra ones added = leftZero + rightZero

Therefore,

Answer

= original number of ones
+ maximum(sum of two adjacent zero blocks)

We only need to scan runs once.

-------------------------------------------------------------------

Intuition

Run-Length Encoding naturally separates consecutive blocks.

Whenever we encounter a zero block,

previousZero + currentZero

represents the merged zero block after deleting the one block between them.

Maintain

preZero = previous zero block length

best = maximum(preZero + currentZero)

Finally

answer = totalOnes + best

-------------------------------------------------------------------

Pseudo Code

count total ones

best = 0
pre = invalid

scan runs

if run is ones
    add length to totalOnes

else
    if pre exists
        best = max(best, pre + currentLength)
    pre = currentLength

return totalOnes + best

-------------------------------------------------------------------

Complete Optimal Code

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {

        int ones = 0;
        int pre = INT_MIN;
        int best = 0;

        int i = 0;

        while(i < s.size()){

            int j = i;

            while(j < s.size() && s[j]==s[i])
                j++;

            int len = j-i;

            if(s[i]=='1')
                ones += len;
            else{
                if(pre!=INT_MIN)
                    best = max(best, pre+len);
                pre = len;
            }

            i = j;
        }

        return ones + best;
    }
};

Time Complexity

O(N)

Space Complexity

O(1)

===================================================================

Dry Run

Input

01010

Runs

0(1)
1(1)
0(1)
1(1)
0(1)

total ones = 2

Zero blocks

First
pre = 1

Second

best = 1+1 = 2

pre = 1

Third

best = max(2,1+1)=2

Answer

2 + 2 = 4

===================================================================

Interview Notes

Pattern

Run Length Encoding (RLE)
Greedy
String Traversal

Key Observation

Removing one surrounded 1-block merges exactly two adjacent zero blocks.

Only adjacent zero blocks matter.

Common Mistakes

1. Actually simulating trades.

2. Forgetting virtual boundary 1's.

3. Considering non-adjacent zero blocks.

4. Using O(N^2) simulation.

When to use this approach

Whenever a binary string problem depends only on consecutive groups.

Run-length encoding often converts difficult simulations into simple arithmetic.

===================================================================

*/
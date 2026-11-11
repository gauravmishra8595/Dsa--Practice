#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {
        long long common = min(need1, need2);
        long long remaining1 = need1 - common;
        long long remaining2 = need2 - common;
        long long ans = common * min(costBoth, cost1 + cost2);
        ans += remaining1 * min(cost1, costBoth);
        ans += remaining2 * min(cost2, costBoth);
        return ans;
    }
};
int main() {
    Solution sol;
    int cost1 = 3;
    int cost2 = 2;
    int costBoth = 1;
    int need1 = 3;
    int need2 = 2;

    cout << sol.minimumCost(cost1, cost2, costBoth, need1, need2)
         << '\n';

    return 0;
}

/*
============================================================
        LEETCODE 3789 - MINIMUM COST TO ACQUIRE REQUIRED ITEMS
============================================================

PROBLEM STATEMENT:
------------------
We are given five integers:
cost1, cost2, costBoth, need1, need2.

There are three types of items:

1. Type 1:
   Costs cost1 and contributes 1 unit to requirement 1.

2. Type 2:
   Costs cost2 and contributes 1 unit to requirement 2.

3. Type 3:
   Costs costBoth and contributes 1 unit to BOTH requirements.

We need to purchase items such that:
- Total contribution to requirement 1 >= need1.
- Total contribution to requirement 2 >= need2.

Return the minimum possible total cost.

EXAMPLE:
--------
Input:
cost1 = 3
cost2 = 2
costBoth = 1
need1 = 3
need2 = 2

Output:
3

Explanation:
Purchase 3 Type-3 items.

Requirement 1 = 3
Requirement 2 = 3

Total Cost = 3 * 1 = 3.


============================================================
BRUTE FORCE APPROACH:
============================================================

IDEA:
-----
Try every possible number of Type-3 items.

If we purchase x Type-3 items:
- Remaining requirement 1 = max(0, need1 - x)
- Remaining requirement 2 = max(0, need2 - x)

Calculate the total cost for every possible x and
take the minimum.

Since buying more than max(need1, need2) Type-3 items
cannot improve the answer, we only need to check:

0 <= x <= max(need1, need2)


PSEUDO CODE:
------------
ans = infinity

for x = 0 to max(need1, need2):

    remaining1 = max(0, need1 - x)
    remaining2 = max(0, need2 - x)

    cost = x * costBoth
         + remaining1 * cost1
         + remaining2 * cost2

    ans = min(ans, cost)

return ans


COMPLETE BRUTE FORCE CODE:
--------------------------
class Solution {
public:
    long long minimumCost(int cost1, int cost2,
                          int costBoth, int need1, int need2) {

        long long ans = LLONG_MAX;

        for (long long x = 0;
             x <= max(need1, need2); x++) {

            long long remaining1 = max(0LL, need1 - x);
            long long remaining2 = max(0LL, need2 - x);

            long long cost = x * costBoth
                           + remaining1 * cost1
                           + remaining2 * cost2;

            ans = min(ans, cost);
        }

        return ans;
    }
};


TIME COMPLEXITY:
----------------
O(max(need1, need2))

SPACE COMPLEXITY:
-----------------
O(1)

NOTE:
-----
This approach is too slow because need1 and need2 can
be as large as 10^9.


============================================================
OPTIMAL APPROACH:
============================================================

OBSERVATION:
------------
A Type-3 item satisfies BOTH requirements simultaneously.

There are two important situations:

1. When both requirements need an item:
   Compare costBoth with cost1 + cost2.

2. When only one requirement needs an item:
   Compare the corresponding individual item cost with
   costBoth.

INTUITION:
----------
First, satisfy the common requirement:

common = min(need1, need2)

For every common unit, we have two choices:

Option 1:
Buy one Type-3 item.
Cost = costBoth

Option 2:
Buy one Type-1 and one Type-2 item.
Cost = cost1 + cost2

Therefore:

Common cost =
common * min(costBoth, cost1 + cost2)


Now calculate the remaining requirements:

remaining1 = need1 - common
remaining2 = need2 - common

For remaining requirement 1, choose the cheaper option:

min(cost1, costBoth)

For remaining requirement 2, choose the cheaper option:

min(cost2, costBoth)

Final Answer:

ans = common * min(costBoth, cost1 + cost2)

    + remaining1 * min(cost1, costBoth)

    + remaining2 * min(cost2, costBoth)


PSEUDO CODE:
------------
common = min(need1, need2)

remaining1 = need1 - common
remaining2 = need2 - common

ans = common * min(costBoth, cost1 + cost2)

ans += remaining1 * min(cost1, costBoth)

ans += remaining2 * min(cost2, costBoth)

return ans


COMPLETE OPTIMAL CODE:
----------------------
class Solution {
public:
    long long minimumCost(int cost1, int cost2,
                          int costBoth, int need1, int need2) {

        long long common = min(need1, need2);

        long long remaining1 = need1 - common;
        long long remaining2 = need2 - common;

        long long ans = common * min(costBoth, cost1 + cost2);

        ans += remaining1 * min(cost1, costBoth);

        ans += remaining2 * min(cost2, costBoth);

        return ans;
    }
};


TIME COMPLEXITY:
----------------
O(1)

Only a constant number of arithmetic operations.

SPACE COMPLEXITY:
-----------------
O(1)

Only a few variables are used.


============================================================
DRY RUN WITH EXAMPLE:
============================================================

Input:
cost1 = 3
cost2 = 2
costBoth = 1
need1 = 3
need2 = 2

STEP 1: Calculate common requirement

common = min(3, 2)
       = 2

STEP 2: Calculate remaining requirements

remaining1 = 3 - 2 = 1
remaining2 = 2 - 2 = 0

STEP 3: Calculate common cost

common cost = 2 * min(1, 3 + 2)

            = 2 * min(1, 5)

            = 2 * 1

            = 2

STEP 4: Calculate remaining cost

remaining cost 1 = 1 * min(3, 1)
                 = 1

remaining cost 2 = 0 * min(2, 1)
                 = 0

STEP 5: Calculate final answer

ans = 2 + 1 + 0

ans = 3

OUTPUT:
3


============================================================
INTERVIEW NOTES:
============================================================

1. PATTERN:
-----------
Greedy + Mathematics + Cost Optimization.

2. KEY OBSERVATION:
-------------------
A Type-3 item can satisfy both requirements simultaneously.

For common requirements, compare:
costBoth vs cost1 + cost2.

For extra requirements, compare:
costBoth vs individual item cost.

Always choose the cheaper option.

3. COMMON MISTAKES:
-------------------
- Using int for the final answer.
  Maximum cost can exceed the 32-bit integer range.

- Forgetting that Type-3 items can satisfy both requirements.

- Always choosing Type-3 items without comparing costs.

- Using costBoth instead of min(costBoth, cost1 + cost2)
  for common requirements.

- Forgetting that requirements may be zero.

- Using an unnecessary loop when a constant-time greedy
  solution is possible.

4. WHEN TO USE THIS APPROACH:
-----------------------------
Use this pattern when:
- Multiple requirements can be satisfied by one operation.
- Different operations have different costs.
- Some operations satisfy multiple requirements together.
- The goal is to minimize total purchasing or operation cost.
- Independent decisions can be optimized by comparing
  their individual costs.

FINAL TAKEAWAY:
---------------
Identify overlapping requirements first.

Optimize the common part using the cheapest combined option.

Optimize the remaining independent parts separately.

The entire problem is solved in O(1) time and O(1) space.

============================================================
                    END OF NOTES
============================================================
*/
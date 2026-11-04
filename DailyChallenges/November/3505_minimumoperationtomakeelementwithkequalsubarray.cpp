#include<bits/stdc++.h>
using namespace std;

class Solution {
    multiset<int> low, high;
    long long sumLow = 0, sumHigh = 0;

    void rebalance() {
        while (low.size() > high.size() + 1) {
            int val = *low.rbegin();
            low.erase(prev(low.end()));
            sumLow -= val;

            high.insert(val);
            sumHigh += val;
        }

        while (low.size() < high.size()) {
            int val = *high.begin();
            high.erase(high.begin());
            sumHigh -= val;

            low.insert(val);
            sumLow += val;
        }
    }

    void add(int val) {
        if (low.empty() || val <= *low.rbegin()) {
            low.insert(val);
            sumLow += val;
        } else {
            high.insert(val);
            sumHigh += val;
        }

        rebalance();
    }

    void remove(int val) {
        auto it = low.find(val);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= val;
        } else {
            it = high.find(val);
            high.erase(it);
            sumHigh -= val;
        }

        rebalance();
    }

    long long getCost() {
        long long median = *low.rbegin();

        return median * (long long)low.size() - sumLow
             + sumHigh - median * (long long)high.size();
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        // Calculate cost of every sliding window.
        low.clear();
        high.clear();
        sumLow = sumHigh = 0;

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            cost[i - x + 1] = getCost();
        }

        // DP: Minimum cost to select exactly t windows
        // from the first i elements.
        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int t = 1; t <= k; t++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Skip current position.
                curr[i] = curr[i - 1];

                // Select window ending at i - 1.
                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};

int main() {
    Solution sol;

    vector<int> nums = {5, -2, 1, 3, 7, 3, 6, 4, -1};

    int x = 3;
    int k = 2;

    cout << sol.minOperations(nums, x, k) << endl;

    return 0;
}

/*
===========================================================
                 LEETCODE 3505 - HARD
 Minimum Operations to Make Elements Within K Subarrays Equal
===========================================================

PROBLEM STATEMENT:
------------------
Given an integer array nums and two integers x and k.

You can increase or decrease any element by 1 in one operation.

Find the minimum operations required to make at least k
NON-OVERLAPPING subarrays of exactly length x such that
all elements inside each selected subarray are equal.

CONSTRAINTS:
------------
2 <= n <= 10^5
-10^6 <= nums[i] <= 10^6
2 <= x <= n
1 <= k <= 15
k * x <= n

EXAMPLE:
--------
Input:
nums = [5,-2,1,3,7,3,6,4,-1]
x = 3
k = 2

Output:
8

Explanation:

Choose subarray [-2,1,3].
Median = 1.
Operations = 3 + 0 + 2 = 5.

Choose subarray [3,6,4].
Median = 4.
Operations = 1 + 2 + 0 = 3.

Total operations = 5 + 3 = 8.

===========================================================
BRUTE FORCE APPROACH:
===========================================================

IDEA:
-----
1. Generate every possible window of size x.
2. Sort each window.
3. Find its median.
4. Calculate sum of absolute differences from median.
5. Use DP to select k non-overlapping windows.

PSEUDO CODE:
------------
for each starting index i:
    create window of size x
    sort window
    median = window[x/2]

    cost[i] = 0

    for each element:
        cost[i] += abs(element - median)

dp[0][i] = 0

for t = 1 to k:
    for i = 1 to n:
        dp[t][i] = dp[t][i-1]

        if i >= x:
            dp[t][i] = min(
                dp[t][i],
                dp[t-1][i-x] + cost[i-x]
            )

return dp[k][n]

COMPLETE BRUTE FORCE CODE:
--------------------------

class SolutionBrute {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        for (int i = 0; i + x <= n; i++) {
            vector<int> window(
                nums.begin() + i,
                nums.begin() + i + x
            );

            sort(window.begin(), window.end());

            int median = window[x / 2];

            for (int val : window) {
                cost[i] += abs((long long)val - median);
            }
        }

        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1,
            vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int t = 1; t <= k; t++) {
            for (int i = 1; i <= n; i++) {
                dp[t][i] = dp[t][i - 1];

                if (i >= x && dp[t - 1][i - x] != INF) {
                    dp[t][i] = min(
                        dp[t][i],
                        dp[t - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};

TIME COMPLEXITY:
----------------
O(n * x log x + n * k)

Sorting every window takes O(x log x).

SPACE COMPLEXITY:
-----------------
O(n + k*n)

===========================================================
OPTIMAL APPROACH:
===========================================================

OBSERVATION:
------------
The minimum operations required to make all elements of
a subarray equal are obtained by converting every element
to the MEDIAN.

Why?

The median minimizes the sum of absolute differences:

       cost = SUM(abs(nums[i] - median))

INTUITION:
----------
We need to solve two problems efficiently:

1. Calculate the minimum cost of every sliding window.
2. Select k non-overlapping windows with minimum total cost.

PART 1: SLIDING WINDOW MEDIAN
----------------------------

Use two multisets:

LOW:
    Stores the smaller half of elements.
    Contains the median.
    Maintains the sum of its elements.

HIGH:
    Stores the larger half of elements.
    Maintains the sum of its elements.

Maintain these conditions:

1. low.size() == high.size()
   OR
   low.size() == high.size() + 1

2. Every element in low <= every element in high.

3. Median = largest element in low.

COST FORMULA:
-------------

Let median = m.

Left cost:
    m * low.size() - sumLow

Right cost:
    sumHigh - m * high.size()

Total cost:

    cost = m * low.size() - sumLow
         + sumHigh - m * high.size()

Each window insertion/deletion takes O(log x).

PART 2: DYNAMIC PROGRAMMING
---------------------------

Define:

dp[t][i] = Minimum operations required to select
           exactly t non-overlapping windows
           from the first i elements.

TRANSITIONS:

OPTION 1: SKIP CURRENT ELEMENT

    dp[t][i] = dp[t][i-1]

OPTION 2: SELECT WINDOW OF SIZE x

    dp[t][i] = min(
        dp[t][i],
        dp[t-1][i-x] + cost[i-x]
    )

The jump of x positions guarantees that selected
subarrays never overlap.

BASE CASE:

    dp[0][i] = 0

We can optimize space using two DP arrays:

    prev[] = Previous number of selected windows.
    curr[] = Current number of selected windows.

PSEUDO CODE:
------------

Initialize two multisets low and high.

Calculate first window cost.

For every next window:
    Remove outgoing element.
    Insert incoming element.
    Rebalance both multisets.
    Calculate median-based cost.

prev[i] = 0

for t = 1 to k:

    curr[i] = INF

    for i = 1 to n:

        curr[i] = curr[i-1]

        if i >= x:
            curr[i] = min(
                curr[i],
                prev[i-x] + cost[i-x]
            )

    swap(prev, curr)

return prev[n]

COMPLETE OPTIMAL CODE AGAIN:
----------------------------

class Solution {
    multiset<int> low, high;
    long long sumLow = 0, sumHigh = 0;

    void rebalance() {
        while (low.size() > high.size() + 1) {
            int v = *low.rbegin();
            low.erase(prev(low.end()));
            sumLow -= v;

            high.insert(v);
            sumHigh += v;
        }

        while (low.size() < high.size()) {
            int v = *high.begin();
            high.erase(high.begin());
            sumHigh -= v;

            low.insert(v);
            sumLow += v;
        }
    }

    void add(int v) {
        if (low.empty() || v <= *low.rbegin()) {
            low.insert(v);
            sumLow += v;
        } else {
            high.insert(v);
            sumHigh += v;
        }

        rebalance();
    }

    void remove(int v) {
        auto it = low.find(v);

        if (it != low.end()) {
            low.erase(it);
            sumLow -= v;
        } else {
            it = high.find(v);
            high.erase(it);
            sumHigh -= v;
        }

        rebalance();
    }

    long long getCost() {
        long long m = *low.rbegin();

        return m * low.size() - sumLow
             + sumHigh - m * high.size();
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(nums[i-x]);
            add(nums[i]);
            cost[i-x+1] = getCost();
        }

        const long long INF = LLONG_MAX / 4;

        vector<long long> prev(n+1, 0);
        vector<long long> curr(n+1, INF);

        for (int t = 1; t <= k; t++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i-1];

                if (i >= x && prev[i-x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i-x] + cost[i-x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};

TIME COMPLEXITY:
----------------

Sliding Window:
    O(n log x)

Dynamic Programming:
    O(n * k)

TOTAL:
    O(n log x + n * k)

SPACE COMPLEXITY:
-----------------
Window costs = O(n)
DP arrays     = O(n)
Two multisets = O(x)

TOTAL:
    O(n + x) = O(n)

===========================================================
DRY RUN WITH EXAMPLE:
===========================================================

nums = [5,-2,1,3,7,3,6,4,-1]
x = 3
k = 2

STEP 1: CALCULATE WINDOW COSTS

Window             Median       Cost
-------------------------------------
[5,-2,1]              1           7
[-2,1,3]              1           5
[1,3,7]               3           6
[3,7,3]               3           4
[7,3,6]               6           4
[3,6,4]               4           3
[6,4,-1]              4           7

Cost array:

cost = [7,5,6,4,4,3,7]

STEP 2: SELECT ONE WINDOW

Minimum single-window cost:

[3,6,4] = 3

But we need two non-overlapping windows.

STEP 3: SELECT TWO WINDOWS

Consider:

Window 1: [-2,1,3]
Cost = 5
Indices = [1,2,3]

Window 2: [3,6,4]
Cost = 3
Indices = [5,6,7]

They do not overlap.

Total:

    5 + 3 = 8

FINAL OUTPUT:

    8

===========================================================
INTERVIEW NOTES:
===========================================================

PATTERN:
--------
Sliding Window + Two Multisets + Dynamic Programming.

KEY OBSERVATION:
----------------
1. Median minimizes the sum of absolute differences.
2. Two multisets maintain a sliding median efficiently.
3. Maintain sums to calculate median cost in O(1).
4. DP selects exactly k non-overlapping windows.
5. Since k <= 15, O(n*k) DP is efficient.

COMMON MISTAKES:
----------------
1. Using mean instead of median.
2. Sorting every sliding window.
3. Forgetting to update sums during insertion/deletion.
4. Incorrectly balancing the two multisets.
5. Allowing overlapping subarrays.
6. Using int instead of long long for costs.
7. Forgetting to initialize dp[0][i] = 0.
8. Using the wrong DP index: cost[i-x].
9. Returning an answer for fewer than k windows.
10. Forgetting that negative array values are valid.

WHEN TO USE THIS APPROACH:
--------------------------
Use Sliding Window Median when:
    - A window moves one element at a time.
    - You need the median dynamically.
    - You need the sum of absolute deviations.

Use Two Heaps / Two Multisets when:
    - You need dynamic median maintenance.
    - You need insertion and deletion.
    - You need efficient median queries.

Use DP with Non-overlapping Intervals when:
    - You must select exactly k intervals.
    - Each interval has a known cost.
    - Selected intervals cannot overlap.

RELATED CONCEPTS:
-----------------
1. Sliding Window
2. Median of a Data Stream
3. Two Heaps
4. Multiset
5. Dynamic Programming
6. Interval Selection
7. Prefix DP

FINAL TAKEAWAY:
---------------
Sliding Window Median calculates the cost of each window.
Dynamic Programming chooses the best k non-overlapping
windows.

Remember:

    MEDIAN + TWO MULTISETS + DP

===========================================================
*/

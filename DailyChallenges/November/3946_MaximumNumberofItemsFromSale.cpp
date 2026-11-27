#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maximumSaleItems(vector<vector<int>> &items, int budget)
    {
        int n = items.size();
        int minPrice = INT_MAX;

        vector<int> freeCnt(n, 0);

        // Calculate free items for each item.
        for (int i = 0; i < n; i++)
        {
            minPrice = min(minPrice, items[i][1]);

            for (int j = 0; j < n; j++)
            {
                if (i != j && items[j][0] % items[i][0] == 0)
                {
                    freeCnt[i]++;
                }
            }
        }

        // 0/1 Knapsack DP.
        // dp[b] = maximum items obtained from first purchases
        // using at most budget b.
        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++)
        {
            int price = items[i][1];
            int profit = 1 + freeCnt[i];

            for (int b = budget; b >= price; b--)
            {
                dp[b] = max(dp[b], dp[b - price] + profit);
            }
        }

        // Spend the remaining budget on cheapest items.
        int ans = 0;

        for (int b = 0; b <= budget; b++)
        {
            int remaining = budget - b;
            int extra = remaining / minPrice;

            ans = max(ans, dp[b] + extra);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> items = {
        {6, 2},
        {2, 6},
        {3, 4}};

    int budget = 9;

    cout << sol.maximumSaleItems(items, budget) << endl;

    return 0;
}

/*

============================================================
                 LEETCODE 3946
             MAXIMUM NUMBER OF ITEMS
                    FROM SALE I
============================================================

PROBLEM STATEMENT:

You are given a 2D array items where:

items[i] = [factor_i, price_i]

Each item has unlimited copies available.

You can buy items within the given budget.

FREE ITEM RULES:

1. If you purchase at least one copy of item i,
   you receive one free copy of every item j such that:

   j != i AND factor_i divides factor_j.

2. Buying multiple copies of the same item does not
   provide additional free copies.

3. The same item can be received multiple times for free
   through purchases of different item types.

Return the maximum total number of items obtained,
including purchased and free items.


EXAMPLE:

Input:
items = [[6,2],[2,6],[3,4]]
budget = 9

Output:
4

Explanation:

Buy:
- 2 copies of item 0 = 2 * 2 = 4
- 1 copy of item 2 = 4

Total spending = 8.

Buying item 2 gives one free copy of item 0
because 3 divides 6.

Total items:
3 purchased + 1 free = 4.

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA:

For every item, we have two choices:

1. Buy its first copy.
   - Pay its price.
   - Receive itself and all eligible free items.

2. Skip the item.
   - Do not pay anything.
   - Do not receive its free items.

Since buying additional copies of an already activated
item gives no additional free benefit, we can consider
only the first purchase of each type.

Enumerate all subsets of activated item types.

For every subset:
- Calculate its total cost.
- Calculate its total reward.
- Use the remaining budget to buy the cheapest item.
- Update the answer.

PSEUDOCODE:

function bruteForce(index, cost, reward):

    if index == n:
        if cost <= budget:
            remaining = budget - cost

            extra = remaining / minPrice

            ans = max(ans, reward + extra)

        return

    // Skip current item
    bruteForce(index + 1, cost, reward)

    // Take current item for the first time
    if cost + price[index] <= budget:

        bruteForce(
            index + 1,
            cost + price[index],
            reward + 1 + freeCnt[index]
        )


COMPLETE BRUTE FORCE CODE:

    int bruteForce(vector<vector<int>>& items, int budget) {

        int n = items.size();
        int minPrice = INT_MAX;

        vector<int> freeCnt(n, 0);

        for (int i = 0; i < n; i++) {
            minPrice = min(minPrice, items[i][1]);

            for (int j = 0; j < n; j++) {
                if (i != j &&
                    items[j][0] % items[i][0] == 0) {
                    freeCnt[i]++;
                }
            }
        }

        int ans = 0;

        function<void(int, int, int)> dfs =
            [&](int idx, int cost, int reward) {

            if (idx == n) {
                int remaining = budget - cost;

                ans = max(ans,
                    reward + remaining / minPrice);

                return;
            }

            // Skip
            dfs(idx + 1, cost, reward);

            // Take
            if (cost + items[idx][1] <= budget) {
                dfs(
                    idx + 1,
                    cost + items[idx][1],
                    reward + 1 + freeCnt[idx]
                );
            }
        };

        dfs(0, 0, 0);

        return ans;
    }


TIME COMPLEXITY:

O(n^2 + 2^n)

- O(n^2) for calculating free items.
- O(2^n) for enumerating subsets.

SPACE COMPLEXITY:

O(n)

- Free item array.
- Recursion stack.

This approach is too slow for n <= 1000.


============================================================
OPTIMAL APPROACH
============================================================

OBSERVATION:

The first purchase of an item is special.

Suppose we purchase item i for the first time.

We receive:

1. One purchased copy of item i.
2. One free copy of every eligible item.

Therefore:

profit[i] = 1 + freeCnt[i]

After the first purchase, every additional copy gives
exactly one item and costs the item's price.

Now comes the important observation:

For additional purchases, we should always buy the
cheapest available item.

Let:

minPrice = minimum price among all items.

After selecting which item types to purchase for the
first time, we can use the remaining budget to purchase
as many cheapest items as possible.

INTUITION:

This problem becomes a 0/1 Knapsack problem.

Why 0/1 Knapsack?

Each item type can provide its special free-item benefit
only once.

For every item type:

Weight = items[i][1]

Value = 1 + freeCnt[i]

We choose whether to activate that item type or not.

After selecting the special first purchases, we use
the remaining money to buy the cheapest item repeatedly.

DP STATE:

dp[b] = Maximum number of items obtained from
        first purchases using at most b budget.

DP TRANSITION:

For every item:

price = items[i][1]

profit = 1 + freeCnt[i]

dp[b] = max(
    dp[b],
    dp[b - price] + profit
)

We iterate budget backwards to ensure each item's
special benefit is counted only once.

FINAL ANSWER:

For every possible knapsack capacity b:

remaining = budget - b

extra = remaining / minPrice

answer = max(
    answer,
    dp[b] + extra
)


PSEUDOCODE:

Calculate minPrice.

For every item i:
    Calculate freeCnt[i].

Initialize dp[0...budget] = 0.

For every item i:

    price = items[i][1]

    profit = 1 + freeCnt[i]

    For b from budget down to price:

        dp[b] = max(
            dp[b],
            dp[b - price] + profit
        )

ans = 0

For b from 0 to budget:

    remaining = budget - b

    extra = remaining / minPrice

    ans = max(ans, dp[b] + extra)

Return ans.


COMPLETE OPTIMAL CODE:

    int maximumSaleItems(vector<vector<int>>& items,
                         int budget) {

        int n = items.size();
        int minPrice = INT_MAX;

        vector<int> freeCnt(n, 0);

        for (int i = 0; i < n; i++) {
            minPrice = min(minPrice, items[i][1]);

            for (int j = 0; j < n; j++) {
                if (i != j &&
                    items[j][0] % items[i][0] == 0) {
                    freeCnt[i]++;
                }
            }
        }

        vector<int> dp(budget + 1, 0);

        for (int i = 0; i < n; i++) {

            int price = items[i][1];
            int profit = 1 + freeCnt[i];

            for (int b = budget; b >= price; b--) {

                dp[b] = max(
                    dp[b],
                    dp[b - price] + profit
                );
            }
        }

        int ans = 0;

        for (int b = 0; b <= budget; b++) {

            int remaining = budget - b;

            int extra = remaining / minPrice;

            ans = max(ans, dp[b] + extra);
        }

        return ans;
    }


TIME COMPLEXITY:

O(n^2 + n * budget)

Breakdown:

1. Calculating freeCnt:
   O(n^2)

2. Knapsack DP:
   O(n * budget)

3. Calculating final answer:
   O(budget)

Overall:

O(n^2 + n * budget)

SPACE COMPLEXITY:

O(n + budget)

1. freeCnt array = O(n)
2. DP array = O(budget)

============================================================
DRY RUN WITH EXAMPLE
============================================================

Input:

items = [[6,2],[2,6],[3,4]]
budget = 9

STEP 1: Calculate minimum price.

Prices:

Item 0 = 2
Item 1 = 6
Item 2 = 4

minPrice = 2


STEP 2: Calculate freeCnt.

Item 0:
factor = 6

No other factor is divisible by 6.

freeCnt[0] = 0

Item 1:
factor = 2

6 % 2 == 0

3 % 2 != 0

freeCnt[1] = 1

Item 2:
factor = 3

6 % 3 == 0

freeCnt[2] = 1


Final arrays:

freeCnt = [0, 1, 1]

Profit:

Item 0 = 1 + 0 = 1
Item 1 = 1 + 1 = 2
Item 2 = 1 + 1 = 2


STEP 3: Apply 0/1 Knapsack.

Initial:

dp[0...9] = 0

Item 0:
price = 2
profit = 1

Item 1:
price = 6
profit = 2

Item 2:
price = 4
profit = 2


After processing all items:

dp capacity values:

Capacity     Maximum first-purchase reward

0            0
1            0
2            1
3            1
4            2
5            2
6            3
7            3
8            3
9            3


STEP 4: Use remaining budget.

minPrice = 2
budget = 9

For capacity b = 2:

dp[2] = 1

remaining = 9 - 2 = 7

extra = 7 / 2 = 3

total = 1 + 3 = 4


For capacity b = 4:

dp[4] = 2

remaining = 5

extra = 5 / 2 = 2

total = 2 + 2 = 4


For capacity b = 6:

dp[6] = 3

remaining = 3

extra = 3 / 2 = 1

total = 3 + 1 = 4


Maximum answer = 4


OUTPUT:

4


============================================================
INTERVIEW NOTES
============================================================

1. PATTERN:

   - Dynamic Programming
   - 0/1 Knapsack
   - Greedy Optimization
   - Precomputation

2. KEY OBSERVATION:

   The first purchase of each item type gives a special
   reward, but subsequent purchases only give one item.

   Therefore:

   First purchase = 0/1 Knapsack

   Additional purchases = Buy cheapest item greedily

3. COMMON MISTAKES:

   - Using vector<int> instead of vector<vector<int>>
     for the items parameter.

   - Counting the item itself as a free item.
     Always check i != j.

   - Reversing the divisibility condition.

     Correct:
     items[j][0] % items[i][0] == 0

   - Using forward iteration in 0/1 Knapsack.

     Correct:
     for (int b = budget; b >= price; b--)

   - Counting free items again for repeated purchases.

   - Forgetting that the same free item can be received
     multiple times from different purchased item types.

   - Forgetting to use the remaining budget to buy
     the cheapest item.

4. WHEN TO USE THIS APPROACH:

   Use this pattern when:

   - An item provides a special bonus only on its
     first purchase.

   - Subsequent purchases provide a fixed value.

   - You have a limited budget.

   - Every special activation can happen at most once.

   - Repeated purchases can be optimized independently
     using a cheapest-cost greedy choice.

============================================================
FINAL COMPLEXITY
============================================================

Time Complexity  : O(n^2 + n * budget)

Space Complexity : O(n + budget)

PATTERN TO REMEMBER:

SPECIAL FIRST PURCHASE -> 0/1 KNAPSACK

REPEATED PURCHASES -> CHEAPEST ITEM GREEDY

============================================================

*/
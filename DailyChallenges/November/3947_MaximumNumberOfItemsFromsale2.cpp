#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        // Step 1: Count frequency of every factor.
        vector<int> freq(n + 1, 0);

        int minPrice = INT_MAX;
        int maxFactor = 0;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            freq[factor]++;
            minPrice = min(minPrice, price);
            maxFactor = max(maxFactor, factor);
        }

        // Step 2: Calculate number of free-item opportunities.
        vector<int> gain(n + 1, 0);

        for (int f = 1; f <= maxFactor; f++) {
            for (int j = f; j <= maxFactor; j += f) {
                gain[f] += freq[j];
            }

            // Exclude the item itself.
            gain[f]--;
        }

        // Step 3: Collect profitable double-value purchases.
        vector<pair<int, int>> candidates;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            // A double-value purchase must be cheaper
            // than buying two cheapest individual items.
            if (price < 2LL * minPrice && gain[factor] > 0) {
                candidates.push_back({price, gain[factor]});
            }
        }

        // Step 4: Buy cheapest double-value opportunities first.
        sort(candidates.begin(), candidates.end());

        long long remaining = budget;
        long long ans = 0;

        for (auto& [price, count] : candidates) {
            long long take = min(
                (long long)count,
                remaining / price
            );

            remaining -= take * price;
            ans += take * 2;
        }

        // Step 5: Spend remaining budget on cheapest item.
        ans += remaining / minPrice;

        return (int)ans;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> items1 = {
        {1, 6},
        {2, 4},
        {3, 5}
    };

    int budget1 = 19;

    cout << sol.maximumSaleItems(items1, budget1) << endl;
    // Output: 5

    vector<vector<int>> items2 = {
        {2, 8},
        {1, 10},
        {6, 6},
        {4, 12},
        {5, 20},
        {5, 17}
    };

    int budget2 = 35;

    cout << sol.maximumSaleItems(items2, budget2) << endl;
    // Output: 7

    return 0;
}
/*
============================================================
        LEETCODE 3947: MAXIMUM NUMBER OF ITEMS FROM SALE II
============================================================

PROBLEM STATEMENT:

You are given:
    items[i] = [factor[i], price[i]]
    budget

There are unlimited copies of every item.

Rules:
1. Every purchased item can provide at most one free item.
2. Item i can provide item j for free if:
       i != j
       factor[i] divides factor[j]
3. Every ordered pair (i, j) can generate a free item
   at most once.
4. Different item types can provide the same item for free.

Return the maximum number of items (purchased + free)
obtainable within the given budget.


============================================================
EXAMPLE:
============================================================

Input:
items = [[1,6],[2,4],[3,5]]
budget = 19

Output:
5

Explanation:

Buy:
    2 copies of item 0 (price = 6)
    1 copy of item 1 (price = 4)

Total spending:
    2 * 6 + 4 = 16

Free items:
    First copy of item 0 gives item 1.
    Second copy of item 0 gives item 2.

Total:
    3 purchased + 2 free = 5 items.

============================================================
BRUTE FORCE APPROACH:
============================================================

1. IDEA:

Try every possible number of purchases for every item type.

For each item type i:
    We can purchase between 0 and budget / price[i] copies.

After deciding the purchase quantities:

    purchased[i] = number of copies purchased.

    free[i] = min(purchased[i], number of eligible
                  different item types).

Total contribution of item type i:

    purchased[i] + free[i]

Explore all possible purchase combinations and
return the maximum obtainable number of items.

This approach is exponential and only suitable for
very small inputs.

2. PSEUDO CODE:

    function solve(index, remainingBudget):

        if index == n:
            calculate total purchased items
            calculate free items
            update answer
            return

        for count = 0 to remainingBudget / price[index]:

            purchased[index] = count

            solve(index + 1,
                  remainingBudget - count * price[index])

        return answer

3. COMPLETE BRUTE FORCE CODE:

    int bruteForce(vector<vector<int>>& items, int budget) {

        int n = items.size();

        vector<int> purchased(n, 0);

        int ans = 0;

        function<void(int, int)> dfs =
        [&](int index, int remaining) {

            if (index == n) {

                int total = 0;

                for (int i = 0; i < n; i++) {

                    total += purchased[i];

                    int freeCount = 0;

                    for (int j = 0; j < n; j++) {

                        if (i != j &&
                            items[j][0] % items[i][0] == 0) {

                            freeCount++;
                        }
                    }

                    total += min(purchased[i], freeCount);
                }

                ans = max(ans, total);
                return;
            }

            int price = items[index][1];

            for (int cnt = 0; cnt <= remaining / price; cnt++) {

                purchased[index] = cnt;

                dfs(index + 1,
                    remaining - cnt * price);
            }

            purchased[index] = 0;
        };

        dfs(0, budget);

        return ans;
    }

4. TIME COMPLEXITY:

    O(product of (budget / price[i] + 1) * n^2)

    Exponential in the number of item types.

5. SPACE COMPLEXITY:

    O(n)

    Recursion stack + purchase array.


============================================================
OPTIMAL APPROACH: GREEDY + FREQUENCY + SORTING
============================================================

1. OBSERVATION:

For an item with factor f:

    gain[f] = Number of items whose factors are
              divisible by f, excluding itself.

If we purchase c copies of this item:

    Purchased items = c

    Free items = min(c, gain[f])

    Total contribution = c + min(c, gain[f])

This gives us two types of purchases:

    First gain[f] purchases:
        Each purchase gives 2 items.

    Remaining purchases:
        Each purchase gives 1 item.

IMPORTANT:

We can treat purchases as two categories:

    Category 1:
        Cost = price
        Value = 2
        Limited quantity = gain[f]

    Category 2:
        Cost = minPrice
        Value = 1
        Unlimited quantity

2. INTUITION:

Let:

    minPrice = Minimum price among all item types.

Buying one cheapest item gives 1 item for minPrice.

Buying one item with an available free-item opportunity
gives 2 items for its price.

Compare their efficiency:

    Cheapest item:
        1 / minPrice

    Double-value purchase:
        2 / price

A double-value purchase is beneficial when:

    2 / price > 1 / minPrice

    price < 2 * minPrice

Therefore:

    1. Ignore double-value opportunities whose price
       is >= 2 * minPrice.

    2. Sort remaining opportunities by increasing price.

    3. Buy as many profitable opportunities as possible,
       starting with the cheapest.

    4. Spend the remaining budget on the cheapest item.

3. PSEUDO CODE:

    Find minimum price.

    Count frequency of every factor.

    For each factor f:

        gain[f] = sum of frequencies of multiples of f

        gain[f] -= 1

    candidates = empty array

    For every item:

        if price < 2 * minPrice AND gain[factor] > 0:

            Add (price, gain[factor]) to candidates.

    Sort candidates by price.

    ans = 0

    remaining = budget

    For each (price, count) in candidates:

        take = min(count, remaining / price)

        ans += take * 2

        remaining -= take * price

    ans += remaining / minPrice

    Return ans.


4. COMPLETE OPTIMAL CODE:

    int maximumSaleItems(vector<vector<int>>& items,
                         int budget) {

        int n = items.size();

        vector<int> freq(n + 1, 0);

        int minPrice = INT_MAX;
        int maxFactor = 0;

        for (auto& item : items) {

            freq[item[0]]++;

            minPrice = min(minPrice, item[1]);

            maxFactor = max(maxFactor, item[0]);
        }

        vector<int> gain(n + 1, 0);

        for (int f = 1; f <= maxFactor; f++) {

            for (int j = f; j <= maxFactor; j += f) {

                gain[f] += freq[j];
            }

            gain[f]--;
        }

        vector<pair<int, int>> candidates;

        for (auto& item : items) {

            int factor = item[0];
            int price = item[1];

            if (price < 2LL * minPrice &&
                gain[factor] > 0) {

                candidates.push_back({
                    price, gain[factor]
                });
            }
        }

        sort(candidates.begin(), candidates.end());

        long long remaining = budget;
        long long ans = 0;

        for (auto& [price, count] : candidates) {

            long long take = min(
                (long long)count,
                remaining / price
            );

            ans += take * 2;

            remaining -= take * price;
        }

        ans += remaining / minPrice;

        return (int)ans;
    }

5. TIME COMPLEXITY:

    Let n = number of item types.

    Frequency calculation:
        O(n)

    Counting multiples:
        O(n/1 + n/2 + n/3 + ... + n/n)

        = O(n log n)

    Creating candidates:
        O(n)

    Sorting candidates:
        O(n log n)

    Processing candidates:
        O(n)

    TOTAL:

        O(n log n)

6. SPACE COMPLEXITY:

    Frequency array:
        O(n)

    Gain array:
        O(n)

    Candidate array:
        O(n)

    TOTAL:

        O(n)


============================================================
DRY RUN WITH EXAMPLE:
============================================================

Input:

    items = [[1,6], [2,4], [3,5]]
    budget = 19

STEP 1: Find minimum price.

    Prices = [6, 4, 5]

    minPrice = 4

STEP 2: Count factor frequencies.

    factor 1 -> 1
    factor 2 -> 1
    factor 3 -> 1

STEP 3: Calculate gain.

    For factor 1:

        Multiples = 1, 2, 3

        gain[1] = 3 - 1 = 2

    For factor 2:

        Multiples = 2

        gain[2] = 1 - 1 = 0

    For factor 3:

        Multiples = 3

        gain[3] = 1 - 1 = 0

    Result:

        gain = [0, 2, 0, 0]

STEP 4: Find profitable candidates.

    Condition:

        price < 2 * minPrice

        price < 8

    Item 0:

        price = 6
        gain = 2

        Valid candidate: (6, 2)

    Item 1:

        price = 4
        gain = 0

        No free-item opportunity.

    Item 2:

        price = 5
        gain = 0

        No free-item opportunity.

    Candidates:

        [(6, 2)]

STEP 5: Greedy purchasing.

    remaining = 19
    ans = 0

    Candidate (6, 2):

        take = min(2, 19 / 6)
             = min(2, 3)
             = 2

        ans = 2 * 2 = 4

        remaining = 19 - 12
                  = 7

STEP 6: Spend remaining budget.

    Cheapest item price = 4

    Additional purchases:

        7 / 4 = 1

    ans = 4 + 1

       = 5

FINAL ANSWER:

    5


============================================================
INTERVIEW NOTES:
============================================================

1. PATTERN:

    Greedy
    Number Theory
    Frequency Counting
    Divisibility / Multiples
    Sorting
    Mathematical Optimization

2. KEY OBSERVATION:

    Every item type has a limited number of
    double-value purchases.

    First gain[f] purchases give 2 items each.

    All remaining purchases give only 1 item each.

    Therefore, prioritize cheaper double-value
    opportunities and use the cheapest item
    for the remaining budget.

3. COMMON MISTAKES:

    1. Forgetting to exclude the item itself
       while calculating gain[f].

    2. Counting only distinct factors instead
       of counting individual item types.

    3. Forgetting that different item types can
       provide the same item for free.

    4. Assuming every purchased copy can
       generate a free item indefinitely.

    5. Forgetting that only the first gain[f]
       purchases provide free items.

    6. Using O(n^2) to check all factor pairs.

    7. Not sorting candidates by price.

    8. Using int for intermediate budget
       multiplication instead of long long.

    9. Including candidates with price >=
       2 * minPrice unnecessarily.

4. WHEN TO USE THIS APPROACH:

    Use this greedy pattern when:

    - Every purchase has a limited number of
      bonus opportunities.

    - Initial purchases provide extra rewards.

    - Later purchases provide only normal value.

    - There is a cheapest baseline option.

    - You need to maximize total value under
      a limited budget.

    - Divisibility relationships can be counted
      efficiently using multiples.

5. IMPORTANT FORMULAS:

    gain[f] = Sum(freq[multiple of f]) - 1

    contribution(c) = c + min(c, gain[f])

    Profitable condition:

        price < 2 * minPrice

    Greedy purchase quantity:

        take = min(gain[f], remaining / price)

    Final answer:

        ans += 2 * take

        ans += remaining / minPrice


============================================================
FINAL TAKEAWAY:
============================================================

The main trick is converting the problem into
limited value-2 purchases and unlimited value-1
purchases.

Then:

    Frequency + Multiples
            |
            v
       Calculate Gain
            |
            v
      Find Profitable Items
            |
            v
        Sort by Price
            |
            v
       Greedy Purchasing
            |
            v
       Spend Remaining Budget

OVERALL COMPLEXITY:

    Time  : O(n log n)
    Space : O(n)

============================================================
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<array<int, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];

            if (x[0] != y[0])
                return x[0] < y[0];

            return x[3] < y[3];
        });

        vector<int> ends(n);

        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];
        vector<int> p(n);

        for (int i = 0; i < n; i++) {
            p[i] = lower_bound(
                ends.begin(),
                ends.begin() + i,
                a[i][0]
            ) - ends.begin();
        }
        struct State {
            long long score = 0;
            vector<int> indices;
        };

        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= 4; k++) {
                State skip = dp[i - 1][k];
                State take = dp[p[i - 1]][k - 1];

                take.score += a[i - 1][2];
                take.indices.push_back(a[i - 1][3]);
                sort(take.indices.begin(), take.indices.end());
                if (take.score > skip.score) {
                    dp[i][k] = move(take);
                }
                else if (take.score < skip.score) {
                    dp[i][k] = move(skip);
                }
                else {
                    if (take.indices < skip.indices)
                        dp[i][k] = move(take);
                    else
                        dp[i][k] = move(skip);
                }
            }
        }

        return dp[n][4].indices;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals = {
        {1, 3, 2},
        {4, 5, 2},
        {1, 5, 5},
        {6, 9, 3},
        {6, 7, 1},
        {8, 9, 1}
    };

    vector<int> ans = sol.maximumWeight(intervals);

    for (int x : ans)
        cout << x << " ";

    cout << '\n';

    return 0;
}


/*
================================================================================
                    LEETCODE 3414 - NOTEBOOK
================================================================================

PROBLEM STATEMENT
-----------------

You are given:

    intervals[i] = [left_i, right_i, weight_i]

You can choose at most 4 intervals.

Two intervals are non-overlapping only when they do not share any
point.

Therefore:

    previous_right < current_left

The score is the sum of weights of selected intervals.

Return the lexicographically smallest array of original indices
among all selections having maximum total score.


================================================================================
EXAMPLE
================================================================================

Input:

    intervals = [
        [1,3,2],   // index 0
        [4,5,2],   // index 1
        [1,5,5],   // index 2
        [6,9,3],   // index 3
        [6,7,1],   // index 4
        [8,9,1]    // index 5
    ]

Possible optimal choice:

    index 2 -> [1,5,5]
    index 3 -> [6,9,3]

Score:

    5 + 3 = 8

Answer:

    [2,3]


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----

Try every possible subset containing at most 4 intervals.

For each subset:

    1. Check whether it contains at most 4 intervals.
    2. Sort selected intervals by their starting point.
    3. Check whether they overlap.
    4. Calculate total weight.
    5. Keep the maximum score.
    6. If scores are equal, keep the lexicographically smaller
       original-index array.


PSEUDO CODE
-----------

    bestScore = 0
    bestAnswer = []

    for every subset:

        if size(subset) > 4:
            continue

        sort selected intervals by start

        if any two consecutive intervals overlap:
            continue

        score = sum of weights

        sort original indices

        if score > bestScore:
            update answer

        else if score == bestScore:
            choose lexicographically smaller answer

    return bestAnswer


COMPLETE BRUTE FORCE CODE
-------------------------

    vector<int> bruteForce(vector<vector<int>>& intervals) {
    
        int n = intervals.size();
    
        long long bestScore = 0;
        vector<int> bestAnswer;
    
        for (long long mask = 0;
             mask < (1LL << n);
             mask++) {
    
            if (__builtin_popcountll(mask) > 4)
                continue;
    
            vector<int> ids;
    
            for (int i = 0; i < n; i++) {
                if (mask & (1LL << i))
                    ids.push_back(i);
            }
    
            sort(ids.begin(), ids.end(), [&](int x, int y) {
                return intervals[x][0] < intervals[y][0];
            });
    
            bool valid = true;
            long long score = 0;
    
            for (int i = 0; i < (int)ids.size(); i++) {
    
                score += intervals[ids[i]][2];
    
                if (i > 0) {
                    int previous = ids[i - 1];
                    int current = ids[i];
    
                    if (intervals[previous][1] >=
                        intervals[current][0]) {
    
                        valid = false;
                        break;
                    }
                }
            }
    
            if (!valid)
                continue;
    
            sort(ids.begin(), ids.end());
    
            if (score > bestScore ||
                (score == bestScore && ids < bestAnswer)) {
    
                bestScore = score;
                bestAnswer = ids;
            }
        }
    
        return bestAnswer;
    }


TIME COMPLEXITY
---------------

There are:

    O(2^n)

subsets.

Therefore brute force is exponential.

More precisely, because we only care about up to 4 intervals:

    C(n,1) + C(n,2) + C(n,3) + C(n,4)

which is still approximately:

    O(n^4)

for large n.


SPACE COMPLEXITY
----------------

Temporary selected indices:

    O(4) = O(1)

apart from subset generation.


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------

This is a Weighted Interval Scheduling problem.

Normally we want:

    maximum weight of non-overlapping intervals.

Here we have an additional constraint:

    choose at most 4 intervals.

Therefore we use:

    Sorting
        +
    Binary Search
        +
    DP


INTUITION
---------

Sort intervals by their ending position.

For every interval i, find the number of previous intervals that
are compatible with it.

If:

    current_start = S

we need:

    previous_end < S

Since the intervals are sorted by ending position, binary search
can find the first ending position that is >= S.

That position tells us how many intervals are compatible.


DP STATE
--------

Define:

    dp[i][k]

as:

    best answer using the first i sorted intervals
    and choosing at most k intervals.

Each DP state stores:

    1. maximum score
    2. lexicographically smallest list of indices
       achieving that score


TRANSITION
----------

For interval i there are two choices.


OPTION 1: SKIP
--------------

Do not choose interval i.

    skip = dp[i-1][k]


OPTION 2: TAKE
--------------

Choose interval i.

Let:

    p[i]

be the number of previous intervals whose ending position is
strictly less than the current starting position.

Then:

    take =
        dp[p[i]][k-1] + current_weight


FINAL TRANSITION
----------------

    dp[i][k] = better(skip, take)

where "better" means:

    1. Higher score is better.
    2. If score is equal, lexicographically smaller index list
       is better.


WHY THE PREVIOUS SOLUTION WAS WRONG
-----------------------------------

The previous code used:

    if (candidate > dp[i][k])

It completely ignored:

    candidate == dp[i][k]

But LeetCode requires the lexicographically smallest answer
when the scores are equal.

For example:

    take  -> score = 10, indices = [1,4]
    skip  -> score = 10, indices = [2,3]

Both have score 10.

We must choose:

    [1,4]

because:

    [1,4] < [2,3]

Therefore every DP transition must handle:

    greater score
        OR
    equal score + lexicographically smaller indices.


PSEUDO CODE
-----------

    sort intervals by end

    for every interval i:

        p[i] =
            first position where
            end >= start[i]

    dp[0][0...4] = empty answer

    for i = 1 to n:

        for k = 1 to 4:

            skip = dp[i-1][k]

            take = dp[p[i-1]][k-1]

            take.score += weight[i-1]

            add original_index to take.indices

            sort take.indices

            if take.score > skip.score:
                dp[i][k] = take

            else if take.score < skip.score:
                dp[i][k] = skip

            else:
                dp[i][k] =
                    lexicographically smaller of
                    take and skip

    return dp[n][4].indices


COMPLETE OPTIMAL LEETCODE CODE
------------------------------

    class Solution {
    public:
        vector<int> maximumWeight(vector<vector<int>>& intervals) {
            int n = intervals.size();
    
            vector<array<int, 4>> a;
    
            for (int i = 0; i < n; i++) {
                a.push_back({
                    intervals[i][0],
                    intervals[i][1],
                    intervals[i][2],
                    i
                });
            }
    
            sort(a.begin(), a.end(),
                 [](const auto& x, const auto& y) {
    
                if (x[1] != y[1])
                    return x[1] < y[1];
    
                if (x[0] != y[0])
                    return x[0] < y[0];
    
                return x[3] < y[3];
            });
    
            vector<int> ends(n);
    
            for (int i = 0; i < n; i++)
                ends[i] = a[i][1];
    
            vector<int> p(n);
    
            for (int i = 0; i < n; i++) {
                p[i] = lower_bound(
                    ends.begin(),
                    ends.begin() + i,
                    a[i][0]
                ) - ends.begin();
            }
    
            struct State {
                long long score = 0;
                vector<int> indices;
            };
    
            vector<vector<State>> dp(
                n + 1,
                vector<State>(5)
            );
    
            for (int i = 1; i <= n; i++) {
    
                for (int k = 1; k <= 4; k++) {
    
                    State skip = dp[i - 1][k];
    
                    State take = dp[p[i - 1]][k - 1];
    
                    take.score += a[i - 1][2];
    
                    take.indices.push_back(a[i - 1][3]);
    
                    sort(take.indices.begin(),
                         take.indices.end());
    
                    if (take.score > skip.score) {
                        dp[i][k] = move(take);
                    }
                    else if (take.score < skip.score) {
                        dp[i][k] = move(skip);
                    }
                    else {
                        if (take.indices < skip.indices)
                            dp[i][k] = move(take);
                        else
                            dp[i][k] = move(skip);
                    }
                }
            }
    
            return dp[n][4].indices;
        }
    };


TIME COMPLEXITY
---------------

Sorting intervals:

    O(n log n)

Binary search for every interval:

    O(n log n)

DP states:

    5 * n = O(n)

Each state contains at most 4 indices.

Therefore copying/sorting the selected indices is constant-sized:

    O(1)

Overall:

    O(n log n)


SPACE COMPLEXITY
----------------

DP:

    O(5n)

Each state stores at most 4 indices.

Therefore:

    O(n)


================================================================================
DRY RUN
================================================================================

Input:

    [
        [1,3,2],   // 0
        [4,5,2],   // 1
        [1,5,5],   // 2
        [6,9,3],   // 3
        [6,7,1],   // 4
        [8,9,1]    // 5
    ]


SORT BY END
-----------

    [1,3,2] -> index 0
    [1,5,5] -> index 2
    [4,5,2] -> index 1
    [6,7,1] -> index 4
    [6,9,3] -> index 3
    [8,9,1] -> index 5


Consider:

    [1,5,5] -> index 2

Its next compatible interval must start strictly after 5.

So:

    [6,9,3] -> index 3

is compatible.

Taking both gives:

    score = 5 + 3
          = 8

indices:

    [2,3]


Now consider:

    [1,3,2] -> index 0

It can be combined with:

    [4,5,2] -> index 1

and then:

    [6,7,1] -> index 4

and:

    [8,9,1] -> index 5

Score:

    2 + 2 + 1 + 1
    = 6


Therefore:

    [2,3]

has score 8 and is better.


IMPORTANT TIE EXAMPLE
---------------------

Suppose two DP choices are:

    take:
        score = 10
        indices = [1,4]

    skip:
        score = 10
        indices = [2,3]

Scores are equal.

Compare:

    [1,4] < [2,3]

Therefore:

    dp = [1,4]


This tie-breaking step is what was missing from the previous
incorrect solution.


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------

Weighted Interval Scheduling

combined with:

    Binary Search
    +
    DP


KEY OBSERVATION
---------------

Sort by ending position.

For each interval, find all previous intervals satisfying:

    previous_end < current_start

using binary search.


MOST IMPORTANT DETAIL
---------------------

The DP must optimize two things:

    1. Maximum total weight
    2. Lexicographically smallest indices when weights tie


COMMON MISTAKES
---------------

1. Using:

       previous_end <= current_start

   WRONG.

   Intervals sharing a boundary overlap.

   Correct:

       previous_end < current_start


2. Ignoring lexicographical tie-breaking.

   This was the bug in the previous solution.

   Correct comparison:

       higher score
           OR
       equal score + smaller index vector


3. Losing original indices after sorting.

   Always store:

       start
       end
       weight
       original index


4. Using greedy.

   Picking the interval with maximum weight does not guarantee
   the globally optimal combination.


5. Forgetting that "at most 4" means fewer than 4 intervals
   are also valid.


6. Using int for the total score.

   Maximum total can exceed 32-bit signed integer range.

   Use:

       long long


7. Using upper_bound incorrectly.

   Since we require:

       end < start

   use:

       lower_bound(ends, start)


WHEN TO USE THIS APPROACH
-------------------------

Use this pattern when:

    - You have intervals/jobs/events.
    - Each interval has a weight/profit.
    - Chosen intervals cannot overlap.
    - You need maximum total weight.
    - There is a small limit K on selected intervals.
    - There is a tie-breaking requirement.


GENERAL TEMPLATE
----------------

    Sort intervals by end

            ↓

    Find previous compatible interval
    using binary search

            ↓

    DP on number of selected intervals

            ↓

    At each state:
        maximize score

        if tied:
            minimize lexicographical indices

            ↓

    Reconstruct / return answer


CORE FORMULA
------------

    skip = dp[i - 1][k]

    take =
        dp[p[i - 1]][k - 1] + weight[i - 1]

    dp[i][k] =
        better(skip, take)

where:

    better =
        maximum score

        and on tie:
        lexicographically smaller index list.


FINAL COMPLEXITY
----------------

    Time  : O(n log n)
    Space : O(n)


================================================================================
*/

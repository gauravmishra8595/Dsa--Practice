#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxSelectedElements(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> dp;
        int ans = 0;
        for (int x : nums)
        {
            dp[x + 1] = max(dp[x + 1], dp[x] + 1);
            dp[x] = max(dp[x], dp[x - 1] + 1);
            ans = max({ans, dp[x], dp[x + 1]});
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {2, 1, 5, 1, 1};

    cout << sol.maxSelectedElements(nums) << endl;

    return 0;
}

/*

============================================================
PROBLEM STATEMENT
============================================================

You are given an integer array nums.

You can perform the following operation at most once on
each element:

    Increment the element by 1.

You can select any number of elements from the array.

Find the maximum number of selected elements such that
the selected elements can be rearranged to form a sequence
of consecutive integers.

============================================================
EXAMPLE
============================================================

Input:
nums = [2, 1, 5, 1, 1]

Output:
3

Explanation:

We can modify the elements as follows:

1 -> 1
1 -> 2
2 -> 3

The selected elements are:

[1, 2, 3]

Maximum length = 3.

============================================================
BRUTE FORCE APPROACH
============================================================

1. IDEA
-------

For every element, we have three choices:

    1. Skip the element.
    2. Select the element without modification.
    3. Select the element after incrementing it by 1.

Generate all possible combinations.

For every combination:
    - Store selected values in a set.
    - Find the longest consecutive sequence.
    - Update the answer.

2. PSEUDO CODE
--------------

function solve(index, selected):

    if index == n:

        Find longest consecutive sequence
        in selected values.

        Update answer.
        return

    // Choice 1: Skip
    solve(index + 1, selected)

    // Choice 2: Select without increment
    selected.push(nums[index])
    solve(index + 1, selected)
    selected.pop()

    // Choice 3: Select after increment
    selected.push(nums[index] + 1)
    solve(index + 1, selected)
    selected.pop()


3. COMPLETE BRUTE FORCE CODE
----------------------------

#include <bits/stdc++.h>
using namespace std;

class BruteForce {
public:
    int ans = 0;

    void solve(int i, vector<int>& nums,
               vector<int>& selected) {

        if (i == nums.size()) {

            set<int> st(selected.begin(), selected.end());

            int len = 0;
            int best = 0;
            int prev = INT_MIN;

            for (int x : st) {

                if (prev != INT_MIN && x == prev + 1) {
                    len++;
                }
                else {
                    len = 1;
                }

                best = max(best, len);
                prev = x;
            }

            ans = max(ans, best);
            return;
        }

        // Choice 1: Skip
        solve(i + 1, nums, selected);

        // Choice 2: Select without increment
        selected.push_back(nums[i]);
        solve(i + 1, nums, selected);
        selected.pop_back();

        // Choice 3: Select after increment
        selected.push_back(nums[i] + 1);
        solve(i + 1, nums, selected);
        selected.pop_back();
    }

    int maxSelectedElements(vector<int>& nums) {

        vector<int> selected;

        ans = 0;

        solve(0, nums, selected);

        return ans;
    }
};


4. TIME COMPLEXITY
------------------

There are 3 choices for every element.

Total combinations = 3^n.

Checking each combination takes O(n log n).

Time Complexity:

O(3^n * n log n)


5. SPACE COMPLEXITY
-------------------

Recursion depth = O(n).
Selected array = O(n).
Set = O(n).

Space Complexity:

O(n)


============================================================
OPTIMAL APPROACH
============================================================

1. OBSERVATION
--------------

Every element can contribute either:

    nums[i]
    nums[i] + 1

We need to construct the longest consecutive sequence.

For example:

    [1, 1, 2, 2]

We can construct:

    [1, 2, 3]

Instead of generating all possible subsequences,
we can use Dynamic Programming.

2. INTUITION
------------

Sort the array.

Maintain a DP hashmap:

    dp[x] = Maximum length of a consecutive sequence
            ending at value x.

For every element x, we have two possibilities.

CASE 1: DO NOT INCREMENT

We select x.

To extend a consecutive sequence ending at x - 1:

    dp[x] = max(dp[x], dp[x - 1] + 1)


CASE 2: INCREMENT

We select x + 1.

To extend a consecutive sequence ending at x:

    dp[x + 1] = max(dp[x + 1], dp[x] + 1)


Process each element and update the answer.

IMPORTANT:

Process dp[x + 1] before dp[x].

This ensures that the current element cannot be used
twice in the same transition.

3. PSEUDO CODE
--------------

sort(nums)

initialize dp hashmap
ans = 0

for each x in nums:

    // Increment x to x + 1
    dp[x + 1] = max(dp[x + 1], dp[x] + 1)

    // Keep x unchanged
    dp[x] = max(dp[x], dp[x - 1] + 1)

    ans = max(ans, dp[x], dp[x + 1])

return ans


4. COMPLETE OPTIMAL CODE
------------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        unordered_map<int, int> dp;

        int ans = 0;

        for (int x : nums) {

            // Increment current element
            dp[x + 1] = max(dp[x + 1], dp[x] + 1);

            // Do not increment current element
            dp[x] = max(dp[x], dp[x - 1] + 1);

            ans = max({ans, dp[x], dp[x + 1]});
        }

        return ans;
    }
};


5. TIME COMPLEXITY
------------------

Sorting:

    O(n log n)

DP traversal:

    O(n) expected

Each hashmap operation takes O(1) expected time.

Overall Time Complexity:

    O(n log n) expected


6. SPACE COMPLEXITY
-------------------

DP hashmap stores at most O(n) relevant states.

Space Complexity:

    O(n)


============================================================
DRY RUN WITH EXAMPLE
============================================================

Input:

nums = [2, 1, 5, 1, 1]

STEP 1: SORT

nums = [1, 1, 1, 2, 5]

Initially:

dp = {}
ans = 0


STEP 2: PROCESS x = 1

Increment:

dp[2] = dp[1] + 1 = 1

Do not increment:

dp[1] = dp[0] + 1 = 1

DP:

dp[1] = 1
dp[2] = 1

ans = 1


STEP 3: PROCESS x = 1

Increment:

dp[2] = dp[2] + 1 = 2

Do not increment:

dp[1] = max(1, dp[0] + 1) = 1

DP:

dp[1] = 1
dp[2] = 2

ans = 2


STEP 4: PROCESS x = 1

Increment:

dp[2] = dp[2] + 1 = 3

Do not increment:

dp[1] = 1

DP:

dp[1] = 1
dp[2] = 3

ans = 3


STEP 5: PROCESS x = 2

Increment:

dp[3] = dp[2] + 1 = 4

Do not increment:

dp[2] = max(3, dp[1] + 1) = 3

DP:

dp[1] = 1
dp[2] = 3
dp[3] = 4

ans = 4


STEP 6: PROCESS x = 5

Increment:

dp[6] = dp[5] + 1 = 1

Do not increment:

dp[5] = dp[4] + 1 = 1

Final answer:

ans = 4

Output:

4

One possible selection:

[1, 2, 3, 4]

============================================================
INTERVIEW NOTES
============================================================

1. PATTERN
----------

Dynamic Programming + Sorting + HashMap.

More specifically:

DP on values instead of array indices.

2. KEY OBSERVATION
------------------

For every number x, there are only two useful
transitions:

    x -> x
    x -> x + 1

Maintain the longest consecutive sequence ending
at each possible value.

3. COMMON MISTAKES
------------------

1. Forgetting to sort the array.

2. Updating dp[x] before dp[x + 1].
   This can allow the same element to be reused.

3. Using assignment instead of max().
   Multiple elements can contribute to the same
   ending value.

4. Forgetting that duplicate elements are allowed
   in the original array.

5. Thinking that every element must be selected.
   We can skip any number of elements.

4. WHEN TO USE THIS APPROACH
----------------------------

Use this technique when:

- You need the longest consecutive sequence.
- Each element has a limited number of possible
  modifications.
- Sorting helps establish a processing order.
- DP states can be represented by ending values.
- Multiple elements can transition into the same
  DP state.

============================================================
FINAL COMPLEXITY
============================================================

Time  : O(n log n) expected
Space : O(n)

============================================================

*/
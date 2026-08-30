#include <bits/stdc++.h>
using namespace std;

// Optimal / Backtracking Solution
class Solution
{
public:
    vector<vector<int>> result;

    void solve(int start, int n, int k, vector<int> &temp)
    {
        if (k == 0)
        {
            result.push_back(temp);
            return;
        }

        if (start > n)
        {
            return;
        }

        temp.push_back(start);
        solve(start + 1, n, k - 1, temp);

        temp.pop_back();
        solve(start + 1, n, k, temp);
    }

    vector<vector<int>> combine(int n, int k)
    {
        result.clear();

        vector<int> temp;
        solve(1, n, k, temp);

        return result;
    }
};

int main()
{
    int n = 4;
    int k = 2;

    Solution sol;

    vector<vector<int>> ans = sol.combine(n, k);

    for (auto &combination : ans)
    {
        for (int x : combination)
        {
            cout << x << " ";
        }
        cout << "\n";
    }

    return 0;
}

/*
================================================================================
                    LEETCODE 77 - COMBINATIONS
================================================================================

Problem Statement:
------------------
Given two integers n and k, return all possible combinations of k numbers
chosen from the range [1, n].

You may return the answer in any order.

A combination is a selection of k different numbers where the order does
not matter.

Example:
--------
Input:
    n = 4
    k = 2

Output:
    [[1,2], [1,3], [1,4], [2,3], [2,4], [3,4]]

For example:

    [1,2] and [2,1]

are considered the same combination.

Therefore, we only generate numbers in increasing order.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
One brute force idea is to generate all possible subsets of numbers from
1 to n.

There are 2^n possible subsets.

For every subset:
    1. Check its size.
    2. If its size is k, add it to the answer.

This works, but it generates many subsets that are not needed.


Pseudo Code:
------------
1. Generate all subsets of [1, n].
2. For every subset:
       If size == k:
           Add it to result.
3. Return result.


Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<vector<int>> result;

    void generate(int index, int n, int k, vector<int>& temp) {
        if (index > n) {
            if (temp.size() == k) {
                result.push_back(temp);
            }
            return;
        }

        // Take current number
        temp.push_back(index);
        generate(index + 1, n, k, temp);
        temp.pop_back();

        // Do not take current number
        generate(index + 1, n, k, temp);
    }

    vector<vector<int>> combine(int n, int k) {
        result.clear();

        vector<int> temp;
        generate(1, n, k, temp);

        return result;
    }
};


Time Complexity:
----------------
O(2^n * k)

There are 2^n subsets and checking/storing a subset can take O(k).


Space Complexity:
-----------------
O(n)

Recursion depth is O(n), and temp can contain at most n elements.

Ignoring the output space.


================================================================================
OPTIMAL APPROACH - BACKTRACKING
================================================================================

Observation:
------------
We only need combinations of exactly k elements.

For every number, there are two choices:

    1. Take the number.
    2. Skip the number.

However, because we generate numbers from left to right, every combination
is automatically generated in increasing order.

For example:

    [1, 3, 4]

will be generated.

But:

    [3, 1, 4]

will never be generated.

This avoids duplicate combinations.


Intuition:
----------
Suppose:

    n = 4
    k = 2

Start with:

    []

At number 1:

    Take 1
        [1]

        Take 2
            [1,2] -> complete

        Skip 2
            Take 3
                [1,3] -> complete

            Skip 3
                Take 4
                    [1,4] -> complete

    Skip 1
        [ ]

        Take 2
            [2]

            Take 3
                [2,3] -> complete

            Skip 3
                Take 4
                    [2,4] -> complete

        ...


Whenever k becomes 0, we have selected exactly k numbers, so we store
the current combination.


Pseudo Code:
------------
solve(start, n, k, temp):

    If k == 0:
        add temp to result
        return

    If start > n:
        return

    Take start:
        temp.push_back(start)
        solve(start + 1, n, k - 1, temp)
        temp.pop_back()

    Skip start:
        solve(start + 1, n, k, temp)


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<vector<int>> result;

    void solve(int start, int n, int k, vector<int>& temp) {
        if (k == 0) {
            result.push_back(temp);
            return;
        }

        if (start > n) {
            return;
        }

        temp.push_back(start);
        solve(start + 1, n, k - 1, temp);

        temp.pop_back();
        solve(start + 1, n, k, temp);
    }

    vector<vector<int>> combine(int n, int k) {
        result.clear();

        vector<int> temp;
        solve(1, n, k, temp);

        return result;
    }
};


Time Complexity:
----------------
There are C(n, k) valid combinations.

Each combination contains k elements.

Therefore, considering the output:

    O(C(n,k) * k)

This is optimal because we must actually generate and store every
combination.


Space Complexity:
-----------------
O(k)

Recursion depth and temp array contain at most k selected elements.

Ignoring the result/output space.


================================================================================
DRY RUN
================================================================================

Example:

    n = 4
    k = 2

Initial:

    start = 1
    temp = []


1. Take 1:

    temp = [1]
    k = 1

    Take 2:

        temp = [1,2]
        k = 0

        Store [1,2]

        Backtrack:

        temp = [1]

    Skip 2:

        Take 3:

            temp = [1,3]
            k = 0

            Store [1,3]

            Backtrack

        Skip 3:

            Take 4:

                temp = [1,4]
                k = 0

                Store [1,4]


2. Skip 1:

    temp = []

    Take 2:

        temp = [2]

        Take 3:

            temp = [2,3]
            k = 0

            Store [2,3]

        Skip 3:

            Take 4:

                temp = [2,4]
                k = 0

                Store [2,4]


3. Continue:

    Take 3:

        temp = [3]

        Take 4:

            temp = [3,4]
            k = 0

            Store [3,4]


Final Result:

    [1,2]
    [1,3]
    [1,4]
    [2,3]
    [2,4]
    [3,4]


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Backtracking / Recursion / Subsets & Combinations


Key Observation:
----------------
For every number, we have two choices:

    Take
    Skip

But because we always move from:

    start -> start + 1

we never generate duplicate combinations.


Common Mistakes:
----------------
1. Forgetting to backtrack:

       temp.push_back(start);
       solve(...);
       temp.pop_back();

   The pop_back() is necessary before exploring the skip branch.

2. Forgetting the k == 0 base case.

3. Using k == 0 without returning.

4. Generating permutations instead of combinations.

5. Not clearing result in combine():

       result.clear();

   This is important if the same Solution object is reused.

6. Passing n by reference unnecessarily.

   This:

       int& n

   is not required.

   Prefer:

       int n


When to Use This Approach:
--------------------------
Use this backtracking pattern when:

    - You need all combinations.
    - You need all subsets of a certain size.
    - You need to choose k elements from n elements.
    - Order does not matter.
    - You need to generate all possible valid choices.


Useful Backtracking Template:
------------------------------

void solve(start, n, k, temp) {

    if (base_condition) {
        result.push_back(temp);
        return;
    }

    // Take
    temp.push_back(choice);
    solve(next_choice, ...);
    temp.pop_back();

    // Skip
    solve(next_choice, ...);
}


Important Difference:
---------------------

COMBINATION:
    [1,2] == [2,1]

PERMUTATION:
    [1,2] != [2,1]

For LeetCode 77, order does NOT matter,
so we use the combination/backtracking pattern.


Complexity:
-----------

Time  = O(C(n,k) * k) considering output
Space = O(k) auxiliary space

================================================================================
*/

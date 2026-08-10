#include <bits/stdc++.h>
using namespace std;

// LeetCode 1441: Build an Array With Stack Operations
class Solution
{
public:
    vector<string> buildArray(vector<int> &target, int n)
    {
        vector<string> ans;
        int idx = 0;

        for (int num = 1; num <= n && idx < target.size(); num++)
        {
            ans.push_back("Push");

            if (num == target[idx])
            {
                idx++;
            }
            else
            {
                ans.push_back("Pop");
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> target = {1, 3};
    int n = 3;

    vector<string> ans = sol.buildArray(target, n);

    for (string op : ans)
    {
        cout << op << " ";
    }
    cout << '\n';

    return 0;
}

/*
================================================================================
LeetCode 1441 - Build an Array With Stack Operations
================================================================================

Problem Statement:
------------------
Given an integer array target and an integer n.

We start with an empty stack and numbers from 1 to n are read one by one.

For every number read, we can perform:
1. Push  -> Push the current number into the stack.
2. Pop   -> Remove the top element from the stack.

The final stack must be exactly equal to target.

Return a list of operations that constructs target.

Example:
--------
Input:
target = [1, 3], n = 3

Output:
["Push", "Push", "Pop", "Push"]

Explanation:
Read 1:
    Push -> [1]

Read 2:
    Push -> [1, 2]
    Pop  -> [1]

Read 3:
    Push -> [1, 3]

Final stack = [1, 3]


================================================================================
Brute Force Approach
================================================================================

Idea:
-----
Try generating different combinations of Push and Pop operations and check
whether the resulting stack becomes equal to target.

However, this is unnecessary because the numbers are read sequentially from
1 to n, and for every number we only need to decide whether to keep it or
discard it.

Pseudo Code:
------------
function buildArrayBruteForce(target, n):
    try all possible Push/Pop operation combinations
    for every combination:
        simulate the stack
        if final stack == target:
            return operations

Complete brute force code (for revision only):
-----------------------------------------------

class SolutionBruteForce {
public:
    bool dfs(int num, int n, vector<int>& target,
             vector<int>& stack, vector<string>& operations) {

        if (num > n) {
            return stack == target;
        }

        Push current number
        stack.push_back(num);
        operations.push_back("Push");

        if (dfs(num + 1, n, target, stack, operations))
            return true;

        operations.pop_back();
        stack.pop_back();

        Push and then Pop current number
        stack.push_back(num);
        operations.push_back("Push");
        operations.push_back("Pop");

        stack.pop_back();

        if (dfs(num + 1, n, target, stack, operations))
            return true;

        operations.pop_back();
        operations.pop_back();

        return false;
    }

    vector<string> buildArray(vector<int>& target, int n) {
        vector<int> stack;
        vector<string> operations;

        dfs(1, n, target, stack, operations);

        return operations;
    }
};

Time Complexity:
----------------
O(2^n * n) in the worst case due to exploring many operation sequences.

Space Complexity:
-----------------
O(n) recursion/stack space, excluding the generated answer.


================================================================================
Optimal Approach
================================================================================

Observation:
------------
Numbers are always read in increasing order:

1, 2, 3, ..., n

For every number:
- If it is present in target, we keep it using "Push".
- If it is not present in target, we Push it and immediately Pop it.

Once all elements of target have been processed, we can stop.

Intuition:
----------
Suppose target = [1, 3].

Read 1:
    1 is required -> Push

Read 2:
    2 is not required -> Push, Pop

Read 3:
    3 is required -> Push

Therefore:
    Push, Push, Pop, Push

Because target is strictly increasing, we can simply maintain an index
pointing to the next required target element.

Pseudo Code:
------------
function buildArray(target, n):
    ans = empty list
    idx = 0

    for num from 1 to n:
        if idx == target.size():
            break

        Push num

        if num == target[idx]:
            idx++
        else:
            Pop num

    return ans

Complete optimal code (for revision only):
-------------------------------------------

class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> ans;
        int idx = 0;

        for (int num = 1; num <= n && idx < target.size(); num++) {
            ans.push_back("Push");

            if (num == target[idx]) {
                idx++;
            } else {
                ans.push_back("Pop");
            }
        }

        return ans;
    }
};

Time Complexity:
----------------
O(n)

Each number from 1 to n is processed at most once.

Space Complexity:
-----------------
O(1) auxiliary space.

The output vector itself requires O(n) space, but that is the required
space for storing the answer.


================================================================================
Dry Run with Example
================================================================================

target = [1, 3]
n = 3

idx = 0

num = 1:
    target[idx] = 1
    1 == 1
    Push
    idx = 1

Operations:
    [Push]

num = 2:
    target[idx] = 3
    2 != 3
    Push
    Pop

Operations:
    [Push, Push, Pop]

num = 3:
    target[idx] = 3
    3 == 3
    Push
    idx = 2

All target elements are processed.

Final Operations:
    [Push, Push, Pop, Push]

Final Stack:
    [1, 3]


================================================================================
Interview Notes
================================================================================

Pattern:
--------
Greedy / Simulation

Key Observation:
----------------
Process numbers from 1 to n sequentially.

For each number:
    Required in target -> Push
    Not required       -> Push + Pop

Since target is strictly increasing, a single pointer is enough to track
the next required element.

Common Mistakes:
----------------
1. Continuing after all target elements have been processed.
2. Forgetting that an unwanted number must first be pushed before it can
   be popped.
3. Using unnecessary stack simulation when only the target index is needed.
4. Comparing against the wrong target index.
5. Using brute force/backtracking when a simple greedy simulation works.

When to use this approach:
--------------------------
Use this pattern when:
- Input values arrive in a fixed sequential order.
- Each value can either be kept or immediately discarded.
- The desired final sequence is already ordered.
- We only need to simulate the required decisions.

The general greedy idea is:

    Process each item once.
    Keep it if needed.
    Otherwise perform the minimum operation to discard it.

================================================================================
*/
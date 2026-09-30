#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> maxDepthAfterSplit(string seq)
    {
        vector<int> ans;
        int depth = 0;

        for (char ch : seq)
        {
            if (ch == '(')
            {
                depth++;
                ans.push_back(depth % 2);
            }
            else
            {
                ans.push_back(depth % 2);
                depth--;
            }
        }

        return ans;
    }
};

int main()
{
    string seq;
    cin >> seq;

    Solution sol;
    vector<int> ans = sol.maxDepthAfterSplit(seq);

    for (int x : ans)
    {
        cout << x << " ";
    }

    return 0;
}

/*
================================================================================
PROBLEM STATEMENT
================================================================================

Given a valid parentheses string seq, split the parentheses into two groups:
Group 0 and Group 1.

Each parenthesis must belong to exactly one group.

Return a vector<int> ans where:
    ans[i] = 0 -> seq[i] belongs to Group 0
    ans[i] = 1 -> seq[i] belongs to Group 1

The goal is to minimize the maximum nesting depth of the two groups.

================================================================================
EXAMPLE
================================================================================

Input:
    (()())

Output:
    1 0 0 0 0 1

The exact optimal assignment can vary, but the nesting depth of the two
groups should be minimized.

================================================================================
BRUTE FORCE APPROACH
================================================================================

-------------------------
Idea
-------------------------

For every parenthesis, choose either Group 0 or Group 1.

There are 2^n possible assignments for a string of length n.

For every assignment:
    1. Build the two groups.
    2. Find the maximum nesting depth of each group.
    3. Take the maximum of those two depths.
    4. Keep the assignment with the minimum value.

This is correct but exponential.

-------------------------
Pseudo Code
-------------------------

function getDepth(s):
    depth = 0
    maxDepth = 0

    for ch in s:
        if ch == '(':
            depth++
            maxDepth = max(maxDepth, depth)
        else:
            depth--

    return maxDepth


function bruteForce(seq):
    n = length(seq)
    bestDepth = infinity

    for every mask from 0 to 2^n - 1:

        group0 = ""
        group1 = ""
        ans = []

        for i from 0 to n-1:
            if mask has bit i:
                group1 += seq[i]
                ans[i] = 1
            else:
                group0 += seq[i]
                ans[i] = 0

        depth0 = getDepth(group0)
        depth1 = getDepth(group1)

        current = max(depth0, depth1)

        if current < bestDepth:
            bestDepth = current
            bestAns = ans

    return bestAns

-------------------------
Complete Brute Force Code
(For revision only - NOT executable)
-------------------------

int getDepth(string s) {
    int depth = 0;
    int maxDepth = 0;

    for (char ch : s) {
        if (ch == '(') {
            depth++;
            maxDepth = max(maxDepth, depth);
        } else {
            depth--;
        }
    }

    return maxDepth;
}

vector<int> bruteForce(string seq) {
    int n = seq.size();

    int bestDepth = INT_MAX;
    vector<int> bestAns;

    for (int mask = 0; mask < (1 << n); mask++) {
        string group0, group1;
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                group1 += seq[i];
                ans[i] = 1;
            } else {
                group0 += seq[i];
                ans[i] = 0;
            }
        }

        int depth0 = getDepth(group0);
        int depth1 = getDepth(group1);

        int currentDepth = max(depth0, depth1);

        if (currentDepth < bestDepth) {
            bestDepth = currentDepth;
            bestAns = ans;
        }
    }

    return bestAns;
}

-------------------------
Time Complexity
-------------------------

O(2^n * n)

There are 2^n possible assignments and each requires O(n) processing.

-------------------------
Space Complexity
-------------------------

O(n)

For storing the groups and the answer.

================================================================================
OPTIMAL APPROACH
================================================================================

-------------------------
Observation
-------------------------

The current nesting depth tells us how deeply nested the current
parenthesis is.

We can divide the nested parentheses between the two groups by alternating
the group according to the parity of the depth.

    Odd depth  -> Group 1
    Even depth -> Group 0

Therefore:

    group = depth % 2

-------------------------
Intuition
-------------------------

If all nested parentheses are placed in the same group, that group gets
a large nesting depth.

By alternating the groups based on depth, the nested levels are distributed
between the two groups.

For '(':
    1. Increase depth.
    2. Assign using depth % 2.

For ')':
    1. It belongs to the current depth.
    2. Assign using depth % 2.
    3. Decrease depth.

This produces an optimal split.

-------------------------
Pseudo Code
-------------------------

function maxDepthAfterSplit(seq):

    ans = empty vector
    depth = 0

    for ch in seq:

        if ch == '(':
            depth++
            ans.push_back(depth % 2)

        else:
            ans.push_back(depth % 2)
            depth--

    return ans

-------------------------
Complete Optimal Code
(For revision only)
-------------------------

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans;
        int depth = 0;

        for (char ch : seq) {
            if (ch == '(') {
                depth++;
                ans.push_back(depth % 2);
            } else {
                ans.push_back(depth % 2);
                depth--;
            }
        }

        return ans;
    }
};

-------------------------
Time Complexity
-------------------------

O(n)

Each character is processed exactly once.

-------------------------
Space Complexity
-------------------------

O(n)

The answer vector stores one value for each character.

Auxiliary space excluding the returned answer: O(1).

================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:
    seq = "(()())"

Initially:
    depth = 0
    ans = []

1. '('
   depth = 1
   1 % 2 = 1
   ans = [1]

2. '('
   depth = 2
   2 % 2 = 0
   ans = [1, 0]

3. ')'
   current depth = 2
   2 % 2 = 0
   ans = [1, 0, 0]
   depth = 1

4. '('
   depth = 2
   2 % 2 = 0
   ans = [1, 0, 0, 0]

5. ')'
   current depth = 2
   2 % 2 = 0
   ans = [1, 0, 0, 0, 0]
   depth = 1

6. ')'
   current depth = 1
   1 % 2 = 1
   ans = [1, 0, 0, 0, 0, 1]
   depth = 0

Final:
    [1, 0, 0, 0, 0, 1]

================================================================================
INTERVIEW NOTES
================================================================================

-------------------------
Pattern
-------------------------

Greedy + Nesting Depth + Parity

-------------------------
Key Observation
-------------------------

Use the parity of the current nesting depth:

    depth % 2

This alternates the two groups and distributes nested parentheses evenly.

-------------------------
Common Mistakes
-------------------------

1. Returning an int instead of vector<int>.

2. Forgetting to increase depth before assigning '('.

3. Decreasing depth before assigning ')'.

4. Assigning every parenthesis to the same group.

5. Trying to construct both groups explicitly when only the assignment
   vector is required.

6. Confusing the current depth with the maximum depth.

-------------------------
When to Use This Approach
-------------------------

Use this approach when:

- A nested structure must be divided between two groups.
- The objective is to minimize maximum nesting depth.
- The current nesting level can determine the group.
- Alternating based on depth can balance the structure.

General pattern:

    Current depth parity -> Group selection

================================================================================
*/
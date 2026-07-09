#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<bool> pathExistenceQueries(int n,
                                      vector<int> &nums,
                                      int maxDiff,
                                      vector<vector<int>> &queries)
    {
        // Stores component ID for every index
        vector<int> component(n, 0);

        int id = 0;

        // Assign component IDs
        for (int i = 1; i < n; i++)
        {
            // If difference is greater than maxDiff,
            // start a new connected component.
            if (nums[i] - nums[i - 1] > maxDiff)
                id++;

            component[i] = id;
        }

        vector<bool> answer;

        // Answer each query
        for (auto &q : queries)
        {
            answer.push_back(component[q[0]] == component[q[1]]);
        }

        return answer;
    }
};

int main()
{
    Solution sol;

    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int maxDiff;
    cin >> maxDiff;

    int q;
    cin >> q;

    vector<vector<int>> queries(q, vector<int>(2));

    for (int i = 0; i < q; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }

    vector<bool> ans = sol.pathExistenceQueries(n, nums, maxDiff, queries);

    for (bool x : ans)
    {
        if (x)
            cout << "true ";
        else
            cout << "false ";
    }

    cout << endl;

    return 0;
}

/*
=========================================================
LeetCode 3532 - Path Existence Queries in a Graph I
=========================================================

BRUTE FORCE APPROACH
=========================================================

Idea:
- Treat every index as a graph node.
- Connect two indices i and j if

      abs(nums[i] - nums[j]) <= maxDiff

- Build the complete graph.
- For every query perform BFS/DFS to check whether
  destination is reachable.

Pseudo Code

Build Graph

for every i
    for every j
        if abs(nums[i]-nums[j]) <= maxDiff
            connect i and j

For every query

BFS(source,destination)

If reachable
    return true
Else
    return false

Problems
--------

• Need to compare every pair.
• Graph construction is expensive.
• BFS is repeated for every query.

Time Complexity

Building Graph : O(n²)

Each Query

O(n + E)

Overall

O(n² + q*(n+E))

Space Complexity

O(n²)

=========================================================
OPTIMAL APPROACH (USED ABOVE)
=========================================================

Observation

The array nums is already sorted.

If

nums[i] - nums[i-1] <= maxDiff

then

index i can directly connect with i-1.

Since i-1 already belongs to a connected component,
i also belongs to that same component.

Whenever

nums[i] - nums[i-1] > maxDiff

there is no possible edge between these groups.

Hence,
a new connected component starts.

Algorithm

Step 1

Create a component array.

component[i]

stores the connected component ID
of index i.

Step 2

Traverse the array once.

If adjacent difference is greater than maxDiff

start a new component.

Otherwise

continue in the same component.

Step 3

For every query

If

component[u] == component[v]

return true

Else

return false

=========================================================
Dry Run
=========================================================

Input

n = 5

nums

1 2 4 7 8

maxDiff = 2

Queries

0 2
1 3
3 4
0 4

---------------------------------

Adjacent Differences

2-1 = 1

Same Component

4-2 = 2

Same Component

7-4 = 3

Greater than maxDiff

Start New Component

8-7 = 1

Same Component

---------------------------------

Component Array

Index

0 1 2 3 4

Component

0 0 0 1 1

---------------------------------

Queries

0 2

0 == 0

true

----------------

1 3

0 != 1

false

----------------

3 4

1 == 1

true

----------------

0 4

0 != 1

false

=========================================================
Why is this Optimal?
=========================================================

✔ Only one traversal of the array.

✔ No graph construction.

✔ No BFS.

✔ No DFS.

✔ Every query answered in O(1).

=========================================================
Time Complexity
=========================================================

Creating Components

O(n)

Answering Queries

O(q)

Overall

O(n + q)

=========================================================
Space Complexity
=========================================================

Component Array

O(n)

=========================================================
Interview Tip
=========================================================

Whenever

• Array is sorted

and

• Connections depend only on adjacent values

always think about

✔ Connected Components

instead of

✔ Building the entire graph.

This reduces the complexity from O(n²)
to O(n).

=========================================================

Sample Input

5
1 2 4 7 8
2
4
0 2
1 3
3 4
0 4

Sample Output

true false true false

=========================================================
*/
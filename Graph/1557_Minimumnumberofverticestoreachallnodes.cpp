#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> &edges)
    {
        vector<bool> hasIncoming(n, false);

        for (auto &edge : edges)
        {
            hasIncoming[edge[1]] = true;
        }

        vector<int> ans;

        for (int i = 0; i < n; i++)
        {
            if (!hasIncoming[i])
            {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    int n = 6;

    vector<vector<int>> edges = {
        {0, 1},
        {0, 2},
        {2, 5},
        {3, 4},
        {4, 5}};

    vector<int> ans = obj.findSmallestSetOfVertices(n, edges);

    for (int x : ans)
        cout << x << " ";

    cout << '\n';

    return 0;
}

/*
===============================================================================
        LEETCODE 1557 - MINIMUM NUMBER OF VERTICES TO REACH ALL NODES
===============================================================================

Problem Statement:
------------------
Given a directed acyclic graph (DAG) with n nodes numbered from 0 to n-1,
find the smallest set of vertices from which all nodes in the graph are
reachable.

The graph is given as a list of directed edges.

We need to return any smallest set of starting vertices.

Example:
--------
n = 6

edges =
    [[0,1],
     [0,2],
     [2,5],
     [3,4],
     [4,5]]

Nodes with no incoming edges:

    0
    3

Answer:

    [0,3]


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Try different subsets of vertices as starting points.

For each subset:

    1. Start DFS/BFS from every vertex in the subset.
    2. Mark all reachable vertices.
    3. Check whether all n vertices are reachable.
    4. Keep the smallest valid subset.

This is essentially a subset enumeration problem and is exponential.

Therefore, it is not practical for large n.


Pseudo Code:
-----------
For every possible subset of vertices:

    visited = empty

    For every vertex in subset:
        DFS/BFS from that vertex

    If all vertices are visited:
        update minimum answer


Complete Brute Force Code:
--------------------------

class Solution {
public:

    void dfs(
        int u,
        vector<vector<int>>& graph,
        vector<bool>& visited
    ) {
        visited[u] = true;

        for (int v : graph[u]) {
            if (!visited[v]) {
                dfs(v, graph, visited);
            }
        }
    }

    vector<int> findSmallestSetOfVertices(
        int n,
        vector<vector<int>>& edges
    ) {

        vector<vector<int>> graph(n);

        for (auto &edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }

        vector<int> best;

        // Try every subset.
        for (int mask = 0; mask < (1 << n); mask++) {

            vector<int> current;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    current.push_back(i);
                }
            }

            if (!best.empty() && current.size() >= best.size())
                continue;

            vector<bool> visited(n, false);

            for (int node : current) {
                if (!visited[node]) {
                    dfs(node, graph, visited);
                }
            }

            bool allVisited = true;

            for (bool x : visited) {
                if (!x) {
                    allVisited = false;
                    break;
                }
            }

            if (allVisited) {
                best = current;
            }
        }

        return best;
    }
};


Time Complexity:
----------------
There are:

    2^N

possible subsets.

For each subset we may perform DFS:

    O(N + E)

Therefore:

    O(2^N * (N + E))

This is exponential.


Space Complexity:
-----------------
O(N + E)

For the graph and DFS visited array.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
Look at nodes with NO incoming edges.

Example:

    0 -> 1
    0 -> 2
    2 -> 5
    3 -> 4
    4 -> 5

Incoming edges:

    0 -> none
    1 -> from 0
    2 -> from 0
    3 -> none
    4 -> from 3
    5 -> from 2 and 4

So:

    0 and 3

are the only nodes with no incoming edges.


Intuition:
----------
If a node has an incoming edge:

    x -> u

then u can be reached from x.

Therefore, u does NOT necessarily need to be chosen as a starting vertex.

But if a node has no incoming edge, there is no other vertex from which
we can reach it.

Therefore, every node with indegree 0 MUST be included in the answer.

Since the graph is a DAG, starting from all indegree-0 vertices will
eventually reach every node.

Thus:

    Answer = all vertices with indegree 0


Pseudo Code:
-----------
Create an array:

    indegree[n] = 0

For every edge [u, v]:

    indegree[v]++

Create answer.

For i from 0 to n-1:

    if indegree[i] == 0:
        add i to answer

Return answer.


Complete Optimal Code:
----------------------

class Solution {
public:

    vector<int> findSmallestSetOfVertices(
        int n,
        vector<vector<int>>& edges
    ) {

        vector<bool> hasIncoming(n, false);

        for (auto &edge : edges) {
            hasIncoming[edge[1]] = true;
        }

        vector<int> ans;

        for (int i = 0; i < n; i++) {
            if (!hasIncoming[i]) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};


Time Complexity:
----------------
We traverse every edge once:

    O(E)

Then traverse all vertices:

    O(N)

Overall:

    O(N + E)


Space Complexity:
-----------------
O(N)

For the incoming-edge array.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Input:

    n = 6

    edges:
        0 -> 1
        0 -> 2
        2 -> 5
        3 -> 4
        4 -> 5


Step 1: Initialize

    hasIncoming:

    Node:       0  1  2  3  4  5
    Incoming:   F  F  F  F  F  F


Step 2: Process edges

    0 -> 1

    hasIncoming[1] = true

    0 -> 2

    hasIncoming[2] = true

    2 -> 5

    hasIncoming[5] = true

    3 -> 4

    hasIncoming[4] = true

    4 -> 5

    hasIncoming[5] = true


Final:

    Node:       0  1  2  3  4  5
    Incoming:   F  T  T  F  T  T


Nodes with no incoming edges:

    0
    3


Answer:

    [0, 3]


===============================================================================
WHY DOES THIS GIVE THE MINIMUM?
===============================================================================

Suppose node X has no incoming edge.

There is NO edge:

    anything -> X

Therefore, X cannot be reached from another node.

So X MUST be selected as a starting point.

This means every indegree-0 node is mandatory.

Now consider any node Y with at least one incoming edge:

    X -> Y

If X is reachable, then Y is also reachable.

Since all indegree-0 nodes are selected and the graph is a DAG,
following outgoing edges from them eventually reaches every node.

Therefore:

    All indegree-0 nodes
            =
    Smallest possible starting set


===============================================================================
WHY IS THE DAG CONDITION IMPORTANT?
===============================================================================

The problem guarantees that the graph is a DAG.

Consider a cycle:

    0 -> 1
    1 -> 0

Both nodes have incoming edges.

But neither can be reached from outside the cycle.

So we would need to choose at least one node from the cycle.

For a general directed graph, simply choosing indegree-0 nodes
would NOT be enough.

For a DAG, however, every connected portion has at least one
indegree-0 node, which makes the solution valid.


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Directed Graph + Indegree


Key Observation:
----------------
Every node with indegree 0 MUST be selected.

Every other node has at least one incoming edge and can potentially
be reached from another node.


Common Mistakes:
----------------
1. Checking OUTDEGREE instead of INDEGREE.

   We need:

       number of edges coming INTO a node.

2. Building the entire graph unnecessarily.

   We only need to know whether each node has an incoming edge.

3. Using topological sorting when it is not required.

   Topological sort works, but this problem has a much simpler
   O(N + E) solution.

4. Forgetting that the graph is directed.

   For:

       u -> v

   only v gets an incoming edge.

5. Assuming the answer is always node 0.

   Any node can be a starting vertex.


When to Use This Approach:
--------------------------
Use this approach when:

- The graph is directed.
- You need the minimum starting nodes to reach all nodes.
- The graph is a DAG.
- Nodes with no incoming edges cannot be reached from anywhere else.

Classic recognition:

    "Minimum vertices to reach all nodes in a DAG"

Immediately think:

    Find all indegree-0 nodes.


===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maximalPathQuality(vector<int> &values,
                           vector<vector<int>> &edges,
                           int maxTime)
    {
        int n = values.size();

        vector<vector<pair<int, int>>> graph(n);

        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            int time = e[2];

            graph[u].push_back({v, time});
            graph[v].push_back({u, time});
        }

        vector<int> visited(n, 0);
        int ans = values[0];

        function<void(int, int, int)> dfs =
            [&](int u, int time, int score)
        {
            if (time > maxTime)
                return;

            if (u == 0)
                ans = max(ans, score);

            for (auto &[v, t] : graph[u])
            {
                if (time + t > maxTime)
                    continue;

                bool firstVisit = (visited[v] == 0);

                if (firstVisit)
                    score += values[v];

                visited[v]++;

                dfs(v, time + t, score);

                visited[v]--;

                if (firstVisit)
                    score -= values[v];
            }
        };

        visited[0] = 1;
        dfs(0, 0, values[0]);

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<int> values = {0, 32, 10, 43};

    vector<vector<int>> edges = {
        {0, 1, 10},
        {1, 2, 15},
        {0, 3, 10}};

    int maxTime = 49;

    cout << obj.maximalPathQuality(values, edges, maxTime) << '\n';

    return 0;
}

/*
===============================================================================
       LEETCODE 2065 - MAXIMUM PATH QUALITY OF A GRAPH
===============================================================================

Problem Statement:
------------------
You are given an undirected weighted graph.

Each node has a value:

    values[i]

Each edge has a travel time:

    [u, v, time]

You start at node 0.

You must return to node 0 within:

    maxTime

The score of a path is the sum of values of UNIQUE nodes visited.

If a node is visited multiple times, its value is counted only once.

Find the maximum possible score.


Example:
--------
values = [0, 32, 10, 43]

edges =
    [[0,1,10],
     [1,2,15],
     [0,3,10]]

maxTime = 49

Possible path:

    0 -> 1 -> 2 -> 1 -> 0

Time:

    10 + 15 + 15 + 10 = 50

Too much.

Another path:

    0 -> 3 -> 0

Time:

    10 + 10 = 20

Score:

    0 + 43 = 43

Answer:

    43


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Try every possible path starting from node 0.

At every node:

    1. Choose any adjacent node.
    2. Move there if enough time remains.
    3. Continue recursively.
    4. Whenever we return to node 0, update the answer.

The graph contains cycles, so nodes may be visited multiple times.

However, the total time is bounded by maxTime, so we only explore paths
that can actually be completed within the time limit.


Pseudo Code:
-----------
DFS(u, time, score):

    If time > maxTime:
        return

    If u == 0:
        update answer

    For every neighbor v:

        If time + edgeTime <= maxTime:

            Add value[v] if v has not been visited before

            DFS(v, newTime, newScore)

            Remove value[v] if this was its first visit


Complete Brute Force Code:
--------------------------

class Solution {
public:

    int ans = 0;

    void dfs(
        int u,
        int time,
        int score,
        vector<int>& values,
        vector<vector<pair<int,int>>>& graph,
        vector<int>& visited,
        int maxTime
    ) {

        if (time > maxTime)
            return;

        if (u == 0)
            ans = max(ans, score);

        for (auto &[v, t] : graph[u]) {

            if (time + t > maxTime)
                continue;

            bool firstVisit = (visited[v] == 0);

            if (firstVisit)
                score += values[v];

            visited[v]++;

            dfs(
                v,
                time + t,
                score,
                values,
                graph,
                visited,
                maxTime
            );

            visited[v]--;

            if (firstVisit)
                score -= values[v];
        }
    }

    int maximalPathQuality(
        vector<int>& values,
        vector<vector<int>>& edges,
        int maxTime
    ) {

        int n = values.size();

        vector<vector<pair<int,int>>> graph(n);

        for (auto &e : edges) {

            int u = e[0];
            int v = e[1];
            int t = e[2];

            graph[u].push_back({v, t});
            graph[v].push_back({u, t});
        }

        vector<int> visited(n, 0);

        visited[0] = 1;

        dfs(
            0,
            0,
            values[0],
            values,
            graph,
            visited,
            maxTime
        );

        return ans;
    }
};


Time Complexity:
----------------
The number of possible paths can be exponential in the number of
edges/time steps.

Worst case is approximately:

    O(N^K)

where K depends on how many edges can be traversed within maxTime.

The important point is that this is exponential.


Space Complexity:
-----------------
O(N + K)

For:

    graph
    visited array
    recursion stack


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
The graph is undirected.

Therefore, we can:

    move from u -> v

and later:

    move from v -> u

This allows us to visit valuable nodes and return to node 0.

The important constraint is:

    total travel time <= maxTime


The score is NOT the sum of every visit.

Instead:

    each node's value is counted only the FIRST time we visit it.


Therefore, during DFS we maintain:

    visited[v]

If:

    visited[v] == 0

then v is being visited for the first time, so:

    score += values[v]


If we visit v again:

    score does not change.


Intuition:
----------
Consider:

    0 -> 1 -> 2 -> 1 -> 0

Suppose:

    values[0] = 0
    values[1] = 10
    values[2] = 20

The score is:

    0 + 10 + 20

NOT:

    0 + 10 + 20 + 10 + 0

because node 1 is visited twice and node 0 is also revisited.

So the DFS needs two independent pieces of information:

    1. How many times each node has been visited
       -> to calculate unique-node score.

    2. Current elapsed time
       -> to ensure we can stay within maxTime.


Why Can We Revisit Nodes?
-------------------------
Because revisiting a node may be necessary to return to node 0.

Example:

    0 -- 1 -- 2

To collect the value at 2, we must do:

    0 -> 1 -> 2 -> 1 -> 0

Therefore, we cannot use a normal visited[] that permanently blocks
already visited nodes.

Instead:

    visited[v]++

when entering v.

Then:

    visited[v]--

when backtracking.


Pseudo Code:
-----------
Build adjacency list.

visited[0] = 1

DFS(u, time, score):

    If u == 0:
        answer = max(answer, score)

    For every edge u -> v:

        newTime = time + edgeTime

        If newTime > maxTime:
            continue

        If visited[v] == 0:
            score += values[v]

        visited[v]++

        DFS(v, newTime, score)

        visited[v]--

        If visited[v] == 0:
            score -= values[v]

Return answer.


Complete Optimal Code:
----------------------

class Solution {
public:

    int maximalPathQuality(
        vector<int>& values,
        vector<vector<int>>& edges,
        int maxTime
    ) {

        int n = values.size();

        vector<vector<pair<int,int>>> graph(n);

        for (auto &e : edges) {

            int u = e[0];
            int v = e[1];
            int t = e[2];

            graph[u].push_back({v, t});
            graph[v].push_back({u, t});
        }

        vector<int> visited(n, 0);

        int ans = values[0];

        function<void(int,int,int)> dfs =
            [&](int u, int time, int score) {

            if (time > maxTime)
                return;

            if (u == 0)
                ans = max(ans, score);

            for (auto &[v, t] : graph[u]) {

                if (time + t > maxTime)
                    continue;

                bool firstVisit = (visited[v] == 0);

                if (firstVisit)
                    score += values[v];

                visited[v]++;

                dfs(
                    v,
                    time + t,
                    score
                );

                visited[v]--;

                if (firstVisit)
                    score -= values[v];
            }
        };

        visited[0] = 1;

        dfs(
            0,
            0,
            values[0]
        );

        return ans;
    }
};


Time Complexity:
----------------
The solution explores all feasible paths whose total travel time is
at most maxTime.

Because revisiting is allowed, the worst-case number of paths is
exponential.

With the problem's constraints, this DFS/backtracking approach is
intended and efficient enough.

A common way to express the worst case is:

    O(N^K)

where K is the maximum number of edges that can be traversed within
maxTime.


Space Complexity:
-----------------
O(N)

for:

    adjacency list
    visited array
    recursion stack

More precisely, the recursion depth is bounded by the number of
edge traversals possible within maxTime.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

values:

    [0, 32, 10, 43]

edges:

    0 --1 (10)
    1 --2 (15)
    0 --3 (10)

maxTime = 49


Initial:

    position = 0
    time = 0
    score = 0

visited:

    [1, 0, 0, 0]


Move:

    0 -> 1

Time:

    10

Node 1 is visited for the first time.

Score:

    0 + 32 = 32


Move:

    1 -> 2

Time:

    10 + 15 = 25

Node 2 is new.

Score:

    32 + 10 = 42


Now return:

    2 -> 1

Time:

    25 + 15 = 40

Node 1 was already visited.

Score remains:

    42


Now:

    1 -> 0

Time:

    40 + 10 = 50

But:

    50 > 49

So this path cannot return to 0 within maxTime.


Backtrack.


Try:

    0 -> 3

Time:

    10

Node 3 is new.

Score:

    43


Then:

    3 -> 0

Time:

    20

We are back at node 0.

Update:

    ans = max(0, 43)

Therefore:

    ans = 43


Final Answer:

    43


===============================================================================
IMPORTANT: WHY DO WE UPDATE ONLY WHEN u == 0?
===============================================================================

The path must START at node 0 and END at node 0.

Therefore, reaching another node with a high score is not enough.

Example:

    0 -> 1 -> 2

Suppose score = 100 at node 2.

If there is not enough time to return:

    2 -> 1 -> 0

then this is NOT a valid final path.

Therefore:

    if (u == 0)
        ans = max(ans, score);

is essential.


===============================================================================
WHY DON'T WE USE A NORMAL visited[] BOOLEAN?
===============================================================================

A normal DFS often does:

    visited[v] = true

and never visits v again.

That would be WRONG here.

Example:

    0 -> 1 -> 2 -> 1 -> 0

Node 1 must be visited twice to return to 0.

So we use a visit COUNT:

    visited[v]++

on entry.

And:

    visited[v]--

on backtracking.

This allows revisiting while still knowing whether the node's value
should be counted.


===============================================================================
WHY IS THE VALUE ADDED ONLY ON FIRST VISIT?
===============================================================================

Suppose:

    values[1] = 50

Path:

    0 -> 1 -> 0 -> 1 -> 0

Node 1 is visited twice.

Its value should be counted only once:

    score = 50

not:

    score = 100


Therefore:

    if (visited[v] == 0)
        score += values[v];

The first visit contributes the value.

Every later visit contributes:

    0


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Graph + DFS + Backtracking + Visit Count


Key Observation:
----------------
The score depends on UNIQUE nodes, while the time depends on EVERY
edge traversal.

Therefore we need to track:

    visited[node] -> how many times node has been visited

and:

    time -> total travel time so far


Common Mistakes:
----------------
1. Using a boolean visited array that permanently prevents revisiting.

   WRONG because the path may need to return through an already visited
   node.

2. Adding values every time a node is visited.

   WRONG.

   Values are counted only once.

3. Updating the answer at every node.

   WRONG.

   The path is valid only when we return to node 0.

4. Forgetting that the graph is undirected.

   Every edge:

       u -- v

   must be stored both ways.

5. Forgetting to backtrack:

       visited[v]--

   Without this, the visited state of one DFS branch affects another.

6. Adding the value before checking whether this is the first visit.

7. Not pruning paths whose time already exceeds maxTime.

8. Thinking this is a shortest-path problem.

   It is not.

   We are maximizing UNIQUE node values under a time constraint.


When to Use This Approach:
--------------------------
Use DFS + backtracking when:

- The graph is relatively small.
- You need to explore many possible paths.
- There is a strict resource constraint such as time.
- Nodes can be revisited.
- The objective depends on unique nodes visited.
- You need to return to a starting node.

Recognition pattern:

    "Start at node 0"
    +
    "Return to node 0"
    +
    "Total time <= limit"
    +
    "Maximize sum of UNIQUE node values"

Think:

    DFS + Backtracking + visited count


===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// LeetCode 1129: Shortest Path with Alternating Colors
class Solution
{
public:
    vector<int> shortestAlternatingPaths(
        int n,
        vector<vector<int>> &redEdges,
        vector<vector<int>> &blueEdges)
    {
        vector<vector<pair<int, int>>> graph(n);

        // type = 0 -> red
        // type = 1 -> blue
        for (auto &e : redEdges)
        {
            graph[e[0]].push_back({e[1], 0});
        }

        for (auto &e : blueEdges)
        {
            graph[e[0]].push_back({e[1], 1});
        }

        // dist[node][color]
        // color = 0 -> reached node using red edge
        // color = 1 -> reached node using blue edge
        vector<vector<int>> dist(n, vector<int>(2, -1));

        queue<pair<int, int>> q;

        // Start can take either color as the first edge.
        dist[0][0] = 0;
        dist[0][1] = 0;

        q.push({0, 0});
        q.push({0, 1});

        while (!q.empty())
        {
            auto [node, lastColor] = q.front();
            q.pop();

            for (auto [next, edgeColor] : graph[node])
            {

                // We must alternate colors.
                if (edgeColor == lastColor)
                    continue;

                if (dist[next][edgeColor] != -1)
                    continue;

                dist[next][edgeColor] =
                    dist[node][lastColor] + 1;

                q.push({next, edgeColor});
            }
        }

        vector<int> ans(n);

        for (int i = 0; i < n; ++i)
        {
            if (dist[i][0] == -1)
            {
                ans[i] = dist[i][1];
            }
            else if (dist[i][1] == -1)
            {
                ans[i] = dist[i][0];
            }
            else
            {
                ans[i] = min(dist[i][0], dist[i][1]);
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    int n = 3;

    vector<vector<int>> redEdges = {
        {0, 1}};

    vector<vector<int>> blueEdges = {
        {1, 2}};

    vector<int> ans =
        sol.shortestAlternatingPaths(
            n,
            redEdges,
            blueEdges);

    for (int x : ans)
    {
        cout << x << " ";
    }

    cout << '\n';

    return 0;
}

/*
======================================================================
                    LEETCODE 1129
             SHORTEST PATH WITH ALTERNATING COLORS
======================================================================


PROBLEM STATEMENT
-----------------

You are given a directed graph with:

    n nodes numbered from 0 to n - 1.

There are two types of edges:

    redEdges
    blueEdges

We need to find the shortest path from node 0 to every node.

The path must follow this rule:

    Consecutive edges must have different colors.

So valid paths look like:

    Red -> Blue -> Red -> Blue ...

or:

    Blue -> Red -> Blue -> Red ...


Return an array where:

    ans[i] = shortest alternating path length
             from node 0 to node i.

If node i cannot be reached using an alternating-color path:

    ans[i] = -1.


======================================================================
EXAMPLE
======================================================================

Input:

    n = 3

    redEdges = {
        {0, 1}
    }

    blueEdges = {
        {1, 2}
    }


Graph:

    0 --RED--> 1 --BLUE--> 2


Path:

    0 -> 1 -> 2

Colors:

    RED -> BLUE

Colors alternate.

Therefore:

    ans[0] = 0
    ans[1] = 1
    ans[2] = 2


Output:

    {0, 1, 2}


======================================================================
BRUTE FORCE APPROACH
======================================================================


IDEA
----

We can try every possible alternating path starting from node 0.

At every node, we keep track of:

    - Current node
    - Last edge color
    - Number of edges used

We can use DFS to explore all valid alternating paths.

However, the same state can be reached multiple times.

Therefore, we need to keep track of visited states:

    (node, lastColor)


For every state, we update the shortest distance.


PSEUDO CODE
-----------

DFS(node, lastColor, distance):

    update answer[node]

    for every outgoing edge:

        if edge color == lastColor:
            skip

        if state (next, edgeColor) already visited:
            skip

        mark state visited

        DFS(next, edgeColor, distance + 1)


Start with both possibilities:

    DFS(0, RED)
    DFS(0, BLUE)


because the first edge can be either red or blue.


COMPLETE BRUTE FORCE CODE
-------------------------

// class Solution {
//     vector<vector<pair<int, int>>> graph;
//     vector<vector<bool>> visited;
//     vector<int> ans;
//
//     void dfs(int node, int lastColor, int dist) {
//
//         ans[node] = min(ans[node], dist);
//
//         for (auto [next, edgeColor] : graph[node]) {
//
//             if (edgeColor == lastColor)
//                 continue;
//
//             if (visited[next][edgeColor])
//                 continue;
//
//             visited[next][edgeColor] = true;
//
//             dfs(
//                 next,
//                 edgeColor,
//                 dist + 1
//             );
//         }
//     }
//
// public:
//     vector<int> shortestAlternatingPaths(
//         int n,
//         vector<vector<int>>& redEdges,
//         vector<vector<int>>& blueEdges
//     ) {
//
//         graph.assign(n, {});
//
//         for (auto& e : redEdges) {
//             graph[e[0]].push_back({e[1], 0});
//         }
//
//         for (auto& e : blueEdges) {
//             graph[e[0]].push_back({e[1], 1});
//         }
//
//         visited.assign(
//             n,
//             vector<bool>(2, false)
//         );
//
//         ans.assign(n, INT_MAX);
//
//         // First edge can be either color.
//
//         visited[0][0] = true;
//         dfs(0, 0, 0);
//
//         visited[0][1] = true;
//         dfs(0, 1, 0);
//
//         for (int i = 0; i < n; ++i) {
//
//             if (ans[i] == INT_MAX)
//                 ans[i] = -1;
//         }
//
//         return ans;
//     }
// };


TIME COMPLEXITY
----------------

There are:

    N * 2

possible states:

    (node, lastColor)

Each state processes its outgoing edges.

So approximately:

    O(N + E)

where:

    E = total number of red and blue edges.


SPACE COMPLEXITY
----------------

Graph:

    O(N + E)

Visited:

    O(N)

Recursion stack:

    O(N)

Therefore:

    O(N + E)


NOTE:
-----

Although this DFS solution with state tracking can work, BFS is
more natural because this is explicitly a shortest-path problem
with every edge having cost 1.


======================================================================
OPTIMAL APPROACH
======================================================================


OBSERVATION
-----------

This is an unweighted shortest-path problem.

Every edge costs:

    1


Therefore:

                    BFS

is the natural choice.


BUT THERE IS A TWIST
--------------------

Normal BFS state would be:

    node


But that is not enough.

Suppose we reach node 2.

The next edge depends on the color of the edge we just used.

For example:

    If we reached node 2 using RED,

then the next edge must be:

    BLUE.


If we reached node 2 using BLUE,

then the next edge must be:

    RED.


Therefore, the state must be:

    (node, lastColor)


This is the KEY OBSERVATION.


STATE
-----

We maintain:

    dist[node][color]


Meaning:

    shortest distance to node when the last edge used
    has the specified color.


Use:

    color = 0 -> RED
    color = 1 -> BLUE


INITIALIZATION
--------------

At node 0, we have not used any edge yet.

Therefore, the first edge can be either color.

So we initialize:

    dist[0][0] = 0
    dist[0][1] = 0


and push both states into the queue.


TRANSITION
----------

Suppose current state is:

    (node, lastColor)


For every outgoing edge:

    (node -> next, edgeColor)


We can use it only if:

    edgeColor != lastColor


Then:

    dist[next][edgeColor]
        =
    dist[node][lastColor] + 1


Finally, for every node:

    ans[node] =
        min(
            dist[node][RED],
            dist[node][BLUE]
        )


======================================================================
PSEUDO CODE
======================================================================


Create adjacency list:

    graph[node] = {
        (neighbor, color)
    }


Create:

    dist[n][2] = -1


Initialize:

    dist[0][RED] = 0
    dist[0][BLUE] = 0


Push:

    (0, RED)
    (0, BLUE)


while queue is not empty:

    current = queue.front()
    queue.pop()

    node = current.node
    lastColor = current.color

    for every edge:

        next = edge.destination
        edgeColor = edge.color

        if edgeColor == lastColor:
            continue

        if dist[next][edgeColor] != -1:
            continue

        dist[next][edgeColor] =
            dist[node][lastColor] + 1

        push(next, edgeColor)


For every node:

    if one color is unreachable:
        use the other

    otherwise:
        take minimum

Return answer.


======================================================================
COMPLETE OPTIMAL CODE
======================================================================

// class Solution {
// public:
//     vector<int> shortestAlternatingPaths(
//         int n,
//         vector<vector<int>>& redEdges,
//         vector<vector<int>>& blueEdges
//     ) {
//
//         vector<vector<pair<int, int>>> graph(n);
//
//         // 0 = RED
//         // 1 = BLUE
//
//         for (auto& e : redEdges) {
//             graph[e[0]].push_back({e[1], 0});
//         }
//
//         for (auto& e : blueEdges) {
//             graph[e[0]].push_back({e[1], 1});
//         }
//
//         vector<vector<int>> dist(
//             n,
//             vector<int>(2, -1)
//         );
//
//         queue<pair<int, int>> q;
//
//         dist[0][0] = 0;
//         dist[0][1] = 0;
//
//         q.push({0, 0});
//         q.push({0, 1});
//
//         while (!q.empty()) {
//
//             auto [node, lastColor] = q.front();
//             q.pop();
//
//             for (auto [next, edgeColor] : graph[node]) {
//
//                 // Colors must alternate.
//                 if (edgeColor == lastColor)
//                     continue;
//
//                 // Already reached this state.
//                 if (dist[next][edgeColor] != -1)
//                     continue;
//
//                 dist[next][edgeColor] =
//                     dist[node][lastColor] + 1;
//
//                 q.push({
//                     next,
//                     edgeColor
//                 });
//             }
//         }
//
//         vector<int> ans(n);
//
//         for (int i = 0; i < n; ++i) {
//
//             if (dist[i][0] == -1) {
//                 ans[i] = dist[i][1];
//             }
//             else if (dist[i][1] == -1) {
//                 ans[i] = dist[i][0];
//             }
//             else {
//                 ans[i] = min(
//                     dist[i][0],
//                     dist[i][1]
//                 );
//             }
//         }
//
//         return ans;
//     }
// };


TIME COMPLEXITY
----------------

Each state is:

    (node, color)

There are only:

    2N

states.

Each edge is processed a constant number of times.

Therefore:

    O(N + E)

where:

    N = number of nodes
    E = number of red + blue edges.


SPACE COMPLEXITY
----------------

Adjacency list:

    O(N + E)

Distance array:

    O(N)

Queue:

    O(N)


Therefore:

    O(N + E)


======================================================================
DRY RUN WITH EXAMPLE
======================================================================


Input:

    n = 3

    redEdges = {
        {0, 1}
    }

    blueEdges = {
        {1, 2}
    }


Graph:

    0 --RED--> 1 --BLUE--> 2


INITIALIZATION
--------------

We start at node 0.

The first edge can be either RED or BLUE.

Therefore:

    dist[0][RED]  = 0
    dist[0][BLUE] = 0


Queue:

    (0, RED)
    (0, BLUE)


STEP 1
------

Pop:

    (0, RED)


Outgoing edge:

    0 -> 1 RED


But:

    lastColor = RED
    edgeColor = RED


Same color.

So we cannot use this edge.


Next:

    (0, BLUE)


Outgoing edge:

    0 -> 1 RED


Now:

    lastColor = BLUE
    edgeColor = RED


Different colors.

So we can use it.

Set:

    dist[1][RED] = 1


Queue:

    (1, RED)


STEP 2
------

Pop:

    (1, RED)


Outgoing edge:

    1 -> 2 BLUE


Colors:

    RED -> BLUE


Valid.


Set:

    dist[2][BLUE] = 2


Queue:

    (2, BLUE)


STEP 3
------

Pop:

    (2, BLUE)


No useful outgoing edges.


Final distance table:

              RED     BLUE

    0          0        0
    1          1       -1
    2         -1        2


For every node, take the minimum reachable value.


Answer:

    node 0 -> 0
    node 1 -> 1
    node 2 -> 2


Final:

    {0, 1, 2}


======================================================================
INTERVIEW NOTES
======================================================================


PATTERN
-------

BFS + State Expansion


KEY OBSERVATION
---------------

Normal BFS with only:

    visited[node]

is WRONG.


Why?

Because reaching the same node using different colors gives
different future possibilities.


For example:

    Reaching X with RED

means:

    next edge must be BLUE.


But:

    Reaching X with BLUE

means:

    next edge must be RED.


Therefore the real state is:

    (node, lastColor)


COMMON MISTAKES
---------------

1. Using only:

       visited[node]

   This can incorrectly discard a valid path.


2. Forgetting to track the color of the previous edge.


3. Allowing:

       RED -> RED

   or:

       BLUE -> BLUE


   The colors must alternate.


4. Starting BFS with only one color.

   The first edge can be either RED or BLUE.


5. Forgetting:

       dist[0][RED] = 0
       dist[0][BLUE] = 0


6. Taking only one of the two distances.

   The answer is:

       min(
           dist[node][RED],
           dist[node][BLUE]
       )


7. Using Dijkstra.

   Every edge has equal cost 1, so BFS is enough.


8. Treating red and blue edges as completely separate graphs.

   They need to be combined into one graph while storing the
   edge color.


======================================================================
WHEN TO USE THIS APPROACH
======================================================================


Use this pattern when:

    - The graph is unweighted.
    - We need a shortest path.
    - There is an additional condition based on the previous edge.
    - The next move depends on some property of the previous move.


Typical examples:

    - Alternating red/blue edges
    - Alternating parity
    - Alternating direction
    - Cannot use the same edge type twice
    - State-dependent shortest paths
    - Graph problems where the previous action matters


GENERAL STATE EXPANSION IDEA
----------------------------

If the next move depends on some previous information:

    Normal state:

        node


may become:

    Expanded state:

        (node, previousInformation)


For this problem:

    previousInformation = previous edge color


So:

    state = (node, lastColor)


======================================================================
ONE-LINE INTERVIEW EXPLANATION
======================================================================

"I use BFS because every edge has unit cost, but the state must
include the last edge color because the next edge has to alternate.
I therefore run BFS on states (node, lastColor), initialize both
colors at node 0, and take the minimum distance for each node."


======================================================================
FINAL TEMPLATE TO REMEMBER
======================================================================


              UNWEIGHTED GRAPH
                      |
                      v
                     BFS
                      |
                      v
          Does next move depend
          on previous information?
                      |
                     YES
                      |
                      v
             Expand the state
                      |
                      v
          (node, previousState)
                      |
                      v
             Shortest distance


For LeetCode 1129:

    State = (node, lastColor)

    Transition only when:

        nextColor != lastColor


======================================================================
*/
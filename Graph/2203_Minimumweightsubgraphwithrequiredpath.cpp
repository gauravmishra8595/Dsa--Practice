#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;
    const ll INF = 4e18;

    vector<ll> dijkstra(int src, const vector<vector<pair<int, int>>>& graph) {
        int n = graph.size();
        vector<ll> dist(n, INF);
        priority_queue<pair<ll, int>,
                       vector<pair<ll, int>>,
                       greater<pair<ll, int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (auto [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }

    long long minimumWeight(
        int n,
        vector<vector<int>>& edges,
        int src1,
        int src2,
        int dest
    ) {
        vector<vector<pair<int, int>>> graph(n), reverseGraph(n);

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].push_back({v, w});
            reverseGraph[v].push_back({u, w});
        }

        vector<ll> d1 = dijkstra(src1, graph);
        vector<ll> d2 = dijkstra(src2, graph);
        vector<ll> dd = dijkstra(dest, reverseGraph);

        ll ans = INF;

        // Merge both paths at node i:
        // src1 -> i -> dest
        // src2 -> i -> dest
        for (int i = 0; i < n; i++) {
            if (d1[i] == INF || d2[i] == INF || dd[i] == INF)
                continue;

            ans = min(ans, d1[i] + d2[i] + dd[i]);
        }

        return ans == INF ? -1 : ans;
    }
};

int main() {
    Solution sol;

    int n = 6;
    vector<vector<int>> edges = {
        {0, 2, 2},
        {0, 3, 8},
        {2, 4, 2},
        {2, 3, 4},
        {3, 5, 3},
        {4, 5, 2},
        {1, 2, 1}
    };

    int src1 = 0;
    int src2 = 1;
    int dest = 5;

    cout << sol.minimumWeight(n, edges, src1, src2, dest) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 2203 - COMPLETE NOTES
================================================================================

Problem Statement:
------------------
You are given a directed weighted graph with n nodes numbered 0 to n-1.

You are also given:
    src1 = source of the first path
    src2 = source of the second path
    dest = common destination

Find the minimum total weight of a subgraph such that:
    1. There is a path from src1 to dest.
    2. There is a path from src2 to dest.

Edges can be shared by both paths.

Return the minimum possible total weight.
If it is impossible, return -1.

Important:
-----------
The two paths are allowed to merge at some intermediate node.

The answer is NOT necessarily:
    shortest(src1, dest) + shortest(src2, dest)

because the two shortest paths may share some edges.

--------------------------------------------------------------------------------
Example:
--------------------------------------------------------------------------------

n = 6

edges =
[
    [0,2,2],
    [0,3,8],
    [2,4,2],
    [2,3,4],
    [3,5,3],
    [4,5,2],
    [1,2,1]
]

src1 = 0
src2 = 1
dest = 5

One optimal solution is:

src1 -> 2 -> 4 -> 5
src2 -> 2 -> 4 -> 5

Weights:
    src1 -> 2 = 2
    src2 -> 2 = 1
    2 -> 4   = 2
    4 -> 5   = 2

Total = 2 + 1 + 2 + 2 = 7

Answer = 7


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
------
We can think about every possible meeting node i.

If both paths meet at i, then the cost is:

    shortest(src1, i)
  + shortest(src2, i)
  + shortest(i, dest)

So technically the same mathematical formula can be used.

A brute-force implementation can run Dijkstra separately for every
possible meeting node i to calculate the three required shortest paths.

This is intentionally inefficient and is useful only for understanding
the optimal observation.

Pseudo Code:
------------
    answer = INF

    for every node i:
        d1 = shortestPath(src1, i)
        d2 = shortestPath(src2, i)
        d3 = shortestPath(i, dest)

        if all three paths exist:
            answer = min(answer, d1 + d2 + d3)

    if answer == INF:
        return -1

    return answer


Complete Brute Force Code:
--------------------------

/*
class Solution {
public:
    using ll = long long;
    const ll INF = 4e18;

    ll dijkstra(
        int src,
        int target,
        const vector<vector<pair<int,int>>>& graph
    ) {
        int n = graph.size();

        vector<ll> dist(n, INF);

        priority_queue<
            pair<ll,int>,
            vector<pair<ll,int>>,
            greater<pair<ll,int>>
        > pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u])
                continue;

            if (u == target)
                return d;

            for (auto [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return INF;
    }

    long long minimumWeight(
        int n,
        vector<vector<int>>& edges,
        int src1,
        int src2,
        int dest
    ) {
        vector<vector<pair<int,int>>> graph(n);

        for (auto &e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
        }

        ll answer = INF;

        for (int i = 0; i < n; i++) {
            ll d1 = dijkstra(src1, i, graph);
            ll d2 = dijkstra(src2, i, graph);
            ll d3 = dijkstra(i, dest, graph);

            if (d1 == INF || d2 == INF || d3 == INF)
                continue;

            answer = min(answer, d1 + d2 + d3);
        }

        return answer == INF ? -1 : answer;
    }
};
*/


// Time Complexity:
// ----------------
// There are O(V) possible meeting nodes.

// Each Dijkstra takes:

//     O((V + E) log V)

// Running it O(V) times gives:

//     O(V * (V + E) log V)

// This is too slow for the constraints.


// Space Complexity:
// -----------------
// Graph + Dijkstra structures:

//     O(V + E)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The two paths can share a suffix.

// Suppose both paths meet at node i.

// Then the minimum cost is:

//     dist(src1, i)
//   + dist(src2, i)
//   + dist(i, dest)

// We need these distances for EVERY node i.

// Instead of running Dijkstra for every i, calculate all required distances
// with only THREE Dijkstra runs.

// 1. Dijkstra from src1:
//        gives dist(src1, i) for every i.

// 2. Dijkstra from src2:
//        gives dist(src2, i) for every i.

// 3. Dijkstra from dest on the REVERSED graph:
//        gives dist(i, dest) for every i.

// Why reverse the graph?
// ----------------------
// Suppose the original graph contains:

//     i ----w----> dest

// After reversing:

//     dest ----w----> i

// Therefore, running Dijkstra from dest in the reversed graph calculates:

//     dist(dest, i in reversed graph)
//         =
//     dist(i, dest in original graph)

// This gives us all three required distances.

// Intuition:
// ----------
// Imagine choosing a meeting node i.

// The final subgraph can look like:

//         src1
//           \
//            \
//             i --------> dest
//            /
//           /
//         src2

// The two source paths are independent until i.

// After i, both can use the SAME path to dest.

// Therefore:

//     cost(i) =
//         src1 -> i
//       + src2 -> i
//       + i -> dest

// We simply try every possible i and take the minimum.

// Pseudo Code:
// ------------
//     Build:
//         graph
//         reverseGraph

//     d1 = Dijkstra(src1, graph)

//     d2 = Dijkstra(src2, graph)

//     dd = Dijkstra(dest, reverseGraph)

//     answer = INF

//     for every node i:
//         if d1[i], d2[i], and dd[i] are reachable:
//             answer = min(
//                 answer,
//                 d1[i] + d2[i] + dd[i]
//             )

//     if answer == INF:
//         return -1

//     return answer


// Complete Optimal Code:
// ----------------------

/*
class Solution {
public:
    using ll = long long;
    const ll INF = 4e18;

    vector<ll> dijkstra(
        int src,
        const vector<vector<pair<int,int>>>& graph
    ) {
        int n = graph.size();

        vector<ll> dist(n, INF);

        priority_queue<
            pair<ll,int>,
            vector<pair<ll,int>>,
            greater<pair<ll,int>>
        > pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u])
                continue;

            for (auto [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }

    long long minimumWeight(
        int n,
        vector<vector<int>>& edges,
        int src1,
        int src2,
        int dest
    ) {
        vector<vector<pair<int,int>>> graph(n);
        vector<vector<pair<int,int>>> reverseGraph(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            graph[u].push_back({v, w});
            reverseGraph[v].push_back({u, w});
        }

        vector<ll> d1 = dijkstra(src1, graph);
        vector<ll> d2 = dijkstra(src2, graph);

        // Gives dist(i, dest) in the original graph.
        vector<ll> dd = dijkstra(dest, reverseGraph);

        ll answer = INF;

        for (int i = 0; i < n; i++) {
            if (d1[i] == INF ||
                d2[i] == INF ||
                dd[i] == INF) {
                continue;
            }

            answer = min(
                answer,
                d1[i] + d2[i] + dd[i]
            );
        }

        return answer == INF ? -1 : answer;
    }
};
*/


// Time Complexity:
// ----------------
// Three Dijkstra runs:

//     3 * O((V + E) log V)

// Therefore:

//     O((V + E) log V)

// The final loop over all meeting nodes costs:

//     O(V)

// Overall:

//     O((V + E) log V)


// Space Complexity:
// -----------------
// Two adjacency lists:

//     O(V + E)

// Three distance arrays:

//     O(V)

// Priority queue:

//     O(E) in the worst case

// Overall:

//     O(V + E)


// ================================================================================
// DRY RUN
// ================================================================================

// Example:

// src1 = 0
// src2 = 1
// dest = 5

// Consider meeting node:

//     i = 2

// Distances:

//     dist(src1, 2) = dist(0, 2) = 2
//     dist(src2, 2) = dist(1, 2) = 1
//     dist(2, dest) = dist(2, 5) = 4

// Therefore:

//     cost(2)
//     = 2 + 1 + 4
//     = 7

// Now consider meeting node:

//     i = 4

// Distances:

//     dist(0, 4) = 4
//     dist(1, 4) = 3
//     dist(4, 5) = 2

// Therefore:

//     cost(4)
//     = 4 + 3 + 2
//     = 9

// So node 2 is better.

// The algorithm checks every possible meeting node and obtains:

//     minimum = 7

// Hence:

//     Answer = 7


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// - Shortest Path
// - Dijkstra
// - Multiple Sources
// - Reverse Graph
// - Shared Path / Meeting Node
// - DAG-like path merging intuition

// Key Observation:
// ----------------
// The two source paths can merge at an intermediate node i.

// Therefore:

//     answer =
//         min over i [
//             dist(src1, i)
//           + dist(src2, i)
//           + dist(i, dest)
//         ]

// The important trick is calculating dist(i, dest) for ALL i.

// Reverse the graph and run Dijkstra from dest.

// Common Mistakes:
// ----------------
// 1. Simply calculating:

//        shortest(src1, dest) + shortest(src2, dest)

//    This can double-count shared edges.

// 2. Forgetting to reverse the graph for the third Dijkstra.

// 3. Using int instead of long long.

//    Path sums can exceed the int range.

// 4. Forgetting the unreachable-node check.

// 5. Assuming the two paths must merge at a particular node.

//    The meeting node can be ANY node, including:
//        src1
//        src2
//        dest

// 6. Using Dijkstra on the original graph from dest to calculate
//    dist(i, dest).

//    That would give dist(dest, i), which is generally different in
//    a directed graph.

// When to use this approach:
// --------------------------
// Use this pattern when:

// - The graph is directed and weighted with non-negative weights.
// - Multiple sources need to reach a common destination.
// - Paths are allowed to share edges.
// - The answer can be represented by choosing a common meeting/merge node.
// - You need shortest distances from several fixed sources to every node.
// - You need distances from every node TO a fixed destination.

// General Template:

//     source1 -> meeting node
//     source2 -> meeting node
//                    |
//                    v
//                 destination

// Use:

//     Dijkstra(source1, graph)
//     Dijkstra(source2, graph)
//     Dijkstra(destination, reversed graph)

// Then:

//     min(
//         d1[i] + d2[i] + dDest[i]
//     )

// for every node i.

// ================================================================================
// */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        const int INF = 1e9;
        int answer = -1;
        int minCount = INF;

        for (int src = 0; src < n; src++) {
            vector<int> dist(n, INF);

            priority_queue<
                pair<int, int>,
                vector<pair<int, int>>,
                greater<pair<int, int>>
            > pq;

            dist[src] = 0;
            pq.push({0, src});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d != dist[u])
                    continue;

                for (auto [v, w] : adj[u]) {
                    if (dist[v] > d + w) {
                        dist[v] = d + w;
                        pq.push({dist[v], v});
                    }
                }
            }

            int count = 0;

            for (int city = 0; city < n; city++) {
                if (city != src && dist[city] <= distanceThreshold) {
                    count++;
                }
            }

            // >= ensures larger city wins in case of a tie.
            if (count <= minCount) {
                minCount = count;
                answer = src;
            }
        }

        return answer;
    }
};

int main() {
    Solution sol;

    int n = 4;

    vector<vector<int>> edges = {
        {0, 1, 3},
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 1}
    };

    int distanceThreshold = 4;

    cout << sol.findTheCity(n, edges, distanceThreshold) << '\n';

    return 0;
}

/*
================================================================================
                 LEETCODE 1334 - COMPLETE CP NOTEBOOK
================================================================================

Problem Statement:
------------------
There are n cities numbered from 0 to n - 1.

You are given an undirected weighted graph where:

    edges[i] = [u, v, weight]

means there is a bidirectional road between city u and city v with
the given weight.

You are also given:

    distanceThreshold

For every city, find how many other cities can be reached using a path
whose total distance is less than or equal to distanceThreshold.

Return the city with the smallest number of reachable cities.

If multiple cities have the same number of reachable cities, return the
city with the greatest number.


--------------------------------------------------------------------------------
Example:
--------------------------------------------------------------------------------

n = 4

edges =
[
    [0,1,3],
    [1,2,1],
    [1,3,4],
    [2,3,1]
]

distanceThreshold = 4


Shortest distances:

From city 0:
    to 1 = 3
    to 2 = 4
    to 3 = 5

Reachable within 4:
    {1, 2}

Count = 2


From city 1:
    to 0 = 3
    to 2 = 1
    to 3 = 2

Reachable:
    {0, 2, 3}

Count = 3


From city 2:
    to 0 = 4
    to 1 = 1
    to 3 = 1

Reachable:
    {0, 1, 3}

Count = 3


From city 3:
    to 0 = 5
    to 1 = 2
    to 2 = 1

Reachable:
    {1, 2}

Count = 2


Minimum count = 2.

Cities having count 2:

    city 0
    city 3

Tie-breaker says choose the greater city number.

Answer:

    3


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
------
For every city, we need the shortest distance to every other city.

A straightforward approach is:

    For each source city:
        Run a shortest path algorithm.
        Count cities whose shortest distance <= threshold.

Since the graph is weighted, we cannot use ordinary BFS.

A basic brute-force way is to enumerate possible paths using DFS and
keep the minimum distance to every city.

This can become exponential because there can be many different paths.

The approach below is only for revision and is NOT used in the executable
solution.


Pseudo Code:
------------

    Build adjacency list.

    for every source city:

        dist[] = INF
        visited[] = false

        DFS(source, 0)

        count cities where:
            city != source
            and dist[city] <= threshold

        update answer


Complete Brute Force Code:
--------------------------

/*
class Solution {
public:
    const int INF = 1e9;

    void dfs(
        int u,
        int currentDistance,
        vector<vector<pair<int,int>>>& adj,
        vector<int>& dist,
        vector<int>& visited
    ) {
        if (currentDistance >= dist[u])
            return;

        dist[u] = currentDistance;

        for (auto [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = 1;

                dfs(
                    v,
                    currentDistance + w,
                    adj,
                    dist,
                    visited
                );

                visited[v] = 0;
            }
        }
    }

    int findTheCity(
        int n,
        vector<vector<int>>& edges,
        int distanceThreshold
    ) {
        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        int answer = -1;
        int minCount = INF;

        for (int src = 0; src < n; src++) {

            vector<int> dist(n, INF);
            vector<int> visited(n, false);

            visited[src] = true;

            dfs(
                src,
                0,
                adj,
                dist,
                visited
            );

            int count = 0;

            for (int i = 0; i < n; i++) {
                if (i != src &&
                    dist[i] <= distanceThreshold) {
                    count++;
                }
            }

            if (count <= minCount) {
                minCount = count;
                answer = src;
            }
        }

        return answer;
    }
};
*/


// Time Complexity:
// ----------------
// DFS may explore exponentially many paths.

// Worst-case complexity can be exponential/factorial depending on the
// number of possible simple paths.

// Therefore this approach is not suitable for the constraints.


// Space Complexity:
// -----------------
// Adjacency list:

//     O(V + E)

// DFS recursion + arrays:

//     O(V)

// Overall:

//     O(V + E)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// For every city, we need the shortest distance to all other cities.

// The graph is:

//     - Weighted
//     - Undirected
//     - Edge weights are positive

// Therefore Dijkstra's Algorithm is suitable.

// We run Dijkstra once from every city.

// For each source:

//     1. Find shortest distance to every city.
//     2. Count cities with distance <= distanceThreshold.
//     3. Keep the city having the minimum count.
//     4. If counts tie, choose the larger city number.


// Intuition:
// ----------
// Suppose we are considering city 2.

// We want to know:

//     "How many cities can city 2 reach within distanceThreshold?"

// The only thing that matters is the SHORTEST distance.

// If:

//     shortestDistance(2, x) <= threshold

// then x is reachable.

// If:

//     shortestDistance(2, x) > threshold

// then x does not count.

// Dijkstra gives all shortest distances from one source efficiently.

// Since every city can become the source, we run Dijkstra n times.


// Why Dijkstra?
// -------------
// Edge weights are positive.

// For a weighted graph:

//     BFS        -> only works correctly for equal edge weights
//     Dijkstra   -> works for non-negative edge weights
//     BellmanFord-> handles negative edges but is slower

// Here Dijkstra is the natural choice.


// Tie-Breaking:
// -------------
// The problem says:

//     If multiple cities have the same minimum number of reachable
//     cities, return the city with the greatest number.

// Suppose:

//     city 1 -> count = 3
//     city 4 -> count = 3

// We must return:

//     4

// An easy implementation is:

//     if (count <= minCount)

// instead of:

//     if (count < minCount)

// Because we iterate cities from 0 to n-1, the later/larger city replaces
// the previous answer when the count is equal.


// Pseudo Code:
// ------------

//     Build undirected adjacency list.

//     minCount = INF
//     answer = -1

//     for source = 0 to n-1:

//         dist[] = INF
//         dist[source] = 0

//         minHeap = {(0, source)}

//         while minHeap is not empty:

//             (distance, u) = pop minimum

//             if this is a stale entry:
//                 continue

//             for every edge (u, v, weight):

//                 newDistance = distance + weight

//                 if newDistance < dist[v]:

//                     dist[v] = newDistance
//                     push (newDistance, v)

//         count = 0

//         for every city:

//             if city != source
//                and dist[city] <= threshold:

//                 count++

//         if count <= minCount:

//             minCount = count
//             answer = source

//     return answer


// Complete Optimal Code:
// ----------------------

/*
class Solution {
public:
    int findTheCity(
        int n,
        vector<vector<int>>& edges,
        int distanceThreshold
    ) {
        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        const int INF = 1e9;

        int answer = -1;
        int minCount = INF;

        for (int src = 0; src < n; src++) {

            vector<int> dist(n, INF);

            priority_queue<
                pair<int,int>,
                vector<pair<int,int>>,
                greater<pair<int,int>>
            > pq;

            dist[src] = 0;
            pq.push({0, src});

            while (!pq.empty()) {

                auto [d, u] = pq.top();
                pq.pop();

                if (d != dist[u])
                    continue;

                for (auto [v, w] : adj[u]) {

                    if (dist[v] > d + w) {

                        dist[v] = d + w;

                        pq.push({
                            dist[v],
                            v
                        });
                    }
                }
            }

            int count = 0;

            for (int city = 0; city < n; city++) {

                if (city != src &&
                    dist[city] <= distanceThreshold) {

                    count++;
                }
            }

            if (count <= minCount) {
                minCount = count;
                answer = src;
            }
        }

        return answer;
    }
};
*/


// Time Complexity:
// ----------------
// We run Dijkstra from every city.

// One Dijkstra using a binary min-heap:

//     O((V + E) log V)

// We do this V times:

//     O(V * (V + E) log V)

// For this problem's constraints, this is efficient enough.


// Space Complexity:
// -----------------
// Adjacency list:

//     O(V + E)

// Distance array:

//     O(V)

// Priority queue:

//     O(E) in the worst case

// Overall:

//     O(V + E)


// Alternative Optimal Approach:
// -----------------------------
// Because the graph is relatively small, Floyd-Warshall is also a valid
// solution.

// It computes all-pairs shortest paths in:

//     O(V^3)

// Then we count distances <= threshold.

// However, Dijkstra from every city is generally preferable here because
// the graph is weighted and the complexity is:

//     O(V * (V + E) log V)

// Both approaches are accepted for the problem.


// ================================================================================
// DRY RUN
// ================================================================================

// Graph:

//     0 --3-- 1
//            / \
//          1/   \4
//          /     \
//         2 --1-- 3

// Threshold = 4


// SOURCE = 0
// ----------------

// Dijkstra gives:

//     dist[0] = 0
//     dist[1] = 3
//     dist[2] = 4
//     dist[3] = 5

// Cities within threshold:

//     1 -> 3 <= 4
//     2 -> 4 <= 4

// Count:

//     2


// SOURCE = 1
// ----------------

// Shortest distances:

//     dist[0] = 3
//     dist[1] = 0
//     dist[2] = 1
//     dist[3] = 2

// Reachable cities:

//     0, 2, 3

// Count:

//     3


// SOURCE = 2
// ----------------

// Shortest distances:

//     dist[0] = 4
//     dist[1] = 1
//     dist[2] = 0
//     dist[3] = 1

// Reachable:

//     0, 1, 3

// Count:

//     3


// SOURCE = 3
// ----------------

// Shortest distances:

//     dist[0] = 5
//     dist[1] = 2
//     dist[2] = 1
//     dist[3] = 0

// Reachable:

//     1, 2

// Count:

//     2


// Now compare:

//     City 0 -> 2 reachable
//     City 1 -> 3 reachable
//     City 2 -> 3 reachable
//     City 3 -> 2 reachable

// Minimum count:

//     2

// Cities with minimum:

//     0 and 3

// Tie-breaker:

//     choose greater city

// Therefore:

//     ANSWER = 3


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// - Shortest Path
// - Dijkstra
// - All Sources
// - Weighted Undirected Graph
// - Distance Threshold
// - Count Reachable Nodes


// Key Observation:
// ----------------
// For each city, we only care about:

//     shortest distance to every other city

// So:

//     Run Dijkstra from every city
//             +
//     Count distances <= threshold


// Common Mistakes:
// ----------------

// 1. Using BFS.

//    The graph has weighted edges.

//    BFS is not generally valid for arbitrary weights.


// 2. Counting the source city.

//    The question asks for OTHER cities.

//    Therefore:

//        if (city != src && dist[city] <= threshold)


// 3. Forgetting the graph is undirected.

//    For every edge:

//        u --w-- v

//    add both:

//        u -> v
//        v -> u


// 4. Getting the tie-breaker wrong.

//    The answer must be the LARGEST city number when counts are equal.

//    Use:

//        if (count <= minCount)

//    not:

//        if (count < minCount)


// 5. Using a normal priority_queue.

//    C++ priority_queue is a max-heap by default.

//    For Dijkstra we need a min-heap:

//        priority_queue<
//            pair<int,int>,
//            vector<pair<int,int>>,
//            greater<pair<int,int>>
//        > pq;


// 6. Not ignoring stale heap entries.

//    Use:

//        if (d != dist[u])
//            continue;


// 7. Using Floyd-Warshall without checking complexity.

//    Floyd-Warshall is:

//        O(V^3)

//    It works here because n is small, but Dijkstra from every node is
//    a more scalable shortest-path approach.


// When to use this approach:
// --------------------------

// Use "Dijkstra from every node" when:

// - You need shortest distances from EVERY node.
// - The graph is weighted.
// - Edge weights are non-negative.
// - n is small/moderate enough for repeated Dijkstra.
// - You need to count/filter nodes based on shortest distance.


// Quick Recognition Trick:
// ------------------------

// If the problem says:

//     "For every node/city, find how many nodes are reachable within
//      some distance"

// think:

//     Dijkstra from every node.


// If the graph is small and asks for:

//     "shortest distance between every pair"

// also consider:

//     Floyd-Warshall.


// Dijkstra Template:
// ------------------

//     dist[src] = 0
//     pq.push({0, src})

//     while (!pq.empty()) {

//         auto [d, u] = pq.top();
//         pq.pop();

//         if (d != dist[u])
//             continue;

//         for (auto [v, w] : adj[u]) {

//             if (dist[v] > d + w) {

//                 dist[v] = d + w;

//                 pq.push({
//                     dist[v],
//                     v
//                 });
//             }
//         }
//     }


// One-Line Memory Trick:
// ----------------------

//     "Every city as source + Dijkstra + count within threshold
//      + larger city on tie."


// ================================================================================
// */

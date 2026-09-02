#include <bits/stdc++.h>
using namespace std;



class Graph
{
public:
    int n;
    vector<vector<pair<int, int>>> adj;

    Graph(int n, vector<vector<int>> &edges)
    {
        this->n = n;
        adj.resize(n);

        for (auto &e : edges)
        {
            adj[e[0]].push_back({e[1], e[2]});
        }
    }

    void addEdge(vector<int> edge)
    {
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    int shortestPath(int node1, int node2)
    {
        const int INF = 1e9;

        vector<int> dist(n, INF);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>>
            pq;

        dist[node1] = 0;
        pq.push({0, node1});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u])
                continue;

            if (u == node2)
                return d;

            for (auto [v, w] : adj[u])
            {
                if (dist[v] > d + w)
                {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        return -1;
    }
};

int main()
{
    vector<vector<int>> edges = {
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 1},
        {0, 3, 10}};

    Graph graph(4, edges);

    cout << graph.shortestPath(0, 3) << '\n';

    graph.addEdge({0, 2, 1});

    cout << graph.shortestPath(0, 3) << '\n';

    return 0;
}

/*
================================================================================
                  LEETCODE 2642 - COMPLETE NOTES
================================================================================

Problem Statement:
------------------
Design a directed weighted graph with n nodes numbered from 0 to n - 1.

Initially, the graph contains a list of directed edges:

    [from, to, cost]

Implement two operations:

1. addEdge(edge)
   Adds a directed edge from `from` to `to` with the given cost.

2. shortestPath(node1, node2)
   Returns the minimum cost of travelling from node1 to node2.

If there is no path, return -1.

Important:
----------
- The graph is directed.
- Edge weights are positive.
- New edges can be added dynamically.
- We need to answer multiple shortest-path queries.


--------------------------------------------------------------------------------
Example:
--------------------------------------------------------------------------------

n = 4

Initial edges:

    0 -> 1 (2)
    1 -> 2 (3)
    2 -> 3 (1)
    0 -> 3 (10)

Query:

    shortestPath(0, 3)

Possible paths:

    0 -> 3
    Cost = 10

    0 -> 1 -> 2 -> 3
    Cost = 2 + 3 + 1 = 6

Therefore:

    Answer = 6

Now add:

    0 -> 2 (1)

Then:

    0 -> 2 -> 3
    Cost = 1 + 1 = 2

So:

    shortestPath(0, 3) = 2


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
------
For every shortestPath query, we can use a simple traversal such as BFS/DFS
while keeping track of the minimum cost found for every node.

However, because the graph is weighted, ordinary BFS is not sufficient.

A brute-force recursive DFS can explore all possible paths and keep the
minimum cost.

This is extremely inefficient because the number of possible paths can
be exponential.

It is useful only for understanding why we need a shortest-path algorithm.


Pseudo Code:
------------

    shortestPath(src, dest):

        answer = INF

        DFS(src, 0)

        return answer if found
        otherwise -1


    DFS(node, currentCost):

        if node == dest:
            answer = min(answer, currentCost)
            return

        for every edge node -> next:
            if next is not currently visited:
                mark next visited
                DFS(next, currentCost + weight)
                unmark next


Complete Brute Force Code:
--------------------------

/*
class Graph {
public:
    int n;
    vector<vector<pair<int,int>>> adj;
    int answer;

    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.resize(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }
    }

    void addEdge(vector<int> edge) {
        adj[edge[0]].push_back({edge[1], edge[2]});
    }

    void dfs(
        int u,
        int dest,
        int cost,
        vector<int>& visited
    ) {
        if (u == dest) {
            answer = min(answer, cost);
            return;
        }

        for (auto [v, w] : adj[u]) {
            if (visited[v])
                continue;

            visited[v] = 1;

            dfs(
                v,
                dest,
                cost + w,
                visited
            );

            visited[v] = 0;
        }
    }

    int shortestPath(int node1, int node2) {
        answer = INT_MAX;

        vector<int> visited(n, 0);
        visited[node1] = 1;

        dfs(node1, node2, 0, visited);

        return answer == INT_MAX ? -1 : answer;
    }
};
*/

// Time Complexity : -- -- -- -- -- -- -- --The number of paths can be exponential in V.

//                   Worst case:

// O(V !)

// or exponential depending on the graph structure.

// This is not suitable for the constraints.


// Space Complexity:
// -----------------
// DFS recursion + visited array:

//     O(V)

// excluding the graph itself.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The graph has positive edge weights.

// Therefore, shortestPath() is a standard single-source shortest-path problem.

// Dijkstra's Algorithm is ideal for this.

// For every shortestPath(node1, node2) query:

//     1. Set distance of node1 = 0.
//     2. Put node1 into a min-heap.
//     3. Always process the node with the smallest known distance.
//     4. Relax all outgoing edges.
//     5. Stop when node2 is removed from the priority queue.


// Intuition:
// ----------
// Suppose we currently know:

//     dist[u] = minimum cost from node1 to u

// If u is the node with the smallest distance in the priority queue,
// then because all edge weights are positive, no future path can produce
// a smaller distance for u.

// Therefore, u's distance is finalized.

// This is the fundamental greedy property behind Dijkstra.


// Why not BFS?
// ------------
// BFS works for:

//     - unweighted graphs
//     - equal-weight edges

// Here edge weights are different.

// For example:

//     0 -> 1 = 100
//     0 -> 2 = 1
//     2 -> 1 = 1

// BFS might process node 1 early, but its cost is actually:

//     0 -> 2 -> 1
//     = 2

// Dijkstra correctly handles different edge weights.


// Pseudo Code:
// ------------

    // Graph(n, edges):

    //     create adjacency list

    //     for each edge:
    //         adj[from].push({to, cost})


    // addEdge(edge):

    //     adj[from].push({to, cost})


    // shortestPath(src, dest):

    //     dist[] = INF

    //     priority_queue = min heap

    //     dist[src] = 0
    //     push(src)

    //     while priority_queue is not empty:

    //         (cost, node) = pop minimum

    //         if cost != dist[node]:
    //             continue

    //         if node == dest:
    //             return cost

    //         for every (next, weight):

    //             newCost = cost + weight

    //             if newCost < dist[next]:
    //                 dist[next] = newCost
    //                 push(newCost, next)

    //     return -1


// Complete Optimal Code:
// ----------------------

/*
class Graph {
public:
    int n;
    vector<vector<pair<int,int>>> adj;

    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.resize(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({
                e[1],
                e[2]
            });
        }
    }

    void addEdge(vector<int> edge) {
        adj[edge[0]].push_back({
            edge[1],
            edge[2]
        });
    }

    int shortestPath(int node1, int node2) {
        const int INF = 1e9;

        vector<int> dist(n, INF);

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        dist[node1] = 0;
        pq.push({0, node1});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u])
                continue;

            if (u == node2)
                return d;

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

        return -1;
    }
};
*/


// Time Complexity:
// ----------------
// Let:

//     V = number of nodes
//     E = number of edges

// Building the graph:

//     O(E)

// addEdge():

//     O(1)

// Each shortestPath() query:

//     O((V + E) log V)

// With a binary heap, this is commonly written as:

//     O(E log V)

// for a connected/sufficiently dense traversal.


// Space Complexity:
// -----------------
// Adjacency list:

//     O(V + E)

// Distance array:

//     O(V)

// Priority queue:

//     O(E) in the worst case

// Overall:

// O(V + E)

// ================================================================================
// DRY RUN
// ================================================================================

// Initial graph:

//     0 -> 1 (2)
//     1 -> 2 (3)
//     2 -> 3 (1)
//     0 -> 3 (10)

// Query:

//     shortestPath(0, 3)


// Initial:

//     dist[0] = 0
//     dist[1] = INF
//     dist[2] = INF
//     dist[3] = INF

// Priority Queue:

//     (0, 0)


// Step 1:
// --------
// Pop:

//     (0, 0)

// From node 0:

//     0 -> 1, cost 2
//     0 -> 3, cost 10

// Update:

//     dist[1] = 2
//     dist[3] = 10

// PQ:

//     (2, 1)
//     (10, 3)


// Step 2:
// --------
// Pop:

//     (2, 1)

// From node 1:

//     1 -> 2, cost 3

// New cost:

//     2 + 3 = 5

// Update:

//     dist[2] = 5

// PQ:

//     (5, 2)
//     (10, 3)


// Step 3:
// --------
// Pop:

//     (5, 2)

// From node 2:

//     2 -> 3, cost 1

// New cost:

//     5 + 1 = 6

// Current dist[3]:

//     10

// Since:

//     6 < 10

// Update:

//     dist[3] = 6


// PQ:

//     (6, 3)
//     (10, 3)


// Step 4:
// --------
// Pop:

//     (6, 3)

// We reached destination.

// Return:

//     6


// Now add:

//     0 -> 2 (1)


// Graph contains:

//     0 -> 1 (2)
//     1 -> 2 (3)
//     2 -> 3 (1)
//     0 -> 3 (10)
//     0 -> 2 (1)


// Run shortestPath(0, 3).

// We immediately get:

//     0 -> 2 = 1
//     2 -> 3 = 1

// Total:

//     1 + 1 = 2

// Answer:

//     2


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// - Shortest Path
// - Dijkstra
// - Weighted Directed Graph
// - Dynamic Edge Addition
// - Priority Queue / Min Heap


// Key Observation:
// ----------------
// Every shortestPath() call is an independent single-source shortest-path
// problem.

// Because all edge weights are positive:

//     Dijkstra = best standard choice


// Common Mistakes:
// ----------------

// 1. Using BFS.

//    BFS is not correct for arbitrary positive edge weights.


// 2. Using DFS without memoization.

//    There can be exponentially many paths.


// 3. Using a normal queue instead of a min-heap.

//    Dijkstra requires processing the currently smallest distance first.


// 4. Forgetting stale priority-queue entries.

//    We may push the same node multiple times.

//    Therefore:

//        if (d != dist[u])
//            continue;

// 5. Assuming addEdge() replaces an existing edge.

//     The problem says to add a new directed edge.

//     Therefore simply append it to the adjacency list.

//     6. Forgetting the graph is directed.

//     For :

//     u -> v

//     we only add :

//     adj[u]
//         .push_back({v, w})

//             7. Returning the first time a node is inserted into the queue.

//     The answer is finalized when the destination is POPPED from the
//     min
//     - priority queue,
//     not merely when it is discovered.

//             When to use this approach : -- -- -- -- -- -- -- -- -- -- -- -- --

//                                         Use Dijkstra when :

//     -Graph is weighted.-
//             Edge weights are non - negative.- You need shortest path from one source.- There may be many different edge weights.- The graph is directed
//         or undirected.

//                Typical pattern :

//     adjacency list
//                +
//                min priority_queue
//                +
//                distance array
//                +
//                edge relaxation

//                Dijkstra Template :

//     dist[src] = 0 pq.push({0, src})

//                     while (!pq.empty())
// {

//     auto [d, u] = pq.top();
//     pq.pop();

//     if (d != dist[u])
//         continue;

//     for (auto [v, w] : adj[u])
//     {

//         if (dist[v] > d + w)
//         {

//             dist[v] = d + w;

//             pq.push({dist[v],
//                      v});
//         }
//     }
// }

// Important Complexity Note:
// --------------------------
// For this particular LeetCode problem, recomputing Dijkstra for each
// shortestPath() query is the intended practical approach.

// Although addEdge() changes the graph dynamically, maintaining an
// all-pairs shortest-path structure is unnecessary because the constraints
// allow Dijkstra per query.

// ================================================================================
// */

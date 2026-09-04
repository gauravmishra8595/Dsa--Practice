#include <bits/stdc++.h>
using namespace std;
// Optimal Solution: Kruskal + DSU

class Solution
{
    struct DSU
    {
        vector<int> parent, rank;

        DSU(int n)
        {
            parent.resize(n);
            rank.resize(n, 0);
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x)
        {
            if (parent[x] == x)
                return x;

            return parent[x] = find(parent[x]);
        }

        bool unite(int a, int b)
        {
            a = find(a);
            b = find(b);

            if (a == b)
                return false;

            if (rank[a] < rank[b])
                swap(a, b);

            parent[b] = a;

            if (rank[a] == rank[b])
                rank[a]++;

            return true;
        }
    };

    vector<vector<int>> edges;
    int n;

    int kruskal(int skip, int force)
    {
        DSU dsu(n);
        int cost = 0;
        int count = 0;

        // Force this edge first
        if (force != -1)
        {
            int u = edges[force][0];
            int v = edges[force][1];
            int w = edges[force][2];

            if (dsu.unite(u, v))
            {
                cost += w;
                count++;
            }
        }

        for (int i = 0; i < edges.size(); i++)
        {
            if (i == skip || i == force)
                continue;

            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            if (dsu.unite(u, v))
            {
                cost += w;
                count++;

                if (count == n - 1)
                    break;
            }
        }

        if (count != n - 1)
            return INT_MAX;

        return cost;
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n,
        vector<vector<int>> &inputEdges)
    {

        this->n = n;

        // Store:
        // {u, v, weight, original_index}
        for (int i = 0; i < inputEdges.size(); i++)
        {
            edges.push_back({inputEdges[i][0],
                             inputEdges[i][1],
                             inputEdges[i][2],
                             i});
        }

        // Sort by weight for Kruskal
        sort(edges.begin(), edges.end(),
             [](const vector<int> &a, const vector<int> &b)
             {
                 return a[2] < b[2];
             });

        // Find MST cost
        int mstCost = kruskal(-1, -1);

        vector<vector<int>> answer(2);

        for (int i = 0; i < edges.size(); i++)
        {

            // If removing this edge increases MST cost,
            // it is critical.
            int withoutEdge = kruskal(i, -1);

            if (withoutEdge > mstCost)
            {
                answer[0].push_back(edges[i][3]);
            }
            else
            {
                // Force this edge.
                // If MST cost remains the same,
                // it is pseudo-critical.
                int withEdge = kruskal(-1, i);

                if (withEdge == mstCost)
                    answer[1].push_back(edges[i][3]);
            }
        }

        return answer;
    }
};

int main()
{
    Solution sol;

    int n = 5;

    vector<vector<int>> edges = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 2},
        {0, 3, 2},
        {0, 4, 3},
        {3, 4, 3},
        {1, 4, 6}};

    vector<vector<int>> ans =
        sol.findCriticalAndPseudoCriticalEdges(n, edges);

    cout << "Critical Edges: ";
    for (int x : ans[0])
        cout << x << " ";

    cout << "\nPseudo-Critical Edges: ";
    for (int x : ans[1])
        cout << x << " ";

    cout << '\n';

    return 0;
}

/*
================================================================================
          LEETCODE 1489 - FIND CRITICAL AND PSEUDO-CRITICAL EDGES
================================================================================

Problem Statement:
------------------
You are given a weighted undirected connected graph with n vertices.

Each edge is represented as:

[u, v, weight]

We need to classify every edge into one of two categories:

1. Critical Edge:
   An edge is critical if removing it causes the weight of the Minimum
   Spanning Tree (MST) to increase.

2. Pseudo-Critical Edge:
   An edge is pseudo-critical if it can be included in some MST without
   increasing the total MST weight.

Return:

answer[0] = indices of critical edges
answer[1] = indices of pseudo-critical edges

The indices must refer to the original input order.


================================================================================
EXAMPLE
================================================================================

Input:

n = 5

edges = [
    [0,1,1],
    [1,2,1],
    [2,3,2],
    [0,3,2],
    [0,4,3],
    [3,4,3],
    [1,4,6]
]

Output:

[
    [0,1],
    [2,3,4,5]
]

Explanation:

Edges 0 and 1 are necessary for every MST, so they are critical.

Edges 2, 3, 4 and 5 can be included in at least one MST with the same
minimum total weight, so they are pseudo-critical.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
First find the MST cost.

Then for every edge:

1. Remove the edge.
2. Calculate the MST again.
3. If the new MST cost becomes larger, the edge is critical.

Otherwise:

4. Force the edge into the MST.
5. Calculate the MST.
6. If the MST cost remains equal to the original MST cost, the edge is
   pseudo-critical.


Pseudo Code:
-----------
sort edges by weight

mstCost = kruskal()

for every edge i:

    costWithout = kruskal(skip = i)

    if costWithout > mstCost:
        add i to critical

    else:
        costWith = kruskal(force = i)

        if costWith == mstCost:
            add i to pseudoCritical

return {critical, pseudoCritical}


Complete Brute Force Code:
--------------------------
(The following code is for revision only and is NOT executable.)

/*
class Solution {
public:

    int n;

    struct DSU {
        vector<int> parent;

        DSU(int n) {
            parent.resize(n);
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x) {
            if (parent[x] == x)
                return x;

            return parent[x] = find(parent[x]);
        }

        bool unite(int a, int b) {
            a = find(a);
            b = find(b);

            if (a == b)
                return false;

            parent[b] = a;
            return true;
        }
    };

    int kruskal(vector<vector<int>>& edges, int skip) {
        DSU dsu(n);

        int cost = 0;
        int count = 0;

        for (int i = 0; i < edges.size(); i++) {

            if (i == skip)
                continue;

            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            if (dsu.unite(u, v)) {
                cost += w;
                count++;
            }
        }

        if (count != n - 1)
            return INT_MAX;

        return cost;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(
        int n,
        vector<vector<int>>& edges) {

        this->n = n;

        vector<vector<int>> critical;
        vector<vector<int>> pseudo;

        // Add original index
        for (int i = 0; i < edges.size(); i++)
            edges[i].push_back(i);

        sort(edges.begin(), edges.end(),
             [](auto& a, auto& b) {
                 return a[2] < b[2];
             });

        int mstCost = kruskal(edges, -1);

        for (int i = 0; i < edges.size(); i++) {

            int without = kruskal(edges, i);

            if (without > mstCost) {
                critical.push_back({edges[i][3]});
            }
        }

        return {critical, pseudo};
    }
};
*/

// Time Complexity:
// ----------------
// Let:

// E = number of edges
// V = number of vertices

// One Kruskal execution:

// O(E log E)

// We may execute Kruskal O(E) times.

// Therefore:

// O(E^2 log E)

// Space:

// O(V + E)


// NOTE:
// -----
// The brute force idea is conceptually the same as the optimal solution, but the
// optimal implementation uses DSU efficiently and performs both "remove" and
// "force" tests systematically.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The key observation is:

// We already know the minimum MST cost.

// For every edge e:

// 1. Remove e and calculate MST.
// 2. If MST becomes more expensive, e is CRITICAL.

// Otherwise:

// 3. Force e into the MST.
// 4. If MST cost remains unchanged, e is PSEUDO-CRITICAL.


// Why does this work?

// CRITICAL:
// ---------
// If removing an edge increases the MST cost, there is no alternative edge set
// with the same minimum cost.

// Therefore the edge must appear in every MST.

// So it is critical.


// PSEUDO-CRITICAL:
// ----------------
// Suppose removing an edge does NOT increase the MST cost.

// Now force that edge to be selected first.

// If we can still construct an MST with the original minimum cost, then that
// edge belongs to at least one MST.

// Therefore it is pseudo-critical.


// Intuition:
// ----------
// Think of the MST as a minimum-cost way of connecting all vertices.

// For an edge:

//                 Remove it
//                     |
//           +---------+---------+
//           |                   |
//      Cost increases       Cost same
//           |                   |
//       CRITICAL          Try forcing edge
//                               |
//                     +---------+---------+
//                     |                   |
//                Same MST cost       Higher cost
//                     |                   |
//              PSEUDO-CRITICAL       Neither


// The actual MST construction is done using Kruskal's algorithm.

// DSU (Disjoint Set Union) is used to efficiently detect whether adding an edge
// creates a cycle.


// Pseudo Code:
// -----------
// add original index to every edge

// sort edges by weight

// mstCost = kruskal(skip = -1, force = -1)

// critical = []
// pseudo = []

// for every edge i:

//     without = kruskal(skip = i)

//     if without > mstCost:
//         critical.push_back(original_index)

//     else:

//         with = kruskal(force = i)

//         if with == mstCost:
//             pseudo.push_back(original_index)

// return {critical, pseudo}


// Complete Optimal Code:
// ----------------------
// (The following code is for revision only and is NOT executable.)

// /*
// #include <bits/stdc++.h>
// using namespace std;

// class Solution {

//     struct DSU {
//         vector<int> parent, rank;

//         DSU(int n) {
//             parent.resize(n);
//             rank.resize(n, 0);
//             iota(parent.begin(), parent.end(), 0);
//         }

//         int find(int x) {
//             if (parent[x] == x)
//                 return x;

//             return parent[x] = find(parent[x]);
//         }

//         bool unite(int a, int b) {
//             a = find(a);
//             b = find(b);

//             if (a == b)
//                 return false;

//             if (rank[a] < rank[b])
//                 swap(a, b);

//             parent[b] = a;

//             if (rank[a] == rank[b])
//                 rank[a]++;

//             return true;
//         }
//     };

//     vector<vector<int>> edges;
//     int n;

//     int kruskal(int skip, int force) {
//         DSU dsu(n);

//         int cost = 0;
//         int count = 0;

//         if (force != -1) {
//             int u = edges[force][0];
//             int v = edges[force][1];
//             int w = edges[force][2];

//             if (dsu.unite(u, v)) {
//                 cost += w;
//                 count++;
//             }
//         }

//         for (int i = 0; i < edges.size(); i++) {

//             if (i == skip || i == force)
//                 continue;

//             int u = edges[i][0];
//             int v = edges[i][1];
//             int w = edges[i][2];

//             if (dsu.unite(u, v)) {
//                 cost += w;
//                 count++;

//                 if (count == n - 1)
//                     break;
//             }
//         }

//         if (count != n - 1)
//             return INT_MAX;

//         return cost;
//     }

// public:

//     vector<vector<int>> findCriticalAndPseudoCriticalEdges(
//         int n,
//         vector<vector<int>>& inputEdges) {

//         this->n = n;

//         for (int i = 0; i < inputEdges.size(); i++) {
//             edges.push_back({
//                 inputEdges[i][0],
//                 inputEdges[i][1],
//                 inputEdges[i][2],
//                 i
//             });
//         }

//         sort(edges.begin(), edges.end(),
//              [](const vector<int>& a,
//                 const vector<int>& b) {
//                  return a[2] < b[2];
//              });

//         int mstCost = kruskal(-1, -1);

//         vector<int> critical;
//         vector<int> pseudo;

//         for (int i = 0; i < edges.size(); i++) {

//             int without = kruskal(i, -1);

//             if (without > mstCost) {
//                 critical.push_back(edges[i][3]);
//             }
//             else {
//                 int with = kruskal(-1, i);

//                 if (with == mstCost)
//                     pseudo.push_back(edges[i][3]);
//             }
//         }

//         return {critical, pseudo};
//     }
// };
// */


// // Time Complexity:
// // ----------------
// // Sorting:

// // O(E log E)

// // For each edge, we perform up to two Kruskal operations.

// // Each Kruskal operation:

// // O(E α(V))

// // after sorting has already been done.

// // Therefore:

// // O(E^2 α(V) + E log E)

// // This is commonly written as:

// // O(E^2 log E)

// // for simplicity.

// // Space Complexity:
// // -----------------
// // Edges:

// // O(E)

// // DSU:

// // O(V)

// // Total:

// // O(E + V)


// // ================================================================================
// // DRY RUN WITH EXAMPLE
// // ================================================================================

// // Input:

// // n = 5

// // Edges:

// // index     edge       weight

// // 0         0 - 1        1
// // 1         1 - 2        1
// // 2         2 - 3        2
// // 3         0 - 3        2
// // 4         0 - 4        3
// // 5         3 - 4        3
// // 6         1 - 4        6


// // Step 1: Sort by weight

// // 0 - 1 : 1
// // 1 - 2 : 1
// // 2 - 3 : 2
// // 0 - 3 : 2
// // 0 - 4 : 3
// // 3 - 4 : 3
// // 1 - 4 : 6


// // Step 2: Build normal MST

// // Take edge 0:

// // 0 - 1

// // Cost = 1


// // Take edge 1:

// // 1 - 2

// // Cost = 2


// // Take edge 2:

// // 2 - 3

// // Cost = 4


// // Edge 3 creates a cycle, skip it.


// // Take edge 4:

// // 0 - 4

// // Cost = 7


// // MST cost = 7


// // Step 3: Check edge 0

// // Remove edge 0.

// // Now edge 3 can connect 0 and 3.

// // An MST with cost 7 can still be formed.

// // So edge 0 is NOT critical.

// // Force edge 0.

// // MST cost is still 7.

// // Therefore edge 0 is pseudo-critical.


// // Step 4: Check edge 1

// // Remove edge 1.

// // There is another way to connect the graph, but the minimum cost becomes
// // larger.

// // Therefore edge 1 is critical.


// // The same process is repeated for every edge.


// // Final classification:

// // Critical:
// // [0, 1]

// // Pseudo-Critical:
// // [2, 3, 4, 5]


// // ================================================================================
// // INTERVIEW NOTES
// // ================================================================================

// // Pattern:
// // --------
// // Minimum Spanning Tree (MST)
// // +
// // Kruskal
// // +
// // DSU
// // +
// // Edge Classification


// // Key Observation:
// // ----------------
// // For each edge:

// // Remove it:
// //     MST cost increases -> CRITICAL

// // Force it:
// //     MST cost stays same -> PSEUDO-CRITICAL


// // Most Important Concept:
// // -----------------------
// // CRITICAL:

// // "Must be present in EVERY MST."


// // PSEUDO-CRITICAL:

// // "Can be present in AT LEAST ONE MST."


// // Common Mistakes:
// // ----------------
// // 1. Forgetting to preserve the original edge index.

// //    After sorting, the edge's position changes.

// 2. Confusing critical and pseudo-critical.

//    Critical:
//    Removing it makes MST worse.

//    Pseudo-critical:
//    It can be forced into an MST without making the MST worse.

// 3. When forcing an edge, add it BEFORE normal Kruskal processing.

// 4. Forgetting to skip the forced edge during the normal loop.

// 5. Not checking whether n - 1 edges were successfully selected.

// 6. Using only edge weights to identify critical edges.

//    Equal-weight edges can create multiple MSTs.

// 7. Forgetting DSU path compression.

// 8. Using int for cost is usually fine for the given constraints, but long long
//    can be used safely if edge weights are larger.


// When to Use This Approach:
// --------------------------
// Use this approach when a problem asks:

// - Which edges are present in every MST?
// - Which edges can belong to some MST?
// - Is an edge necessary for the MST?
// - Is an edge optional but still compatible with an MST?
// - Classify edges as critical/pseudo-critical.


// RELATED PROBLEMS:
// -----------------
// LeetCode 1584:
// Min Cost to Connect All Points

// LeetCode 1135:
// Connecting Cities With Minimum Cost

// LeetCode 1489:
// Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

// LeetCode 1584 and 1135 are good for learning basic MST first.

// LeetCode 1489 is a more advanced MST + DSU problem.


// ================================================================================
// FINAL COMPLEXITY
// ================================================================================

// Sorting:
// O(E log E)

// For every edge:
// At most two Kruskal runs.

// Overall:
// O(E^2 * alpha(V))

// Often written as:
// O(E^2 log E)

// Space:
// O(E + V)


// ================================================================================
// ONE-LINE MEMORY TRICK
// ================================================================================

// "REMOVE it -> cost increases = CRITICAL.
//  FORCE it -> cost stays same = PSEUDO-CRITICAL."


// ================================================================================
// */

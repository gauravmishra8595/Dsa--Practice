#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();

        vector<int> minDist(n, INT_MAX);
        vector<bool> inMST(n, false);

        minDist[0] = 0;

        int totalCost = 0;

        for (int count = 0; count < n; count++)
        {
            int u = -1;

            // Find the unused point with minimum connection cost
            for (int i = 0; i < n; i++)
            {
                if (!inMST[i] && (u == -1 || minDist[i] < minDist[u]))
                    u = i;
            }

            // Add this point to MST
            inMST[u] = true;
            totalCost += minDist[u];

            // Update minimum distance of remaining points
            for (int v = 0; v < n; v++)
            {
                if (!inMST[v])
                {
                    int dist = abs(points[u][0] - points[v][0]) +
                               abs(points[u][1] - points[v][1]);

                    minDist[v] = min(minDist[v], dist);
                }
            }
        }

        return totalCost;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> points = {
        {0, 0},
        {2, 2},
        {3, 10},
        {5, 2},
        {7, 0}};

    cout << sol.minCostConnectPoints(points) << '\n';

    return 0;
}

/*
================================================================================
              LEETCODE 1584 - MIN COST TO CONNECT ALL POINTS
================================================================================

Problem Statement:
------------------
You are given n points on a 2D plane.

points[i] = [xi, yi]

The cost of connecting two points is their Manhattan distance:

cost(i, j) = |xi - xj| + |yi - yj|

We need to connect all points such that:

1. Every point is reachable from every other point.
2. The total cost is minimum.

Return the minimum total cost.

This is exactly a Minimum Spanning Tree (MST) problem.


================================================================================
EXAMPLE
================================================================================

Input:

points = [
    [0,0],
    [2,2],
    [3,10],
    [5,2],
    [7,0]
]

Output:

20

Manhattan distances are used as edge weights.

The goal is to choose n - 1 edges that connect all points with minimum
possible total cost.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Treat every pair of points as an edge.

For n points, there are:

n * (n - 1) / 2

possible edges.

We can explicitly create all edges and then apply Kruskal's algorithm.

Steps:

1. Create an edge between every pair of points.
2. Calculate Manhattan distance as the edge weight.
3. Sort all edges by weight.
4. Use DSU to construct the MST.
5. Stop after selecting n - 1 edges.


Pseudo Code:
-----------
edges = []

for i = 0 to n-1:
    for j = i+1 to n-1:
        cost = ManhattanDistance(i, j)
        add {cost, i, j} to edges

sort edges by cost

create DSU

answer = 0
count = 0

for every edge:
    if endpoints belong to different components:
        unite them
        answer += edge.cost
        count++

        if count == n - 1:
            break

return answer


Complete Brute Force Code:
--------------------------
(The following code is for revision only and is NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct DSU {
        vector<int> parent, rank;

        DSU(int n) {
            parent.resize(n);
            rank.resize(n, 0);
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

            if (rank[a] < rank[b])
                swap(a, b);

            parent[b] = a;

            if (rank[a] == rank[b])
                rank[a]++;

            return true;
        }
    };

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();

        vector<tuple<int, int, int>> edges;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int cost = abs(points[i][0] - points[j][0]) +
                           abs(points[i][1] - points[j][1]);

                edges.push_back({cost, i, j});
            }
        }

        sort(edges.begin(), edges.end());

        DSU dsu(n);

        int answer = 0;
        int count = 0;

        for (auto [cost, u, v] : edges) {

            if (dsu.unite(u, v)) {
                answer += cost;
                count++;

                if (count == n - 1)
                    break;
            }
        }

        return answer;
    }
};
*/

// Time Complexity:
// ----------------
// Number of edges:

// E = n(n - 1) / 2 = O(n^2)

// Creating edges:
// O(n^2)

// Sorting:
// O(n^2 log(n^2))
// = O(n^2 log n)

// DSU operations:
// O(n^2 * alpha(n))

// Overall:

// O(n^2 log n)

// Space Complexity:
// -----------------
// O(n^2)

// because we explicitly store all possible edges.


// ================================================================================
// OPTIMAL APPROACH - PRIM'S ALGORITHM
// ================================================================================

// Observation:
// ------------
// This is an MST problem.

// But we do NOT need to explicitly create all O(n^2) edges.

// Prim's algorithm can calculate the minimum connection cost to each point
// directly using the coordinates.

// For each point we maintain:

// minDist[i] = minimum cost required to connect point i to the current MST.


// Intuition:
// ----------
// Start with any point.

// Suppose point 0 is already in the MST.

// For every remaining point, calculate its Manhattan distance from point 0.

// Choose the point with the smallest distance.

// Add it to the MST.

// Then this newly added point may provide a cheaper connection to other points.

// So update:

// minDist[v] = min(
//     minDist[v],
//     distance(newPoint, v)
// )

// Repeat until all points are included.


// Example:

// Suppose:

// A = (0,0)
// B = (2,2)
// C = (3,10)

// Initially:

// MST = {A}

// Distances:

// A -> B = 4
// A -> C = 13

// Choose B because 4 is smaller.

// Now:

// MST = {A,B}

// C can connect to:

// A -> C = 13
// B -> C = 9

// So update:

// minDist[C] = 9

// Continue this process until every point is included.


// Why Prim is Optimal Here:
// --------------------------
// There can be O(n^2) possible edges.

// Instead of storing all of them, we calculate distances only when needed.

// Since n <= 1000 for this problem, an O(n^2) Prim implementation is efficient
// and simpler than building all edges and sorting them.


// Pseudo Code:
// -----------
// n = number of points

// minDist[i] = infinity
// inMST[i] = false

// minDist[0] = 0

// answer = 0

// repeat n times:

//     find unused point u having minimum minDist[u]

//     mark u as used

//     answer += minDist[u]

//     for every unused point v:

//         distance =
//             |x[u] - x[v]| +
//             |y[u] - y[v]|

//         minDist[v] =
//             min(minDist[v], distance)

// return answer


// Complete Optimal Code:
// ----------------------
// (The following code is for revision only and is NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {

        int n = points.size();

        vector<int> minDist(n, INT_MAX);
        vector<bool> inMST(n, false);

        minDist[0] = 0;

        int totalCost = 0;

        for (int count = 0; count < n; count++) {

            int u = -1;

            for (int i = 0; i < n; i++) {

                if (!inMST[i] &&
                    (u == -1 || minDist[i] < minDist[u])) {

                    u = i;
                }
            }

            inMST[u] = true;

            totalCost += minDist[u];

            for (int v = 0; v < n; v++) {

                if (!inMST[v]) {

                    int dist =
                        abs(points[u][0] - points[v][0]) +
                        abs(points[u][1] - points[v][1]);

                    minDist[v] =
                        min(minDist[v], dist);
                }
            }
        }

        return totalCost;
    }
};
*/


// Time Complexity:
// ----------------
// We repeat n times.

// Finding minimum unused point:
// O(n)

// Updating all remaining points:
// O(n)

// Therefore:

// O(n * n)

// = O(n^2)


// Space Complexity:
// -----------------
// minDist:
// O(n)

// inMST:
// O(n)

// Total:

// O(n)


// ================================================================================
// DRY RUN WITH EXAMPLE
// ================================================================================

// Input:

// points = [
//     [0,0],
//     [2,2],
//     [3,10],
//     [5,2],
//     [7,0]
// ]


// Let:

// P0 = (0,0)
// P1 = (2,2)
// P2 = (3,10)
// P3 = (5,2)
// P4 = (7,0)


// Initial:

// minDist:

// P0 = 0
// P1 = INF
// P2 = INF
// P3 = INF
// P4 = INF

// MST = {}


// Step 1:
// -------

// Choose P0.

// Cost = 0

// MST = {P0}

// Calculate distances from P0:

// P0 -> P1:
// |0-2| + |0-2| = 4

// P0 -> P2:
// |0-3| + |0-10| = 13

// P0 -> P3:
// |0-5| + |0-2| = 7

// P0 -> P4:
// |0-7| + |0-0| = 7

// minDist:

// P1 = 4
// P2 = 13
// P3 = 7
// P4 = 7


// Step 2:
// -------

// Smallest = P1 with cost 4.

// Add P1.

// Total:

// 0 + 4 = 4

// Now update distances from P1:

// P1 -> P2:
// |2-3| + |2-10| = 9

// P1 -> P3:
// |2-5| + |2-2| = 3

// P1 -> P4:
// |2-7| + |2-0| = 7

// Updated:

// P2 = min(13, 9) = 9
// P3 = min(7, 3) = 3
// P4 = min(7, 7) = 7


// Step 3:
// -------

// Smallest = P3 with cost 3.

// Total:

// 4 + 3 = 7

// Update from P3:

// P3 -> P2:
// |5-3| + |2-10| = 10

// P3 -> P4:
// |5-7| + |2-0| = 4

// Updated:

// P2 = min(9, 10) = 9
// P4 = min(7, 4) = 4


// Step 4:
// -------

// Smallest = P4 with cost 4.

// Total:

// 7 + 4 = 11

// Update remaining P2:

// P4 -> P2:
// |7-3| + |0-10| = 14

// P2 remains:

// 9


// Step 5:
// -------

// Choose P2 with cost 9.

// Total:

// 11 + 9 = 20


// All points are now connected.

// Final Answer:

// 20


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Minimum Spanning Tree (MST)

// Two standard solutions:

// 1. Kruskal + DSU
// 2. Prim's Algorithm


// Key Observation:
// ----------------
// The problem asks us to connect ALL points with minimum total cost.

// That is exactly the definition of a Minimum Spanning Tree.

// The graph is complete because every pair of points can be connected.

// But explicitly creating all O(n^2) edges is unnecessary.

// Prim can calculate the required distances directly.


// Manhattan Distance:
// -------------------

// distance(i, j) =
// abs(xi - xj) + abs(yi - yj)


// Important Prim Concept:
// -----------------------
// minDist[i] means:

// "The minimum cost by which point i can currently be connected to the MST."


// Initially:

// minDist[0] = 0

// All others = INF.


// At every step:

// 1. Pick unused point with minimum minDist.
// 2. Add its cost to answer.
// 3. Mark it as part of MST.
// 4. Update minDist of all remaining points.


// Common Mistakes:
// ----------------
// 1. Using Euclidean distance instead of Manhattan distance.

// Wrong:

// sqrt((x1-x2)^2 + (y1-y2)^2)

// Correct:

// abs(x1-x2) + abs(y1-y2)


// 2. Forgetting to mark the selected point as part of MST.

// 3. Adding every distance to the answer.

// Only add the minimum connection cost when a point is selected.


// 4. Confusing Prim and Dijkstra.

// Prim:
// Finds Minimum Spanning Tree.

// Dijkstra:
// Finds shortest paths from a source.


// 5. Using a normal shortest-path interpretation.

// This problem is NOT asking for shortest path between two points.

// It asks to connect ALL points as cheaply as possible.


// 6. Building all O(n^2) edges unnecessarily.

// For this problem, O(n^2) Prim is simpler and uses much less memory.


// When to Use This Approach:
// --------------------------
// Use Prim when:

// - You need a Minimum Spanning Tree.
// - The graph is dense.
// - You can calculate edge weights easily.
// - You don't want to explicitly store every edge.
// - n is small enough for O(n^2).


// Use Kruskal when:

// - Edges are already given.
// - The graph is sparse.
// - You naturally have an edge list.
// - You want to use DSU.


// For LeetCode 1584:

// Prim's O(n^2) solution is particularly clean because the graph is complete.


// ================================================================================
// PRIM VS KRUSKAL
// ================================================================================

// Prim:

// Input representation:
// Usually adjacency matrix / implicit graph

// Typical complexity:
// O(V^2) for simple implementation

// Best for:
// Dense graphs


// Kruskal:

// Input representation:
// Edge list

// Typical complexity:
// O(E log E)

// Best for:
// Sparse graphs


// Here:

// E = O(n^2)

// So Prim is a very natural choice.


// ================================================================================
// RELATED PROBLEMS
// ================================================================================

// LeetCode 1584:
// Min Cost to Connect All Points

// LeetCode 1135:
// Connecting Cities With Minimum Cost

// LeetCode 1489:
// Find Critical and Pseudo-Critical Edges in MST

// LeetCode 743:
// Network Delay Time
// (Dijkstra - do NOT confuse with MST)


// ================================================================================
// FINAL COMPLEXITY
// ================================================================================

// Brute Force:
// Time  : O(n^2 log n)
// Space : O(n^2)

// Optimal Prim:
// Time  : O(n^2)
// Space : O(n)


// ================================================================================
// ONE-LINE MEMORY TRICK
// ================================================================================

// "MST problem + complete graph + coordinates
//  -> Prim + minDist array."


// ================================================================================
// */

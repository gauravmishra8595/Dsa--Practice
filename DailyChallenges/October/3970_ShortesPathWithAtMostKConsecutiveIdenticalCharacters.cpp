#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {
        if (k == 0) return -1;
        vector<vector<pair<int, int>>> adj(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], wt = e[2];
            adj[u].push_back({v, wt});
        }

        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));

        // {distance, node, consecutiveCount}
        using T = tuple<int, int, int>;

        priority_queue<T, vector<T>, greater<T>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [d, node, cnt] = pq.top();
            pq.pop();

            if (d > dist[node][cnt])
                continue;

            if (node == n - 1)
                return d;

            for (auto &[nextNode, wt] : adj[node]) {

                int newCnt;

                if (labels[node] == labels[nextNode])
                    newCnt = cnt + 1;
                else
                    newCnt = 1;

                if (newCnt > k)
                    continue;

                int newDist = d + wt;

                if (newDist < dist[nextNode][newCnt]) {

                    dist[nextNode][newCnt] = newDist;

                    pq.push({
                        newDist,
                        nextNode,
                        newCnt
                    });
                }
            }
        }

        return -1;
    }
};

int main() {

    Solution sol;

    int n = 5;
    vector<vector<int>> edges = {
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 1},
        {3, 4, 2},
        {0, 3, 10}
    };

    string labels = "aabbb";
    int k = 2;

    cout << sol.shortestPath(n, edges, labels, k) << endl;

    return 0;
}

/*
============================================================
PROBLEM STATEMENT
============================================================

You are given:
    n     = number of nodes in a directed weighted graph.
    edges = directed edges [u, v, w].
    labels = character assigned to every node.
    k     = maximum allowed consecutive identical characters.

Find the minimum total edge weight from node 0 to node n-1
such that the concatenation of labels along the path does
not contain more than k consecutive identical characters.

Return -1 if no valid path exists.

============================================================
EXAMPLE
============================================================

Input:

n = 5

edges = {
    {0, 1, 2},
    {1, 2, 3},
    {2, 3, 1},
    {3, 4, 2},
    {0, 3, 10}
}

labels = "aabbb"
k = 2

Valid path:

0 -> 1 -> 2 -> 3 -> 4

Labels:

a -> a -> b -> b -> b

This path is INVALID because three consecutive b's
are present.

Another path:

0 -> 3 -> 4

Labels:

a -> b -> b

Total cost = 10 + 2 = 12

Output:

12

============================================================
BRUTE FORCE APPROACH
============================================================

1. IDEA
-------

Explore every possible path from node 0 to node n-1
using DFS.

Maintain:
    current node
    current path cost
    previous character
    consecutive character count

Whenever we visit a node:

    If its label matches the previous label:
        increment consecutive count.

    Otherwise:
        reset consecutive count to 1.

If consecutive count exceeds k:
    Stop exploring that path.

Whenever destination is reached:
    Update minimum answer.

This explores all possible valid paths.

For a general graph, cycles can cause infinitely many
paths. Since weights are non-negative, an optimal
simple path exists. We can use a visited array to
enumerate simple paths.

2. PSEUDO CODE
--------------

DFS(node, cost, previousChar, count):

    If count > k:
        return

    If node == n-1:
        answer = min(answer, cost)
        return

    Mark node visited

    For every adjacent node:

        If adjacent node is already visited:
            continue

        If labels[node] == labels[adjacent]:
            newCount = count + 1
        Else:
            newCount = 1

        If newCount <= k:
            DFS(adjacent, cost + weight,
                labels[node], newCount)

    Unmark node

3. COMPLETE BRUTE FORCE CODE
----------------------------

    class BruteForceSolution {

    public:

        int ans = INT_MAX;

        void dfs(int node, int cost, int count,
                 int n, int k,
                 vector<vector<pair<int,int>>>& adj,
                 string& labels,
                 vector<int>& visited) {

            if (count > k)
                return;

            if (node == n - 1) {
                ans = min(ans, cost);
                return;
            }

            visited[node] = 1;

            for (auto &[nextNode, wt] : adj[node]) {

                if (visited[nextNode])
                    continue;

                int newCount;

                if (labels[node] == labels[nextNode])
                    newCount = count + 1;
                else
                    newCount = 1;

                if (newCount <= k) {

                    dfs(nextNode, cost + wt, newCount,
                        n, k, adj, labels, visited);
                }
            }

            visited[node] = 0;
        }

        int shortestPath(int n, vector<vector<int>>& edges,
                         string labels, int k) {

            if (k == 0)
                return -1;

            vector<vector<pair<int,int>>> adj(n);

            for (auto &e : edges) {
                adj[e[0]].push_back({e[1], e[2]});
            }

            vector<int> visited(n, 0);

            dfs(0, 0, 1, n, k, adj, labels, visited);

            return ans == INT_MAX ? -1 : ans;
        }
    };

4. TIME COMPLEXITY
------------------

O(number of simple paths * path length)

In the worst case, the number of simple paths
can grow exponentially.

5. SPACE COMPLEXITY
-------------------

O(V + E)

For adjacency list and recursion stack.

============================================================
OPTIMAL APPROACH - DIJKSTRA WITH STATE
============================================================

1. OBSERVATION
--------------

Normal Dijkstra maintains:

    dist[node]

But here, reaching the same node with different
consecutive character counts represents different states.

For example:

    State 1 = (node = 3, count = 1)
    State 2 = (node = 3, count = 2)

Both states are different because their future
transitions may have different validity.

Therefore, maintain:

    dist[node][count]

Where:

    node  = current node
    count = consecutive occurrences of labels[node]

The last character does not need to be stored separately
because it is always labels[node].

2. INTUITION
------------

Use Dijkstra's algorithm on an expanded state graph.

Each state is:

    (distance, node, consecutiveCount)

Initially:

    Node = 0
    Count = 1
    Distance = 0

For every adjacent node:

CASE 1:

    labels[node] == labels[nextNode]

    newCount = count + 1

CASE 2:

    labels[node] != labels[nextNode]

    newCount = 1

If:

    newCount > k

Reject this transition.

Otherwise:

    newDist = currentDist + edgeWeight

Relax the state:

    dist[nextNode][newCount] = min(
        dist[nextNode][newCount],
        newDist
    )

Push the updated state into the min heap.

Since all edge weights are non-negative, the first
valid destination state removed from the priority
queue gives the minimum distance.

3. PSEUDO CODE
--------------

shortestPath(n, edges, labels, k):

    If k == 0:
        return -1

    Build adjacency list

    Create dist[n][k+1] initialized with INF

    Create min priority queue

    dist[0][1] = 0

    Push (0, 0, 1)

    While priority queue is not empty:

        (d, node, count) = pop minimum state

        If d > dist[node][count]:
            continue

        If node == n-1:
            return d

        For every (nextNode, weight) in adj[node]:

            If labels[node] == labels[nextNode]:
                newCount = count + 1
            Else:
                newCount = 1

            If newCount > k:
                continue

            newDist = d + weight

            If newDist < dist[nextNode][newCount]:

                Update distance

                Push (newDist, nextNode, newCount)

    return -1

4. COMPLETE OPTIMAL CODE
------------------------

    class Solution {

    public:

        int shortestPath(int n, vector<vector<int>>& edges,
                         string labels, int k) {

            if (k == 0)
                return -1;

            vector<vector<pair<int,int>>> adj(n);

            for (auto &e : edges) {
                int u = e[0];
                int v = e[1];
                int wt = e[2];

                adj[u].push_back({v, wt});
            }

            vector<vector<int>> dist(
                n, vector<int>(k + 1, INT_MAX)
            );

            using T = tuple<int, int, int>;

            priority_queue<T, vector<T>, greater<T>> pq;

            dist[0][1] = 0;
            pq.push({0, 0, 1});

            while (!pq.empty()) {

                auto [d, node, count] = pq.top();
                pq.pop();

                if (d > dist[node][count])
                    continue;

                if (node == n - 1)
                    return d;

                for (auto &[nextNode, wt] : adj[node]) {

                    int newCount;

                    if (labels[node] == labels[nextNode])
                        newCount = count + 1;
                    else
                        newCount = 1;

                    if (newCount > k)
                        continue;

                    int newDist = d + wt;

                    if (newDist < dist[nextNode][newCount]) {

                        dist[nextNode][newCount] = newDist;

                        pq.push({
                            newDist,
                            nextNode,
                            newCount
                        });
                    }
                }
            }

            return -1;
        }
    };

5. TIME COMPLEXITY
------------------

Number of states:

    V * K

Each state has outgoing transitions corresponding
to the outgoing edges of its node.

Total transitions:

    O(E * K)

Priority queue operations:

    O(E * K)

Each operation takes:

    O(log(V * K))

Overall Time Complexity:

    O(E * K * log(V * K))

6. SPACE COMPLEXITY
-------------------

Distance array:

    O(V * K)

Adjacency list:

    O(V + E)

Priority queue:

    O(E * K) worst case

Overall Space Complexity:

    O(V * K + E * K)

============================================================
DRY RUN WITH EXAMPLE
============================================================

Input:

n = 5

edges:

0 -> 1 (2)
1 -> 2 (3)
2 -> 3 (1)
3 -> 4 (2)
0 -> 3 (10)

labels = "aabbb"

k = 2

INITIAL STATE
-------------

dist[0][1] = 0

Priority Queue:

(0, 0, 1)

STEP 1
------

Pop:

(d = 0, node = 0, count = 1)

Neighbor:

0 -> 1, weight = 2

labels[0] = 'a'
labels[1] = 'a'

Same character:

newCount = 2

newDist = 0 + 2 = 2

Update:

dist[1][2] = 2

Push:

(2, 1, 2)

STEP 2
------

Pop:

(d = 2, node = 1, count = 2)

Neighbor:

1 -> 2, weight = 3

labels[1] = 'a'
labels[2] = 'b'

Different character:

newCount = 1

newDist = 2 + 3 = 5

Update:

dist[2][1] = 5

Push:

(5, 2, 1)

STEP 3
------

Pop:

(d = 5, node = 2, count = 1)

Neighbor:

2 -> 3, weight = 1

labels[2] = 'b'
labels[3] = 'b'

Same character:

newCount = 2

newDist = 5 + 1 = 6

Update:

dist[3][2] = 6

Push:

(6, 3, 2)

STEP 4
------

Pop:

(d = 6, node = 3, count = 2)

Neighbor:

3 -> 4, weight = 2

labels[3] = 'b'
labels[4] = 'b'

Same character:

newCount = 3

Since:

    3 > k

Reject this transition.

STEP 5
------

The other available path is:

0 -> 3 -> 4

Labels:

a -> b -> b

Counts:

1 -> 1 -> 2

Total distance:

10 + 2 = 12

Destination reached.

Answer:

12

============================================================
INTERVIEW NOTES
============================================================

1. PATTERN
----------

Dijkstra's Algorithm + State Expansion

Also known as:

    Dijkstra on an expanded state graph

Used when shortest path depends on additional
information about the path taken so far.

2. KEY OBSERVATION
------------------

A node alone is not sufficient to represent a state.

We need:

    (node, consecutiveCount)

because reaching the same node with different
consecutive counts can lead to different valid
future transitions.

Whenever path validity depends on history,
include the necessary history in the state.

3. COMMON MISTAKES
------------------

1. Using only dist[node].

   Wrong because different consecutive counts
   represent different states.

2. Forgetting to reset count.

   When characters differ, count must become 1.

3. Using count = 0 initially.

   The starting node itself contributes one character.

4. Forgetting the k constraint.

   Reject whenever newCount > k.

5. Returning when destination is first discovered.

   Wrong. Return only when the destination state
   is popped from the min priority queue.

6. Forgetting stale-state checking.

   Always check:

       if (d > dist[node][count])
           continue;

7. Ignoring k == 0.

   No valid path exists because the starting node
   already contributes one character.

8. Using BFS instead of Dijkstra.

   Edge weights are not necessarily equal.

4. WHEN TO USE THIS APPROACH
----------------------------

Use Dijkstra with state expansion when:

1. Finding minimum cost paths in weighted graphs.

2. Path validity depends on previous moves.

3. You have constraints such as:
   - At most K consecutive identical characters.
   - At most K obstacles can be removed.
   - Limited fuel or resources.
   - Maximum number of special edges.
   - Number of coupons used.
   - Parity or direction-dependent restrictions.

4. The state can be represented using a manageable
   number of additional variables.

GENERAL TEMPLATE:

    dist[node][state]

    priority_queue<{
        distance,
        node,
        state
    }>

Remember:

    State = Current Node + Relevant Path History

============================================================
END OF NOTEBOOK
============================================================
*/

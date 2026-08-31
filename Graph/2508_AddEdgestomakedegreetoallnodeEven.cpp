#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isPossible(int n, vector<vector<int>> &edges)
    {
        vector<int> degree(n + 1, 0);
        vector<unordered_set<int>> adj(n + 1);

        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];

            degree[u]++;
            degree[v]++;

            adj[u].insert(v);
            adj[v].insert(u);
        }

        vector<int> odd;

        for (int i = 1; i <= n; i++)
        {
            if (degree[i] % 2 == 1)
                odd.push_back(i);
        }

        // Number of odd-degree vertices must be 0, 2, or 4.
        if (odd.size() == 0)
            return true;

        if (odd.size() == 2)
        {
            int a = odd[0];
            int b = odd[1];

            // Case 1:
            // Directly connect the two odd-degree vertices.
            if (!adj[a].count(b))
                return true;

            // Case 2:
            // Connect a and some intermediate vertex x,
            // and b and x.
            for (int x = 1; x <= n; x++)
            {
                if (x == a || x == b)
                    continue;

                if (!adj[a].count(x) && !adj[b].count(x))
                    return true;
            }

            return false;
        }

        if (odd.size() == 4)
        {
            int a = odd[0];
            int b = odd[1];
            int c = odd[2];
            int d = odd[3];

            // Try the three possible pairings.
            if (!adj[a].count(b) && !adj[c].count(d))
                return true;

            if (!adj[a].count(c) && !adj[b].count(d))
                return true;

            if (!adj[a].count(d) && !adj[b].count(c))
                return true;

            return false;
        }

        return false;
    }
};

int main()
{
    Solution obj;

    int n = 5;

    vector<vector<int>> edges = {
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5}};

    cout << boolalpha << obj.isPossible(n, edges) << '\n';

    return 0;
}

/*
===============================================================================
       LEETCODE 2508 - ADD EDGES TO MAKE DEGREES OF ALL NODES EVEN
===============================================================================

Problem Statement:
------------------
You are given an undirected graph with n nodes and some existing edges.

You may add at most two edges.

An edge cannot:

    1. Connect a node to itself.
    2. Already exist in the graph.

Return true if it is possible to add at most two edges such that every
node has an even degree.

Example:

    n = 5
    edges = [[1,2],[2,3],[3,4],[4,5]]

Degrees:

    1 -> 1  (odd)
    2 -> 2  (even)
    3 -> 2  (even)
    4 -> 2  (even)
    5 -> 1  (odd)

Only nodes 1 and 5 have odd degree.

Add:

    [1,5]

Then both become even.

Answer:

    true


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
There can be at most two new edges.

Try every possible pair of nodes:

    (u, v)

that does not already have an edge.

For each possible added edge:

    1. Add it.
    2. Check whether all degrees are even.

Also try adding two edges.

This works conceptually, but trying all combinations of edges is expensive.


Pseudo Code:
-----------
Find all missing edges.

Try adding one missing edge:

    If all degrees become even:
        return true

Try every pair of missing edges:

    Add both.

    If all degrees become even:
        return true

Return false.


Complete Brute Force Code:
--------------------------

class Solution {
public:

    bool check(vector<int>& degree) {

        for (int i = 1; i < degree.size(); i++) {
            if (degree[i] % 2 == 1)
                return false;
        }

        return true;
    }

    bool isPossible(int n, vector<vector<int>>& edges) {

        vector<vector<bool>> connected(
            n + 1,
            vector<bool>(n + 1, false)
        );

        vector<int> degree(n + 1, 0);

        for (auto &e : edges) {

            int u = e[0];
            int v = e[1];

            connected[u][v] = true;
            connected[v][u] = true;

            degree[u]++;
            degree[v]++;
        }

        vector<pair<int,int>> missing;

        for (int i = 1; i <= n; i++) {

            for (int j = i + 1; j <= n; j++) {

                if (!connected[i][j]) {
                    missing.push_back({i, j});
                }
            }
        }

        // Try one edge.
        for (auto [u, v] : missing) {

            degree[u]++;
            degree[v]++;

            if (check(degree))
                return true;

            degree[u]--;
            degree[v]--;
        }

        // Try two edges.
        for (int i = 0; i < missing.size(); i++) {

            for (int j = i + 1; j < missing.size(); j++) {

                auto [a, b] = missing[i];
                auto [c, d] = missing[j];

                degree[a]++;
                degree[b]++;
                degree[c]++;
                degree[d]++;

                if (check(degree))
                    return true;

                degree[a]--;
                degree[b]--;
                degree[c]--;
                degree[d]--;
            }
        }

        return false;
    }
};


Time Complexity:
----------------
There can be O(N^2) missing edges.

Trying pairs of missing edges can take:

    O(N^4)

which is too slow.


Space Complexity:
-----------------
O(N^2)

for storing all possible edges.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
Adding an edge changes the degree of exactly TWO vertices.

Therefore, the parity of exactly two vertices changes.

We only care about vertices with odd degree.


Important property:
-------------------
In every undirected graph, the number of odd-degree vertices is even.

Since we can add at most two edges, there can be only:

    0, 2, or 4

odd-degree vertices for a possible answer.


Case 1: 0 odd vertices
----------------------
All degrees are already even.

Answer:

    true


Case 2: 2 odd vertices
----------------------
Suppose the odd vertices are:

    a, b

We need to make both even.

Option 1:
    Directly connect a and b.

This works if:

    edge(a,b) does not already exist.


Option 2:
    Use one intermediate vertex x.

Add:

    (a,x)
    (b,x)

Then:

    degree(a) changes by 1 -> even
    degree(b) changes by 1 -> even
    degree(x) changes by 2 -> parity unchanged

So we need:

    x != a
    x != b
    (a,x) does not exist
    (b,x) does not exist


Case 3: 4 odd vertices
-----------------------
Suppose the odd vertices are:

    a, b, c, d

Two edges are required.

There are only three possible pairings:

    (a,b) and (c,d)

    (a,c) and (b,d)

    (a,d) and (b,c)

If any pairing consists entirely of edges that do not already exist,
we can make all degrees even.


Case 4: More than 4 odd vertices
--------------------------------
Each added edge can change the parity of only two vertices.

With at most two edges, we can fix at most four odd vertices.

Therefore:

    odd.size() > 4

means:

    false


Intuition:
----------
The entire graph structure does not matter.

Only degree parity matters.

For example:

    Odd vertices = {1, 5}

We only need to determine whether we can connect these vertices in
one of the valid ways.

This reduces the problem to checking a very small number of cases.


Pseudo Code:
-----------
Calculate degree of every node.

Store every existing edge in a hash set.

Find all odd-degree vertices.

If odd.size() == 0:
    return true

If odd.size() == 2:

    Let a, b be odd vertices.

    If edge(a,b) does not exist:
        return true

    For every x:
        if x != a
        and x != b
        and edge(a,x) does not exist
        and edge(b,x) does not exist:

            return true

    return false

If odd.size() == 4:

    Check:

        (a,b) + (c,d)

        (a,c) + (b,d)

        (a,d) + (b,c)

    Return true if any pairing is valid.

Return false.


Complete Optimal Code:
----------------------

class Solution {
public:

    bool isPossible(
        int n,
        vector<vector<int>>& edges
    ) {

        vector<int> degree(n + 1, 0);

        vector<unordered_set<int>> adj(n + 1);

        for (auto &e : edges) {

            int u = e[0];
            int v = e[1];

            degree[u]++;
            degree[v]++;

            adj[u].insert(v);
            adj[v].insert(u);
        }

        vector<int> odd;

        for (int i = 1; i <= n; i++) {

            if (degree[i] % 2 == 1)
                odd.push_back(i);
        }

        if (odd.size() == 0)
            return true;

        if (odd.size() == 2) {

            int a = odd[0];
            int b = odd[1];

            // One direct edge.
            if (!adj[a].count(b))
                return true;

            // Two edges using an intermediate node.
            for (int x = 1; x <= n; x++) {

                if (x == a || x == b)
                    continue;

                if (!adj[a].count(x) &&
                    !adj[b].count(x)) {

                    return true;
                }
            }

            return false;
        }

        if (odd.size() == 4) {

            int a = odd[0];
            int b = odd[1];
            int c = odd[2];
            int d = odd[3];

            if (!adj[a].count(b) &&
                !adj[c].count(d))
                return true;

            if (!adj[a].count(c) &&
                !adj[b].count(d))
                return true;

            if (!adj[a].count(d) &&
                !adj[b].count(c))
                return true;

            return false;
        }

        return false;
    }
};


Time Complexity:
----------------
Building degrees and adjacency:

    O(E)

Finding odd-degree vertices:

    O(N)

For two odd vertices, we may scan all nodes:

    O(N)

For four odd vertices, only constant number of checks are required.

Overall:

    O(N + E)

with average O(1) unordered_set lookup.


Space Complexity:
-----------------
O(N + E)

For the adjacency hash sets and degree array.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Example:

    n = 5

    edges:
        [1,2]
        [2,3]
        [3,4]
        [4,5]


Calculate degrees:

    Node 1 -> 1 -> ODD
    Node 2 -> 2 -> EVEN
    Node 3 -> 2 -> EVEN
    Node 4 -> 2 -> EVEN
    Node 5 -> 1 -> ODD


Therefore:

    odd = [1,5]


There are two odd vertices.

Try direct edge:

    [1,5]

Does [1,5] already exist?

    No.

So add [1,5].

New degrees:

    Node 1: 1 + 1 = 2 -> EVEN
    Node 5: 1 + 1 = 2 -> EVEN

All nodes now have even degree.

Answer:

    true


===============================================================================
DRY RUN - 4 ODD VERTICES
===============================================================================

Suppose:

    odd = [1, 2, 3, 4]

Try pairing 1:

    (1,2) and (3,4)

If both edges do not already exist:

    Add them.

Then:

    1 -> odd + 1 = even
    2 -> odd + 1 = even
    3 -> odd + 1 = even
    4 -> odd + 1 = even

Therefore return true.


If that pairing is blocked, try:

    (1,3) and (2,4)

Then:

    (1,4) and (2,3)


There are only three possible pairings.


===============================================================================
WHY CAN WE IGNORE EVEN-DEGREE VERTICES?
===============================================================================

An even-degree vertex already has correct parity.

If we use it as an intermediate vertex x in the two-edge solution:

    a -- x -- b

then x receives TWO new edges.

Therefore:

    even + 2 = even

Its parity remains unchanged.

This is why, in the two-odd-vertex case, we can simply search for any
valid intermediate vertex.


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Graph + Degree Parity + Case Analysis


Key Observation:
----------------
An edge changes the parity of exactly two vertices.

Therefore, only odd-degree vertices matter.

With at most two new edges:

    0 odd -> already valid
    2 odd -> fix with one or two edges
    4 odd -> pair them using two edges
    >4 odd -> impossible


Common Mistakes:
----------------
1. Checking whether the graph is connected.

   Connectivity does not matter.

   Only degree parity matters.

2. Forgetting that an existing edge cannot be added again.

3. Allowing self-loops:

       (x, x)

   These are not allowed.

4. Handling only the case of exactly two odd vertices.

   Four odd vertices are also possible.

5. Checking only one pairing for four odd vertices.

   There are three possible pairings.

6. Trying to actually modify the graph for every possibility.

   Only parity and edge existence are needed.


When to Use This Approach:
--------------------------
Use this approach when:

- You can add only a small number of edges.
- The desired property depends on vertex degree parity.
- Adding an edge flips the parity of exactly two vertices.

Classic recognition:

    "Make all degrees even"

Immediately think:

    Find odd-degree vertices.


===============================================================================
IMPORTANT LEETCODE SIGNATURE
===============================================================================

For LeetCode 2508, the function MUST be:

    bool isPossible(
        int n,
        vector<vector<int>>& edges
    )

If you use another name such as:

    validArrangement()
    findSmallestSetOfVertices()
    largestComponentSize()

LeetCode's driver code will produce:

    no member named 'isPossible' in 'Solution'


===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool dfs(vector<vector<int>> &graph, vector<int> &visited, int node, int destination)
    {
        if (node == destination)
            return true;

        visited[node] = 1;

        for (int neighbor : graph[node])
        {
            if (!visited[neighbor])
            {
                if (dfs(graph, visited, neighbor, destination))
                    return true;
            }
        }

        return false;
    }

    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> graph(n);

        for (auto &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> visited(n, 0);

        return dfs(graph, visited, source, destination);
    }
};

int main()
{
    Solution obj;

    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};
    int source = 0;
    int destination = 2;

    cout << (obj.validPath(n, edges, source, destination) ? "true" : "false");

    return 0;
}

/*

===========================================
LeetCode 1971. Find if Path Exists in Graph
===========================================

Problem Statement
-----------------
There is a bi-directional graph with n vertices numbered from 0 to n-1.

Given:
- n
- edges (undirected)
- source
- destination

Return true if there exists a valid path from source to destination,
otherwise return false.

--------------------------------------------------
Example
--------------------------------------------------

Input:
n = 3
edges = {{0,1},{1,2},{2,0}}
source = 0
destination = 2

Output:
true

Explanation:
0 -> 2 exists directly (or 0->1->2).

==================================================
Brute Force Approach
==================================================

Idea
----
Generate every possible path from source and check whether destination
can be reached.

Since cycles may exist, this becomes extremely inefficient without proper
visited tracking.

Pseudo Code
-----------

check(node):
    if node == destination
        return true

    for every neighbor
        recursively visit neighbor

Complete Brute Force Code
-------------------------

class Solution {
public:

    bool dfs(vector<vector<int>>& graph,int node,int destination){

        if(node==destination)
            return true;

        for(int neighbor:graph[node]){
            if(dfs(graph,neighbor,destination))
                return true;
        }

        return false;
    }

    bool validPath(int n, vector<vector<int>>& edges,
                   int source, int destination) {

        vector<vector<int>> graph(n);

        for(auto &e:edges){
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        return dfs(graph,source,destination);
    }
};

Time Complexity
---------------
Exponential (can revisit nodes infinitely because of cycles)

Space Complexity
----------------
O(V) recursion stack

==================================================
Optimal Approach (DFS)
==================================================

Observation
-----------
We only need to know whether destination is reachable.

Each vertex only needs to be explored once.

Use DFS + Visited array.

Intuition
---------
1. Build adjacency list.
2. Start DFS from source.
3. Mark every visited node.
4. If destination is reached return true.
5. Otherwise continue exploring.
6. If traversal finishes, return false.

Pseudo Code
-----------

Create adjacency list

visited[]

DFS(node):

    if node == destination
        return true

    visited[node]=true

    for every neighbor

        if neighbor not visited

            if DFS(neighbor)

                return true

return false

Complete Optimal Code
---------------------

class Solution {
public:

    bool dfs(vector<vector<int>> &graph,
             vector<int> &visited,
             int node,
             int destination){

        if(node==destination)
            return true;

        visited[node]=1;

        for(int neighbor:graph[node]){

            if(!visited[neighbor]){

                if(dfs(graph,visited,neighbor,destination))
                    return true;
            }
        }

        return false;
    }

    bool validPath(int n,
                   vector<vector<int>> &edges,
                   int source,
                   int destination){

        vector<vector<int>> graph(n);

        for(auto &edge:edges){

            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);

        }

        vector<int> visited(n,0);

        return dfs(graph,visited,source,destination);
    }
};

Time Complexity
---------------
Building Graph : O(E)

DFS Traversal : O(V + E)

Overall : O(V + E)

Space Complexity
----------------
Adjacency List : O(V + E)

Visited Array : O(V)

Recursion Stack : O(V)

Overall : O(V + E)

==================================================
Dry Run
==================================================

Input

n = 6

edges =
{
{0,1},
{0,2},
{3,5},
{5,4},
{4,3}
}

source = 0
destination = 5

Graph

0 -> 1,2
1 -> 0
2 -> 0
3 -> 5,4
4 -> 5,3
5 -> 3,4

DFS

Start at 0

Visited = {0}

Go to 1

Visited = {0,1}

Return

Go to 2

Visited = {0,1,2}

Return

No more neighbors

Destination 5 never reached

Answer = false

==================================================
Interview Notes
==================================================

Pattern
-------
Graph Traversal
DFS
Connected Components
Reachability

Key Observation
---------------
If every node is visited only once, DFS explores the entire connected
component containing the source.

Common Mistakes
---------------
1. Forgetting visited array.
2. Marking visited after recursion.
3. Building graph as directed instead of undirected.
4. Forgetting to add both directions.
5. Stack overflow for extremely deep graphs (iterative DFS/BFS can help).

When to use this approach
-------------------------
1. Path existence problems.
2. Connected components.
3. Reachability.
4. Tree traversal.
5. Graph exploration.

*/
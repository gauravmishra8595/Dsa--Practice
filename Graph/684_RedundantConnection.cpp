#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> parent;

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);   // Path Compression
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        parent.resize(n + 1);

        for (int i = 1; i <= n; i++)
            parent[i] = i;

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            int pu = find(u);
            int pv = find(v);

            if (pu == pv)
                return edge;       // Cycle found

            parent[pu] = pv;       // Union
        }

        return {};
    }
};

int main() {
    Solution obj;

    vector<vector<int>> edges = {
        {1,2},
        {1,3},
        {2,3}
    };

    vector<int> ans = obj.findRedundantConnection(edges);

    cout << "Redundant Edge: ";
    cout << ans[0] << " " << ans[1] << endl;

    return 0;
}

/*

=========================================================
LeetCode 684 - Redundant Connection
=========================================================

Problem Statement
-----------------
You are given a graph that started as a tree with n nodes.

One extra edge has been added.

Return the edge that can be removed so that the graph
becomes a tree again.

If multiple answers exist, return the one that appears last.

---------------------------------------------------------

Example
-------

Input:
edges = [[1,2],[1,3],[2,3]]

Output:
[2,3]

Explanation

1--2
 \ |
  \|
   3

Edge (2,3) creates the cycle.

---------------------------------------------------------
BRUTE FORCE APPROACH
---------------------------------------------------------

Idea
----
For every edge:
1. Remove it.
2. Check if remaining graph is a valid tree using DFS/BFS.
3. If yes, return that edge.

Pseudo Code
-----------

for each edge from last to first

    remove edge

    perform DFS

    if connected and no cycle
        return edge

Time Complexity
---------------
O(E * (V + E))

Space Complexity
----------------
O(V + E)

Complete Brute Force Code
-------------------------

class Solution {
public:

    bool dfs(int node,int parent,
             vector<vector<int>>&adj,
             vector<int>&vis){

        vis[node]=1;

        for(int nei:adj[node]){

            if(!vis[nei]){
                if(!dfs(nei,node,adj,vis))
                    return false;
            }
            else if(nei!=parent)
                return false;
        }

        return true;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges){

        int n=edges.size();

        for(int remove=n-1;remove>=0;remove--){

            vector<vector<int>> adj(n+1);

            for(int i=0;i<n;i++){

                if(i==remove) continue;

                adj[edges[i][0]].push_back(edges[i][1]);
                adj[edges[i][1]].push_back(edges[i][0]);
            }

            vector<int> vis(n+1,0);

            if(dfs(1,-1,adj,vis)){

                bool ok=true;

                for(int i=1;i<=n;i++)
                    if(!vis[i]) ok=false;

                if(ok)
                    return edges[remove];
            }
        }

        return {};
    }
};

---------------------------------------------------------
OPTIMAL APPROACH (Union Find / DSU)
---------------------------------------------------------

Observation
-----------
A tree has exactly one path between every pair of nodes.

If two nodes already belong to the same connected component,
adding another edge between them creates a cycle.

---------------------------------------------------------

Intuition
---------
Maintain connected components using Disjoint Set Union.

For every edge:

Find parent of u.

Find parent of v.

If both parents are same

    cycle found

    return current edge

Otherwise

    union both components.

---------------------------------------------------------

Pseudo Code
-----------

initialize parent array

for every edge

    pu = find(u)

    pv = find(v)

    if pu == pv
        return edge

    parent[pu] = pv

---------------------------------------------------------

Complete Optimal Code
---------------------

class Solution {
public:

    vector<int> parent;

    int find(int x){

        if(parent[x]==x)
            return x;

        return parent[x]=find(parent[x]);
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges){

        int n=edges.size();

        parent.resize(n+1);

        for(int i=1;i<=n;i++)
            parent[i]=i;

        for(auto &edge:edges){

            int u=edge[0];
            int v=edge[1];

            int pu=find(u);
            int pv=find(v);

            if(pu==pv)
                return edge;

            parent[pu]=pv;
        }

        return {};
    }
};

---------------------------------------------------------

Time Complexity
---------------
Find + Union ≈ O(α(n))

Overall

O(n)

(α(n) = Inverse Ackermann Function, almost constant)

---------------------------------------------------------

Space Complexity
----------------

O(n)

---------------------------------------------------------
Dry Run
---------------------------------------------------------

edges

1 2
1 3
2 3

Initially

1
2
3

All separate.

---------------------------------

Edge (1,2)

Different parents

Union

1--2

3

---------------------------------

Edge (1,3)

Different parents

Union

1--2--3

---------------------------------

Edge (2,3)

find(2)=3

find(3)=3

Same parent

Cycle detected

Return

[2,3]

---------------------------------------------------------
Interview Notes
---------------------------------------------------------

Pattern
-------
Graph + Disjoint Set Union (DSU)

Key Observation
---------------
If two vertices already belong to the same connected
component, adding another edge creates a cycle.

Common Mistakes
---------------
1. Forgetting path compression.
2. Returning the first edge instead of the cycle edge.
3. Incorrect parent initialization.
4. Using DFS for every edge (TLE for larger constraints).

When to use DSU
---------------
✔ Cycle Detection in Undirected Graph
✔ Kruskal's MST
✔ Connected Components
✔ Dynamic Connectivity
✔ Network Connectivity Problems

DSU Template to Remember
------------------------

find(x)

if(parent[x]==x)
    return x;

return parent[x]=find(parent[x]);

union(u,v)

parent[find(u)] = find(v);

*/
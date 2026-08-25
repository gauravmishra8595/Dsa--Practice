#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);

        for (auto &e : invocations)
            adj[e[0]].push_back(e[1]);

        vector<int> suspicious(n, 0);

        queue<int> q;
        q.push(k);
        suspicious[k] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = 1;
                    q.push(v);
                }
            }
        }

        // If any edge enters the suspicious set from outside,
        // removal is impossible.
        for (auto &e : invocations) {
            int u = e[0], v = e[1];
            if (!suspicious[u] && suspicious[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (!suspicious[i])
                ans.push_back(i);

        return ans;
    }
};

int main() {
    Solution obj;

    int n = 5;
    int k = 0;
    vector<vector<int>> invocations = {
        {1,2},
        {0,2},
        {0,1},
        {3,4}
    };

    vector<int> ans = obj.remainingMethods(n, k, invocations);

    cout << "Remaining Methods: ";
    for (int x : ans) cout << x << " ";
    cout << "\n";

    return 0;
}

/*

==========================
LeetCode 3310 - Remove Methods From Project
==========================

----------------------------------
Problem Statement
----------------------------------
There are n methods numbered from 0 to n-1.

Method k is known to contain a bug.

Every method that is directly or indirectly invoked by k is also considered
suspicious.

A suspicious group can be removed only if NO method outside the suspicious
group invokes any method inside the suspicious group.

Return all remaining methods after removing the suspicious group.
If removal is impossible, return every method.

----------------------------------
Example
----------------------------------

Input:
n = 5
k = 0
invocations =
[[1,2],[0,2],[0,1],[3,4]]

Output:
[3,4]

Explanation:

Suspicious methods:
0 -> 1 -> 2

No outside method calls
{0,1,2}

Hence remove them.

----------------------------------
Brute Force Approach
----------------------------------

Idea
----
1. Find suspicious nodes.
2. For every suspicious node,
   check every edge to see if some outside node calls it.

Overall this repeatedly scans edges.

Pseudo Code
------------

Find suspicious nodes.

For every suspicious node S
    For every edge (u,v)
        if v==S and u is not suspicious
             return all nodes

Return non-suspicious nodes

Complete Brute Force Code
-------------------------

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {

        vector<vector<int>> adj(n);

        for(auto &e:invocations)
            adj[e[0]].push_back(e[1]);

        vector<int> suspicious(n);

        queue<int> q;
        q.push(k);
        suspicious[k]=1;

        while(!q.empty()){

            int u=q.front();
            q.pop();

            for(int v:adj[u]){

                if(!suspicious[v]){

                    suspicious[v]=1;
                    q.push(v);

                }

            }

        }

        for(int s=0;s<n;s++){

            if(!suspicious[s]) continue;

            for(auto &e:invocations){

                if(e[1]==s && !suspicious[e[0]]){

                    vector<int> ans;

                    for(int i=0;i<n;i++)
                        ans.push_back(i);

                    return ans;

                }

            }

        }

        vector<int> ans;

        for(int i=0;i<n;i++)
            if(!suspicious[i])
                ans.push_back(i);

        return ans;
    }
};

Time Complexity
---------------
O(V * E)

Space Complexity
----------------
O(V + E)

----------------------------------
Optimal Approach
----------------------------------

Observation
-----------

We only need to know whether ANY edge enters the suspicious component from
outside.

A single scan over all edges is sufficient.

Intuition
---------

1. BFS/DFS from k.
2. Mark every reachable node as suspicious.
3. Scan each edge once.
4. If an edge goes

Outside ---> Suspicious

then removal is impossible.

Otherwise remove every suspicious node.

Pseudo Code
-----------

Build graph

BFS from k

Mark suspicious nodes

For every edge

    if outside -> suspicious

        return all nodes

Return non-suspicious nodes

Complete Optimal Code
---------------------

class Solution {
public:

    vector<int> remainingMethods(int n,int k,vector<vector<int>>& invocations){

        vector<vector<int>> adj(n);

        for(auto &e:invocations)
            adj[e[0]].push_back(e[1]);

        vector<int> suspicious(n,0);

        queue<int> q;

        q.push(k);

        suspicious[k]=1;

        while(!q.empty()){

            int u=q.front();
            q.pop();

            for(int v:adj[u]){

                if(!suspicious[v]){

                    suspicious[v]=1;
                    q.push(v);

                }

            }

        }

        for(auto &e:invocations){

            int u=e[0];
            int v=e[1];

            if(!suspicious[u] && suspicious[v]){

                vector<int> ans;

                for(int i=0;i<n;i++)
                    ans.push_back(i);

                return ans;

            }

        }

        vector<int> ans;

        for(int i=0;i<n;i++)
            if(!suspicious[i])
                ans.push_back(i);

        return ans;

    }

};

Time Complexity
---------------
O(V + E)

Space Complexity
----------------
O(V + E)

----------------------------------
Dry Run
----------------------------------

Example

n=5

k=0

Edges

0->1

0->2

1->2

3->4

Step 1

BFS from 0

Suspicious

{0,1,2}

Step 2

Scan edges

0->1

inside -> inside

0->2

inside -> inside

1->2

inside -> inside

3->4

outside -> outside

No outside node enters suspicious group.

Answer

{3,4}

----------------------------------
Interview Notes
----------------------------------

Pattern
-------
Graph Traversal + Reachability

Key Observation
---------------
Only incoming edges from outside the suspicious component matter.

Common Mistakes
---------------
1. Checking outgoing edges instead of incoming edges.
2. Forgetting indirect reachable methods.
3. Using repeated scans for every suspicious node.

When to use this approach
-------------------------
Whenever you need

- Reachable nodes
- Connected dependency analysis
- Dependency graph validation
- Graph pruning problems

*/
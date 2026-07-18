#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        for (auto &it : prerequisites) {
            adj[it[1]].push_back(it[0]);
            indegree[it[0]]++;
        }

        queue<int> q;

        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        int cnt = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cnt++;

            for (auto &nbr : adj[node]) {
                indegree[nbr]--;
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }

        return cnt == numCourses;
    }
};

int main() {
    Solution obj;

    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}};

    cout << (obj.canFinish(numCourses, prerequisites) ? "true" : "false") << endl;

    return 0;
}

/*

========================================
Problem Statement
========================================

There are 'numCourses' courses labeled from 0 to numCourses-1.

You are given prerequisites where
[a, b] means you must complete course b before course a.

Determine whether it is possible to finish all courses.

This is equivalent to checking whether the directed graph
formed by prerequisites contains a cycle.

========================================
Example
========================================

Example 1

Input:
numCourses = 2
prerequisites = [[1,0]]

Graph:
0 ---> 1

Output:
true

Explanation:
Take course 0 first, then course 1.

----------------------------------------

Example 2

Input:
numCourses = 2
prerequisites = [[1,0],[0,1]]

Graph:
0 <----> 1

Output:
false

Explanation:
Cycle exists, so courses cannot be completed.

====================================================
Brute Force Approach (DFS Cycle Detection)
====================================================

Idea
----

Start DFS from every unvisited node.

Maintain two arrays:

1. visited[]
2. pathVisited[] (recursion stack)

If during DFS we revisit a node already in the current recursion stack,
then a cycle exists.

Pseudo Code
-----------

Create graph

visited[]
pathVisited[]

for every node

    if not visited

        if dfs(node)
            return false

return true


dfs(node)

visited[node]=1
pathVisited[node]=1

for every neighbour

    if not visited

        if dfs(neighbour)
            return true

    else if pathVisited[neighbour]

        return true

pathVisited[node]=0

return false

Complete Brute Force Code
-------------------------

class Solution {
public:

    bool dfs(int node,
             vector<vector<int>>& adj,
             vector<int>& vis,
             vector<int>& pathVis){

        vis[node]=1;
        pathVis[node]=1;

        for(auto it:adj[node]){

            if(!vis[it]){

                if(dfs(it,adj,vis,pathVis))
                    return true;
            }

            else if(pathVis[it])
                return true;
        }

        pathVis[node]=0;

        return false;
    }

    bool canFinish(int numCourses,
                   vector<vector<int>>& prerequisites) {

        vector<vector<int>> adj(numCourses);

        for(auto &it:prerequisites)
            adj[it[1]].push_back(it[0]);

        vector<int> vis(numCourses,0);
        vector<int> pathVis(numCourses,0);

        for(int i=0;i<numCourses;i++){

            if(!vis[i]){

                if(dfs(i,adj,vis,pathVis))
                    return false;
            }
        }

        return true;
    }
};

Time Complexity
---------------
O(V + E)

Space Complexity
----------------
O(V)

====================================================
Optimal Approach (Kahn's Algorithm)
====================================================

Observation
-----------

A Directed Acyclic Graph (DAG) always contains at least
one node with indegree 0.

If after repeatedly removing indegree 0 nodes,
every node gets removed,
then no cycle exists.

Otherwise,
a cycle is present.

Intuition
---------

1. Build adjacency list.
2. Compute indegree of every node.
3. Push all indegree-0 nodes into queue.
4. Pop node.
5. Decrease indegree of neighbours.
6. Push neighbour if indegree becomes 0.
7. Count processed nodes.
8. If processed nodes == total nodes
   => No cycle.
   Else
   => Cycle exists.

Pseudo Code
-----------

Create graph

Compute indegree

Push all indegree 0 nodes

count = 0

while queue not empty

    node = front

    pop

    count++

    for neighbour

        indegree--

        if indegree==0

            push

return count==numCourses

Complete Optimal Code
---------------------

class Solution {
public:

    bool canFinish(int numCourses,
                   vector<vector<int>>& prerequisites){

        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses,0);

        for(auto &it:prerequisites){

            adj[it[1]].push_back(it[0]);
            indegree[it[0]]++;
        }

        queue<int> q;

        for(int i=0;i<numCourses;i++)
            if(indegree[i]==0)
                q.push(i);

        int cnt=0;

        while(!q.empty()){

            int node=q.front();
            q.pop();

            cnt++;

            for(auto &it:adj[node]){

                indegree[it]--;

                if(indegree[it]==0)
                    q.push(it);
            }
        }

        return cnt==numCourses;
    }
};

Time Complexity
---------------
O(V + E)

Space Complexity
----------------
O(V + E)

====================================================
Dry Run
====================================================

numCourses = 4

prerequisites

[[1,0],[2,0],[3,1],[3,2]]

Graph

0 -> 1
0 -> 2
1 -> 3
2 -> 3

Initial Indegree

0 : 0
1 : 1
2 : 1
3 : 2

Queue

[0]

--------------------------------

Pop 0

Processed = 1

Decrease indegree

1 -> 0
2 -> 0

Queue

1 2

--------------------------------

Pop 1

Processed = 2

Decrease indegree

3 -> 1

Queue

2

--------------------------------

Pop 2

Processed = 3

Decrease indegree

3 -> 0

Queue

3

--------------------------------

Pop 3

Processed = 4

Queue empty

Processed == numCourses

Answer = true

====================================================
Interview Notes
====================================================

Pattern
-------
Topological Sorting (BFS)

Key Observation
---------------
If every node appears in a topological ordering,
the graph is acyclic.

Common Mistakes
---------------
1. Reversing edge direction.
2. Forgetting indegree calculation.
3. Returning queue size instead of processed count.
4. Forgetting disconnected components.
5. Confusing Course Schedule I (207) with
   Course Schedule II (210).

When to use this approach
-------------------------
1. Detect cycle in directed graph.
2. Course scheduling problems.
3. Dependency resolution.
4. Build order problems.
5. Task scheduling.
6. Package installation ordering.

*/
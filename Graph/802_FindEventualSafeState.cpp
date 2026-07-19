#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();

        vector<vector<int>> revGraph(n);
        vector<int> indegree(n, 0);

        // Reverse the graph
        for (int i = 0; i < n; i++)
        {
            for (auto it : graph[i])
            {
                revGraph[it].push_back(i);
            }
            indegree[i] = graph[i].size();
        }

        queue<int> q;

        // Terminal nodes
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }

        vector<int> safe;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            safe.push_back(node);

            for (auto prev : revGraph[node])
            {
                indegree[prev]--;

                if (indegree[prev] == 0)
                    q.push(prev);
            }
        }

        sort(safe.begin(), safe.end());

        return safe;
    }
};

int main()
{

    Solution obj;

    vector<vector<int>> graph = {
        {1, 2},
        {2, 3},
        {5},
        {0},
        {5},
        {},
        {}};

    vector<int> ans = obj.eventualSafeNodes(graph);

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*

==========================
Problem Statement
==========================

There is a directed graph of n nodes numbered from 0 to n-1.

A node is called a Safe Node if every possible path starting from that node
eventually ends at a terminal node (a node with no outgoing edges).

Return all safe nodes in increasing order.

--------------------------------------------------

Example

Input

graph =

[
 [1,2],
 [2,3],
 [5],
 [0],
 [5],
 [],
 []
]

Output

2 4 5 6

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea

For every node:

Run DFS.

If during DFS we encounter a cycle,
then this node is unsafe.

Otherwise it is safe.

Do this for every node separately.

Pseudo Code

for every node

    clear visited

    if DFS detects cycle

        unsafe

    else

        safe

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:

    bool dfs(int node,
             vector<vector<int>>& graph,
             vector<int>& vis,
             vector<int>& path){

        vis[node]=1;
        path[node]=1;

        for(auto nxt:graph[node]){

            if(!vis[nxt]){

                if(dfs(nxt,graph,vis,path))
                    return true;
            }

            else if(path[nxt])
                return true;
        }

        path[node]=0;

        return false;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph){

        int n=graph.size();

        vector<int> ans;

        for(int i=0;i<n;i++){

            vector<int> vis(n,0);
            vector<int> path(n,0);

            if(!dfs(i,graph,vis,path))
                ans.push_back(i);
        }

        return ans;
    }
};

Time Complexity

O(V*(V+E))

Space Complexity

O(V)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation

Safe nodes are those that eventually reach a terminal node.

If we reverse the graph,

terminal nodes become starting nodes.

Removing terminal nodes repeatedly is exactly Kahn's Algorithm.

Pseudo Code

Reverse graph

Compute outdegree of every node

Push nodes with outdegree = 0

while queue not empty

    pop node

    mark safe

    for every parent

        decrease outdegree

        if outdegree becomes 0

            push parent

Sort answer

Return answer

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:

    vector<int> eventualSafeNodes(vector<vector<int>>& graph){

        int n=graph.size();

        vector<vector<int>> revGraph(n);
        vector<int> indegree(n);

        for(int i=0;i<n;i++){

            indegree[i]=graph[i].size();

            for(auto it:graph[i])
                revGraph[it].push_back(i);
        }

        queue<int> q;

        for(int i=0;i<n;i++)
            if(indegree[i]==0)
                q.push(i);

        vector<int> safe;

        while(!q.empty()){

            int node=q.front();
            q.pop();

            safe.push_back(node);

            for(auto prev:revGraph[node]){

                indegree[prev]--;

                if(indegree[prev]==0)
                    q.push(prev);
            }
        }

        sort(safe.begin(),safe.end());

        return safe;
    }
};

Time Complexity

O(V + E)

Space Complexity

O(V + E)

--------------------------------------------------
Dry Run
--------------------------------------------------

Graph

0 -> 1 2
1 -> 2 3
2 -> 5
3 -> 0
4 -> 5
5 ->
6 ->

Reverse Graph

1 <- 0
2 <- 0
2 <- 1
3 <- 1
0 <- 3
5 <- 2
5 <- 4

Outdegree

0 = 2
1 = 2
2 = 1
3 = 1
4 = 1
5 = 0
6 = 0

Queue

5 6

Pop 5

Safe = {5}

Decrease outdegree of

2 -> 0
4 -> 0

Queue

6 2 4

Pop 6

Safe = {5,6}

Pop 2

Decrease outdegree of 0 and 1

Pop 4

Eventually

Safe

2 4 5 6

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern

- Topological Sort
- Reverse Graph
- Multi-source BFS
- Kahn's Algorithm

Key Observation

Unsafe nodes belong to or lead to cycles.

Safe nodes are obtained by repeatedly removing terminal nodes.

Common Mistakes

1. Forgetting to reverse the graph.

2. Using indegree instead of outdegree.

3. Not sorting the answer.

4. Building reverse graph incorrectly.

5. Confusing terminal nodes with source nodes.

When to use this approach

Whenever the problem asks for

- Safe nodes
- Nodes not in cycles
- Eventual termination
- Reverse dependency removal
- Eliminate terminal nodes repeatedly

Classic Problems

- Find Eventual Safe States
- Course Schedule
- Topological Sort
- Alien Dictionary
- Parallel Courses
- Dependency Resolution

*/
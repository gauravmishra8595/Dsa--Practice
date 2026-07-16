#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> &graph,
             vector<vector<int>> &paths,
             vector<int> &path,
             int node,
             int destination)
    {
        path.push_back(node);
        if (node == destination)
        {
            paths.push_back(path);
        }
        else
        {
            for (int neighbor : graph[node])
            {
                dfs(graph, paths, path, neighbor, destination);
            }
        }
        path.pop_back();
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {

        vector<vector<int>> paths;
        vector<int> path;

        dfs(graph, paths, path, 0, graph.size() - 1);

        return paths;
    }
};

int main()
{
    Solution obj;

    vector<vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {}};

    vector<vector<int>> ans = obj.allPathsSourceTarget(graph);

    cout << "All Paths:\n";

    for (auto &path : ans)
    {
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}

/*

===========================================
LeetCode 797. All Paths From Source to Target
===========================================

Problem Statement
-----------------
Given a Directed Acyclic Graph (DAG) represented as an adjacency list,
return all possible paths from node 0 to node n-1.

Every path should start from node 0 and end at node n-1.

--------------------------------------------------
Example
--------------------------------------------------

Input:
graph = [[1,2],[3],[3],[]]

Output:
[[0,1,3],[0,2,3]]

Explanation:

0 -> 1 -> 3
0 -> 2 -> 3

==================================================
Brute Force Approach
==================================================

Idea
----
Generate every possible path from node 0.

Whenever destination is reached,
store the current path.

Since the graph is a DAG,
there are no cycles.

Pseudo Code
-----------

DFS(node)

    add node to path

    if node == destination

        save path

    else

        for every neighbor

            DFS(neighbor)

    remove node from path

Complete Brute Force Code
-------------------------

class Solution {
public:

    void dfs(vector<vector<int>>& graph,
             vector<vector<int>>& ans,
             vector<int>& path,
             int node,
             int destination){

        path.push_back(node);

        if(node==destination){

            ans.push_back(path);

        }

        else{

            for(int child:graph[node]){

                dfs(graph,ans,path,child,destination);

            }

        }

        path.pop_back();
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph){

        vector<vector<int>> ans;
        vector<int> path;

        dfs(graph,ans,path,0,graph.size()-1);

        return ans;
    }
};

Time Complexity
---------------
O(2^N × N)

Reason:
There can be exponentially many paths.
Each stored path takes O(N) time to copy.

Space Complexity
----------------
O(N)
(Recursion stack + current path)

Ignoring output storage.

==================================================
Optimal Approach (DFS + Backtracking)
==================================================

Observation
-----------
The graph is a DAG.

Since there are no cycles,
we can safely perform DFS.

Whenever destination is reached,
store the current path.

Backtracking removes the last node
before exploring another path.

Intuition
---------
1. Start DFS from node 0.
2. Add current node into current path.
3. If destination is reached,
   store the path.
4. Otherwise explore every neighbor.
5. Remove current node while returning
   (Backtracking).

Pseudo Code
-----------

DFS(node)

    path.push(node)

    if node == destination

        save path

    else

        for neighbor

            DFS(neighbor)

    path.pop()

Complete Optimal Code
---------------------

class Solution {
public:

    void dfs(vector<vector<int>>& graph,
             vector<vector<int>>& paths,
             vector<int>& path,
             int node,
             int destination){

        path.push_back(node);

        if(node==destination){

            paths.push_back(path);

        }

        else{

            for(int neighbor:graph[node]){

                dfs(graph,paths,path,neighbor,destination);

            }

        }

        path.pop_back();
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph){

        vector<vector<int>> paths;
        vector<int> path;

        dfs(graph,paths,path,0,graph.size()-1);

        return paths;
    }
};

Time Complexity
---------------
O(2^N × N)

N = Number of vertices

Reason:
Every possible path is explored.
Copying each path takes O(N).

Space Complexity
----------------
Recursion Stack : O(N)

Current Path : O(N)

Overall : O(N)

(Output array not included.)

==================================================
Dry Run
==================================================

graph =

0 -> 1,2
1 -> 3
2 -> 3
3 -> {}

Initially

path = []

DFS(0)

path = [0]

↓

DFS(1)

path = [0,1]

↓

DFS(3)

path = [0,1,3]

Store

Backtrack

path = [0,1]

Backtrack

path = [0]

↓

DFS(2)

path = [0,2]

↓

DFS(3)

path = [0,2,3]

Store

Backtrack

Answer

[
 [0,1,3],
 [0,2,3]
]

==================================================
Interview Notes
==================================================

Pattern
-------
DFS

Backtracking

Path Enumeration

Graph Traversal

Key Observation
---------------
The graph is a DAG.

No visited array is required because
there are no cycles.

Backtracking restores the path after
exploring each branch.

Common Mistakes
---------------
1. Forgetting path.pop_back().

2. Passing path by value (unnecessary copying).

3. Using visited[] (not required in DAG).

4. Returning immediately after finding one path.

5. Forgetting to save the path before backtracking.

When to use this approach
-------------------------
1. Generate all possible paths.

2. Root-to-leaf path problems.

3. DAG path enumeration.

4. Backtracking on graphs.

5. DFS where the complete traversal path
   must be stored.

*/
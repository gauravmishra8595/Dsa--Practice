#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool bfs(int src, vector<vector<int>> &graph, vector<int> &color)
    {

        queue<int> q;
        q.push(src);
        color[src] = 0;

        while (!q.empty())
        {

            int node = q.front();
            q.pop();

            for (auto adjNode : graph[node])
            {

                if (color[adjNode] == -1)
                {
                    color[adjNode] = !color[node];
                    q.push(adjNode);
                }
                else if (color[adjNode] == color[node])
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool isBipartite(vector<vector<int>> &graph)
    {

        int n = graph.size();

        vector<int> color(n, -1);

        for (int i = 0; i < n; i++)
        {
            if (color[i] == -1)
            {
                if (!bfs(i, graph, color))
                    return false;
            }
        }

        return true;
    }
};

int main()
{

    Solution obj;

    vector<vector<int>> graph = {
        {1, 3},
        {0, 2},
        {1, 3},
        {0, 2}};

    cout << obj.isBipartite(graph);

    return 0;
}

/*

==========================
Problem Statement
==========================

Given an undirected graph, determine whether it is Bipartite.

A graph is Bipartite if its vertices can be divided into two sets such that
every edge connects vertices from different sets.

Return true if the graph is bipartite, otherwise return false.

--------------------------------------------------

Example

Input

graph =

[
 [1,3],
 [0,2],
 [1,3],
 [0,2]
]

Output

true

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea

Try assigning every possible coloring of vertices using two colors
and verify whether every edge connects different colors.

This requires checking all possible assignments.

Pseudo Code

For every possible coloring

    Check every edge

    If all edges satisfy
        return true

Return false

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

(Not practical)

bool isBipartite(vector<vector<int>>& graph){

    // Try all possible 2^V color assignments

    // For every assignment

        // Check every edge

    // Return true if any assignment works

}

Time Complexity

O(2^V * E)

Space Complexity

O(V)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation

A graph is Bipartite iff it can be colored using only two colors
such that adjacent vertices have opposite colors.

This can be checked using BFS (or DFS).

Pseudo Code

Initialize color array with -1

For every node

    If not colored

        Start BFS

        Assign first color

        While queue not empty

            Pop node

            For every neighbour

                If uncolored

                    Assign opposite color

                    Push

                Else if same color

                    Return false

Return true

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:

    bool bfs(int src, vector<vector<int>>& graph, vector<int>& color){

        queue<int> q;
        q.push(src);

        color[src]=0;

        while(!q.empty()){

            int node=q.front();
            q.pop();

            for(auto adj:graph[node]){

                if(color[adj]==-1){

                    color[adj]=!color[node];
                    q.push(adj);
                }

                else if(color[adj]==color[node])
                    return false;
            }
        }

        return true;
    }

    bool isBipartite(vector<vector<int>>& graph){

        int n=graph.size();

        vector<int> color(n,-1);

        for(int i=0;i<n;i++){

            if(color[i]==-1){

                if(!bfs(i,graph,color))
                    return false;
            }
        }

        return true;
    }
};

Time Complexity

O(V + E)

Space Complexity

O(V)

--------------------------------------------------
Dry Run
--------------------------------------------------

Graph

0 ----- 1
|       |
|       |
3 ----- 2

Initially

Color

[-1 -1 -1 -1]

Start BFS from 0

Color[0] = 0

Queue

0

Pop 0

Neighbours

1 -> color 1

3 -> color 1

Queue

1 3

Pop 1

Neighbour

2 -> color 0

Queue

3 2

Pop 3

Neighbour 2 already has opposite color

Pop 2

All checks passed

Return true

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern

- BFS on Graph
- Graph Coloring
- Two Coloring

Key Observation

A graph is Bipartite iff it has no odd-length cycle.

Two-coloring automatically detects odd cycles.

Common Mistakes

1. Forgetting disconnected components.

2. Using visited array instead of color array.

3. Assigning same color to neighbours.

4. Returning true after checking only one component.

5. Treating graph as directed.

When to use this approach

Whenever the problem asks for

- Bipartite Graph
- Two Coloring
- Team Division
- Alternate Coloring
- Odd Cycle Detection

Classic Problems

- Is Graph Bipartite
- Possible Bipartition
- Divide Players into Two Teams
- Graph Coloring (2 Colors)

*/
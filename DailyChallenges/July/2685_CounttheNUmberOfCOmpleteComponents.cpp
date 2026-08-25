

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {

        // Create adjacency list
        vector<vector<int>> adj(n);
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> visited(n, false);
        int completeComponents = 0;

        // Traverse every connected component
        for (int i = 0; i < n; i++)
        {

            if (visited[i])
                continue;

            queue<int> q;
            q.push(i);
            visited[i] = true;

            vector<int> component;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                component.push_back(node);

                for (int neigh : adj[node])
                {
                    if (!visited[neigh])
                    {
                        visited[neigh] = true;
                        q.push(neigh);
                    }
                }
            }

            int vertices = component.size();
            int edgeCount = 0;

            // Count total degrees
            for (int node : component)
                edgeCount += adj[node].size();

            // Since every edge is counted twice
            edgeCount /= 2;

            // Complete graph condition
            if (edgeCount == vertices * (vertices - 1) / 2)
                completeComponents++;
        }

        return completeComponents;
    }
};

int main()
{

    Solution obj;

    int n = 6;

    vector<vector<int>> edges = {
        {0, 1},
        {0, 2},
        {1, 2},
        {3, 4}};

    cout << "Complete Components = "
         << obj.countCompleteComponents(n, edges);

    return 0;
}

/*
=========================================
BRUTE FORCE APPROACH
=========================================

Idea:
1. Find every connected component using BFS/DFS.
2. Store all vertices of that component.
3. For every pair of vertices inside the component,
   check whether an edge exists.
4. If every pair has an edge, the component is complete.

Steps:
- Find connected component.
- Let component size be k.
- Check all k*(k-1)/2 pairs.
- If every pair is connected, answer++.


class BruteForce
{
public:
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {

        vector<unordered_set<int>> adj(n);

        for (auto &e : edges)
        {
            adj[e[0]].insert(e[1]);
            adj[e[1]].insert(e[0]);
        }

        vector<bool> visited(n, false);

        int count = 0;

        for (int i = 0; i < n; i++)
        {

            if (visited[i])
                continue;

            queue<int> q;
            vector<int> component;

            q.push(i);
            visited[i] = true;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                component.push_back(node);

                for (int next : adj[node])
                {
                    if (!visited[next])
                    {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }

            bool complete = true;

            for (int i = 0; i < component.size() && complete; i++)
            {
                for (int j = i + 1; j < component.size(); j++)
                {
                    if (adj[component[i]].count(component[j]) == 0)
                    {
                        complete = false;
                        break;
                    }
                }
            }

            if (complete)
                count++;
        }

        return count;
    }
};

Time Complexity:
Finding Components = O(V + E)

Checking every pair:
O(k²) for each component

Worst Case:
O(V²)

Space Complexity:
O(V + E)


=========================================
OPTIMAL APPROACH (Used Above)
=========================================

Observation:

A complete graph having k vertices must contain

k*(k-1)/2 edges.

Algorithm:
1. Build adjacency list.
2. Find each connected component using BFS.
3. Count:
      vertices = number of nodes
      edges = total degrees / 2
4. If

edges == vertices*(vertices-1)/2

then this component is complete.

Why divide by 2?

Every undirected edge appears in adjacency list
of both endpoints.

Example:
0 ---- 1

adj[0] contains 1
adj[1] contains 0

Degree sum = 2
Actual edges = 1

Hence:
edges = degreeSum / 2

Time Complexity:
O(V + E)

Space Complexity:
O(V + E)

=========================================
*/
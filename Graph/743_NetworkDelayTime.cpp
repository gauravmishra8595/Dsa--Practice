#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {

        vector<vector<pair<int, int>>> graph(n + 1);

        for (auto &edge : times)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            graph[u].push_back({v, wt});
        }

        vector<int> dist(n + 1, INT_MAX);

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq;

        dist[k] = 0;
        pq.push({0, k});

        while (!pq.empty())
        {

            auto [currDist, node] = pq.top();
            pq.pop();

            if (currDist > dist[node])
                continue;

            for (auto &it : graph[node])
            {

                int neigh = it.first;
                int wt = it.second;

                if (dist[node] + wt < dist[neigh])
                {
                    dist[neigh] = dist[node] + wt;
                    pq.push({dist[neigh], neigh});
                }
            }
        }

        int ans = 0;

        for (int i = 1; i <= n; i++)
        {
            if (dist[i] == INT_MAX)
                return -1;

            ans = max(ans, dist[i]);
        }

        return ans;
    }
};

int main()
{

    Solution obj;

    vector<vector<int>> times = {
        {2, 1, 1},
        {2, 3, 1},
        {3, 4, 1}};

    int n = 4;
    int k = 2;

    cout << obj.networkDelayTime(times, n, k);

    return 0;
}

/*

===============================================================================
                         LEETCODE 743 - NETWORK DELAY TIME
===============================================================================

Problem Statement
-----------------
You are given a network of n nodes labeled from 1 to n.

times[i] = {ui, vi, wi}
means there is a directed edge from ui to vi taking wi units of time.

A signal starts from node k.

Return the minimum time required for all nodes to receive the signal.
If it is impossible for all nodes to receive the signal, return -1.

------------------------------------------------------------------------------
Example
------------------------------------------------------------------------------

Input:
times = {{2,1,1},{2,3,1},{3,4,1}}
n = 4
k = 2

Graph:

        1
      ↗
2 --------> 3 -----> 4
 \           (1)      (1)
  \ (1)

Output:
2

Explanation:
2 -> 1 = 1
2 -> 3 = 1
2 -> 4 = 2

Maximum distance = 2

===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea
----
Run a shortest path algorithm separately for every node or repeatedly relax
edges until no improvement occurs.

Bellman-Ford can solve the problem.

Pseudo Code
-----------

Build graph

distance[source]=0

Repeat n-1 times

    for every edge(u,v,w)

        if(distance[u]+w < distance[v])

            update distance[v]

If any node unreachable
    return -1

Return maximum distance.

------------------------------------------------------------------------------
Complete Brute Force Code
------------------------------------------------------------------------------

class Solution {
public:

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        vector<int> dist(n+1, INT_MAX);

        dist[k]=0;

        for(int i=1;i<n;i++){

            for(auto &edge:times){

                int u=edge[0];
                int v=edge[1];
                int wt=edge[2];

                if(dist[u]!=INT_MAX && dist[u]+wt<dist[v]){

                    dist[v]=dist[u]+wt;
                }
            }
        }

        int ans=0;

        for(int i=1;i<=n;i++){

            if(dist[i]==INT_MAX)
                return -1;

            ans=max(ans,dist[i]);
        }

        return ans;
    }
};

Time Complexity
---------------
O(V * E)

Space Complexity
----------------
O(V)

===============================================================================
OPTIMAL APPROACH (DIJKSTRA)
===============================================================================

Observation
-----------
All edge weights are non-negative.

Whenever all edge weights are non-negative, Dijkstra gives the shortest
distance from one source to every other node.

Intuition
---------
Maintain the nearest node using a Min Heap.

Whenever a shorter distance is found for a neighbour,
update it and push it into the priority queue.

Finally,

Maximum(shortest distance to every node)
=
Network Delay Time.

If any node remains unreachable,
return -1.

------------------------------------------------------------------------------
Pseudo Code
------------------------------------------------------------------------------

Build adjacency list

distance[]=INF

distance[source]=0

Push (0,source)

while(priority queue not empty)

    pop minimum distance node

    if outdated
        continue

    relax every neighbour

Find maximum distance

If any node INF
    return -1

Else return maximum distance

------------------------------------------------------------------------------
Complete Optimal Code
------------------------------------------------------------------------------

class Solution {
public:

    int networkDelayTime(vector<vector<int>>& times, int n, int k){

        vector<vector<pair<int,int>>> graph(n+1);

        for(auto &edge:times){

            graph[edge[0]].push_back({edge[1],edge[2]});
        }

        vector<int> dist(n+1,INT_MAX);

        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        dist[k]=0;

        pq.push({0,k});

        while(!pq.empty()){

            auto [curr,node]=pq.top();

            pq.pop();

            if(curr>dist[node])
                continue;

            for(auto &it:graph[node]){

                int neigh=it.first;
                int wt=it.second;

                if(dist[node]+wt<dist[neigh]){

                    dist[neigh]=dist[node]+wt;

                    pq.push({dist[neigh],neigh});
                }
            }
        }

        int ans=0;

        for(int i=1;i<=n;i++){

            if(dist[i]==INT_MAX)
                return -1;

            ans=max(ans,dist[i]);
        }

        return ans;
    }
};

Time Complexity
---------------
O((V+E) log V)

Space Complexity
----------------
O(V+E)

===============================================================================
DRY RUN
===============================================================================

Source = 2

Initially

dist = [INF, INF, 0, INF, INF]

PQ

(0,2)

--------------------------------

Pop

(0,2)

Update

1 = 1

3 = 1

PQ

(1,1)
(1,3)

--------------------------------

Pop

(1,1)

No neighbours

--------------------------------

Pop

(1,3)

Update

4 = 2

PQ

(2,4)

--------------------------------

Pop

(2,4)

Done

Distances

1 -> 1

2 -> 0

3 -> 1

4 -> 2

Maximum = 2

Answer = 2

===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern
-------
Single Source Shortest Path

Key Observation
---------------
Whenever graph has non-negative weights and shortest distance from one source
is required, Dijkstra is usually the optimal choice.

Common Mistakes
---------------
1. Using max heap instead of min heap.
2. Forgetting graph is directed.
3. Using vector<int> dist(n) instead of n+1.
4. Forgetting outdated node check.
5. Returning minimum instead of maximum distance.
6. Forgetting to return -1 for unreachable nodes.

When to use this approach
-------------------------
✓ Non-negative edge weights
✓ Directed or Undirected graph
✓ Single source shortest path
✓ Sparse graphs where Dijkstra is efficient

===============================================================================

*/
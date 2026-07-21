#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        // Bellman-Ford for at most (k+1) edges
        for(int i = 0; i <= k; i++) {

            vector<int> temp = dist;

            for(auto &flight : flights) {

                int u = flight[0];
                int v = flight[1];
                int cost = flight[2];

                if(dist[u] == INT_MAX)
                    continue;

                temp[v] = min(temp[v], dist[u] + cost);
            }

            dist = temp;
        }

        return (dist[dst] == INT_MAX) ? -1 : dist[dst];
    }
};

int main() {

    Solution obj;

    int n = 4;

    vector<vector<int>> flights = {
        {0,1,100},
        {1,2,100},
        {2,3,100},
        {0,2,500}
    };

    int src = 0;
    int dst = 3;
    int k = 1;

    cout << obj.findCheapestPrice(n, flights, src, dst, k);

    return 0;
}

/*

==========================
Problem Statement
==========================

There are n cities connected by flights.

Each flight is represented as:
[from, to, price]

Given:
- source city (src)
- destination city (dst)
- maximum K stops

Return the cheapest price from src to dst with at most K stops.
If no such route exists, return -1.

----------------------------------------------------

Example

Input:

n = 4

Flights

0 -> 1 (100)
1 -> 2 (100)
2 -> 3 (100)
0 -> 2 (500)

src = 0
dst = 3
k = 1

Output

600

Explanation

Allowed edges = K + 1 = 2

Possible paths

0->2->3 = 600

0->1->2->3 uses 3 edges (2 stops)
Not allowed.

====================================================
Brute Force Approach
====================================================

Idea

Generate every possible path from src to dst using DFS.

Keep track of

- current cost
- current stops

Whenever destination is reached,
update minimum answer.

Pseudo Code

DFS(node,cost,stops)

if stops > K+1
    return

if node == destination
    answer=min(answer,cost)

for every neighbour
    DFS(next,cost+weight,stops+1)

----------------------------------------------------
Complete Brute Force Code

class Solution {
public:

    int ans = INT_MAX;

    void dfs(int node,int dst,int stops,int k,int cost,
             vector<vector<pair<int,int>>>& adj){

        if(stops>k+1)
            return;

        if(node==dst){
            ans=min(ans,cost);
            return;
        }

        for(auto &it:adj[node]){
            dfs(it.first,dst,stops+1,k,cost+it.second,adj);
        }
    }

    int findCheapestPrice(int n,
                          vector<vector<int>>& flights,
                          int src,
                          int dst,
                          int k){

        vector<vector<pair<int,int>>> adj(n);

        for(auto &e:flights)
            adj[e[0]].push_back({e[1],e[2]});

        dfs(src,dst,0,k,0,adj);

        if(ans==INT_MAX)
            return -1;

        return ans;
    }
};

Time Complexity

Exponential

O(Number of possible paths)

Space Complexity

O(Path Length)

====================================================
Optimal Approach (Bellman-Ford)
====================================================

Observation

Bellman-Ford finds shortest path using at most i edges
after the i-th relaxation.

K stops means

Maximum edges allowed = K + 1

Therefore we only relax all edges exactly K+1 times.

Very important:

Each iteration must use the previous distances.

Hence we use a temporary array.

----------------------------------------------------

Intuition

Iteration 0

Use only 1 edge.

Iteration 1

Use at most 2 edges.

Iteration 2

Use at most 3 edges.

...

After K+1 iterations

We have shortest path using at most K+1 edges.

----------------------------------------------------

Pseudo Code

dist[source]=0

Repeat K+1 times

    temp = dist

    for every edge

        if source reachable

            temp[v]=min(temp[v],dist[u]+cost)

    dist=temp

return answer

----------------------------------------------------

Complete Optimal Code

class Solution {
public:

    int findCheapestPrice(int n,
                          vector<vector<int>>& flights,
                          int src,
                          int dst,
                          int k){

        vector<int> dist(n,INT_MAX);

        dist[src]=0;

        for(int i=0;i<=k;i++){

            vector<int> temp=dist;

            for(auto &flight:flights){

                int u=flight[0];
                int v=flight[1];
                int w=flight[2];

                if(dist[u]==INT_MAX)
                    continue;

                temp[v]=min(temp[v],dist[u]+w);
            }

            dist=temp;
        }

        if(dist[dst]==INT_MAX)
            return -1;

        return dist[dst];
    }
};

----------------------------------------------------

Time Complexity

O((K+1) * E)

E = Number of flights

----------------------------------------------------

Space Complexity

O(N)

====================================================
Dry Run
====================================================

Flights

0->1 (100)

1->2 (100)

0->2 (500)

K=1

Initial

dist

0 INF INF

--------------------

Iteration 1

Relax

0->1

dist

0 100 INF

Relax

0->2

dist

0 100 500

--------------------

Iteration 2

Copy previous array

Relax

1->2

New cost

100+100=200

Update

dist

0 100 200

Answer

200

====================================================
Interview Notes
====================================================

Pattern

Single Source Shortest Path

Bellman-Ford

Dynamic Programming on edges

--------------------------------

Key Observation

After i relaxations

Shortest path uses at most i edges.

K stops

=

K+1 edges.

--------------------------------

Common Mistakes

1. Updating original distance array instead of temporary array.

2. Running V-1 iterations instead of K+1.

3. Forgetting INT_MAX check before relaxation.

4. Confusing Stops with Edges.

Maximum edges = Stops + 1.

--------------------------------

When to use this approach

1. Negative edge weights exist.

2. Limited number of edges/stops.

3. Need shortest path with edge constraints.

4. LeetCode 787.

*/

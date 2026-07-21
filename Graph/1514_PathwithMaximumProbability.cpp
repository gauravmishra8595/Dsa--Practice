#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start, int end)
    {

        vector<vector<pair<int, double>>> adj(n);

        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            double p = succProb[i];

            adj[u].push_back({v, p});
            adj[v].push_back({u, p});
        }

        vector<double> prob(n, 0.0);

        priority_queue<pair<double, int>> pq;

        prob[start] = 1.0;
        pq.push({1.0, start});

        while (!pq.empty())
        {

            auto it = pq.top();
            pq.pop();

            double currProb = it.first;
            int node = it.second;

            if (node == end)
                return currProb;

            if (currProb < prob[node])
                continue;

            for (auto &nbr : adj[node])
            {

                int adjNode = nbr.first;
                double edgeProb = nbr.second;

                double newProb = currProb * edgeProb;

                if (newProb > prob[adjNode])
                {
                    prob[adjNode] = newProb;
                    pq.push({newProb, adjNode});
                }
            }
        }

        return 0.0;
    }
};

int main()
{

    Solution obj;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(m, vector<int>(2));
    vector<double> succProb(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i][0] >> edges[i][1] >> succProb[i];
    }

    int start, end;
    cin >> start >> end;

    cout << fixed << setprecision(5)
         << obj.maxProbability(n, edges, succProb, start, end);

    return 0;
}

/*

=========================== Problem Statement ===========================

LeetCode 1514 - Path with Maximum Probability

You are given an undirected weighted graph with n nodes.

Each edge has a success probability.

Find the path from start to end that has the maximum probability of success.

Probability of a path =
product of probabilities of all edges in the path.

Return the maximum probability.
If no path exists, return 0.

=========================================================================

Example

Input

n = 3

edges =
[[0,1],[1,2],[0,2]]

succProb =
[0.5,0.5,0.2]

start = 0
end = 2

Output

0.25000

Explanation

Path 0→1→2

Probability

0.5 × 0.5 = 0.25

which is larger than

0→2 = 0.2

=========================================================================

Brute Force Approach

Idea

Generate every possible path from start to end.

For every path,

calculate the product of probabilities.

Return the maximum.

Pseudo Code

DFS(node)

if destination
    update answer

visit neighbours

Complete Brute Force Code

// class Solution {
// public:
//
// double ans = 0;
//
// void dfs(...) {
//
//     Explore every path
//
// }
//
// double maxProbability(...) {
//
//     dfs(...);
//
//     return ans;
// }
// };

Time Complexity

O(Number of Paths)

Worst Case : Exponential

Space Complexity

O(N)

=========================================================================

Optimal Approach

Observation

Instead of minimizing distance,

we maximize probability.

Normal Dijkstra performs

newDist = dist + weight

Here

newProbability

= currentProbability × edgeProbability

Priority Queue always expands

the node having highest probability.

Hence use Max Heap.

-------------------------------------------------------------------------

Intuition

Maintain

prob[node]

= best probability found so far.

Whenever

current × edgeProbability

improves neighbour,

update it.

The first time destination is removed from Max Heap,

it has the maximum possible probability.

-------------------------------------------------------------------------

Pseudo Code

Build Graph

prob[start]=1

Push start into Max Heap

while heap not empty

    pop highest probability

    if destination
        return probability

    relax neighbours

return 0

-------------------------------------------------------------------------

Complete Optimal Code

class Solution {
public:

double maxProbability(int n,
vector<vector<int>>& edges,
vector<double>& succProb,
int start,
int end) {

    vector<vector<pair<int,double>>> adj(n);

    for(int i=0;i<edges.size();i++){

        int u=edges[i][0];
        int v=edges[i][1];

        adj[u].push_back({v,succProb[i]});
        adj[v].push_back({u,succProb[i]});
    }

    vector<double> prob(n,0);

    priority_queue<pair<double,int>> pq;

    prob[start]=1;

    pq.push({1,start});

    while(!pq.empty()){

        auto it=pq.top();
        pq.pop();

        double curr=it.first;
        int node=it.second;

        if(node==end)
            return curr;

        if(curr<prob[node])
            continue;

        for(auto &x:adj[node]){

            int adjNode=x.first;
            double edge=x.second;

            if(curr*edge>prob[adjNode]){

                prob[adjNode]=curr*edge;

                pq.push({prob[adjNode],adjNode});
            }
        }
    }

    return 0;
}
};

Time Complexity

O((V + E) log V)

Space Complexity

O(V + E)

=========================================================================

Dry Run

Input

0 --0.5-- 1 --0.5-- 2

 \

0.2

 \

 2

Initially

prob[0]=1

Heap

(1,0)

Pop

0

Update

1 → 0.5

2 → 0.2

Heap

0.5
0.2

Pop

1

Update

2

0.5 × 0.5 = 0.25

0.25 > 0.2

Update

Heap

0.25

Destination reached

Answer = 0.25

=========================================================================

Interview Notes

Pattern

Modified Dijkstra

Maximum Path Problem

Graph

Priority Queue

Key Observation

Replace

addition

with

multiplication.

Instead of minimizing cost,

maximize probability.

Common Mistakes

1. Using Min Heap instead of Max Heap.

2. Adding probabilities instead of multiplying.

3. Forgetting stale heap entries.

4. Using BFS because all probabilities differ.

When to use this approach

Whenever

Path Score

=

maximum product

or

maximum reliability

or

maximum success probability.

This is a direct application of Modified Dijkstra.

=========================================================================

*/
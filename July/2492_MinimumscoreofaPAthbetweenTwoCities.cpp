#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution
{
private:
    vector<vector<pair<int, int>>> adj;
    vector<bool> visited;
    int answer;

    void dfs(int node)
    {
        visited[node] = true;

        for (auto &it : adj[node])
        {
            int neighbour = it.first;
            int weight = it.second;

            // Keep track of the minimum edge seen so far
            answer = min(answer, weight);

            if (!visited[neighbour])
            {
                dfs(neighbour);
            }
        }
    }

public:
    int minScore(int n, vector<vector<int>> &roads)
    {
        adj.resize(n + 1);
        visited.assign(n + 1, false);
        answer = INT_MAX;

        // Build Graph
        for (auto &road : roads)
        {
            int u = road[0];
            int v = road[1];
            int w = road[2];

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Traverse the connected component of city 1
        dfs(1);

        return answer;
    }
};

int main()
{
    int n = 4;

    vector<vector<int>> roads =
    {
        {1, 2, 9},
        {2, 3, 6},
        {2, 4, 5},
        {1, 4, 7}
    };

    Solution obj;

    cout << "Minimum Score = " << obj.minScore(n, roads);

    return 0;
}
/*
===========================================================
LeetCode 2492 - Minimum Score of a Path Between Two Cities
===========================================================

Problem:
You are given n cities connected by bidirectional roads.
Each road = {city1, city2, distance}.

The score of a path is the minimum edge weight present in that path.

Return the minimum possible score of a path between city 1 and city n.

-----------------------------------------------------------
Brute Force Approach (Not Feasible)
-----------------------------------------------------------

Idea:
1. Generate every possible path from city 1 to city n.
2. For every path:
      - Find the minimum edge weight in that path.
      - Update the global answer.
3. Return the minimum score.

Example

1 -----9-----2------6------3
 \             |
  \7           |5
   \           |
    -----------4

Possible Paths

1 -> 2 -> 3
Minimum Edge = 6

1 -> 4 -> 2 -> 3
Minimum Edge = 5

Answer = min(6,5) = 5

Why Brute Force Fails?

There can be exponentially many paths.

Worst Time Complexity:
O(2^N)

Since N can be 100000,
this approach is impossible (TLE).

-----------------------------------------------------------
Optimal Approach (DFS)
-----------------------------------------------------------

Observation:

The problem states:

"You may visit a city or road multiple times."

This is the key observation.

Since revisiting is allowed, we don't need the shortest path.

If city n belongs to the same connected component as city 1,
we can travel around the component as many times as needed.

Therefore,

Answer =
Minimum edge weight present in the connected component
containing city 1.

Algorithm

1. Build an adjacency list.
2. Start DFS from city 1.
3. While traversing every edge:
       answer = min(answer, edgeWeight)
4. Continue DFS until every reachable city is visited.
5. Return answer.

Time Complexity:
O(V + E)

Space Complexity:
O(V + E)

===========================================================
*/

/*
==========================
Dry Run
==========================

Graph

      9
1 -------- 2
|          | \
|7         |5 \6
|          |   \
4 ---------     3

Start DFS from city 1

answer = INF

Visit Edge (1,2,9)
answer = 9

Visit Edge (2,3,6)
answer = 6

Visit Edge (2,4,5)
answer = 5

Visit Edge (4,1,7)
answer = min(5,7) = 5

DFS Complete

Final Answer = 5

==========================
Why Does This Work?
==========================

Because revisiting roads and cities is allowed, we are free to
move anywhere inside the connected component containing city 1.

Hence every road in that connected component is reachable.

Therefore, the minimum score is simply the smallest edge weight
present in that connected component.

This is exactly what DFS computes.

Overall Complexity

Time  : O(V + E)
Space : O(V + E)
*/
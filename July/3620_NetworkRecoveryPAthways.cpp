#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int findMaxPathScore(vector<vector<int>> &edges, vector<bool> &online, long long k)
    {
        int n = online.size();
        vector<vector<pair<int, int>>> g(n);
        int max_w = 0;

        // 1. Correct Graph Construction (Directed Graph)
        // We only add edges where both the starting node (u) and ending node (v) are online.
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            max_w = max(max_w, w);

            if (online[u] && online[v])
            {
                g[u].emplace_back(v, w); // Directed connection from u -> v
            }
        }

        // Helper lambda function to run Dijkstra's algorithm.
        // It checks if we can travel from 0 to n-1 using ONLY edges >= mid, within total cost k.
        auto isValid = [&](int mid) -> bool
        {
            vector<long long> dist(n, LLONG_MAX);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

            dist[0] = 0;
            pq.emplace(0, 0); // Start processing from source node 0

            while (!pq.empty())
            {
                auto [d, u] = pq.top();
                pq.pop();

                if (d > dist[u])
                    continue;
                if (u == n - 1)
                    return d <= k; // Early exit if we reached the destination

                for (auto &[v, w] : g[u])
                {
                    // Filter: Skip any edge whose weight is strictly less than our threshold 'mid'
                    if (w >= mid && dist[v] > d + w)
                    {
                        dist[v] = d + w;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist[n - 1] <= k;
        };

        // Initial feasibility check: if we can't even reach n-1 with zero filtering, return -1
        if (!isValid(0))
            return -1;

        // 2. Binary Search on the Minimum Edge Weight Range
        int l = 0, r = max_w;
        int ans = 0;

        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (isValid(mid))
            {
                ans = mid;   // mid is a valid minimum bottleneck; record it!
                l = mid + 1; // Try to see if we can push for a larger minimum constraint
            }
            else
            {
                r = mid - 1; // mid is too strict (destroys vital paths), back down the limit
            }
        }

        return ans;
    }
};

int main()
{
    Solution solver;

    // Test Case Setup
    int n = 4;
    vector<bool> online = {true, true, true, true};

    // Directed Edges represented as {from, to, weight}
    vector<vector<int>> edges = {
        {0, 1, 10},
        {1, 3, 20},
        {0, 2, 5},
        {2, 3, 15}};

    long long k = 35; // Maximum total cost budget

    int result = solver.findMaxPathScore(edges, online, k);

    cout << "--- VS Code Execution ---" << endl;
    cout << "Maximum valid path score: " << result << endl;

    return 0;
}

/* ==========================================================================================
                                APPROACH EXPLANATIONS
==========================================================================================

1. THE BRUTE FORCE APPROACH (Why it fails / TLE)
------------------------------------------------------------------------------------------
- How it works:
  A brute-force strategy relies on backtracking or Depth First Search (DFS) to traverse
  every single unique path from the source node (0) to the destination node (n-1).

- Mechanism:
  1. Use DFS starting from node 0. Keep track of the nodes visited to avoid cycles.
  2. For every step along a path, maintain two tracking variables:
     - The cumulative sum of all edge weights taken so far.
     - The lowest individual edge weight seen across the current path (the bottleneck).
  3. When the destination node (n-1) is reached, look at the running sum. If `sum <= k`,
     compare the current path's bottleneck weight to a global maximum variable and maximize it.

- Complexity Analysis:
  - Time Complexity: O(2^E) or O(V!), where V is vertices and E is edges. In worst-case
    dense graphs, exploring every permutation of paths scales exponentially, resulting in
    a definitive Time Limit Exceeded (TLE) on LeetCode.


2. THE OPTIMAL APPROACH (Binary Search + Modified Dijkstra)
------------------------------------------------------------------------------------------
Instead of finding all paths and checking their configurations, we invert the goal using
monotonic properties: If we can successfully complete a path where every edge is >= 20,
we can definitely complete it when the bar is lowered to >= 10. This structural property allows
Binary Search.

- Mechanism:
  1. Establish Search Range: The minimum potential edge weight threshold is 0. The maximum is
     the heaviest edge weight in the entire graph (`max_w`).
  2. Pick a Guess (`mid`): Assume `mid` is our strict quality score limit. We dynamically
     ban any edge in the graph whose weight is lower than `mid`.
  3. Run Dijkstra's Algorithm: Starting from node 0, we try to reach node n-1.
     - During graph exploration, we act as if any edge with `weight < mid` does not exist.
     - Dijkstra ensures we discover the absolute absolute cheapest paths under this restriction.
  4. Evaluate Condition:
     - If the shortest total path found to `n-1` is `<= k`, our guess `mid` is perfectly safe.
       We save it (`ans = mid`) and narrow our search range to the right half (`l = mid + 1`)
       to try and find an even higher bottleneck score.
     - If the shortest path is `> k` (or `n-1` becomes entirely unreachable because we banned too
       many small edges), then `mid` is too high. We narrow our search range to the left
       half (`r = mid - 1`).

- Complexity Analysis:
  - Time Complexity: O(log(Max_W) * E log V)
    Where `Max_W` is the range of weights, and `E log V` is the time complexity of running
    Dijkstra's algorithm via a priority queue. This runs effortlessly within execution limits.
  - Space Complexity: O(V + E) to store the adjacency list representation of the network.
*/
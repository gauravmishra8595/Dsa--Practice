#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int n = heights.size();
        int m = heights[0].size();

        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>>
            pq;

        dist[0][0] = 0;
        pq.push({0, {0, 0}});

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();

            int effort = it.first;
            int r = it.second.first;
            int c = it.second.second;

            if (r == n - 1 && c == m - 1)
                return effort;

            if (effort > dist[r][c])
                continue;

            for (int k = 0; k < 4; k++)
            {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m)
                {
                    int newEffort = max(effort, abs(heights[r][c] - heights[nr][nc]));

                    if (newEffort < dist[nr][nc])
                    {
                        dist[nr][nc] = newEffort;
                        pq.push({newEffort, {nr, nc}});
                    }
                }
            }
        }

        return 0;
    }
};

int main()
{
    Solution obj;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> heights(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> heights[i][j];

    cout << obj.minimumEffortPath(heights);

    return 0;
}

/*

========================== Problem Statement ==========================

LeetCode 1631 - Path With Minimum Effort

You are given an m x n grid heights.

You start from (0,0) and want to reach (m-1,n-1).

The effort of a path is defined as the maximum absolute difference
between heights of two consecutive cells in the path.

Return the minimum effort required.

=======================================================================

Example

Input

3 3

1 2 2
3 8 2
5 3 5

Output

2

Explanation

One optimal path is

1 → 3 → 5 → 3 → 5

Maximum absolute difference = 2

=======================================================================

Brute Force Approach

Idea

Generate every possible path from source to destination.

For every path,
calculate the maximum absolute difference.

Return the minimum among all paths.

Pseudo Code

DFS(i,j)

if destination
    update answer

visit neighbours

Complete Brute Force Code

// class Solution {
// public:
//
// int ans = INT_MAX;
//
// void dfs(...){
//
//     Explore all paths
//
// }
//
// int minimumEffortPath(vector<vector<int>>& heights) {
//
//     dfs(...);
//
//     return ans;
// }
// };

Time Complexity

Exponential

O(4^(N*M))

Space Complexity

O(N*M)

=======================================================================

Optimal Approach

Observation

Instead of minimizing total cost,
we minimize the maximum edge weight.

Whenever moving to a neighbour,

newEffort

= max(currentEffort,
      abs(height difference))

This is exactly a modified Dijkstra.

-----------------------------------------------------------------------

Intuition

Normal Dijkstra stores

minimum sum distance.

Here we store

minimum possible maximum effort.

Priority Queue always expands the cell having
smallest effort so far.

The first time destination is popped,
its answer is optimal.

-----------------------------------------------------------------------

Pseudo Code

dist[][] = INF

priority queue

push source

while queue not empty

    pop smallest effort

    for every neighbour

        newEffort =
        max(currentEffort,
            edgeWeight)

        relax

return answer

-----------------------------------------------------------------------

Complete Optimal Code

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {

        int n=heights.size();
        int m=heights[0].size();

        vector<vector<int>> dist(n,vector<int>(m,INT_MAX));

        priority_queue<
        pair<int,pair<int,int>>,
        vector<pair<int,pair<int,int>>>,
        greater<pair<int,pair<int,int>>>> pq;

        pq.push({0,{0,0}});
        dist[0][0]=0;

        int dr[]={-1,0,1,0};
        int dc[]={0,1,0,-1};

        while(!pq.empty()){

            auto it=pq.top();
            pq.pop();

            int effort=it.first;
            int r=it.second.first;
            int c=it.second.second;

            if(r==n-1 && c==m-1)
                return effort;

            if(effort>dist[r][c]) continue;

            for(int k=0;k<4;k++){

                int nr=r+dr[k];
                int nc=c+dc[k];

                if(nr>=0 && nr<n && nc>=0 && nc<m){

                    int newEffort=max(
                        effort,
                        abs(heights[r][c]-heights[nr][nc])
                    );

                    if(newEffort<dist[nr][nc]){

                        dist[nr][nc]=newEffort;
                        pq.push({newEffort,{nr,nc}});
                    }
                }
            }
        }

        return 0;
    }
};

Time Complexity

O(N*M * log(N*M))

Space Complexity

O(N*M)

=======================================================================

Dry Run

Input

1 2 2
3 8 2
5 3 5

Initially

dist[0][0]=0

Move

1→2 effort=1

1→3 effort=2

Next smallest effort

2

Continue relaxing.

Eventually destination gets effort

2

Answer = 2

=======================================================================

Interview Notes

Pattern

Modified Dijkstra
Shortest Path on Grid

Key Observation

Distance is NOT cumulative.

Distance = maximum edge weight encountered so far.

Common Mistakes

1. Using BFS.

2. Adding edge weights instead of taking maximum.

3. Forgetting stale priority queue entries.

4. Using normal shortest path relaxation.

When to use this approach

Whenever path cost is defined as

minimum possible maximum value

instead of

minimum sum.

This is a classic "Minimax Path" problem and is solved efficiently
using Modified Dijkstra.

=======================================================================

*/
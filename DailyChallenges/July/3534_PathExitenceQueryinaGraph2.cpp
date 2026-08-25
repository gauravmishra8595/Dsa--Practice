#include <bits/stdc++.h>
using namespace std;

constexpr int L = 18;
constexpr int N = 100000 + 5;

using pii = pair<int, int>;

int up[L][N];
int pos[N];
pii xId[N];

class Solution {
public:
    static int cnt(int u, int v, int LOG) {
        if (u == v) return 0;

        if (up[0][u] >= v)
            return 1;

        if (up[LOG - 1][u] < v)
            return -1;

        int steps = 0;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] < v) {
                steps += (1 << j);
                u = up[j][u];
            }
        }

        return steps + 1;
    }

    vector<int> pathExistenceQueries(int n,
                                     vector<int>& nums,
                                     int maxDiff,
                                     vector<vector<int>>& queries) {

        int LOG = std::bit_width((unsigned)n) + 1;

        for (int i = 0; i < n; i++)
            xId[i] = {nums[i], i};

        sort(xId, xId + n);

        for (int i = 0; i < n; i++)
            pos[xId[i].second] = i;

        // Sliding Window
        for (int l = 0, r = 0; l < n; l++) {
            while (r + 1 < n &&
                   xId[r + 1].first - xId[l].first <= maxDiff)
                r++;

            up[0][l] = r;
        }

        // Binary Lifting
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            auto [u, v] = minmax(pos[q[0]], pos[q[1]]);
            ans.push_back(cnt(u, v, LOG));
        }

        return ans;
    }
};

int main() {

    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int maxDiff;
    cin >> maxDiff;

    int q;
    cin >> q;

    vector<vector<int>> queries(q, vector<int>(2));

    for (int i = 0; i < q; i++)
        cin >> queries[i][0] >> queries[i][1];

    Solution obj;

    vector<int> ans = obj.pathExistenceQueries(n, nums, maxDiff, queries);

    for (int x : ans)
        cout << x << " ";

    cout << endl;

    return 0;
}

/*
==========================
Brute Force Approach
==========================

Idea:
-----
1. Build the graph.
2. For every pair (i,j):
      if(abs(nums[i]-nums[j])<=maxDiff)
          connect i and j.
3. For every query run BFS to find minimum edges.

Code:

vector<int> answer;
for(auto &q:queries){

    vector<int> dist(n,-1);
    queue<int> qu;

    qu.push(q[0]);
    dist[q[0]]=0;

    while(!qu.empty()){

        int u=qu.front();
        qu.pop();

        for(int v:adj[u]){

            if(dist[v]==-1){

                dist[v]=dist[u]+1;
                qu.push(v);
            }
        }
    }

    answer.push_back(dist[q[1]]);
}

Time Complexity

Building Graph = O(n²)

Each Query BFS = O(n²)

Total

O(n² + q*n²)

Not possible for n=100000.


====================================================
Optimal Approach (Sliding Window + Binary Lifting)
====================================================

Observation
-----------
Sort nodes according to nums.

Suppose

value:
1 3 5 7 8 11

If maxDiff=3

From 1 we can directly reach upto 3.

From 3 we can reach upto 7.

Instead of storing all edges,
store only the farthest reachable position.

Step 1
------
Sort (value,index)

Example

value
1 3 5 7 8 11

position
0 1 2 3 4 5

Step 2
------
Sliding Window

Maintain

l
r

Move r while

value[r]-value[l]<=maxDiff

Then

up[0][l]=r

Meaning

From l
one jump reaches r.

Time

O(n)

Step 3
------
Binary Lifting

up[k][i]

=
after 2^k jumps
where do we reach?

Formula

up[k][i]=up[k-1][ up[k-1][i] ]

Time

O(n log n)

Step 4
------
Answer Query

Suppose

u
v

Need minimum jumps.

Greedily jump using largest powers.

for(j=LOG-1;j>=0;j--)

if(up[j][u]<v)

jump.

Finally answer=steps+1.

Complexities
------------

Sorting          O(n log n)

Sliding Window   O(n)

Binary Lifting   O(n log n)

Each Query       O(log n)

Overall

O((n+q) log n)

Space

O(n log n)

This is the intended solution for LeetCode 3534.
*/
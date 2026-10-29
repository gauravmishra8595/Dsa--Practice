#include <bits/stdc++.h>
using namespace std;
class Solution
{
    int n, LOG, timer = 0;
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, bit;
    vector<int> euler;
    string s;
    void add(int idx, int mask)
    {
        for (int i = idx; i <= n; i += i & -i)
            bit[i] ^= mask;
    }
    int get(int idx)
    {
        int mask = 0;
        for (int i = idx; i > 0; i -= i & -i)
            mask ^= bit[i];
        return mask;
    }
    void rangeXor(int l, int r, int mask)
    {
        add(l, mask);
        if (r < n)
            add(r + 1, mask);
    }
    int prefixMask(int u)
    {
        return get(tin[u]);
    }
    void dfs(int root)
    {
        vector<int> parent(n, -1);
        vector<pair<int, bool>> st;
        st.push_back({root, false});
        parent[root] = root;

        while (!st.empty())
        {
            auto [u, exiting] = st.back();
            st.pop_back();

            if (exiting)
            {
                tout[u] = timer;
                continue;
            }

            tin[u] = ++timer;
            euler[timer] = u;

            up[0][u] = parent[u];
            for (int j = 1; j < LOG; ++j)
                up[j][u] = up[j - 1][up[j - 1][u]];

            depth[u] = (u == root ? 0 : depth[parent[u]] + 1);

            st.push_back({u, true});

            for (int v : adj[u])
            {
                if (v == parent[u])
                    continue;
                parent[v] = u;
                st.push_back({v, false});
            }
        }
    }

    int lca(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];
        for (int j = 0; j < LOG; ++j)
            if (diff & (1 << j))
                u = up[j][u];

        if (u == v)
            return u;

        for (int j = LOG - 1; j >= 0; --j)
        {
            if (up[j][u] != up[j][v])
            {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>> &edges,
                                string s, vector<string> &queries)
    {
        this->n = n;
        this->s = s;
        timer = 0;

        LOG = 1;
        while ((1 << LOG) <= n)
            ++LOG;

        adj.assign(n, {});
        up.assign(LOG, vector<int>(n));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        bit.assign(n + 1, 0);
        euler.assign(n + 1, 0);

        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0);

        for (int u = 0; u < n; ++u)
        {
            int mask = 1 << (s[u] - 'a');
            rangeXor(tin[u], tout[u], mask);
        }

        vector<bool> ans;

        for (const string &q : queries)
        {
            string op;
            int u, v;
            char c;

            stringstream ss(q);
            ss >> op >> u;

            if (op == "update")
            {
                ss >> c;
                int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));

                rangeXor(tin[u], tout[u], delta);
                s[u] = c;
            }
            else
            {
                ss >> v;
                int w = lca(u, v);

                int mask = prefixMask(u) ^ prefixMask(v) ^ (1 << (s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}};
    string s = "aac";

    vector<string> queries = {
        "query 0 2",
        "update 1 b",
        "query 0 2"};

    Solution sol;
    vector<bool> ans = sol.palindromePath(n, edges, s, queries);

    cout << "[";
    for (int i = 0; i < (int)ans.size(); ++i)
    {
        if (i)
            cout << ", ";
        cout << (ans[i] ? "true" : "false");
    }
    cout << "]\n";

    return 0;
}

/*
============================================================
LEETCODE 3841: PALINDROMIC PATH QUERIES IN A TREE
============================================================

PROBLEM STATEMENT
-----------------
Given a tree whose nodes contain lowercase letters, process:
1. update u c: Change the character at node u to c.
2. query u v: Determine whether the characters on the path from
   u to v can be rearranged into a palindrome.

A palindrome permutation is possible if at most one character
has an odd frequency.

EXAMPLE
-------
n = 3
edges = [[0,1],[1,2]]
s = "aac"
queries = ["query 0 2", "update 1 b", "query 0 2"]

Output: [true, false]

BRUTE FORCE APPROACH
--------------------

Idea:
- For every query, traverse the unique path between u and v.
- Count the frequency of each character on the path.
- Check whether at most one frequency is odd.
- For updates, directly replace the character.

Pseudo Code:
    for each query:
        if update:
            s[u] = c
        else:
            find path from u to v using DFS/BFS
            count characters on path
            odd = number of odd frequencies
            answer = (odd <= 1)

Complete Brute Force Code (revision only):

    vector<bool> bruteForce(
        int n, vector<vector<int>>& edges,
        string s, vector<string>& queries
    ) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> ans;

        for (string q : queries) {
            string op;
            int u, v;
            char c;

            stringstream ss(q);
            ss >> op >> u;

            if (op == "update") {
                ss >> c;
                s[u] = c;
                continue;
            }

            ss >> v;

            vector<int> parent(n, -1);
            queue<int> qu;
            qu.push(u);
            parent[u] = u;

            while (!qu.empty()) {
                int x = qu.front();
                qu.pop();

                if (x == v) break;

                for (int y : adj[x]) {
                    if (parent[y] != -1) continue;
                    parent[y] = x;
                    qu.push(y);
                }
            }

            int freq[26] = {};

            for (int x = v;; x = parent[x]) {
                freq[s[x] - 'a']++;
                if (x == u) break;
            }

            int odd = 0;
            for (int i = 0; i < 26; ++i)
                odd += freq[i] % 2;

            ans.push_back(odd <= 1);
        }

        return ans;
    }

Time Complexity:
- O(n + q*n) in the worst case.
- Each query may traverse the tree and inspect a path.

Space Complexity:
- O(n) for adjacency lists, BFS parent array, and queue.

OPTIMAL APPROACH
----------------

Observation:
A string can be rearranged into a palindrome iff at most one
character occurs an odd number of times.

Intuition:
- Represent each character by one bit: 1 << (c - 'a').
- XOR toggles parity: even occurrences cancel; odd occurrences
  leave their bit set.
- Let P[u] be the XOR of character masks from the root to u.
- For w = LCA(u, v), the path mask is:

      P[u] XOR P[v] XOR mask(s[w])

  The LCA is included once after the two root prefixes cancel.

Dynamic updates:
- Changing a node from old character to new character changes
  its mask by:

      delta = mask(old) XOR mask(new)

- Every root-to-node prefix for a node in that subtree changes
  by delta.
- DFS entry/exit times make each subtree a contiguous interval.
- A Fenwick tree supports range XOR updates and point queries
  using a difference-array technique.
- Binary lifting finds the LCA in O(log n).

Pseudo Code:
    build adjacency list
    run iterative DFS to compute:
        tin, tout, depth, binary-lifting ancestors

    for each node u:
        apply its character mask to subtree [tin[u], tout[u]]

    for each query:
        if update u c:
            delta = mask(s[u]) XOR mask(c)
            rangeXor(tin[u], tout[u], delta)
            s[u] = c
        else:
            w = LCA(u, v)
            mask = prefixMask(u) XOR prefixMask(v)
                   XOR mask(s[w])
            answer = ((mask & (mask - 1)) == 0)

Complete Optimal Code (revision only):

    // Core path query:
    int w = lca(u, v);

    int mask = prefixMask(u) ^ prefixMask(v)
             ^ (1 << (s[w] - 'a'));

    bool possible = ((mask & (mask - 1)) == 0);

    // Core character update:
    int delta = (1 << (s[u] - 'a'))
              ^ (1 << (c - 'a'));

    rangeXor(tin[u], tout[u], delta);
    s[u] = c;

    // The complete implementation is the Solution class above.

Time Complexity:
- DFS and preprocessing: O(n log n).
- Each update: O(log n).
- Each query: O(log n) for LCA and Fenwick operations.
- Total: O(n log n + q log n).

Space Complexity:
- O(n log n) for binary lifting.
- O(n) for adjacency lists, Euler intervals, and Fenwick tree.
- Total: O(n log n).

DRY RUN
-------
Initial tree:
    0(a) -- 1(a) -- 2(c)

Query 0 2:
    Path characters = "aac"
    a occurs twice; c occurs once.
    Path mask = bit(c)
    Only one bit is set.
    Result = true.

Update 1 b:
    Old mask = bit(a)
    New mask = bit(b)
    Delta = bit(a) XOR bit(b)
    Apply delta to subtree of node 1.
    Current labels = "abc".

Query 0 2:
    Path characters = "abc"
    Path mask = bit(a) XOR bit(b) XOR bit(c)
    Three bits are set.
    Result = false.

Final output:
    [true, false]

INTERVIEW NOTES
---------------

Pattern:
- Tree path queries
- Lowest Common Ancestor (LCA)
- Binary lifting
- Bitmask parity
- Euler tour + Fenwick tree
- Subtree range XOR updates

Key Observation:
- Palindrome permutation depends on character parity, not order.
- A 26-bit integer represents all character parities.
- A mask is valid iff it has at most one set bit:
      (mask & (mask - 1)) == 0

Common Mistakes:
- Forgetting to include the LCA character exactly once.
- Updating only the node instead of its entire subtree's prefixes.
- Using incorrect Euler interval boundaries.
- Forgetting to update s[u] after processing an update.
- Using recursion on a long chain and risking stack overflow.
- Confusing a palindrome itself with a rearrangement into one.

When to Use This Approach:
- Dynamic tree labels with path parity queries.
- Small alphabets that fit into a bitmask.
- Subtree range updates and point queries.
- Problems combining LCA with XOR or parity.
============================================================
*/
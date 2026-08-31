#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> parent, sz;

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b, vector<vector<int>> &restrictions)
    {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb)
            return true;

        // Check whether merging these two components violates
        // any restriction.
        for (auto &r : restrictions)
        {
            int pr1 = find(r[0]);
            int pr2 = find(r[1]);

            if ((pr1 == pa && pr2 == pb) ||
                (pr1 == pb && pr2 == pa))
            {
                return false;
            }
        }

        if (sz[pa] < sz[pb])
            swap(pa, pb);

        parent[pb] = pa;
        sz[pa] += sz[pb];

        return true;
    }

    vector<bool> friendRequests(
        int n,
        vector<vector<int>> &restrictions,
        vector<vector<int>> &requests)
    {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        vector<bool> ans;

        for (auto &request : requests)
        {
            int u = request[0];
            int v = request[1];

            if (unite(u, v, restrictions))
                ans.push_back(true);
            else
                ans.push_back(false);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    int n = 3;

    vector<vector<int>> restrictions = {
        {0, 1}};

    vector<vector<int>> requests = {
        {0, 2},
        {2, 1}};

    vector<bool> ans = obj.friendRequests(
        n,
        restrictions,
        requests);

    for (bool x : ans)
        cout << (x ? "true " : "false ");

    cout << '\n';

    return 0;
}

/*
===============================================================================
             LEETCODE 2076 - PROCESS RESTRICTED FRIEND REQUESTS
                         UNION-FIND / DSU APPROACH
===============================================================================

Problem Statement:
------------------
There are n people numbered from 0 to n-1.

We are given:

    restrictions[i] = [x, y]

which means:

    x and y can NEVER become friends.

We are also given friend requests:

    requests[i] = [u, v]

For every request:

    - If accepting the request does NOT violate any restriction,
      accept it and return true.
    - Otherwise reject it and return false.

Important:
----------
Friendship is transitive.

If:

    0 becomes friends with 2
    2 becomes friends with 3

then:

    0, 2, 3

are in the same friendship group.

Therefore, DSU is a natural choice.


Example:
--------
n = 3

restrictions:

    [0, 1]

requests:

    [0, 2]
    [2, 1]

First request:

    0 and 2 can become friends.

    Components:

        {0, 2}
        {1}

Accept.

Second request:

    2 wants to become friends with 1.

Since 2 is already connected to 0, accepting this would make:

    0 and 1

friends.

But [0, 1] is restricted.

Therefore reject.

Output:

    [true, false]


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Maintain an explicit friendship graph.

For every request (u, v):

    1. Temporarily consider u and v connected.
    2. Find the connected component of u.
    3. Find the connected component of v.
    4. Check whether any restriction pair would end up in the same
       connected component.
    5. If no restriction is violated:
           permanently add the friendship.
       Otherwise:
           reject the request.

We can use DFS/BFS to determine connected components after every request.


Pseudo Code:
-----------
Initialize graph.

For every request (u, v):

    Add edge u <-> v temporarily.

    Find connected components using DFS/BFS.

    For every restriction (a, b):
        if a and b are in the same component:
            request is invalid

    If invalid:
        remove the temporary edge
        answer = false
    Else:
        keep the edge
        answer = true


Complete Brute Force Code:
--------------------------

class Solution {
public:

    bool connected(
        int start,
        int target,
        vector<vector<int>>& graph
    ) {

        int n = graph.size();
        vector<bool> visited(n, false);

        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {

            int u = q.front();
            q.pop();

            if (u == target)
                return true;

            for (int v : graph[u]) {

                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        return false;
    }

    vector<bool> friendRequests(
        int n,
        vector<vector<int>>& restrictions,
        vector<vector<int>>& requests
    ) {

        vector<vector<int>> graph(n);
        vector<bool> ans;

        for (auto &req : requests) {

            int u = req[0];
            int v = req[1];

            // Temporarily add friendship.
            graph[u].push_back(v);
            graph[v].push_back(u);

            bool valid = true;

            for (auto &r : restrictions) {

                if (connected(r[0], r[1], graph)) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {

                // Remove temporary edge.
                graph[u].pop_back();
                graph[v].pop_back();

                ans.push_back(false);

            } else {

                ans.push_back(true);
            }
        }

        return ans;
    }
};


Time Complexity:
----------------
For each request, we may run BFS/DFS for every restriction.

Approximately:

    O(Q * R * (N + Q))

where:

    N = number of people
    Q = number of requests
    R = number of restrictions

This is too expensive for large constraints.


Space Complexity:
-----------------
O(N + Q)

For the friendship graph and traversal arrays.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
We don't actually need to maintain the complete friendship graph.

We only care about:

    Which people belong to the same friendship group?

This is exactly what DSU maintains.

Suppose:

    0 -- 2 -- 3

Then DSU tells us:

    find(0) == find(2) == find(3)

So they are effectively one group.


Core Idea:
----------
For a request:

    [u, v]

we want to merge the components containing u and v.

Let:

    A = find(u)
    B = find(v)

Before merging, we must check every restriction [x, y].

If:

    find(x) == A AND find(y) == B

or:

    find(x) == B AND find(y) == A

then merging A and B would put x and y into the same component.

That violates the restriction.

Therefore:

    Reject the request.


Otherwise:

    Merge A and B.


Intuition:
----------
Suppose we have:

    Restriction:
        [0, 1]

Current friendship groups:

    {0, 2}
    {1}

Request:

    [2, 1]

Before merging:

    find(2) = group {0, 2}
    find(1) = group {1}

Restriction:

    [0, 1]

We get:

    find(0) = group {0, 2}
    find(1) = group {1}

So if we merge the two groups:

    {0, 1, 2}

The restriction is violated.

Therefore:

    false


Another important case:

Restriction:

    [0, 1]

Current groups:

    {0, 2}
    {1, 3}

Request:

    [2, 3]

Here:

    find(2) = {0, 2}
    find(3) = {1, 3}

Restriction [0,1] would become inside the same component.

Therefore reject.


Pseudo Code:
-----------
Initialize DSU.

For every request [u, v]:

    pu = find(u)
    pv = find(v)

    valid = true

    For every restriction [x, y]:

        px = find(x)
        py = find(y)

        If:
            (px == pu AND py == pv)
            OR
            (px == pv AND py == pu)

        Then:
            valid = false
            break

    If valid:

        union(pu, pv)
        answer.push_back(true)

    Else:

        answer.push_back(false)

Return answer.


Complete Optimal Code:
----------------------

class Solution {
public:

    vector<int> parent, sz;

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(
        int a,
        int b,
        vector<vector<int>>& restrictions
    ) {

        int pa = find(a);
        int pb = find(b);

        if (pa == pb)
            return true;

        for (auto &r : restrictions) {

            int pr1 = find(r[0]);
            int pr2 = find(r[1]);

            if ((pr1 == pa && pr2 == pb) ||
                (pr1 == pb && pr2 == pa)) {

                return false;
            }
        }

        if (sz[pa] < sz[pb])
            swap(pa, pb);

        parent[pb] = pa;
        sz[pa] += sz[pb];

        return true;
    }

    vector<bool> friendRequests(
        int n,
        vector<vector<int>>& restrictions,
        vector<vector<int>>& requests
    ) {

        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        vector<bool> ans;

        for (auto &request : requests) {

            int u = request[0];
            int v = request[1];

            if (unite(u, v, restrictions))
                ans.push_back(true);
            else
                ans.push_back(false);
        }

        return ans;
    }
};


Time Complexity:
----------------
For each request, we check all restrictions.

Let:

    Q = number of requests
    R = number of restrictions

Each check performs a few DSU find operations.

With path compression and union by size:

    O(alpha(N))

per find operation.

Therefore:

    O(Q * R * alpha(N))

Since alpha(N) is practically constant:

    Approximately O(Q * R)


Space Complexity:
-----------------
O(N)

For:

    parent[]
    sz[]


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Input:

    n = 3

Restrictions:

    [0, 1]

Requests:

    [0, 2]
    [2, 1]


Initial DSU:

    {0}
    {1}
    {2}


-------------------------------
Request 1: [0, 2]
-------------------------------

Find:

    find(0) = 0
    find(2) = 2

Restriction:

    [0, 1]

Find restriction components:

    find(0) = 0
    find(1) = 1

Compare:

    (0 == 0 && 1 == 2) -> false
    (0 == 2 && 1 == 0) -> false

No violation.

Accept request.

Union:

    0 and 2

DSU becomes:

    {0, 2}
    {1}

Answer:

    true


-------------------------------
Request 2: [2, 1]
-------------------------------

Find:

    find(2) = 0
    find(1) = 1

So we are trying to merge:

    Group A = {0, 2}
    Group B = {1}


Check restriction:

    [0, 1]

Find:

    find(0) = 0
    find(1) = 1

Now:

    pr1 == A
    pr2 == B

Therefore merging A and B would make:

    {0, 1, 2}

But 0 and 1 are restricted.

Reject.

Answer:

    false


Final:

    [true, false]


===============================================================================
WHY ONLY CHECK RESTRICTIONS BEFORE UNION?
===============================================================================

This is an important DSU concept.

Suppose request is:

    [u, v]

We are about to merge two components:

    A = find(u)
    B = find(v)

A restriction [x, y] becomes invalid ONLY if:

    x belongs to A
    y belongs to B

or:

    x belongs to B
    y belongs to A

If both x and y are already in the same component before the request,
then that situation would already have existed and could not have been
created by this request.

If neither belongs to the two components being merged, this request
cannot affect that restriction.

Therefore checking the restriction components before the union is enough.


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Union-Find / DSU + Constraint Checking


Key Observation:
----------------
A friendship request merges TWO connected components.

The request is invalid only when some restricted pair lies across
those two components.

Therefore:

    Find both request components.
    Check all restrictions.
    Merge only if no restriction is violated.


Common Mistakes:
----------------
1. Checking only the requested pair against restrictions.

   Example:

       restriction = [0, 1]
       request = [2, 3]

   But if:

       2 is already connected to 0
       3 is already connected to 1

   then accepting [2,3] violates [0,1].

   Always check the COMPONENTS.


2. Checking:

       nums[x] == nums[y]

   Instead, check:

       find(x) == find(y)


3. Merging before checking restrictions.

   Once merged, it becomes difficult to determine whether the request
   itself caused a violation.

   Always check first, then union.


4. Forgetting that friendship is transitive.

   If:

       0 -- 2
       2 -- 3

   then:

       0, 2, 3

   are in the same component.


5. Not using path compression.

6. Not using union by size/rank.

7. Rejecting a request without rolling back DSU.

   The optimal approach never performs the union until the request has
   been verified as valid, so no rollback is necessary.


When to Use This Approach:
--------------------------
Use DSU when:

- Relationships permanently merge groups.
- Connectivity is transitive.
- You need to know whether two elements are already connected.
- Operations consist of repeated union/check queries.

Use this specific technique when:

    "Can I merge these two groups without violating restrictions?"

The general pattern is:

    1. Find both components.
    2. Check constraints.
    3. If valid, union them.
    4. Otherwise, do nothing.


===============================================================================
*/

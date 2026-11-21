#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> findSubtreeSizes(vector<int> &parent, string s)
    {
        int n = parent.size();

        vector<vector<int>> adj(n), newAdj(n);
        vector<int> newParent(n);

        for (int i = 1; i < n; i++)
        {
            adj[parent[i]].push_back(i);
        }

        // Stores the nearest ancestor for each character.
        vector<int> last(26, -1);

        // Step 1: Construct the modified parent relationships.
        function<void(int)> dfs = [&](int u)
        {
            int c = s[u] - 'a';

            int previous = last[c];

            if (previous != -1)
            {
                newParent[u] = previous;
            }
            else
            {
                newParent[u] = parent[u];
            }

            last[c] = u;

            for (int v : adj[u])
            {
                dfs(v);
            }

            // Backtrack to maintain the current DFS path.
            last[c] = previous;
        };

        dfs(0);

        // Step 2: Build the modified tree.
        for (int i = 1; i < n; i++)
        {
            newAdj[newParent[i]].push_back(i);
        }

        // Step 3: Calculate subtree sizes.
        vector<int> ans(n, 0);

        function<int(int)> calculateSize = [&](int u)
        {
            ans[u] = 1;

            for (int v : newAdj[u])
            {
                ans[u] += calculateSize(v);
            }

            return ans[u];
        };

        calculateSize(0);

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> parent = {-1, 0, 0, 1, 1, 1};
    string s = "abaabc";

    vector<int> ans = sol.findSubtreeSizes(parent, s);

    for (int x : ans)
    {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

/*
============================================================
                LEETCODE 3331
             FIND SUBTREE SIZES AFTER CHANGES
============================================================

1. PROBLEM STATEMENT
--------------------

You are given:
    - An integer array parent representing a rooted tree.
    - A string s where s[i] represents the character of node i.

The tree is rooted at node 0.

For every node x (except root):

    Find the closest ancestor y of x such that:

        s[x] == s[y]

If such an ancestor exists:
    Change the parent of x to y.

Otherwise:
    Keep its original parent.

All parent changes happen simultaneously.

After modifying the tree, return an array answer where:

    answer[i] = Size of the subtree rooted at node i.


2. EXAMPLE
----------

Input:

    parent = [-1, 0, 0, 1, 1, 1]
    s = "abaabc"

Original Tree:

                0(a)
               /    \
            1(b)    2(a)
           / | \
        3(a) 4(b) 5(c)

Modified Parent Relationships:

    Node 1(b):
        No matching ancestor.
        Parent = 0

    Node 2(a):
        Matching ancestor = 0(a).
        Parent = 0

    Node 3(a):
        Closest matching ancestor = 0(a).
        Parent = 0

    Node 4(b):
        Closest matching ancestor = 1(b).
        Parent = 1

    Node 5(c):
        No matching ancestor.
        Parent = 1

Modified Tree:

                  0(a)
                /  |  \
             1(b) 2(a) 3(a)
             / \
          4(b) 5(c)

Output:

    [6, 3, 1, 1, 1, 1]


============================================================
3. BRUTE FORCE APPROACH
============================================================

IDEA:
-----

For every node:

1. Start traversing from its original parent.
2. Move upward towards the root.
3. Find the first ancestor having the same character.
4. If found, assign it as the new parent.
5. Otherwise, retain the original parent.

After finding all modified parents:

1. Construct the modified tree.
2. Run DFS on the modified tree.
3. Calculate subtree sizes.

Since we traverse ancestors separately for every node,
the worst-case complexity becomes O(N^2).


PSEUDOCODE:
-----------

function findSubtreeSizes(parent, s):

    n = parent.size()

    newParent = parent

    for node = 1 to n-1:

        ancestor = parent[node]

        while ancestor != -1:

            if s[ancestor] == s[node]:

                newParent[node] = ancestor
                break

            ancestor = parent[ancestor]

    Build modified adjacency list using newParent.

    DFS(node):

        size[node] = 1

        for child in adjacency[node]:

            size[node] += DFS(child)

        return size[node]

    DFS(0)

    return size


COMPLETE BRUTE FORCE CODE:
--------------------------

    class Solution {
    public:
        vector<int> findSubtreeSizes(
            vector<int>& parent, string s
        ) {
            int n = parent.size();
    
            vector<int> newParent = parent;
    
            // Find nearest matching ancestor.
            for (int i = 1; i < n; i++) {
    
                int curr = parent[i];
    
                while (curr != -1) {
    
                    if (s[curr] == s[i]) {
                        newParent[i] = curr;
                        break;
                    }
    
                    curr = parent[curr];
                }
            }
    
            // Build modified tree.
            vector<vector<int>> adj(n);
    
            for (int i = 1; i < n; i++) {
                adj[newParent[i]].push_back(i);
            }
    
            vector<int> ans(n, 0);
    
            // Calculate subtree sizes.
            function<int(int)> dfs = [&](int u) {
    
                ans[u] = 1;
    
                for (int v : adj[u]) {
                    ans[u] += dfs(v);
                }
    
                return ans[u];
            };
    
            dfs(0);
    
            return ans;
        }
    };


TIME COMPLEXITY:
----------------

    Finding ancestors: O(N^2) worst case.

    Building modified tree: O(N).

    Calculating subtree sizes: O(N).

    Overall: O(N^2).


SPACE COMPLEXITY:
-----------------

    Adjacency list: O(N).

    Parent and answer arrays: O(N).

    Recursion stack: O(N).

    Overall: O(N).


============================================================
4. OPTIMAL APPROACH
============================================================

OBSERVATION:
------------

The important observation is:

We only need the CLOSEST ancestor having the same character.

During DFS, we are already traversing the original tree
from root to leaf.

Therefore, we can maintain the most recently visited
ancestor for every character.

Since DFS maintains the current root-to-node path,
the last occurrence of a character is automatically
the closest ancestor with that character.


INTUITION:
----------

Maintain an array:

    last[26]

Where:

    last[c] = Nearest ancestor having character c.

Initially:

    last[c] = -1 for every character.

While visiting node u:

STEP 1:

    Find its character:

        c = s[u] - 'a'

STEP 2:

    Store the previous occurrence:

        previous = last[c]

STEP 3:

    Determine its modified parent:

        If previous != -1:
            newParent[u] = previous

        Else:
            newParent[u] = parent[u]

STEP 4:

    Update the latest occurrence:

        last[c] = u

STEP 5:

    Visit all children recursively.

STEP 6:

    BACKTRACK:

        last[c] = previous

WHY BACKTRACKING?

Because last[] must represent only the current
root-to-node path.

Suppose node 2 has character 'a'.

After finishing its subtree, its occurrence must
not affect the processing of another sibling.

Therefore, restore the previous value.

After constructing the modified parent relationships:

1. Build the new adjacency list.
2. Perform another DFS.
3. Calculate subtree sizes using postorder traversal.


PSEUDOCODE:
-----------

function findSubtreeSizes(parent, s):

    n = parent.size()

    Build original adjacency list.

    Initialize last[26] = -1.

    DFS_BUILD(u):

        c = s[u] - 'a'

        previous = last[c]

        if last[c] != -1:

            newParent[u] = last[c]

        else:

            newParent[u] = parent[u]

        last[c] = u

        for each child v of u:

            DFS_BUILD(v)

        last[c] = previous

    DFS_BUILD(0)

    Build modified adjacency list using newParent.

    DFS_SIZE(u):

        ans[u] = 1

        for each child v of u:

            ans[u] += DFS_SIZE(v)

        return ans[u]

    DFS_SIZE(0)

    return ans


COMPLETE OPTIMAL CODE:
----------------------

    class Solution {
    public:
        vector<int> findSubtreeSizes(
            vector<int>& parent, string s
        ) {
            int n = parent.size();
    
            vector<vector<int>> adj(n), newAdj(n);
    
            vector<int> newParent(n);
    
            for (int i = 1; i < n; i++) {
                adj[parent[i]].push_back(i);
            }
    
            vector<int> last(26, -1);
    
            function<void(int)> dfs = [&](int u) {
    
                int c = s[u] - 'a';
    
                int previous = last[c];
    
                if (previous != -1) {
                    newParent[u] = previous;
                }
                else {
                    newParent[u] = parent[u];
                }
    
                last[c] = u;
    
                for (int v : adj[u]) {
                    dfs(v);
                }
    
                last[c] = previous;
            };
    
            dfs(0);
    
            for (int i = 1; i < n; i++) {
                newAdj[newParent[i]].push_back(i);
            }
    
            vector<int> ans(n, 0);
    
            function<int(int)> calculateSize =
                [&](int u) {
    
                    ans[u] = 1;
    
                    for (int v : newAdj[u]) {
                        ans[u] += calculateSize(v);
                    }
    
                    return ans[u];
                };
    
            calculateSize(0);
    
            return ans;
        }
    };


TIME COMPLEXITY:
----------------

    Building original tree: O(N)

    First DFS:
        Each node visited once = O(N)

    Building modified tree: O(N)

    Second DFS:
        Each node visited once = O(N)

    Total:

        O(N) + O(N) + O(N) + O(N)

        O(N)


SPACE COMPLEXITY:
-----------------

    Original adjacency list: O(N)

    Modified adjacency list: O(N)

    Last occurrence array: O(26) = O(1)

    Parent and answer arrays: O(N)

    Recursion stack: O(N)

    Overall:

        O(N)


============================================================
5. DRY RUN WITH EXAMPLE
============================================================

INPUT:

    parent = [-1, 0, 0, 1, 1, 1]

    s = "abaabc"


ORIGINAL TREE:

                0(a)
               /    \
            1(b)    2(a)
           / | \
        3(a) 4(b) 5(c)


INITIAL STATE:

    last = [-1, -1, -1, ...]


DFS VISITATION:

NODE 0 (a):

    previous = -1

    newParent[0] = -1

    last[a] = 0


NODE 1 (b):

    previous = -1

    newParent[1] = 0

    last[b] = 1


NODE 3 (a):

    previous = 0

    newParent[3] = 0

    last[a] = 3

    Backtrack:
        last[a] = 0


NODE 4 (b):

    previous = 1

    newParent[4] = 1

    last[b] = 4

    Backtrack:
        last[b] = 1


NODE 5 (c):

    previous = -1

    newParent[5] = 1

    last[c] = 5

    Backtrack:
        last[c] = -1


NODE 2 (a):

    previous = 0

    newParent[2] = 0

    last[a] = 2

    Backtrack:
        last[a] = 0


FINAL MODIFIED PARENT ARRAY:

    [-1, 0, 0, 0, 1, 1]


MODIFIED TREE:

                  0(a)
                /  |  \
             1(b) 2(a) 3(a)
             / \
          4(b) 5(c)


SECOND DFS: SUBTREE SIZE CALCULATION

NODE 4:

    ans[4] = 1

NODE 5:

    ans[5] = 1

NODE 1:

    ans[1] = 1 + ans[4] + ans[5]

    ans[1] = 3

NODE 2:

    ans[2] = 1

NODE 3:

    ans[3] = 1

NODE 0:

    ans[0] = 1 + ans[1] + ans[2] + ans[3]

    ans[0] = 1 + 3 + 1 + 1

    ans[0] = 6


FINAL ANSWER:

    [6, 3, 1, 1, 1, 1]


============================================================
6. INTERVIEW NOTES
============================================================

PATTERN:
--------

    Tree DFS + Backtracking + Subtree DP

    Two DFS Traversals:

        DFS 1:
            Construct modified parent relationships.

        DFS 2:
            Calculate subtree sizes.


KEY OBSERVATION:
----------------

Maintain the nearest ancestor for each character
while traversing the original tree.

The last occurrence on the current DFS path is
always the closest matching ancestor.

Backtracking is essential to ensure sibling
subtrees do not affect one another.


COMMON MISTAKES:
----------------

1. FORGETTING BACKTRACKING

   Incorrect:

       last[c] = u;

   Without restoring the previous value, one
   sibling can incorrectly affect another sibling.

2. USING THE MODIFIED TREE DURING FIRST DFS

   The matching ancestor must be determined using
   the ORIGINAL tree.

3. USING ORIGINAL PARENT ARRAY FOR SUBTREE DFS

   Subtree sizes must be calculated using the
   MODIFIED tree.

4. NOT COUNTING THE CURRENT NODE

   Every subtree size must initially be 1.

5. WRONG ANCESTOR DIRECTION

   We need the closest matching ancestor, not
   the farthest matching ancestor.

6. NOT HANDLING ROOT

   Node 0 has no parent and remains the root.


WHEN TO USE THIS APPROACH:
--------------------------

Use this technique when:

    - A tree problem asks for the nearest ancestor
      satisfying some condition.

    - You need information about ancestors during DFS.

    - The condition can be represented using a
      hashmap or frequency/last-occurrence array.

    - You need to maintain information only along
      the current root-to-node path.

    - DFS backtracking can restore previous states.


FINAL COMPLEXITY:
-----------------

    Brute Force:

        Time  = O(N^2)
        Space = O(N)

    Optimal:

        Time  = O(N)
        Space = O(N)


INTERVIEW TAKEAWAY:

    "Maintain path-dependent information during DFS,
     update it before visiting children, and restore
     it after processing children."

    This is the key technique behind the solution.

============================================================
                    END OF NOTES
============================================================
*/
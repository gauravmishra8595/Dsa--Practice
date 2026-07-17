#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> neighbors;

    Node()
    {
        val = 0;
        neighbors = {};
    }

    Node(int _val)
    {
        val = _val;
        neighbors = {};
    }

    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    unordered_map<Node *, Node *> mp;

    Node *dfs(Node *node)
    {
        if (node == NULL)
            return NULL;

        if (mp.count(node))
            return mp[node];

        Node *clone = new Node(node->val);
        mp[node] = clone;

        for (Node *nei : node->neighbors)
            clone->neighbors.push_back(dfs(nei));

        return clone;
    }

    Node *cloneGraph(Node *node)
    {
        return dfs(node);
    }
};

int main()
{

    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);

    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};

    Solution obj;
    Node *clone = obj.cloneGraph(n1);

    cout << "Cloned Node Value: " << clone->val << endl;
    cout << "Neighbors: ";

    for (Node *x : clone->neighbors)
        cout << x->val << " ";

    cout << endl;

    return 0;
}

/*

=========================================================
LeetCode 133 - Clone Graph
=========================================================

---------------------------------------------------------
Problem Statement
---------------------------------------------------------

Given a reference of a node in a connected undirected graph,
return a deep copy (clone) of the graph.

Each node contains

1. value
2. list of neighbors

The cloned graph should contain entirely new nodes while
preserving the original graph structure.

---------------------------------------------------------
Example
---------------------------------------------------------

Input

1 ----- 2
|       |
|       |
4 ----- 3

Output

A completely new graph having the same connections.

=========================================================
Brute Force Approach
=========================================================

-------------------------
Idea
-------------------------

Traverse the graph.

For every node encountered,
create a new node.

Maintain a map from original node to cloned node.

Without the map,
cycles will cause infinite recursion.

(There is actually no practical brute-force solution without
remembering visited nodes because graphs may contain cycles.)

-------------------------
Pseudo Code
-------------------------

If node already cloned

    return cloned node

Create clone

Store mapping

Clone every neighbor recursively

Return clone

-------------------------
Complete Brute Force Code
-------------------------

// No true brute-force exists because cyclic graphs
// require remembering visited nodes.
// The optimal DFS/BFS with hashing is the standard solution.

-------------------------
Time Complexity
-------------------------

Exponential without visited map (invalid for cyclic graphs).

-------------------------
Space Complexity
-------------------------

Very High / Infinite due to repeated traversal.

=========================================================
Optimal Approach
=========================================================

-------------------------
Observation
-------------------------

Graphs may contain

• Cycles

• Multiple paths to same node

So every original node should be cloned exactly once.

Use a HashMap

Original Node
        →
Cloned Node

-------------------------
Intuition
-------------------------

Whenever a node is visited

If already cloned

Return its clone.

Otherwise

Create clone

Store in map

Clone all neighbors recursively.

Finally return cloned node.

-------------------------
Pseudo Code
-------------------------

DFS(node)

if node==NULL

    return NULL

if node already cloned

    return clone

create new node

store mapping

for every neighbor

    clone neighbors

return clone

-------------------------
Complete Optimal Code
-------------------------

class Solution {
public:

unordered_map<Node*,Node*> mp;

Node* dfs(Node* node){

    if(node==NULL)
        return NULL;

    if(mp.count(node))
        return mp[node];

    Node* clone=new Node(node->val);

    mp[node]=clone;

    for(Node* nbr:node->neighbors)
        clone->neighbors.push_back(
            dfs(nbr)
        );

    return clone;
}

Node* cloneGraph(Node* node){

    return dfs(node);

}

};

-------------------------
Time Complexity
-------------------------

Every node visited once.

Every edge visited once.

O(V + E)

-------------------------
Space Complexity
-------------------------

HashMap

O(V)

Recursive Stack

O(V)

Overall

O(V)

=========================================================
Dry Run
=========================================================

Graph

1 ---- 2
|      |
|      |
4 ---- 3

Start DFS(1)

Clone 1

Map

1→1'

Visit neighbor 2

Clone 2

Map

2→2'

Visit neighbor 1

Already cloned

Return 1'

Visit neighbor 3

Clone 3

Visit neighbor 4

Clone 4

Visit neighbor 1

Already cloned

Done

New graph

1' ---- 2'
|         |
|         |
4' ---- 3'

=========================================================
Interview Notes
=========================================================

Pattern

• Graph DFS

• Graph BFS

• HashMap

• Deep Copy

---------------------------------------------------------

Key Observation

Whenever cloning a graph,

always maintain

Original Node → Cloned Node

mapping.

---------------------------------------------------------

Common Mistakes

1. Forgetting visited map.

2. Creating duplicate nodes.

3. Infinite recursion due to cycles.

4. Returning original neighbors instead of cloned neighbors.

---------------------------------------------------------

When to use this approach

Use whenever

• Deep copy of Graph.

• Random Pointer Linked List.

• Graph reconstruction.

• Graph serialization/deserialization.

• Problems involving cycles.

=========================================================

*/
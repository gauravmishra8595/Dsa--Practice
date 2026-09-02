#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;

        for (auto &d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if (!nodes.count(parent))
                nodes[parent] = new TreeNode(parent);

            if (!nodes.count(child))
                nodes[child] = new TreeNode(child);

            if (isLeft)
                nodes[parent]->left = nodes[child];
            else
                nodes[parent]->right = nodes[child];

            children.insert(child);
        }

        for (auto &[value, node] : nodes) {
            if (!children.count(value))
                return node;
        }

        return nullptr;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> descriptions = {
        {20, 15, 1},
        {20, 17, 0},
        {15, 10, 1},
        {15, 12, 0}
    };

    TreeNode* root = sol.createBinaryTree(descriptions);

    // Level-order print for testing.
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        cout << node->val << " ";

        if (node->left)
            q.push(node->left);

        if (node->right)
            q.push(node->right);
    }

    cout << '\n';

    return 0;
}

/*
================================================================================
              LEETCODE 2196 - CREATE BINARY TREE FROM DESCRIPTIONS
================================================================================

Problem Statement:
------------------
You are given a 2D array `descriptions`.

Each description is:

    [parent, child, isLeft]

Meaning:

    - parent is the value of the parent node.
    - child is the value of the child node.
    - if isLeft == 1, child is the LEFT child of parent.
    - if isLeft == 0, child is the RIGHT child of parent.

The descriptions uniquely describe a binary tree.

Return the root of the binary tree.


--------------------------------------------------------------------------------
Example:
--------------------------------------------------------------------------------

Input:

descriptions =
[
    [20, 15, 1],
    [20, 17, 0],
    [15, 10, 1],
    [15, 12, 0]
]


Build:

          20
         /  \
       15    17
      /  \
    10    12


Answer:

        20
       /  \
     15    17
    /  \
  10    12


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
------
One straightforward approach is to process the descriptions and create
the tree.

To find the root, after constructing the tree we can:

    1. Store all created nodes.
    2. For every node, check whether it appears as a child.
    3. The node that never appears as a child is the root.

A less efficient implementation could repeatedly scan the entire
description list whenever we need to determine whether a node is a child.

For every possible node:

    scan all descriptions
    check whether this node appears as a child

This gives O(N^2) time.


Pseudo Code:
------------

    Create all nodes.

    For every node:
        Scan all descriptions.
        Check whether node appears as a child.

        If it never appears as a child:
            return this node.

    While processing descriptions:
        connect left/right child to parent.


Complete Brute Force Code:
--------------------------

/*
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {

        unordered_map<int, TreeNode*> nodes;

        // Create all required nodes.
        for (auto &d : descriptions) {
            int parent = d[0];
            int child = d[1];

            if (!nodes.count(parent))
                nodes[parent] = new TreeNode(parent);

            if (!nodes.count(child))
                nodes[child] = new TreeNode(child);
        }

        // Connect the nodes.
        for (auto &d : descriptions) {
            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if (isLeft)
                nodes[parent]->left = nodes[child];
            else
                nodes[parent]->right = nodes[child];
        }

        // Find root by scanning descriptions for every node.
        for (auto &[value, node] : nodes) {

            bool isChild = false;

            for (auto &d : descriptions) {
                if (d[1] == value) {
                    isChild = true;
                    break;
                }
            }

            if (!isChild)
                return node;
        }

        return nullptr;
    }
};
*/


// Time Complexity:
// ----------------
// Let:

//     N = number of descriptions

// There can be O(N) distinct nodes.

// For every node, we scan all descriptions:

//     O(N * N)

// Therefore:

//     O(N^2)


// Space Complexity:
// -----------------
// Nodes + hash map:

//     O(N)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// Every node except the root appears as a CHILD in at least one description.

// The root is the only node that:

//     appears as a parent
//     but NEVER appears as a child.


// Therefore, while processing descriptions:

//     - Create nodes using a hash map.
//     - Connect parent and child.
//     - Put every child into a `children` set.

// After processing everything:

//     The node whose value is NOT in `children`
//     is the root.


// Intuition:
// ----------
// Consider:

//     [20, 15, 1]
//     [20, 17, 0]
//     [15, 10, 1]
//     [15, 12, 0]


// Children are:

//     15
//     17
//     10
//     12

// Notice:

//     20 is never a child.

// Therefore:

//     20 = root


// This avoids repeatedly scanning the descriptions.

// We simply maintain:

//     unordered_set<int> children;


// Whenever a node becomes a child:

//     children.insert(child);


// At the end:

//     if value is not in children:
//         it is the root.


// Why unordered_map?
// ------------------
// The same node can appear in multiple descriptions.

// For example:

//     [20, 15, 1]
//     [15, 10, 1]

// Node 15 appears once as a child and later as a parent.

// We need the SAME TreeNode object for both appearances.

// So:

//     value -> TreeNode*

// is stored in an unordered_map.


// Pseudo Code:
// ------------

//     nodes = empty map
//     children = empty set

//     for each [parent, child, isLeft]:

//         if parent doesn't exist:
//             create parent node

//         if child doesn't exist:
//             create child node

//         if isLeft:
//             parent.left = child
//         else:
//             parent.right = child

//         add child to children set

//     for every node in nodes:

//         if node.value is not in children:
//             return node

//     return null


// Complete Optimal Code:
// ----------------------

/*
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {

        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;

        for (auto &d : descriptions) {

            int parent = d[0];
            int child = d[1];
            int isLeft = d[2];

            if (!nodes.count(parent))
                nodes[parent] = new TreeNode(parent);

            if (!nodes.count(child))
                nodes[child] = new TreeNode(child);

            if (isLeft)
                nodes[parent]->left = nodes[child];
            else
                nodes[parent]->right = nodes[child];

            children.insert(child);
        }

        for (auto &[value, node] : nodes) {

            if (!children.count(value))
                return node;
        }

        return nullptr;
    }
};
*/


// Time Complexity:
// ----------------
// Each description is processed once:

//     O(N)

// Finding the root requires iterating over all created nodes:

//     O(N)

// Average total:

//     O(N)


// Space Complexity:
// -----------------
// Hash map:

//     O(N)

// Children set:

//     O(N)

// Tree nodes:

//     O(N)

// Overall:

//     O(N)


// ================================================================================
// DRY RUN
// ================================================================================

// Input:

//     [20, 15, 1]
//     [20, 17, 0]
//     [15, 10, 1]
//     [15, 12, 0]


// Initially:

//     nodes = {}
//     children = {}


// STEP 1:
// --------
// Description:

//     [20, 15, 1]

// Create:

//     Node(20)
//     Node(15)

// Connect:

//     20.left = 15

// Add child:

//     children = {15}


// Current tree:

//         20
//        /
//      15


// STEP 2:
// --------
// Description:

//     [20, 17, 0]

// Create:

//     Node(17)

// Connect:

//     20.right = 17

// Add child:

//     children = {15, 17}


// Current tree:

//         20
//        /  \
//      15    17


// STEP 3:
// --------
// Description:

//     [15, 10, 1]

// Create:

//     Node(10)

// Connect:

//     15.left = 10

// Add child:

//     children = {15, 17, 10}


// Current tree:

//         20
//        /  \
//      15    17
//     /
//   10


// STEP 4:
// --------
// Description:

//     [15, 12, 0]

// Create:

//     Node(12)

// Connect:

//     15.right = 12

// Add child:

//     children = {15, 17, 10, 12}


// Final tree:

//           20
//          /  \
//        15    17
//       /  \
//     10    12


// Now check every node:

//     20 -> NOT in children
//     15 -> in children
//     17 -> in children
//     10 -> in children
//     12 -> in children

// Therefore:

//     Root = 20


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// - Binary Tree Construction
// - Hash Map
// - Hash Set
// - Parent-Child Relationship
// - Root Identification


// Key Observation:
// ----------------
// "The root is the only node that is never a child."

// So maintain:

//     children.insert(child)

// Then find:

//     node NOT in children


// Common Mistakes:
// ----------------

// 1. Creating a new TreeNode every time a value appears.

//    WRONG:

//        nodes[parent] = new TreeNode(parent);

//    without checking whether it already exists.

//    A node may appear in multiple descriptions.

//    Correct:

//        if (!nodes.count(parent))
//            nodes[parent] = new TreeNode(parent);


// 2. Forgetting that isLeft == 1 means LEFT.

//        if (isLeft)
//            parent->left = child;


//    and isLeft == 0 means RIGHT.

//        else
//            parent->right = child;


// 3. Trying to find the root by assuming it is the first parent.

//    This is not a safe/general method.

//    The correct property is:

//        root never appears as a child.


// 4. Forgetting to mark every child.

//        children.insert(child);


// 5. Using a set of TreeNode pointers instead of node values unnecessarily.

//    The problem gives unique node values, so:

//        unordered_set<int>

//    is simple and sufficient.


// 6. Reversing parent and child.

//    Description:

//        [parent, child, isLeft]

//    means:

//        parent -> child


// 7. Using BFS/DFS to construct the tree.

//    Traversal is unnecessary because the descriptions directly specify
//    every parent-child relationship.


// When to use this approach:
// --------------------------
// Use this pattern when a problem gives relationships like:

//     parent -> child

// and asks you to reconstruct a tree.

// Typical technique:

//     value -> node pointer
//             +
//     child set
//             +
//     connect edges
//             +
//     find node that never appeared as child


// Quick Memory Trick:
// -------------------

//     "Everyone except ROOT is someone's CHILD."

// Therefore:

//     Mark all children.

//     The unmarked node = ROOT.


// Complexity:
// -----------

//     Time  = O(N) average
//     Space = O(N)


// LeetCode Submission Note:
// -------------------------
// On LeetCode, `TreeNode` is already provided.

// Therefore, the actual LeetCode submission is only:

//     class Solution { ... };

// The TreeNode definition and main() above are included only to make the
// code directly runnable in VS Code.


// ================================================================================
// */

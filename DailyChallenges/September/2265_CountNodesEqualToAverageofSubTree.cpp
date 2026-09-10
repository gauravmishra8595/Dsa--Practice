#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
public:
    int count = 0;

    pair<int, int> dfs(TreeNode *root)
    {
        if (!root)
            return {0, 0};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        int nodes = left.first + right.first + 1;
        int sum = left.second + right.second + root->val;

        if (sum / nodes == root->val)
            count++;

        return {nodes, sum};
    }

    int averageOfSubtree(TreeNode *root)
    {
        dfs(root);
        return count;
    }
};

int main()
{

    /*
            4
           / \
          8   5
         / \   \
        0   1   6

        Expected Answer = 5
    */

    TreeNode *root = new TreeNode(4);

    root->left = new TreeNode(8);
    root->right = new TreeNode(5);

    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(1);

    root->right->right = new TreeNode(6);

    Solution obj;

    cout << "Answer: " << obj.averageOfSubtree(root) << endl;

    return 0;
}

/*
============================================================
                    LEETCODE 2265
       COUNT NODES EQUAL TO AVERAGE OF SUBTREE
============================================================

Problem Statement:
------------------
Given the root of a binary tree, return the number of nodes
where the value of the node is equal to the average of the
values in its subtree.

The average is calculated using integer division.

The subtree of a node includes the node itself and all of
its descendants.

Example:
--------
Input:

        4
       / \
      8   5
     / \   \
    0   1   6

Output:
5

The valid nodes are:
0, 1, 6, 5, 4

============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
For every node:

1. Traverse its complete subtree.
2. Calculate the sum of the subtree.
3. Calculate the number of nodes.
4. Calculate average = sum / count.
5. Check whether average == current node value.

The problem is that the subtree is traversed repeatedly.

Pseudo Code:
------------
function countNodes(root):

    if root == NULL:
        return 0

    return 1
           + countNodes(root->left)
           + countNodes(root->right)

function sumNodes(root):

    if root == NULL:
        return 0

    return root->val
           + sumNodes(root->left)
           + sumNodes(root->right)

function solve(root):

    if root == NULL:
        return 0

    sum = sumNodes(root)
    count = countNodes(root)

    ans = 0

    if sum / count == root->val:
        ans++

    ans += solve(root->left)
    ans += solve(root->right)

    return ans

Complete Brute Force Code:
--------------------------

class Solution {
public:

    int countNodes(TreeNode* root) {
        if (!root)
            return 0;

        return 1
             + countNodes(root->left)
             + countNodes(root->right);
    }

    int sumNodes(TreeNode* root) {
        if (!root)
            return 0;

        return root->val
             + sumNodes(root->left)
             + sumNodes(root->right);
    }

    int solve(TreeNode* root) {
        if (!root)
            return 0;

        int sum = sumNodes(root);
        int nodes = countNodes(root);

        int ans = 0;

        if (sum / nodes == root->val)
            ans++;

        ans += solve(root->left);
        ans += solve(root->right);

        return ans;
    }

    int averageOfSubtree(TreeNode* root) {
        return solve(root);
    }
};

Time Complexity:
----------------
O(N^2) in the worst case.

For every node, we may traverse a large part of its subtree
again.

Space Complexity:
-----------------
O(H)

H = height of the tree due to recursion.

============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
For each subtree, we only need two things:

1. Sum of all values in the subtree.
2. Number of nodes in the subtree.

We can calculate both using one postorder DFS.

The children are processed first, then the current node.

For every node:

    subtreeNodes =
        leftNodes + rightNodes + 1

    subtreeSum =
        leftSum + rightSum + root->val

Intuition:
----------
Suppose the left subtree gives us:

    {leftNodes, leftSum}

and the right subtree gives us:

    {rightNodes, rightSum}

Then the current subtree information can be calculated
immediately.

This avoids traversing the same subtree multiple times.

Therefore every node is visited exactly once.

Pseudo Code:
------------

function DFS(root):

    if root == NULL:
        return {0, 0}

    left = DFS(root->left)
    right = DFS(root->right)

    nodes = left.nodes + right.nodes + 1

    sum = left.sum + right.sum + root->val

    if sum / nodes == root->val:
        answer++

    return {nodes, sum}

function averageOfSubtree(root):

    DFS(root)

    return answer

Complete Optimal Code:
----------------------

class Solution {
public:

    int count = 0;

    pair<int, int> dfs(TreeNode* root) {

        if (!root)
            return {0, 0};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        int nodes =
            left.first +
            right.first +
            1;

        int sum =
            left.second +
            right.second +
            root->val;

        if (sum / nodes == root->val)
            count++;

        return {nodes, sum};
    }

    int averageOfSubtree(TreeNode* root) {

        dfs(root);

        return count;
    }
};

Time Complexity:
----------------
O(N)

Every node is visited exactly once.

Space Complexity:
-----------------
O(H)

H = height of the tree due to recursion stack.

Worst case:
O(N) for a skewed tree.

Balanced tree:
O(log N)

============================================================
DRY RUN WITH EXAMPLE
============================================================

Tree:

        4
       / \
      8   5
     / \   \
    0   1   6

Step 1: Node 0

sum = 0
nodes = 1

average = 0 / 1 = 0

0 == 0

answer = 1

Step 2: Node 1

sum = 1
nodes = 1

average = 1 / 1 = 1

1 == 1

answer = 2

Step 3: Node 8

Left subtree:
sum = 0
nodes = 1

Right subtree:
sum = 1
nodes = 1

Current node = 8

sum = 0 + 1 + 8
    = 9

nodes = 1 + 1 + 1
      = 3

average = 9 / 3
        = 3

3 != 8

answer = 2

Step 4: Node 6

sum = 6
nodes = 1

average = 6 / 1
        = 6

6 == 6

answer = 3

Step 5: Node 5

Left subtree:
sum = 0
nodes = 0

Right subtree:
sum = 6
nodes = 1

Current node = 5

sum = 0 + 6 + 5
    = 11

nodes = 0 + 1 + 1
      = 2

average = 11 / 2
        = 5

Integer division gives 5.

5 == 5

answer = 4

Step 6: Node 4

Left subtree:
sum = 9
nodes = 3

Right subtree:
sum = 11
nodes = 2

Current node = 4

sum = 9 + 11 + 4
    = 24

nodes = 3 + 2 + 1
      = 6

average = 24 / 6
        = 4

4 == 4

answer = 5

Final Answer:
-------------
5

============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Binary Tree
+
Postorder DFS
+
Tree DP / Subtree Information

Key Observation:
----------------
For each node, return:

    {subtreeNodeCount, subtreeSum}

The parent can combine the information returned by its
children.

General pattern:

    DFS(left)
        +
    DFS(right)
        +
    current node
        =
    current subtree information

Common Mistakes:
----------------

1. Forgetting to include the current node in the sum.

2. Forgetting to include the current node in the count.

3. Using floating point unnecessarily.

   We can simply use:

       sum / nodes

   because the problem uses integer division.

4. Recalculating sum and count for every node.

   This gives O(N^2) in the worst case.

5. Forgetting that the subtree includes the current node.

6. Using a global count and reusing the same Solution object
   without resetting it.

When to use this approach:
--------------------------
Use this pattern when a binary tree problem asks for some
property of every subtree.

Examples:

- Subtree sum
- Subtree size
- Subtree height
- Subtree average
- Number of valid subtrees
- Tree DP problems
- Problems where parent information depends on children

Important Template:
-------------------

pair<int, int> dfs(TreeNode* root) {

    if (!root)
        return {0, 0};

    auto left = dfs(root->left);
    auto right = dfs(root->right);

    int nodes =
        left.first +
        right.first +
        1;

    int sum =
        left.second +
        right.second +
        root->val;

    // Process current node

    return {nodes, sum};
}

CORE IDEA:
----------

        Children
           |
           v
    Get subtree information
           |
           v
    Combine at current node
           |
           v
      Check condition
           |
           v
    Return to parent

Time:  O(N)
Space: O(H)

============================================================
*/
// ```
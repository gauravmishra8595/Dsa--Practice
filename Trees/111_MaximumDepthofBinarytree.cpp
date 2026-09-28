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
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    int minDepth(TreeNode *root)
    {

        if (root == NULL)
        {
            return 0;
        }

        if (root->left == NULL && root->right != NULL)
        {

            int left = minDepth(root->left);
            int right = minDepth(root->right);

            return max(left, right) + 1;
        }

        if (root->right == NULL && root->left != NULL)
        {

            int le = minDepth(root->left);
            int ri = minDepth(root->right);

            return max(le, ri) + 1;
        }

        int leftheight = minDepth(root->left);
        int rightheight = minDepth(root->right);

        return min(leftheight, rightheight) + 1;
    }
};

int main()
{

    /*
                3
               / \
              9   20
                 /  \
                15   7

        Minimum Depth = 2
    */

    TreeNode *root = new TreeNode(3);

    root->left = new TreeNode(9);
    root->right = new TreeNode(20);

    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution obj;

    cout << "Minimum Depth = "
         << obj.minDepth(root)
         << endl;

    return 0;
}

/*
====================================================================
              LEETCODE 111 - MINIMUM DEPTH OF BINARY TREE
====================================================================

PROBLEM STATEMENT
-----------------

Given the root of a binary tree, return its minimum depth.

The minimum depth is the number of nodes along the shortest path
from the root node down to the nearest leaf node.

A leaf is a node that has no left child and no right child.


====================================================================
                              EXAMPLE
====================================================================

Input:

              3
             / \
            9   20
               /  \
              15   7

Output:

    2

Shortest path:

    3 -> 9

Number of nodes = 2.


====================================================================
                       BRUTE FORCE APPROACH
====================================================================

IDEA
----

We can recursively calculate the depth of both left and right
subtrees.

For every node:

    leftDepth  = minimum depth of left subtree
    rightDepth = minimum depth of right subtree

Then take the minimum.

But if one child is NULL, we cannot directly use min() because
NULL contributes 0 and can produce an incorrect answer.

Example:

            1
             \
              2

If we directly calculate:

    1 + min(0, 1)

we get 1.

But the correct answer is 2.

So the missing child must be ignored.


PSEUDO CODE
-----------

function minDepth(root):

    if root == NULL:
        return 0

    if only right child exists:
        calculate right depth
        return right depth + 1

    if only left child exists:
        calculate left depth
        return left depth + 1

    calculate left depth
    calculate right depth

    return minimum + 1


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    int minDepth(TreeNode* root) {

        if (root == NULL) {
            return 0;
        }

        if (root->left == NULL && root->right == NULL) {
            return 1;
        }

        if (root->left == NULL) {
            return 1 + minDepth(root->right);
        }

        if (root->right == NULL) {
            return 1 + minDepth(root->left);
        }

        int left = minDepth(root->left);
        int right = minDepth(root->right);

        return min(left, right) + 1;
    }
};


TIME COMPLEXITY
---------------

O(N)

Every node is visited once.


SPACE COMPLEXITY
----------------

O(H)

H = height of the tree.


====================================================================
                        OPTIMAL APPROACH
====================================================================

OBSERVATION
-----------

We need the shortest path from root to a LEAF.

There are three cases:

1. Root is NULL

       return 0

2. Only one child exists

       We must go through that child.

3. Both children exist

       Take the minimum of both subtree depths.


INTUITION
---------

Your logic is based on handling the one-child cases separately.

If only the right child exists:

            1
             \
              2

Then:

    left = 0
    right = 1

Using:

    max(left, right) + 1

gives:

    max(0, 1) + 1
    = 2

So your max() logic correctly ignores the NULL side.

Similarly, when only the left child exists:

            1
           /
          2

We get:

    max(1, 0) + 1
    = 2

When both children exist, we use:

    min(leftheight, rightheight) + 1


PSEUDO CODE
-----------

function minDepth(root):

    if root == NULL:
        return 0

    if left == NULL and right != NULL:

        left = minDepth(left)
        right = minDepth(right)

        return max(left, right) + 1

    if right == NULL and left != NULL:

        left = minDepth(left)
        right = minDepth(right)

        return max(left, right) + 1

    leftheight = minDepth(left)
    rightheight = minDepth(right)

    return min(leftheight, rightheight) + 1


COMPLETE OPTIMAL CODE
---------------------

class Solution {

public:

    int minDepth(TreeNode* root) {

        if (root == NULL) {
            return 0;
        }

        if (root->left == NULL && root->right != NULL) {

            int left = minDepth(root->left);
            int right = minDepth(root->right);

            return max(left, right) + 1;
        }

        if (root->right == NULL && root->left != NULL) {

            int le = minDepth(root->left);
            int ri = minDepth(root->right);

            return max(le, ri) + 1;
        }

        int leftheight = minDepth(root->left);
        int rightheight = minDepth(root->right);

        return min(leftheight, rightheight) + 1;
    }
};


TIME COMPLEXITY
---------------

O(N)

Every node is visited at most once.


SPACE COMPLEXITY
----------------

O(H)

H = height of the tree.

Balanced tree:

    O(log N)

Skewed tree:

    O(N)


====================================================================
                            DRY RUN
====================================================================

Example:

              3
             / \
            9   20
               /  \
              15   7


At node 3:

    left != NULL
    right != NULL

So:

    leftheight  = minDepth(9)
    rightheight = minDepth(20)


Node 9:

    left  = NULL
    right = NULL

Therefore:

    leftheight  = 0
    rightheight = 0

Return:

    min(0, 0) + 1
    = 1


Node 20:

            20
           /  \
          15   7

Both children exist.

Node 15:

    minDepth(15) = 1

Node 7:

    minDepth(7) = 1

Therefore:

    minDepth(20)
    = min(1, 1) + 1
    = 2


Now return to node 3:

    leftheight  = 1
    rightheight = 2

Therefore:

    min(1, 2) + 1
    = 2


FINAL ANSWER:

    2


====================================================================
                         INTERVIEW NOTES
====================================================================

PATTERN
-------

Binary Tree
+
DFS
+
Recursion
+
Minimum Root-to-Leaf Path


KEY OBSERVATION
---------------

NULL is not a leaf.

If one child is NULL, we must use the existing child.

Your use of max() handles this correctly because:

    max(0, validDepth)

returns the valid depth.


COMMON MISTAKES
---------------

1. Writing:

       return NULL;

   Since the function returns int, use:

       return 0;


2. Using min() when only one child exists.

   Example:

       min(0, 2) = 0

   This is incorrect because NULL is not a valid path.


3. Forgetting the +1 for the current node.


4. Confusing minimum depth with maximum depth.

   Minimum depth:

       shortest root-to-leaf path

   Maximum depth:

       longest root-to-leaf path


5. Forgetting that a leaf is an actual node:

       left == NULL
       right == NULL


====================================================================
                     WHEN TO USE THIS APPROACH
====================================================================

Use this approach when:

    - The problem involves a binary tree.
    - You need minimum depth.
    - You need a shortest root-to-leaf path.
    - You can solve the problem recursively.
    - Each node contributes one level.


====================================================================
                         FINAL COMPLEXITY
====================================================================

Time Complexity:

    O(N)

Space Complexity:

    O(H)

where:

    N = number of nodes
    H = height of the tree


====================================================================
                              END
====================================================================
*/


#include <iostream>
using namespace std;

// Definition for a Binary Tree Node
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
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {

        // Base Case
        if (root == NULL || root == p || root == q)
            return root;

        // Search in left subtree
        TreeNode *left = lowestCommonAncestor(root->left, p, q);

        // Search in right subtree
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        // If one node found in each subtree
        if (left != NULL && right != NULL)
            return root;

        // Otherwise return the non-null node
        if (left != NULL)
            return left;
        else
            return right;
    }
};

int main()
{


    TreeNode *root = new TreeNode(3);

    root->left = new TreeNode(5);
    root->right = new TreeNode(1);

    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);

    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    TreeNode *p = root->left;               // Node 5
    TreeNode *q = root->left->right->right; // Node 4

    Solution obj;

    TreeNode *ans = obj.lowestCommonAncestor(root, p, q);

    cout << "Lowest Common Ancestor: " << ans->val << endl;

    return 0;
}

/*
======================== BRUTE FORCE APPROACH ========================

Idea:

1. Find the path from root to node p.

2. Find the path from root to node q.

3. Compare both paths.

4. The last common node in both paths
   is the Lowest Common Ancestor.

Example:

Path to 5

3 -> 5

Path to 4

3 -> 5 -> 2 -> 4

Common Path

3 -> 5

Answer = 5

Time Complexity:

Finding each path = O(N)

Comparing paths = O(N)

Overall = O(N)

Space Complexity:

O(N)


======================== OPTIMAL APPROACH ========================

Idea:

Use recursion.

Case 1

If root is NULL

return NULL

Case 2

If root is equal to p or q

return root

Otherwise

Search both subtrees.

left = LCA(left subtree)

right = LCA(right subtree)

Now three cases arise.

Case 1

left != NULL
right != NULL

It means one node was found in each subtree.

Current root is the LCA.

Return root.


Case 2

Only left is non-null.

Both nodes lie in left subtree.

Return left.


Case 3

Only right is non-null.

Both nodes lie in right subtree.

Return right.


Dry Run

Suppose

            3
          /   \
         5     1
        / \
       6   2
          / \
         7   4

Find LCA of 5 and 4.

At node 5

root == p

Return 5

At node 4

root == q

Return 4

At node 2

left = NULL

right = 4

Return 4

At node 5

Already returned 5

At node 3

left = 5

right = NULL

Return 5

Answer = 5


Time Complexity:

O(N)

Each node is visited only once.


Space Complexity:

O(H)

H = Height of the tree

Worst Case (Skew Tree)

O(N)

Balanced Tree

O(log N)
*/
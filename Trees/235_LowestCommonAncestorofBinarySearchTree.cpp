// LeetCode 235. Lowest Common Ancestor of a Binary Search Tree
// VS Code Compatible C++ Solution

#include <iostream>
using namespace std;

// Definition for a binary tree node
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = right = NULL;
    }
};

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {

        // Base case
        if (root == NULL)
            return NULL;

        // Both p and q are smaller than root
        // So LCA must be in left subtree
        if (p->val < root->val && q->val < root->val)
        {
            return lowestCommonAncestor(root->left, p, q);
        }

        // Both p and q are greater than root
        // So LCA must be in right subtree
        if (p->val > root->val && q->val > root->val)
        {
            return lowestCommonAncestor(root->right, p, q);
        }

        // One node is on left and one node is on right
        // OR root itself is p or q
        // Therefore current root is the LCA
        return root;
    }
};

// Function to print result
void print(TreeNode *ans)
{
    cout << "Lowest Common Ancestor: "
         << ans->val;
}

int main()
{

    /*
              6
            /   \
           2     8
          / \   / \
         0   4 7   9
            / \
           3   5
    */

    TreeNode *root = new TreeNode(6);

    root->left = new TreeNode(2);
    root->right = new TreeNode(8);

    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);

    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);

    TreeNode *p = root->left;  // Node 2
    TreeNode *q = root->right; // Node 8

    Solution obj;

    TreeNode *ans = obj.lowestCommonAncestor(root, p, q);

    print(ans);

    return 0;
}

/*

==========================================================
LeetCode 235. Lowest Common Ancestor of a Binary Search Tree
==========================================================


Problem
-------

Given a Binary Search Tree and two nodes p and q,

Find their Lowest Common Ancestor (LCA).

LCA means the lowest node in the tree that has both p and q
as descendants.


Example:


              6
            /   \
           2     8


p = 2
q = 8


Answer = 6


==========================================================
Brute Force Approach
==========================================================

Idea:

Use the normal Binary Tree LCA approach.

1. Search left subtree.
2. Search right subtree.
3. If both sides return a node,
   current root is LCA.


Code Logic:

left = search(root->left)

right = search(root->right)


if(left && right)

    return root


Time Complexity:

O(n)


Space Complexity:

O(h)


==========================================================
Optimal Approach (BST Property)
==========================================================

Observation:

BST has ordering:

Left subtree  < Root < Right subtree


So we know where p and q can exist.


Cases:


Case 1:

Both p and q are smaller than root


          8
         /
        4
       / \
      2   6


Move left.


----------------------------------------------------------


Case 2:

Both p and q are greater than root


      4
       \
        8


Move right.


----------------------------------------------------------


Case 3:

One node is smaller and one node is greater


          6
        /   \
       2     8


They split here.

Current root is LCA.


==========================================================
Algorithm
==========================================================


1. If p and q are smaller than root

        go left


2. If p and q are greater than root

        go right


3. Otherwise

        return root



==========================================================
Complexity
==========================================================


Time Complexity:

O(h)


Where h is height of tree.


Balanced BST:

O(log n)


Worst Case:

O(n)



Space Complexity:

O(h)

Recursive stack.


==========================================================
Interview Tip
==========================================================

Binary Tree LCA (236)

Search both left and right.


BST LCA (235)

Use BST property.

Only move in one direction.


==========================================================

*/
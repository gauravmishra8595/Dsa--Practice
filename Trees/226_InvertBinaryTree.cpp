
#include <iostream>
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
    TreeNode *invertTree(TreeNode *root)
    {
       
        if (root == NULL)
            return NULL;

        swap(root->left, root->right);

        invertTree(root->left);

        invertTree(root->right);

        return root;
    }
};

void inorder(TreeNode *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main()
{
  
    TreeNode *root = new TreeNode(4);

    root->left = new TreeNode(2);
    root->right = new TreeNode(7);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    cout << "Inorder Before Inverting : ";
    inorder(root);

    Solution obj;
    obj.invertTree(root);

    cout << "\nInorder After Inverting  : ";
    inorder(root);

    return 0;
}

/*
===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:
------
Visit every node in the tree.
For every node:
1. Swap its left child and right child.
2. Repeat the same process for both subtrees.

Since every node must be visited once,
there is no better approach than this.

Time Complexity : O(n)
Space Complexity : O(h)

where
n = number of nodes
h = height of tree

===========================================================
OPTIMAL APPROACH (Recursive DFS)
===========================================================

Algorithm

invertTree(root)

1. If root is NULL
      return NULL

2. Swap
      root->left
      root->right

3. Recursively invert left subtree

4. Recursively invert right subtree

5. Return root

===========================================================
DRY RUN
===========================================================

Original Tree

            4
          /   \
         2     7
        / \   / \
       1   3 6   9


Step 1

Current Node = 4

Swap

        4
      /   \
     7     2
    / \   / \
   6   9 1   3


Recursive Call

invertTree(7)

Swap

      7
     / \
    9   6

Both children are leaves.

Return.


Recursive Call

invertTree(2)

Swap

      2
     / \
    3   1

Return.


Final Tree

            4
          /   \
         7     2
        / \   / \
       9   6 3   1

===========================================================
RECURSION TREE
===========================================================

invert(4)

|

|--- invert(7)

|       |

|       |--- invert(9)

|       |

|       |--- invert(6)

|

|--- invert(2)

        |

        |--- invert(3)

        |

        |--- invert(1)

Every node swaps its own children exactly once.

===========================================================
TIME COMPLEXITY
===========================================================

Every node is visited exactly once.

O(n)

===========================================================
SPACE COMPLEXITY
===========================================================

Recursive stack depends upon tree height.

Balanced Tree

Height = log n

Space = O(log n)

Worst Case (Skew Tree)

1
 \
  2
   \
    3
     \
      4

Height = n

Space = O(n)

===========================================================
IMPORTANT INTERVIEW POINT
===========================================================

Why does this work?

Each node is responsible only for swapping its own
left and right child.

The recursive calls ensure that every node in the
entire tree performs the same operation.

Hence, the whole tree gets inverted.

===========================================================
INTERVIEW ONE-LINER
===========================================================

Invert Binary Tree is solved using recursion by swapping
the left and right child of every node and recursively
doing the same for both subtrees.

Time : O(n)
Space : O(h)

===========================================================*/
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
    // Helper function to compare two subtrees
    bool isMirror(TreeNode *left, TreeNode *right)
    {
        // If both are NULL
        if (left == NULL && right == NULL)
            return true;

        // If one is NULL
        if (left == NULL || right == NULL)
            return false;

        // Values should be equal
        if (left->val != right->val)
            return false;

        // Check mirror condition
        return isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }

    bool isSymmetric(TreeNode *root)
    {
        if (root == NULL)
            return true;

        return isMirror(root->left, root->right);
    }
};

// Inorder Traversal
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
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(2);

    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);

    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout << "Inorder Traversal : ";
    inorder(root);

    Solution obj;

    if (obj.isSymmetric(root))
        cout << "\n\nTree is Symmetric";
    else
        cout << "\n\nTree is Not Symmetric";

    return 0;
}

/*
===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:
------
Check whether the left subtree is the mirror image
of the right subtree.

For every pair of nodes:

1. Both should exist.
2. Values should be equal.
3. Left child of first tree should match
   Right child of second tree.
4. Right child of first tree should match
   Left child of second tree.

===========================================================
OPTIMAL APPROACH (Recursive DFS)
===========================================================

Algorithm

isSymmetric(root)

1. If root == NULL
      return true

2. Compare

      root->left
      root->right

using helper function.

Helper Function

isMirror(left,right)

If both NULL
    return true

If one NULL
    return false

If values different
    return false

Return

isMirror(left->left,right->right)
&&
isMirror(left->right,right->left)

===========================================================
DRY RUN
===========================================================

Tree

             1
           /   \
          2     2
         / \   / \
        3   4 4   3

Call

isMirror(2,2)

Values Same

↓

Compare

3 with 3

Values Same

↓

NULL NULL

Return true

↓

NULL NULL

Return true

Node 3 returns true

Now compare

4 with 4

↓

NULL NULL

Return true

↓

NULL NULL

Return true

Node 4 returns true

Final

true && true

=

true

Tree is Symmetric.

===========================================================
RECURSION TREE
===========================================================

isMirror(2,2)

|

|--- isMirror(3,3)

|      |

|      |--- NULL NULL

|      |

|      |--- NULL NULL

|

|--- isMirror(4,4)

       |

       |--- NULL NULL

       |

       |--- NULL NULL

===========================================================
TIME COMPLEXITY
===========================================================

Every node is visited once.

O(n)

===========================================================
SPACE COMPLEXITY
===========================================================

Recursive stack = Height of tree

Balanced Tree

O(log n)

Worst Case

O(n)

===========================================================
IMPORTANT INTERVIEW POINT
===========================================================

Difference from LeetCode 100 (Same Tree)

LeetCode 100:

left->left  ↔ right->left

left->right ↔ right->right

LeetCode 101:

left->left  ↔ right->right

left->right ↔ right->left

This "cross comparison" makes it a mirror check.

===========================================================
INTERVIEW ONE-LINER
===========================================================

A tree is symmetric if its left subtree is the mirror
image of its right subtree. We recursively compare
left-left with right-right and left-right with
right-left.

Time : O(n)

Space : O(h)

===========================================================*/
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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        
        if (p == NULL && q == NULL)
            return true;

        if (p == NULL || q == NULL)
            return false;

        
        if (p->val != q->val)
            return false;

        
        bool left = isSameTree(p->left, q->left);

        
        bool right = isSameTree(p->right, q->right);

        
        return left && right;
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


    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);

    TreeNode *root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);

    cout << "Tree 1 Inorder : ";
    inorder(root1);

    cout << "\nTree 2 Inorder : ";
    inorder(root2);

    Solution obj;

    if (obj.isSameTree(root1, root2))
        cout << "\n\nBoth Trees are Same";
    else
        cout << "\n\nBoth Trees are Different";

    return 0;
}

/*
===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:
------
Traverse both trees simultaneously.

At every node check:

1. Both nodes should exist.
2. Their values should be equal.
3. Left subtrees should be same.
4. Right subtrees should be same.

If every node satisfies these conditions,
the trees are identical.

Time Complexity : O(n)

Space Complexity : O(h)

===========================================================
OPTIMAL APPROACH (Recursive DFS)
===========================================================

Algorithm

isSameTree(p, q)

1. If both are NULL
      return true

2. If one is NULL
      return false

3. If values are different
      return false

4. Compare left subtree

5. Compare right subtree

6. Return left && right

===========================================================
DRY RUN
===========================================================

Tree 1                Tree 2

      1                  1
     / \                / \
    2   3              2   3


Call

isSameTree(1,1)

Values equal

↓

Compare Left

isSameTree(2,2)

Values equal

↓

Compare Left

NULL NULL

Return true

↓

Compare Right

NULL NULL

Return true

Node 2 returns true

↓

Compare Right

isSameTree(3,3)

Values equal

↓

Left

NULL NULL

Return true

↓

Right

NULL NULL

Return true

Node 3 returns true

↓

Root returns

true && true

=

true

===========================================================
RECURSION TREE
===========================================================

isSameTree(1,1)

|

|--- isSameTree(2,2)

|      |

|      |--- NULL NULL

|      |

|      |--- NULL NULL

|

|--- isSameTree(3,3)

       |

       |--- NULL NULL

       |

       |--- NULL NULL

===========================================================
TIME COMPLEXITY
===========================================================

Each node is visited once.

O(n)

===========================================================
SPACE COMPLEXITY
===========================================================

Recursive stack depends on tree height.

Balanced Tree

O(log n)

Worst Case (Skew Tree)

O(n)

===========================================================
INTERVIEW POINTS
===========================================================

1. Both nodes NULL
   -> true

2. One node NULL
   -> false

3. Values different
   -> false

4. Values same
   -> Check both left and right subtree.

===========================================================
INTERVIEW ONE-LINER
===========================================================

Traverse both trees simultaneously. If every corresponding
node exists and has the same value, and both left and right
subtrees are identical, then the trees are the same.

Time : O(n)

Space : O(h)

===========================================================*/
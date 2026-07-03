#include <iostream>
#include <algorithm>
#include <cmath>
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
  
    int height(TreeNode *root)
    {
  
        if (root == NULL)
            return 0;
        int leftHeight = height(root->left);
        if (leftHeight == -1)
            return -1;
        int rightHeight = height(root->right);
        if (rightHeight == -1)
            return -1;
        if (abs(leftHeight - rightHeight) > 1)
            return -1;
        return 1 + max(leftHeight, rightHeight);
    }

    bool isBalanced(TreeNode *root)
    {
        
        return height(root) != -1;
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

    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Inorder Traversal : ";
    inorder(root);

    Solution obj;

    if (obj.isBalanced(root))
        cout << "\n\nTree is Balanced";
    else
        cout << "\n\nTree is Not Balanced";

    return 0;
}

/*
===========================================================
OPTIMAL APPROACH
===========================================================

Idea
-----

Instead of calculating height separately for every node,
calculate height and check balance together.

If any subtree becomes unbalanced,
immediately return -1.

Otherwise,
return its height.

This avoids recalculating heights.

===========================================================
ALGORITHM
===========================================================

height(root)

1. If root == NULL
      return 0

2. Find left subtree height.

3. If left height == -1
      return -1

4. Find right subtree height.

5. If right height == -1
      return -1

6. If

      abs(left-right) > 1

      return -1

7. Return

      1 + max(left,right)

-----------------------------------------------------------

isBalanced(root)

Return

height(root) != -1

===========================================================
DRY RUN
===========================================================

Tree

              1
             / \
            2   3
           / \
          4   5

--------------------------------

Node 4

Left = 0

Right = 0

Difference = 0

Height = 1

--------------------------------

Node 5

Left = 0

Right = 0

Difference = 0

Height = 1

--------------------------------

Node 2

Left Height = 1

Right Height = 1

Difference = 0

Height = 2

--------------------------------

Node 3

Height = 1

--------------------------------

Node 1

Left Height = 2

Right Height = 1

Difference = 1

Height = 3

Return 3

Since height != -1

Answer = Balanced

===========================================================
UNBALANCED EXAMPLE
===========================================================

        1
       /
      2
     /
    3

Node 3

Height = 1

↓

Node 2

Left = 1

Right = 0

Difference = 1

Height = 2

↓

Node 1

Left = 2

Right = 0

Difference = 2

Return -1

Tree is NOT Balanced.

===========================================================
WHY IS IT OPTIMAL?
===========================================================

Brute Force

height() is calculated repeatedly.

Example

height(2)

↓

height(4)

↓

Later

height(4)

Again...

Repeated work leads to O(n²).

-----------------------------------------------------------

Optimal

Every node is visited exactly once.

Height and balance are calculated together.

No repeated computation.

===========================================================
TIME COMPLEXITY
===========================================================

O(n)

Each node is visited exactly once.

===========================================================
SPACE COMPLEXITY
===========================================================

O(h)

h = Height of tree

Balanced Tree

O(log n)

Worst Case (Skew Tree)

O(n)

===========================================================
INTERVIEW ONE-LINER
===========================================================

Compute the height while checking balance.
Return -1 immediately if any subtree is unbalanced.
Otherwise, return the subtree height.
This makes the solution O(n).

===========================================================*/
#include <iostream>
#include <algorithm>
using namespace std;

// Definition of a Binary Tree Node
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
    int maxDepth(TreeNode *root)
    {
        // Base Case:
        // If tree is empty, depth is 0.
        if (root == NULL)
            return 0;

        // Recursively find depth of left subtree
        int left = maxDepth(root->left);

        // Recursively find depth of right subtree
        int right = maxDepth(root->right);

        // Current node depth =
        // 1 (current node) + maximum of left and right subtree
        return 1 + max(left, right);
    }
};

int main()
{

    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution obj;

    cout << "Maximum Depth of Binary Tree = "
         << obj.maxDepth(root);

    return 0;
}

/*
===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:
-----
Traverse every node and calculate the depth of both
left and right subtrees separately.

Steps:
1. Go to left subtree.
2. Go to right subtree.
3. Compare both depths.
4. Return larger depth + 1.

Since every node is visited exactly once,
this itself becomes the optimal solution.

Time Complexity : O(n)
Space Complexity : O(h)
where h = height of tree (recursive stack)

===========================================================
OPTIMAL APPROACH (Recursive DFS)
===========================================================

Algorithm

maxDepth(root)

1. If root == NULL
      return 0

2. leftDepth = maxDepth(root->left)

3. rightDepth = maxDepth(root->right)

4. return 1 + max(leftDepth,rightDepth)

Reason:

Every node contributes exactly one level.

Current Depth =
1 (Current Node)
+
Maximum(Left Depth, Right Depth)

===========================================================
DRY RUN
===========================================================

Tree

          1
        /   \
       2     3
      / \
     4   5

Call

maxDepth(1)

|
|-- maxDepth(2)
|      |
|      |-- maxDepth(4)
|      |      |
|      |      |-- NULL -> 0
|      |      |-- NULL -> 0
|      |
|      |      return 1
|      |
|      |-- maxDepth(5)
|             |
|             |-- NULL -> 0
|             |-- NULL -> 0
|
|             return 1
|
|      left =1
|      right=1
|
|      return 2

|

|-- maxDepth(3)
       |
       |-- NULL ->0
       |-- NULL ->0

       return 1

Now at root

left = 2
right = 1

return

1 + max(2,1)

= 3

Answer = 3

===========================================================
RECURSION TREE
===========================================================

                    1
                 /     \
                2       3
              /   \
             4     5

Depth Returned

4 -> 1

5 -> 1

2 -> 2

3 -> 1

1 -> 3

===========================================================
TIME COMPLEXITY
===========================================================

Every node is visited exactly one time.

O(n)

===========================================================
SPACE COMPLEXITY
===========================================================

Recursive stack stores at most height of tree.

Worst Case (Skew Tree)

1
 \
  2
   \
    3
     \
      4

Stack = O(n)

Balanced Tree

Height = log n

Stack = O(log n)

===========================================================
INTERVIEW ONE-LINER
===========================================================

The maximum depth of a binary tree is calculated recursively
by finding the maximum depth of the left and right subtrees
and returning 1 plus the greater of the two. Each node is
visited exactly once, making the time complexity O(n).
===========================================================*/
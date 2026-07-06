#include <iostream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
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
    int diameter = 0;

    int height(TreeNode *root)
    {

        if (root == nullptr)
            return 0;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        // Update the diameter
        diameter = max(diameter, leftHeight + rightHeight);

        // Return height of current subtree
        return 1 + max(leftHeight, rightHeight);
    }

    int diameterOfBinaryTree(TreeNode *root)
    {

        height(root);

        return diameter;
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

    cout << "Diameter = "
         << obj.diameterOfBinaryTree(root);

    return 0;
}

/*
======================== BRUTE FORCE ========================

Idea:

For every node,

1. Find height of left subtree.
2. Find height of right subtree.
3. Diameter through current node =
       leftHeight + rightHeight
4. Repeat for every node.
5. Maximum value is the answer.

Pseudo Code

diameter(root)

    if root == NULL
        return 0

    leftHeight = height(root->left)
    rightHeight = height(root->right)

    current = leftHeight + rightHeight

    leftDiameter = diameter(root->left)
    rightDiameter = diameter(root->right)

    return max(current,
               max(leftDiameter, rightDiameter))

Problem:

Height is calculated repeatedly.

Time Complexity:
O(n²)

Space Complexity:
O(h)

(h = tree height)

=============================================================



======================== OPTIMAL ============================

Observation:

While computing the height of a node,

we already know

• Height of left subtree
• Height of right subtree

So we can also calculate

Diameter through that node

without computing heights again.

Formula

Diameter through current node

= leftHeight + rightHeight

Update global answer

diameter = max(diameter,
               leftHeight + rightHeight)

Return height

1 + max(leftHeight, rightHeight)

Example

              1
             / \
            2   3
           / \
          4   5

Node 4
Height = 1

Node 5
Height = 1

Node 2

left = 1
right = 1

Diameter = 2

Height = 2

Node 3

Height = 1

Node 1

left = 2
right = 1

Diameter = 3

Answer = 3

Time Complexity:
O(n)

Every node is visited exactly once.

Space Complexity:
O(h)

Recursive call stack.

=============================================================*/
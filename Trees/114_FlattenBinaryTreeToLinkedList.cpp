#include <bits/stdc++.h>
using namespace std;

/*
Definition for Binary Tree Node
*/

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
    TreeNode *prev = nullptr;

public:
    void flatten(TreeNode *root)
    {
        if (root == nullptr)
        {
            return;
        }

        // Reverse Preorder Traversal
        // Right -> Left -> Root
        flatten(root->right);
        flatten(root->left);

        // Make current node point to previous processed node
        root->left = NULL;
        root->right = prev;

        // Update previous node
        prev = root;
    }
};

// Build Binary Tree using Level Order Input
// Use -1 for NULL nodes

TreeNode *buildTree()
{
    int val;
    cin >> val;

    if (val == -1)
        return NULL;

    TreeNode *root = new TreeNode(val);

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        int leftVal, rightVal;

        cin >> leftVal;
        cin >> rightVal;

        if (leftVal != -1)
        {
            node->left = new TreeNode(leftVal);
            q.push(node->left);
        }

        if (rightVal != -1)
        {
            node->right = new TreeNode(rightVal);
            q.push(node->right);
        }
    }

    return root;
}

// Print Flattened Tree
// Only right pointers should contain nodes

void printFlatten(TreeNode *root)
{
    while (root != NULL)
    {
        cout << root->val << " ";
        root = root->right;
    }
}

int main()
{

    TreeNode *root = buildTree();

    Solution obj;

    obj.flatten(root);

    printFlatten(root);

    return 0;
}

/*
=========================================================
LeetCode 114 - Flatten Binary Tree to Linked List
=========================================================


BRUTE FORCE APPROACH
=========================================================

Idea:

Use preorder traversal:

Root -> Left -> Right

Store every node in a vector.

Then connect nodes one by one:

current->left = NULL

current->right = next node


Example:

Tree:

        1
       / \
      2   5
     / \   \
    3   4   6


Preorder:

1 2 3 4 5 6


Create links:

1 -> 2 -> 3 -> 4 -> 5 -> 6


Problems:

- Extra space is required.
- We are storing all nodes unnecessarily.
- Problem asks for in-place modification.


Time Complexity:

O(N)


Space Complexity:

O(N)

=========================================================
OPTIMAL APPROACH (USED ABOVE)
=========================================================

Idea:

Use Reverse Preorder Traversal.

Normal preorder:

Root -> Left -> Right


Reverse it:

Right -> Left -> Root


Maintain a pointer:

prev


prev stores the node which should come after
the current node in the flattened list.


Algorithm:

1. Traverse right subtree.

2. Traverse left subtree.

3. Connect current node with previous processed node.

        root->right = prev

4. Remove left pointer.

        root->left = NULL

5. Move prev to current node.


=========================================================
Dry Run
=========================================================

Tree:

        1
       / \
      2   5
     / \   \
    3   4   6


Reverse preorder:

6 -> 5 -> 4 -> 3 -> 2 -> 1


Step 1:

Node 6

prev = 6


Step 2:

Node 5

5->right = 6

prev = 5


Step 3:

Node 4

4->right = 5

prev = 4


Step 4:

Node 3

3->right = 4

prev = 3


Step 5:

Node 2

2->right = 3

prev = 2


Step 6:

Node 1

1->right = 2

prev = 1


Final:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6


=========================================================
Why is this Optimal?
=========================================================

✔ No extra vector.

✔ Tree is modified in-place.

✔ Every node is visited exactly once.

✔ No searching for the tail node.

✔ Uses only one pointer.


=========================================================
Time Complexity
=========================================================

O(N)

Each node is processed once.


=========================================================
Space Complexity
=========================================================

O(H)

H = Height of Binary Tree

Recursive Stack:

Worst Case:

O(N)

Balanced Tree:

O(log N)


=========================================================
Interview Tip
=========================================================

When a problem asks:

"Modify Binary Tree in-place"

avoid storing nodes.

Think about:

1. Traversal order.

2. Maintaining previous/next pointers.

For flattening:

Normal Preorder:

Root -> Left -> Right


Reverse Preorder:

Right -> Left -> Root

is the easiest way to connect nodes using O(1)
extra pointer space.

=========================================================
*/
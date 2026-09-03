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
        left = nullptr;
        right = nullptr;
    }
};
class Solution
{
public:
    TreeNode *deleteNode(TreeNode *root, int key)
    {

        // Key not found
        if (root == nullptr)
            return nullptr;

        // Search in left subtree
        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }

        // Search in right subtree
        else if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }

        // Node found
        else
        {

            // Case 1: No left child
            if (root->left == nullptr)
                return root->right;

            // Case 2: No right child
            if (root->right == nullptr)
                return root->left;

            // Case 3: Two children
            // Find smallest value in right subtree
            TreeNode *temp = root->right;

            while (temp->left != nullptr)
                temp = temp->left;

            // Replace current value
            root->val = temp->val;

            // Delete duplicate node
            root->right = deleteNode(root->right, temp->val);
        }

        return root;
    }
};

int main()
{

    // Example BST:
    //
    //        5
    //       / \
    //      3   6
    //     / \   \
    //    2   4   7
    //
    // Delete 3

    TreeNode *root = new TreeNode(5);

    root->left = new TreeNode(3);
    root->right = new TreeNode(6);

    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);

    root->right->right = new TreeNode(7);

    Solution obj;

    root = obj.deleteNode(root, 3);

    // Inorder traversal
    // Expected: 2 4 5 6 7

    function<void(TreeNode *)> inorder = [&](TreeNode *node)
    {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    };

    inorder(root);

    return 0;
}

/*
================================================================================
                  LEETCODE 450 - DELETE NODE IN A BST
================================================================================

Problem Statement:
------------------
Given the root of a Binary Search Tree (BST) and an integer key, delete the
node with value key from the BST.

Return the root of the BST after deletion.

Example:
--------
Input:

        5
       / \
      3   6
     / \   \
    2   4   7

key = 3

Output:

        5
       / \
      4   6
     /     \
    2       7


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
One simple approach is to first find the node and then rebuild the BST by
collecting all values except the value to be deleted.

This does not make use of the BST structure efficiently.

Pseudo Code:
-----------
1. Traverse the entire tree.
2. Store every value except key.
3. Create a new BST by inserting all stored values.
4. Return the new root.

Complete Brute Force Code (inside comments only):
---------------------------------------------------

vector<int> values;

void store(TreeNode* root, int key) {
    if (root == nullptr)
        return;

    store(root->left, key);

    if (root->val != key)
        values.push_back(root->val);

    store(root->right, key);
}

TreeNode* insert(TreeNode* root, int val) {
    if (root == nullptr)
        return new TreeNode(val);

    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    values.clear();

    store(root, key);

    TreeNode* newRoot = nullptr;

    for (int val : values)
        newRoot = insert(newRoot, val);

    return newRoot;
}


Time Complexity:
----------------
O(N^2) in the worst case because rebuilding the BST can take O(N) for each
insertion.

Space Complexity:
-----------------
O(N) for storing the values.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
BST gives us three possibilities while searching:

    key < root->val
        -> search left

    key > root->val
        -> search right

    key == root->val
        -> node found


After finding the node, there are 3 cases.

Case 1: No left child
---------------------
Return the right child.

Case 2: No right child
----------------------
Return the left child.

Case 3: Two children
--------------------
We cannot simply remove the node.

Find the smallest node in the right subtree.

This is called the INORDER SUCCESSOR.

Copy its value into the current node, then delete that duplicate node from
the right subtree.


Intuition:
----------
For a node with two children:

        5
       / \
      3   7

If we delete 5, we need a value that can safely replace 5.

The smallest value in the right subtree is perfect.

Example:

        5
       / \
      3   7
         /
        6

The smallest value on the right is 6.

Replace 5 with 6:

        6
       / \
      3   7

Then delete the old 6.


Pseudo Code:
-----------
deleteNode(root, key):

    if root == NULL:
        return NULL

    if key < root->val:
        root->left = deleteNode(root->left, key)

    else if key > root->val:
        root->right = deleteNode(root->right, key)

    else:

        if left child is NULL:
            return right child

        if right child is NULL:
            return left child

        temp = smallest node in right subtree

        root->val = temp->val

        root->right = deleteNode(root->right, temp->val)

    return root


Complete Optimal Code (inside comments only):
-----------------------------------------------

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {

        if (root == nullptr)
            return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        }
        else {

            if (root->left == nullptr)
                return root->right;

            if (root->right == nullptr)
                return root->left;

            TreeNode* temp = root->right;

            while (temp->left != nullptr)
                temp = temp->left;

            root->val = temp->val;

            root->right = deleteNode(root->right, temp->val);
        }

        return root;
    }
};


Time Complexity:
----------------
O(H), where H is the height of the BST.

Balanced BST -> O(log N)
Skewed BST   -> O(N)


Space Complexity:
-----------------
O(H) because of recursion.

Balanced BST -> O(log N)
Worst case    -> O(N)


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Delete 3:

        5
       / \
      3   6
     / \   \
    2   4   7


Step 1:
-------
key = 3

3 < 5

Go left.

        3
       / \
      2   4


Step 2:
-------
key = 3

3 == 3

Node found.

Node 3 has TWO children:

    left  = 2
    right = 4


Step 3:
-------
Find smallest node in right subtree.

Right subtree:

    4

Smallest value = 4.


Step 4:
-------
Replace 3 with 4.

        5
       / \
      4   6
     /     \
    2       7


Step 5:
-------
Delete the old node 4.

Final tree:

        5
       / \
      4   6
     /     \
    2       7


Inorder:

2 4 5 6 7


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
BST Search + Structural Modification.


Key Observation:
----------------
Deletion has 3 cases:

1. Leaf / no children
2. One child
3. Two children


For two children:
-----------------
Use the INORDER SUCCESSOR.

Inorder successor = smallest node in the RIGHT subtree.


Common Mistakes:
----------------
1. Forgetting the NULL case.
2. Not reconnecting the parent after deletion.
3. For two children, deleting the node without replacing its value.
4. Finding the wrong replacement node.
5. Forgetting to delete the duplicate successor.
6. Returning the wrong root.


When to use this approach:
--------------------------
Whenever you need to delete a value from a Binary Search Tree.

Remember:

    Search using BST property.

    Then handle:

        0 children -> return NULL
        1 child    -> return that child
        2 children -> use inorder successor


================================================================================
KEY TAKEAWAY
================================================================================

BST Deletion:

        Find the node
             |
       +-----+-----+
       |           |
   0/1 child    2 children
       |           |
   return child   successor
                   |
             replace value
                   |
             delete successor


Optimal:
    Time  = O(H)
    Space = O(H)

Balanced BST:
    Time  = O(log N)
    Space = O(log N)

Worst-case skewed BST:
    Time  = O(N)
    Space = O(N)

================================================================================
*/

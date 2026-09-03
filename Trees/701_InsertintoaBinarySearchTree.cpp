#include <bits/stdc++.h>
using namespace std;

// TreeNode definition for VS Code
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
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {

        // If tree is empty
        if (root == nullptr)
            return new TreeNode(val);

        TreeNode *curr = root;

        while (true)
        {

            // Go left
            if (val < curr->val)
            {

                // Empty place found
                if (curr->left == nullptr)
                {
                    curr->left = new TreeNode(val);
                    break;
                }

                curr = curr->left;
            }

            // Go right
            else
            {

                // Empty place found
                if (curr->right == nullptr)
                {
                    curr->right = new TreeNode(val);
                    break;
                }

                curr = curr->right;
            }
        }

        return root;
    }
};

int main()
{

    // Create BST:
    //
    //       4
    //      / \
    //     2   7
    //    / \
    //   1   3

    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution obj;

    // Insert 5
    root = obj.insertIntoBST(root, 5);

    // Print inorder traversal
    // Expected: 1 2 3 4 5 7
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
                    LEETCODE 701 - INSERT INTO A BINARY SEARCH TREE
================================================================================

Problem Statement:
------------------
Given the root node of a Binary Search Tree (BST) and a value val, insert the
value into the BST and return the root node of the BST.

The BST property must be maintained after insertion.

BST Property:
    - Left subtree contains smaller values.
    - Right subtree contains greater values.

It is guaranteed that val does not already exist in the BST.

Example:
--------
Input:

        4
       / \
      2   7
     / \
    1   3

val = 5

Output:

        4
       / \
      2   7
     / \  /
    1   3 5


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
A simple way is to recursively traverse the BST.

At every node:
    - If val < root->val, insert into the left subtree.
    - Otherwise, insert into the right subtree.
    - If the current position is nullptr, create the new node there.

This approach is already efficient in terms of time, but uses recursion.

Pseudo Code:
-----------
insert(root, val):

    if root == nullptr:
        return new node(val)

    if val < root->val:
        root->left = insert(root->left, val)
    else:
        root->right = insert(root->right, val)

    return root


Complete Brute Force Code (inside comments only):
---------------------------------------------------

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr)
            return new TreeNode(val);

        if (val < root->val)
            root->left = insertIntoBST(root->left, val);
        else
            root->right = insertIntoBST(root->right, val);

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
O(H) because of recursion stack.

Worst case: O(N)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
Because this is a BST, we do not need to visit every node.

At each node:

    val < curr->val  -> move to left
    val > curr->val  -> move to right

Eventually, we reach a nullptr child position.

That is exactly where the new node should be inserted.

Intuition:
----------
Insertion in a BST is basically a search for the correct empty position.

We follow the same path that we would follow while searching for val.

When the required left/right child is nullptr, attach the new node there.

We use an iterative approach to achieve O(1) auxiliary space.

Pseudo Code:
-----------
insertIntoBST(root, val):

    if root == nullptr:
        return new node(val)

    curr = root

    while true:

        if val < curr->val:

            if curr->left == nullptr:
                curr->left = new node(val)
                break

            curr = curr->left

        else:

            if curr->right == nullptr:
                curr->right = new node(val)
                break

            curr = curr->right

    return root


Complete Optimal Code (inside comments only):
-----------------------------------------------

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr)
            return new TreeNode(val);

        TreeNode* curr = root;

        while (true) {
            if (val < curr->val) {
                if (curr->left == nullptr) {
                    curr->left = new TreeNode(val);
                    break;
                }
                curr = curr->left;
            }
            else {
                if (curr->right == nullptr) {
                    curr->right = new TreeNode(val);
                    break;
                }
                curr = curr->right;
            }
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
O(1) auxiliary space.

Only a pointer curr is used.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Initial BST:

        4
       / \
      2   7
     / \
    1   3

Insert val = 5


Step 1:
-------
curr = 4

5 > 4

Move right.

        4
       / \
      2   7



Step 2:
-------
curr = 7

5 < 7

Move left.

        7
       /
      5


Step 3:
-------
curr->left == nullptr

Create new node 5 and attach it to 7's left.

Final BST:

        4
       / \
      2   7
     / \  /
    1   3 5

Return the original root 4.


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Binary Search Tree Insertion.

Key Observation:
----------------
BST insertion follows exactly one path from the root.

    val < current -> go LEFT
    val > current -> go RIGHT
    nullptr       -> INSERT HERE


Common Mistakes:
----------------
1. Forgetting the case where root == nullptr.
2. Returning the newly inserted node instead of the original root.
3. Changing the wrong child pointer.
4. Searching both left and right subtrees.
5. Forgetting to move curr after deciding the direction.
6. Using recursion when O(1) auxiliary space is preferred.
7. Violating the BST property during insertion.


When to use this approach:
--------------------------
Use this whenever you need to insert a value into a Binary Search Tree.

The general pattern is:

    1. Start at root.
    2. Compare target with current node.
    3. Choose left or right.
    4. Continue until the required child is nullptr.
    5. Insert the new node there.


================================================================================
KEY TAKEAWAY
================================================================================

BST Insertion = Search for the correct NULL position.

    target < current -> LEFT
    target > current -> RIGHT
    NULL child       -> INSERT

Optimal:
    Time  = O(H)
    Space = O(1)

For a balanced BST:
    Time = O(log N)

For a skewed BST:
    Time = O(N)

================================================================================
*/

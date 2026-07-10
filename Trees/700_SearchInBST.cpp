#include <iostream>
using namespace std;

// Definition for a Binary Search Tree Node
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
    TreeNode *searchBST(TreeNode *root, int val)
    {

        while (root != nullptr)
        {

            if (root->val == val)
                return root;

            else if (val < root->val)
                root = root->left;

            else
                root = root->right;
        }

        return nullptr;
    }
};

int main()
{



    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    int val;
    cout << "Enter value to search: ";
    cin >> val;

    Solution obj;

    TreeNode *ans = obj.searchBST(root, val);

    if (ans != nullptr)
        cout << "Node Found : " << ans->val << endl;
    else
        cout << "Node Not Found" << endl;

    return 0;
}

/*
=========================================================
LeetCode 700. Search in a Binary Search Tree
=========================================================

Problem:
--------
Given the root of a Binary Search Tree (BST) and an integer val,
return the node where val is found.
If the value does not exist, return nullptr.

=========================================================
Brute Force Approach
=========================================================

Idea:
-----
Traverse every node of the binary tree without using the BST property.

Algorithm:
----------
1. If root is NULL, return NULL.
2. If root value equals val, return root.
3. Search in left subtree.
4. If found, return it.
5. Otherwise search in right subtree.

Code:

TreeNode* searchBST(TreeNode* root, int val){

    if(root==nullptr)
        return nullptr;

    if(root->val==val)
        return root;

    TreeNode* left=searchBST(root->left,val);

    if(left!=nullptr)
        return left;

    return searchBST(root->right,val);
}

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n) (Recursion Stack)

=========================================================
Optimal Approach (Using BST Property)
=========================================================

Observation:
------------
In a Binary Search Tree,

Left Child  < Root
Right Child > Root

So we don't need to search the entire tree.

Algorithm:
----------
1. Start from the root.
2. If root->val == val
      return root.
3. If val < root->val
      move to left child.
4. Else
      move to right child.
5. Continue until root becomes NULL.

Code:

TreeNode* searchBST(TreeNode* root, int val){

    while(root!=nullptr){

        if(root->val==val)
            return root;

        else if(val < root->val)
            root=root->left;

        else
            root=root->right;
    }

    return nullptr;
}

Example:
--------

            4
          /   \
         2     7
        / \   / \
       1   3 6   9

Search = 6

Step 1:
Root = 4
6 > 4
Move Right

Step 2:
Root = 7
6 < 7
Move Left

Step 3:
Root = 6
Found

Answer = Node(6)

=========================================================
Complexity Analysis
=========================================================

Brute Force

Time  : O(n)
Space : O(n)

Optimal

Best Case        : O(1)
Balanced BST     : O(log n)
Worst Case       : O(n)

Space            : O(1)

=========================================================
Why is this Optimal?
=========================================================

Instead of visiting every node, we eliminate half of the tree
at every comparison using the BST property.

This makes the search much faster for balanced trees and is the
expected solution for LeetCode 700.
*/
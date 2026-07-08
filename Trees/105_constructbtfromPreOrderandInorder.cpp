#include <iostream>
#include <vector>
#include <unordered_map>
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
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    // Linear search in inorder array
    int search(vector<int> &inorder, int left, int right, int val)
    {
        for (int i = left; i <= right; i++)
        {
            if (inorder[i] == val)
                return i;
        }
        return -1;
    }

    // preIdx is passed by reference so that every recursive call
    // shares the same preorder index.
    TreeNode *helper(vector<int> &preorder, vector<int> &inorder,
                     int &preIdx, int left, int right)
    {

        if (left > right)
            return NULL;

        TreeNode *root = new TreeNode(preorder[preIdx]);

        int inIdx = search(inorder, left, right, preorder[preIdx]);

        preIdx++;

        root->left = helper(preorder, inorder, preIdx, left, inIdx - 1);
        root->right = helper(preorder, inorder, preIdx, inIdx + 1, right);

        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {

        int preIdx = 0;

        return helper(preorder, inorder, preIdx, 0, inorder.size() - 1);
    }
};

// Preorder Traversal
void preorderPrint(TreeNode *root)
{
    if (root == NULL)
        return;

    cout << root->val << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}

// Inorder Traversal
void inorderPrint(TreeNode *root)
{
    if (root == NULL)
        return;

    inorderPrint(root->left);
    cout << root->val << " ";
    inorderPrint(root->right);
}

int main()
{

    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    Solution obj;

    TreeNode *root = obj.buildTree(preorder, inorder);

    cout << "Preorder Traversal : ";
    preorderPrint(root);

    cout << "\nInorder Traversal  : ";
    inorderPrint(root);

    cout << endl;

    return 0;
}

/*
======================== LeetCode 105 ========================

Question:
Construct a Binary Tree from Preorder and Inorder Traversal.

--------------------------------------------------------------
Brute Force Approach (Implemented Above)
--------------------------------------------------------------

Idea:

1. First element of preorder is always the root.
2. Find the root in inorder array using linear search.
3. Elements left of root belong to left subtree.
4. Elements right of root belong to right subtree.
5. Recursively repeat the same process.

Time Complexity:
- search() takes O(n)
- It is called for every node.

Overall Time = O(n^2)

Space Complexity:
O(h)
where h is the height of tree.
Worst case = O(n)

--------------------------------------------------------------
Optimal Approach
--------------------------------------------------------------

Problem in Brute Force:
Finding the root index in inorder every time takes O(n).

Optimization:
Store every inorder value and its index in an unordered_map.

unordered_map<int,int> mp;

for(int i=0;i<inorder.size();i++)
    mp[inorder[i]] = i;

Now finding root index becomes

int inIdx = mp[root->val];

which is O(1).

Time Complexity:
Building HashMap = O(n)
Building Tree = O(n)

Overall = O(n)

Space Complexity:
HashMap = O(n)
Recursion Stack = O(h)

Overall = O(n)

--------------------------------------------------------------
Important Interview Point
--------------------------------------------------------------

preIdx must be passed by reference.

Wrong:

helper(..., int preIdx, ...)

Every recursive call gets its own copy, causing incorrect tree construction.

Correct:

helper(..., int &preIdx, ...)

Now all recursive calls share the same preorder index.

--------------------------------------------------------------
Flow Example

Preorder : 3 9 20 15 7
Inorder  : 9 3 15 20 7

Root = 3

Left Inorder  = 9
Right Inorder = 15 20 7

Left Subtree:
Root = 9

Right Subtree:
Root = 20

Left = 15
Right = 7

Final Tree:

        3
       / \
      9   20
         /  \
        15   7

==============================================================
*/
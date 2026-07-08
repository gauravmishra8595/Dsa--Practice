#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Definition for Binary Tree Node
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
    // Linear Search in inorder array
    int search(vector<int> &inorder, int left, int right, int val)
    {
        for (int i = left; i <= right; i++)
        {
            if (inorder[i] == val)
                return i;
        }
        return -1;
    }

    // Build Tree using Inorder and Postorder
    TreeNode *helper(vector<int> &inorder, vector<int> &postorder,
                     int &postIdx, int left, int right)
    {

        if (left > right)
            return NULL;

        // Last element of postorder is the root
        TreeNode *root = new TreeNode(postorder[postIdx]);

        int inIdx = search(inorder, left, right, postorder[postIdx]);

        postIdx--;
       root->right = helper(inorder, postorder, postIdx, inIdx + 1, right);
        root->left = helper(inorder, postorder, postIdx, left, inIdx - 1);

        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {

        int postIdx = postorder.size() - 1;

        return helper(inorder, postorder, postIdx, 0, inorder.size() - 1);
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

    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    Solution obj;

    TreeNode *root = obj.buildTree(inorder, postorder);

    cout << "Preorder Traversal : ";
    preorderPrint(root);

    cout << "\nInorder Traversal  : ";
    inorderPrint(root);

    cout << endl;

    return 0;
}

/*
======================== LeetCode 106 ========================

Question:
Construct Binary Tree from Inorder and Postorder Traversal.

--------------------------------------------------------------
Brute Force Approach (Implemented Above)
--------------------------------------------------------------

Idea:

1. Last element of postorder is always the root.
2. Find that root in inorder using linear search.
3. Elements on the left belong to left subtree.
4. Elements on the right belong to right subtree.
5. Since we traverse postorder backwards, construct
   the RIGHT subtree first and then the LEFT subtree.

Time Complexity:
- search() = O(n)
- Called for every node.

Overall Time = O(n^2)

Space Complexity:
O(h)

Worst Case = O(n)

--------------------------------------------------------------
Optimal Approach
--------------------------------------------------------------

Problem:
Searching the root in inorder every recursive call
takes O(n).

Optimization:
Store inorder indices in a HashMap.

unordered_map<int,int> mp;

for(int i=0;i<inorder.size();i++)
    mp[inorder[i]] = i;

Now root index becomes

int inIdx = mp[root->val];

Time Complexity:
Building HashMap = O(n)
Tree Construction = O(n)

Overall = O(n)

Space Complexity:
HashMap = O(n)
Recursion Stack = O(h)

Overall = O(n)

--------------------------------------------------------------
Important Interview Points
--------------------------------------------------------------

1. postIdx must be passed by reference.

Wrong:

helper(..., int postIdx, ...)

Every recursive call gets its own copy.

Correct:

helper(..., int &postIdx, ...)

--------------------------------------------------------------

2. Build RIGHT subtree first.

Postorder:

Left -> Right -> Root

Reading backwards:

Root -> Right -> Left

Therefore,

root->right = helper(...);

must come before

root->left = helper(...);

Otherwise the tree will be incorrect.

--------------------------------------------------------------
Flow Example

Inorder   : 9 3 15 20 7
Postorder : 9 15 7 20 3

Last element = 3

          3
         / \
        9   20
           /  \
          15   7

==============================================================
*/
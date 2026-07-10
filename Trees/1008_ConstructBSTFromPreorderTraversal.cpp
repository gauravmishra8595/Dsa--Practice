#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Definition for a Binary Tree Node
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
    TreeNode *helper(vector<int> &preorder, int &i, int bound)
    {

        if (i >= preorder.size() || preorder[i] > bound)
            return nullptr;

        TreeNode *root = new TreeNode(preorder[i++]);

        root->left = helper(preorder, i, root->val);
        root->right = helper(preorder, i, bound);

        return root;
    }

    TreeNode *bstFromPreorder(vector<int> &preorder)
    {

        int i = 0;
        return helper(preorder, i, INT_MAX);
    }
};

// Inorder Traversal
void inorder(TreeNode *root)
{

    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main()
{

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<int> preorder(n);

    cout << "Enter preorder traversal:\n";

    for (int i = 0; i < n; i++)
        cin >> preorder[i];

    Solution obj;

    TreeNode *root = obj.bstFromPreorder(preorder);

    cout << "\nInorder Traversal of Constructed BST:\n";
    inorder(root);

    cout << endl;

    return 0;
}

/*

==========================================================
LeetCode 1008. Construct Binary Search Tree from Preorder Traversal
==========================================================

Problem:
--------
Given the preorder traversal of a BST,
construct and return the BST.

Example:

Preorder:
8 5 1 7 10 12

Construct BST

        8
      /   \
     5     10
    / \      \
   1   7      12


==========================================================
Brute Force Approach
==========================================================

Idea:
-----
Insert every node one by one into an empty BST.

Algorithm:
----------
for every value in preorder

insert(value)

Insertion Code:

TreeNode* insert(TreeNode* root,int val){

    if(root==nullptr)
        return new TreeNode(val);

    if(val < root->val)
        root->left=insert(root->left,val);

    else
        root->right=insert(root->right,val);

    return root;
}

Time Complexity:
----------------
Worst Case : O(n²)

Example:
1 2 3 4 5

Every insertion traverses almost the whole tree.


Space Complexity:
-----------------
O(n)


==========================================================
Optimal Approach (Bound Method)
==========================================================

Observation:
------------
Preorder = Root Left Right

Maintain an index pointing to the current element.

Every recursive call has an upper bound.

If preorder[i] > bound

that value cannot belong to this subtree.

So return NULL.

Algorithm:
----------

helper(preorder,index,bound)

1. If index reaches end
      return NULL

2. If preorder[index] > bound
      return NULL

3. Create root.

4. Build left subtree
      bound = root->val

5. Build right subtree
      bound = previous bound

6. Return root.


Example:
--------

Preorder

8 5 1 7 10 12

helper(INF)

Create 8

Left bound = 8

Create 5

Left bound = 5

Create 1

Next = 7

7 > 5

Return

Build right of 5

Create 7

Return

Back to 8

Right bound = INF

Create 10

Right bound = INF

Create 12

BST Constructed.


==========================================================
Complexity Analysis
==========================================================

Brute Force

Time  : O(n²)

Space : O(n)


Optimal

Time  : O(n)

Every node is visited exactly once.

Space : O(n)

(recursion stack)


==========================================================
Why O(n)?
==========================================================

Each preorder element is

1. Read exactly once.

2. Used to create exactly one node.

3. Never revisited.

Hence total work is linear.

==========================================================

*/
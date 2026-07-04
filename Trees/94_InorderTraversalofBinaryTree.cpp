#include <iostream>
#include <vector>

using namespace std;

// Definition of TreeNode
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
    void inorder(TreeNode *root, vector<int> &ans)
    {
        if (root == NULL)
            return;

        // Left
        inorder(root->left, ans);

        // Root
        ans.push_back(root->val);

        // Right
        inorder(root->right, ans);
    }

    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> ans;

        inorder(root, ans);

        return ans;
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

    vector<int> ans = obj.inorderTraversal(root);

    cout << "Inorder Traversal : ";

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*
=================================
Inorder Traversal (Left-Root-Right)
=================================

Example Tree

        1
       / \
      2   3
     / \
    4   5

Traversal Order

Left -> Root -> Right

Dry Run

Start at 1

Go Left

Go Left

Visit 4
Output : 4

Return to 2

Visit 2
Output : 4 2

Go Right

Visit 5
Output : 4 2 5

Return to 1

Visit 1
Output : 4 2 5 1

Go Right

Visit 3
Output : 4 2 5 1 3

Final Output

4 2 5 1 3

Time Complexity : O(N)

Every node is visited once.

Space Complexity : O(H)

H = Height of Tree
Worst Case = O(N)
Balanced Tree = O(log N)
*/
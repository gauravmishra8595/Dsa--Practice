#include <iostream>
#include <vector>

using namespace std;

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
    // Recursive DFS Function
    void preorder(TreeNode *root, vector<int> &ans)
    {
        // Base Case
        if (root == NULL)
            return;

        // Visit Root
        ans.push_back(root->val);

        // Traverse Left Subtree
        preorder(root->left, ans);

        // Traverse Right Subtree
        preorder(root->right, ans);
    }

    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> ans;

        preorder(root, ans);

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

    vector<int> ans = obj.preorderTraversal(root);

    cout << "Preorder Traversal : ";

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*

Traversal Order:
Root -> Left -> Right

Example:

        1
       / \
      2   3
     / \
    4   5

Preorder Traversal:
1 2 4 5 3

---------------------------------------------------------
Approach (Recursive DFS)
---------------------------------------------------------

Algorithm

1. If the current node is NULL, return.
2. Visit the current node (store its value).
3. Traverse the left subtree.
4. Traverse the right subtree.

Time Complexity : O(N)
Each node is visited exactly once.

Space Complexity : O(H)
H = Height of the tree (Recursion Stack)
Worst Case = O(N)
Balanced Tree = O(log N)

=========================================================

=========================
Dry Run
=========================

Tree

        1
       / \
      2   3
     / \
    4   5

Step 1:
Visit 1
ans = [1]

Step 2:
Go Left

Visit 2
ans = [1,2]

Step 3:
Go Left

Visit 4
ans = [1,2,4]

4 has no children
Return

Step 4:
Go Right of 2

Visit 5
ans = [1,2,4,5]

Return to 1

Step 5:
Go Right of 1

Visit 3
ans = [1,2,4,5,3]

Traversal Complete

Output

1 2 4 5 3

=========================
Why does it work?
=========================

Preorder traversal always follows:

1. Visit Root
2. Visit Left Subtree
3. Visit Right Subtree

The recursive function follows exactly this order,
so every node is visited once in preorder sequence.

=========================
Complexity
=========================

Time  : O(N)
Space : O(H)

N = Number of Nodes
H = Height of Tree
*/
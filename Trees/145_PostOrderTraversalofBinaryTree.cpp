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
    void postorder(TreeNode *root, vector<int> &ans)
    {
        // Base Case
        if (root == NULL)
            return;

        // Traverse Left Subtree
        postorder(root->left, ans);

        // Traverse Right Subtree
        postorder(root->right, ans);

        // Visit Root
        ans.push_back(root->val);
    }

    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> ans;

        postorder(root, ans);

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

    vector<int> ans = obj.postorderTraversal(root);

    cout << "Postorder Traversal : ";

    for (int x : ans)
        cout << x << " ";

    return 0;
}
/*
=========================================================
Binary Tree Postorder Traversal (LeetCode 145)
=========================================================

Traversal Order:
Left -> Right -> Root

Example:

        1
       / \
      2   3
     / \
    4   5

Postorder Traversal:
4 5 2 3 1

---------------------------------------------------------
Approach (Recursive DFS)
---------------------------------------------------------

Algorithm

1. If the current node is NULL, return.
2. Traverse the left subtree.
3. Traverse the right subtree.
4. Visit the current node (store its value).

Time Complexity : O(N)
Each node is visited exactly once.

Space Complexity : O(H)
H = Height of the tree (Recursion Stack)

Worst Case = O(N)
Balanced Tree = O(log N)

=========================================================
*/
/*
=========================
Dry Run
=========================

Tree

        1
       / \
      2   3
     / \
    4   5

Traversal Order

Left -> Right -> Root

Step 1:
Go Left from 1

Step 2:
Go Left from 2

Visit 4
Output = 4

Return to 2

Step 3:
Go Right from 2

Visit 5
Output = 4 5

Step 4:
Visit 2
Output = 4 5 2

Return to 1

Step 5:
Go Right

Visit 3
Output = 4 5 2 3

Step 6:
Visit 1
Output = 4 5 2 3 1

Final Output

4 5 2 3 1

=========================
Why does it work?
=========================

Postorder traversal always follows:

1. Visit Left Subtree
2. Visit Right Subtree
3. Visit Root

The recursive function follows exactly this order,
so every node is visited once in postorder sequence.

=========================
Complexity
=========================

Time  : O(N)

Each node is visited exactly once.

Space : O(H)

H = Height of the tree

Worst Case : O(N)
Balanced Tree : O(log N)
*/
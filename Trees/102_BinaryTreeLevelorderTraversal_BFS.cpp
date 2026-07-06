#include <iostream>
#include <vector>
#include <queue>

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
        left = nullptr;
        right = nullptr;
    }
};

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {

        vector<vector<int>> ans;

        if (root == nullptr)
            return ans;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {

            int size = q.size();
            vector<int> level;

            for (int i = 0; i < size; i++)
            {

                TreeNode *curr = q.front();
                q.pop();

                level.push_back(curr->val);

                if (curr->left)
                    q.push(curr->left);

                if (curr->right)
                    q.push(curr->right);
            }

            ans.push_back(level);
        }

        return ans;
    }
};

int main()
{


    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution obj;

    vector<vector<int>> ans = obj.levelOrder(root);

    cout << "Level Order Traversal:\n";

    for (auto level : ans)
    {
        for (int x : level)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}

/*
======================== BRUTE FORCE ========================

Idea:
Store every node along with its level using DFS.

1. Traverse the tree recursively.
2. Pass the current level as a parameter.
3. If the current level does not exist in the answer,
   create a new vector.
4. Insert the node into its corresponding level.

Time Complexity:
O(n)

Space Complexity:
O(n)

Although this works, interviewers generally expect
the BFS (Queue) approach for level order traversal.

=============================================================



======================== OPTIMAL (BFS) =======================

Idea:

Use a Queue.

1. Push the root node.
2. While the queue is not empty:
      • Find the number of nodes currently in the queue.
        (These nodes belong to one level.)

      • Process exactly those nodes.

      • Store their values in a temporary vector.

      • Push their left and right children into the queue.

      • Add the temporary vector to the answer.

Example:

        3
      /   \
     9     20
          /  \
         15   7

Queue:

Step 1:
[3]

Process:
Level = [3]

Queue:
[9,20]

--------------------------

Process:
Level = [9,20]

Queue:
[15,7]

--------------------------

Process:
Level = [15,7]

Queue:
[]

Answer:

[
 [3],
 [9,20],
 [15,7]
]

Time Complexity:
O(n)

Each node is visited exactly once.

Space Complexity:
O(n)

Queue may contain all nodes of one level
(worst case: last level).

=============================================================*/
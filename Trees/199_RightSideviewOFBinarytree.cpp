// LeetCode 199 - Binary Tree Right Side View
// Optimal Solution (BFS - Level Order Traversal)

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
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> ans;

        // If tree is empty
        if (root == nullptr)
            return ans;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size();

            for (int i = 0; i < size; i++)
            {
                TreeNode *curr = q.front();
                q.pop();

                // Last node of current level = Right Side View
                if (i == size - 1)
                    ans.push_back(curr->val);

                // Push left child
                if (curr->left)
                    q.push(curr->left);

                // Push right child
                if (curr->right)
                    q.push(curr->right);
            }
        }

        return ans;
    }
};

int main()
{
    /*
            1
          /   \
         2     3
          \     \
           5     4

    Right Side View = 1 3 4
    */

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);

    Solution obj;
    vector<int> ans = obj.rightSideView(root);

    cout << "Right Side View : ";

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*==========================================================
                    EXPLANATION
==========================================================

PROBLEM
-------
Return the values of the nodes that are visible when the binary
tree is viewed from the right side.

----------------------------------------------------------
BRUTE FORCE APPROACH (DFS + Store Every Level)
----------------------------------------------------------

Idea:
1. Traverse the complete tree.
2. Store every node of every level.
3. After traversal, take the last element of each level.

Time Complexity  : O(N)
Space Complexity : O(N)

Code:

void dfs(TreeNode* root, int level, vector<vector<int>>& levels)
{
    if(root==nullptr)
        return;

    if(level==levels.size())
        levels.push_back({});

    levels[level].push_back(root->val);

    dfs(root->left, level+1, levels);
    dfs(root->right, level+1, levels);
}

Then,
for every level,
answer.push_back(level.back());

----------------------------------------------------------
OPTIMAL APPROACH (BFS / Level Order Traversal)
----------------------------------------------------------

Idea:

We traverse the tree level by level.

Queue stores all nodes of the current level.

For every level:

1. Find number of nodes
      size = q.size()

2. Process exactly 'size' nodes.

3. Push their children into the queue.

4. The LAST node processed at that level is the node visible
   from the right side.

Therefore,

if(i == size-1)
    ans.push_back(curr->val);

----------------------------------------------------------
Dry Run

Tree

        1
      /   \
     2     3
      \     \
       5     4

Queue = [1]

Level 1:
Process: 1
Answer = [1]

Queue = [2,3]

Level 2:
Process 2
Process 3  <-- last node
Answer = [1,3]

Queue = [5,4]

Level 3:
Process 5
Process 4 <-- last node
Answer = [1,3,4]

----------------------------------------------------------
Time Complexity

Each node is visited exactly once.

Time = O(N)

----------------------------------------------------------
Space Complexity

Queue can contain at most one complete level.

Worst Case = O(N)

----------------------------------------------------------
Why BFS Works?

Since BFS processes one level at a time,
the last node of every level is exactly the node visible
from the right side.

Hence we simply save the last node of each level.

==========================================================*/
#include <iostream>
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
    int widthOfBinaryTree(TreeNode *root)
    {

        if (root == nullptr)
            return 0;

        long long maxWidth = 0;

        queue<pair<TreeNode *, long long>> q;
        q.push({root, 0});

        while (!q.empty())
        {

            int size = q.size();

            long long base = q.front().second; // normalization base
            long long first = 0, last = 0;

            for (int i = 0; i < size; i++)
            {

                auto curr = q.front();
                q.pop();

                long long idx = curr.second - base; // normalize index

                if (i == 0)
                    first = idx;
                if (i == size - 1)
                    last = idx;

                if (curr.first->left)
                    q.push({curr.first->left, 2 * idx});

                if (curr.first->right)
                    q.push({curr.first->right, 2 * idx + 1});
            }

            maxWidth = max(maxWidth, last - first + 1);
        }

        return (int)maxWidth;
    }
};

int main()
{

    

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);

    root->left->left = new TreeNode(5);
    root->right->right = new TreeNode(9);

    root->left->left->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    Solution obj;

    cout << "Maximum Width = "
         << obj.widthOfBinaryTree(root);

    return 0;
}

/*
======================== BRUTE FORCE ========================

Idea:

For every level:
1. Do BFS or DFS
2. Track positions of nodes in a conceptual complete binary tree
3. For each level, compute:
      rightmost index - leftmost index + 1

But recomputing positions repeatedly is inefficient.

Time Complexity:
O(n²)

Space Complexity:
O(n)


=============================================================



======================== OPTIMAL (BFS + INDEXING) =================

Idea:

We simulate a complete binary tree using indices.

Rules:
- root index = 0
- left child = 2 * i
- right child = 2 * i + 1

Problem:
Indices grow very large → overflow risk.

Fix:
Normalize indices at each level by subtracting
the first index of that level.

Steps:

1. Push root with index 0
2. For each level:
   - base = first node index
   - convert all indices:
        idx = idx - base
   - track first and last index
   - width = last - first + 1

Why it works:
We only care about relative positions,
not absolute values.

Example:

        1
       / \
      3   2
     /     \
    5       9

Indices (conceptual):
1 -> 0
3 -> 0
2 -> 1
5 -> 0
9 -> 3

Width = 4

Time Complexity:
O(n)

Each node is processed once.

Space Complexity:
O(n)

Queue stores at most one level.

=============================================================*/
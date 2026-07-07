#include <iostream>
#include <vector>
#include <map>
#include <set>
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
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    vector<vector<int>> verticalTraversal(TreeNode *root)
    {

        map<int, map<int, multiset<int>>> nodes;
        queue<pair<TreeNode *, pair<int, int>>> q;

        q.push({root, {0, 0}});

        while (!q.empty())
        {

            auto temp = q.front();
            q.pop();

            TreeNode *node = temp.first;
            int col = temp.second.first;
            int row = temp.second.second;

            nodes[col][row].insert(node->val);

            if (node->left)
                q.push({node->left, {col - 1, row + 1}});

            if (node->right)
                q.push({node->right, {col + 1, row + 1}});
        }

        vector<vector<int>> ans;

        for (auto p : nodes)
        {

            vector<int> column;

            for (auto q : p.second)
            {
                column.insert(column.end(), q.second.begin(), q.second.end());
            }

            ans.push_back(column);
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

    vector<vector<int>> ans = obj.verticalTraversal(root);

    cout << "Vertical Traversal:\n";

    for (auto col : ans)
    {
        for (int x : col)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}

/*
======================== BRUTE FORCE APPROACH ========================

Idea:

1. Perform DFS/BFS and store every node as:
      (column, row, value)

2. Store these triples in a vector.

3. Sort the vector according to:
      a) Column
      b) Row
      c) Value

4. Traverse the sorted vector and group nodes having the same column.

Time Complexity:
O(N log N)

Space Complexity:
O(N)

Drawback:
Sorting the complete vector takes O(N log N).


======================== OPTIMAL APPROACH ========================

Idea:

Instead of storing everything in one vector and sorting later,
store nodes directly in ordered data structures.

Data Structure Used:

map<
    column,
    map<
        row,
        multiset<value>
    >
>

Why?

1. map automatically keeps columns sorted.

2. Nested map automatically keeps rows sorted.

3. multiset automatically sorts nodes having
   the same row and column.

Algorithm:

1. Perform BFS.

2. Root starts at
      (column = 0, row = 0)

3. Left child:
      (column - 1, row + 1)

4. Right child:
      (column + 1, row + 1)

5. Insert every node into

      nodes[column][row].insert(value);

6. Finally traverse the maps from left column
   to right column and collect the answer.

Why multiset?

Suppose two nodes have

Same Column
Same Row

Example:

        1
       / \
      2   3
       \ /
        5 4

Coordinates:

1 -> (0,0)
2 -> (-1,1)
3 -> (1,1)
5 -> (0,2)
4 -> (0,2)

Output should be

1 4 5

instead of

1 5 4

multiset automatically keeps

4 5

in sorted order.

Time Complexity:

Insertion into map/multiset:
O(log N)

Total:
O(N log N)

Space Complexity:

O(N)
*/
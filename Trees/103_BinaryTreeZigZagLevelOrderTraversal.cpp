#include <iostream>
#include <vector>
#include <queue>
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
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {

        vector<vector<int>> ans;

        if (root == NULL)
            return ans;

        queue<TreeNode *> q;
        q.push(root);

        bool leftToRight = true;

        while (!q.empty())
        {

            int size = q.size();
            vector<int> level(size);

            for (int i = 0; i < size; i++)
            {

                TreeNode *curr = q.front();
                q.pop();

                // Decide the index based on traversal direction
                int index;

                if (leftToRight)
                    index = i;
                else
                    index = size - 1 - i;

                level[index] = curr->val;

                if (curr->left)
                    q.push(curr->left);

                if (curr->right)
                    q.push(curr->right);
            }

            ans.push_back(level);

            leftToRight = !leftToRight;
        }

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

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution obj;

    vector<vector<int>> ans = obj.zigzagLevelOrder(root);

    cout << "Zigzag Level Order Traversal:\n";

    for (auto level : ans)
    {
        for (int x : level)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}

/*
======================== BRUTE FORCE APPROACH ========================

Idea:

1. Perform normal Level Order Traversal using BFS.

2. Store each level in a vector.

3. Reverse every alternate level using reverse().

Example:

Level 0 : 1

Level 1 : 2 3
Reverse -> 3 2

Level 2 : 4 5 6 7

Answer:

1
3 2
4 5 6 7

Time Complexity:
O(N)

Space Complexity:
O(N)

The reverse() function takes O(K) time for a level
having K nodes.


======================== OPTIMAL APPROACH ========================

Idea:

Instead of filling the vector from left to right
and reversing later, place every node directly
at its correct index.

For every level:

If traversing Left -> Right

index = i

If traversing Right -> Left

index = size - 1 - i

Example:

Level:

2 3

size = 2

i = 0

index = 2-1-0 = 1

Store 2 at position 1

i = 1

index = 2-1-1 = 0

Store 3 at position 0

Vector becomes

3 2

No reverse() required.

Algorithm:

1. Perform BFS.

2. For every level create

vector<int> level(size);

3. Calculate correct index.

4. Store node value at that index.

5. Push children into queue.

6. Toggle traversal direction.

Time Complexity:

O(N)

Space Complexity:

O(N)

Why is it better?

No extra traversal is needed to reverse the vector.

Each node is placed exactly once in its final position.
*/
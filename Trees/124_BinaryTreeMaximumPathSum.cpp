#include <bits/stdc++.h>
using namespace std;

/*
Definition for a Binary Tree Node.
*/

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
    // Helper function
    int maxPathDown(TreeNode *node, int &maxi)
    {
        // Base Case
        if (node == NULL)
            return 0;

        // Ignore negative path sums
        int left = max(0, maxPathDown(node->left, maxi));
        int right = max(0, maxPathDown(node->right, maxi));

        // Update maximum path sum
        maxi = max(maxi, left + right + node->val);

        // Return maximum path extending to parent
        return max(left, right) + node->val;
    }

    int maxPathSum(TreeNode *root)
    {
        int maxi = INT_MIN;

        maxPathDown(root, maxi);

        return maxi;
    }
};

// Function to build Binary Tree (Level Order)
// Use -1 for NULL nodes.
TreeNode *buildTree()
{
    int val;
    cin >> val;

    if (val == -1)
        return NULL;

    TreeNode *root = new TreeNode(val);

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();

        int leftValue, rightValue;

        cin >> leftValue;

        if (leftValue != -1)
        {
            current->left = new TreeNode(leftValue);
            q.push(current->left);
        }

        cin >> rightValue;

        if (rightValue != -1)
        {
            current->right = new TreeNode(rightValue);
            q.push(current->right);
        }
    }

    return root;
}

int main()
{
    

    TreeNode *root = buildTree();

    Solution obj;

    cout << obj.maxPathSum(root);

    return 0;
}

/*
=========================================================
LeetCode 124 - Binary Tree Maximum Path Sum
=========================================================

BRUTE FORCE APPROACH
=========================================================

Idea

For every node,

consider it as the highest node
of the path.

Then

find every possible path passing through it.

Finally

take the maximum path sum.

Pseudo Code

For every node

    Find maximum path from left subtree.

    Find maximum path from right subtree.

    Calculate

    left + node + right

    Update answer.

Problems

---------

• Same subtree is calculated many times.

• Huge amount of repeated work.

Time Complexity

O(N²)

Worst case

(Skewed Tree)

Space Complexity

O(H)

Recursive Stack

=========================================================
OPTIMAL APPROACH (USED ABOVE)
=========================================================

Idea

We use Postorder Traversal.

Why?

Because

before calculating answer for a node,

we first need answers of

Left Subtree

and

Right Subtree.

For every node,

there are two possibilities.

1.

Return only one side to parent.

Either

Left Path

or

Right Path

because parent cannot take both.

Return

max(left,right)+node->val

--------------------------------

2.

Update Global Maximum

Current node can connect

Left Path

+

Current Node

+

Right Path

So

Candidate Answer

left + right + node->val

Update

maxi

with this value.

--------------------------------

Negative Path

If a subtree contributes a negative sum,

ignore it.

Instead of

-10

take

0

Hence

left = max(0,left)

right = max(0,right)

=========================================================
Dry Run
=========================================================

Tree

        -10
       /    \
      9      20
            /  \
           15   7

--------------------------------

Node 15

left = 0

right = 0

Current Sum

15

maxi = 15

Return

15

--------------------------------

Node 7

Current Sum

7

maxi = 15

Return

7

--------------------------------

Node 20

left = 15

right = 7

Current Sum

15 + 7 + 20

= 42

maxi = 42

Return

20 + max(15,7)

= 35

--------------------------------

Node 9

Current Sum

9

Return

9

--------------------------------

Node -10

left = 9

right = 35

Current Sum

9 + 35 -10

=34

maxi remains

42

Answer

42

=========================================================
Why is this Optimal?
=========================================================

✔ Every node is visited only once.

✔ No repeated calculations.

✔ Ignores negative paths.

✔ Uses Postorder Traversal.

✔ Maintains global maximum while traversing.

=========================================================
Time Complexity
=========================================================

O(N)

Every node is visited exactly once.

=========================================================
Space Complexity
=========================================================

O(H)

H = Height of Tree

Worst Case

O(N)

(Skewed Tree)

Best Case

O(log N)

(Balanced Tree)

=========================================================
Interview Tip
=========================================================

Whenever a Binary Tree problem asks for

"Maximum Path"

think about

✔ Postorder Traversal

because answers of left and right child
must be known before processing the parent.

Also remember

Return value

≠

Final Answer

Return Value

=

Maximum path that can extend to parent.

Final Answer

=

Maximum path anywhere in the tree.

=========================================================

Sample Input

-10 9 20 -1 -1 15 7 -1 -1 -1 -1

Sample Output

42

=========================================================*/
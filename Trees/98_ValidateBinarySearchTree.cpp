#include <iostream>
#include <climits>
using namespace std;

// Definition for a binary tree node.
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = right = NULL;
    }
};

class Solution
{
public:
    bool solve(TreeNode *root, long long low, long long high)
    {

        // Empty tree is always a valid BST
        if (root == NULL)
            return true;

        // Current node must lie within the valid range
        if (root->val <= low || root->val >= high)
            return false;

        // Left subtree: values must be smaller than root
        // Right subtree: values must be greater than root
        return solve(root->left, low, root->val) &&
               solve(root->right, root->val, high);
    }

    bool isValidBST(TreeNode *root)
    {
        return solve(root, LLONG_MIN, LLONG_MAX);
    }
};

// Function to print result
void printResult(bool ans)
{
    if (ans)
        cout << "Valid BST";
    else
        cout << "Not a Valid BST";
}

int main()
{

    /*
              5
            /   \
           3     7
          / \   / \
         2  4  6   8
    */

    TreeNode *root = new TreeNode(5);

    root->left = new TreeNode(3);
    root->right = new TreeNode(7);

    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);

    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(8);

    Solution obj;

    bool ans = obj.isValidBST(root);

    printResult(ans);

    return 0;
}

/*

==========================================================
LeetCode 98. Validate Binary Search Tree
==========================================================

Problem
-------

Given the root of a binary tree,

Return true if it is a valid Binary Search Tree (BST),
otherwise return false.


A BST satisfies:

1. Left subtree contains only smaller values.

2. Right subtree contains only greater values.

3. Both left and right subtrees are also BSTs.


Example

        5
      /   \
     3     7
    / \   / \
   2   4 6   8

Output

Valid BST


==========================================================
Wrong Approach
==========================================================

Many beginners think we only need to check

left->val < root->val

right->val > root->val

Example

        10
       /  \
      5    15
          /  \
         6    20

Checks

5 < 10 ✔

15 > 10 ✔

6 < 15 ✔

20 > 15 ✔

Looks correct...

But 6 is inside the RIGHT subtree of 10.

So 6 should also be greater than 10.

Hence this tree is NOT a BST.

Therefore checking only parent-child relation
is NOT enough.


==========================================================
Brute Force Approach
==========================================================

Idea

For every node,

Find

Maximum value in left subtree

Minimum value in right subtree

If

max(left) < root

and

min(right) > root

then continue recursively.

Functions Required

findMax()

findMin()

isValidBST()

Time Complexity

O(n²)

Because for every node we again traverse
its subtree.

Space Complexity

O(h)


==========================================================
Optimal Approach (Range Method)
==========================================================

Idea

Every node has a valid range.

Initially

(-∞ , +∞)

Root can take any value.

Suppose

        8

Left subtree

must be

(-∞ , 8)

Right subtree

must be

(8 , +∞)

Now suppose we move to node 6.

Its range becomes

(4 , 8)

because

it must be greater than 4

and

less than 8.

Algorithm

1. Start with

(-∞ , +∞)

2. If node value is outside range

Return false.

3. Go Left

(high = root value)

4. Go Right

(low = root value)

5. If every node satisfies its range

Return true.


==========================================================
Complexity
==========================================================

Time Complexity

O(n)

Every node visited once.


Space Complexity

O(h)

Recursive stack.

Worst Case

O(n)

Balanced Tree

O(log n)


==========================================================
Interview Tip
==========================================================

Brute Force

Find Max Left

Find Min Right

O(n²)


Optimal

Pass

Minimum Allowed Value

Maximum Allowed Value

to every recursive call.

Time

O(n)

This is the expected solution for
LeetCode 98.

==========================================================*/

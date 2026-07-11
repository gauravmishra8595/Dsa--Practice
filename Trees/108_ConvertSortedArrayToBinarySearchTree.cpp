#include <iostream>
#include <vector>
using namespace std;

// Definition for a binary tree node
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
    TreeNode *build(vector<int> &nums, int left, int right)
    {

        // Base Case
        if (left > right)
            return NULL;

        // Find middle element
        int mid = left + (right - left) / 2;

        // Create root node
        TreeNode *root = new TreeNode(nums[mid]);

        // Left half of array creates left subtree
        root->left = build(nums, left, mid - 1);

        // Right half of array creates right subtree
        root->right = build(nums, mid + 1, right);

        return root;
    }

    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return build(nums, 0, nums.size() - 1);
    }
};

// Inorder Traversal to check BST
void inorder(TreeNode *root)
{
    if (root == NULL)
        return;

    inorder(root->left);

    cout << root->val << " ";

    inorder(root->right);
}

int main()
{

    vector<int> nums = {-10, -3, 0, 5, 9};

    Solution obj;

    TreeNode *root = obj.sortedArrayToBST(nums);

    cout << "Inorder Traversal of BST: ";

    inorder(root);

    return 0;
}

/*

==========================================================
LeetCode 108. Convert Sorted Array to Binary Search Tree
==========================================================


Problem
-------

Given a sorted array,

convert it into a height-balanced Binary Search Tree.


Example:

Array:

[-10,-3,0,5,9]


BST:


          0
        /   \
      -3     5
     /        \
   -10         9



==========================================================
Brute Force Approach
==========================================================

Idea:

Take the first or last element as root and insert
remaining elements into BST.

Problem:

The tree may become unbalanced.


Example:

Array:

[1,2,3,4,5]


Taking first element:


1
 \
  2
   \
    3
     \
      4
       \
        5


This becomes a skewed tree.


Time Complexity:

O(n log n)


Space Complexity:

O(n)



==========================================================
Optimal Approach
==========================================================

Observation:

The array is already sorted.

For a balanced BST:

Middle element should be the root.


Example:


Array:

[-10,-3,0,5,9]


Middle element:

0


             0
           /   \
        -3       5
       /          \
    -10            9



Algorithm:

1. Find middle element.

2. Create node with middle value.

3. Left half of array becomes left subtree.

4. Right half of array becomes right subtree.

5. Repeat recursively.



Recursive Function:

build(nums,left,right)



Base Case:

If

left > right


return NULL



==========================================================
Dry Run
==========================================================


nums:

[-10,-3,0,5,9]


left = 0

right = 4


mid = 2


root = 0



Left Part:

[-10,-3]


mid = 0


left child = -10


Right Part:

[5,9]


mid = 3


right child = 5



Final Tree:


          0
        /   \
     -10      5
        \       \
        -3       9



==========================================================
Complexity
==========================================================


Time Complexity:

O(n)


Every element is visited once.


Space Complexity:

O(log n)


Recursive stack for balanced tree.


Worst Case:

O(n)


==========================================================
Interview Tip
==========================================================


Sorted Array + Balanced BST

Always think:

Middle element = Root


Left half = Left subtree


Right half = Right subtree


This is the expected solution for
LeetCode 108.


==========================================================

*/
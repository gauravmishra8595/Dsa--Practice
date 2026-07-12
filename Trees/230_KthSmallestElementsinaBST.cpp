#include <bits/stdc++.h>
using namespace std;

// Tree Node Definition
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

// =========================================================
// Optimal Solution
// =========================================================

class Solution
{
public:
    void inorder(TreeNode *root, vector<int> &ans)
    {
        if (root == nullptr)
            return;

        inorder(root->left, ans);

        ans.push_back(root->val);

        inorder(root->right, ans);
    }

    int kthSmallest(TreeNode *root, int k)
    {
        vector<int> ans;

        inorder(root, ans);

        return ans[k - 1];
    }
};
int main()
{
    TreeNode *root = new TreeNode(3);

    root->left = new TreeNode(1);
    root->right = new TreeNode(4);

    root->left->right = new TreeNode(2);

    int k = 2;

    Solution obj;

    cout << obj.kthSmallest(root, k);

    return 0;
}

/*
=========================================================
LeetCode 230 - Kth Smallest Element in a BST
=========================================================


Problem Statement
-----------------

Given the root of a Binary Search Tree (BST) and an integer k,
return the kth smallest value in the BST.



Example:

Input:

        3
       / \
      1   4
       \
        2


k = 2


BST Inorder:

1 2 3 4


Answer:

2



=========================================================
BRUTE FORCE APPROACH
=========================================================


Idea
----

A BST inorder traversal gives values in sorted order.

So:

1. Perform inorder traversal.
2. Store all values in a vector.
3. Return vector[k-1].



Pseudo Code
-----------


inorder(root)

    if root is null

        return


    inorder(left)


    store root value


    inorder(right)



call inorder(root)


return ans[k-1]



Brute Force Code
----------------


void inorder(TreeNode* root, vector<int>& ans)
{
    if(root == nullptr)
        return;


    inorder(root->left, ans);


    ans.push_back(root->val);


    inorder(root->right, ans);
}



int kthSmallest(TreeNode* root, int k)
{
    vector<int> ans;


    inorder(root, ans);


    return ans[k-1];
}



Time Complexity:

O(n)


Every node is visited once.



Space Complexity:

O(n)


Vector stores all nodes.

Recursive stack:

O(height)



=========================================================
OPTIMAL APPROACH
=========================================================


Observation
-----------

In a BST:

Left subtree contains smaller values.

Root contains middle value.

Right subtree contains larger values.


Therefore:

Inorder traversal gives sorted order.



Instead of storing all nodes:

Maintain:

count = number of visited nodes

answer = kth node value



Stop immediately when count becomes k.



Pseudo Code
-----------


count = 0


inorder(root)

    if root is null

        return


    inorder(left)


    count++

    if count == k

        answer = root value

        return



    inorder(right)



return answer



Optimal Code
------------


void inorder(TreeNode* root)
{
    if(root == nullptr)
        return;


    inorder(root->left);


    count++;


    if(count == k)

        answer = root->val;



    inorder(root->right);
}



int kthSmallest(TreeNode* root, int k)
{
    inorder(root);

    return answer;
}



Time Complexity:

O(k)

Average case:

Only first k nodes are visited.



Space Complexity:

O(height)


Only recursion stack is used.



=========================================================
INTERVIEW NOTES
=========================================================


Pattern:

BST + Inorder Traversal


Key Observation:

Inorder traversal of BST gives sorted order.



Common Mistakes:

1. Using preorder traversal.

2. Forgetting that k is 1-indexed.

3. Returning ans[k] instead of ans[k-1].



Dry Run:

Tree:

        3
       / \
      1   4
       \
        2


Inorder:

1 -> count 1

2 -> count 2


k = 2


Answer:

2



Final Complexity:


Vector Approach:

Time  : O(n)

Space : O(n)



Optimized Approach:

Time  : O(k)

Space : O(height)



=========================================================
*/
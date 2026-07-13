#include <bits/stdc++.h>
using namespace std;

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
    unordered_set<int> seen;

    bool dfs(TreeNode *root, int k)
    {
        if (root == nullptr)
            return false;

        if (seen.count(k - root->val))
            return true;

        seen.insert(root->val);

        return dfs(root->left, k) || dfs(root->right, k);
    }

    bool findTarget(TreeNode *root, int k)
    {
        seen.clear();
        return dfs(root, k);
    }
};

int main()
{
    /*
            5
          /   \
         3     6
        / \     \
       2   4     7
    */

    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);

    Solution obj;

    cout << obj.findTarget(root, 9) << endl;  // 1
    cout << obj.findTarget(root, 28) << endl; // 0

    return 0;
}

/*

=========================================
Leetcode 653. Two Sum IV - Input is a BST
=========================================

Problem Statement:
------------------
Given the root of a Binary Search Tree and an integer k,
return true if there exist two elements in the BST such that
their sum is equal to k, otherwise return false.

------------------------------------------------------------

Example:
--------

Input:
        5
      /   \
     3     6
    / \     \
   2   4     7

k = 9

Output:
true

Explanation:
2 + 7 = 9
or
3 + 6 = 9

------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Store the inorder traversal of the BST in a vector.
Since inorder traversal of BST is sorted, apply the
Two Pointer technique.

Pseudo Code:
------------

Perform inorder traversal

Store values in vector

i = 0
j = n-1

while(i<j)

    if(vec[i]+vec[j]==k)
        return true

    else if(sum<k)
        i++

    else
        j--

return false

Complete Brute Force Code:
--------------------------

class Solution {
public:

    void inorder(TreeNode* root, vector<int>& vec){

        if(root==nullptr)
            return;

        inorder(root->left,vec);
        vec.push_back(root->val);
        inorder(root->right,vec);
    }

    bool findTarget(TreeNode* root, int k) {

        vector<int> vec;

        inorder(root,vec);

        int i=0;
        int j=vec.size()-1;

        while(i<j){

            int sum=vec[i]+vec[j];

            if(sum==k)
                return true;

            else if(sum<k)
                i++;

            else
                j--;
        }

        return false;
    }
};

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n)

------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
For every node having value x,
we only need to know whether
(k - x) has already been visited.

A HashSet provides O(1) average lookup.

No need to store the complete inorder traversal.

Intuition:
----------
Traverse the tree using DFS.

For every node:

1. Check whether (k-node->val) exists in HashSet.
2. If yes → answer found.
3. Otherwise insert current value.
4. Continue DFS.

Pseudo Code:
------------

DFS(node)

if node==NULL
    return false

if HashSet contains (k-node->val)
    return true

insert node->val

return DFS(left) OR DFS(right)

Complete Optimal Code:
----------------------

class Solution {
public:

    unordered_set<int> seen;

    bool dfs(TreeNode* root,int k){

        if(root==nullptr)
            return false;

        if(seen.count(k-root->val))
            return true;

        seen.insert(root->val);

        return dfs(root->left,k) || dfs(root->right,k);
    }

    bool findTarget(TreeNode* root,int k){

        seen.clear();

        return dfs(root,k);
    }
};

Time Complexity:
----------------
O(n)

Every node is visited exactly once.

Space Complexity:
-----------------
O(n)

HashSet may store all node values.

------------------------------------------------------------
Dry Run
------------------------------------------------------------

Tree:

        5
      /   \
     3     6
    / \     \
   2   4     7

k = 9

HashSet = {}

Visit 5

Need 4

Not found

Insert 5

HashSet = {5}

Visit 3

Need 6

Not found

Insert 3

HashSet = {5,3}

Visit 2

Need 7

Not found

Insert 2

HashSet = {5,3,2}

Backtrack

Visit 4

Need 5

Found!!

Return true.

------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
DFS + HashSet

Key Observation:
----------------
Instead of comparing every pair,
store previously visited values and
search for the complement.

Common Mistakes:
----------------
1. Forgetting to clear the HashSet before each call.
2. Searching after inserting current value when
   k = 2 * node->val (can match the same node).
3. Assuming inorder traversal is mandatory.
4. Returning false before checking both children.

When to use this approach:
--------------------------
Use whenever:

• Need to find a pair with target sum in a tree.
• O(n²) pair checking is too slow.
• Fast complement lookup using HashSet is possible.

*/
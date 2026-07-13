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
        left = right = nullptr;
    }
};
class BSTIterator
{
    stack<TreeNode *> st;

    void pushAll(TreeNode *node)
    {
        while (node)
        {
            st.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode *root)
    {
        pushAll(root);
    }

    int next()
    {
        TreeNode *node = st.top();
        st.pop();
        pushAll(node->right);
        return node->val;
    }

    bool hasNext()
    {
        return !st.empty();
    }
};
int main()
{


    TreeNode *root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    BSTIterator it(root);

    while (it.hasNext())
        cout << it.next() << " ";

    return 0;
}

/*

======================================== LeetCode 173 ========================================
                           Binary Search Tree Iterator
===============================================================================================

Problem Statement
-----------------
Implement the BSTIterator class that represents an iterator over the in-order traversal
of a Binary Search Tree (BST).

Implement:

1. BSTIterator(TreeNode* root)
   Initializes the iterator.

2. int next()
   Returns the next smallest number.

3. bool hasNext()
   Returns true if there exists a next smallest number.

The iterator should run with:
- next() : Average O(1)
- hasNext() : O(1)
- Extra Space : O(h)
where h = height of BST.

-----------------------------------------------------------------------------------------------
Example
-----------------------------------------------------------------------------------------------

Input:
Tree = [7,3,15,null,null,9,20]

Operations:
BSTIterator(root)
next()
next()
hasNext()
next()
hasNext()
next()
hasNext()
next()
hasNext()

Output:
3
7
true
9
true
15
true
20
false

===============================================================================================
Brute Force Approach
===============================================================================================

Idea
----
Store complete inorder traversal into a vector.

Then simply move an index forward whenever next() is called.

Pseudo Code
-----------
inorder(root)

next():
    return inorder[index++]

hasNext():
    return index < inorder.size()

Complete Brute Force Code
-------------------------

class BSTIterator {
    vector<int> inorder;
    int idx = 0;

    void dfs(TreeNode* root){
        if(root==NULL) return;
        dfs(root->left);
        inorder.push_back(root->val);
        dfs(root->right);
    }

public:
    BSTIterator(TreeNode* root){
        dfs(root);
    }

    int next(){
        return inorder[idx++];
    }

    bool hasNext(){
        return idx < inorder.size();
    }
};

Time Complexity
---------------
Construction : O(N)

next() : O(1)

hasNext() : O(1)

Space Complexity
----------------
O(N)

===============================================================================================
Optimal Approach
===============================================================================================

Observation
-----------
Instead of storing the entire inorder traversal, we only need the path to the current node.

The next inorder node can always be obtained by:

- Pop stack top.
- Move to its right subtree.
- Push all left nodes.

Thus only O(height) nodes remain inside stack.

Intuition
---------
The stack always stores the path to the next smallest element.

Whenever we visit a node:
1. Remove it.
2. Process its right child.
3. Push every left descendant.

Pseudo Code
-----------

pushAll(root)

next():
    node = st.top()
    st.pop()

    pushAll(node->right)

    return node->val

hasNext():
    return stack not empty

Complete Optimal Code
---------------------

class BSTIterator {
    stack<TreeNode*> st;

    void pushAll(TreeNode* node){
        while(node){
            st.push(node);
            node=node->left;
        }
    }

public:

    BSTIterator(TreeNode* root){
        pushAll(root);
    }

    int next(){
        TreeNode* node=st.top();
        st.pop();
        pushAll(node->right);
        return node->val;
    }

    bool hasNext(){
        return !st.empty();
    }
};

Time Complexity
---------------
Constructor : O(h)

next() :
Amortized O(1)

(Each node enters and leaves stack exactly once.)

hasNext() :
O(1)

Space Complexity
----------------
O(h)

where h = height of tree.

===============================================================================================
Dry Run
===============================================================================================

Tree

        7
      /   \
     3     15
          /  \
         9   20

Initialization

pushAll(7)

Stack:
7
3(top)

--------------------------------

next()

Pop 3

Output = 3

Stack:
7

--------------------------------

next()

Pop 7

pushAll(15)

Push 15
Push 9

Stack

15
9(top)

Output = 7

--------------------------------

next()

Pop 9

Output = 9

Stack

15(top)

--------------------------------

next()

Pop 15

pushAll(20)

Stack

20(top)

Output = 15

--------------------------------

next()

Pop 20

Stack empty

Output = 20

===============================================================================================
Interview Notes
===============================================================================================

Pattern
-------
BST + Stack + Controlled Inorder Traversal

Key Observation
---------------
Instead of storing entire inorder traversal, keep only the left path.

Each node is pushed exactly once and popped exactly once.

Hence amortized O(1).

Common Mistakes
---------------
1. Forgetting to push left chain of right subtree.
2. Returning before processing right child.
3. Using recursion for every next() call.
4. Storing full inorder unnecessarily.

When to use this approach
-------------------------
Whenever:
- BST Iterator
- Kth Smallest in BST
- Controlled inorder traversal
- Lazy traversal
- Memory optimization over full traversal

===============================================================================================

*/
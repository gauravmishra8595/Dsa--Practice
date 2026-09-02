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
    bool checkTree(TreeNode *root)
    {
        return root->val == root->left->val + root->right->val;
    }
};

int main()
{
    TreeNode *root = new TreeNode(10);
    root->left = new TreeNode(4);
    root->right = new TreeNode(6);

    Solution sol;

    cout << boolalpha << sol.checkTree(root) << '\n';

    return 0;
}

/*
================================================================================
             LEETCODE 2236 - ROOT EQUALS SUM OF CHILDREN
================================================================================

Problem Statement:
------------------
Given the root of a binary tree with exactly 3 nodes:

        root
       /    \
    left    right

Return true if:

    root.val == root.left.val + root.right.val

Otherwise return false.


--------------------------------------------------------------------------------
Example:
--------------------------------------------------------------------------------

Input:

        10
       /  \
      4    6

Root value:

    10

Children:

    4 + 6 = 10

Therefore:

    10 == 10

Answer:

    true


Another Example:

        5
       / \
      2   7

    2 + 7 = 9

    5 != 9

Answer:

    false


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
------
There is no meaningful brute-force approach required.

We only need to inspect three nodes:

    root
    root->left
    root->right

A traversal would be unnecessary because the problem guarantees that
the binary tree contains exactly 3 nodes.

For revision, we can still imagine traversing the tree and collecting
all node values, then checking the root against its two children.

Pseudo Code:
------------

    traverse the tree

    collect node values

    return:
        root value == left value + right value


Complete Brute Force Code:
--------------------------

/*
class Solution {
public:
    void dfs(TreeNode* root, vector<int>& values) {
        if (root == nullptr)
            return;

        values.push_back(root->val);

        dfs(root->left, values);
        dfs(root->right, values);
    }

    bool checkTree(TreeNode* root) {
        vector<int> values;

        dfs(root, values);

        return values[0] == values[1] + values[2];
    }
};
*/

// Time Complexity:
// ----------------
// Traversal visits all 3 nodes:

//     O(N)

// Since N = 3:

//     O(1)


// Space Complexity:
// -----------------
// The vector stores 3 values and recursion depth is at most 3:

//     O(N)

// Since N = 3:

//     O(1)


// This approach is unnecessarily complicated for this problem.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// The tree is guaranteed to contain exactly 3 nodes.

// Its structure is always:

//         root
//        /    \
//     left    right

// Therefore, there is no need for traversal.

// We can directly check:

//     root->val == root->left->val + root->right->val


// Intuition:
// ----------
// The problem literally asks whether the root's value equals the sum
// of its two children's values.

// So just access the three values directly.


// Pseudo Code:
// ------------

//     if root.val == root.left.val + root.right.val:
//         return true

//     return false


// Complete Optimal Code:
// ----------------------

// /*
// class Solution {
// public:
//     bool checkTree(TreeNode* root) {
//         return root->val ==
//                root->left->val +
//                root->right->val;
//     }
// };
// */


// Time Complexity:
// ----------------
// Only three node values are accessed.

//     O(1)


// Space Complexity:
// -----------------
// No extra data structure or recursion is used.

//     O(1)


// ================================================================================
// DRY RUN
// ================================================================================

// Example:

//         10
//        /  \
//       4    6


// Step 1:
// -------
// Access root:

//     root->val = 10


// Step 2:
// -------
// Access left child:

//     root->left->val = 4


// Step 3:
// -------
// Access right child:

//     root->right->val = 6


// Step 4:
// -------
// Calculate:

//     4 + 6 = 10


// Step 5:
// -------
// Compare:

//     10 == 10

// Therefore:

//     return true


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// - Binary Tree
// - Direct Tree Property Check
// - Constant-Time Tree Traversal


// Key Observation:
// ----------------
// The tree has EXACTLY 3 nodes.

// Therefore its structure is fixed:

//         root
//        /    \
//     left    right

// No DFS, BFS, recursion, or queue is required.


// Common Mistakes:
// ----------------

// 1. Performing unnecessary traversal.

//    There are only 3 nodes and the required values are directly available.


// 2. Checking the wrong relationship.

//    Required:

//        root.val == left.val + right.val


// 3. Forgetting that the tree is guaranteed to have exactly 3 nodes.

//    Therefore root->left and root->right exist according to the problem
//    constraints.


// 4. Overcomplicating the solution with a vector or recursion.


// 5. In LeetCode, forgetting that TreeNode is already provided.

//    The LeetCode submission should contain only the Solution class.

//    The TreeNode definition and main() are only included here for
//    VS Code local testing.


// When to use this approach:
// --------------------------
// Use direct access when:

// - The tree structure is fixed.
// - The problem asks about a small number of specific nodes.
// - No traversal is required to find the answer.
// - The required nodes are directly accessible through pointers.


// Quick Memory Trick:
// -------------------

//     "Exactly 3 nodes -> root = left + right"

// So the solution is simply:

//     root->val == root->left->val + root->right->val


// Complexity:
// -----------

//     Time  = O(1)
//     Space = O(1)

// ================================================================================
// */

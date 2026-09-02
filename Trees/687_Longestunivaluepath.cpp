#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
    LeetCode 687 - Longest Univalue Path

    Optimal Solution:
    DFS + Postorder
    For every node, calculate the longest same-value chain going
    downward through its left/right child.

    A path can pass through the current node:
        left chain + right chain
*/
class Solution {
public:
    int ans = 0;

    int dfs(TreeNode* root) {
        if (!root)
            return 0;

        int left = dfs(root->left);
        int right = dfs(root->right);

        int leftPath = 0;
        int rightPath = 0;

        if (root->left && root->left->val == root->val)
            leftPath = left + 1;

        if (root->right && root->right->val == root->val)
            rightPath = right + 1;

        // Path passing through root.
        ans = max(ans, leftPath + rightPath);

        // Return only one direction to parent.
        return max(leftPath, rightPath);
    }

    int longestUnivaluePath(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};

int main() {
    Solution sol;

    /*
            5
           / \
          4   5
         / \   \
        1   1   5
                 \
                  5

        Longest univalue path:
        5 -> 5 -> 5 -> 5

        Number of edges = 3
    */

    TreeNode* root = new TreeNode(5);

    root->left = new TreeNode(4);
    root->right = new TreeNode(5);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(1);

    root->right->right = new TreeNode(5);
    root->right->right->right = new TreeNode(5);

    cout << sol.longestUnivaluePath(root) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 687 - COMPLETE NOTES
================================================================================

Problem Statement:
------------------
Given the root of a binary tree, return the length of the longest path
where every node in the path has the same value.

The path can start and end at any two nodes.

The path does NOT necessarily have to pass through the root.

Important:
----------
The answer is measured in EDGES, not number of nodes.

For example:

        5
        |
        5
        |
        5

There are 3 nodes but only 2 edges.

Therefore:

    answer = 2


--------------------------------------------------------------------------------
Example:
--------------------------------------------------------------------------------

Input:

            5
           / \
          4   5
         / \   \
        1   1   5
                 \
                  5

The longest path containing the value 5 is:

    5 -> 5 -> 5 -> 5

There are:

    3 edges

Therefore:

    Answer = 3


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
------
For every node, consider it as the starting point of a possible
univalue path.

From that node, perform DFS in all directions while only continuing
through nodes having the same value.

We can find the longest same-value path starting from each node.

However, this may repeatedly traverse the same parts of the tree and
can become O(N^2) in the worst case.

A simple brute-force version can use DFS from every node.


Pseudo Code:
------------

    answer = 0

    for every node:
        find longest same-value path starting from that node

    return answer


Complete Brute Force Code:
--------------------------

/*
class Solution {
public:
    int longestFrom(TreeNode* root, int value) {
        if (!root || root->val != value)
            return 0;

        return 1 + max(
            longestFrom(root->left, value),
            longestFrom(root->right, value)
        );
    }

    void traverse(TreeNode* root, int& answer) {
        if (!root)
            return;

        int left = longestFrom(root->left, root->val);
        int right = longestFrom(root->right, root->val);

        answer = max(
            answer,
            left + right
        );

        traverse(root->left, answer);
        traverse(root->right, answer);
    }

    int longestUnivaluePath(TreeNode* root) {
        int answer = 0;

        traverse(root, answer);

        return answer;
    }
};
*/


// Time Complexity:
// ----------------
// In the worst case, the same nodes can be visited repeatedly for
// different starting nodes.

// Worst case:

//     O(N^2)


// Space Complexity:
// -----------------
// Recursion depth:

//     O(H)

// where H is the height of the tree.

// Worst case for a skewed tree:

//     O(N)


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// For every node, we only need two pieces of information:

//     1. Longest same-value path going downward through the LEFT child.
//     2. Longest same-value path going downward through the RIGHT child.

// Suppose we are at:

//           root
//          /    \
//         L      R

// If:

//     L.val == root.val

// then the left contribution is:

//     leftDown + 1

// Similarly, if:

//     R.val == root.val

// then the right contribution is:

//     rightDown + 1


// The longest path passing THROUGH root is:

//     leftPath + rightPath


// But when returning a value to the parent, we can only return ONE side:

//     max(leftPath, rightPath)

// because a path returned to the parent cannot branch into both directions.


// Intuition:
// ----------
// Think of every node as the possible CENTER of the answer.

// For example:

//             5
//            / \
//           5   5
//          /     \
//         5       5

// At the root:

//     left chain  = 1 edge
//     right chain = 1 edge

// Therefore the path through root has:

//     1 + 1 = 2 edges

// But the recursive calls can also find longer paths deeper in the tree.

// The global variable `ans` stores the best path found anywhere.


// Why Postorder DFS?
// ------------------
// We need information from children before calculating the answer
// for the current node.

// Therefore:

//     left subtree
//     right subtree
//           ↓
//        current

// This is exactly POSTORDER traversal.


// Key Difference Between Returned Value and Answer:
// -------------------------------------------------

// Returned value:

//     Longest same-value chain going DOWN from current node
//     through only ONE child direction.

// Global answer:

//     Longest path passing THROUGH current node
//     and potentially using BOTH children.


// For example:

//           5
//          / \
//         5   5

// Each child returns:

//     0

// because it has no same-value child.

// At root:

//     leftPath  = 0 + 1 = 1
//     rightPath = 0 + 1 = 1

// Global answer:

//     1 + 1 = 2


// Pseudo Code:
// ------------

//     dfs(node):

//         if node == null:
//             return 0

//         left = dfs(node.left)
//         right = dfs(node.right)

//         leftPath = 0
//         rightPath = 0

//         if left child exists AND
//            left child value == node value:

//             leftPath = left + 1

//         if right child exists AND
//            right child value == node value:

//             rightPath = right + 1

//         ans = max(ans, leftPath + rightPath)

//         return max(leftPath, rightPath)


//     longestUnivaluePath(root):

//         ans = 0
//         dfs(root)

//         return ans


// Complete Optimal Code:
// ----------------------

/*
class Solution {
public:
    int ans = 0;

    int dfs(TreeNode* root) {
        if (!root)
            return 0;

        int left = dfs(root->left);
        int right = dfs(root->right);

        int leftPath = 0;
        int rightPath = 0;

        if (root->left &&
            root->left->val == root->val) {

            leftPath = left + 1;
        }

        if (root->right &&
            root->right->val == root->val) {

            rightPath = right + 1;
        }

        ans = max(
            ans,
            leftPath + rightPath
        );

        return max(
            leftPath,
            rightPath
        );
    }

    int longestUnivaluePath(TreeNode* root) {
        ans = 0;

        dfs(root);

        return ans;
    }
};
*/


// Time Complexity:
// ----------------
// Every node is visited exactly once.

// For each node, we perform O(1) work.

// Therefore:

//     O(N)


// Space Complexity:
// -----------------
// The recursion stack contains at most H nodes.

// Therefore:

//     O(H)

// Worst case for a skewed tree:

//     O(N)

// For a balanced tree:

//     O(log N)


// ================================================================================
// DRY RUN
// ================================================================================

// Example:

//             5
//            / \
//           4   5
//              / \
//             5   5
//                  \
//                   5


// Focus on the right subtree:

//             5
//            / \
//           5   5
//                \
//                 5


// Start from the bottom node:

//             5

// No children.

// Return:

//     0


// Its parent:

//             5
//              \
//               5

// Right child has same value.

// Therefore:

//     rightPath = 0 + 1
//               = 1

// Global answer:

//     max(0, 1)
//     = 1

// Return:

//     1


// Next parent:

//             5
//            / \
//           5   5
//                \
//                 5

// For the right child:

//     right = 1

// Since right child has the same value:

//     rightPath = 1 + 1
//               = 2

// Left child also has value 5.

// Its returned value is:

//     0

// Therefore:

//     leftPath = 0 + 1
//              = 1


// Path through current node:

//     leftPath + rightPath
//     = 1 + 2
//     = 3


// So:

//     ans = 3


// The path is:

//     5 -> 5 -> 5 -> 5

// Number of edges:

//     3


// Therefore:

//     Answer = 3


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// - Binary Tree
// - DFS
// - Postorder Traversal
// - Tree DP
// - Bottom-Up DP
// - Longest Path Through a Node


// Key Observation:
// ----------------
// For every node:

//     left contribution
//   + right contribution

// gives the longest same-value path passing through that node.

// But when returning to the parent:

//     return max(left, right)

// because the parent can extend only ONE branch.


// Very Important Formula:
// -----------------------

//     leftPath =
//         (left child has same value)
//         ? left + 1
//         : 0

//     rightPath =
//         (right child has same value)
//         ? right + 1
//         : 0

//     answer =
//         max(answer, leftPath + rightPath)

//     return =
//         max(leftPath, rightPath)


// Common Mistakes:
// ----------------

// 1. Returning leftPath + rightPath to the parent.

//    WRONG.

//    A path returned to the parent cannot contain both branches.

//    Correct:

//        return max(leftPath, rightPath)


// 2. Forgetting the +1.

//    If the child has the same value, the edge from:

//        current -> child

//    contributes one edge.

//    Therefore:

//        childPath + 1


// 3. Comparing grandchildren instead of direct children.

//    The returned value from DFS already contains the longest valid
//    downward chain.


// 4. Counting nodes instead of edges.

//    Example:

//        5 -> 5 -> 5

//    Nodes = 3

//    Edges = 2

//    Answer = 2


// 5. Assuming the longest path must start at the root.

//    It can exist anywhere in the tree.

//    That is why we maintain a global `ans`.


// 6. Forgetting to reset `ans`.

//    If the same Solution object is reused:

//        ans = 0

//    should be done inside longestUnivaluePath().


// 7. Using preorder instead of postorder.

//    We need children's answers before calculating the current node.

//    Therefore use:

//        DFS(left)
//        DFS(right)
//        process(current)


// When to use this approach:
// --------------------------
// Use this DFS + Tree DP pattern when:

// - The answer depends on information from child subtrees.
// - You need the longest/maximum path in a tree.
// - A path may pass through a node from both left and right sides.
// - Each subtree can return a useful "best downward chain" to its parent.

// Common related patterns:

//     Maximum Path Sum
//     Diameter of Binary Tree
//     Longest Univalue Path
//     Longest ZigZag Path
//     Height / Depth of Binary Tree


// Quick Memory Trick:
// -------------------

//     "Child gives ONE branch.
//      Current node combines TWO branches."

// So:

//     return max(leftPath, rightPath)

// but:

//     ans = max(ans, leftPath + rightPath)


// Complexity:
// -----------

//     Time  = O(N)
//     Space = O(H)


// LeetCode Submission Note:
// -------------------------
// On LeetCode, TreeNode is already defined.

// Therefore submit only the Solution class.

// The TreeNode definition and main() above are included only to make the
// code directly runnable in VS Code.


// ================================================================================
// */

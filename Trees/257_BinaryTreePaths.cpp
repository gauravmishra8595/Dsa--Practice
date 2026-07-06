#include <bits/stdc++.h>
using namespace std;

// Definition of TreeNode
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = right = nullptr;
    }
};

class Solution
{
public:
    void dfs(TreeNode *root, string path, vector<string> &ans)
    {
        if (root == nullptr)
            return;

        if (!path.empty())
        {
            path += "->";
        }
        path += to_string(root->val);

        // leaf node
        if (root->left == nullptr && root->right == nullptr)
        {
            ans.push_back(path);
            return;
        }

        dfs(root->left, path, ans);
        dfs(root->right, path, ans);
    }

    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> ans;
        dfs(root, "", ans);
        return ans;
    }
};

int main()
{
    /*
        Example Tree:
                1
               / \
              2   3
               \
                5
    */

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);

    Solution obj;
    vector<string> result = obj.binaryTreePaths(root);

    for (string s : result)
    {
        cout << s << endl;
    }

    return 0;
}

/*
====================== EXPLANATION ======================

BRUTE FORCE APPROACH:


class Solution {
public:
    void dfs(TreeNode* root, vector<int>& path, vector<string>& ans) {
        if (!root) return;

        path.push_back(root->val);

        if (!root->left && !root->right) {
            string s = "";
            for (int i = 0; i < path.size(); i++) {
                s += to_string(path[i]);
                if (i != path.size() - 1) s += "->";
            }
            ans.push_back(s);
        }

        dfs(root->left, path, ans);
        dfs(root->right, path, ans);

        path.pop_back(); // backtracking
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        vector<int> path;
        dfs(root, path, ans);
        return ans;
    }
};
- Generate ALL possible root-to-node paths using DFS.
- At every node, store path in a vector or list.
- When leaf is reached, convert full path into string.
- Problem: Repeated copying of vectors/strings increases overhead.

Time Complexity: O(N^2) in worst case (due to repeated string copying)
Space Complexity: O(H + N)


---------------------------------------------------------

OPTIMAL APPROACH (USED ABOVE):
class Solution {
public:
    void dfs(TreeNode* root, string path, vector<string>& ans) {
        if (!root) return;

        if (!path.empty()) path += "->";
        path += to_string(root->val);

        if (!root->left && !root->right) {
            ans.push_back(path);
            return;
        }

        dfs(root->left, path, ans);
        dfs(root->right, path, ans);
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ans;
        dfs(root, "", ans);
        return ans;
    }
};
- Use DFS (Depth First Search)
- Maintain a string "path" while traversing
- Append node value during traversal
- Only store result when we reach a LEAF node
- Avoid storing intermediate paths

Time Complexity: O(N)
Space Complexity: O(H) recursion stack

WHY IT IS OPTIMAL:
- Each node visited once
- No extra path storage at each step
- Efficient string building using backtracking style DFS

=========================================================
*/
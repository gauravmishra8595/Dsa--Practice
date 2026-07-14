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

class Codec
{
public:
    // Serialize (Level Order Traversal)
    string serialize(TreeNode *root)
    {
        if (!root)
            return "";

        string ans;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            if (node == nullptr)
            {
                ans += "#,";
                continue;
            }

            ans += to_string(node->val) + ",";
            q.push(node->left);
            q.push(node->right);
        }

        return ans;
    }

    // Deserialize
    TreeNode *deserialize(string data)
    {
        if (data.empty())
            return nullptr;

        stringstream ss(data);
        string str;

        getline(ss, str, ',');
        TreeNode *root = new TreeNode(stoi(str));

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            // Left Child
            getline(ss, str, ',');
            if (str != "#")
            {
                node->left = new TreeNode(stoi(str));
                q.push(node->left);
            }

            // Right Child
            getline(ss, str, ',');
            if (str != "#")
            {
                node->right = new TreeNode(stoi(str));
                q.push(node->right);
            }
        }

        return root;
    }
};

// Level Order Traversal (For Testing)
void levelOrder(TreeNode *root)
{
    if (!root)
        return;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();

        if (!node)
        {
            cout << "# ";
            continue;
        }

        cout << node->val << " ";

        q.push(node->left);
        q.push(node->right);
    }

    cout << endl;
}

int main()
{

    /*
              1
            /   \
           2     3
                / \
               4   5
    */

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec obj;

    string s = obj.serialize(root);

    cout << "Serialized Tree:\n";
    cout << s << endl
         << endl;

    TreeNode *newRoot = obj.deserialize(s);

    cout << "Level Order After Deserialization:\n";
    levelOrder(newRoot);

    return 0;
}

/*

=========================================================
297. Serialize and Deserialize Binary Tree
=========================================================

---------------------------------------------------------
Problem Statement
---------------------------------------------------------

Design an algorithm to serialize and deserialize a binary tree.

Serialize:
Convert the binary tree into a string.

Deserialize:
Convert the string back into the original binary tree.

There is no restriction on the serialization format as long
as deserialization reconstructs exactly the same tree.

---------------------------------------------------------
Example
---------------------------------------------------------

Input Tree

          1
        /   \
       2     3
            / \
           4   5

Serialized

1,2,3,#,#,4,5,#,#,#,#,

---------------------------------------------------------
Brute Force Approach
---------------------------------------------------------

Idea

Store complete preorder traversal along with inorder traversal.

Then reconstruct tree using both traversals.

Although correct, this is unnecessary because it requires
storing two traversals.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

Serialize

Store preorder
Store inorder

Deserialize

Build tree using preorder + inorder

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Codec {

serialize(root){

    preorder(root)

    inorder(root)

}

deserialize(){

    Build Tree from
    preorder and inorder

}

};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

Serialize : O(N)

Deserialize : O(N)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(N)

---------------------------------------------------------
Optimal Approach
---------------------------------------------------------

Observation

Level Order Traversal naturally preserves tree structure.

Store NULL nodes as '#'.

While reconstructing,

Read nodes level by level.

---------------------------------------------------------
Intuition
---------------------------------------------------------

Every node has exactly two children.

During serialization,

Store

value

or

#

for NULL.

During deserialization,

Read nodes in same order and reconnect children.

Queue guarantees correct parent-child order.

---------------------------------------------------------
Pseudo Code
---------------------------------------------------------

Serialize

queue ← root

while queue not empty

    node = pop()

    if node==NULL

        add "#"

    else

        add value

        push left

        push right

Deserialize

Read root

queue ← root

while queue not empty

    parent = pop()

    Read left

    if not #

        create left

    Read right

    if not #

        create right

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Codec{

public:

string serialize(TreeNode* root){

    if(root==NULL)
        return "";

    queue<TreeNode*> q;

    q.push(root);

    string ans="";

    while(!q.empty()){

        TreeNode* node=q.front();
        q.pop();

        if(node==NULL){

            ans+="#,";

            continue;
        }

        ans+=to_string(node->val)+",";

        q.push(node->left);
        q.push(node->right);
    }

    return ans;
}

TreeNode* deserialize(string data){

    if(data.empty())
        return NULL;

    stringstream ss(data);

    string cur;

    getline(ss,cur,',');

    TreeNode* root=new TreeNode(stoi(cur));

    queue<TreeNode*> q;

    q.push(root);

    while(!q.empty()){

        TreeNode* node=q.front();
        q.pop();

        getline(ss,cur,',');

        if(cur!="#"){

            node->left=new TreeNode(stoi(cur));

            q.push(node->left);
        }

        getline(ss,cur,',');

        if(cur!="#"){

            node->right=new TreeNode(stoi(cur));

            q.push(node->right);
        }
    }

    return root;
}

};

---------------------------------------------------------
Time Complexity
---------------------------------------------------------

Serialize : O(N)

Deserialize : O(N)

---------------------------------------------------------
Space Complexity
---------------------------------------------------------

O(N)

Queue + Serialized String

---------------------------------------------------------
Dry Run
---------------------------------------------------------

Tree

        1
      /   \
     2     3
          / \
         4   5

Queue

1

Output

1,

Queue

2 3

Output

1,2,3,

Queue

# # 4 5

Output

1,2,3,#,#,4,5,

Continue...

Final String

1,2,3,#,#,4,5,#,#,#,#,

Deserialize

Read

1

Create root

Read

2

Attach left

Read

3

Attach right

Read

#

Left=NULL

Read

#

Right=NULL

Continue similarly

Original Tree reconstructed.

---------------------------------------------------------
Interview Notes
---------------------------------------------------------

Pattern

✔ Binary Tree

✔ BFS

✔ Queue

✔ Serialization

✔ Tree Construction

---------------------------------------------------------

Key Observation

NULL nodes must also be stored.

Otherwise different trees can produce identical traversals.

---------------------------------------------------------

Common Mistakes

1. Forgetting NULL markers.

2. Reading only one child while deserializing.

3. Assigning left child to right.

4. Forgetting queue order.

5. Missing comma separator.

---------------------------------------------------------

When to use this approach

Whenever

• Need to save binary tree.

• Send tree over network.

• Store tree in file/database.

• Clone or reconstruct exact tree.

Level Order + NULL markers is one of the simplest and most
commonly accepted serialization techniques.

=========================================================

*/
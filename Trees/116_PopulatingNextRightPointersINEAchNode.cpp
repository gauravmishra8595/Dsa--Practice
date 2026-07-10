#include <iostream>
#include <queue>
using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node()
    {
        val = 0;
        left = right = next = nullptr;
    }

    Node(int _val)
    {
        val = _val;
        left = right = next = nullptr;
    }
};

class Solution
{
public:
    Node *connect(Node *root)
    {

        if (root == NULL || root->left == NULL)
            return root;

        queue<Node *> q;

        q.push(root);
        q.push(NULL);

        Node *prev = NULL;

        while (!q.empty())
        {

            Node *curr = q.front();
            q.pop();

            if (curr == NULL)
            {

                if (q.empty())
                    break;

                q.push(NULL);
                prev = NULL; // Reset previous node for next level
            }
            else
            {

                if (prev != NULL)
                    prev->next = curr;

                prev = curr;

                if (curr->left)
                    q.push(curr->left);

                if (curr->right)
                    q.push(curr->right);
            }
        }

        return root;
    }
};

// Print level order using next pointers
void printLevels(Node *root)
{

    while (root != NULL)
    {

        Node *curr = root;

        while (curr != NULL)
        {
            cout << curr->val << " ";
            curr = curr->next;
        }

        cout << "#\n";
        root = root->left;
    }
}

int main()
{

    /*
              1
            /   \
           2     3
          / \   / \
         4  5  6   7
    */

    Node *root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);

    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution obj;

    root = obj.connect(root);

    cout << "Level Order using Next Pointer:\n";
    printLevels(root);

    return 0;
}

/*

==========================================================
LeetCode 116. Populating Next Right Pointers in Each Node
==========================================================

Problem
-------
Given a Perfect Binary Tree, connect each node to its next
right node. If there is no next right node, set next = NULL.

Example

Before

            1
          /   \
         2     3
        / \   / \
       4  5  6  7

After

1 -> NULL

2 -> 3 -> NULL

4 -> 5 -> 6 -> 7 -> NULL


==========================================================
Brute Force Approach (Level Order Traversal)
==========================================================

Idea
----
Traverse the tree level by level using a queue.

For every level:

Store all nodes.

Connect each node with the next node.

Code

queue<Node*> q;

q.push(root);

while(!q.empty()){

    int size=q.size();

    Node* prev=NULL;

    while(size--){

        Node* curr=q.front();
        q.pop();

        if(prev!=NULL)
            prev->next=curr;

        prev=curr;

        if(curr->left)
            q.push(curr->left);

        if(curr->right)
            q.push(curr->right);
    }

}

Time Complexity

O(n)

Space Complexity

O(n)


==========================================================
Optimal Approach (Queue with NULL Marker)
==========================================================

Idea
----

Use level order traversal.

Insert NULL after every level.

Maintain a previous pointer.

Whenever previous exists

previous->next=current

When NULL comes

Move to next level.

Reset previous=NULL.


Algorithm
---------

1. Push root.

2. Push NULL.

3. Pop nodes one by one.

4. If current is NULL

      push another NULL if queue isn't empty.

      reset previous.

5. Else

      previous->next=current.

      Push left child.

      Push right child.

6. Continue until queue becomes empty.


Dry Run
-------

Queue

1 NULL

Pop 1

Push 2 3

Queue

NULL 2 3

Pop NULL

Push NULL

Queue

2 3 NULL

Pop 2

Pop 3

Connect

2 -> 3

Queue

NULL 4 5 6 7

Pop NULL

Push NULL

Queue

4 5 6 7 NULL

Connections

4 -> 5

5 -> 6

6 -> 7

7 -> NULL


==========================================================
Complexity
==========================================================

Time

O(n)

Each node is visited once.


Space

O(n)

Queue stores one level.


==========================================================
Even Better Solution (Constant Space)
==========================================================

Since the tree is Perfect,

root->left->next = root->right

root->right->next = root->next->left

Traverse one level using already established next pointers.

Time

O(n)

Space

O(1)

This is the most optimal solution expected for LeetCode 116.

==========================================================

*/
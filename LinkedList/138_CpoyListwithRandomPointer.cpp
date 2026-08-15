#include <bits/stdc++.h>
using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

// Optimal Solution
class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;

        // Step 1: Insert copied nodes between original nodes.
        Node *curr = head;

        while (curr != nullptr)
        {
            Node *copy = new Node(curr->val);

            copy->next = curr->next;
            curr->next = copy;

            curr = copy->next;
        }

        // Step 2: Set random pointers of copied nodes.
        curr = head;

        while (curr != nullptr)
        {
            if (curr->random != nullptr)
            {
                curr->next->random = curr->random->next;
            }

            curr = curr->next->next;
        }

        // Step 3: Separate original and copied lists.
        Node *dummy = new Node(0);
        Node *copyCurr = dummy;

        curr = head;

        while (curr != nullptr)
        {
            Node *copy = curr->next;

            curr->next = copy->next;

            copyCurr->next = copy;
            copyCurr = copy;

            curr = curr->next;
        }

        return dummy->next;
    }
};

int main()
{
    // Example:
    // nodes = [[7,null],[13,0],[11,4],[10,2],[1,0]]

    Node *head = new Node(7);
    head->next = new Node(13);
    head->next->next = new Node(11);
    head->next->next->next = new Node(10);
    head->next->next->next->next = new Node(1);

    head->random = nullptr;
    head->next->random = head;
    head->next->next->random = head->next->next->next->next;
    head->next->next->next->random = head->next->next;
    head->next->next->next->next->random = head;

    Solution obj;
    Node *ans = obj.copyRandomList(head);

    Node *curr = ans;

    while (curr != nullptr)
    {
        cout << "[";
        cout << curr->val << ", ";

        if (curr->random != nullptr)
            cout << curr->random->val;
        else
            cout << "null";

        cout << "] ";

        curr = curr->next;
    }

    cout << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 138 - CP NOTEBOOK
                    Copy List with Random Pointer
================================================================================

Problem Statement:
------------------
A linked list is given where each node contains:

    1. val
    2. next
    3. random

The random pointer can point to any node in the list or NULL.

Create a deep copy of the entire linked list.

The copied list must contain completely new nodes.

The next and random pointers of the copied nodes must point only to nodes
inside the copied list.

Example:
--------
Input:

    [[7,null],
     [13,0],
     [11,4],
     [10,2],
     [1,0]]

Output:

    [[7,null],
     [13,0],
     [11,4],
     [10,2],
     [1,0]]

The values and random-pointer relationships are the same, but all nodes
in the output are newly created nodes.


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Create a copy of every node.

The difficult part is assigning the random pointers.

For every original node, find the position of its random pointer.

Then find the corresponding copied node at the same position.

We can use two vectors:

    original
    copied

For each node:

1. Store all original nodes.
2. Create corresponding copied nodes.
3. Connect next pointers.
4. For every random pointer, find its index in the original vector.
5. Use that index to connect the copied random pointer.


Pseudo Code:
------------

function copyRandomList(head):

    original = empty vector
    copied = empty vector

    curr = head

    while curr != NULL:

        add curr to original
        create copied node
        add copied node to copied

        curr = curr->next

    Connect copied next pointers.

    For every original node:

        Find index of original[i]->random.

        If random is not NULL:

            copied[i]->random = copied[index]

    return copied[0]


Complete Brute Force Code:
---------------------------

Node *bruteForce(Node *head)
{
    if (head == nullptr)
        return nullptr;

    vector<Node *> original;
    vector<Node *> copied;

    Node *curr = head;

    while (curr != nullptr)
    {
        original.push_back(curr);
        copied.push_back(new Node(curr->val));

        curr = curr->next;
    }

    int n = original.size();

    for (int i = 0; i < n - 1; i++)
    {
        copied[i]->next = copied[i + 1];
    }

    for (int i = 0; i < n; i++)
    {
        if (original[i]->random == nullptr)
        {
            copied[i]->random = nullptr;
            continue;
        }

        int randomIndex = -1;

        for (int j = 0; j < n; j++)
        {
            if (original[j] == original[i]->random)
            {
                randomIndex = j;
                break;
            }
        }

        copied[i]->random = copied[randomIndex];
    }

    return copied[0];
}


Time Complexity:
----------------
O(n^2)

For every random pointer, we may scan all n nodes.


Space Complexity:
-----------------
O(n)

We store the original and copied node pointers.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------
The main difficulty is:

    How do we map each original node to its copied node?

Normally, we use a hash map:

    original node -> copied node

That gives O(n) time and O(n) extra space.

But we can do even better in terms of auxiliary space.

We can insert every copied node directly after its original node.

Original:

    A -> B -> C -> NULL


After inserting copies:

    A -> A' -> B -> B' -> C -> C' -> NULL


Now, for every original node:

    original->next

is its copied node.


Intuition:
----------
Suppose:

    A.random = C

After inserting copies:

    A -> A' -> B -> B' -> C -> C'

Since C' is immediately after C:

    C' = C->next

Therefore:

    A'.random = A.random->next

This is the key observation.


The solution has three steps:


Step 1:
-------
Insert copied nodes after their original nodes.

Before:

    A -> B -> C

After:

    A -> A' -> B -> B' -> C -> C'


Step 2:
-------
Set random pointers.

For every original node:

    if curr->random != NULL:

        curr->next->random = curr->random->next

Why?

    curr->next

is the copied current node.

And:

    curr->random->next

is the copied random node.


Step 3:
-------
Separate the original and copied lists.

Before separation:

    A -> A' -> B -> B' -> C -> C'

After:

Original:

    A -> B -> C


Copied:

    A' -> B' -> C'


Pseudo Code:
------------

function copyRandomList(head):

    if head == NULL:
        return NULL


    Step 1:

    curr = head

    while curr != NULL:

        copy = new Node(curr->val)

        copy->next = curr->next
        curr->next = copy

        curr = copy->next


    Step 2:

    curr = head

    while curr != NULL:

        if curr->random != NULL:

            curr->next->random = curr->random->next

        curr = curr->next->next


    Step 3:

    curr = head
    copyHead = NULL
    copyCurr = NULL

    while curr != NULL:

        copy = curr->next

        curr->next = copy->next

        connect copy into copied list

        curr = curr->next

    return copyHead


Complete Optimal Code:
-----------------------

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;

        Node *curr = head;

        while (curr != nullptr)
        {
            Node *copy = new Node(curr->val);

            copy->next = curr->next;
            curr->next = copy;

            curr = copy->next;
        }

        curr = head;

        while (curr != nullptr)
        {
            if (curr->random != nullptr)
            {
                curr->next->random = curr->random->next;
            }

            curr = curr->next->next;
        }

        Node *dummy = new Node(0);
        Node *copyCurr = dummy;

        curr = head;

        while (curr != nullptr)
        {
            Node *copy = curr->next;

            curr->next = copy->next;

            copyCurr->next = copy;
            copyCurr = copy;

            curr = curr->next;
        }

        return dummy->next;
    }
};


Time Complexity:
----------------
O(n)

We traverse the list three times.

    Step 1 -> O(n)
    Step 2 -> O(n)
    Step 3 -> O(n)

Therefore:

    O(3n) = O(n)


Space Complexity:
-----------------
O(1) auxiliary space.

We do not use a hash map or vector.

The copied nodes themselves require O(n) memory, but that is required
for the output and is not counted as auxiliary space.


===============================================================================
Dry Run With Example
===============================================================================

Consider:

    A -> B -> C -> NULL

Suppose:

    A.random = C
    B.random = A
    C.random = B


Step 1:
-------
Insert copied nodes.

Before:

    A -> B -> C


After:

    A -> A' -> B -> B' -> C -> C'


Now:

    A'.next = B
    B'.next = C


Step 2:
-------
Set random pointers.

For A:

    A.random = C

Therefore:

    A'.random = A.random->next
              = C->next
              = C'


For B:

    B.random = A

Therefore:

    B'.random = A->next
              = A'


For C:

    C.random = B

Therefore:

    C'.random = B->next
              = B'


So:

    A' -> random C'
    B' -> random A'
    C' -> random B'


Step 3:
-------
Separate the two lists.

Original:

    A -> B -> C -> NULL


Copied:

    A' -> B' -> C' -> NULL


The copied list is returned.


===============================================================================
Why Does random->next Work?
===============================================================================

This is the most important trick in the problem.

After Step 1:

    Original node:
        A

    Copy:
        A'

and:

    A->next = A'


Similarly, if:

    A.random = C

then:

    C->next = C'


Therefore:

    A'.random
    = A.random->next
    = C->next
    = C'


So we can connect random pointers without a hash map.


===============================================================================
Edge Cases
===============================================================================

1. Empty list:

       NULL

   Return NULL.


2. Single node with random = NULL:

       [1, null]

   Copy contains one new node.


3. Single node pointing to itself:

       [1, 0]

   During Step 2:

       copy->random = original->random->next

   Since original->random is itself:

       copy->random = original->next

   which is the copied node itself.

   Correct.


4. Random pointer points to another node.

   The copied random pointer is obtained using:

       curr->random->next


5. All random pointers are NULL.

   No random pointers need to be assigned.


===============================================================================
Interview Notes
===============================================================================

Pattern:
--------
Linked List + Pointer Manipulation


Key Observation:
----------------
Insert every copied node immediately after its original node.

For example:

    A -> B -> C

becomes:

    A -> A' -> B -> B' -> C -> C'


Then:

    original->next = copy

and:

    original->random->next = copied random


This eliminates the need for a hash map.


Common Mistakes:
----------------

1. Forgetting to save the original next node.

   Correct:

       copy->next = curr->next;
       curr->next = copy;
       curr = copy->next;


2. Incorrect random pointer assignment.

   Correct:

       curr->next->random = curr->random->next;


3. Accessing random->next when random is NULL.

   Always check:

       if (curr->random != nullptr)


4. Forgetting to restore the original list.

   The problem requires a deep copy, and the original list should remain
   structurally unchanged.

   Therefore, after copying, separate the two lists.


5. Returning head instead of the copied head.

   The answer must contain completely new nodes.


6. Using the original random pointers in the copied list.

   This would not be a deep copy.

   Copied random pointers must point to copied nodes.


When To Use This Approach:
--------------------------

Use this approach when:

- A linked list contains arbitrary/random pointers.
- You need a deep copy.
- You want O(n) time.
- O(1) auxiliary space is expected.
- You can temporarily modify the original linked list.


Core Mental Template:
---------------------

Step 1:

    Insert copy after every original node.

        A -> A' -> B -> B' -> C -> C'


Step 2:

    Set random pointers.

        copy->random = original->random->next


Step 3:

    Separate original and copied lists.


Final Complexity:
-----------------

Time  : O(n)
Space : O(1) auxiliary space

================================================================================
*/
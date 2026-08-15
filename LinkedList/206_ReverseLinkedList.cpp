#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Optimal Solution
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr != nullptr)
        {
            ListNode *nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }
};

int main()
{
    // Example: [1, 2, 3, 4, 5]
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution obj;
    ListNode *ans = obj.reverseList(head);

    while (ans != nullptr)
    {
        cout << ans->val << " ";
        ans = ans->next;
    }

    cout << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 206 - CP NOTEBOOK
                         Reverse Linked List
================================================================================

Problem Statement:
------------------
Given the head of a singly linked list, reverse the list and return the
reversed linked list.

Example:

Input:

    [1, 2, 3, 4, 5]

Output:

    [5, 4, 3, 2, 1]


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Store all node values in a vector.

Then traverse the linked list again and replace the node values in reverse
order.

This produces the correct result, but it does not actually reverse the
links using the optimal pointer-based technique.

It also requires O(n) extra space.


Pseudo Code:
------------

function reverseList(head):

    values = empty vector
    curr = head

    while curr != NULL:

        add curr->val to values
        curr = curr->next

    curr = head
    i = n - 1

    while curr != NULL:

        curr->val = values[i]
        i--
        curr = curr->next

    return head


Complete Brute Force Code:
---------------------------

ListNode *bruteForce(ListNode *head)
{
    vector<int> values;

    ListNode *curr = head;

    while (curr != nullptr)
    {
        values.push_back(curr->val);
        curr = curr->next;
    }

    curr = head;

    for (int i = values.size() - 1; i >= 0; i--)
    {
        curr->val = values[i];
        curr = curr->next;
    }

    return head;
}


Time Complexity:
----------------
O(n)


Space Complexity:
-----------------
O(n)

The vector stores all node values.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------
A singly linked list can be reversed by changing the direction of every
next pointer.

For example:

    1 -> 2 -> 3 -> NULL

After reversal:

    1 <- 2 <- 3

which becomes:

    3 -> 2 -> 1 -> NULL


Intuition:
----------
We need three pointers:

    prev
        Stores the previous node.

    curr
        Stores the current node.

    nextNode
        Stores the next node before changing curr->next.

Initially:

    prev = NULL
    curr = head


For:

    1 -> 2 -> 3 -> NULL

First iteration:

    nextNode = 2

Save the next node before changing the link.

Then:

    curr->next = prev

So:

    1 -> NULL

Move pointers:

    prev = 1
    curr = 2


Second iteration:

    nextNode = 3

    2->next = 1

Now:

    2 -> 1 -> NULL

Move:

    prev = 2
    curr = 3


Third iteration:

    nextNode = NULL

    3->next = 2

Now:

    3 -> 2 -> 1 -> NULL

Move:

    prev = 3
    curr = NULL

The loop ends.

The new head is stored in prev.


Pseudo Code:
------------

function reverseList(head):

    prev = NULL
    curr = head

    while curr != NULL:

        nextNode = curr->next
        curr->next = prev

        prev = curr
        curr = nextNode

    return prev


Complete Optimal Code:
-----------------------

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr != nullptr)
        {
            ListNode *nextNode = curr->next;

            curr->next = prev;

            prev = curr;
            curr = nextNode;
        }

        return prev;
    }
};


Time Complexity:
----------------
O(n)

Every node is processed exactly once.


Space Complexity:
-----------------
O(1)

Only three pointers are used.


===============================================================================
Dry Run With Example
===============================================================================

Example:

    1 -> 2 -> 3 -> 4 -> 5 -> NULL


Initial:

    prev = NULL
    curr = 1


Iteration 1:
------------

    nextNode = 2

    1->next = NULL

Now:

    1 -> NULL

Move:

    prev = 1
    curr = 2


Iteration 2:
------------

    nextNode = 3

    2->next = 1

Now:

    2 -> 1 -> NULL

Move:

    prev = 2
    curr = 3


Iteration 3:
------------

    nextNode = 4

    3->next = 2

Now:

    3 -> 2 -> 1 -> NULL

Move:

    prev = 3
    curr = 4


Iteration 4:
------------

    nextNode = 5

    4->next = 3

Now:

    4 -> 3 -> 2 -> 1 -> NULL

Move:

    prev = 4
    curr = 5


Iteration 5:
------------

    nextNode = NULL

    5->next = 4

Now:

    5 -> 4 -> 3 -> 2 -> 1 -> NULL

Move:

    prev = 5
    curr = NULL


Loop ends.

Return:

    prev = 5

Final Answer:

    [5, 4, 3, 2, 1]


===============================================================================
Edge Cases
===============================================================================

1. Empty list:

       []

   head = NULL

   Return NULL.


2. Single node:

       [1]

   Nothing needs to be changed.

   Return [1].


3. Two nodes:

       [1, 2]

   Result:

       [2, 1]


4. Already reversed:

       [5, 4, 3, 2, 1]

   Result:

       [1, 2, 3, 4, 5]


===============================================================================
Interview Notes
===============================================================================

Pattern:
--------
Linked List + Pointer Manipulation


Key Observation:
----------------
To reverse a linked list, reverse the direction of every next pointer.

The most important line is:

    curr->next = prev;


Why Do We Need nextNode?
------------------------
Before changing:

    curr->next

we must save the original next node.

Otherwise, we lose access to the remaining linked list.

Therefore:

    nextNode = curr->next;

must happen before:

    curr->next = prev;


Common Mistakes:
----------------

1. Forgetting to save the next node.

   Wrong:

       curr->next = prev;
       curr = curr->next;

   This loses the original next node.


2. Returning head instead of prev.

   After reversal:

       head

   still points to the old first node, which is now the last node.

   The new head is:

       prev


3. Using extra memory unnecessarily.

   A vector or stack is not required.


4. Incorrect pointer update order.

   Correct order:

       nextNode = curr->next;
       curr->next = prev;
       prev = curr;
       curr = nextNode;


5. Forgetting the empty-list case.

   The loop naturally handles it:

       curr = NULL

   so prev remains NULL.


When To Use This Approach:
--------------------------

Use this approach when:

- You need to reverse a singly linked list.
- You need O(1) extra space.
- The problem involves changing linked-list directions.
- You need in-place pointer manipulation.


Core Mental Template:
---------------------

prev = NULL
curr = head

while curr != NULL:

    nextNode = curr->next
    curr->next = prev

    prev = curr
    curr = nextNode

return prev


Final Complexity:
-----------------

Time  : O(n)
Space : O(1)

================================================================================
*/
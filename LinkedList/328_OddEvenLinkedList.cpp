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
    ListNode *oddEvenList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *evenHead = even;

        while (even != nullptr && even->next != nullptr)
        {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }

        odd->next = evenHead;

        return head;
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
    ListNode *ans = obj.oddEvenList(head);

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
                    LEETCODE 328 - CP NOTEBOOK
                         Odd Even Linked List
================================================================================

Problem Statement:
------------------
Given the head of a singly linked list, group all nodes with odd indices
together followed by the nodes with even indices.

The first node has index 1.

The relative order inside the odd-indexed nodes and even-indexed nodes
must be preserved.

The solution must run in O(n) time and O(1) extra space.


Example:
--------
Input:

[1, 2, 3, 4, 5]

Output:

[1, 3, 5, 2, 4]

Explanation:

Odd-indexed nodes:

    1 -> 3 -> 5

Even-indexed nodes:

    2 -> 4

Combine them:

    1 -> 3 -> 5 -> 2 -> 4


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Traverse the linked list and store odd-indexed and even-indexed nodes
separately.

We can use two vectors:

    odd
    even

After traversal, connect all odd nodes followed by all even nodes.

This approach works but uses O(n) extra space.

Since the problem asks for O(1) extra space, this is not optimal.


Pseudo Code:
------------

function oddEvenList(head):

    odd = empty list
    even = empty list

    curr = head
    index = 1

    while curr != NULL:

        if index is odd:
            add curr->val to odd
        else:
            add curr->val to even

        curr = curr->next
        index++

    create result using:

        all values from odd
        followed by all values from even

    return result


Complete Brute Force Code:
---------------------------

ListNode *bruteForce(ListNode *head)
{
    if (head == nullptr)
        return head;

    vector<int> odd;
    vector<int> even;

    ListNode *curr = head;
    int index = 1;

    while (curr != nullptr)
    {
        if (index % 2 == 1)
            odd.push_back(curr->val);
        else
            even.push_back(curr->val);

        curr = curr->next;
        index++;
    }

    curr = head;

    for (int x : odd)
    {
        curr->val = x;
        curr = curr->next;
    }

    for (int x : even)
    {
        curr->val = x;
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

We store all node values in vectors.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------
The nodes are already connected in a linked list.

We do not need extra arrays.

Maintain two separate chains:

    Odd-indexed nodes
    Even-indexed nodes

For example:

    1 -> 2 -> 3 -> 4 -> 5

Initially:

    odd  = 1
    even = 2

Keep the head of the even list because we need to attach it after the
odd list at the end.

Then rearrange the pointers:

    odd->next = even->next

This connects the current odd node to the next odd node.

Then:

    even->next = odd->next

This connects the current even node to the next even node.


Intuition:
----------
Use three pointers:

    odd
        Current odd-indexed node.

    even
        Current even-indexed node.

    evenHead
        Head of the even-indexed list.

For:

    1 -> 2 -> 3 -> 4 -> 5

Start:

    odd      = 1
    even     = 2
    evenHead = 2


First iteration:

    odd->next = even->next

    1 -> 3

Then:

    odd = 3

Connect even nodes:

    even->next = odd->next

    2 -> 4

Then:

    even = 4


Next iteration:

    3 -> 5

and:

    4 -> NULL


Now we have:

    Odd list:

    1 -> 3 -> 5


    Even list:

    2 -> 4


Finally connect:

    5 -> 2

Result:

    1 -> 3 -> 5 -> 2 -> 4


Pseudo Code:
------------

function oddEvenList(head):

    if head == NULL or head->next == NULL:
        return head

    odd = head
    even = head->next
    evenHead = even

    while even != NULL and even->next != NULL:

        odd->next = even->next
        odd = odd->next

        even->next = odd->next
        even = even->next

    odd->next = evenHead

    return head


Complete Optimal Code:
-----------------------

class Solution
{
public:
    ListNode *oddEvenList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode *odd = head;
        ListNode *even = head->next;
        ListNode *evenHead = even;

        while (even != nullptr && even->next != nullptr)
        {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }

        odd->next = evenHead;

        return head;
    }
};


Time Complexity:
----------------
O(n)

Each node is processed a constant number of times.


Space Complexity:
-----------------
O(1)

Only three pointers are used.


===============================================================================
Dry Run With Example
===============================================================================

Example:

    1 -> 2 -> 3 -> 4 -> 5 -> NULL


Initial State:
--------------

    odd      = 1
    even     = 2
    evenHead = 2


Iteration 1:
------------

Connect current odd node to next odd node:

    odd->next = even->next

Therefore:

    1 -> 3

Move odd:

    odd = 3


Connect current even node to next even node:

    even->next = odd->next

Therefore:

    2 -> 4

Move even:

    even = 4


Current structure:

    Odd:

    1 -> 3 -> 4 -> 5

    Even:

    2 -> 4 -> 5


Iteration 2:
------------

Current:

    odd = 3
    even = 4


Connect next odd:

    odd->next = even->next

Therefore:

    3 -> 5

Move:

    odd = 5


Connect next even:

    even->next = odd->next

Since odd is 5 and:

    5->next = NULL

we get:

    4 -> NULL

Move:

    even = NULL


Now:

    Odd list:

    1 -> 3 -> 5


    Even list:

    2 -> 4


Final Connection:
-----------------

    odd->next = evenHead

Therefore:

    5 -> 2


Final list:

    1 -> 3 -> 5 -> 2 -> 4 -> NULL


Answer:

    [1, 3, 5, 2, 4]


===============================================================================
Another Example
===============================================================================

Input:

    [2, 1, 3, 5, 6, 4, 7]

Odd-indexed nodes:

    2 -> 3 -> 6 -> 7

Even-indexed nodes:

    1 -> 5 -> 4

Final:

    2 -> 3 -> 6 -> 7 -> 1 -> 5 -> 4


===============================================================================
Edge Cases
===============================================================================

1. Empty list:

       []

   Return NULL.


2. One node:

       [1]

   Already valid.

   Return [1].


3. Two nodes:

       [1, 2]

   Odd list:

       1

   Even list:

       2

   Result:

       [1, 2]


4. Three nodes:

       [1, 2, 3]

   Odd nodes:

       1 -> 3

   Even nodes:

       2

   Result:

       [1, 3, 2]


===============================================================================
Interview Notes
===============================================================================

Pattern:
--------
Linked List + Pointer Manipulation


Key Observation:
----------------
Do not create a new linked list.

Split the original list into two chains:

    Odd positions
    Even positions

Then connect:

    Odd list -> Even list


Important Pointers:
-------------------

1. odd

   Points to the current odd-indexed node.


2. even

   Points to the current even-indexed node.


3. evenHead

   Stores the first even-indexed node.

   We need it later to connect:

       lastOdd -> firstEven


Common Mistakes:
----------------

1. Forgetting to store evenHead.

   If we lose the original even head, we cannot connect the odd list
   to the even list at the end.


2. Confusing node values with node positions.

   Odd/even refers to the INDEX of the node:

       Position 1 -> odd
       Position 2 -> even
       Position 3 -> odd
       Position 4 -> even


3. Using value parity instead of index parity.

   Example:

       [2, 3, 4, 5]

   All nodes are grouped according to positions, not whether their values
   are odd or even.

   Result:

       [2, 4, 3, 5]


4. Breaking the list incorrectly.

   Pointer updates must happen in this order:

       odd->next = even->next
       odd = odd->next

       even->next = odd->next
       even = even->next


5. Forgetting the final connection:

       odd->next = evenHead


6. Creating extra arrays or lists.

   The optimal solution requires O(1) extra space.


When To Use This Approach:
--------------------------

Use this approach when:

- A linked list needs to be rearranged.
- Relative order must be preserved.
- Nodes can be divided into two groups.
- In-place pointer manipulation is required.
- O(1) extra space is expected.


Core Mental Template:
---------------------

odd = head
even = head->next
evenHead = even

while even != NULL and even->next != NULL:

    odd->next = even->next
    odd = odd->next

    even->next = odd->next
    even = even->next

odd->next = evenHead

return head


Final Complexity:
-----------------

Time  : O(n)
Space : O(1)

================================================================================
*/
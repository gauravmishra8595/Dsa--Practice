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
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *curr = head;

        while (curr != nullptr && curr->next != nullptr)
        {
            if (curr->val == curr->next->val)
            {
                curr->next = curr->next->next;
            }
            else
            {
                curr = curr->next;
            }
        }

        return head;
    }
};

int main()
{
    // Example: [1, 1, 2, 3, 3]
    ListNode *head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(3);

    Solution obj;
    ListNode *ans = obj.deleteDuplicates(head);

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
                    LEETCODE 83 - CP NOTEBOOK
                  Remove Duplicates from Sorted List
================================================================================

Problem Statement:
------------------
Given the head of a sorted singly linked list, delete all duplicates such
that each element appears only once.

Return the linked list after removing duplicates.

The linked list is sorted in non-decreasing order.


Example:
--------
Input:

[1, 1, 2, 3, 3]

Output:

[1, 2, 3]

Explanation:

The duplicate 1 and duplicate 3 are removed.


===============================================================================
Brute Force Approach
===============================================================================

Idea:
-----
Traverse the linked list and store every value in a set.

Whenever a value appears for the first time, keep it.

If the value already exists in the set, remove the duplicate node.

However, because the linked list is already sorted, using a set is unnecessary.

The same duplicate values are always adjacent.

This approach is mainly useful for understanding the general duplicate-removal
technique.


Pseudo Code:
------------

function deleteDuplicates(head):

    seen = empty set
    curr = head
    prev = NULL

    while curr != NULL:

        if curr->val exists in seen:

            prev->next = curr->next

        else:

            insert curr->val into seen
            prev = curr

        curr = curr->next

    return head


Complete Brute Force Code:
---------------------------

ListNode *bruteForce(ListNode *head)
{
    unordered_set<int> seen;

    ListNode *curr = head;
    ListNode *prev = nullptr;

    while (curr != nullptr)
    {
        if (seen.count(curr->val))
        {
            prev->next = curr->next;
        }
        else
        {
            seen.insert(curr->val);
            prev = curr;
        }

        curr = curr->next;
    }

    return head;
}


Time Complexity:
----------------
O(n) average


Space Complexity:
-----------------
O(n)

The set can contain up to n different values.


===============================================================================
Optimal Approach
===============================================================================

Observation:
------------
The linked list is sorted.

Therefore, all duplicate values are adjacent.

For example:

    1 -> 1 -> 1 -> 2 -> 3 -> 3

When we are at the first 1, the next node also contains 1.

So we can simply skip the next node.

There is no need for a set.


Intuition:
----------
Maintain a pointer curr.

At every node:

1. Compare curr->val with curr->next->val.
2. If both values are equal:
       Skip curr->next.
3. Otherwise:
       Move curr forward.

To delete a duplicate node:

    curr->next = curr->next->next

We do NOT move curr when deleting a duplicate because there may be
more duplicates immediately after it.

Example:

    1 -> 1 -> 1 -> 2

First:

    curr = first 1

Delete second 1:

    1 -> 1 -> 2

Keep curr at the same position.

Again delete duplicate:

    1 -> 2

Now the next value is different, so move curr forward.


Pseudo Code:
------------

function deleteDuplicates(head):

    curr = head

    while curr != NULL AND curr->next != NULL:

        if curr->val == curr->next->val:

            curr->next = curr->next->next

        else:

            curr = curr->next

    return head


Complete Optimal Code:
-----------------------

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *curr = head;

        while (curr != nullptr && curr->next != nullptr)
        {
            if (curr->val == curr->next->val)
            {
                curr->next = curr->next->next;
            }
            else
            {
                curr = curr->next;
            }
        }

        return head;
    }
};


Time Complexity:
----------------
O(n)

Each node is visited at most a constant number of times.


Space Complexity:
-----------------
O(1)

Only one pointer is used.


===============================================================================
Dry Run With Example
===============================================================================

Example:

    [1, 1, 2, 3, 3]


Initial List:

    1 -> 1 -> 2 -> 3 -> 3 -> NULL


Step 1:
-------
curr = first 1

Compare:

    curr->val = 1
    curr->next->val = 1

They are equal.

Skip the duplicate:

    curr->next = curr->next->next


List becomes:

    1 -> 2 -> 3 -> 3 -> NULL


Step 2:
-------
curr is still at 1.

Compare:

    1 != 2

Move curr:

    curr = curr->next

Now:

    curr = 2


Step 3:
-------
Compare:

    2 != 3

Move curr to 3.


Step 4:
-------
Compare:

    3 == 3

Skip the duplicate:

    curr->next = curr->next->next


List becomes:

    1 -> 2 -> 3 -> NULL


Step 5:
-------
curr->next is NULL.

Stop.

Final Answer:

    [1, 2, 3]


===============================================================================
Edge Cases
===============================================================================

1. Empty list:

       []

   head == NULL

   Return NULL.


2. Single node:

       [1]

   Nothing to remove.

   Return [1].


3. All elements are duplicates:

       [1, 1, 1, 1]

   Result:

       [1]


4. No duplicates:

       [1, 2, 3, 4]

   Result remains unchanged.


5. Multiple duplicate groups:

       [1, 1, 2, 2, 3, 3]

   Result:

       [1, 2, 3]


===============================================================================
Interview Notes
===============================================================================

Pattern:
--------
Linked List + Two Pointer / In-place Modification


Key Observation:
----------------
The list is sorted.

Therefore:

    Duplicate values are always adjacent.

This allows us to compare only:

    curr
    curr->next


Common Mistakes:
----------------

1. Moving curr after deleting a duplicate.

   Wrong:

       if (curr->val == curr->next->val)
       {
           curr->next = curr->next->next;
           curr = curr->next;   // unnecessary
       }

   There may be more duplicates immediately after the current node.

   Correct:

       curr->next = curr->next->next;

   Keep curr at the same node.


2. Using extra space.

   A set is unnecessary because the list is sorted.


3. Forgetting NULL checks.

   Always make sure:

       curr != nullptr
       curr->next != nullptr

   before accessing curr->next->val.


4. Deleting the current node unnecessarily.

   We can simply bypass the duplicate node by changing the next pointer.


5. Confusing this problem with LeetCode 82.

   LeetCode 83:

       Keep ONE occurrence of every value.

       [1, 1, 2, 3, 3]
           ->
       [1, 2, 3]


   LeetCode 82:

       Remove ALL values that have duplicates.

       [1, 1, 2, 3, 3]
           ->
       [2]


When To Use This Approach:
--------------------------

Use this approach when:

- The linked list is sorted.
- Duplicate values should be merged/removed.
- Equal values appear consecutively.
- In-place modification is allowed.
- O(1) extra space is preferred.


Core Mental Template:
---------------------

curr = head

while curr != NULL and curr->next != NULL:

    if curr->val == curr->next->val:

        curr->next = curr->next->next

    else:

        curr = curr->next

return head


Final Complexity:
-----------------

Time  : O(n)
Space : O(1)

================================================================================
*/
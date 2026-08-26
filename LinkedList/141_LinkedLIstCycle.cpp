#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }

        return false;
    }
};

int main()
{
    
    ListNode *head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(-4);

    head->next->next->next->next = head->next;

    Solution sol;

    cout << (sol.hasCycle(head) ? "Cycle exists" : "No cycle") << '\n';

    return 0;
}

/*
============================================================
             LEETCODE 141 - LINKED LIST CYCLE
============================================================

Problem Statement:
------------------
Given the head of a linked list, determine if the linked list
has a cycle in it.

A cycle exists if there is some node in the list that can be
reached again by continuously following the next pointer.

Return:

    true  -> if a cycle exists
    false -> otherwise


Example:
--------
Input:

    3 -> 2 -> 0 -> -4
        ^             |
        |_____________|

Output:

    true

Explanation:

The last node points back to the node containing 2, creating
a cycle.


============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
Use a hash set to store every node that we have already visited.

While traversing:

    If the current node is already present in the set,
    a cycle exists.

Otherwise, add the node to the set and continue.

If we reach nullptr, there is no cycle.


Pseudo Code:
------------
set = empty hash set

current = head

while current != NULL:

    if current is already in set:
        return true

    add current to set

    current = current->next

return false


Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool hasCycle(ListNode *head) {

        unordered_set<ListNode*> visited;

        ListNode *current = head;

        while (current != nullptr) {

            if (visited.count(current))
                return true;

            visited.insert(current);

            current = current->next;
        }

        return false;
    }
};

Time Complexity:
----------------
O(n)

Every node is visited at most once.

Space Complexity:
-----------------
O(n)

The hash set can contain every node.


============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
We don't actually need extra memory.

Use two pointers:

    slow -> moves one step
    fast -> moves two steps

This is called Floyd's Cycle Detection Algorithm.


Intuition:
----------
If there is no cycle:

    fast will eventually reach nullptr.

If there is a cycle:

    slow and fast will eventually meet.

Why?

Inside a cycle, fast moves one step faster than slow.

Therefore, the distance between them keeps changing until
fast catches slow.

Think of two runners on a circular track:

    slow -> 1 step
    fast -> 2 steps

The faster runner must eventually catch the slower runner.


Pseudo Code:
------------
slow = head
fast = head

while fast != NULL AND fast->next != NULL:

    slow = slow->next
    fast = fast->next->next

    if slow == fast:
        return true

return false


Complete Optimal Code:
----------------------

class Solution {
public:
    bool hasCycle(ListNode *head) {

        ListNode *slow = head;
        ListNode *fast = head;

        while (fast != nullptr && fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }

        return false;
    }
};

Time Complexity:
----------------
O(n)

Each pointer traverses the list a linear number of times.

Space Complexity:
-----------------
O(1)

Only two pointers are used.


============================================================
DRY RUN WITH EXAMPLE
============================================================

List:

    3 -> 2 -> 0 -> -4
         ^         |
         |_________|

Initial:

    slow = 3
    fast = 3


Iteration 1:
------------
slow moves one step:

    slow = 2

fast moves two steps:

    fast = 0


Iteration 2:
------------
slow:

    slow = 0

fast:

    fast = 2


Iteration 3:
------------
slow:

    slow = -4

fast:

    fast = -4

Now:

    slow == fast

Therefore:

    return true


============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Two Pointers / Fast & Slow Pointers

Key Observation:
----------------
If a linked list contains a cycle, a pointer moving two steps
at a time will eventually meet a pointer moving one step at a
time.

Use:

    slow = slow->next
    fast = fast->next->next


Common Mistakes:
----------------
1. Comparing node values instead of node addresses.

   Correct:

       if (slow == fast)

   Not:

       if (slow->val == fast->val)

   Different nodes can have the same value.

2. Forgetting to check:

       fast != nullptr
       fast->next != nullptr

   before doing:

       fast = fast->next->next

3. Using a visited set when O(1) extra space is expected.

4. Thinking fast must become nullptr in a cyclic list.

   It never does. Both pointers remain inside the cycle
   and eventually meet.


When to use this approach:
--------------------------
Use Floyd's Fast and Slow Pointer technique when:

- You need to detect a cycle in a linked list.
- You want O(1) extra space.
- You need to detect repeated states in a sequence.
- A slow pointer and faster pointer can eventually meet.


Related Problems:
-----------------
LeetCode 142:
    Linked List Cycle II

LeetCode 287:
    Find the Duplicate Number

Both can be solved using the same fundamental
Fast & Slow Pointer / Floyd's Cycle Detection idea.


Quick Revision:
---------------

    slow = 1 step
    fast = 2 steps

    No cycle:
        fast reaches NULL

    Cycle:
        slow == fast

    Time  = O(n)
    Space = O(1)

============================================================
*/

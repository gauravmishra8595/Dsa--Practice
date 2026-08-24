#include <bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x)
    {
        val = x;
        next = nullptr;
    }
};

class Solution
{
public:
    ListNode *insertionSortList(ListNode *head)
    {
        ListNode dummy(0);
        ListNode *curr = head;

        while (curr != nullptr)
        {
            ListNode *nextNode = curr->next;

            ListNode *prev = &dummy;

            while (prev->next != nullptr &&
                   prev->next->val <= curr->val)
            {
                prev = prev->next;
            }

            curr->next = prev->next;
            prev->next = curr;

            curr = nextNode;
        }

        return dummy.next;
    }
};

int main()
{
    // Simple local ListNode definition for VS Code testing.
    struct Node
    {
        int val;
        Node *next;

        Node(int x) : val(x), next(nullptr) {}
    };

   
    return 0;
}

/*
================================================================================
                  LEETCODE 147 - INSERTION SORT LIST
================================================================================

IMPORTANT:
----------
LeetCode provides the ListNode structure automatically.

For LeetCode submission, use:

    class Solution {
        ...
    };

Do NOT add your own ListNode definition on LeetCode.


===============================================================================
PROBLEM STATEMENT
===============================================================================

Given the head of a singly linked list, sort the linked list using
Insertion Sort and return the sorted list.


Example:
--------

Input:

    4 -> 2 -> 1 -> 3 -> NULL

Output:

    1 -> 2 -> 3 -> 4 -> NULL


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
Copy all linked-list values into a vector.

Sort the vector using std::sort.

Then write the sorted values back into the linked list.


Pseudo Code:
-----------

create vector

traverse linked list:
    push every value into vector

sort vector

traverse linked list again:
    replace node values using sorted vector

return head


Complete Brute Force Code:
--------------------------

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {

        vector<int> values;

        ListNode* curr = head;

        while (curr != nullptr) {
            values.push_back(curr->val);
            curr = curr->next;
        }

        sort(values.begin(), values.end());

        curr = head;
        int i = 0;

        while (curr != nullptr) {
            curr->val = values[i];
            i++;
            curr = curr->next;
        }

        return head;
    }
};


Time Complexity:
----------------
O(N log N)


Space Complexity:
-----------------
O(N)


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
The problem specifically asks for Insertion Sort on a linked list.

Insertion Sort works by maintaining a sorted portion.

For every current node:

1. Remove it from the original list.
2. Find its correct position in the sorted portion.
3. Insert it there.


Intuition:
----------
Suppose the list is:

    4 -> 2 -> 1 -> 3

Initially:

    sorted = empty

Take 4:

    4


Take 2:

    2 -> 4


Take 1:

    1 -> 2 -> 4


Take 3:

    1 -> 2 -> 3 -> 4


The key advantage of linked lists is that insertion does not require
shifting elements.

We only need to change pointers.


Dummy Node:
-----------
Use a dummy node before the sorted list:

    dummy -> sorted elements

This makes inserting before the first element easy.

For every current node, start from dummy and find the first node
whose value is greater than the current value.

Then insert current before that node.


Pseudo Code:
-----------

dummy = new node

curr = head

while curr exists:

    save curr->next

    prev = dummy

    while prev->next exists AND
          prev->next->val <= curr->val:

        prev = prev->next

    insert curr after prev

    curr = saved next node

return dummy->next


Complete Optimal Code:
----------------------

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {

        ListNode dummy(0);

        ListNode* curr = head;

        while (curr != nullptr) {

            ListNode* nextNode = curr->next;

            ListNode* prev = &dummy;

            while (prev->next != nullptr &&
                   prev->next->val <= curr->val) {

                prev = prev->next;
            }

            curr->next = prev->next;
            prev->next = curr;

            curr = nextNode;
        }

        return dummy.next;
    }
};


Time Complexity:
----------------
Worst Case:

O(N^2)

For every node, we may scan almost the entire sorted portion.


Space Complexity:
-----------------
O(1)

Only a few pointers are used.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Input:

    4 -> 2 -> 1 -> 3


Initial:

    dummy -> NULL
    curr = 4


STEP 1:
-------
Take 4.

Sorted:

    4

    dummy -> 4


STEP 2:
-------
Take 2.

Compare 2 with 4.

2 < 4

Insert before 4.

Sorted:

    2 -> 4


STEP 3:
-------
Take 1.

Compare 1 with 2.

1 < 2

Insert before 2.

Sorted:

    1 -> 2 -> 4


STEP 4:
-------
Take 3.

Compare:

    3 > 1
    3 > 2
    3 < 4

Insert between 2 and 4.

Sorted:

    1 -> 2 -> 3 -> 4


Final:

    1 -> 2 -> 3 -> 4 -> NULL


===============================================================================
WHY DO WE SAVE nextNode?
===============================================================================

Before inserting curr, we do:

    ListNode* nextNode = curr->next;


This is necessary because curr->next will be changed during insertion.

Example:

    4 -> 2 -> 1

Suppose curr = 2.

We need to remember:

    nextNode = 1

because after inserting 2 into the sorted list, curr->next no
longer necessarily points to 1.


===============================================================================
WHY USE A DUMMY NODE?
===============================================================================

Without a dummy node, inserting before the current head requires
special handling.

For example:

    sorted = 4

Insert 2:

    2 -> 4

With dummy:

    dummy -> 4

We can simply insert 2 after dummy:

    dummy -> 2 -> 4

Therefore dummy removes special cases.


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Linked List + Insertion Sort


Key Observation:
----------------
Insertion Sort is naturally suitable for linked lists because
inserting a node only requires changing pointers.

Unlike arrays, we do NOT need to shift elements.


Common Mistakes:
----------------

1. Forgetting to save curr->next before changing curr->next.

2. Losing the remaining unsorted portion of the list.

3. Forgetting to use a dummy node or incorrectly updating the head.

4. Searching from head instead of dummy.

5. Returning dummy instead of:

       dummy.next


6. Writing:

       prev->next->val < curr->val

   instead of <= when you want stable insertion behavior.


===============================================================================
WHEN TO USE THIS APPROACH
===============================================================================

Use this approach when:

- The problem explicitly asks for Insertion Sort.
- You are sorting a singly linked list.
- You need O(1) extra space.
- You want to practice pointer manipulation.
- The input is already partially sorted and insertion sort may perform
  well in practical scenarios.


===============================================================================
IMPORTANT COMPLEXITY NOTE
===============================================================================

Insertion Sort on a linked list:

    Time:
        Best     = O(N)
        Average  = O(N^2)
        Worst    = O(N^2)

    Space:
        O(1)


Merge Sort on a linked list can achieve:

    Time  = O(N log N)
    Space = O(log N) recursively
            or O(1) with bottom-up implementation

But LeetCode 147 specifically asks for:

    Insertion Sort


===============================================================================
STANDALONE VS CODE VERSION
===============================================================================

If you want to test the exact solution in VS Code, define ListNode
yourself and use it in main.

Example:

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) {
        val = x;
        next = nullptr;
    }
};


Then main can create:

    4 -> 2 -> 1 -> 3

call insertionSortList(), and print the result.


===============================================================================
FINAL REVISION LINE
===============================================================================

Linked List
    ↓
Insertion Sort
    ↓
Maintain sorted portion
    ↓
Find correct position
    ↓
Change pointers
    ↓
O(N^2) Time
    ↓
O(1) Space


================================================================================
*/

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// ==================== OPTIMAL SOLUTION ====================

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode dummy(0);
        ListNode *tail = &dummy;

        while (list1 && list2)
        {
            if (list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        if (list1)
        {
            tail->next = list1;
        }
        else
        {
            tail->next = list2;
        }

        return dummy.next;
    }
};

int main()
{
    
    struct Node
    {
        int val;
        Node *next;

        Node(int x) : val(x), next(nullptr) {}
    };

  

    Node *list1 = new Node(1);
    list1->next = new Node(2);
    list1->next->next = new Node(4);

    Node *list2 = new Node(1);
    list2->next = new Node(3);
    list2->next->next = new Node(4);

    Node dummy(0);
    Node *tail = &dummy;

    Node *a = list1;
    Node *b = list2;

    while (a && b)
    {
        if (a->val <= b->val)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }

        tail = tail->next;
    }

    tail->next = a ? a : b;

    Node *ans = dummy.next;

    while (ans)
    {
        cout << ans->val << " ";
        ans = ans->next;
    }

    cout << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 21
                  MERGE TWO SORTED LISTS
================================================================================

PROBLEM STATEMENT
-----------------
You are given the heads of two sorted singly linked lists:

    list1
    list2

Merge the two lists into one sorted linked list.

The merged list should be made by reusing the existing nodes.

Return the head of the merged linked list.


================================================================================
EXAMPLE
================================================================================

Input:

    list1 = 1 -> 2 -> 4
    list2 = 1 -> 3 -> 4

Output:

    1 -> 1 -> 2 -> 3 -> 4 -> 4


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Store all values from both linked lists into a vector.

Then sort the vector.

Finally, create a new linked list using the sorted values.

This works, but it does not take advantage of the fact that
both input linked lists are already sorted.


PSEUDO CODE
-----------

    create vector arr

    traverse list1:
        add values to arr

    traverse list2:
        add values to arr

    sort(arr)

    create linked list using sorted values

    return head


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        vector<int> arr;

        ListNode* curr = list1;

        while (curr) {
            arr.push_back(curr->val);
            curr = curr->next;
        }

        curr = list2;

        while (curr) {
            arr.push_back(curr->val);
            curr = curr->next;
        }

        sort(arr.begin(), arr.end());

        ListNode dummy(0);
        ListNode* tail = &dummy;

        for (int x : arr) {

            tail->next = new ListNode(x);
            tail = tail->next;
        }

        return dummy.next;
    }
};


TIME COMPLEXITY
----------------

Let:

    n = length of list1
    m = length of list2

Collecting values:

    O(n + m)

Sorting:

    O((n + m) log(n + m))

Overall:

    O((n + m) log(n + m))


SPACE COMPLEXITY
----------------

Vector:

    O(n + m)

New linked list:

    O(n + m)

Therefore:

    O(n + m)


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------

Both linked lists are ALREADY SORTED.

Example:

    list1:

        1 -> 2 -> 4

    list2:

        1 -> 3 -> 4


So we don't need to sort everything again.

We can use TWO POINTERS.


INTUITION
---------

Keep one pointer on each list:

    p1 -> list1
    p2 -> list2


Compare:

    p1->val
    p2->val


Take the smaller node and attach it to the result.

Then move that pointer forward.

Repeat until one list becomes empty.

Finally, attach the remaining part of the other list.


Example:

    list1 = 1 -> 2 -> 4
    list2 = 1 -> 3 -> 4

Compare:

    1 vs 1

Take list1's 1.

Result:

    1

Compare:

    2 vs 1

Take list2's 1.

Result:

    1 -> 1

Compare:

    2 vs 3

Take 2.

Result:

    1 -> 1 -> 2

Continue...


DUMMY NODE
----------

We use a dummy node to make linked-list manipulation easier.

    dummy -> ...

Keep:

    tail

pointing to the last node of the result.

Whenever we choose a node:

    tail->next = chosen_node

    tail = tail->next


PSEUDO CODE
-----------

    create dummy node

    tail = dummy

    while list1 AND list2:

        if list1->val <= list2->val:

            tail->next = list1
            list1 = list1->next

        else:

            tail->next = list2
            list2 = list2->next

        tail = tail->next


    if list1 exists:
        tail->next = list1

    else:
        tail->next = list2


    return dummy.next


COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode dummy(0);

        ListNode* tail = &dummy;

        while (list1 && list2) {

            if (list1->val <= list2->val) {

                tail->next = list1;
                list1 = list1->next;

            } else {

                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        if (list1) {
            tail->next = list1;
        } else {
            tail->next = list2;
        }

        return dummy.next;
    }
};


TIME COMPLEXITY
----------------

Each node is visited exactly once.

If:

    n = length of list1
    m = length of list2

Then:

    O(n + m)


SPACE COMPLEXITY
----------------

No new nodes are required.

Only a few pointers are used.

Therefore:

    O(1)


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

list1:

    1 -> 2 -> 4

list2:

    1 -> 3 -> 4


Initially:

    p1 -> 1
    p2 -> 1

    dummy -> NULL


STEP 1
------

Compare:

    1 <= 1

Take list1's node.

    result:
        1

Move p1:

    p1 -> 2


STEP 2
------

Compare:

    2 > 1

Take list2's node.

    result:
        1 -> 1

Move p2:

    p2 -> 3


STEP 3
------

Compare:

    2 < 3

Take list1's node.

    result:
        1 -> 1 -> 2

Move p1:

    p1 -> 4


STEP 4
------

Compare:

    4 > 3

Take list2's node.

    result:
        1 -> 1 -> 2 -> 3

Move p2:

    p2 -> 4


STEP 5
------

Compare:

    4 <= 4

Take list1's node.

    result:
        1 -> 1 -> 2 -> 3 -> 4

Move p1:

    p1 -> NULL


STEP 6
------

list1 is empty.

Attach remaining list2:

    4


FINAL RESULT
------------

    1 -> 1 -> 2 -> 3 -> 4 -> 4


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------

Two Pointers + Linked List


KEY OBSERVATION
---------------

Both linked lists are already sorted.

Therefore:

    NO NEED TO SORT AGAIN.


Just compare the current nodes from both lists.

    smaller value
          |
          v
    add to answer
          |
          v
    move that pointer


COMMON MISTAKES
---------------

1. Forgetting to move the selected pointer.

       list1 = list1->next;


2. Forgetting:

       tail = tail->next;


3. Forgetting to attach the remaining list.

       tail->next = list1 ? list1 : list2;


4. Returning dummy instead of:

       dummy.next


5. Creating unnecessary new nodes.

   We can simply reuse the existing nodes.


6. Handling only one list.

   If:

       list1 == NULL

   return list2.

   If:

       list2 == NULL

   return list1.


7. Forgetting that linked-list nodes contain:

       val
       next


================================================================================
WHEN TO USE THIS APPROACH
================================================================================

Use this pattern when:

    - Two linked lists are sorted.
    - You need to merge them.
    - You want O(n + m) time.
    - You can reuse existing nodes.


This same idea appears in:

    - Merge Sort
    - Merge K Sorted Lists
    - Merging sorted arrays
    - Two-pointer problems


================================================================================
IMPORTANT LINKED LIST TEMPLATE
================================================================================

Dummy node:

    ListNode dummy(0);

    ListNode* tail = &dummy;


Build answer:

    tail->next = node;
    tail = tail->next;


Return:

    dummy.next


This avoids special handling for the first node.


================================================================================
RECURSIVE VERSION
================================================================================

Another valid solution is recursion.

The idea:

    Compare list1 and list2.

    Pick the smaller node.

    Recursively merge the remaining lists.


Recursive code:

// class Solution {
// public:
//
//     ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
//
//         if (!list1) {
//             return list2;
//         }
//
//         if (!list2) {
//             return list1;
//         }
//
//         if (list1->val <= list2->val) {
//
//             list1->next = mergeTwoLists(
//                 list1->next,
//                 list2
//             );
//
//             return list1;
//
//         } else {
//
//             list2->next = mergeTwoLists(
//                 list1,
//                 list2->next
//             );
//
//             return list2;
//         }
//     }
// };


Recursive Complexity:

    Time  : O(n + m)
    Space : O(n + m)

because of recursion stack.

Therefore, the ITERATIVE solution above is preferred for CP.


================================================================================
FINAL COMPLEXITY
================================================================================

Optimal Iterative Solution:

    Time  : O(n + m)
    Space : O(1)


================================================================================
CORE IDEA TO REMEMBER
================================================================================

        TWO SORTED LISTS
                |
                v
        TWO POINTERS
                |
                v
       COMPARE CURRENT NODES
                |
                v
        TAKE THE SMALLER
                |
                v
          MOVE POINTER
                |
                v
        ATTACH REMAINING
                |
                v
             ANSWER


================================================================================
*/

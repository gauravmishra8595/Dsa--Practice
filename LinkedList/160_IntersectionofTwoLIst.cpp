#include <iostream>
using namespace std;

// Definition for singly-linked list
struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x)
    {
        val = x;
        next = NULL;
    }
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {

        ListNode *a = headA;
        ListNode *b = headB;

        while (a != b)
        {

            if (a == NULL)
                a = headB;
            else
                a = a->next;

            if (b == NULL)
                b = headA;
            else
                b = b->next;
        }

        return a;
    }
};

int main()
{

    // Common part (intersection)
    ListNode *common = new ListNode(8);
    common->next = new ListNode(4);
    common->next->next = new ListNode(5);

    // List A: 4 -> 1 -> 8 -> 4 -> 5
    ListNode *headA = new ListNode(4);
    headA->next = new ListNode(1);
    headA->next->next = common;

    // List B: 5 -> 6 -> 1 -> 8 -> 4 -> 5
    ListNode *headB = new ListNode(5);
    headB->next = new ListNode(6);
    headB->next->next = new ListNode(1);
    headB->next->next->next = common;

    Solution obj;

    ListNode *result = obj.getIntersectionNode(headA, headB);

    if (result != NULL)
        cout << "Intersection Node Value: " << result->val << endl;
    else
        cout << "No Intersection Found" << endl;

    return 0;
}
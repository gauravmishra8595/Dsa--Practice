#include <iostream>
using namespace std;

// Definition for singly-linked list
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode dummy(0);
        dummy.next = head;

        ListNode *slow = &dummy;
        ListNode *fast = &dummy;

        // move fast n steps ahead
        for (int i = 0; i < n; i++)
        {
            fast = fast->next;
        }

        // move both until fast reaches last node
        while (fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }

        // delete node
        slow->next = slow->next->next;

        return dummy.next;
    }
};

// Helper function to print list
void printList(ListNode *head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Helper function to insert node at end
ListNode *insert(ListNode *head, int val)
{
    if (!head)
        return new ListNode(val);

    ListNode *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new ListNode(val);
    return head;
}

int main()
{
    ListNode *head = NULL;

    // Creating linked list: 1 -> 2 -> 3 -> 4 -> 5
    head = insert(head, 1);
    head = insert(head, 2);
    head = insert(head, 3);
    head = insert(head, 4);
    head = insert(head, 5);

    cout << "Original List: ";
    printList(head);

    int n = 2;

    Solution obj;
    head = obj.removeNthFromEnd(head, n);

    cout << "After removing " << n << "th node from end: ";
    printList(head);

    return 0;
}
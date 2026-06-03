#include <iostream>

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

bool hasCycle(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // Create nodes
    ListNode *head = new ListNode(1);
    ListNode *second = new ListNode(2);
    ListNode *third = new ListNode(3);
    ListNode *fourth = new ListNode(4);

    // Link nodes
    head->next = second;
    second->next = third;
    third->next = fourth;

    // Create a cycle: 4 -> 2
    fourth->next = second;

    if (hasCycle(head))
    {
        cout << "Cycle detected!" << endl;
    }
    else
    {
        cout << "No cycle detected." << endl;
    }

    return 0;
}
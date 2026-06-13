#include <iostream>
using namespace std;

class ListNode
{
public:
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *temp = head;
        int cnt = 0;

        // Check if at least k nodes exist
        while (cnt < k)
        {
            if (temp == NULL)
                return head;

            temp = temp->next;
            cnt++;
        }

        // Reverse remaining list recursively
        ListNode *prevNode = reverseKGroup(temp, k);

        temp = head;
        cnt = 0;

        // Reverse current k nodes
        while (cnt < k)
        {
            ListNode *next = temp->next;
            temp->next = prevNode;
            prevNode = temp;
            temp = next;
            cnt++;
        }

        return prevNode;
    }
};

// Helper function to print list
void printList(ListNode *head)
{
    while (head != nullptr)
    {
        cout << head->val;
        if (head->next)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    // Create linked list:
    // 1 -> 2 -> 3 -> 4 -> 5
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 2;

    cout << "Original List:\n";
    printList(head);

    Solution sol;
    ListNode *newHead = sol.reverseKGroup(head, k);

    cout << "\nAfter Reversing in Groups of " << k << ":\n";
    printList(newHead);

    return 0;
}
#include <iostream>
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
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
            {
                ListNode *ptr = head;

                while (ptr != slow)
                {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};

// Helper: create list
ListNode *createList(int arr[], int n)
{
    if (n == 0)
        return nullptr;

    ListNode *head = new ListNode(arr[0]);
    ListNode *curr = head;

    for (int i = 1; i < n; i++)
    {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }

    return head;
}

// Helper: create cycle
void createCycle(ListNode *head, int pos)
{
    if (pos == -1)
        return;

    ListNode *cycleNode = nullptr;
    ListNode *curr = head;
    int index = 0;

    while (curr->next)
    {
        if (index == pos)
        {
            cycleNode = curr;
        }
        curr = curr->next;
        index++;
    }

    if (index == pos)
    {
        cycleNode = curr;
    }

    curr->next = cycleNode;
}

int main()
{
    int arr[] = {3, 2, 0, -4};
    int n = sizeof(arr) / sizeof(arr[0]);

    ListNode *head = createList(arr, n);

    // Create cycle at position 1 (node with value 2)
    createCycle(head, 1);

    Solution obj;
    ListNode *res = obj.detectCycle(head);

    if (res)
        cout << "Cycle starts at node with value: " << res->val << endl;
    else
        cout << "No cycle" << endl;

    return 0;
}
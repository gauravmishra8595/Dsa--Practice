#include <iostream>
using namespace std;

// Definition for singly-linked list.
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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(0);
        ListNode *current = &dummy;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry)
        {
            int sum = carry;

            if (l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }

        return dummy.next;
    }
};

// Helper function to create linked list
ListNode *createList(int arr[], int n)
{
    if (n == 0)
        return nullptr;

    ListNode *head = new ListNode(arr[0]);
    ListNode *temp = head;

    for (int i = 1; i < n; i++)
    {
        temp->next = new ListNode(arr[i]);
        temp = temp->next;
    }

    return head;
}

// Helper function to print linked list
void printList(ListNode *head)
{
    while (head)
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
    // Example:
    // l1 = [2,4,3]
    // l2 = [5,6,4]
    // Output = [7,0,8]

    int arr1[] = {2, 4, 3};
    int arr2[] = {5, 6, 4};

    ListNode *l1 = createList(arr1, 3);
    ListNode *l2 = createList(arr2, 3);

    Solution obj;
    ListNode *result = obj.addTwoNumbers(l1, l2);

    cout << "Result: ";
    printList(result);

    return 0;
}
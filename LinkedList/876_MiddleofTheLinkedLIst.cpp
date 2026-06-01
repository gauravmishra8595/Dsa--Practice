#include <iostream>
using namespace std;

// Definition of ListNode
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
    ListNode *middleNode(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};

// Helper function to insert nodes at end
void insertNode(ListNode *&head, int val)
{
    ListNode *newNode = new ListNode(val);

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    ListNode *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Helper function to print list from a node
void printFromNode(ListNode *node)
{
    while (node != NULL)
    {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

int main()
{
    ListNode *head = NULL;

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        insertNode(head, val);
    }

    Solution obj;
    ListNode *middle = obj.middleNode(head);

    cout << "\nMiddle node and onward list:\n";
    printFromNode(middle);

    return 0;
}
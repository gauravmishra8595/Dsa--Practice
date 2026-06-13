#include <iostream>
#include <unordered_map>
using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == NULL)
        {
            return NULL;
        }

        unordered_map<Node *, Node *> m;

        Node *newHead = new Node(head->val);
        m[head] = newHead;

        Node *oldtemp = head->next;
        Node *newTemp = newHead;

        while (oldtemp != NULL)
        {
            Node *copyNode = new Node(oldtemp->val);
            m[oldtemp] = copyNode;

            newTemp->next = copyNode;

            oldtemp = oldtemp->next;
            newTemp = newTemp->next;
        }

        oldtemp = head;
        newTemp = newHead;

        while (oldtemp != NULL)
        {
            newTemp->random = m[oldtemp->random];

            oldtemp = oldtemp->next;
            newTemp = newTemp->next;
        }

        return newHead;
    }
};

void printList(Node *head)
{
    while (head)
    {
        cout << "Value: " << head->val;

        if (head->random)
            cout << ", Random: " << head->random->val;
        else
            cout << ", Random: NULL";

        cout << endl;
        head = head->next;
    }
}

int main()
{
    // Create sample list:
    // 1 -> 2 -> 3
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);

    n1->next = n2;
    n2->next = n3;

    // Random pointers
    n1->random = n3; // 1 -> 3
    n2->random = n1; // 2 -> 1
    n3->random = n2; // 3 -> 2

    cout << "Original List:\n";
    printList(n1);

    Solution sol;
    Node *copiedHead = sol.copyRandomList(n1);

    cout << "\nCopied List:\n";
    printList(copiedHead);

    return 0;
}
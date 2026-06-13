#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) {
        val = x;
        next = nullptr;
    }
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        int n = 0;
        ListNode* temp = head;

        while (temp) {
            n++;
            temp = temp->next;
        }

        k = k % n;

        if (k == 0) {
            return head;
        }

        ListNode* start = head;
        ListNode* end = head;

        // Move end k steps ahead
        for (int i = 0; i < k; i++) {
            end = end->next;
        }

        // Move both pointers
        while (end->next != nullptr) {
            start = start->next;
            end = end->next;
        }

        ListNode* newHead = start->next;
        start->next = nullptr;
        end->next = head;

        return newHead;
    }
};

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Create: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 4;

    cout << "Original List: ";
    printList(head);

    Solution obj;
    head = obj.rotateRight(head, k);

    cout << "Rotated List: ";
    printList(head);

    return 0;
}
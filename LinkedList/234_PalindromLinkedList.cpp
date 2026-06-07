#include <iostream>
#include <vector>
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

class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        if (!head || !head->next)
            return true;

        ListNode *slow = head;
        ListNode *fast = head;

        // Find middle
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Skip middle node for odd-length lists
        if (fast != nullptr)
        {
            slow = slow->next;
        }

        // Reverse second half
        ListNode *prev = nullptr;
        ListNode *curr = slow;

        while (curr)
        {
            ListNode *nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        // Compare halves
        while (prev)
        {
            if (head->val != prev->val)
                return false;

            head = head->next;
            prev = prev->next;
        }

        return true;
    }
};

ListNode *createList(const vector<int> &nums)
{
    if (nums.empty())
        return nullptr;

    ListNode *head = new ListNode(nums[0]);
    ListNode *curr = head;

    for (int i = 1; i < nums.size(); i++)
    {
        curr->next = new ListNode(nums[i]);
        curr = curr->next;
    }

    return head;
}

int main()
{
    vector<int> nums = {1, 2, 3, 2, 1};

    ListNode *head = createList(nums);

    Solution obj;

    if (obj.isPalindrome(head))
        cout << "Palindrome\n";
    else
        cout << "Not Palindrome\n";

    return 0;
}
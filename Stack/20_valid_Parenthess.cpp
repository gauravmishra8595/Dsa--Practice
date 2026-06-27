#include <iostream>
#include <stack>

using namespace std;

class Solution
{
    stack<int> st;
    stack<int> mini;

public:
    // Push element into stack
    void push(int val)
    {
        st.push(val);

        if (mini.empty() || val <= mini.top())
            mini.push(val);
    }

    // Remove top element
    void pop()
    {
        if (st.empty())
        {
            cout << "Stack is empty.\n";
            return;
        }

        if (st.top() == mini.top())
            mini.pop();

        st.pop();
    }

    // Return top element
    int top()
    {
        if (st.empty())
        {
            cout << "Stack is empty.\n";
            return -1;
        }

        return st.top();
    }

    // Return minimum element
    int getMin()
    {
        if (mini.empty())
        {
            cout << "Stack is empty.\n";
            return -1;
        }

        return mini.top();
    }
};

int main()
{
    Solution obj;

    int n;
    cout << "Enter number of elements to push: ";
    cin >> n;

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        obj.push(x);
    }

    cout << "\nTop Element: " << obj.top() << endl;
    cout << "Minimum Element: " << obj.getMin() << endl;

    obj.pop();

    cout << "\nAfter one pop:\n";
    cout << "Top Element: " << obj.top() << endl;
    cout << "Minimum Element: " << obj.getMin() << endl;

    return 0;
}

/*
=========================================
LeetCode 155 : Min Stack
=========================================

Problem:
Design a stack that supports the following
operations in O(1) time.

1. push(x)
2. pop()
3. top()
4. getMin()

getMin() should always return the minimum
element currently present in the stack.

Example:

Input:
push(5)
push(2)
push(7)

top()    -> 7
getMin() -> 2

pop()

top()    -> 2
getMin() -> 2

=========================================
Brute Force Approach
=========================================

Idea:

Whenever getMin() is called,
traverse the entire stack to find
the smallest element.

Algorithm:

push(x)
    Push into stack

pop()
    Remove top element

top()
    Return top

getMin()
    Traverse entire stack
    Return smallest element

Time Complexity:

push    : O(1)
pop     : O(1)
top     : O(1)
getMin  : O(N)

Space Complexity:
O(N)

=========================================
Optimal Approach (Two Stacks)
=========================================

Idea:

Maintain two stacks.

1. Main Stack
   Stores all elements.

2. Min Stack
   Stores only minimum elements.

Rules:

Push:

If Min Stack is empty OR
current value <= current minimum,
push into Min Stack also.

Pop:

If popped element equals
minimum element,
remove from Min Stack.

Top:

Return top of Main Stack.

getMin():

Return top of Min Stack.

=========================================
Dry Run
=========================================

Input:

push(5)

Main Stack:
5

Min Stack:
5

------------------

push(2)

Main Stack:
5 2

Min Stack:
5 2

------------------

push(7)

Main Stack:
5 2 7

Min Stack:
5 2

------------------

getMin()

Answer = 2

------------------

pop()

Removed = 7

Main Stack:
5 2

Min Stack:
5 2

------------------

getMin()

Answer = 2

=========================================
Time & Space Complexity
=========================================

Push     : O(1)

Pop      : O(1)

Top      : O(1)

getMin() : O(1)

Space:
O(N)

=========================================
Interview Tip
=========================================

Instead of searching for the minimum
every time, maintain another stack
that keeps track of the minimum
element seen so far.

This allows all operations,
including getMin(),
to run in constant time O(1),
which is the expected interview solution.
=========================================
*/
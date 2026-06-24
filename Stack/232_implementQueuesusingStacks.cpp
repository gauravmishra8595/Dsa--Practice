#include <iostream>
#include <stack>
using namespace std;

class MyQueue
{
private:
    stack<int> input;
    stack<int> output;

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        input.push(x);
    }

    int pop()
    {
        peek(); // Ensure output stack has elements

        int frontElement = output.top();
        output.pop();

        return frontElement;
    }

    int peek()
    {
        if (output.empty())
        {
            while (!input.empty())
            {
                output.push(input.top());
                input.pop();
            }
        }

        return output.top();
    }

    bool empty()
    {
        return input.empty() && output.empty();
    }
};

int main()
{
    MyQueue q;

    q.push(1);
    q.push(2);
    q.push(3);

    cout << "Front Element: " << q.peek() << endl;

    cout << "Popped: " << q.pop() << endl;

    cout << "Front Element After Pop: " << q.peek() << endl;

    return 0;
}

/*
=========================================
LeetCode 232: Implement Queue using Stacks
=========================================

Queue Operations:
push(x)  -> Insert element
pop()    -> Remove front element
peek()   -> Return front element
empty()  -> Check if queue is empty

FIFO Principle:
First In First Out

Example:

push(1)
push(2)
push(3)

Queue:
Front -> 1 2 3 <- Rear

pop() => 1

=========================================
Brute Force Approach
=========================================

Idea:
Use two stacks.

For every push:
Move all elements from s1 to s2.
Insert new element into s1.
Move everything back from s2 to s1.

This keeps the front element
always on top of s1.

Code Sketch:

stack<int> s1, s2;

void push(int x)
{
    while(!s1.empty())
    {
        s2.push(s1.top());
        s1.pop();
    }

    s1.push(x);

    while(!s2.empty())
    {
        s1.push(s2.top());
        s2.pop();
    }
}

int pop()
{
    int x = s1.top();
    s1.pop();
    return x;
}

Time Complexity:
push -> O(n)
pop  -> O(1)

Space Complexity:
O(n)

=========================================
Optimal Approach (Lazy Transfer)
=========================================

Use Two Stacks:

input  -> For incoming elements
output -> For outgoing elements

Push:
Simply push into input stack.

Pop / Peek:
If output stack is empty:

Move all elements from input
to output.

This reverses the order and makes
the oldest element appear on top.

Example:

push(1)
push(2)
push(3)

Input:
3
2
1

Output:
empty

Need peek():

Transfer:

Output:
1
2
3

Now top of output = front of queue.

=========================================
Dry Run
=========================================

push(1)
push(2)
push(3)

Input:
3 2 1

Output:
empty

peek()

Transfer all elements

Output:
1 2 3

peek() => 1

pop() => 1

Output:
2 3

peek() => 2

=========================================
Complexities
=========================================

push()  -> O(1)

pop()   -> Amortized O(1)

peek()  -> Amortized O(1)

empty() -> O(1)

Space Complexity:
O(n)

=========================================
Why Amortized O(1)?
=========================================

Each element:

1. Pushed once into input
2. Moved once to output
3. Popped once from output

Every element is processed
a constant number of times.

Therefore average cost per
operation is O(1).

=========================================
Interview Tip
=========================================

Stack → LIFO

Queue → FIFO

To convert Stack into Queue:

Use two stacks and transfer elements
only when output stack becomes empty.

This "lazy transfer" approach is the
expected optimal solution for
LeetCode 232.
=========================================
*/
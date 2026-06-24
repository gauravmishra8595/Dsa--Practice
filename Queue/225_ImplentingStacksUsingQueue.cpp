#include <iostream>
#include <queue>
using namespace std;

class MyStack
{
private:
    queue<int> q;

public:
    MyStack()
    {
    }

    void push(int x)
    {
        q.push(x);

        // Rotate the queue so that the new element
        // comes to the front
        int size = q.size();

        for (int i = 0; i < size - 1; i++)
        {
            q.push(q.front());
            q.pop();
        }
    }

    int pop()
    {
        int topElement = q.front();
        q.pop();
        return topElement;
    }

    int top()
    {
        return q.front();
    }

    bool empty()
    {
        return q.empty();
    }
};

int main()
{
    MyStack st;

    st.push(1);
    st.push(2);
    st.push(3);

    cout << "Top Element: " << st.top() << endl;

    cout << "Popped: " << st.pop() << endl;

    cout << "Top Element After Pop: " << st.top() << endl;

    return 0;
}

/*
=========================================
LeetCode 225: Implement Stack using Queues
=========================================

Stack Operations:
push(x)  -> Insert element
pop()    -> Remove top element
top()    -> Return top element
empty()  -> Check if stack is empty

LIFO Principle:
Last In First Out

Example:

push(1)
push(2)
push(3)

Stack:
3 <- Top
2
1

pop() => 3

=========================================
Brute Force Approach (Using Two Queues)
=========================================

Idea:
Use two queues.

Push:
Insert into q1.

Pop:
Move first n-1 elements from q1 to q2.
Last remaining element is stack top.

After removing:
Swap q1 and q2.

Code Sketch:

queue<int> q1, q2;

void push(int x) {
    q1.push(x);
}

int pop() {
    while(q1.size() > 1) {
        q2.push(q1.front());
        q1.pop();
    }

    int ans = q1.front();
    q1.pop();

    swap(q1, q2);

    return ans;
}

Time Complexity:
push -> O(1)
pop  -> O(n)

Space Complexity:
O(n)

=========================================
Optimal Approach (Single Queue)
=========================================

Idea:
After every push,
rotate the queue so that the newly inserted
element comes to the front.

Example:

push(1)

Queue:
1

push(2)

Queue:
1 2

Rotate:
2 1

push(3)

Queue:
2 1 3

Rotate:
3 2 1

Now front always represents stack top.

pop():
Remove front.

top():
Return front.

=========================================
Dry Run
=========================================

push(1)
Queue: 1

push(2)
Queue: 2 1

push(3)
Queue: 3 2 1

top() => 3

pop() => 3

Queue: 2 1

top() => 2

=========================================
Complexities
=========================================

push()  -> O(n)
pop()   -> O(1)
top()   -> O(1)
empty() -> O(1)

Space Complexity: O(n)

=========================================
Interview Tip
=========================================

Two Common Solutions:

1. Two Queues
   Push O(1), Pop O(n)

2. One Queue (Expected)
   Push O(n), Pop O(1)

The single-queue approach is the most popular
solution for LeetCode 225.
=========================================
*/
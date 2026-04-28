#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
public:
    stack<int> st1;
    stack<int> st2;

    MyQueue() {}

    void push(int x) {
        st1.push(x);
    }

    int pop() {
        if (st2.empty()) {
            while (!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        int val = st2.top();
        st2.pop();
        return val;
    }

    int peek() {
        if (st2.empty()) {
            while (!st1.empty()) {
                st2.push(st1.top());
                st1.pop();
            }
        }
        return st2.top();
    }

    bool empty() {
        return st1.empty() && st2.empty();
    }
};

int main() {
    MyQueue q;

    q.push(1);
    q.push(2);
    q.push(3);

    cout << "Peek: " << q.peek() << endl; // 1
    cout << "Pop: " << q.pop() << endl;   // 1
    cout << "Peek: " << q.peek() << endl; // 2

    cout << "Is Empty: " << (q.empty() ? "Yes" : "No") << endl;

    return 0;
}
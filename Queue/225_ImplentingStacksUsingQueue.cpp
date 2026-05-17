#include <iostream>
#include <queue>
using namespace std;

class MyStack {
    queue<int> q;

public:
    MyStack() {
        
    }

    void push(int x) {
        q.push(x);

        // Rotate previous elements behind new element
        int n = q.size();

        for (int i = 0; i < n - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};

int main() {
    MyStack st;

    st.push(1);
    st.push(2);
    st.push(3);

    cout << st.top() << endl;   // 3
    cout << st.pop() << endl;   // 3
    cout << st.top() << endl;   // 2

    return 0;
}
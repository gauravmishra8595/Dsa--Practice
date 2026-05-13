#include <iostream>
#include <stack>

using namespace std;

class MinStack {
public:
    stack<int> st;
    stack<int> mini;

    MinStack() {

    }

    void push(int val) {
        st.push(val);

        if (mini.empty() || val <= mini.top()) {
            mini.push(val);
        }
    }

    void pop() {
        if (st.top() == mini.top()) {
            mini.pop();
        }

        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return mini.top();
    }
};

int main() {

    MinStack obj;

    obj.push(5);
    obj.push(2);
    obj.push(7);

    cout << "Top Element: " << obj.top() << endl;
    cout << "Minimum Element: " << obj.getMin() << endl;

    obj.pop();

    cout << "\nAfter one pop:\n";

    cout << "Top Element: " << obj.top() << endl;
    cout << "Minimum Element: " << obj.getMin() << endl;

    obj.pop();

    cout << "\nAfter second pop:\n";

    cout << "Top Element: " << obj.top() << endl;
    cout << "Minimum Element: " << obj.getMin() << endl;

    return 0;
}
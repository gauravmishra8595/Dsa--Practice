#include <bits/stdc++.h>
using namespace std;

class MyCircularQueue {
    vector<int> arr;
    int front;
    int rear;
    int size;
    int capacity;

public:
    MyCircularQueue(int k) {
        capacity = k;
        arr.resize(k);
        front = 0;
        rear = 0;
        size = 0;
    }

    bool enQueue(int value) {
        if (isFull()) return false;

        arr[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;

        front = (front + 1) % capacity;
        size--;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    int Rear() {
        if (isEmpty()) return -1;
        return arr[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }

    // ✅ DISPLAY FUNCTION
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "Queue elements: ";

        int i = front;
        for (int cnt = 0; cnt < size; cnt++) {
            cout << arr[i] << " ";
            i = (i + 1) % capacity;
        }

        cout << endl;
    }
};

int main() {
    MyCircularQueue q(3);

    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);

    q.display(); // 10 20 30

    q.deQueue(); // remove 10

    q.display(); // 20 30

    q.enQueue(40); // wrap-around happens

    q.display(); // 20 30 40

    cout << "Front: " << q.Front() << endl;
    cout << "Rear: " << q.Rear() << endl;

    return 0;
}
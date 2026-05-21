#include <iostream>
#include <vector>
using namespace std;
class MyCircularDeque {
    vector<int> arr;
    int front;
    int rear;
    int size;
    int capacity;
public:
    MyCircularDeque(int k) {
        capacity = k;
        arr.resize(k);
        front = 0;
        rear = 0;
        size = 0;
    }

    bool insertFront(int value) {
        if (isFull()) return false;
        front = (front - 1 + capacity) % capacity;
        arr[front] = value;
        size++;
        return true;
    }
    bool insertLast(int value) {
        if (isFull()) return false;
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
        return true;
    }
    bool deleteFront() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        size--;
        return true;
    }
    bool deleteLast() {
        if (isEmpty()) return false;
        rear = (rear - 1 + capacity) % capacity;
        size--;
        return true;
    }
    int getFront() {
        if (isEmpty()) return -1;
        return arr[front];
    }
    int getRear() {
        if (isEmpty()) return -1;
        return arr[(rear - 1 + capacity) % capacity];
    }
    bool isEmpty() {
        return size == 0;
    }
    bool isFull() {
        return size == capacity;
    }
};

int main() {
    MyCircularDeque dq(3);
    cout << dq.insertLast(1) << endl;   // true
    cout << dq.insertLast(2) << endl;   // true
    cout << dq.insertFront(3) << endl;  // true
    cout << dq.insertFront(4) << endl;  // false
    cout << dq.getRear() << endl;       // 2
    cout << dq.isFull() << endl;        // true
    cout << dq.deleteLast() << endl;    // true
    cout << dq.insertFront(4) << endl;  // true
    cout << dq.getFront() << endl;      // 4
    return 0;
}
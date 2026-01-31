#include <iostream>
#include <climits>
using namespace std;

int getMin(int num[], int n) {
    int minVal = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (num[i] < minVal) {
            minVal = num[i];
        }
    }
    return minVal;
}

int getMax(int num[], int n) {
    int maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (num[i] > maxVal) {
            maxVal = num[i];
        }
    }
    return maxVal;
}

int main() {
    int size;
    cout << "Enter the size of array: ";
    cin >> size;

    int num[100];
    for (int i = 0; i < size; i++) {
        cin >> num[i];
    }

    cout << "Maximum value is: " << getMax(num, size) << endl;
    cout << "Minimum value is: " << getMin(num, size) << endl;

    return 0;
}

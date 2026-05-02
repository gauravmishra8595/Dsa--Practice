#include <iostream>
#include <vector>
using namespace std;

vector<int> plusOne(vector<int>& digits) {
    int n = digits.size();

    for (int i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }

    // if all digits were 9
    digits.insert(digits.begin(), 1);
    return digits;
}

int main() {
    vector<int> digits = {9, 9, 9};

    vector<int> result = plusOne(digits);

    for (int x : result) {
        cout << x << " ";
    }

    return 0;
}
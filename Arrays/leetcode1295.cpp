#include <iostream>
#include <vector>
using namespace std;


int findNumbers(vector<int>& nums) {
    int count = 0;  

    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        int digits = 0;

        // count digits in current number
        while (num > 0) {
            digits++;
            num /= 10;
        }

        // if digits are even, increment count
        if (digits % 2 == 0) {
            count++;
        }
    }

    return count; // return total numbers with even digits
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    int result = findNumbers(nums);
    cout << "Number of elements with even digits = " << result << endl;

    return 0;
}

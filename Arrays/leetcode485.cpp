#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findMaxConsecutiveOnes(vector<int>& nums) {
    int maxCount = 0;
    int count = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
            count++;
            maxCount = max(maxCount, count);
        } else {
            count = 0;
        }
    }
    return maxCount;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements (0s and 1s): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int result = findMaxConsecutiveOnes(nums);
    cout << "Maximum consecutive ones = " << result << endl;

    return 0;
}

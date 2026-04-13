#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0, count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }

        return candidate;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

    int result = obj.majorityElement(nums);

    cout << "Majority Element: " << result << endl;

    return 0;
}
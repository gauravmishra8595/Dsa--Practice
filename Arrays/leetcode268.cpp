#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long expectedSum = 1LL * n * (n + 1) / 2;
        long long actualSum = 0;
        for(int i = 0; i < n; i++){
            actualSum += nums[i];
        }
        int missingNumber = expectedSum - actualSum;
        return missingNumber;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {0, 1};
    

    int missing = sol.missingNumber(nums);
    
    cout << "Missing number: " << missing << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            ans ^= num;
        }
        return ans;
    }
};

int main() {
    Solution obj;
    
    vector<int> nums = {4, 1, 2, 1, 2};  // test input
    
    int result = obj.singleNumber(nums);
    
    cout << "Single number is: " << result << endl;
    
    return 0;
}
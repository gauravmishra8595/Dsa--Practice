#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        m[0] = 1;  
        int sum = 0;
        int count = 0;
        
        for (int num : nums) {
            sum += num;
            if (m.find(sum - k) != m.end()) {
                count += m[sum - k];  
            }
            m[sum]++;  
        }
        
        return count;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    int k = 3;
    
    int result = sol.subarraySum(nums, k);
    cout << "Number of subarrays that sum to " << k << " is: " << result << endl;

    return 0;
}

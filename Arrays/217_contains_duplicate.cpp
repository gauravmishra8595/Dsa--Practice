#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if (nums.size() < 2) return false;

        sort(nums.begin(), nums.end());

        int start = 0;
        int end = 1;

        while (end < nums.size()) {
            if (nums[start] == nums[end]) {
                return true;
            }
            start++;
            end++;
        }

        return false;
    }
};

int main() {
    Solution sol;

    
    vector<int> nums1 = {1, 2, 3, 4};     
    vector<int> nums2 = {1, 2, 3, 1};      
    vector<int> nums3 = {5, 5, 5, 5, 5};   

    cout << boolalpha; 

    cout << "Test 1: " << sol.containsDuplicate(nums1) << endl; // false
    cout << "Test 2: " << sol.containsDuplicate(nums2) << endl; // true
    cout << "Test 3: " << sol.containsDuplicate(nums3) << endl; // true

    return 0;
}

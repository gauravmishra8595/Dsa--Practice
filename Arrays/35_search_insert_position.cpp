#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int s = 0;
        int e = nums.size() - 1;
        
        while (s <= e) {
            int m = s + (e - s) / 2; 
            if (nums[m] == target)
                return m;
            else if (nums[m] < target)
                s = m + 1;
            else
                e = m - 1;
        }
        
        return s; 
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 3, 5, 6};
    int target = 5;
    
    cout << "Insert position: " << sol.searchInsert(nums, target) << endl; 
    
    target = 2;
    cout << "Insert position: " << sol.searchInsert(nums, target) << endl; 
    
    target = 7;
    cout << "Insert position: " << sol.searchInsert(nums, target) << endl; 
    
    return 0;
}

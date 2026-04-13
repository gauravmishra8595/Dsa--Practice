#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;

        int k = 0; 

        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] != nums[k]) {
                k++;              
                nums[k] = nums[i]; 
            }

            cout << "i = " << i << ", k = " << k << ", nums = [";
            for(int j = 0; j <= k; j++) cout << nums[j] << (j < k ? "," : "");
            cout << "]" << endl;
        }

        return k + 1; 
    }
};

int main() {
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};
    Solution sol;
    int uniqueCount = sol.removeDuplicates(nums);

    cout << "\nNumber of unique elements: " << uniqueCount << endl;
    cout << "Array after removing duplicates: [";
    for(int i = 0; i < uniqueCount; i++)
        cout << nums[i] << (i < uniqueCount - 1 ? "," : "");
    cout << "]" << endl;

    return 0;
}

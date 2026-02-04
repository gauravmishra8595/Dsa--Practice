#include <iostream>
#include<vector>
using namespace std;
 class Solution{
    public:
    vector<int> running_sum(vector<int>&nums){
        for (int i = 1; i < nums.size(); i++)
        {
            nums[i]=nums[i]+nums[i-1];
        }
        return nums;
    }
 };
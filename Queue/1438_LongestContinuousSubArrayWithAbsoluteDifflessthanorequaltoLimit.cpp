#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {

        deque<int> maxi;
        deque<int> mini;

        int left = 0;
        int ans = 0;

        for(int right = 0; right < nums.size(); right++) {

            // Maintain decreasing deque for maximum
            while(!maxi.empty() && maxi.back() < nums[right]) {
                maxi.pop_back();
            }
            maxi.push_back(nums[right]);

            // Maintain increasing deque for minimum
            while(!mini.empty() && mini.back() > nums[right]) {
                mini.pop_back();
            }
            mini.push_back(nums[right]);

            // Shrink window if invalid
            while(maxi.front() - mini.front() > limit) {

                if(nums[left] == maxi.front()) {
                    maxi.pop_front();
                }

                if(nums[left] == mini.front()) {
                    mini.pop_front();
                }

                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

int main() {

    Solution obj;

    vector<int> nums = {8, 2, 4, 7};
    int limit = 4;

    int result = obj.longestSubarray(nums, limit);

    cout << "Longest Subarray Length: " << result << endl;

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            // Make mid even
            if (mid % 2 == 1)
                mid--;

            if (nums[mid] == nums[mid + 1])
            {
                left = mid + 2;
            }
            else
            {
                right = mid;
            }
        }

        return nums[left];
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 8, 8};

    cout << "Single element: "
         << sol.singleNonDuplicate(nums)
         << endl;

    return 0;
}
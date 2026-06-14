#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int farthest = 0;
        int target = nums.size() - 1;

        for (int i = 0; i < nums.size(); i++)
        {
            if (i > farthest)
            {
                return false;
            }

            farthest = max(farthest, i + nums[i]);

            if (farthest >= target)
            {
                return true;
            }
        }

        return true;
    }
};

int main()
{
    vector<int> nums = {2, 3, 1, 1, 4};

    Solution sol;

    if (sol.canJump(nums))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    return 0;
}
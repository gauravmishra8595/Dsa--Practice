#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution
{
public:
    bool canSplit(vector<int> &nums, int k, long long maxSum)
    {
        int subarrays = 1;
        long long currSum = 0;

        for (int num : nums)
        {
            if (currSum + num > maxSum)
            {
                subarrays++;
                currSum = num;

                if (subarrays > k)
                    return false;
            }
            else
            {
                currSum += num;
            }
        }

        return true;
    }

    int splitArray(vector<int> &nums, int k)
    {
        long long left = *max_element(nums.begin(), nums.end());
        long long right = accumulate(nums.begin(), nums.end(), 0LL);

        while (left < right)
        {
            long long mid = left + (right - left) / 2;

            if (canSplit(nums, k, mid))
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {7, 2, 5, 10, 8};
    int k = 2;

    int answer = obj.splitArray(nums, k);

    cout << "Minimum largest subarray sum = "
         << answer << endl;

    return 0;
}
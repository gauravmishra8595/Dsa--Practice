#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        for (int i = 0; i < n - 3; i++)
        {

            // Skip duplicates for i
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i + 1; j < n - 2; j++)
            {

                // Skip duplicates for j
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                int left = j + 1;
                int right = n - 1;

                while (left < right)
                {

                    long long sum = (long long)nums[i] +
                                    nums[j] +
                                    nums[left] +
                                    nums[right];

                    if (sum == target)
                    {
                        ans.push_back({nums[i],
                                       nums[j],
                                       nums[left],
                                       nums[right]});

                        left++;
                        right--;

                        // Skip duplicates for left
                        while (left < right &&
                               nums[left] == nums[left - 1])
                            left++;

                        // Skip duplicates for right
                        while (left < right &&
                               nums[right] == nums[right + 1])
                            right--;
                    }
                    else if (sum < target)
                    {
                        left++;
                    }
                    else
                    {
                        right--;
                    }
                }
            }
        }

        return ans;
    }
};

int main()
{
    int n, target;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    cout << "Enter target: ";
    cin >> target;

    Solution obj;
    vector<vector<int>> result = obj.fourSum(nums, target);

    cout << "\nQuadruplets:\n";

    if (result.empty())
    {
        cout << "No quadruplets found.\n";
    }
    else
    {
        for (auto &quad : result)
        {
            cout << "[ ";
            for (int x : quad)
            {
                cout << x << " ";
            }
            cout << "]\n";
        }
    }

    return 0;
}
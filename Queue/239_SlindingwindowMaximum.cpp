#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        deque<int> dq;
        vector<int> res;

        for (int i = 0; i < nums.size(); i++)
        {
            // remove out-of-window elements
            if (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            // maintain decreasing order in deque
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();

            dq.push_back(i);

            // start adding results after first window
            if (i >= k - 1)
                res.push_back(nums[dq.front()]);
        }

        return res;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> ans = obj.maxSlidingWindow(nums, k);

    cout << "Sliding Window Maximum: ";
    for (int x : ans)
        cout << x << " ";

    cout << endl;

    return 0;
}

/*
=========================================
LeetCode 239: Sliding Window Maximum
=========================================

Brute Force:
- Check every window of size k
- Find max each time
- Time: O(n * k)

Optimal (Deque):
- Use monotonic decreasing deque
- Front always stores max element index

Rules:
1. Remove elements out of window
2. Remove smaller elements from back
3. Push current index
4. If window formed, take front as answer

Time Complexity: O(n)
Space Complexity: O(k)

=========================================
Pattern:
Sliding Window + Monotonic Queue
=========================================
*/
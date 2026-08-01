#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> st(nums.begin(), nums.end());
        int max_length = 0;

        for (int x : st)
        {
            // start only if x is the beginning of a sequence
            if (st.find(x - 1) == st.end())
            {
                int curr = x;
                int curr_length = 1;

                while (st.find(curr + 1) != st.end())
                {
                    curr++;
                    curr_length++;
                }

                max_length = max(max_length, curr_length);
            }
        }

        return max_length;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {100, 4, 200, 1, 3, 2};

    cout << obj.longestConsecutive(nums) << endl;

    return 0;
}
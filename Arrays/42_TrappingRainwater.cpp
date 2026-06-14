// class Solution
// {
// public:
//     int trap(vector<int> &height)
//     {
//         int n = height.size();
//         int total_water = 0;
//         for (int i = 0; i < n; i++)
//         {
//             int lmax = height[i];
//             int rmax = height[i];
//             for (int j = 0; j < i; j++)
//             {
//                 lmax = max(lmax, height[j]);
//             }
//             for (int j = i; j < n; j++)
//             {
//                 rmax = max(rmax, height[j]);
//             }
//             total_water += min(lmax, rmax) - height[i];
//         }
//         return total_water;
//     }
// };  brute force mthod
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int ans = 0;
        int n = height.size();

        int l = 0, r = n - 1;
        int lmax = 0, rmax = 0;

        while (l < r)
        {
            lmax = max(lmax, height[l]);
            rmax = max(rmax, height[r]);

            if (lmax < rmax)
            {
                ans += lmax - height[l];
                l++;
            }
            else
            {
                ans += rmax - height[r];
                r--;
            }
        }

        return ans;
    }
};

int main()
{
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    Solution obj;
    int result = obj.trap(height);

    cout << "Trapped water = " << result << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    bool canPlace(vector<int> &position, int m, int dist)
    {
        int count = 1; // first ball at position[0]
        int last = position[0];

        for (int i = 1; i < position.size(); i++)
        {
            if (position[i] - last >= dist)
            {
                count++;
                last = position[i];

                if (count >= m)
                    return true;
            }
        }
        return false;
    }

    int maxDistance(vector<int> &position, int m)
    {
        sort(position.begin(), position.end());

        int low = 1;
        int high = position.back() - position.front();
        int ans = 0;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (canPlace(position, m, mid))
            {
                ans = mid;
                low = mid + 1; // try larger distance
            }
            else
            {
                high = mid - 1; // reduce distance
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> position = {1, 2, 3, 4, 7};
    int m = 3;

    cout << "Maximum minimum distance = "
         << sol.maxDistance(position, m) << endl;

    return 0;
}
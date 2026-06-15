#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxEvents(vector<vector<int>> &events)
    {
        sort(events.begin(), events.end());

        priority_queue<int, vector<int>, greater<int>> pq; // min-heap of end days

        int n = events.size();
        int i = 0;
        int ans = 0;

        // find maximum day
        int maxDay = 0;
        for (auto &e : events)
        {
            maxDay = max(maxDay, e[1]);
        }

        for (int day = 1; day <= maxDay; day++)
        {

            // add all events starting today
            while (i < n && events[i][0] == day)
            {
                pq.push(events[i][1]);
                i++;
            }

            // remove expired events
            while (!pq.empty() && pq.top() < day)
            {
                pq.pop();
            }

            // attend one event
            if (!pq.empty())
            {
                pq.pop();
                ans++;
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> events1 = {{1, 2}, {2, 3}, {3, 4}};
    vector<vector<int>> events2 = {{1, 2}, {2, 3}, {3, 4}, {1, 2}};

    cout << "Test 1: " << sol.maxEvents(events1) << endl;
    cout << "Test 2: " << sol.maxEvents(events2) << endl;

    return 0;
}
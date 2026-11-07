#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        // Available: {weight, index}
        priority_queue<pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>> available;

        // Busy: {freeTime, weight, index}
        priority_queue<tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>> busy;

        int n = servers.size();
        int m = tasks.size();

        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long currentTime = 0;

        for (int i = 0; i < m; i++) {

            // Task cannot be processed before its arrival.
            currentTime = max(currentTime, (long long)i);

            // Release all servers that have become free.
            while (!busy.empty() &&
                   get<0>(busy.top()) <= currentTime) {

                auto [freeTime, weight, idx] = busy.top();
                busy.pop();

                available.push({weight, idx});
            }

            // If no server is available, jump to the
            // earliest server's free time.
            if (available.empty()) {

                currentTime = get<0>(busy.top());

                // Release all servers available at this time.
                while (!busy.empty() &&
                       get<0>(busy.top()) <= currentTime) {

                    auto [freeTime, weight, idx] = busy.top();
                    busy.pop();

                    available.push({weight, idx});
                }
            }

            // Select the best available server.
            auto [weight, idx] = available.top();
            available.pop();

            ans[i] = idx;

            // Assign task and update server's free time.
            busy.push({
                currentTime + tasks[i],
                weight,
                idx
            });
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> servers = {3, 3, 2};
    vector<int> tasks = {1, 2, 3, 2, 1, 2};

    vector<int> ans = sol.assignTasks(servers, tasks);

    for (int x : ans) {
        cout << x << " ";
    }

    cout << '\n';

    return 0;
}

/*
============================================================
       LEETCODE 1882 - PROCESS TASKS USING SERVERS
============================================================

PROBLEM STATEMENT:
------------------
Given servers[i] (server weight) and tasks[i] (processing
time), assign every task to a server.

Rules:
1. Choose the available server with minimum weight.
2. Break ties using minimum server index.
3. If no server is available, wait.
4. Tasks arrive at time i.
5. Each server processes one task at a time.

EXAMPLE:
--------

servers = [3, 3, 2]
tasks   = [1, 2, 3, 2, 1, 2]

Output:
[2, 2, 0, 2, 2, 0]


BRUTE FORCE APPROACH:
---------------------

IDEA:
Maintain the free time of each server.
For every task, scan all servers to find the best
available server. If none is available, jump to the
earliest free time.

PSEUDO CODE:

Initialize freeTime[n] = 0

For each task i:

    currentTime = max(currentTime, i)

    Find best available server

    If no server available:
        currentTime = minimum freeTime
        Find best available server again

    Assign task

    freeTime[server] = currentTime + tasks[i]

COMPLETE BRUTE FORCE CODE:

    class Solution {
    public:
        vector<int> assignTasks(vector<int>& servers,
                                vector<int>& tasks) {

            int n = servers.size();
            vector<long long> freeTime(n, 0);
            vector<int> ans(tasks.size());

            long long currentTime = 0;

            for (int i = 0; i < tasks.size(); i++) {

                currentTime = max(currentTime, (long long)i);

                while (true) {

                    int best = -1;

                    for (int j = 0; j < n; j++) {

                        if (freeTime[j] <= currentTime) {

                            if (best == -1 ||
                                servers[j] < servers[best] ||
                                (servers[j] == servers[best] &&
                                 j < best)) {
                                best = j;
                            }
                        }
                    }

                    if (best != -1) {
                        ans[i] = best;
                        freeTime[best] =
                            currentTime + tasks[i];
                        break;
                    }

                    currentTime = *min_element(
                        freeTime.begin(), freeTime.end()
                    );
                }
            }

            return ans;
        }
    };

TIME COMPLEXITY:
O(m * n)

SPACE COMPLEXITY:
O(n + m)


OPTIMAL APPROACH:
-----------------

OBSERVATION:

Two different priority queues are needed.

1. Available heap:
   {weight, index}

2. Busy heap:
   {freeTime, weight, index}

INTUITION:

Maintain a global currentTime.

For every task:
1. Update currentTime to at least its arrival time.
2. Release every server whose freeTime <= currentTime.
3. If no server is available, jump currentTime to
   the earliest freeTime.
4. Release all servers that become free at that time.
5. Select the minimum (weight, index).
6. Assign the task.
7. Update freeTime = currentTime + tasks[i].

PSEUDO CODE:

Initialize available and busy heaps

Insert all servers into available heap

currentTime = 0

For each task i:

    currentTime = max(currentTime, i)

    While busy is not empty AND
          busy.top.freeTime <= currentTime:

        Move server from busy to available

    If available is empty:

        currentTime = busy.top.freeTime

        While busy is not empty AND
              busy.top.freeTime <= currentTime:

            Move server from busy to available

    Select best available server

    ans[i] = server index

    busy.push(
        currentTime + tasks[i],
        weight,
        index
    )

Return ans


COMPLETE OPTIMAL CODE:

    class Solution {
    public:
        vector<int> assignTasks(vector<int>& servers,
                                vector<int>& tasks) {

            priority_queue<pair<int, int>,
                vector<pair<int, int>>,
                greater<pair<int, int>>> available;

            priority_queue<tuple<long long, int, int>,
                vector<tuple<long long, int, int>>,
                greater<tuple<long long, int, int>>> busy;

            for (int i = 0; i < servers.size(); i++) {
                available.push({servers[i], i});
            }

            vector<int> ans(tasks.size());

            long long currentTime = 0;

            for (int i = 0; i < tasks.size(); i++) {

                currentTime = max(currentTime, (long long)i);

                while (!busy.empty() &&
                       get<0>(busy.top()) <= currentTime) {

                    auto [t, w, idx] = busy.top();
                    busy.pop();

                    available.push({w, idx});
                }

                if (available.empty()) {

                    currentTime = get<0>(busy.top());

                    while (!busy.empty() &&
                           get<0>(busy.top()) <= currentTime) {

                        auto [t, w, idx] = busy.top();
                        busy.pop();

                        available.push({w, idx});
                    }
                }

                auto [weight, idx] = available.top();
                available.pop();

                ans[i] = idx;

                busy.push({
                    currentTime + tasks[i],
                    weight,
                    idx
                });
            }

            return ans;
        }
    };

TIME COMPLEXITY:
O((n + m) log n)

SPACE COMPLEXITY:
O(n + m)


DRY RUN:
--------

servers = [3, 3, 2]
tasks   = [1, 2, 3, 2, 1, 2]

| Task | Arrival | Start | Server | Free Time |
|------|---------|-------|--------|-----------|
| 0    | 0       | 0     | 2      | 1         |
| 1    | 1       | 1     | 2      | 3         |
| 2    | 2       | 2     | 0      | 5         |
| 3    | 3       | 3     | 2      | 5         |
| 4    | 4       | 5     | 2      | 6         |
| 5    | 5       | 5     | 0      | 7         |

Answer:
[2, 2, 0, 2, 2, 0]


INTERVIEW NOTES:
----------------

PATTERN:
Greedy + Two Min Heaps

KEY OBSERVATION:
The available heap handles server selection.
The busy heap handles server scheduling.

COMMON MISTAKES:

1. Not updating global currentTime.
2. Using arrival time instead of actual execution time.
3. Releasing only one server when multiple servers
   become free simultaneously.
4. Forgetting weight and index tie-breaking.
5. Using int instead of long long for freeTime.

WHEN TO USE THIS APPROACH:

Use two priority queues when objects move between
available and busy states and each state requires
a different priority ordering.

RELATED PROBLEMS:
- LeetCode 1834: Single-Threaded CPU
- LeetCode 2402: Meeting Rooms III

============================================================
                    END OF NOTES
============================================================
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // Min heap: {finish_time, server_index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            // Release all servers whose tasks are completed.
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }

            // No server is available.
            if (available.empty()) {
                continue;
            }

            // Preferred server for this request.
            int preferred = i % k;

            // Find first available server >= preferred.
            auto it = available.lower_bound(preferred);

            // Wrap around if necessary.
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            available.erase(it);

            count[server]++;

            busy.push({
                arrival[i] + load[i],
                server
            });
        }

        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    int k = 3;

    vector<int> arrival = {1,2,3,4,5};
    vector<int> load = {5,2,3,3,3};

    vector<int> ans = sol.busiestServers(k, arrival, load);

    for (int x : ans) {
        cout << x << " ";
    }

    cout << endl;

    return 0;
}

/*
===========================================================
                 LEETCODE 1606 - HARD
                  Find Servers That Handled Most Number of Requests
===========================================================

PROBLEM STATEMENT:
------------------
There are k servers numbered from 0 to k-1.

You are given two arrays:

arrival[i] = Arrival time of the ith request.
load[i]    = Time required to process the ith request.

Requests arrive in increasing order of arrival time.

For the ith request:

1. Preferred server = i % k.
2. If the preferred server is available, assign it.
3. Otherwise, assign the next available server with a
   larger index, wrapping around to server 0 if necessary.
4. If no server is available, drop the request.

A server becomes available when its current request finishes.

Return all servers that handled the maximum number
of requests, in ascending order.

EXAMPLE:
--------
Input:
k = 3
arrival = [1,2,3,4,5]
load = [5,2,3,3,3]

Output:
[1]

Explanation:

Request 0:
    Preferred server = 0
    Server 0 handles request.
    Finishes at 6.

Request 1:
    Preferred server = 1
    Server 1 handles request.
    Finishes at 4.

Request 2:
    Preferred server = 2
    Server 2 handles request.
    Finishes at 6.

Request 3:
    Preferred server = 0
    Server 0 busy.
    Server 1 finishes at 4.
    Assign server 1.
    Finishes at 7.

Request 4:
    Preferred server = 1
    Server 1 busy.
    Server 2 busy.
    Server 0 busy.
    Request dropped.

Request counts:

Server 0 = 1
Server 1 = 2
Server 2 = 1

Answer = [1]

===========================================================
BRUTE FORCE APPROACH:
===========================================================

IDEA:
-----
Maintain an array representing the finishing time of
each server.

For every request:
    1. Calculate preferred server i % k.
    2. Search servers in circular order.
    3. Find the first server whose finishing time
       is <= arrival[i].
    4. Assign the request and update finishing time.
    5. If no server is available, drop the request.

PSEUDO CODE:
------------

finish[k] = 0
count[k] = 0

for i = 0 to n-1:

    preferred = i % k
    assigned = false

    for j = 0 to k-1:

        server = (preferred + j) % k

        if finish[server] <= arrival[i]:

            finish[server] = arrival[i] + load[i]
            count[server]++

            assigned = true
            break

    if not assigned:
        continue

return all servers having maximum count

COMPLETE BRUTE FORCE CODE:
--------------------------

class SolutionBrute {
public:
    vector<int> busiestServers(
        int k,
        vector<int>& arrival,
        vector<int>& load
    ) {
        int n = arrival.size();

        vector<int> finish(k, 0);
        vector<int> count(k, 0);

        for (int i = 0; i < n; i++) {

            int preferred = i % k;

            for (int j = 0; j < k; j++) {

                int server = (preferred + j) % k;

                if (finish[server] <= arrival[i]) {

                    finish[server] = arrival[i] + load[i];

                    count[server]++;

                    break;
                }
            }
        }

        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
----------------
O(n * k + k)

For every request, we may check all k servers.

SPACE COMPLEXITY:
-----------------
O(k)

===========================================================
OPTIMAL APPROACH:
===========================================================

OBSERVATION:
------------
We need two different operations:

1. Quickly identify servers that have finished processing.
2. Quickly find the next available server in circular order.

Use:

A. MIN HEAP
-----------
Stores:

    {finish_time, server_index}

The server that finishes earliest stays at the top.

Before processing a request, release every server
whose finish_time <= arrival[i].

B. ORDERED SET
--------------
Stores all currently available server indices.

Use:

    set<int> available;

The set keeps server indices sorted.

Use lower_bound() to find the smallest available
server index >= i % k.

If no such server exists, wrap around using:

    available.begin()

INTUITION:
----------
For each request:

1. Release completed servers from the min heap.
2. If the set is empty, drop the request.
3. Calculate preferred server = i % k.
4. Use lower_bound() to find the next available server.
5. If lower_bound() returns end(), select the smallest
   available server.
6. Remove the selected server from the set.
7. Increase its request count.
8. Insert its new finishing time into the min heap.

PSEUDO CODE:
------------

available = {0, 1, 2, ..., k-1}

busy = min_heap()
count[k] = 0

for i = 0 to n-1:

    while busy is not empty AND
          busy.top.finish_time <= arrival[i]:

        release = busy.top.server
        available.insert(release)
        busy.pop()

    if available is empty:
        continue

    preferred = i % k

    it = available.lower_bound(preferred)

    if it == available.end():
        it = available.begin()

    server = *it

    available.erase(it)

    count[server]++

    busy.push({
        arrival[i] + load[i],
        server
    })

maxi = maximum count

return all servers whose count == maxi

COMPLETE OPTIMAL CODE AGAIN:
----------------------------

class Solution {
public:
    vector<int> busiestServers(
        int k,
        vector<int>& arrival,
        vector<int>& load
    ) {
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            while (!busy.empty() &&
                   busy.top().first <= arrival[i]) {

                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) {
                continue;
            }

            int preferred = i % k;

            auto it = available.lower_bound(preferred);

            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            available.erase(it);

            count[server]++;

            busy.push({
                arrival[i] + load[i],
                server
            });
        }

        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
----------------
For n requests:

Heap operations:
    O(log k) per insertion/removal.

Set operations:
    O(log k) per insertion/removal/search.

Each server is released at most once per request,
so there are at most n heap removals.

TOTAL:
    O((n + k) log k)

SPACE COMPLEXITY:
-----------------
Available set = O(k)
Busy min heap  = O(k)
Count array    = O(k)

TOTAL:
    O(k)

===========================================================
DRY RUN WITH EXAMPLE:
===========================================================

k = 3

arrival = [1,2,3,4,5]
load    = [5,2,3,3,3]

Initially:

Available = {0,1,2}
Busy      = {}
Count     = [0,0,0]

REQUEST 0:
----------
Time = 1
Preferred = 0

Server 0 available.

Assign server 0.
Finishing time = 1 + 5 = 6.

Available = {1,2}
Busy      = {(6,0)}
Count     = [1,0,0]

REQUEST 1:
----------
Time = 2
Preferred = 1

Server 1 available.

Assign server 1.
Finishing time = 2 + 2 = 4.

Available = {2}
Busy      = {(4,1),(6,0)}
Count     = [1,1,0]

REQUEST 2:
----------
Time = 3
Preferred = 2

Server 2 available.

Assign server 2.
Finishing time = 3 + 3 = 6.

Available = {}
Busy      = {(4,1),(6,0),(6,2)}
Count     = [1,1,1]

REQUEST 3:
----------
Time = 4
Preferred = 0

Release server 1 because:
4 <= 4

Available = {1}

Server 0 is busy.
Next available server after 0 is 1.

Assign server 1.
Finishing time = 4 + 3 = 7.

Available = {}
Count     = [1,2,1]

REQUEST 4:
----------
Time = 5
Preferred = 1

Server 0, 1 and 2 are busy.

No available server.

Request dropped.

FINAL COUNTS:
-------------

Server 0 = 1
Server 1 = 2
Server 2 = 1

Maximum = 2

FINAL OUTPUT:
-------------

[1]

===========================================================
INTERVIEW NOTES:
===========================================================

PATTERN:
--------
Greedy + Min Heap + Ordered Set + Simulation.

KEY OBSERVATION:
----------------
The min heap efficiently tracks the earliest finishing
server.

The ordered set efficiently finds the next available
server using lower_bound().

COMMON MISTAKES:
----------------
1. Using < instead of <= when releasing servers.
2. Forgetting circular wrap-around.
3. Selecting the first available server instead of
   the next available server from i % k.
4. Forgetting to remove an assigned server from the set.
5. Using a max heap instead of a min heap.
6. Forgetting to drop requests when all servers are busy.
7. Using an incorrect preferred server index.
8. Not returning all servers tied for maximum requests.

WHEN TO USE THIS APPROACH:
--------------------------
Use Min Heap + Ordered Set when:

1. You need to track resources that become available
   at different times.
2. You need the earliest finishing resource.
3. You need to find the next available index efficiently.
4. Circular allocation or scheduling is involved.

RELATED CONCEPTS:
-----------------
1. Priority Queue
2. Min Heap
3. Ordered Set
4. lower_bound()
5. Greedy Scheduling
6. Simulation
7. Circular Array

FINAL TAKEAWAY:
---------------
MIN HEAP:
    Tracks busy servers and their finishing times.

ORDERED SET:
    Tracks available servers and finds the next
    server using lower_bound().

Remember:

    MIN HEAP + SET + GREEDY SIMULATION

===========================================================
*/

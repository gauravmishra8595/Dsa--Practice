#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<int> countServers(int n, vector<vector<int>> &logs, int x,
                             vector<int> &queries)
    {
        int m = logs.size();
        int q = queries.size();

        // Sort logs by timestamp
        sort(logs.begin(), logs.end(),
             [](const vector<int> &a, const vector<int> &b)
             {
                 return a[1] < b[1];
             });

        // Store query time with original index
        vector<pair<int, int>> timeIndex(q);

        for (int i = 0; i < q; i++)
        {
            timeIndex[i] = {queries[i], i};
        }

        sort(timeIndex.begin(), timeIndex.end());

        unordered_map<int, int> freq;
        vector<int> result(q);

        int i = 0, j = 0;

        for (auto [time, idx] : timeIndex)
        {
            int start = time - x;
            int end = time;

            // Add logs inside the right boundary
            while (j < m && logs[j][1] <= end)
            {
                freq[logs[j][0]]++;
                j++;
            }

            // Remove logs outside the left boundary
            while (i < j && logs[i][1] < start)
            {
                freq[logs[i][0]]--;

                if (freq[logs[i][0]] == 0)
                {
                    freq.erase(logs[i][0]);
                }

                i++;
            }

            // Servers without logs in the given interval
            result[idx] = n - freq.size();
        }

        return result;
    }
};

int main()
{
    Solution obj;

    int n = 3;
    vector<vector<int>> logs = {
        {1, 3},
        {2, 6},
        {1, 5}};

    int x = 5;

    vector<int> queries = {10, 11};

    vector<int> ans = obj.countServers(n, logs, x, queries);

    for (int val : ans)
    {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}

/*

============================================================
                    COUNT SERVERS
============================================================

PROBLEM STATEMENT:

You are given:
- n: Number of servers (numbered from 1 to n).
- logs: A 2D array where logs[i] = [server_id, time].
- x: Time window length.
- queries: Array containing query timestamps.

For each query time t, consider the interval:

                [t - x, t]

A server is considered active if it has at least one log
within this interval (both boundaries are inclusive).

Return an array where each answer represents the number
of servers that did NOT have any logs in the given interval.

------------------------------------------------------------
EXAMPLE:
------------------------------------------------------------

Input:

n = 3
logs = [[1,3], [2,6], [1,5]]
x = 5
queries = [10,11]

Output:

[2,2]

Explanation:

Query = 10
Interval = [5,10]

Logs inside interval:
[2,6], [1,5]

Active servers = {1,2}
Inactive servers = {3}

Answer = 3 - 2 = 1

Query = 11
Interval = [6,11]

Logs inside interval:
[2,6]

Active servers = {2}
Inactive servers = {1,3}

Answer = 3 - 1 = 2

Correct output for this example is actually:

[1,2]

============================================================
BRUTE FORCE APPROACH
============================================================

1. IDEA:

For every query:
- Calculate start = query - x.
- Calculate end = query.
- Traverse all logs.
- Check whether each log falls inside the interval.
- Maintain a set of active server IDs.
- Answer = n - number of active servers.

2. PSEUDO CODE:

for each query:
    start = query - x
    end = query

    create empty set activeServers

    for each log:
        if start <= log.time <= end:
            insert log.serverId into activeServers

    answer = n - activeServers.size()

3. COMPLETE BRUTE FORCE CODE:

    class Solution {
    public:
        vector<int> countServers(int n,
                                 vector<vector<int>>& logs,
                                 int x,
                                 vector<int>& queries) {

            vector<int> result;

            for (int time : queries) {

                int start = time - x;
                int end = time;

                unordered_set<int> activeServers;

                for (auto& log : logs) {

                    int server = log[0];
                    int timestamp = log[1];

                    if (timestamp >= start &&
                        timestamp <= end) {

                        activeServers.insert(server);
                    }
                }

                result.push_back(
                    n - activeServers.size()
                );
            }

            return result;
        }
    };

4. TIME COMPLEXITY:

Let:
m = Number of logs
q = Number of queries

For every query, we traverse all logs.

Time Complexity:

O(q * m)

5. SPACE COMPLEXITY:

O(n)

For the set containing active servers.

============================================================
OPTIMAL APPROACH
============================================================

1. OBSERVATION:

Every query asks for the number of servers that have
NO logs in a particular time interval.

Instead of checking every log for every query,
we can process queries in sorted order.

Important observations:

- Sort logs by timestamp.
- Sort queries while preserving their original indices.
- Maintain a sliding window of logs.
- Use a frequency map to track active server IDs.

Since queries are processed in increasing order,
the sliding window only moves forward.

2. INTUITION:

For a query time t:

        start = t - x
        end   = t

We need logs satisfying:

        start <= log.timestamp <= end

Maintain two pointers:

i = Left pointer
j = Right pointer

FREQUENCY MAP:

freq[server_id] = Number of logs of that server
                  currently inside the window.

STEP 1: EXPAND WINDOW

Add all logs whose timestamp is <= end.

        while (j < m && logs[j][1] <= end)

        freq[logs[j][0]]++;
        j++;

STEP 2: SHRINK WINDOW

Remove logs whose timestamp is < start.

        while (i < j && logs[i][1] < start)

        freq[logs[i][0]]--;

If frequency becomes zero, erase that server.

STEP 3: CALCULATE ANSWER

Number of active servers = freq.size()

Number of inactive servers:

        answer = n - freq.size()

STEP 4: RESTORE ORIGINAL ORDER

Queries are sorted for efficient processing.

We store their original indices so that answers
are placed at their correct positions.

3. PSEUDO CODE:

Sort logs by timestamp.

Create pairs:
    (query_time, original_index)

Sort query pairs.

Create frequency map.

i = 0
j = 0

For every sorted query:

    start = query_time - x
    end = query_time

    while j < m and logs[j].time <= end:
        freq[logs[j].server]++
        j++

    while i < j and logs[i].time < start:
        freq[logs[i].server]--

        if freq[logs[i].server] == 0:
            erase server from map

        i++

    result[original_index] = n - freq.size()

Return result.

4. COMPLETE OPTIMAL CODE:

    class Solution {
    public:
        vector<int> countServers(int n,
                                 vector<vector<int>>& logs,
                                 int x,
                                 vector<int>& queries) {

            int m = logs.size();
            int q = queries.size();

            sort(logs.begin(), logs.end(),
                 [](const vector<int>& a,
                    const vector<int>& b) {
                     return a[1] < b[1];
                 });

            vector<pair<int,int>> timeIndex(q);

            for (int i = 0; i < q; i++) {
                timeIndex[i] = {queries[i], i};
            }

            sort(timeIndex.begin(), timeIndex.end());

            unordered_map<int,int> freq;

            vector<int> result(q);

            int i = 0, j = 0;

            for (auto [time, idx] : timeIndex) {

                int start = time - x;
                int end = time;

                while (j < m && logs[j][1] <= end) {
                    freq[logs[j][0]]++;
                    j++;
                }

                while (i < j && logs[i][1] < start) {

                    freq[logs[i][0]]--;

                    if (freq[logs[i][0]] == 0) {
                        freq.erase(logs[i][0]);
                    }

                    i++;
                }

                result[idx] = n - freq.size();
            }

            return result;
        }
    };

5. TIME COMPLEXITY:

Let:
m = Number of logs
q = Number of queries

Sorting logs:
    O(m log m)

Sorting queries:
    O(q log q)

Sliding window:
    O(m)

Each log is:
- Added exactly once.
- Removed at most once.

Hash map operations take O(1) average time.

TOTAL TIME COMPLEXITY:

    O(m log m + q log q)

6. SPACE COMPLEXITY:

Frequency map:
    O(n)

Query index array:
    O(q)

Result array:
    O(q)

TOTAL AUXILIARY SPACE:

    O(n + q)

============================================================
DRY RUN
============================================================

Input:

n = 3

logs = [
    [1,3],
    [2,6],
    [1,5]
]

x = 5

queries = [10,11]

STEP 1: SORT LOGS

logs = [
    [1,3],
    [1,5],
    [2,6]
]

STEP 2: SORT QUERIES WITH ORIGINAL INDEX

timeIndex = [
    {10,0},
    {11,1}
]

Initially:

i = 0
j = 0
freq = {}

------------------------------------------------------------
QUERY 1:
------------------------------------------------------------

time = 10

start = 10 - 5 = 5
end = 10

Required interval:

[5,10]

EXPAND:

Log [1,3]:

3 <= 10

freq = {1:1}

Log [1,5]:

5 <= 10

freq = {1:2}

Log [2,6]:

6 <= 10

freq = {1:2, 2:1}

Now j = 3.

SHRINK:

Check timestamp of logs[i]:

logs[0][1] = 3

3 < 5

Remove server 1:

freq = {1:1, 2:1}

Now i = 1.

Next timestamp:

logs[1][1] = 5

5 < 5 is FALSE.

STOP.

Active servers = 2

Inactive servers = 3 - 2 = 1

result[0] = 1

------------------------------------------------------------
QUERY 2:
------------------------------------------------------------

time = 11

start = 11 - 5 = 6
end = 11

Required interval:

[6,11]

EXPAND:

No more logs to add.

SHRINK:

Current logs[i]:

logs[1][1] = 5

5 < 6

Remove server 1:

freq = {2:1}

Now i = 2.

Next:

logs[2][1] = 6

6 < 6 is FALSE.

STOP.

Active servers = 1

Inactive servers = 3 - 1 = 2

result[1] = 2

------------------------------------------------------------
FINAL RESULT:
------------------------------------------------------------

result = [1,2]

============================================================
INTERVIEW NOTES
============================================================

1. PATTERN:

    Sorting + Sliding Window + Hash Map

This is an offline query processing problem.

We sort queries so that we can process all time
intervals efficiently using two pointers.

2. KEY OBSERVATION:

The most important observation is:

Queries can be sorted by timestamp without changing
the final answer order if we store their original indices.

This allows us to maintain a continuously moving
sliding window instead of rebuilding the window
for every query.

3. COMMON MISTAKES:

- Forgetting to preserve original query indices.
- Using logs[j][2] instead of logs[j][1] in comparator.
- Using log instead of logs.
- Removing logs with timestamp <= start.

  Correct condition:

      logs[i][1] < start

  Because the left boundary is inclusive.

- Forgetting to erase a server when its frequency
  becomes zero.

- Using i < m instead of i < j while removing logs.

4. WHEN TO USE THIS APPROACH:

Use Sorting + Sliding Window + Hash Map when:

- There are multiple range queries.
- Queries can be processed offline.
- Query intervals move in one direction after sorting.
- You need frequency/count information inside a window.
- You need distinct elements inside a range.
- Rebuilding the range for every query is too expensive.

SIMILAR PROBLEMS:

- Number of Servers That Stopped Receiving Requests
- Sliding Window Maximum
- Subarrays with K Different Integers
- Count Distinct Elements in Every Window
- Maximum Sum Subarray of Size K

============================================================
FINAL TAKEAWAY
============================================================

Instead of processing every query independently:

    SORT + TWO POINTERS + FREQUENCY MAP

Each log enters the window once and leaves the window
at most once.

This reduces the complexity from:

    O(q * m)

to:

    O(m log m + q log q)

============================================================

*/
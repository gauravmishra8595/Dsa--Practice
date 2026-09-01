#include <bits/stdc++.h>
#include<algorithm>
#include<queue>
using namespace std;

// LeetCode 1311: Get Watched Videos by Your Friends
class Solution
{
public:
    vector<string> watchedVideosByFriends(
        vector<vector<string>> &watchedVideos,
        vector<vector<int>> &friends,
        int id,
        int level)
    {
        int n = friends.size();

        // BFS to find all friends exactly at given level.
        vector<int> dist(n, -1);
        queue<int> q;

        q.push(id);
        dist[id] = 0;

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int next : friends[curr])
            {
                if (dist[next] == -1)
                {
                    dist[next] = dist[curr] + 1;
                    q.push(next);
                }
            }
        }

        // Count videos watched by friends at the required level.
        map<string, int> freq;

        for (int i = 0; i < n; ++i)
        {
            if (dist[i] == level)
            {
                for (string &video : watchedVideos[i])
                {
                    freq[video]++;
                }
            }
        }

        // map keeps videos sorted lexicographically.
        vector<pair<int, string>> videos;

        for (auto &[video, count] : freq)
        {
            videos.push_back({count, video});
        }

        // Sort by frequency first, then name.
        sort(videos.begin(), videos.end());

        vector<string> ans;

        for (auto &[count, video] : videos)
        {
            ans.push_back(video);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<vector<string>> watchedVideos = {
        {"A", "B"},
        {"C"},
        {"B", "C"},
        {"D"}};

    vector<vector<int>> friends = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}};

    int id = 0;
    int level = 1;

    vector<string> ans =
        sol.watchedVideosByFriends(
            watchedVideos,
            friends,
            id,
            level);

    for (string &video : ans)
    {
        cout << video << " ";
    }

    cout << '\n';

    return 0;
}

/*
======================================================================
                  LEETCODE 1311
          GET WATCHED VIDEOS BY YOUR FRIENDS
======================================================================


PROBLEM STATEMENT
-----------------

You are given:

    watchedVideos[i]

which contains the videos watched by person i.

You are also given:

    friends[i]

which contains the friends of person i.

You are given:

    id
    level

We need to find all videos watched by friends who are exactly
'level' friends away from person 'id'.

Return the videos sorted by:

    1. Increasing frequency.
    2. If frequencies are equal, lexicographically increasing order.


======================================================================
EXAMPLE
======================================================================

Input:

    watchedVideos = {
        {"A", "B"},
        {"C"},
        {"B", "C"},
        {"D"}
    }

    friends = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    }

    id = 0
    level = 1


Friend graph:

        1
       / \
      0   3
       \ /
        2


Person 0 has direct friends:

    1
    2


Videos watched by friend 1:

    C

Videos watched by friend 2:

    B
    C


Frequency:

    B -> 1
    C -> 2


Therefore answer:

    {"B", "C"}


======================================================================
BRUTE FORCE APPROACH
======================================================================


IDEA
----

We need people exactly 'level' edges away from id.

A simple approach is to use BFS to find the distance of every
person from id.

Then:

    - Find people whose distance == level.
    - Count all videos watched by them.
    - Sort the videos according to the required rules.


This is already essentially the optimal graph traversal approach.

A less optimized implementation can separately perform BFS levels
and use an unordered_map for counting, followed by a custom sort.


PSEUDO CODE
-----------

BFS:

    queue = {id}
    mark id visited
    currentLevel = 0

    while queue not empty:

        process current level

        if currentLevel == level:
            collect all people in queue
            break

        push all unvisited friends

        currentLevel++


For every person at required level:

    count every watched video


Convert frequency map into vector.

Sort:

    frequency ascending
    name ascending


Return video names.


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:
    vector<string> watchedVideosByFriends(
        vector<vector<string>>& watchedVideos,
        vector<vector<int>>& friends,
        int id,
        int level
    ) {

        int n = friends.size();

        queue<int> q;
        vector<bool> visited(n, false);

        q.push(id);
        visited[id] = true;

        int currentLevel = 0;
        vector<int> target;

        while (!q.empty()) {

            int sz = q.size();

            if (currentLevel == level) {

                while (sz--) {
                    target.push_back(q.front());
                    q.pop();
                }

                break;
            }

            while (sz--) {

                int curr = q.front();
                q.pop();

                for (int next : friends[curr]) {

                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }

            currentLevel++;
        }

        unordered_map<string, int> freq;

        for (int person : target) {
            for (string& video : watchedVideos[person]) {
                freq[video]++;
            }
        }

        vector<pair<int, string>> videos;

        for (auto& [video, count] : freq) {
            videos.push_back({count, video});
        }

        sort(
            videos.begin(),
            videos.end(),
            [](const auto& a, const auto& b) {

                if (a.first != b.first)
                    return a.first < b.first;

                return a.second < b.second;
            }
        );

        vector<string> ans;

        for (auto& [count, video] : videos) {
            ans.push_back(video);
        }

        return ans;
    }
};


TIME COMPLEXITY
----------------

BFS visits every person and every friendship:

    O(N + E)

where:

    N = number of people
    E = number of friendship edges


Suppose there are V distinct videos.

Counting:

    O(total number of watched videos)


Sorting:

    O(V log V)


Overall:

    O(N + E + W + V log V)

where W is the total number of watched-video entries.


SPACE COMPLEXITY
----------------

BFS:

    O(N)

Frequency map:

    O(V)

Answer:

    O(V)

Therefore:

    O(N + V)


======================================================================
OPTIMAL APPROACH
======================================================================


OBSERVATION
-----------

The friendship structure is an unweighted graph.

Every friendship represents an edge with cost 1.

We need people at exactly:

    level

distance from:

    id


Therefore, this is a standard BFS problem.


INTUITION
---------

BFS naturally explores a graph level by level.

For example:

    Level 0:
        id

    Level 1:
        Direct friends

    Level 2:
        Friends of friends

    Level 3:
        ...

So we can calculate the shortest distance from id to every person.

Then only consider:

    dist[i] == level


After identifying those people, count their watched videos.


Finally, sort using:

    frequency ascending

and:

    video name ascending


IMPORTANT POINT
---------------

The friendship graph is unweighted.

Therefore:

                    BFS

is sufficient.

We do NOT need:

    Dijkstra
    Floyd-Warshall
    DFS


======================================================================
PSEUDO CODE
======================================================================


Create:

    dist[n] = -1


Initialize:

    dist[id] = 0
    queue = {id}


BFS:

    while queue is not empty:

        curr = queue.front()
        queue.pop()

        for every friend next:

            if dist[next] == -1:

                dist[next] =
                    dist[curr] + 1

                push next


Now count videos:

    for every person i:

        if dist[i] == level:

            for every video:

                frequency[video]++


Create:

    (frequency, video)


Sort pairs.

Because pair<int, string> uses lexicographical comparison,
sorting naturally gives:

    frequency ascending
    then video name ascending


Return only video names.


======================================================================
COMPLETE OPTIMAL CODE
======================================================================

class Solution {
public:
    vector<string> watchedVideosByFriends(
        vector<vector<string>>& watchedVideos,
        vector<vector<int>>& friends,
        int id,
        int level
    ) {

        int n = friends.size();

        vector<int> dist(n, -1);
        queue<int> q;

        q.push(id);
        dist[id] = 0;

        while (!q.empty()) {

            int curr = q.front();
            q.pop();

            for (int next : friends[curr]) {

                if (dist[next] == -1) {

                    dist[next] = dist[curr] + 1;
                    q.push(next);
                }
            }
        }

        map<string, int> freq;

        for (int i = 0; i < n; ++i) {

            if (dist[i] == level) {

                for (string& video : watchedVideos[i]) {
                    freq[video]++;
                }
            }
        }

        vector<pair<int, string>> videos;

        for (auto& [video, count] : freq) {
            videos.push_back({count, video});
        }

        sort(videos.begin(), videos.end());

        vector<string> ans;

        for (auto& [count, video] : videos) {
            ans.push_back(video);
        }

        return ans;
    }
};


TIME COMPLEXITY
----------------

BFS:

    O(N + E)


Let:

    W = total number of watched-video entries
    V = number of distinct videos


Counting:

    O(W)


Sorting:

    O(V log V)


Total:

    O(N + E + W + V log V)


SPACE COMPLEXITY
----------------

Distance array:

    O(N)

Queue:

    O(N)

Frequency map:

    O(V)

Answer:

    O(V)


Total:

    O(N + V)


======================================================================
DRY RUN WITH EXAMPLE
======================================================================


Input:

    watchedVideos = {
        {"A", "B"},
        {"C"},
        {"B", "C"},
        {"D"}
    }

    friends = {
        {1, 2},
        {0, 3},
        {0, 3},
        {1, 2}
    }

    id = 0
    level = 1


INITIAL STATE
-------------

Distance:

    [0, -1, -1, -1]


Queue:

    [0]


STEP 1
------

Pop:

    0


Friends of 0:

    1
    2


Set:

    dist[1] = 1
    dist[2] = 1


Queue:

    [1, 2]


Distance:

    [0, 1, 1, -1]


STEP 2
------

Pop:

    1

Friend:

    0 -> already visited

Friend:

    3 -> unvisited

Set:

    dist[3] = 2


Queue:

    [2, 3]


STEP 3
------

Pop:

    2

Friends:

    0 -> already visited
    3 -> already visited


Final distances:

    Person 0 -> 0
    Person 1 -> 1
    Person 2 -> 1
    Person 3 -> 2


We need:

    level = 1


Therefore target people:

    1
    2


VIDEOS OF PERSON 1
------------------

    C


Frequency:

    C -> 1


VIDEOS OF PERSON 2
------------------

    B
    C


Updated frequency:

    B -> 1
    C -> 2


Sort by frequency:

    B -> 1
    C -> 2


Answer:

    {"B", "C"}


======================================================================
INTERVIEW NOTES
======================================================================


PATTERN
-------

Graph BFS + Frequency Map + Sorting


KEY OBSERVATION
---------------

The friendship network is an unweighted graph.

We need people exactly 'level' edges away.

Therefore:

                    BFS


is the natural choice.


SECOND KEY OBSERVATION
----------------------

After BFS, we only care about:

    dist[i] == level


Then aggregate videos using a frequency map.


THIRD KEY OBSERVATION
---------------------

The sorting rule is:

    1. Frequency ascending
    2. Name lexicographically ascending


Using:

    pair<int, string>

and normal:

    sort()

automatically gives exactly this order.


COMMON MISTAKES
---------------

1. Using DFS to find the level.

   DFS does not naturally give shortest distance in an unweighted
   graph.


2. Forgetting to mark the starting person as visited.


3. Counting videos from all friends instead of only friends at the
   required level.


4. Sorting only by frequency.

   The problem also requires lexicographical ordering when
   frequencies are equal.


5. Sorting by video name first.

   Frequency has higher priority.


6. Including videos watched by the original person.

   We only count videos from people at the requested level.


7. Visiting the same person multiple times.

   Use a distance/visited array.


8. Confusing:

       level 0

   with:

       level 1

   Level 0 is the person themselves.


======================================================================
WHEN TO USE THIS APPROACH
======================================================================


Use this approach when:

    - The data forms an unweighted graph.
    - You need nodes at an exact distance.
    - You need shortest number of edges.
    - Relationships are represented using adjacency lists.


Typical problems:

    - Friends at K distance
    - Nodes at K distance
    - Shortest path in unweighted graph
    - Level-order graph traversal
    - Social network problems
    - Minimum number of connections
    - Word ladder style problems


GENERAL BFS TEMPLATE
--------------------

    vector<int> dist(n, -1);

    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {

        int curr = q.front();
        q.pop();

        for (int next : graph[curr]) {

            if (dist[next] == -1) {

                dist[next] =
                    dist[curr] + 1;

                q.push(next);
            }
        }
    }


Then:

    if (dist[i] == requiredLevel)

process node i.


======================================================================
ONE-LINE INTERVIEW EXPLANATION
======================================================================

"This is an unweighted graph, so I use BFS from the given person
to calculate the shortest distance to every friend. I then consider
only people at the required level, count their watched videos, and
sort by frequency followed by lexicographical order."


======================================================================
FINAL PATTERN
======================================================================

            UNWEIGHTED GRAPH
                    |
                    v
                   BFS
                    |
                    v
          Find exact LEVEL nodes
                    |
                    v
             Frequency Map
                    |
                    v
             Sort by:
       frequency -> name
                    |
                    v
                 ANSWER

======================================================================
*/
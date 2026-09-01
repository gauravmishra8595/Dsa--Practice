#include <bits/stdc++.h>
using namespace std;

// LeetCode 815: Bus Routes
class Solution
{
public:
    int numBusesToDestination(
        vector<vector<int>> &routes,
        int source,
        int target)
    {
        if (source == target)
            return 0;

        int n = routes.size();

        // stop -> list of buses passing through this stop
        unordered_map<int, vector<int>> stopToBuses;

        for (int bus = 0; bus < n; ++bus)
        {
            for (int stop : routes[bus])
            {
                stopToBuses[stop].push_back(bus);
            }
        }

        // BFS on bus routes.
        // Each BFS level represents taking one more bus.
        queue<int> q;
        vector<bool> visitedBus(n, false);
        unordered_set<int> visitedStop;

        q.push(source);
        visitedStop.insert(source);

        int busesTaken = 0;

        while (!q.empty())
        {
            int sz = q.size();
            ++busesTaken;

            while (sz--)
            {
                int stop = q.front();
                q.pop();

                for (int bus : stopToBuses[stop])
                {
                    if (visitedBus[bus])
                        continue;

                    visitedBus[bus] = true;

                    for (int nextStop : routes[bus])
                    {
                        if (nextStop == target)
                            return busesTaken;

                        if (!visitedStop.count(nextStop))
                        {
                            visitedStop.insert(nextStop);
                            q.push(nextStop);
                        }
                    }
                }
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;

    vector<vector<int>> routes = {
        {1, 2, 7},
        {3, 6, 7}};

    int source = 1;
    int target = 6;

    cout << sol.numBusesToDestination(
                routes,
                source,
                target)
         << '\n';

    return 0;
}

/*
======================================================================
                       LEETCODE 815
                         BUS ROUTES
======================================================================


PROBLEM STATEMENT
-----------------

You are given several bus routes.

Each:

    routes[i]

represents the sequence of stops visited by bus i.

You are given:

    source
    target

You need to travel from source to target using buses.

Return the minimum number of buses required.

If it is impossible to reach target:

    return -1.


IMPORTANT:

The answer counts the number of BUSES taken, not the number of
stops traveled.


======================================================================
EXAMPLE
======================================================================

Input:

    routes = {
        {1, 2, 7},
        {3, 6, 7}
    }

    source = 1
    target = 6


Bus 0:

    1 -> 2 -> 7


Bus 1:

    3 -> 6 -> 7


Starting from:

    1


Take Bus 0:

    1 -> 2 -> 7


At stop 7, we can change to Bus 1.

Take Bus 1:

    7 -> 3 -> 6


Therefore:

    Minimum buses = 2


Output:

    2


======================================================================
BRUTE FORCE APPROACH
======================================================================


IDEA
----

A direct approach is to construct a graph where every bus stop is a
node.

Two stops are connected if they appear on the same bus route.

Then we can run BFS from source to target.

However, there is an important issue.

The problem asks for the minimum NUMBER OF BUSES, not the minimum
number of stops.

If we treat every stop-to-stop movement as cost 1, BFS would minimize
the number of stops instead of the number of buses.

We can still solve it by explicitly considering bus changes and
keeping track of which buses have been used.

A state can be:

    (stop, set of buses used)

But this creates a very large state space.

Another brute-force formulation is to try all possible sequences
of buses.

This can become exponential.


PSEUDO CODE
-----------

DFS(stop, usedBuses):

    if stop == target:
        return number of buses used

    for every bus containing stop:

        if bus has not been used:

            mark bus used

            visit every stop of that bus

            recursively continue

            unmark bus


Return the minimum result.


COMPLETE BRUTE FORCE CODE
-------------------------

// class Solution {
//     int ans = INT_MAX;
//
//     void dfs(
//         int stop,
//         int target,
//         vector<vector<int>>& routes,
//         vector<vector<int>>& stopToBuses,
//         vector<bool>& usedBus,
//         int buses
//     ) {
//
//         if (stop == target) {
//             ans = min(ans, buses);
//             return;
//         }
//
//         if (buses >= ans)
//             return;
//
//         for (int bus : stopToBuses[stop]) {
//
//             if (usedBus[bus])
//                 continue;
//
//             usedBus[bus] = true;
//
//             for (int nextStop : routes[bus]) {
//
//                 dfs(
//                     nextStop,
//                     target,
//                     routes,
//                     stopToBuses,
//                     usedBus,
//                     buses + 1
//                 );
//             }
//
//             usedBus[bus] = false;
//         }
//     }
//
// public:
//     int numBusesToDestination(
//         vector<vector<int>>& routes,
//         int source,
//         int target
//     ) {
//
//         if (source == target)
//             return 0;
//
//         int maxStop = 1000000;
//
//         vector<vector<int>> stopToBuses(maxStop);
//
//         for (int bus = 0; bus < routes.size(); ++bus) {
//
//             for (int stop : routes[bus]) {
//                 stopToBuses[stop].push_back(bus);
//             }
//         }
//
//         vector<bool> usedBus(routes.size(), false);
//
//         ans = INT_MAX;
//
//         dfs(
//             source,
//             target,
//             routes,
//             stopToBuses,
//             usedBus,
//             0
//         );
//
//         return ans == INT_MAX ? -1 : ans;
//     }
// };


TIME COMPLEXITY
----------------

In the worst case, DFS may try many combinations of buses.

If there are B buses, the number of possible bus sequences can be
exponential.

Worst-case complexity is approximately:

    O(B!)

or exponential depending on the graph structure.


SPACE COMPLEXITY
----------------

Recursion depth:

    O(B)

Visited bus array:

    O(B)

Therefore approximately:

    O(B)


This approach is not suitable for the constraints.


======================================================================
OPTIMAL APPROACH
======================================================================


OBSERVATION
-----------

We want to minimize:

                    NUMBER OF BUSES


not:

                    NUMBER OF STOPS


Suppose we are currently at stop 7.

If Bus 0 and Bus 1 both contain stop 7, we can switch between them
at the same stop.


This suggests building an implicit graph:

    STOP
      |
      v
    BUS
      |
      v
    STOPS ON THAT BUS


The key is to perform BFS where:

                    ONE BFS LEVEL = ONE BUS


Therefore, whenever we take a new bus, the BFS distance increases
by exactly 1.


INTUITION
---------

First create:

    stopToBuses[stop]

which tells us all buses that pass through a particular stop.


Example:

    routes = {
        {1, 2, 7},
        {3, 6, 7}
    }


Then:

    stopToBuses[1] = {0}
    stopToBuses[2] = {0}
    stopToBuses[7] = {0, 1}
    stopToBuses[3] = {1}
    stopToBuses[6] = {1}


Start BFS from:

    source


When we are at a stop, we can take any bus that passes through it.

Once we take a bus, all stops on that bus become reachable using
one additional bus.


We process each bus only once.

This is important for efficiency.


WHY VISITED BUS?
----------------

Suppose we reach stop 7 multiple times.

Bus 1 may be available from stop 7.

There is no reason to process Bus 1 repeatedly.

The first time we process a bus in BFS, we are processing it using
the minimum number of buses possible.

Therefore:

    visitedBus[bus] = true

after processing it once.


WHY VISITED STOP?
-----------------

A stop does not need to be added to the queue repeatedly.

The first time we reach a stop, it is reachable using the minimum
number of buses because BFS explores level by level.


======================================================================
PSEUDO CODE
-----------


If:

    source == target

return:

    0


Build:

    stopToBuses


For every bus:

    for every stop on that bus:

        stopToBuses[stop].push_back(bus)


Initialize:

    queue = {source}

    visitedBus = false

    visitedStop[source] = true

    busesTaken = 0


BFS:

while queue is not empty:

    process all stops of current level

    busesTaken++


    for each current stop:

        for every bus containing current stop:

            if bus already visited:
                continue

            mark bus visited


            for every stop on this bus:

                if stop == target:
                    return busesTaken

                if stop not visited:

                    mark stop visited
                    push stop


return -1


======================================================================
COMPLETE OPTIMAL CODE
---------------------

// class Solution {
// public:
//     int numBusesToDestination(
//         vector<vector<int>>& routes,
//         int source,
//         int target
//     ) {
//
//         if (source == target)
//             return 0;
//
//         int n = routes.size();
//
//         unordered_map<int, vector<int>> stopToBuses;
//
//         for (int bus = 0; bus < n; ++bus) {
//
//             for (int stop : routes[bus]) {
//                 stopToBuses[stop].push_back(bus);
//             }
//         }
//
//         queue<int> q;
//
//         vector<bool> visitedBus(
//             n,
//             false
//         );
//
//         unordered_set<int> visitedStop;
//
//         q.push(source);
//         visitedStop.insert(source);
//
//         int busesTaken = 0;
//
//         while (!q.empty()) {
//
//             int sz = q.size();
//
//             ++busesTaken;
//
//             while (sz--) {
//
//                 int stop = q.front();
//                 q.pop();
//
//                 for (int bus : stopToBuses[stop]) {
//
//                     if (visitedBus[bus])
//                         continue;
//
//                     visitedBus[bus] = true;
//
//                     for (int nextStop : routes[bus]) {
//
//                         if (nextStop == target)
//                             return busesTaken;
//
//                         if (!visitedStop.count(nextStop)) {
//
//                             visitedStop.insert(nextStop);
//
//                             q.push(nextStop);
//                         }
//                     }
//                 }
//             }
//         }
//
//         return -1;
//     }
// };


TIME COMPLEXITY
----------------

Let:

    B = number of bus routes

Let:

    S = total number of stops across all routes

That means:

    S = sum of routes[i].size()


We process every bus at most once.

When a bus is processed, we iterate through all stops on that bus.

Therefore, the total work for processing routes is:

    O(S)


We also process stop-to-bus relationships.

Those relationships contain exactly S entries.

Therefore:

    O(S)


Overall:

    O(S)


where:

    S = total number of stops in all bus routes.


SPACE COMPLEXITY
----------------

stopToBuses contains:

    O(S)


visitedBus:

    O(B)


visitedStop:

    O(S)


queue:

    O(S)


Therefore:

    O(S + B)


Since B <= S for non-empty routes, this is commonly written as:

    O(S)


======================================================================
DRY RUN WITH EXAMPLE
======================================================================


Input:

    routes = {
        {1, 2, 7},
        {3, 6, 7}
    }

    source = 1
    target = 6


BUS MAP
-------

Stop 1:

    Bus 0


Stop 2:

    Bus 0


Stop 7:

    Bus 0, Bus 1


Stop 3:

    Bus 1


Stop 6:

    Bus 1


INITIAL STATE
-------------

Queue:

    [1]


Visited stops:

    {1}


Buses taken:

    0


STEP 1
------

Current BFS level contains:

    1


We need to take one bus.

Therefore:

    busesTaken = 1


Stop 1 belongs to:

    Bus 0


Bus 0 has not been visited.


Mark:

    visitedBus[0] = true


Stops on Bus 0:

    1
    2
    7


Stop 1:

    already visited


Stop 2:

    add to queue


Stop 7:

    add to queue


Queue:

    [2, 7]


Visited stops:

    {1, 2, 7}


STEP 2
------

Current level:

    2, 7


We are now considering taking another bus.

Therefore:

    busesTaken = 2


Stop 2 belongs to:

    Bus 0


Bus 0 already processed.


Skip.


Now process stop 7.


Stop 7 belongs to:

    Bus 0
    Bus 1


Bus 0:

    already processed


Bus 1:

    not processed


Mark:

    visitedBus[1] = true


Stops on Bus 1:

    3
    6
    7


We find:

    6 == target


Therefore:

    return 2


ANSWER:

    2


======================================================================
WHY THE BFS LEVEL REPRESENTS NUMBER OF BUSES
======================================================================


This is the most important part of the problem.


Initial:

    source

We have taken:

    0 buses


From source, taking one route gives:

    1 bus


From any stop reached after one bus, taking another route gives:

    2 buses


Therefore:

    BFS Level 0 -> source
    BFS Level 1 -> 1 bus
    BFS Level 2 -> 2 buses
    BFS Level 3 -> 3 buses
    ...


So the first time we reach target, we have the minimum number
of buses.


======================================================================
INTERVIEW NOTES
======================================================================


PATTERN
-------

BFS + Graph Compression / Implicit Graph


KEY OBSERVATION
---------------

We are NOT minimizing the number of stops.

We are minimizing:

                    number of buses


Therefore, each BFS level should represent:

                    one bus taken.


The useful mapping is:

    stop -> buses passing through stop


This allows us to switch between buses at common stops.


SECOND KEY OBSERVATION
----------------------

A bus should be processed only once.

If we have already processed a bus using fewer or equal buses,
processing the same route again cannot improve the answer.


Therefore:

    visitedBus[bus]


is essential.


THIRD KEY OBSERVATION
---------------------

A stop should also be processed only once.

The first BFS visit to a stop is the shortest number of buses
required to reach it.


Therefore:

    visitedStop[stop]


prevents duplicate queue entries.


COMMON MISTAKES
---------------

1. Running BFS directly between individual stops and counting
   stop-to-stop moves.

   That minimizes stops, not buses.


2. Forgetting the special case:

       source == target

   Answer is:

       0


3. Not mapping:

       stop -> buses


4. Processing the same bus multiple times.

   This can make the solution much slower.


5. Marking buses incorrectly.

   A bus should be marked visited when we decide to process it.


6. Returning the number of stops instead of the number of buses.


7. Using DFS for a minimum-bus problem.

   BFS is the correct shortest-path technique here.


8. Building every possible stop-to-stop edge explicitly.

   This can create a very large graph.

   The stop-to-bus mapping is much cleaner.


======================================================================
WHEN TO USE THIS APPROACH
======================================================================


Use this approach when:

    - You need a minimum number of transfers.
    - Objects belong to multiple groups.
    - Moving through a group gives access to all its members.
    - You need to minimize the number of groups used.


Examples:

    - Bus Routes
    - Minimum number of flights
    - Minimum transfers
    - Train lines
    - Subway routes
    - Social groups
    - Courses sharing prerequisites/resources
    - Any problem involving "switching between routes"


GENERAL PATTERN
---------------


        SOURCE STOP
             |
             v
      Buses containing it
             |
             v
       All stops on bus
             |
             v
      Buses containing
       those stops
             |
             v
       Continue BFS


Think of it as:

    STOP -> BUS -> STOP -> BUS -> STOP


But instead of explicitly creating the bipartite graph,
we use:

    stopToBuses


and process each bus only once.


======================================================================
ALTERNATIVE WAY TO VISUALIZE THE GRAPH
======================================================================


We can imagine a bipartite graph:


          STOP 1
             |
             v
          BUS 0
         /  |  \
        v   v   v
      STOP2 STOP7 STOP1
               |
               v
             BUS 1
            /  |  \
           v   v   v
        STOP3 STOP6 STOP7


Each bus transition costs:

    1


Therefore BFS finds the minimum number of buses.


======================================================================
ONE-LINE INTERVIEW EXPLANATION
======================================================================

"I use BFS where each level represents taking one additional bus.
I map every stop to the buses passing through it, process each bus
only once, and expand all stops on that bus. The first time I reach
the target gives the minimum number of buses."


======================================================================
FINAL TEMPLATE TO REMEMBER
======================================================================


            MINIMUM BUSES
                  |
                  v
                 BFS
                  |
                  v
        stop -> list of buses
                  |
                  v
        take one unvisited bus
                  |
                  v
       all stops on that bus
                  |
                  v
             next BFS level
                  |
                  v
              TARGET


KEY FORMULA:

    BFS LEVEL = NUMBER OF BUSES TAKEN


KEY DATA STRUCTURES:

    unordered_map<int, vector<int>> stopToBuses

    vector<bool> visitedBus

    unordered_set<int> visitedStop

    queue<int> q


======================================================================
*/
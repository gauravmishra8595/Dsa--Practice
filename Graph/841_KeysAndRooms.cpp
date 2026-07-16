#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> &rooms, vector<int> &visited, int room)
    {
        visited[room] = 1;

        for (int key : rooms[room])
        {
            if (!visited[key])
            {
                dfs(rooms, visited, key);
            }
        }
    }

    bool canVisitAllRooms(vector<vector<int>> &rooms)
    {
        int n = rooms.size();
        vector<int> visited(n, 0);

        dfs(rooms, visited, 0);

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
                return false;
        }

        return true;
    }
};

int main()
{
    Solution obj;

    vector<vector<int>> rooms = {
        {1},
        {2},
        {3},
        {}};

    cout << (obj.canVisitAllRooms(rooms) ? "true" : "false") << endl;

    return 0;
}

/*

===========================================
LeetCode 841. Keys and Rooms
===========================================

Problem Statement
-----------------
There are n rooms numbered from 0 to n-1.

Initially, all rooms are locked except room 0.

Each room contains keys to other rooms.

A key with number i unlocks room i.

Return true if you can visit every room,
otherwise return false.

--------------------------------------------------
Example
--------------------------------------------------

Input:
rooms = [[1],[2],[3],[]]

Output:
true

Explanation:

Start from room 0
Get key of room 1
Visit room 1
Get key of room 2
Visit room 2
Get key of room 3
Visit room 3

All rooms are visited.

==================================================
Brute Force Approach
==================================================

Idea
----
Keep checking every room repeatedly.

Whenever a new room becomes accessible,
visit it and continue until no new room can be visited.

Pseudo Code
-----------

visited[0] = true

repeat

    changed = false

    for every room

        if visited

            for every key

                if not visited

                    visited[key] = true
                    changed = true

until changed == false

check if every room visited

Complete Brute Force Code
-------------------------

class Solution {
public:

    bool canVisitAllRooms(vector<vector<int>>& rooms) {

        int n = rooms.size();

        vector<int> visited(n,0);

        visited[0]=1;

        bool changed=true;

        while(changed){

            changed=false;

            for(int i=0;i<n;i++){

                if(visited[i]){

                    for(int key:rooms[i]){

                        if(!visited[key]){

                            visited[key]=1;
                            changed=true;

                        }

                    }

                }

            }

        }

        for(int x:visited)

            if(!x)
                return false;

        return true;
    }
};

Time Complexity
---------------
O(N^2)

Space Complexity
----------------
O(N)

==================================================
Optimal Approach (DFS)
==================================================

Observation
-----------
Rooms and keys naturally form a graph.

Room -> Key means an edge.

We only need to know which rooms are reachable
starting from room 0.

Intuition
---------
Start DFS from room 0.

Whenever a key is found,
visit that room if it has not been visited.

After DFS finishes,
if every room has been visited,
answer is true.

Pseudo Code
-----------

visited[]

DFS(room)

    mark visited

    for every key

        if not visited

            DFS(key)

Start DFS from room 0

Check every room

Complete Optimal Code
---------------------

class Solution {
public:

    void dfs(vector<vector<int>>& rooms,
             vector<int>& visited,
             int room){

        visited[room]=1;

        for(int key:rooms[room]){

            if(!visited[key]){

                dfs(rooms,visited,key);

            }

        }

    }

    bool canVisitAllRooms(vector<vector<int>>& rooms){

        int n=rooms.size();

        vector<int> visited(n,0);

        dfs(rooms,visited,0);

        for(int x:visited)

            if(!x)
                return false;

        return true;
    }
};

Time Complexity
---------------
Each room is visited once.

Each key is processed once.

Overall:

O(V + E)

where

V = number of rooms

E = total number of keys

Space Complexity
----------------
Visited Array : O(V)

Recursion Stack : O(V)

Overall : O(V)

==================================================
Dry Run
==================================================

rooms =

0 -> {1}

1 -> {2}

2 -> {3}

3 -> {}

Initially

visited = [0,0,0,0]

DFS(0)

visited = [1,0,0,0]

Go to room 1

visited = [1,1,0,0]

Go to room 2

visited = [1,1,1,0]

Go to room 3

visited = [1,1,1,1]

DFS ends

All rooms visited

Answer = true

==================================================
Interview Notes
==================================================

Pattern
-------
Graph Traversal

Depth First Search (DFS)

Reachability

Connected Component

Key Observation
---------------
Treat every room as a node.

Treat every key as a directed edge.

If DFS from room 0 reaches every node,
then every room can be visited.

Common Mistakes
---------------
1. Forgetting to mark a room visited before recursion.

2. Visiting already visited rooms again.

3. Thinking graph is undirected.
   It is directed because keys only go one way.

4. Starting DFS from every room.
   Only room 0 is initially unlocked.

When to use this approach
-------------------------
1. Reachability in graphs.

2. Connected component problems.

3. Maze traversal.

4. Dependency traversal.

5. DFS/BFS based graph exploration.

*/
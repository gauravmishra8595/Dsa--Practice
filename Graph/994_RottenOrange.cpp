#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int, int>, int>> q;
        int fresh = 0;
        int ans = 0;

        // Push all rotten oranges into queue
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 2)
                {
                    q.push({{i, j}, 0});
                }
                else if (grid[i][j] == 1)
                {
                    fresh++;
                }
            }
        }

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.empty())
        {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            q.pop();

            ans = max(ans, t);

            for (int k = 0; k < 4; k++)
            {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1)
                {
                    grid[nr][nc] = 2;
                    fresh--;
                    q.push({{nr, nc}, t + 1});
                }
            }
        }

        return (fresh == 0) ? ans : -1;
    }
};

int main()
{
    Solution obj;

    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}};

    cout << obj.orangesRotting(grid);

    return 0;
}

/*

==========================
Problem Statement
==========================

You are given an m x n grid where:

0 -> Empty cell
1 -> Fresh Orange
2 -> Rotten Orange

Every minute, any fresh orange adjacent (up, down, left, right) to a rotten orange becomes rotten.

Return the minimum number of minutes required so that no fresh orange remains.
If impossible, return -1.

--------------------------------------------------

Example

Input:

2 1 1
1 1 0
0 1 1

Output:

4

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea

For every minute:

1. Traverse the entire grid.
2. Find all rotten oranges.
3. Mark their adjacent fresh oranges.
4. Update after completing traversal.
5. Repeat until no changes occur.

This repeatedly scans the entire grid.

Pseudo Code

while(changes occur)
{
    traverse entire grid

    for every rotten orange
        mark adjacent fresh oranges

    update grid

    minute++
}

if fresh orange exists
    return -1

return minute

--------------------------------------------------
Complete Brute Force Code
--------------------------------------------------

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        int minutes = 0;

        while(true){

            vector<pair<int,int>> temp;

            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++){

                    if(grid[i][j]==2){

                        int dr[4]={-1,0,1,0};
                        int dc[4]={0,1,0,-1};

                        for(int k=0;k<4;k++){

                            int nr=i+dr[k];
                            int nc=j+dc[k];

                            if(nr>=0 && nr<n && nc>=0 && nc<m && grid[nr][nc]==1)
                                temp.push_back({nr,nc});
                        }
                    }
                }
            }

            if(temp.empty())
                break;

            for(auto &it:temp)
                grid[it.first][it.second]=2;

            minutes++;
        }

        for(auto &row:grid)
            for(auto &x:row)
                if(x==1)
                    return -1;

        return minutes;
    }
};

Time Complexity

O((N*M)^2)

Space Complexity

O(N*M)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation

All rotten oranges start spreading simultaneously.

This is a classic Multi-Source BFS.

Instead of running BFS from one source, push all rotten oranges into the queue initially.

The first time a fresh orange is reached is the minimum possible time.

Pseudo Code

Push all rotten oranges into queue

Count fresh oranges

while(queue not empty)

    pop node

    update answer

    visit 4 neighbours

    if neighbour is fresh

        make rotten

        decrease fresh count

        push with time+1

if fresh oranges remain

    return -1

return answer

--------------------------------------------------
Complete Optimal Code
--------------------------------------------------

class Solution {
public:

    int orangesRotting(vector<vector<int>>& grid) {

        int n=grid.size();
        int m=grid[0].size();

        queue<pair<pair<int,int>,int>> q;

        int fresh=0;
        int ans=0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){

                if(grid[i][j]==2)
                    q.push({{i,j},0});

                else if(grid[i][j]==1)
                    fresh++;
            }
        }

        int dr[]={-1,0,1,0};
        int dc[]={0,1,0,-1};

        while(!q.empty()){

            int r=q.front().first.first;
            int c=q.front().first.second;
            int t=q.front().second;

            q.pop();

            ans=max(ans,t);

            for(int k=0;k<4;k++){

                int nr=r+dr[k];
                int nc=c+dc[k];

                if(nr>=0 && nr<n && nc>=0 && nc<m && grid[nr][nc]==1){

                    grid[nr][nc]=2;
                    fresh--;

                    q.push({{nr,nc},t+1});
                }
            }
        }

        if(fresh>0)
            return -1;

        return ans;
    }
};

Time Complexity

O(N*M)

Space Complexity

O(N*M)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input

2 1 1
1 1 0
0 1 1

Initially

Queue

(0,0,0)

Fresh = 6

Minute 0

Rot (0,1)
Rot (1,0)

Queue

(0,1,1)
(1,0,1)

Minute 1

Rot (0,2)
Rot (1,1)

Queue

(0,2,2)
(1,1,2)

Minute 2

Rot (2,1)

Queue

(2,1,3)

Minute 3

Rot (2,2)

Queue

(2,2,4)

Minute 4

No fresh oranges left

Answer = 4

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern

- Multi-Source BFS
- Matrix BFS
- Shortest Time Spread

Key Observation

All rotten oranges spread simultaneously.

So every rotten orange must be inserted into the queue before starting BFS.

Common Mistakes

1. Starting BFS from only one rotten orange.

2. Forgetting to mark orange rotten while pushing.

3. Using visited array unnecessarily.

4. Forgetting fresh orange count.

5. Updating answer incorrectly.

When to use this approach

Whenever:

- Multiple starting points
- Infection spread
- Fire spread
- Rotten oranges
- Nearest source
- Minimum time to spread

Classic Problems

- Rotten Oranges
- Walls and Gates
- 01 Matrix
- Fire Spread
- Zombie Infection
- Multi Source Shortest Distance

*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int dir[5] = {-1, 0, 1, 0, -1};

public:
    int minMoves(vector<string> &classroom, int energy)
    {
        int m = classroom.size();    
        int n = classroom[0].size(); 

        int stx, sty;
        int trash = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (classroom[i][j] == 'S')
                {
                    stx = i;
                    sty = j;
                }
                else if (classroom[i][j] == 'L')
                {
                    classroom[i][j] = '0' + trash;
                    ++trash;
                }
            }
        }
        if (trash == 0)
            return 0;

        int bitMax = (1 << trash) - 1;
        int maxEng[20][20][1024];
        memset(maxEng, -1, sizeof(maxEng));
        queue<tuple<int, int, int, int>> q;

        q.push({stx, sty, energy, 0});
        maxEng[stx][sty][0] = energy;

        int step = 0;

        while (!q.empty())
        {
            int sz = q.size();
            for (int run = 0; run < sz; ++run)
            {
                auto [x, y, en, mask] = q.front();
                q.pop();

        
                if (mask == bitMax)
                    return step;
                if (en == 0)
                    continue;

                for (int i = 0; i < 4; ++i)
                {
                    int nextX = x + dir[i];
                    int nextY = y + dir[i + 1];

                    // Outside grid or wall.
                    if (nextX < 0 || nextX >= m ||
                        nextY < 0 || nextY >= n ||
                        classroom[nextX][nextY] == 'X')
                    {
                        continue;
                    }
                    int nextEn = en - 1;
                    int nextMask = mask;
                    if (classroom[nextX][nextY] == 'R')
                    {
                        nextEn = energy;
                    }
                    else if (classroom[nextX][nextY] <= '9' &&
                             classroom[nextX][nextY] >= '0')
                    {

                        nextMask |=
                            1 << (classroom[nextX][nextY] - '0');
                    }
                    if (maxEng[nextX][nextY][nextMask] < nextEn)
                    {
                        maxEng[nextX][nextY][nextMask] = nextEn;
                        q.push({nextX,
                                nextY,
                                nextEn,
                                nextMask});
                    }
                }
            }

            ++step;
        }

        return -1;
    }
};

int main()
{
    Solution sol;

    vector<string> classroom = {
        "S.",
        ".L"};

    int energy = 2;

    cout << sol.minMoves(classroom, energy) << '\n';

    return 0;
}

/*
======================================================================
                    LEETCODE 3568
             MINIMUM MOVES TO CLEAN THE CLASSROOM
======================================================================


PROBLEM STATEMENT
-----------------

You are given a grid representing a classroom.

The grid contains:

    'S' -> Starting position
    'L' -> Litter that needs to be cleaned
    'R' -> Recharge station
    'X' -> Wall / blocked cell
    '.' -> Empty cell

You are initially at 'S' with a given amount of energy.

Rules:

1. Moving to an adjacent cell costs exactly 1 unit of energy.

2. You cannot move when your energy becomes 0.

3. Whenever you enter a cell containing 'L', that litter is cleaned.

4. Whenever you enter a cell containing 'R', your energy becomes
   equal to the initial energy.

5. You can move in four directions:
       Up
       Down
       Left
       Right

Return the minimum number of moves required to clean all litter.

If it is impossible to clean all litter, return -1.


CONSTRAINTS
-----------

    1 <= m, n <= 20

The number of litter cells is small enough to represent their
cleaned/not-cleaned status using a bitmask.


======================================================================
EXAMPLE
======================================================================

Example:

    classroom = {
        "S.",
        ".L"
    }

    energy = 2


Grid:

    S .
    . L


Start:

    S

Possible shortest path:

    S -> . -> L


Move 1:
    S -> .

    Energy = 1

Move 2:
    . -> L

    Energy = 0
    Litter is cleaned.


Answer:

    2


======================================================================
BRUTE FORCE APPROACH
======================================================================


IDEA
----

Try all possible paths using DFS.

A state needs to remember:

    1. Current row
    2. Current column
    3. Current energy
    4. Which litter cells have been cleaned

The cleaned litter cells can be represented using a bitmask.

For example, if there are 3 litter cells:

    000 -> no litter cleaned
    001 -> litter 0 cleaned
    010 -> litter 1 cleaned
    100 -> litter 2 cleaned
    111 -> all litter cleaned

A naive DFS may revisit the same state many times.

Therefore, memoization can be used.


PSEUDO CODE
-----------

dfs(x, y, energy, mask):

    if all litter is cleaned:
        return 0

    if state is already calculated:
        return memo[state]

    answer = INF

    for each of 4 directions:

        calculate next cell

        if outside grid:
            continue

        if next cell is wall:
            continue

        if energy == 0:
            continue

        nextEnergy = energy - 1
        nextMask = mask

        if next cell is litter:
            add its bit to nextMask

        if next cell is recharge:
            nextEnergy = initialEnergy

        answer =
            min(answer,
                1 + dfs(nextX, nextY,
                         nextEnergy, nextMask))

    return answer


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
    int dir[5] = {-1, 0, 1, 0, -1};
    int m, n, initialEnergy, trash;

    vector<vector<int>> id;

    // memo[x][y][energy][mask]
    vector<vector<vector<vector<int>>>> memo;

    const int INF = 1e9;

    int dfs(int x, int y, int en, int mask,
            vector<string>& classroom) {

        if (mask == (1 << trash) - 1)
            return 0;

        int &ans = memo[x][y][en][mask];

        if (ans != -1)
            return ans;

        ans = INF;

        for (int i = 0; i < 4; ++i) {

            int nx = x + dir[i];
            int ny = y + dir[i + 1];

            if (nx < 0 || nx >= m ||
                ny < 0 || ny >= n)
                continue;

            if (classroom[nx][ny] == 'X')
                continue;

            if (en == 0)
                continue;

            int nextEn = en - 1;
            int nextMask = mask;

            if (classroom[nx][ny] == 'R') {
                nextEn = initialEnergy;
            }
            else if (classroom[nx][ny] >= '0' &&
                     classroom[nx][ny] <= '9') {

                int idx = classroom[nx][ny] - '0';
                nextMask |= (1 << idx);
            }

            int sub = dfs(
                nx,
                ny,
                nextEn,
                nextMask,
                classroom
            );

            if (sub != INF)
                ans = min(ans, 1 + sub);
        }

        return ans;
    }

public:
    int minMoves(vector<string>& classroom, int energy) {

        m = classroom.size();
        n = classroom[0].size();
        initialEnergy = energy;

        int sx = 0, sy = 0;
        trash = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                else if (classroom[i][j] == 'L') {
                    classroom[i][j] = '0' + trash;
                    ++trash;
                }
            }
        }

        if (trash == 0)
            return 0;

        memo.assign(
            m,
            vector<vector<vector<int>>>(
                n,
                vector<vector<int>>(
                    energy + 1,
                    vector<int>(1 << trash, -1)
                )
            )
        );

        int ans = dfs(
            sx,
            sy,
            energy,
            0,
            classroom
        );

        return ans == INF ? -1 : ans;
    }
};


TIME COMPLEXITY
----------------

Number of possible states:

    O(m * n * energy * 2^L)

where:

    m = number of rows
    n = number of columns
    energy = maximum energy
    L = number of litter cells

Each state tries 4 directions.

Therefore:

    O(m * n * energy * 2^L)


SPACE COMPLEXITY
----------------

Memoization stores:

    O(m * n * energy * 2^L)

states.

Therefore:

    O(m * n * energy * 2^L)

There is also recursion stack space.


======================================================================
OPTIMAL APPROACH
======================================================================


OBSERVATION
-----------

This is fundamentally a shortest-path problem.

Every movement costs exactly 1.

Therefore:

                    BFS

is the natural shortest-path algorithm.


However, position alone is NOT enough to describe a state.

Suppose we reach the same cell twice.

The two visits may have:

    Different remaining energy

or

    Different litter already cleaned

Therefore, the state must contain:

    (x, y, energy, mask)


INTUITION
---------

We use BFS because every movement has cost 1.

BFS processes states level by level:

    level 0 -> 0 moves
    level 1 -> 1 move
    level 2 -> 2 moves
    ...

Therefore, when we first find:

    mask == bitMax

we have found the minimum number of moves.


BITMASK
--------

Every litter gets a unique bit.

Suppose there are 4 litter cells:

    L0 -> bit 0
    L1 -> bit 1
    L2 -> bit 2
    L3 -> bit 3

Then:

    0000 -> nothing cleaned
    0001 -> L0 cleaned
    0011 -> L0, L1 cleaned
    1111 -> all cleaned


WHY maxEng INSTEAD OF visited?
------------------------------

A normal BFS would store:

    visited[x][y][energy][mask]

But we can do better.

For a fixed:

    (x, y, mask)

suppose we have already reached it with energy = 7.

Later, if we reach the same:

    (x, y, mask)

with energy = 5,

the second state is useless.

Why?

Because having more energy is always at least as good as having
less energy.

From energy 7, we can perform everything possible from energy 5,
and potentially more.

Therefore we store only:

    maximum energy seen for (x, y, mask)


This is the key optimization.


DOMINANCE RULE
--------------

For the same:

    (x, y, mask)

if:

    previousEnergy >= newEnergy

then discard the new state.


Otherwise:

    update maxEng[x][y][mask]
    push the new state into BFS.


PSEUDO CODE
-----------

Find starting position.

Convert every litter cell into a unique index:

    L -> '0'
    L -> '1'
    L -> '2'
    ...


bitMax = (1 << numberOfLitter) - 1


Initialize:

    maxEng[startX][startY][0] = initialEnergy

Push:

    (startX, startY, initialEnergy, 0)


BFS:

while queue is not empty:

    process all states at current BFS level

    for every state:

        if mask == bitMax:
            return currentStep

        if energy == 0:
            continue

        try all 4 directions:

            if outside grid:
                continue

            if wall:
                continue

            nextEnergy = energy - 1
            nextMask = mask

            if next cell is recharge:
                nextEnergy = initialEnergy

            if next cell is litter:
                add its bit to nextMask

            if maxEng[nextX][nextY][nextMask]
               < nextEnergy:

                update maxEng

                push new state

    step++


return -1


COMPLETE OPTIMAL CODE
---------------------

class Solution {
    int dir[5] = {-1, 0, 1, 0, -1};

public:
    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        int stx, sty;
        int trash = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {

                if (classroom[i][j] == 'S') {
                    stx = i;
                    sty = j;
                }
                else if (classroom[i][j] == 'L') {
                    classroom[i][j] = '0' + trash;
                    ++trash;
                }
            }
        }

        if (trash == 0)
            return 0;

        int bitMax = (1 << trash) - 1;

        int maxEng[20][20][1024];
        memset(maxEng, -1, sizeof(maxEng));

        queue<tuple<int, int, int, int>> q;

        q.push({
            stx,
            sty,
            energy,
            0
        });

        maxEng[stx][sty][0] = energy;

        int step = 0;

        while (!q.empty()) {

            int sz = q.size();

            for (int run = 0; run < sz; ++run) {

                auto [x, y, en, mask] = q.front();
                q.pop();

                if (mask == bitMax)
                    return step;

                if (en == 0)
                    continue;

                for (int i = 0; i < 4; ++i) {

                    int nextX = x + dir[i];
                    int nextY = y + dir[i + 1];

                    if (nextX < 0 || nextX >= m ||
                        nextY < 0 || nextY >= n ||
                        classroom[nextX][nextY] == 'X') {

                        continue;
                    }

                    int nextEn = en - 1;
                    int nextMask = mask;

                    if (classroom[nextX][nextY] == 'R') {

                        nextEn = energy;

                    }
                    else if (classroom[nextX][nextY] >= '0' &&
                             classroom[nextX][nextY] <= '9') {

                        nextMask |=
                            1 << (classroom[nextX][nextY] - '0');
                    }

                    if (maxEng[nextX][nextY][nextMask] < nextEn) {

                        maxEng[nextX][nextY][nextMask] = nextEn;

                        q.push({
                            nextX,
                            nextY,
                            nextEn,
                            nextMask
                        });
                    }
                }
            }

            ++step;
        }

        return -1;
    }
};


TIME COMPLEXITY
----------------

There are at most:

    O(m * n * 2^L)

position + mask combinations.

For each combination, we may keep improving the maximum energy.

The bounded energy dimension gives the overall worst-case:

    O(m * n * energy * 2^L)

Each state checks 4 directions, which is a constant factor.

Therefore:

    O(m * n * energy * 2^L)


SPACE COMPLEXITY
----------------

The main memory structures are:

    maxEng[20][20][1024]

and the BFS queue.

Therefore:

    O(m * n * 2^L)

for the dominance table, plus queue space.

The fixed-size implementation uses:

    20 * 20 * 1024

integer entries.


======================================================================
DRY RUN WITH EXAMPLE
======================================================================


Example:

    classroom = {
        "S.",
        ".L"
    }

    energy = 2


Step 0
------

Position:

    S

Energy:

    2

Mask:

    0

Binary mask:

    0

Queue:

    (S, 2, 0)


Possible moves:

    S -> top/right '.'
    S -> bottom/left '.'


After one move:

    Energy = 1
    Mask   = 0
    Step   = 1


Step 1
------

Suppose BFS chooses:

    S -> .

State:

    Position = .
    Energy   = 1
    Mask     = 0


Move to L:

    nextEnergy = 1 - 1
               = 0

Litter index:

    0

So:

    nextMask = 0 | (1 << 0)
             = 1


New state:

    Position = L
    Energy   = 0
    Mask     = 1


Step 2
------

Check:

    mask == bitMax

Here:

    trash = 1

Therefore:

    bitMax = (1 << 1) - 1
           = 1


We have:

    mask = 1

So all litter has been cleaned.


Answer:

    2


======================================================================
INTERVIEW NOTES
======================================================================


PATTERN
-------

Grid BFS + Bitmask + Resource State + Dominance Optimization


KEY OBSERVATION
---------------

The most important observation is:

    Same position + same cleaned-mask

does NOT require keeping every energy value.

Only the maximum energy matters.

If we have:

    (x, y, mask, energy = 8)

then:

    (x, y, mask, energy = 5)

is dominated and can be ignored.


COMMON MISTAKES
---------------

1. Using only:

       visited[x][y]

   This is incorrect because energy and cleaned litter matter.


2. Using only:

       visited[x][y][mask]

   This can also be insufficient because reaching the same state
   with more remaining energy is better.


3. Forgetting to subtract energy before entering the next cell.


4. Refilling energy incorrectly.

   Correct behavior:

       nextEnergy = currentEnergy - 1

   and then if the destination is 'R':

       nextEnergy = initialEnergy


5. Forgetting to update the litter bit when entering 'L'.


6. Using DFS without handling repeated states.


7. Not using BFS when every movement costs exactly 1.


8. Returning when a litter is found instead of when ALL litter
   has been cleaned.


9. Forgetting the special case:

       trash == 0

   In that case the answer is immediately 0.


10. Using an oversized multidimensional state without recognizing
    the dominance optimization.


======================================================================
WHEN TO USE THIS APPROACH
======================================================================

Use this approach when:

    - You have a grid.
    - Movement cost is uniform.
    - You need minimum number of moves.
    - There are a small number of special objects.
    - You have an additional resource such as:
          energy
          fuel
          stamina
          keys
    - The set of collected/cleaned/visited objects can be represented
      using a bitmask.


Typical state:

    (position + resource + bitmask)


And if a state has a monotonic resource:

    Keep the best resource value for each
    (position + bitmask).


Common examples:

    - Collect all keys
    - Clean all litter
    - Visit all special cells
    - Collect all items
    - Grid with limited energy
    - Grid with recharge stations
    - Shortest path with a small set of required targets


FINAL TEMPLATE TO REMEMBER
--------------------------

For this type of problem, think:

    1. Is it shortest path?
           |
           +-- Yes -> BFS

    2. Do I need to remember collected objects?
           |
           +-- Yes -> Bitmask

    3. Is there an energy/resource value?
           |
           +-- Yes -> Include it in the state

    4. Can a larger resource value dominate a smaller one?
           |
           +-- Yes -> Store only the maximum resource value


Final state:

    (row, column, cleanedMask)

with:

    maxEng[row][column][cleanedMask]


This dominance optimization is the key idea behind the
given optimal implementation.

======================================================================
*/
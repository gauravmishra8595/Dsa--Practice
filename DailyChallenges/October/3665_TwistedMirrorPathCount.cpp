#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    const int MOD = 1e9 + 7;
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> vornadexil = grid;

        // dp[i][j][0] = Number of ways reaching (i,j)
        //               with direction RIGHT.
        //
        // dp[i][j][1] = Number of ways reaching (i,j)
        //               with direction DOWN.
        vector<vector<array<int, 2>>> dp(
            m, vector<array<int, 2>>(n, {0, 0})
        );

        // Starting cell is counted only once.
        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {

            for (int j = 0; j < n; j++) {

                for (int dir = 0; dir < 2; dir++) {

                    int ways = dp[i][j][dir];

                    if (ways == 0)
                        continue;

                    // Destination reached.
                    if (i == m - 1 && j == n - 1)
                        continue;

                    // CASE 1: EMPTY CELL
                    if (grid[i][j] == 0) {

                        // Move RIGHT
                        if (j + 1 < n) {

                            dp[i][j + 1][0] =
                                (dp[i][j + 1][0] + ways) % MOD;
                        }

                        // Move DOWN
                        if (i + 1 < m) {

                            dp[i + 1][j][1] =
                                (dp[i + 1][j][1] + ways) % MOD;
                        }
                    }

                    // CASE 2: MIRROR CELL
                    else {

                        // Entered mirror while moving RIGHT.
                        // Reflection changes direction to DOWN.

                        if (dir == 0 && i + 1 < m) {

                            dp[i + 1][j][1] =
                                (dp[i + 1][j][1] + ways) % MOD;
                        }

                        // Entered mirror while moving DOWN.
                        // Reflection changes direction to RIGHT.

                        else if (dir == 1 && j + 1 < n) {

                            dp[i][j + 1][0] =
                                (dp[i][j + 1][0] + ways) % MOD;
                        }
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};


int main() {

    Solution obj;

    vector<vector<int>> grid1 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };

    vector<vector<int>> grid2 = {
        {0, 0},
        {0, 0}
    };

    vector<vector<int>> grid3 = {
        {0, 1, 1},
        {1, 1, 0}
    };

    cout << "Example 1: "
         << obj.uniquePaths(grid1) << endl;

    cout << "Example 2: "
         << obj.uniquePaths(grid2) << endl;

    cout << "Example 3: "
         << obj.uniquePaths(grid3) << endl;

    return 0;
}


/*
================================================================================
                 LEETCODE 3665 - TWISTED MIRROR PATH COUNT
================================================================================


1. PROBLEM STATEMENT
================================================================================

Given an m x n binary grid:

    grid[i][j] == 0  -> Empty cell
    grid[i][j] == 1  -> Mirror cell

A robot starts at the top-left corner (0,0) and wants to reach
the bottom-right corner (m-1,n-1).

The robot can move only RIGHT or DOWN.

MIRROR RULES:

1. If the robot tries to move RIGHT into a mirror:

       It gets reflected DOWN.

       It moves to the cell directly below the mirror.

2. If the robot tries to move DOWN into a mirror:

       It gets reflected RIGHT.

       It moves to the cell directly right of the mirror.

IMPORTANT:

If reflection moves the robot into another mirror, that mirror
also reflects the robot immediately.

If reflection takes the robot outside the grid, that path
is invalid.

Return the number of unique valid paths modulo 10^9 + 7.


2. EXAMPLES
================================================================================

EXAMPLE 1:

Input:

    grid = [
        [0, 1, 0],
        [0, 0, 1],
        [1, 0, 0]
    ]

Output:

    5

EXAMPLE 2:

Input:

    grid = [
        [0, 0],
        [0, 0]
    ]

Output:

    2

EXAMPLE 3:

Input:

    grid = [
        [0, 1, 1],
        [1, 1, 0]
    ]

Output:

    1


3. BRUTE FORCE APPROACH
================================================================================

IDEA:

Use recursion to explore all possible paths.

At every empty cell, we have two choices:

    1. Move RIGHT.
    2. Move DOWN.

At every mirror cell, movement depends on the direction
used to enter that mirror.

If direction == RIGHT:

    Move DOWN.

If direction == DOWN:

    Move RIGHT.

If we reach outside the grid:

    Return 0.

If we reach the destination:

    Return 1.

Add the number of paths obtained from all possible choices.


PSEUDO CODE:

    solve(i, j, dir):

        if i >= m or j >= n:
            return 0

        if destination reached:
            return 1

        if grid[i][j] == 1:

            if dir == RIGHT:
                return solve(i+1, j, DOWN)

            else:
                return solve(i, j+1, RIGHT)

        right = solve(i, j+1, RIGHT)

        down = solve(i+1, j, DOWN)

        return right + down


    answer = solve(0, 0, RIGHT)


COMPLETE BRUTE FORCE CODE:

    int MOD = 1e9 + 7;

    int m, n;

    int solve(vector<vector<int>>& grid,
              int i, int j, int dir) {

        if (i >= m || j >= n)
            return 0;

        if (i == m-1 && j == n-1)
            return 1;

        if (grid[i][j] == 1) {

            if (dir == 0) {
                return solve(grid, i+1, j, 1);
            }

            else {
                return solve(grid, i, j+1, 0);
            }
        }

        int right = solve(grid, i, j+1, 0);

        int down = solve(grid, i+1, j, 1);

        return (right + down) % MOD;
    }

    int uniquePaths(vector<vector<int>>& grid) {

        m = grid.size();
        n = grid[0].size();

        return solve(grid, 0, 0, 0);
    }


TIME COMPLEXITY:

    O(2^(m+n))

Each empty cell can generate two recursive calls.

Many identical states are calculated repeatedly.

SPACE COMPLEXITY:

    O(m+n)

Maximum recursion depth is proportional to the
maximum path length.

CONCLUSION:

Brute force results in TLE for large constraints.


4. OPTIMAL APPROACH - DYNAMIC PROGRAMMING
================================================================================

OBSERVATION:

The future movement depends on two things:

    1. Current position (i,j).
    2. Direction from which we entered the current cell.

Why?

Because a mirror behaves differently depending on
the direction used to enter it.

Therefore, position alone is not sufficient to
represent our DP state.

We need an additional direction dimension.


DP STATE:

    dp[i][j][0]

    Number of ways to reach cell (i,j) while moving RIGHT.

    dp[i][j][1]

    Number of ways to reach cell (i,j) while moving DOWN.


DIRECTION REPRESENTATION:

    RIGHT = 0
    DOWN  = 1


INTUITION:

We process the grid from TOP-LEFT to BOTTOM-RIGHT.

Since movement is only RIGHT and DOWN, row-major
traversal is a valid processing order.

For every cell, we process both possible direction states.


INITIALIZATION:

    dp[0][0][0] = 1

Why initialize only one state?

Because the starting cell is empty and has no incoming
direction.

We represent the starting position using exactly one
artificial state.

From this state, the empty cell generates both possible
movements:

    RIGHT -> dp[0][1][0]

    DOWN  -> dp[1][0][1]

Initializing both states to 1 would count every path twice.


TRANSITIONS:

CASE 1: EMPTY CELL

    grid[i][j] == 0

We can move in both directions.

MOVE RIGHT:

    dp[i][j+1][0] += dp[i][j][dir]

MOVE DOWN:

    dp[i+1][j][1] += dp[i][j][dir]


CASE 2: MIRROR CELL

    grid[i][j] == 1

If direction == RIGHT:

    Mirror redirects DOWN.

    dp[i+1][j][1] += dp[i][j][0]


If direction == DOWN:

    Mirror redirects RIGHT.

    dp[i][j+1][0] += dp[i][j][1]


BOUNDARY CHECK:

Before every transition:

    j + 1 < n

    i + 1 < m

Otherwise, that path is invalid.


FINAL ANSWER:

    dp[m-1][n-1][0] + dp[m-1][n-1][1]

Take modulo 10^9 + 7.


PSEUDO CODE:

    Initialize dp[m][n][2] with 0.

    dp[0][0][0] = 1

    for i = 0 to m-1:

        for j = 0 to n-1:

            for dir = 0 to 1:

                ways = dp[i][j][dir]

                if ways == 0:
                    continue

                if destination reached:
                    continue

                if grid[i][j] == 0:

                    if j+1 < n:
                        dp[i][j+1][0] += ways

                    if i+1 < m:
                        dp[i+1][j][1] += ways

                else:

                    if dir == RIGHT:

                        if i+1 < m:
                            dp[i+1][j][1] += ways

                    else:

                        if j+1 < n:
                            dp[i][j+1][0] += ways

                Apply MOD.

    return dp[m-1][n-1][0] +
           dp[m-1][n-1][1]


COMPLETE OPTIMAL CODE:

    class Solution {
    public:
        const int MOD = 1e9 + 7;

        int uniquePaths(vector<vector<int>>& grid) {

            int m = grid.size();
            int n = grid[0].size();

            vector<vector<int>> vornadexil = grid;

            vector<vector<array<int,2>>> dp(
                m, vector<array<int,2>>(n, {0,0})
            );

            dp[0][0][0] = 1;

            for(int i = 0; i < m; i++) {

                for(int j = 0; j < n; j++) {

                    for(int dir = 0; dir < 2; dir++) {

                        int ways = dp[i][j][dir];

                        if(ways == 0)
                            continue;

                        if(i == m-1 && j == n-1)
                            continue;

                        if(grid[i][j] == 0) {

                            if(j+1 < n) {

                                dp[i][j+1][0] =
                                    (dp[i][j+1][0] + ways) % MOD;
                            }

                            if(i+1 < m) {

                                dp[i+1][j][1] =
                                    (dp[i+1][j][1] + ways) % MOD;
                            }
                        }

                        else {

                            if(dir == 0 && i+1 < m) {

                                dp[i+1][j][1] =
                                    (dp[i+1][j][1] + ways) % MOD;
                            }

                            else if(dir == 1 && j+1 < n) {

                                dp[i][j+1][0] =
                                    (dp[i][j+1][0] + ways) % MOD;
                            }
                        }
                    }
                }
            }

            return (
                dp[m-1][n-1][0] +
                dp[m-1][n-1][1]
            ) % MOD;
        }
    };


TIME COMPLEXITY:

    O(m * n * 2)

    We visit every cell.

    For every cell, we process two direction states.

    Therefore:

    O(m*n)


SPACE COMPLEXITY:

    O(m * n * 2)

    We store two states for every cell.

    Therefore:

    O(m*n)


5. DRY RUN WITH EXAMPLE
================================================================================

INPUT:

    grid = [
        [0, 1, 0],
        [0, 0, 1],
        [1, 0, 0]
    ]


INITIALIZATION:

    dp[0][0][0] = 1

All other states are initially 0.


STEP 1: CELL (0,0)

    grid[0][0] = 0

    It is an empty cell.

    Move RIGHT:

        dp[0][1][0] = 1

    Move DOWN:

        dp[1][0][1] = 1


STEP 2: CELL (0,1)

    grid[0][1] = 1

    It is a mirror.

    Incoming direction = RIGHT.

    Therefore, reflection sends the robot DOWN.

        dp[1][1][1] = 1


STEP 3: CELL (1,0)

    grid[1][0] = 0

    It is an empty cell.

    Move RIGHT:

        dp[1][1][0] = 1

    Move DOWN:

        dp[2][0][1] = 1


STEP 4: CELL (1,1)

    grid[1][1] = 0

    We have two states:

        dp[1][1][0] = 1

        dp[1][1][1] = 1

    Both states can move RIGHT and DOWN.

    RIGHT:

        dp[1][2][0] = 2

    DOWN:

        dp[2][1][1] = 2


STEP 5: CELL (1,2)

    grid[1][2] = 1

    Incoming direction = RIGHT.

    Mirror redirects DOWN.

        dp[2][2][1] = 2


STEP 6: CELL (2,0)

    grid[2][0] = 1

    Incoming direction = DOWN.

    Mirror redirects RIGHT.

        dp[2][1][0] = 1


STEP 7: CELL (2,1)

    grid[2][1] = 0

    We have:

        dp[2][1][0] = 1

        dp[2][1][1] = 2

    Both can move RIGHT.

        dp[2][2][0] = 3


FINAL DESTINATION:

    dp[2][2][0] = 3

    dp[2][2][1] = 2

    Answer = 3 + 2

           = 5


OUTPUT:

    5


6. INTERVIEW NOTES
================================================================================

PATTERN:

    Dynamic Programming on Grid

    Directional State DP

    Bottom-Up Tabulation


KEY OBSERVATION:

    When the next movement depends on the direction
    from which we entered a cell, direction must be
    included in the DP state.

    Therefore:

        dp[i][j][direction]

    is required instead of:

        dp[i][j]


COMMON MISTAKES:

    1. Not including direction in the DP state.

    2. Initializing both starting direction states to 1.

    3. Forgetting that reflection happens before entering
       the mirror cell.

    4. Forgetting chained mirror reflections.

    5. Not checking boundaries after reflection.

    6. Forgetting modulo operations.

    7. Forgetting to add both destination states.

    8. Applying mirror logic after reaching destination.


WHEN TO USE THIS APPROACH:

    Use directional-state DP when:

    1. Movement depends on the previous direction.

    2. The same cell can have different future possibilities
       depending on how we entered it.

    3. Grid paths have direction-dependent restrictions.

    4. You need to count paths with additional movement states.

    5. The problem has deterministic state transitions.


FINAL COMPLEXITY:

    Time Complexity  : O(m * n)

    Space Complexity : O(m * n)

    Technique        : 3D DP / Directional State DP

    Difficulty       : Medium

    LeetCode         : 3665

================================================================================
                         END OF NOTEBOOK
================================================================================
*/
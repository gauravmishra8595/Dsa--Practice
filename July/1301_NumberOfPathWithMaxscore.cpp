#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1000000007;
        int n = board.size();

        // These arrays store DP values for the row below.
        vector<int> nextScore(n + 1, -1);
        vector<int> nextWays(n + 1, 0);

        // I process rows from bottom to top.
        for (int i = n - 1; i >= 0; i--) {
            // Fresh arrays store the current row.
            vector<int> currScore(n + 1, -1);
            vector<int> currWays(n + 1, 0);

            // I process right to left so the right cell is already solved.
            for (int j = n - 1; j >= 0; j--) {
                char cell = board[i][j];

                // Obstacles cannot be used.
                if (cell == 'X')
                    continue;

                // S is the base case of the reversed DP.
                if (cell == 'S') {
                    currScore[j] = 0;
                    currWays[j] = 1;
                    continue;
                }

                // Find the best score among down, right, and diagonal.
                int best = nextScore[j];
                best = max(best, currScore[j + 1]);
                best = max(best, nextScore[j + 1]);

                // No reachable next cell means this cell is unreachable.
                if (best == -1)
                    continue;

                long long ways = 0;

                // Count every next cell that gives the best score.
                if (nextScore[j] == best)
                    ways = (ways + nextWays[j]) % MOD;

                if (currScore[j + 1] == best)
                    ways = (ways + currWays[j + 1]) % MOD;

                if (nextScore[j + 1] == best)
                    ways = (ways + nextWays[j + 1]) % MOD;

                // E adds no points; digit cells add their digit value.
                int value = 0;
                if (cell != 'E')
                    value = cell - '0';

                currScore[j] = best + value;
                currWays[j] = ways;
            }

            // The current row becomes the row below.
            nextScore = currScore;
            nextWays = currWays;
        }

        // An unreachable E means no valid path exists.
        if (nextScore[0] == -1)
            return {0, 0};

        return {nextScore[0], nextWays[0]};
    }
};

int main() {
    Solution obj;

    vector<string> board = {
        "E23",
        "2X2",
        "12S"
    };

    vector<int> ans = obj.pathsWithMaxScore(board);

    cout << "Maximum Score: " << ans[0] << endl;
    cout << "Number of Paths: " << ans[1] << endl;

    return 0;
}
/*
Brute Force Approach

Idea:
- Start from the 'E' cell.
- At every position, recursively try all three possible moves:
    1. Down
    2. Right
    3. Diagonal Down-Right
- Ignore cells containing 'X'.
- Whenever we reach 'S', compare the collected score with the maximum score found so far.
- If the score is greater, update the maximum score and reset the path count.
- If the score equals the maximum score, increment the path count.

Time Complexity:
- O(3^(2N))
  Each move can branch into three choices, leading to exponential time.

Space Complexity:
- O(2N)
  Due to the recursion stack.

Why it fails:
- The same cells are explored repeatedly.
- It exceeds the time limit for larger boards.
*/
/*
Optimal Approach (Dynamic Programming)

Idea:
- Process the board from 'S' towards 'E' (bottom-right to top-left).
- For every cell store:
    score[i][j] -> Maximum score obtainable from this cell to S.
    ways[i][j]  -> Number of paths producing that maximum score.
- Transition uses only three neighbours:
    1. Down
    2. Right
    3. Diagonal
- Pick the neighbour with the largest score.
- If multiple neighbours have the same best score,
  sum all of their path counts.
- Add the current cell's digit to the score
  (except for 'E' and 'S').
- Use rolling arrays to reduce memory usage.

Time Complexity:
- O(N²)

Space Complexity:
- O(N)
  Since only the current and next rows are stored.
*/
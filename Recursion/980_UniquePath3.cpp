#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int ans;

    void findall(vector<vector<int>> &grid,
                 vector<vector<bool>> &vis,
                 int i, int j, int cnt)
    {

        if (i < 0 || i >= grid.size() ||
            j < 0 || j >= grid[0].size() ||
            vis[i][j] || grid[i][j] == -1)
        {
            return;
        }

        // Reached destination
        if (grid[i][j] == 2)
        {
            if (cnt == 0)
                ans++;
            return;
        }

        vis[i][j] = true;
        cnt--;

        findall(grid, vis, i + 1, j, cnt);
        findall(grid, vis, i - 1, j, cnt);
        findall(grid, vis, i, j + 1, cnt);
        findall(grid, vis, i, j - 1, cnt);

        vis[i][j] = false; // backtrack
    }

    int uniquePathsIII(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> vis(m, vector<bool>(n, false));

        int start_i = 0, start_j = 0;
        int cnt = 0;
        ans = 0;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0 || grid[i][j] == 1)
                    cnt++;

                if (grid[i][j] == 1)
                {
                    start_i = i;
                    start_j = j;
                }
            }
        }

        findall(grid, vis, start_i, start_j, cnt);

        return ans;
    }
};

int main()
{
    vector<vector<int>> grid = {
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 2, -1}};

    Solution obj;
    cout << "Number of unique paths: "
         << obj.uniquePathsIII(grid) << endl;

    return 0;
}
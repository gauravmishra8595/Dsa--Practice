#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        // =========================
        // Max Heap Approach (Best)
        // =========================

        // Stores {distance, point}
        priority_queue<pair<int, vector<int>>> pq;

        for (int i = 0; i < points.size(); i++)
        {
            int x = points[i][0];
            int y = points[i][1];

            int dist = x * x + y * y;

            pq.push({dist, points[i]});

            // Keep only k closest points
            if (pq.size() > k)
            {
                pq.pop();
            }
        }

        vector<vector<int>> result;

        while (!pq.empty())
        {
            result.push_back(pq.top().second);
            pq.pop();
        }

        return result;
    }
};

int main()
{
    vector<vector<int>> points = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}};
    int k = 2;

    Solution obj;
    vector<vector<int>> ans = obj.kClosest(points, k);

    cout << "K Closest Points: ";
    for (auto &p : ans)
    {
        cout << "[" << p[0] << "," << p[1] << "] ";
    }

    return 0;
}

/*
=========================
Brute Force Approach
=========================

1. Compute distance for each point.
2. Sort points based on distance.
3. Return first k points.

Code:

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) {
        return (a[0]*a[0] + a[1]*a[1]) < (b[0]*b[0] + b[1]*b[1]);
    });

    return vector<vector<int>>(points.begin(), points.begin() + k);
}

Time Complexity: O(n log n)
Space Complexity: O(1) (excluding output)

=========================
Max Heap Approach
=========================

1. Use a max heap of size k.
2. Store {distance, point}.
3. If heap size exceeds k, remove farthest point.

Time Complexity: O(n log k)
Space Complexity: O(k)

=========================
Optimal Quick Select
=========================
code:
class Solution
{
public:
    int dist(vector<int> &p)
    {
        return p[0] * p[0] + p[1] * p[1];
    }

    int partition(vector<vector<int>> &points, int left, int right)
    {
        vector<int> pivot = points[right];
        int pivotDist = dist(pivot);

        int i = left;

        for (int j = left; j < right; j++)
        {
            if (dist(points[j]) <= pivotDist)
            {
                swap(points[i], points[j]);
                i++;
            }
        }

        swap(points[i], points[right]);
        return i;
    }

    void quickSelect(vector<vector<int>> &points, int left, int right, int k)
    {
        if (left >= right)
            return;

        int pivotIndex = partition(points, left, right);

        if (pivotIndex == k)
            return;
        else if (pivotIndex > k)
            quickSelect(points, left, pivotIndex - 1, k);
        else
            quickSelect(points, pivotIndex + 1, right, k);
    }

    vector<vector<int>> kClosest(vector<vector<int>> &points, int k)
    {
        int n = points.size();

        // We want first k closest points => index k-1
        quickSelect(points, 0, n - 1, k - 1);

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};

1. Partition points around a pivot based on distance.
2. After partition, first k elements are closest.
3. Average Time Complexity: O(n)
Worst Case: O(n^2)
*/
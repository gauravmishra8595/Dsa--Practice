#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int> q; // Max Heap

        for (int i = 0; i < nums.size(); i++)
        {
            q.push(nums[i]);
        }

        for (int i = 0; i < k; i++)
        {
            if (i == k - 1)
            {
                return q.top();
            }
            else
            {
                q.pop();
            }
        }

        return -1;
    }
};

int main()
{
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;

    Solution obj;
    cout << "Kth Largest Element: " << obj.findKthLargest(nums, k) << endl;

    return 0;
}

/*
=========================
Brute Force Approach
=========================

1. Sort the array in ascending order.
2. Return the element at index (n - k).

Code:

int findKthLargest(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() - k];
}

Time Complexity: O(n log n)
Space Complexity: O(1) (excluding sorting stack space)

=========================
Max Heap Approach (Current Code)
=========================

1. Insert all elements into a max heap.
2. Remove the largest element (k-1) times.
3. The top of the heap is the kth largest element.

Time Complexity: O(n log n)
Space Complexity: O(n)

=========================
Optimal Min Heap Approach
=========================

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int num : nums) {
        pq.push(num);

        if (pq.size() > k) {
            pq.pop();
        }
    }

    return pq.top();
}

Time Complexity: O(n log k)
Space Complexity: O(k)

*/
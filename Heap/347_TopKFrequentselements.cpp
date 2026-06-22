#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {

        // Store frequency of each element
        unordered_map<int, int> freq;

        for (int num : nums)
        {
            freq[num]++;
        }

        // Max Heap: {frequency, element}
        priority_queue<pair<int, int>> pq;

        for (auto it : freq)
        {
            pq.push({it.second, it.first});
        }

        vector<int> ans;

        // Extract top k frequent elements
        while (k--)
        {
            ans.push_back(pq.top().second);
            pq.pop();
        }

        return ans;
    }
};

int main()
{
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;

    Solution obj;
    vector<int> result = obj.topKFrequent(nums, k);

    cout << "Top K Frequent Elements: ";
    for (int x : result)
    {
        cout << x << " ";
    }

    return 0;
}

/*
=========================================
Brute Force Approach
=========================================

1. Count frequency of every element using map.
2. Store frequencies in a vector of pairs.
3. Sort the vector in descending order of frequency.
4. Take first k elements.

Code:

unordered_map<int,int> freq;

for(int num : nums)
    freq[num]++;

vector<pair<int,int>> v;

for(auto p : freq)
    v.push_back({p.second, p.first});

sort(v.rbegin(), v.rend());

vector<int> ans;

for(int i=0; i<k; i++)
    ans.push_back(v[i].second);

Time Complexity: O(n log n)
Space Complexity: O(n)

=========================================
Max Heap Approach
=========================================

1. Count frequencies.
2. Push {frequency, element} into max heap.
3. Pop k elements.

Time Complexity: O(n log n)
Space Complexity: O(n)

=========================================
Optimal Bucket Sort Approach
=========================================

vector<int> topKFrequent(vector<int>& nums, int k) {

    unordered_map<int,int> freq;

    for(int num : nums)
        freq[num]++;

    vector<vector<int>> bucket(nums.size() + 1);

    for(auto p : freq)
        bucket[p.second].push_back(p.first);

    vector<int> ans;

    for(int i = nums.size(); i >= 0 && ans.size() < k; i--) {
        for(int num : bucket[i]) {
            ans.push_back(num);

            if(ans.size() == k)
                return ans;
        }
    }

    return ans;
}

Time Complexity: O(n)
Space Complexity: O(n)

Expected Interview Answer:
Bucket Sort (O(n))
or
Min Heap (O(n log k))

*/
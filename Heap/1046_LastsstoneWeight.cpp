#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {

        priority_queue<int> pq;

        // Insert all stones into max heap
        for (auto x : stones)
        {
            pq.push(x);
        }

        // Keep smashing the two heaviest stones
        while (pq.size() > 1)
        {

            int y = pq.top(); // heaviest
            pq.pop();

            int x = pq.top(); // second heaviest
            pq.pop();

            if (y != x)
            {
                pq.push(y - x);
            }
        }

        return pq.empty() ? 0 : pq.top();
    }
};

int main()
{

    vector<int> stones = {2, 7, 4, 1, 8, 1};

    Solution obj;

    cout << "Last Stone Weight: "
         << obj.lastStoneWeight(stones)
         << endl;

    return 0;
}

/*
=========================================
Brute Force Approach
=========================================

Idea:
1. Sort the array.
2. Pick the two largest stones.
3. Remove them.
4. If they are unequal, insert their difference.
5. Sort again.
6. Repeat until <= 1 stone remains.

Code Sketch:

while(stones.size() > 1){

    sort(stones.begin(), stones.end());

    int y = stones.back();
    stones.pop_back();

    int x = stones.back();
    stones.pop_back();

    if(y != x)
        stones.push_back(y - x);
}

return stones.empty() ? 0 : stones[0];

Time Complexity:
O(n² log n)

Space Complexity:
O(1)

=========================================
Optimal Approach (Max Heap)
=========================================

Idea:
- Use a max heap to always get the
  two largest stones efficiently.

Steps:
1. Insert all stones into max heap.
2. Extract largest two stones.
3. If different, push back their difference.
4. Continue until one or zero stones remain.

Example:

stones = [2,7,4,1,8,1]

Heap:
8 7 4 2 1 1

8 - 7 = 1
Heap:
4 2 1 1 1

4 - 2 = 2
Heap:
2 1 1 1

2 - 1 = 1
Heap:
1 1 1

1 - 1 = 0
Heap:
1

Answer = 1

Time Complexity:
O(n log n)

Space Complexity:
O(n)

=========================================
Why Priority Queue?
=========================================

top()  -> largest stone
pop()  -> remove largest stone
push() -> insert remaining stone

All operations take O(log n),
making it efficient for repeated
largest-element retrieval.

LeetCode 1046 Expected Solution:
Max Heap (Priority Queue)

*/
#include <bits/stdc++.h>
using namespace std;

class KthLargest
{
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;

public:
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;

        for (int num : nums)
        {
            pq.push(num);
            if (pq.size() > k)
                pq.pop();
        }
    }

    int add(int val)
    {
        pq.push(val);

        if (pq.size() > k)
            pq.pop();

        return pq.top();
    }
};

int main()
{
    vector<int> nums = {4, 5, 8, 2};

    KthLargest obj(3, nums);

    cout << obj.add(3) << endl;  // 4
    cout << obj.add(5) << endl;  // 5
    cout << obj.add(10) << endl; // 5
    cout << obj.add(9) << endl;  // 8
    cout << obj.add(4) << endl;  // 8

    return 0;
}

/*

=========================================
LeetCode 703 - Kth Largest Element in a Stream
=========================================

Problem Statement
-----------------
Design a class that continuously receives integers from a stream.

Implement:

1. KthLargest(int k, vector<int>& nums)
   Initializes the object with integer k and the initial stream nums.

2. int add(int val)
   Adds val to the stream and returns the kth largest element in the stream.

----------------------------------------------------

Example
-------

Input:
k = 3
nums = [4,5,8,2]

Operations:

add(3)  -> 4
add(5)  -> 5
add(10) -> 5
add(9)  -> 8
add(4)  -> 8

Output:
4 5 5 8 8

====================================================
Brute Force Approach
====================================================

Idea
----
Maintain all elements in a vector.

Whenever add(val) is called:
1. Insert val.
2. Sort the entire vector.
3. Return the kth largest element.

----------------------------------------------------

Pseudo Code
-----------

store all numbers in vector

add(val):
    push val
    sort(vector)
    return vector[size-k]

----------------------------------------------------

Complete Brute Force Code
----------------------------------------------------

class KthLargest {
    int k;
    vector<int> nums;

public:
    KthLargest(int k, vector<int>& arr) {
        this->k = k;
        nums = arr;
    }

    int add(int val) {
        nums.push_back(val);
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};

----------------------------------------------------

Time Complexity
---------------
Constructor : O(n)

Each add():
Sorting takes O(n log n)

Space Complexity
----------------
O(n)

====================================================
Optimal Approach
====================================================

Observation
-----------
We never need all elements in sorted order.

We only care about the largest k elements.

Among these k elements,
the smallest one is exactly the kth largest element.

----------------------------------------------------

Intuition
---------
Maintain a Min Heap of size k.

Why Min Heap?

Suppose k = 3

Numbers:
4 5 8 2 10

Keep only:

5 8 10

The smallest among them is 5,
which is the 3rd largest overall.

Whenever a new value arrives:

1. Push it into heap.
2. If heap size exceeds k,
   remove the smallest element.
3. Heap top always becomes kth largest.

----------------------------------------------------

Pseudo Code
-----------

Constructor:

store k

for every number
    push into heap

    if heap size > k
        pop

--------------------------------

add(val)

push val

if heap size > k
    pop

return heap top

----------------------------------------------------

Complete Optimal Code
----------------------------------------------------

class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;

        for(int num : nums) {
            pq.push(num);

            if(pq.size() > k)
                pq.pop();
        }
    }

    int add(int val) {
        pq.push(val);

        if(pq.size() > k)
            pq.pop();

        return pq.top();
    }
};

----------------------------------------------------

Time Complexity
---------------

Constructor:
O(n log k)

Each add():
O(log k)

Space Complexity
----------------
O(k)

====================================================
Dry Run
====================================================

k = 3

nums = [4,5,8,2]

Insert 4
Heap = [4]

Insert 5
Heap = [4,5]

Insert 8
Heap = [4,5,8]

Insert 2
Heap = [2,4,8,5]
Size > 3

Pop 2

Heap = [4,5,8]

--------------------------------

add(3)

Push 3

Heap = [3,4,8,5]

Pop 3

Heap = [4,5,8]

Top = 4

Answer = 4

--------------------------------

add(10)

Heap = [4,5,8,10]

Pop 4

Heap = [5,10,8]

Top = 5

Answer = 5

====================================================
Interview Notes
====================================================

Pattern
-------
Heap
Priority Queue
Top-K Elements
Streaming Data

Key Observation
---------------
1. Need only k largest elements.
2. Maintain a Min Heap of size k.
3. Heap top always represents kth largest element.

Common Mistakes
---------------
1. Using Max Heap instead of Min Heap.
2. Forgetting to pop when heap size exceeds k.
3. Sorting after every insertion.
4. Returning the largest element instead of kth largest.

When to use this approach
-------------------------
Use this pattern whenever:

- Finding kth largest/smallest continuously.
- Processing streaming data.
- Solving Top-K problems.
- Maintaining only the most important k elements.

*/
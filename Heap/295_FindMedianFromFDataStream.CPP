#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class MedianFinder
{
private:
    priority_queue<int> left; // Max Heap (Smaller Half)

    priority_queue<int,
                   vector<int>,
                   greater<int>>
        right; // Min Heap (Larger Half)

public:
    MedianFinder() {}

    void addNum(int num)
    {
        // Insert into Max Heap

        left.push(num);

        // Maintain ordering property

        if (!right.empty() &&
            left.top() > right.top())
        {
            right.push(left.top());
            left.pop();
        }

        // Balance heap sizes

        if (left.size() > right.size() + 1)
        {
            right.push(left.top());
            left.pop();
        }

        else if (right.size() > left.size() + 1)
        {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian()
    {
        if (left.size() == right.size())
        {
            return (left.top() +
                    right.top()) /
                   2.0;
        }

        if (left.size() > right.size())
        {
            return left.top();
        }

        return right.top();
    }
};

int main()
{
    MedianFinder obj;

    obj.addNum(1);
    obj.addNum(2);

    cout << "Median: "
         << obj.findMedian()
         << endl;

    obj.addNum(3);

    cout << "Median: "
         << obj.findMedian()
         << endl;

    return 0;
}

/*
=========================
Brute Force Approach
=========================

1. Store all numbers in a vector.
2. Whenever median is requested:
   - Sort the vector.
   - Return middle element(s).

Code:

vector<int> nums;

void addNum(int num) {
    nums.push_back(num);
}

double findMedian() {

    sort(nums.begin(), nums.end());

    int n = nums.size();

    if(n % 2 == 1)
        return nums[n / 2];

    return (nums[n / 2] +
            nums[n / 2 - 1]) / 2.0;
}

Time Complexity:
addNum()      -> O(1)
findMedian()  -> O(n log n)

Space Complexity:
O(n)

=========================
Two Heap Approach
(Current Code)
=========================

1. Maintain two heaps:

   Max Heap (left)
   -> Smaller Half

   Min Heap (right)
   -> Larger Half

2. Insert every number
   into Max Heap.

3. If ordering property
   is violated

   left.top() > right.top()

   move element from
   left to right.

4. Balance heap sizes.

5. Median:

   Equal Size:
   (left.top() + right.top()) / 2

   Unequal Size:
   Top of larger heap

Time Complexity:
addNum()      -> O(log n)
findMedian()  -> O(1)

Space Complexity:
O(n)

=========================
Interview Preferred
Approach
=========================

1. If left is empty OR

   num <= left.top()

   push into Max Heap.

2. Else

   push into Min Heap.

3. Balance heap sizes.

4. Median calculation
   remains same.

Code:

if(left.empty() ||
   num <= left.top())
{
    left.push(num);
}
else
{
    right.push(num);
}

Time Complexity:
addNum()      -> O(log n)
findMedian()  -> O(1)

Space Complexity:
O(n)

=========================
Summary
=========================

Brute Force:
O(1) add
O(n log n) median

Two Heaps:
O(log n) add
O(1) median

Expected Interview Solution:
Two Heaps

*/
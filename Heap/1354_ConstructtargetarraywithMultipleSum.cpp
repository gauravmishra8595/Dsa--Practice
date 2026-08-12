#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isPossible(vector<int> &target)
    {
        priority_queue<long long> pq;

        long long sum = 0;

        for (int x : target)
        {
            pq.push(x);
            sum += x;
        }

        while (pq.top() != 1)
        {
            long long largest = pq.top();
            pq.pop();

            long long rest = sum - largest;

            // No other elements exist
            if (rest == 0)
                return false;

            // If rest is 1, we can always reduce
            // the largest element down to 1.
            if (rest == 1)
                return true;

            // Largest must be greater than the sum
            // of all remaining elements.
            if (largest <= rest)
                return false;

            long long previous = largest % rest;

            // Previous value cannot be 0.
            if (previous == 0)
                return false;

            pq.push(previous);

            sum = rest + previous;
        }

        return true;
    }
};

int main()
{
    Solution obj;

    vector<int> target = {8, 5};

    cout << (obj.isPossible(target) ? "true" : "false") << endl;

    return 0;
}

/*
=========================================*
LeetCode 1354: Construct Target Array
With Multiple Sums
=========================================*

Problem Statement:
------------------
Start with an array of positive integers:

    [1,1,1,...,1]

In one operation, choose an index i and replace:

    arr[i] = sum of all elements of arr

Determine whether it is possible to construct
the given target array.

Return true if possible, otherwise false.

=========================================*
Example:
=========================================*

Input:

target = [9,3,5]

Output:

true

Reverse process:

[9,3,5]
   ↓
[1,3,5]
   ↓
[1,3,1]
   ↓
[1,1,1]

Therefore:

true

=========================================*
Brute Force Approach
=========================================*

Idea:
-----
Start from [1,1,...,1] and repeatedly perform
the operation until we reach target.

This directly simulates the construction process.

However, target values can be extremely large,
so the number of operations can become huge.

Pseudo Code:
------------

Start with:

arr = [1,1,...,1]

While arr != target:

    Find an element that can be increased.

    Replace it with sum(arr).

    If it becomes larger than target:
        return false.

Return true.

Complete Brute Force Code:
--------------------------

bool isPossible(vector<int>& target)
{
    int n = target.size();

    vector<long long> arr(n, 1);

    while (true)
    {
        bool same = true;

        for (int i = 0; i < n; i++)
        {
            if (arr[i] != target[i])
            {
                same = false;
                break;
            }
        }

        if (same)
            return true;

        long long sum = 0;

        for (long long x : arr)
            sum += x;

        int index = -1;

        for (int i = 0; i < n; i++)
        {
            if (arr[i] < target[i])
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return false;

        arr[index] = sum;

        if (arr[index] > target[index])
            return false;
    }
}

Time Complexity:
----------------
Potentially very large.

The number of operations depends on the
values in target.

Space Complexity:
-----------------
O(n)

=========================================*
Optimal Approach
=========================================*

Observation:
------------
Instead of constructing target forward,
construct the answer BACKWARDS.

Suppose:

target = [9,3,5]

Total:

17

Largest:

9

Sum of remaining elements:

17 - 9 = 8

The previous value of 9 must have been:

9 - 8 = 1

So:

[9,3,5]

becomes:

[1,3,5]

We continue until every value becomes 1.

-----------------------------------------

Why Max Heap?
-------------

At every step, we need the largest element.

So use:

    priority_queue<long long>

The largest element is always:

    pq.top()

-----------------------------------------

Why Modulo?
-----------

Suppose:

largest = 100
rest = 3

We could repeatedly do:

100 - 3
97 - 3
94 - 3
91 - 3
...

This is very slow.

Instead:

100 % 3 = 1

So we can directly jump to:

1

Thus:

previous = largest % rest

-----------------------------------------

Important Special Case:
-----------------------

If:

rest == 1

then the answer is always true.

For example:

[8,5]

Reverse:

[8,5]
[3,5]
[3,2]
[1,2]
[1,1]

At [1,2]:

largest = 2
rest = 1

Although:

2 % 1 = 0

this is NOT invalid.

We simply subtract 1 once:

2 -> 1

Therefore:

if (rest == 1)
    return true;

-----------------------------------------

Invalid Conditions:
-------------------

1. rest == 0

There are no other elements.

Impossible.

2. largest <= rest

The largest element could not have been created
from the sum of the remaining elements.

3. largest % rest == 0

If rest > 1, modulo 0 means the previous value
would become 0, which is invalid.

Pseudo Code:
------------

Create max heap.

Calculate total sum.

While largest != 1:

    largest = maximum element

    rest = sum - largest

    If rest == 0:
        return false

    If rest == 1:
        return true

    If largest <= rest:
        return false

    previous = largest % rest

    If previous == 0:
        return false

    Push previous into heap.

    Update sum.

Return true.

Complete Optimal Code:
----------------------

class Solution
{
public:
    bool isPossible(vector<int>& target)
    {
        priority_queue<long long> pq;

        long long sum = 0;

        for (int x : target)
        {
            pq.push(x);
            sum += x;
        }

        while (pq.top() != 1)
        {
            long long largest = pq.top();
            pq.pop();

            long long rest = sum - largest;

            if (rest == 0)
                return false;

            if (rest == 1)
                return true;

            if (largest <= rest)
                return false;

            long long previous = largest % rest;

            if (previous == 0)
                return false;

            pq.push(previous);

            sum = rest + previous;
        }

        return true;
    }
};

Time Complexity:
----------------
O(n log(max(target)))

The max heap allows us to extract the largest
element efficiently, while modulo skips repeated
subtractions.

Space Complexity:
-----------------
O(n)

=========================================*
Dry Run
=========================================*

Input:

target = [8,5]

-----------------------------------------

Step 1:

Largest = 8

Sum = 13

Rest:

13 - 8 = 5

Previous:

8 % 5 = 3

Array becomes:

[3,5]

-----------------------------------------

Step 2:

Largest = 5

Sum = 8

Rest:

8 - 5 = 3

Previous:

5 % 3 = 2

Array becomes:

[3,2]

-----------------------------------------

Step 3:

Largest = 3

Sum = 5

Rest:

5 - 3 = 2

Previous:

3 % 2 = 1

Array becomes:

[1,2]

-----------------------------------------

Step 4:

Largest = 2

Rest:

2 - 1 = 1

Since:

rest == 1

return true.

Final Answer:

true

=========================================*
Interview Notes:
=========================================*

Pattern:
--------
Max Heap + Greedy + Reverse Simulation

Key Observation:
----------------
Always reverse the largest element.

Formula:

rest = sum - largest

previous = largest % rest

Special case:

rest == 1 -> true

Common Mistakes:
----------------
1. Checking previous == 0 before handling
   rest == 1.

2. Forgetting the rest == 1 special case.

3. Using int instead of long long for sum.

4. Simulating forward.

5. Using repeated subtraction instead of modulo.

6. Forgetting that the largest element must be
   strictly greater than rest when rest > 1.

When to use this approach:
--------------------------
Use this pattern when:

- The forward operation creates a large value.
- The last operation can be identified using
  the largest element.
- The reverse operation is easier.
- Repeated subtraction can be optimized with modulo.

=========================================*
Complexity Summary:
=========================================*

Brute Force:

Time  -> Potentially very large
Space -> O(n)

Optimal:

Time  -> O(n log(max(target)))
Space -> O(n)

=========================================*
Interview Tip:
=========================================*

Remember the three important checks:

1. rest == 0
       -> false

2. rest == 1
       -> true

3. largest % rest == 0
       -> false

The order matters.

For:

[8,5]

the critical case is:

largest = 2
rest = 1

So we must return true before checking:

2 % 1 == 0

=========================================*
*/
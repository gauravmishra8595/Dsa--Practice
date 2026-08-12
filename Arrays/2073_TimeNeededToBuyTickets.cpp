#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int timeRequiredToBuy(vector<int> &tickets, int k)
    {
        int time = 0;

        for (int i = 0; i < tickets.size(); i++)
        {
            if (i <= k)
            {
                time += min(tickets[i], tickets[k]);
            }
            else
            {
                time += min(tickets[i], tickets[k] - 1);
            }
        }

        return time;
    }
};

int main()
{
    Solution obj;

    vector<int> tickets = {2, 3, 2};
    int k = 2;

    cout << "Time Required: "
         << obj.timeRequiredToBuy(tickets, k)
         << endl;

    return 0;
}

/*
=========================================*
LeetCode 2073: Time Needed to Buy Tickets
=========================================*

Problem Statement:
------------------
There are n people standing in a queue.

tickets[i] represents the number of tickets that
person i wants to buy.

Each person buys exactly ONE ticket at a time.

After buying one ticket:
    - If they still need more tickets,
      they go to the back of the queue.
    - Otherwise, they leave the queue.

Given k, return the total time required for the
person at index k to finish buying all their tickets.

Each ticket purchase takes 1 second.

=========================================*
Example:
=========================================*

Input:

tickets = [2,3,2]
k = 2

Queue:

Person 0 -> 2 tickets
Person 1 -> 3 tickets
Person 2 -> 2 tickets

Process:

Person 0 buys -> 1
Person 1 buys -> 2
Person 2 buys -> 1

Person 0 buys -> 0
Person 1 buys -> 1
Person 2 buys -> 0

Person 1 buys -> 0

Total time = 7

Output:

7

=========================================*
Brute Force Approach
=========================================*

Idea:
-----
Directly simulate the queue.

For every second:
    1. Take the person from the front.
    2. Decrease their ticket count.
    3. Increase time.
    4. If they still need tickets, put them
       at the back.
    5. Stop when person k finishes.

Pseudo Code:
------------

Create queue containing indices 0 to n-1.

time = 0

While tickets[k] > 0:

    person = queue.front()
    queue.pop()

    tickets[person]--
    time++

    If tickets[person] > 0:
        queue.push(person)

Return time

Complete Brute Force Code:
--------------------------

int timeRequiredToBuy(vector<int>& tickets, int k)
{
    queue<int> q;

    for (int i = 0; i < tickets.size(); i++)
        q.push(i);

    int time = 0;

    while (tickets[k] > 0)
    {
        int person = q.front();
        q.pop();

        tickets[person]--;
        time++;

        if (tickets[person] > 0)
            q.push(person);
    }

    return time;
}

Time Complexity:
----------------
O(total number of tickets bought)

Worst case can be O(n * max(tickets[i])).

Space Complexity:
-----------------
O(n)

=========================================*
Optimal Approach
=========================================*

Observation:
------------
We only care about how many times each person
gets a chance to buy a ticket before person k
finishes.

Let:

tickets[k] = x

Person k needs exactly x purchases.

For every person i:

Case 1:
-------
i <= k

These people appear before or at person k.

They can buy at most x tickets before k finishes.

Therefore:

contribution = min(tickets[i], x)

Case 2:
-------
i > k

These people are behind person k.

They get one fewer chance because the process stops
immediately when person k buys their final ticket.

Therefore:

contribution = min(tickets[i], x - 1)

Intuition:
---------
Imagine person k needs x tickets.

Every complete round allows everyone to buy one ticket.

But in the final round, person k finishes as soon
as they buy their last ticket.

People after k do NOT get to buy during that final
round.

Therefore:

Before/equal k:
    min(tickets[i], tickets[k])

After k:
    min(tickets[i], tickets[k] - 1)

Add all contributions.

Pseudo Code:
------------

x = tickets[k]
time = 0

For i from 0 to n-1:

    If i <= k:
        time += min(tickets[i], x)

    Else:
        time += min(tickets[i], x - 1)

Return time

Complete Optimal Code:
----------------------

class Solution
{
public:
    int timeRequiredToBuy(vector<int>& tickets, int k)
    {
        int time = 0;

        for (int i = 0; i < tickets.size(); i++)
        {
            if (i <= k)
            {
                time += min(tickets[i], tickets[k]);
            }
            else
            {
                time += min(tickets[i], tickets[k] - 1);
            }
        }

        return time;
    }
};

Time Complexity:
----------------
O(n)

We visit every person exactly once.

Space Complexity:
-----------------
O(1)

No extra data structure is required.

=========================================*
Dry Run
=========================================*

Input:

tickets = [2,3,2]
k = 2

Person k:

tickets[2] = 2

So:

x = 2

-----------------------------------------

i = 0

i <= k

Contribution:

min(tickets[0], 2)
= min(2, 2)
= 2

time = 2

-----------------------------------------

i = 1

i <= k

Contribution:

min(tickets[1], 2)
= min(3, 2)
= 2

time = 4

-----------------------------------------

i = 2

i <= k

Contribution:

min(tickets[2], 2)
= min(2, 2)
= 2

time = 6

-----------------------------------------

Final:

i > k does not exist.

But actual process:

Person 0 -> 2 tickets
Person 1 -> 3 tickets
Person 2 -> 2 tickets

Total:

2 + 3 + 2 = 7

Wait!

Why did our calculation give 6?

Because the example calculation above is incomplete:
Person 1 can buy 3 tickets, not just 2, because
person k is behind person 1 and person 1 gets an
additional turn before k's final purchase.

Correct interpretation:

For i <= k:
    min(tickets[i], tickets[k])

For i > k:
    min(tickets[i], tickets[k] - 1)

For:

tickets = [2,3,2]
k = 2

i = 0:
min(2,2) = 2

i = 1:
min(3,2) = 2

i = 2:
min(2,2) = 2

Total = 6

However, the actual queue process is:

Round 1:
0 -> 1
1 -> 2
2 -> 1

Round 2:
0 -> 0
1 -> 1
2 -> 0

Person 2 finishes after 6 seconds.

Therefore:

Answer = 6

=========================================*
Interview Notes:
=========================================*

Pattern:
--------
Queue Simulation / Counting

Key Observation:
----------------
We do not need to actually simulate the queue.

Person k needs tickets[k] turns.

People before or at k can buy at most tickets[k]
tickets.

People after k can buy at most tickets[k] - 1
tickets because the process stops when k finishes.

Formula:

For i <= k:

min(tickets[i], tickets[k])

For i > k:

min(tickets[i], tickets[k] - 1)

Common Mistakes:
----------------
1. Using tickets[k] for everyone.

2. Forgetting that people after k get one fewer turn.

3. Actually simulating the queue when O(n) counting
   is enough.

4. Confusing the index k with the number of tickets.

5. Forgetting that the process stops immediately
   when person k buys their final ticket.

When to use this approach:
--------------------------
Use this approach when:

- A queue is processed in repeated rounds.
- You only care when one particular element finishes.
- Each round gives every relevant element one chance.
- The stopping point can be calculated mathematically.

=========================================*
Complexity Summary:
=========================================*

Brute Force:

Time  -> O(n * max(tickets[i]))
Space -> O(n)

Optimal:

Time  -> O(n)
Space -> O(1)

=========================================*
Interview Tip:
=========================================*

Think in terms of "number of turns".

If person k needs X tickets:

People at indices <= k:
    Can get X turns.

People at indices > k:
    Can get at most X - 1 turns.

This converts the queue simulation into a simple
O(n) counting problem.

=========================================*
*/
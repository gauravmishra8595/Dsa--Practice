#include <bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x)
    {
        val = x;
        next = nullptr;
    }
};

class Solution
{
public:
    vector<int> nodesBetweenCriticalPoints(ListNode *head)
    {
        ListNode *prev = head;
        ListNode *curr = head->next;

        int pos = 1;
        int firstCritical = -1;
        int prevCritical = -1;
        int minDist = INT_MAX;

        while (curr->next != nullptr)
        {
            // Local minimum or local maximum
            if ((curr->val < prev->val && curr->val < curr->next->val) ||
                (curr->val > prev->val && curr->val > curr->next->val))
            {

                if (firstCritical == -1)
                {
                    firstCritical = pos;
                }

                if (prevCritical != -1)
                {
                    minDist = min(minDist, pos - prevCritical);
                }

                prevCritical = pos;
            }

            prev = curr;
            curr = curr->next;
            pos++;
        }

        if (firstCritical == -1 || firstCritical == prevCritical)
        {
            return {-1, -1};
        }

        return {minDist, prevCritical - firstCritical};
    }
};

int main()
{
    // Example:
    // Linked List: 5 -> 3 -> 1 -> 2 -> 5 -> 1 -> 2
    //
    // Critical points are at positions:
    // 3 (local minimum), 5 (local maximum), 6 (local minimum)
    //
    // Minimum distance = 1
    // Maximum distance = 6 - 3 = 3

    ListNode *head = nullptr;
    ListNode *tail = nullptr;

    vector<int> values = {5, 3, 1, 2, 5, 1, 2};

    for (int x : values)
    {
        ListNode *node = new ListNode(x);

        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    Solution obj;
    vector<int> ans = obj.nodesBetweenCriticalPoints(head);

    cout << "[" << ans[0] << ", " << ans[1] << "]\n";

    return 0;
}

/*
===============================================================================
                    NODES BETWEEN CRITICAL POINTS
===============================================================================

Problem Statement:
------------------
Given a singly linked list, a critical point is a node that is either:

1. A local maximum:
   curr->val > prev->val && curr->val > next->val

2. A local minimum:
   curr->val < prev->val && curr->val < next->val

Find:
    [minimum distance between any two critical points,
     maximum distance between any two critical points]

If there are fewer than two critical points, return {-1, -1}.


Example:
--------
Input:
    5 -> 3 -> 1 -> 2 -> 5 -> 1 -> 2

Critical points:
    Position 3 -> 1  (local minimum)
    Position 5 -> 5  (local maximum)
    Position 6 -> 1  (local minimum)

Minimum distance:
    min(5 - 3, 6 - 5) = min(2, 1) = 1

Maximum distance:
    6 - 3 = 3

Output:
    [1, 3]


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

Idea:
-----
1. Traverse the linked list and store all critical point positions.
2. For every pair of critical points:
       - Calculate their distance.
       - Update minimum distance.
       - Update maximum distance.
3. If fewer than two critical points exist, return {-1, -1}.


Pseudo Code:
-----------
criticalPositions = empty list

Traverse linked list:
    if current node is local minimum or local maximum:
        store its position

if number of critical points < 2:
    return {-1, -1}

minDist = INF
maxDist = 0

for i = 0 to size - 1:
    for j = i + 1 to size - 1:
        distance = criticalPositions[j] - criticalPositions[i]

        minDist = min(minDist, distance)
        maxDist = max(maxDist, distance)

return {minDist, maxDist}


Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> criticalPositions;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int pos = 1;

        while (curr->next != nullptr) {

            if ((curr->val < prev->val && curr->val < curr->next->val) ||
                (curr->val > prev->val && curr->val > curr->next->val)) {
                criticalPositions.push_back(pos);
            }

            prev = curr;
            curr = curr->next;
            pos++;
        }

        if (criticalPositions.size() < 2) {
            return {-1, -1};
        }

        int minDist = INT_MAX;
        int maxDist = 0;

        for (int i = 0; i < criticalPositions.size(); i++) {
            for (int j = i + 1; j < criticalPositions.size(); j++) {
                int dist = criticalPositions[j] - criticalPositions[i];

                minDist = min(minDist, dist);
                maxDist = max(maxDist, dist);
            }
        }

        return {minDist, maxDist};
    }
};


Time Complexity:
----------------
O(N + K^2)

N = number of nodes
K = number of critical points

Worst case:
O(N^2)


Space Complexity:
-----------------
O(K)

Used to store positions of all critical points.


===============================================================================
OPTIMAL APPROACH
===============================================================================

Observation:
------------
We do NOT need to store every critical point.

For maximum distance:
    Last critical point - First critical point

For minimum distance:
    The minimum distance must occur between two CONSECUTIVE
    critical points.

Therefore, while traversing the list, we only need:

    firstCritical -> first critical point
    prevCritical  -> previous critical point
    minDist       -> minimum distance found so far


Intuition:
----------
Suppose critical points occur at:

    3, 5, 6, 10

Maximum distance:
    10 - 3 = 7

Minimum distance:
    min(5-3, 6-5, 10-6)
    = min(2, 1, 4)
    = 1

There is no need to compare every pair.

Whenever we find a new critical point:

1. If it is the first one:
       Store its position as firstCritical.

2. Otherwise:
       Calculate distance from prevCritical.
       Update minDist.
       Move prevCritical to the current position.

At the end:
    maximum distance = prevCritical - firstCritical


Pseudo Code:
-----------
firstCritical = -1
prevCritical = -1
minDist = INF

Traverse linked list:
    if current node is critical:

        if firstCritical == -1:
            firstCritical = current position

        if prevCritical != -1:
            minDist = min(minDist,
                          current position - prevCritical)

        prevCritical = current position

if fewer than two critical points:
    return {-1, -1}

maxDist = prevCritical - firstCritical

return {minDist, maxDist}


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;
        int firstCritical = -1;
        int prevCritical = -1;
        int minDist = INT_MAX;

        while (curr->next != nullptr) {

            if ((curr->val < prev->val &&
                 curr->val < curr->next->val) ||
                (curr->val > prev->val &&
                 curr->val > curr->next->val)) {

                if (firstCritical == -1) {
                    firstCritical = pos;
                }

                if (prevCritical != -1) {
                    minDist = min(minDist,
                                  pos - prevCritical);
                }

                prevCritical = pos;
            }

            prev = curr;
            curr = curr->next;
            pos++;
        }

        if (firstCritical == -1 ||
            firstCritical == prevCritical) {
            return {-1, -1};
        }

        return {minDist,
                prevCritical - firstCritical};
    }
};


Time Complexity:
----------------
O(N)

We traverse the linked list only once.


Space Complexity:
-----------------
O(1)

Only a few variables are used.


===============================================================================
DRY RUN WITH EXAMPLE
===============================================================================

Linked List:

    5 -> 3 -> 1 -> 2 -> 5 -> 1 -> 2
    Position:
    0    1    2    3    4    5    6

We start checking from position 1 because a critical point
needs both a previous and a next node.

Position 1:
    Value = 3
    Neighbours = 5, 1

    3 is not a local minimum or maximum.

Position 2:
    Value = 1
    Neighbours = 3, 2

    1 < 3 and 1 < 2
    => Critical point

    firstCritical = 2
    prevCritical = 2

Position 3:
    Value = 2
    Neighbours = 1, 5

    Not critical.

Position 4:
    Value = 5
    Neighbours = 2, 1

    5 > 2 and 5 > 1
    => Critical point

    distance = 4 - 2 = 2

    minDist = 2
    prevCritical = 4

Position 5:
    Value = 1
    Neighbours = 5, 2

    1 < 5 and 1 < 2
    => Critical point

    distance = 5 - 4 = 1

    minDist = min(2, 1) = 1
    prevCritical = 5

End of traversal:

    Minimum distance = 1
    Maximum distance = 5 - 2 = 3

Answer:

    {1, 3}


===============================================================================
INTERVIEW NOTES
===============================================================================

Pattern:
--------
Linked List Traversal + One-Pass Tracking


Key Observation:
----------------
For minimum distance, only consecutive critical points matter.

For maximum distance, only the first and last critical points matter.

Therefore, storing every critical point is unnecessary.


Common Mistakes:
----------------
1. Using:
       return (minDist, maxDist);

   This uses the comma operator and returns only maxDist.

   Correct:
       return {minDist, maxDist};


2. Forgetting that the first and last nodes cannot be critical points.

3. Checking a node without ensuring:
       curr->next != nullptr

4. Returning a valid distance when there are fewer than two
   critical points.

5. Using O(K) extra space when O(1) space is possible.


When to Use This Approach:
--------------------------
Use this approach whenever:

- You need distances between special positions in a sequence.
- Minimum distance depends only on consecutive special positions.
- Maximum distance depends only on the first and last special positions.
- The data can be processed in one traversal.

This is a classic example of replacing pairwise comparison with
incremental tracking.

===============================================================================
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> reserved;

        for (auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9) {
                reserved[row] |= (1 << col);
            }
        }

        int ans = (n - reserved.size()) * 2;

        for (auto& [row, mask] : reserved) {
            bool left = !(mask & ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5)));
            bool right = !(mask & ((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9)));
            bool middle = !(mask & ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)));

            if (left && right)
                ans += 2;
            else if (left || right || middle)
                ans += 1;
        }

        return ans;
    }
};

int main() {
    Solution obj;

    int n = 3;

    vector<vector<int>> reservedSeats = {
        {1, 2},
        {1, 3},
        {1, 8},
        {2, 6}
    };

    cout << obj.maxNumberOfFamilies(n, reservedSeats) << endl;

    return 0;
}

/*

===========================
Problem Statement
===========================

There are n rows in a cinema and each row contains 10 seats.

Seats are numbered from 1 to 10.

A family of 4 people wants to sit together.

The possible groups are:

    [2,3,4,5]
    [4,5,6,7]
    [6,7,8,9]

Some seats are already reserved.

Return the maximum number of families that can be seated.

Leetcode 1386 - Cinema Seat Allocation


===========================
Example
===========================

Input:

n = 3

reservedSeats =
[
    [1,2],
    [1,3],
    [1,8],
    [2,6]
]

Output:

4

Explanation:

Row 1:
Seats 2, 3 and 8 are reserved.

Possible group:

    [4,5,6,7]

=> 1 family


Row 2:
Seat 6 is reserved.

Possible group:

    [2,3,4,5]

=> 1 family


Row 3:
No seats are reserved.

=> 2 families


Total:

    1 + 1 + 2 = 4


==========================================================
Brute Force Approach
==========================================================

Idea:

Store all seats of every row.

For every row, check the three possible groups:

    LEFT   = [2,3,4,5]
    MIDDLE = [4,5,6,7]
    RIGHT  = [6,7,8,9]

If LEFT and RIGHT are both available:

    => 2 families

Otherwise, if any one of the three groups is available:

    => 1 family


Pseudo Code:

create reserved[row][seat]

answer = 0

for row = 1 to n:

    check LEFT
    check RIGHT
    check MIDDLE

    if LEFT and RIGHT are free:
        answer += 2

    else if LEFT or RIGHT or MIDDLE is free:
        answer += 1

return answer


----------------------------------------------------------
Complete Brute Force Code
----------------------------------------------------------

class Solution {
public:

    int maxNumberOfFamilies(
        int n,
        vector<vector<int>>& reservedSeats
    ) {

        vector<vector<bool>> seat(
            n + 1,
            vector<bool>(11, false)
        );

        for (auto& x : reservedSeats) {
            seat[x[0]][x[1]] = true;
        }

        int ans = 0;

        for (int row = 1; row <= n; row++) {

            bool left = true;
            bool right = true;
            bool middle = true;

            for (int col = 2; col <= 5; col++) {
                if (seat[row][col])
                    left = false;
            }

            for (int col = 6; col <= 9; col++) {
                if (seat[row][col])
                    right = false;
            }

            for (int col = 4; col <= 7; col++) {
                if (seat[row][col])
                    middle = false;
            }

            if (left && right)
                ans += 2;

            else if (left || right || middle)
                ans += 1;
        }

        return ans;
    }
};


Time Complexity:

O(N + M)

where:

N = number of rows
M = number of reserved seats


Space Complexity:

O(N)

We store the seats of every row.


==========================================================
Optimal Approach
==========================================================

Observation:

Only seats 2 to 9 are important.

Seats 1 and 10 can never be part of a group of 4.

For every row, there are only three possible groups:

    LEFT   = [2,3,4,5]
    MIDDLE = [4,5,6,7]
    RIGHT  = [6,7,8,9]


If:

    LEFT && RIGHT

then we can place:

    2 families


Otherwise, if:

    LEFT || MIDDLE || RIGHT

then we can place:

    1 family


Important Observation:

n can be very large.

But only rows containing reserved seats can affect the answer.

Therefore, instead of storing every row, we store only affected rows
using an unordered_map.


Intuition:

Suppose a row has no relevant reserved seats.

Then that row can always accommodate:

    2 families

So initially:

    answer = (n - affectedRows) * 2


For every affected row, we check the three possible groups.

A bitmask is used to store the reserved seats of a row.

For example:

    mask & (1 << 2)

checks whether seat 2 is reserved.


Pseudo Code:

create map:

    row -> bitmask

for every reserved seat:

    row = seat[0]
    col = seat[1]

    if col is between 2 and 9:
        mark col in the bitmask


answer = (n - affectedRows) * 2


for every affected row:

    check LEFT
    check RIGHT
    check MIDDLE

    if LEFT && RIGHT:
        answer += 2

    else if LEFT || RIGHT || MIDDLE:
        answer += 1


return answer


----------------------------------------------------------
Complete Optimal Code - Leetcode Version
----------------------------------------------------------

class Solution {
public:

    int maxNumberOfFamilies(
        int n,
        vector<vector<int>>& reservedSeats
    ) {

        unordered_map<int, int> reserved;

        for (auto& seat : reservedSeats) {

            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9) {
                reserved[row] |= (1 << col);
            }
        }

        int ans = (n - reserved.size()) * 2;

        for (auto& [row, mask] : reserved) {

            bool left =
                !(mask & (
                    (1 << 2) |
                    (1 << 3) |
                    (1 << 4) |
                    (1 << 5)
                ));

            bool right =
                !(mask & (
                    (1 << 6) |
                    (1 << 7) |
                    (1 << 8) |
                    (1 << 9)
                ));

            bool middle =
                !(mask & (
                    (1 << 4) |
                    (1 << 5) |
                    (1 << 6) |
                    (1 << 7)
                ));

            if (left && right)
                ans += 2;

            else if (left || right || middle)
                ans += 1;
        }

        return ans;
    }
};


Time Complexity:

O(M) average

where:

M = number of reserved seats

Each reserved seat is processed once.

Each affected row is checked in O(1).


Space Complexity:

O(M)

The unordered_map stores only rows that contain relevant reserved seats.


==========================================================
Dry Run
==========================================================

Input:

n = 3

reservedSeats =
[
    [1,2],
    [1,3],
    [1,8],
    [2,6]
]


Step 1:
--------

Affected rows:

    {1,2}

Row 3 is unaffected.

Therefore:

    unaffected rows = 3 - 2
                    = 1

Contribution:

    1 * 2
    = 2 families


Step 2: Row 1
-------------

Reserved seats:

    2, 3, 8


LEFT:

    [2,3,4,5]

Seats 2 and 3 are reserved.

Therefore:

    LEFT = false


RIGHT:

    [6,7,8,9]

Seat 8 is reserved.

Therefore:

    RIGHT = false


MIDDLE:

    [4,5,6,7]

All seats are free.

Therefore:

    MIDDLE = true


So:

    +1 family


Step 3: Row 2
-------------

Reserved seat:

    6


LEFT:

    [2,3,4,5]

All seats are free.

Therefore:

    LEFT = true


RIGHT:

    [6,7,8,9]

Seat 6 is reserved.

Therefore:

    RIGHT = false


MIDDLE:

    [4,5,6,7]

Seat 6 is reserved.

Therefore:

    MIDDLE = false


So:

    +1 family


Final:

    Row 3 = 2
    Row 1 = 1
    Row 2 = 1

Total:

    2 + 1 + 1 = 4


==========================================================
Interview Notes
==========================================================

Pattern:

- Greedy
- Bitmask
- Hash Map
- Sparse Data Processing


Key Observation:

- Each row can contain at most 2 families.
- Only seats 2 to 9 matter.
- Possible groups are [2..5], [4..7], [6..9].
- [2..5] and [6..9] can both be used.
- [4..7] overlaps with both other groups.
- Completely unaffected rows always contribute 2 families.
- Store only affected rows instead of all n rows.


Common Mistakes:

1. Iterating over all n rows.

   n can be very large.

   Store only affected rows using unordered_map.


2. Forgetting seats 1 and 10.

   They are not part of any valid family group.


3. Checking only LEFT and RIGHT.

   MIDDLE can be the only available group.


4. Combining MIDDLE with LEFT or RIGHT.

   They overlap, so they cannot be used together.


5. Forgetting that an unaffected row gives 2 families.


When to use this approach:

- Very large N.
- Number of modifications/reservations is relatively small.
- Only a fixed number of configurations are possible.
- State can be represented using a bitmask.
- Unaffected states have a fixed/direct contribution.


General CP Pattern:

    Huge N + Sparse Updates
            |
            v
    Store only affected rows
            |
            v
    Represent state using Bitmask
            |
            v
    Process each affected row in O(1)


==========================================================

*/
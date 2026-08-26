#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int magicalString(int n)
    {
        if (n <= 0)
            return 0;

        if (n <= 3)
            return 1;

        vector<int> magical(n + 1);

        magical[0] = 1;
        magical[1] = 2;
        magical[2] = 2;

        int read = 2;
        int write = 3;
        int num = 1;
        int countOnes = 1;

        while (write < n)
        {
            int frequency = magical[read];

            for (int i = 0; i < frequency && write < n; i++)
            {
                magical[write++] = num;

                if (num == 1)
                    countOnes++;
            }

            num = 3 - num;
            read++;
        }

        return countOnes;
    }
};

int main()
{
    int n;
    cin >> n;

    Solution sol;

    cout << sol.magicalString(n) << '\n';

    return 0;
}

/*
============================================================
              LEETCODE 481 - MAGICAL STRING
============================================================

Problem Statement:
------------------
A magical string s consists of only '1' and '2' and obeys the
following rule:

    s = "1221121221221121122..."

The string is magical because when we group consecutive equal
characters, the sequence of group lengths is exactly the
magical string itself.

For example:

    s = 1 22 11 2 1 22 1 22 11 2 ...

Group lengths:

    1, 2, 2, 1, 1, 2, 1, 2, 2, ...

which gives the same magical sequence.

Given an integer n, return the number of '1's in the first
n characters of the magical string.


Example:
--------
Input:
    n = 6

Magical string:

    1 2 2 1 1 2

First 6 characters:

    "122112"

Number of '1's:

    3

Output:
    3


============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
Generate the magical string until its length becomes n.

At every step, use the current magical string itself to decide
how many times the next number should be written.

A direct implementation can use a string and repeatedly append
the current number according to the frequency indicated by the
read pointer.


Pseudo Code:
------------
if n <= 0:
    return 0

s = "122"

read = 2
num = '1'

while length(s) < n:

    frequency = s[read] - '0'

    append num frequency times

    switch num between '1' and '2'

    read++

count number of '1's in first n characters

return count


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int magicalString(int n) {

        if (n <= 0)
            return 0;

        string s = "122";

        int read = 2;
        char num = '1';

        while ((int)s.size() < n) {

            int frequency = s[read] - '0';

            for (int i = 0; i < frequency; i++) {

                if ((int)s.size() == n)
                    break;

                s.push_back(num);
            }

            num = (num == '1' ? '2' : '1');

            read++;
        }

        return count(s.begin(), s.end(), '1');
    }
};

Time Complexity:
----------------
O(n)

The string is generated up to length n and then traversed
to count the number of '1's.

Space Complexity:
-----------------
O(n)

The generated string is stored.


============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
The magical string starts as:

    1 2 2

Now look at the third character:

    2

This means the next number should occur twice.

The next number is:

    1

So append:

    1 1

Now:

    1 2 2 1 1

The next unread number is again:

    2

So append the next number twice.

The construction becomes:

    1 2 2 1 1 2 1 2 2 ...

We use two pointers:

    read
        -> tells us how many times the next number should occur

    write
        -> tells us where to place the generated numbers


Intuition:
----------
Start with:

    magical = [1, 2, 2]

The first two values establish the pattern.

Set:

    read = 2

The value at magical[read] tells us the frequency.

Initially:

    magical[2] = 2

So write the current number:

    1

twice:

    [1, 2, 2, 1, 1]

Then switch:

    1 -> 2

Move read forward.

Now:

    magical[3] = 1

So write:

    2

once:

    [1, 2, 2, 1, 1, 2]

Then switch:

    2 -> 1

Continue until n characters are generated.


Pseudo Code:
------------
if n <= 0:
    return 0

if n <= 3:
    return 1

magical[0] = 1
magical[1] = 2
magical[2] = 2

read = 2
write = 3
num = 1
countOnes = 1

while write < n:

    frequency = magical[read]

    repeat frequency times:

        if write == n:
            stop

        magical[write] = num

        if num == 1:
            countOnes++

        write++

    switch num:

        1 -> 2
        2 -> 1

    read++

return countOnes


Complete Optimal Code:
----------------------

class Solution {
public:
    int magicalString(int n) {

        if (n <= 0)
            return 0;

        if (n <= 3)
            return 1;

        vector<int> magical(n + 1);

        magical[0] = 1;
        magical[1] = 2;
        magical[2] = 2;

        int read = 2;
        int write = 3;
        int num = 1;
        int countOnes = 1;

        while (write < n) {

            int frequency = magical[read];

            for (int i = 0;
                 i < frequency && write < n;
                 i++) {

                magical[write++] = num;

                if (num == 1)
                    countOnes++;
            }

            num = 3 - num;

            read++;
        }

        return countOnes;
    }
};

Time Complexity:
----------------
O(n)

Every position is generated exactly once.

Space Complexity:
-----------------
O(n)

We store the magical string in a vector.


============================================================
DRY RUN WITH EXAMPLE
============================================================

Example:

    n = 6


Initial:

    magical = [1, 2, 2]

    read = 2
    write = 3
    num = 1
    countOnes = 1


Iteration 1:
------------
Read:

    magical[2] = 2

Therefore write '1' twice.

Before:

    [1, 2, 2]

After:

    [1, 2, 2, 1, 1]

countOnes:

    3

Switch:

    num = 2

Move:

    read = 3


Iteration 2:
------------
Read:

    magical[3] = 1

Therefore write '2' once.

Array:

    [1, 2, 2, 1, 1, 2]

write = 6

Now:

    write == n

Stop.


First 6 characters:

    1 2 2 1 1 2

Number of ones:

    3

Answer:

    3


============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Simulation / Two Pointers / Sequence Generation


Key Observation:
----------------
The magical string describes its own run lengths.

For example:

    Magical string:
        1 2 2 1 1 2 ...

The values:

    1, 2, 2, 1, 1, 2 ...

tell us how many times the next alternating number should
be written.

Use:

    read pointer
        -> frequency

    write pointer
        -> position where new value is inserted


Common Mistakes:
----------------
1. Forgetting the initial sequence:

       1 2 2

2. Starting read from the wrong index.

   We start with:

       read = 2

3. Forgetting to alternate between 1 and 2.

   Use:

       num = 3 - num

   This changes:

       1 -> 2
       2 -> 1

4. Generating more than n characters.

   Always check:

       write < n

5. Counting ones before generating the complete required
   prefix.

6. Forgetting the special case:

       n <= 3

   The first three characters are:

       1 2 2

   Therefore there is exactly one '1'.


When to use this approach:
--------------------------
Use this technique when:

- A sequence describes how it should be generated.
- Previous elements determine the frequency of future elements.
- The problem asks for only a prefix of a self-describing sequence.
- Two pointers can separate reading the description from writing
  the generated sequence.


Quick Revision:
---------------

    Start:

        [1, 2, 2]

    read:
        tells frequency

    write:
        generates next values

    num:
        alternates 1 <-> 2

    countOnes:
        tracks number of 1s

    Time  = O(n)
    Space = O(n)


Core Pattern:

    frequency = magical[read]

    write 'num' frequency times

    num = 3 - num

    read++


============================================================
*/

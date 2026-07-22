#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int fib(int n)
  {
    if (n <= 1)
      return n;

    int a = 0, b = 1;

    for (int i = 2; i <= n; i++)
    {
      int c = a + b;
      a = b;
      b = c;
    }

    return b;
  }
};

int main()
{
  Solution obj;

  int n = 5;

  cout << obj.fib(n) << "\n";

  return 0;
}

/*

======================== PROBLEM STATEMENT ========================

LeetCode 509 - Fibonacci Number

The Fibonacci numbers, commonly denoted F(n), form a sequence,
where each number is the sum of the two preceding ones.

F(0) = 0
F(1) = 1

F(n) = F(n - 1) + F(n - 2)

Given n, return F(n).

==================================================================

Example

Input:

n = 4

Output:

3

Explanation:

F(0) = 0
F(1) = 1
F(2) = 1
F(3) = 2
F(4) = 3


==================================================================
====================== BRUTE FORCE APPROACH =======================

Idea

Use recursion directly.

For every n:

F(n) = F(n-1) + F(n-2)

Keep splitting until base cases.

Problem:

The same Fibonacci values are calculated repeatedly.


--------------------------------------------------

Pseudo Code

function fib(n):

    if n <= 1:
        return n

    return fib(n-1) + fib(n-2)


--------------------------------------------------

Complete Brute Force Code

class Solution {

public:

    int fib(int n) {

        if(n <= 1)
            return n;

        return fib(n-1) + fib(n-2);
    }

};


--------------------------------------------------

Time Complexity

O(2^N)

Each call creates two more calls.

--------------------------------------------------

Space Complexity

O(N)

Due to recursion stack.


==================================================================
====================== OPTIMAL APPROACH ===========================

Observation

Every Fibonacci number only depends on the previous two numbers.

We do not need to store the complete sequence.

Maintain:

a = F(i-2)

b = F(i-1)

Calculate:

c = a + b

Then shift:

a = b

b = c


--------------------------------------------------

Intuition

Instead of recursively solving smaller problems again and again,
calculate Fibonacci numbers from bottom to top.

This removes repeated calculations.


--------------------------------------------------

Pseudo Code

function fib(n):

    if n <= 1:
        return n

    a = 0
    b = 1

    for i from 2 to n:

        c = a + b

        a = b

        b = c

    return b


--------------------------------------------------

Complete Optimal Code

#include<bits/stdc++.h>
using namespace std;

class Solution {

public:

    int fib(int n) {

        if(n <= 1)
            return n;

        int a = 0;
        int b = 1;

        for(int i = 2; i <= n; i++) {

            int c = a + b;

            a = b;
            b = c;
        }

        return b;
    }
};


--------------------------------------------------

Time Complexity

O(N)

One loop from 2 to n.


--------------------------------------------------

Space Complexity

O(1)

Only three variables are used.


==================================================================
======================== DRY RUN ==================================

Example:

n = 5


Initial:

a = 0
b = 1


i = 2

c = 1

a = 1
b = 1


i = 3

c = 2

a = 1
b = 2


i = 4

c = 3

a = 2
b = 3


i = 5

c = 5

a = 3
b = 5


Answer = 5


==================================================================
====================== INTERVIEW NOTES ============================

Pattern

Dynamic Programming (DP)

Specifically:

Space Optimized 1D DP


--------------------------------------------------

Key Observation

When a DP state depends only on previous few states,
we can optimize memory.

Here:

F(n) depends only on

F(n-1)

and

F(n-2)


--------------------------------------------------

Common Mistakes

1. Forgetting base cases:

F(0)=0

F(1)=1


2. Using recursion without memoization.

3. Using an array when only two previous values are needed.

4. Integer overflow for very large n.


--------------------------------------------------

When to use this approach

Use this pattern when:

- A sequence depends on previous values.
- Only recent DP states are required.
- Memory optimization is needed.

Examples:

- Fibonacci
- Climbing Stairs
- House Robber (space optimized)
- Linear DP problems


==================================================================

*/

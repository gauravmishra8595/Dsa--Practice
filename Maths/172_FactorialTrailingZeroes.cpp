#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    int trailingZeroes(int n)
    {

        int ans = 0;

        while (n > 0)
        {

            n /= 5;
            ans += n;
        }

        return ans;
    }
};

int main()
{

    Solution sol;

    int n = 100;

    cout << sol.trailingZeroes(n);

    return 0;
}

/*

============================================================
Problem Statement
============================================================

LeetCode 172: Factorial Trailing Zeroes

Given an integer n, return the number of trailing zeroes in n!.

Trailing zero means the number of consecutive 0s at the end of
a number.


Example:

Input:

n = 5


5! = 120


Output:

1


Explanation:

There is one zero at the end of 120.


============================================================
Brute Force Approach
============================================================

Idea:
------

Calculate n!.

Then count how many zeros are present at the end.

The problem is that factorial grows extremely large, causing
integer overflow even for moderate n.


Pseudo Code:
------------

function trailingZeroes(n):

    factorial = 1


    for i from 1 to n:

        factorial *= i


    count = 0


    while factorial % 10 == 0:

        count++

        factorial /= 10


    return count



Complete Brute Force Code:

------------------------------------------------------------

// Not feasible because factorial becomes extremely large

class Solution {

public:

    int trailingZeroes(int n) {

        long long fact = 1;


        for(int i = 1; i <= n; i++) {

            fact *= i;
        }


        int count = 0;


        while(fact % 10 == 0) {

            count++;

            fact /= 10;
        }


        return count;
    }
};


------------------------------------------------------------


Time Complexity:

O(n)


Space Complexity:

O(1)


============================================================
Optimal Approach
============================================================

Observation:
------------

Trailing zeroes are created by multiplying:

10 = 2 * 5


In factorials:

There are always more factors of 2 than factors of 5.

So the answer depends only on how many times 5 appears in the
factorization of numbers from 1 to n.


Intuition:
----------

Count multiples of 5:

n / 5

Count multiples of 25:

n / 25

Count multiples of 125:

n / 125


because numbers like 25 contribute two factors of 5,
125 contribute three factors of 5, etc.


Formula:

answer = n/5 + n/25 + n/125 + ...


Pseudo Code:
------------

function trailingZeroes(n):

    answer = 0


    while n > 0:

        n = n / 5

        answer += n


    return answer



Complete Optimal Code:

------------------------------------------------------------

class Solution {

public:

    int trailingZeroes(int n) {

        int ans = 0;


        while(n > 0) {

            n /= 5;

            ans += n;
        }


        return ans;
    }
};


------------------------------------------------------------


Time Complexity:

O(log5(n))


Space Complexity:

O(1)


============================================================
Dry Run With Example
============================================================

Input:

n = 100


First iteration:

n = 100 / 5

n = 20

ans = 20


Second iteration:

n = 20 / 5

n = 4

ans = 24


Third iteration:

n = 4 / 5

n = 0

ans = 24


Therefore:

100! has 24 trailing zeroes.


============================================================
Interview Notes
============================================================

Pattern:

Mathematical Observation


Key Observation:

Trailing zeros depend on pairs of:

2 * 5

Since factors of 2 are always greater, only count factors of 5.


Common Mistakes:

1. Calculating factorial directly.

2. Forgetting numbers like 25 contribute two factors of 5.

3. Using n/5 only and missing higher powers.

4. Integer overflow due to huge factorial.


When to use this approach:

Use when:

- Finding trailing zeros in factorial.
- Counting repeated prime factors.
- Factorial value itself is too large to calculate.


============================================================

*/

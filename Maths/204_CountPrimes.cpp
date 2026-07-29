#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    int countPrimes(int n)
    {

        if (n <= 2)
            return 0;

        vector<bool> isPrime(n, true);

        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i * i < n; i++)
        {

            if (isPrime[i])
            {

                for (int j = i * i; j < n; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }

        int count = 0;

        for (int i = 2; i < n; i++)
        {

            if (isPrime[i])
                count++;
        }

        return count;
    }
};

int main()
{

    Solution sol;

    int n = 10;

    cout << sol.countPrimes(n);

    return 0;
}

/*

============================================================
Problem Statement
============================================================

LeetCode 204: Count Primes

Given an integer n, return the number of prime numbers that
are strictly less than n.


Example:

Input:

n = 10


Prime numbers less than 10:

2, 3, 5, 7


Output:

4


============================================================
Brute Force Approach
============================================================

Idea:
------

For every number from 2 to n-1:

1. Check if the number is prime.
2. If prime, increase count.


A number is prime if it has no divisor between 2 and sqrt(n).


Pseudo Code:
------------

function countPrimes(n):

    count = 0

    for i from 2 to n-1:

        if isPrime(i):

            count++


    return count



isPrime(x):

    for i from 2 to sqrt(x):

        if x % i == 0:

            return false


    return true


Complete Brute Force Code:

------------------------------------------------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {

public:

    bool isPrime(int x) {

        if(x <= 1)
            return false;


        for(int i = 2; i * i <= x; i++) {

            if(x % i == 0)
                return false;
        }


        return true;
    }


    int countPrimes(int n) {

        int count = 0;


        for(int i = 2; i < n; i++) {

            if(isPrime(i))
                count++;
        }


        return count;
    }
};


------------------------------------------------------------


Time Complexity:
----------------

O(n * sqrt(n))

Checking every number individually.


Space Complexity:
-----------------

O(1)


============================================================
Optimal Approach
============================================================

Observation:
------------

Instead of checking every number separately, we can eliminate
all multiples of prime numbers.

This is called the Sieve of Eratosthenes.


Intuition:
----------

Initially assume every number is prime.

Starting from 2:

- Mark all multiples of 2 as non-prime.
- Move to next prime.
- Mark its multiples.

At the end, remaining marked numbers are primes.


Important:

Start marking from i*i because smaller multiples are already
handled by smaller primes.


Pseudo Code:
------------

function countPrimes(n):

    create boolean array prime[n]

    mark all as true


    prime[0] = prime[1] = false


    for i from 2 to sqrt(n):

        if prime[i]:

            mark all multiples of i as false


    count true values

    return count



Complete Optimal Code:

------------------------------------------------------------

class Solution {

public:

    int countPrimes(int n) {


        if(n <= 2)
            return 0;


        vector<bool> prime(n,true);


        prime[0] = prime[1] = false;


        for(int i = 2; i*i < n; i++) {


            if(prime[i]) {


                for(int j = i*i; j < n; j += i) {

                    prime[j] = false;
                }
            }
        }


        int ans = 0;


        for(int i = 2; i < n; i++) {

            if(prime[i])
                ans++;
        }


        return ans;
    }
};


------------------------------------------------------------


Time Complexity:
----------------

O(n log(log n))

Sieve removes multiples efficiently.


Space Complexity:
-----------------

O(n)

Boolean array used for marking primes.


============================================================
Dry Run With Example
============================================================

Input:

n = 10


Initial:

[0,1,2,3,4,5,6,7,8,9]

All marked prime.


Remove:

0 and 1


i = 2:

Mark multiples:

4,6,8


Array:

2,3,5,7,9 are still possible


i = 3:

Mark multiples:

9


Remaining primes:

2,3,5,7


Count:

4


Output:

4


============================================================
Interview Notes
============================================================

Pattern:

Mathematical Algorithm / Sieve of Eratosthenes


Key Observation:

Prime checking individually is expensive.

Generate all primes together by eliminating multiples.


Common Mistakes:

1. Starting inner loop from i instead of i*i.

2. Forgetting that n is exclusive.

3. Not handling n <= 2.

4. Integer overflow in i*i for very large constraints.


When to use this approach:

Use Sieve when:

- Need many prime numbers in a range.
- Need count of primes smaller than n.
- n is large and individual checking is too slow.


============================================================

*/

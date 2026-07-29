#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    vector<int> closestPrimes(int left, int right)
    {

        vector<bool> isPrime(right + 1, true);

        isPrime[0] = isPrime[1] = false;

        // Sieve of Eratosthenes
        for (int i = 2; i * i <= right; i++)
        {

            if (isPrime[i])
            {

                for (int j = i * i; j <= right; j += i)
                {

                    isPrime[j] = false;
                }
            }
        }

        vector<int> primes;

        for (int i = left; i <= right; i++)
        {

            if (isPrime[i])
                primes.push_back(i);
        }

        if (primes.size() < 2)
            return {-1, -1};

        int minimumDifference = INT_MAX;

        vector<int> answer = {-1, -1};

        for (int i = 1; i < primes.size(); i++)
        {

            int difference = primes[i] - primes[i - 1];

            if (difference < minimumDifference)
            {

                minimumDifference = difference;

                answer = {primes[i - 1], primes[i]};
            }
        }

        return answer;
    }
};

int main()
{

    Solution sol;

    int left = 10;
    int right = 50;

    vector<int> ans = sol.closestPrimes(left, right);

    cout << "[" << ans[0] << ", " << ans[1] << "]";

    return 0;
}

/*

============================================================
Problem Statement
============================================================

LeetCode 2523: Closest Prime Numbers in Range

Given two positive integers left and right, find two prime
numbers num1 and num2 such that:

1. left <= num1 < num2 <= right
2. num2 - num1 is minimum

Return the pair with the smallest difference.

If no such pair exists, return {-1, -1}.


Example:

Input:

left = 10
right = 50


Prime numbers:

11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47


Closest pair:

(11,13)


Output:

[11,13]


============================================================
Brute Force Approach
============================================================

Idea:
------

Check every number in the range.

For each number:

1. Check if it is prime.
2. Store prime numbers.
3. Compare every possible pair to find minimum difference.


Pseudo Code:
------------

function closestPrimes(left,right):

    primes = empty list


    for i from left to right:

        if isPrime(i):

            add i to primes


    minimum = infinity


    for every pair (i,j):

        update minimum difference


    return answer



Complete Brute Force Code:

------------------------------------------------------------

// Checking primality for every number

class Solution {

public:

    bool isPrime(int n) {

        if(n < 2)
            return false;


        for(int i = 2; i*i <= n; i++) {

            if(n % i == 0)
                return false;
        }


        return true;
    }


    vector<int> closestPrimes(int left,int right) {


        vector<int> primes;


        for(int i = left; i <= right; i++) {

            if(isPrime(i))
                primes.push_back(i);
        }


        int diff = INT_MAX;

        vector<int> ans = {-1,-1};


        for(int i = 0; i < primes.size(); i++) {

            for(int j = i+1; j < primes.size(); j++) {


                if(primes[j]-primes[i] < diff) {

                    diff = primes[j]-primes[i];

                    ans = {primes[i],primes[j]};
                }
            }
        }


        return ans;
    }
};


------------------------------------------------------------


Time Complexity:

O(n * sqrt(n) + p^2)

where p is number of primes.


Space Complexity:

O(p)


============================================================
Optimal Approach
============================================================

Observation:
------------

Prime checking for every number is expensive.

Use Sieve of Eratosthenes to find all primes in the range.


Intuition:
----------

After generating sorted primes:

Closest pair must always be two adjacent primes.

Because any prime between two selected primes would create a
smaller difference.


Pseudo Code:
------------

function closestPrimes(left,right):

    create sieve array


    mark all primes using Sieve


    store all primes between left and right


    compare adjacent primes


    return minimum difference pair



Complete Optimal Code:

------------------------------------------------------------

class Solution {

public:

    vector<int> closestPrimes(int left,int right) {


        vector<bool> prime(right+1,true);


        prime[0]=prime[1]=false;


        for(int i=2;i*i<=right;i++) {

            if(prime[i]) {

                for(int j=i*i;j<=right;j+=i)

                    prime[j]=false;
            }
        }


        vector<int> primes;


        for(int i=left;i<=right;i++) {

            if(prime[i])

                primes.push_back(i);
        }


        if(primes.size()<2)

            return {-1,-1};


        int best=INT_MAX;

        vector<int> ans;


        for(int i=1;i<primes.size();i++) {


            if(primes[i]-primes[i-1]<best) {

                best=primes[i]-primes[i-1];

                ans={primes[i-1],primes[i]};
            }
        }


        return ans;
    }
};


------------------------------------------------------------


Time Complexity:

O(n log(log n))


Space Complexity:

O(n)


============================================================
Dry Run
============================================================

Input:

left = 10
right = 50


Sieve gives:

11,13,17,19,23,29,31,37,41,43,47


Compare adjacent pairs:

13-11 = 2

17-13 = 4

19-17 = 2

23-19 = 4

...


Minimum difference:

2


Answer:

[11,13]


============================================================
Interview Notes
============================================================

Pattern:

Sieve of Eratosthenes + Two Pointer Style Traversal


Key Observation:

Closest primes will always be adjacent in the sorted prime
list.


Common Mistakes:

1. Forgetting to handle less than two primes.

2. Starting sieve marking from i instead of i*i.

3. Including numbers outside the range.

4. Comparing all pairs unnecessarily.


When to use this approach:

Use when:

- Finding prime numbers in a range.
- Multiple prime queries are required.
- Need efficient prime generation.


============================================================

*/

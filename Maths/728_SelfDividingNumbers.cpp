#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool selfDivide(int num)
    {
        int temp = num;

        while (temp)
        {
            int digit = temp % 10;

            if (digit == 0 || num % digit != 0)
                return false;

            temp /= 10;
        }

        return true;
    }

    vector<int> selfDividingNumbers(int left, int right)
    {
        vector<int> ans;

        for (int i = left; i <= right; i++)
        {
            if (selfDivide(i))
                ans.push_back(i);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    int left = 1, right = 22;

    vector<int> ans = obj.selfDividingNumbers(left, right);

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*

===========================
LeetCode 728
Self Dividing Numbers
===========================

--------------------------------------------------
Problem Statement
--------------------------------------------------
A self-dividing number is a number that is divisible
by every digit it contains.

A self-dividing number cannot contain the digit 0.

Given two integers left and right, return a list of
all the self-dividing numbers in the range
[left, right].

--------------------------------------------------
Example
--------------------------------------------------

Input:
left = 1
right = 22

Output:
[1,2,3,4,5,6,7,8,9,11,12,15,22]

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
-----
For every number in the range:
Extract each digit.
If any digit is 0 or doesn't divide the number,
discard it.
Otherwise include it in the answer.

Pseudo Code
------------
for num = left to right
    temp = num

    while temp > 0
        digit = temp % 10

        if digit == 0
            invalid

        if num % digit != 0
            invalid

        temp /= 10

    if valid
        store num

Complete Brute Force Code
-------------------------

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {

        vector<int> ans;

        for(int num = left; num <= right; num++) {

            int temp = num;
            bool ok = true;

            while(temp) {

                int digit = temp % 10;

                if(digit == 0 || num % digit != 0) {
                    ok = false;
                    break;
                }

                temp /= 10;
            }

            if(ok)
                ans.push_back(num);
        }

        return ans;
    }
};

Time Complexity
---------------
O((right-left+1) × log10(right))

Space Complexity
----------------
O(1)
(excluding output array)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
Each digit only needs to be checked once.

Separating the digit-checking logic into a helper
function keeps the code clean and reusable.

Intuition
---------
Traverse every number.

Extract digits one by one.

If a digit is zero or doesn't divide the original
number, reject it immediately.

Otherwise, if every digit passes,
store the number.

Pseudo Code
------------
function selfDivide(num)

    temp = num

    while temp

        digit = temp % 10

        if digit == 0
            return false

        if num % digit != 0
            return false

        temp /= 10

    return true

for i = left to right

    if selfDivide(i)
        add to answer

Complete Optimal Code
---------------------

class Solution {
public:
    bool selfDivide(int num) {
        int temp = num;

        while(temp) {
            int digit = temp % 10;

            if(digit == 0 || num % digit != 0)
                return false;

            temp /= 10;
        }

        return true;
    }

    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ans;

        for(int i = left; i <= right; i++) {
            if(selfDivide(i))
                ans.push_back(i);
        }

        return ans;
    }
};

Time Complexity
---------------
O((right-left+1) × log10(right))

Space Complexity
----------------
O(1)
(excluding output array)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
left = 10
right = 15

10
digit = 0
Rejected

11
1 divides 11
1 divides 11
Accepted

12
2 divides 12
1 divides 12
Accepted

13
3 does not divide 13
Rejected

14
4 does not divide 14
Rejected

15
5 divides 15
1 divides 15
Accepted

Answer:
[11,12,15]

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Simulation + Digit Extraction

Key Observation
---------------
Each digit is checked independently.

Any occurrence of digit 0 immediately disqualifies
the number.

Common Mistakes
---------------
1. Forgetting to reject numbers containing 0.
2. Modifying the original number while extracting digits.
3. Using the modified value instead of the original
   for divisibility checks.

When to use this approach
-------------------------
Whenever a problem involves checking a property of
individual digits of a number, repeatedly extract
digits using %10 and /10.

*/
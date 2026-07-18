#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findGCD(vector<int> &nums)
    {
        int mn = nums[0], mx = nums[0];

        for (int x : nums)
        {
            mn = min(mn, x);
            mx = max(mx, x);
        }

        return __gcd(mn, mx);
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {2, 5, 6, 9, 10};

    cout << "GCD of Min and Max = " << obj.findGCD(nums) << endl;

    return 0;
}

/*

==========================
LeetCode 1979 - Find Greatest Common Divisor of Array
==========================

Problem Statement
-----------------
Given an integer array nums, return the greatest common divisor (GCD)
of the smallest number and largest number in nums.

The GCD of two numbers is the largest positive integer that divides both numbers.

--------------------------------------------------

Example
-------

Input:
nums = [2,5,6,9,10]

Output:
2

Explanation:
Minimum = 2
Maximum = 10
GCD(2,10) = 2

--------------------------------------------------
BRUTE FORCE APPROACH
--------------------------------------------------

Idea
----
1. Find the minimum and maximum element.
2. Start from min(minimum, maximum) and move downward.
3. First number dividing both is the answer.

Pseudo Code
-----------

mn = minimum element
mx = maximum element

for i = min(mn,mx) down to 1
    if mn % i == 0 AND mx % i == 0
        return i

Complete Brute Force Code
-------------------------

class Solution {
public:
    int findGCD(vector<int>& nums) {

        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        for(int i=min(mn,mx); i>=1; i--){
            if(mn%i==0 && mx%i==0)
                return i;
        }

        return 1;
    }
};

Time Complexity
---------------
O(n + min(mn,mx))

Space Complexity
----------------
O(1)

--------------------------------------------------
OPTIMAL APPROACH
--------------------------------------------------

Observation
-----------
The problem only asks for the GCD of the minimum and maximum element.

Instead of checking every divisor,
use Euclid's Algorithm to compute GCD efficiently.

Intuition
---------
1. Traverse once to find minimum and maximum.
2. Apply gcd(minimum, maximum).
3. Return the answer.

Pseudo Code
-----------

mn = nums[0]
mx = nums[0]

for every x in nums
    mn = min(mn,x)
    mx = max(mx,x)

return gcd(mn,mx)

Complete Optimal Code
---------------------

class Solution {
public:
    int findGCD(vector<int>& nums) {

        int mn = nums[0];
        int mx = nums[0];

        for(int x : nums){
            mn = min(mn,x);
            mx = max(mx,x);
        }

        return __gcd(mn,mx);
    }
};

Time Complexity
---------------
Finding min & max : O(n)

Euclid GCD        : O(log(min(mn,mx)))

Overall           : O(n)

Space Complexity
----------------
O(1)

--------------------------------------------------
Dry Run
--------------------------------------------------

nums = [2,5,6,9,10]

Initially
mn = 2
mx = 2

Read 5
mn = 2
mx = 5

Read 6
mn = 2
mx = 6

Read 9
mn = 2
mx = 9

Read 10
mn = 2
mx = 10

Answer

gcd(2,10)
= gcd(10,2)
= gcd(2,0)
= 2

Return 2

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Array + Mathematics (GCD)

Key Observation
---------------
The GCD of the entire array is NOT required.

Only:
GCD(minimum element, maximum element)

Common Mistakes
---------------
1. Computing GCD of every element.
2. Sorting the array unnecessarily (O(n log n)).
3. Using brute-force divisor checking.

When to use this approach
-------------------------
Whenever the problem asks for GCD of only two numbers
that must first be identified from an array (min/max),
find them in one traversal and apply Euclid's Algorithm.

*/
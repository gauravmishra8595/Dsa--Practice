#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------
// Optimal Solution (One Pass)
// Time Complexity: O(n)
// Space Complexity: O(1)
// ---------------------------------------------------------
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int max1 = INT_MIN, max2 = INT_MIN;

        for (int x : nums)
        {
            if (x > max1)
            {
                max2 = max1;
                max1 = x;
            }
            else if (x > max2)
            {
                max2 = x;
            }
        }

        return (max1 - 1) * (max2 - 1);
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {3, 4, 5, 2};

    cout << obj.maxProduct(nums);

    return 0;
}

/*

============================================================
                LEETCODE 1464
Maximum Product of Two Elements in an Array
============================================================

------------------------------------------------------------
Problem Statement
------------------------------------------------------------
Given an integer array nums, choose two different indices i and j.

Return the maximum value of:

(nums[i] - 1) * (nums[j] - 1)

------------------------------------------------------------
Example
------------------------------------------------------------

Input:
nums = [3,4,5,2]

Output:
12

Explanation:
Choose 5 and 4.

(5-1)*(4-1)
=4*3
=12

------------------------------------------------------------
Approach 1 : Brute Force
------------------------------------------------------------

Idea
-----
Try every possible pair and calculate the product.
Keep track of the maximum answer.

Pseudo Code
------------

ans = 0

for i = 0 to n-1
    for j = i+1 to n-1
        ans = max(ans,
                  (nums[i]-1)*(nums[j]-1))

return ans

Complete Brute Force Code
-------------------------

class Solution {
public:
    int maxProduct(vector<int>& nums) {

        int ans = 0;

        for(int i=0;i<nums.size();i++){

            for(int j=i+1;j<nums.size();j++){

                ans = max(ans,
                         (nums[i]-1)*(nums[j]-1));

            }

        }

        return ans;
    }
};

Time Complexity
---------------
O(n²)

Space Complexity
----------------
O(1)

============================================================
Approach 2 : Sorting
============================================================

Idea
-----
Sort the array.

The two largest numbers will always produce the maximum product.

Pseudo Code
------------

sort(nums)

n = nums.size()

return (nums[n-1]-1)*(nums[n-2]-1)

Complete Sorting Code
---------------------

class Solution {
public:
    int maxProduct(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int n = nums.size();

        return (nums[n-1]-1)*(nums[n-2]-1);
    }
};

Time Complexity
---------------
O(n log n)

Space Complexity
----------------
O(1)

============================================================
Approach 3 : Optimal (One Pass)
============================================================

Observation
-----------
The answer only depends on the two largest numbers.

No need to sort the entire array.

Maintain:
largest element
second largest element

Intuition
---------
Traverse the array once.

If current element is greater than largest:
    secondLargest = largest
    largest = current

Else if current element is greater than secondLargest:
    secondLargest = current

Finally compute

(largest-1)*(secondLargest-1)

Pseudo Code
------------

largest = -INF
secondLargest = -INF

for each number

    if number > largest

        secondLargest = largest
        largest = number

    else if number > secondLargest

        secondLargest = number

return (largest-1)*(secondLargest-1)

Complete Optimal Code
---------------------

class Solution {
public:
    int maxProduct(vector<int>& nums) {

        int largest = INT_MIN;
        int secondLargest = INT_MIN;

        for(int x : nums){

            if(x > largest){

                secondLargest = largest;
                largest = x;
            }

            else if(x > secondLargest){

                secondLargest = x;
            }
        }

        return (largest-1)*(secondLargest-1);
    }
};

Time Complexity
---------------
O(n)

Space Complexity
----------------
O(1)

============================================================
Dry Run
============================================================

nums = [3,4,5,2]

largest = -INF
secondLargest = -INF

Read 3

largest = 3
secondLargest = -INF

Read 4

largest = 4
secondLargest = 3

Read 5

largest = 5
secondLargest = 4

Read 2

Nothing changes

Answer

(5-1)*(4-1)

4*3

12

============================================================
Interview Notes
============================================================

Pattern
-------
✔ Array
✔ One Pass
✔ Tracking Largest Elements
✔ Greedy Observation

Key Observation
---------------
Only the two maximum values matter.

Sorting is unnecessary.

Maintain the top two values while traversing.

Common Mistakes
---------------
1. Forgetting to subtract 1 before multiplication.

2. Updating second largest incorrectly.

3. Using only one 'if' instead of
   'if ... else if ...'

4. Initializing largest values with 0 instead of INT_MIN.

When to use this approach
-------------------------
Whenever the problem asks for:

• Largest two numbers
• Second maximum
• Top K (small constant K)
• Maximum pair computation

Use one-pass tracking instead of sorting whenever possible.

============================================================

*/
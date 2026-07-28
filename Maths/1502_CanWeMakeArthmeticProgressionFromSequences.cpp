#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool canMakeArithmeticProgression(vector<int> &arr)
    {
        sort(arr.begin(), arr.end());

        int diff = arr[1] - arr[0];

        for (int i = 2; i < arr.size(); i++)
        {
            if (arr[i] - arr[i - 1] != diff)
                return false;
        }

        return true;
    }
};

int main()
{
    Solution obj;

    vector<int> arr = {3, 5, 1};

    if (obj.canMakeArithmeticProgression(arr))
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}

/*

===========================
LeetCode 1502
Can Make Arithmetic Progression From Sequence
===========================

--------------------------------------------------
Problem Statement
--------------------------------------------------
Given an array of numbers arr, return true if the array can be rearranged
to form an arithmetic progression. Otherwise, return false.

An arithmetic progression is a sequence where the difference between every
two consecutive elements is the same.

--------------------------------------------------
Example
--------------------------------------------------

Input:
arr = [3,5,1]

Output:
true

Explanation:
After rearranging:
[1,3,5]
Difference = 2

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
-----
Generate every possible permutation of the array and check whether any
permutation forms an arithmetic progression.

Pseudo Code
------------
Generate all permutations
    Check if adjacent difference remains constant
    If yes return true

Return false

Complete Brute Force Code
-------------------------

class Solution {
public:
    bool isAP(vector<int>& a){
        int d = a[1] - a[0];
        for(int i=2;i<a.size();i++){
            if(a[i]-a[i-1]!=d)
                return false;
        }
        return true;
    }

    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        do{
            if(isAP(arr))
                return true;
        }while(next_permutation(arr.begin(),arr.end()));

        return false;
    }
};

Time Complexity
---------------
O(N! * N)

Space Complexity
----------------
O(N)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
If the array can be rearranged into an arithmetic progression,
then after sorting it, the elements must already appear in the
required order.

Intuition
---------
Sort the array.

Compute the common difference using the first two elements.

Traverse the remaining elements and verify that every consecutive
difference equals the common difference.

If any difference differs, answer is false.

Otherwise true.

Pseudo Code
-----------
Sort array

diff = arr[1]-arr[0]

For i = 2 to n-1
    if arr[i]-arr[i-1] != diff
        return false

return true

Complete Optimal Code
---------------------

class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int diff = arr[1] - arr[0];

        for(int i = 2; i < arr.size(); i++) {
            if(arr[i] - arr[i - 1] != diff)
                return false;
        }

        return true;
    }
};

Time Complexity
---------------
Sorting : O(N log N)

Traversal : O(N)

Overall : O(N log N)

Space Complexity
----------------
O(1)
(ignoring sorting implementation space)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
arr = [3,5,1]

After Sorting:
[1,3,5]

diff = 3-1 = 2

i=2

5-3 = 2

Matches diff.

Return true.

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
Sorting + Checking Adjacent Difference

Key Observation
---------------
Sorting automatically places the numbers in the only possible order
for an arithmetic progression.

Common Mistakes
---------------
1. Forgetting to sort first.
2. Computing difference before sorting.
3. Starting loop from index 1 instead of 2.
4. Not handling duplicate values correctly (sorting naturally handles them).

When to use this approach
-------------------------
Whenever a problem asks whether elements can be rearranged into a
particular ordered pattern, sorting is often the simplest optimal strategy.

*/
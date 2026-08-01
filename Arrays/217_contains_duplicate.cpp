#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> st;

        for (int num : nums)
        {
            if (st.find(num) != st.end())
            {
                return true;
            }

            st.insert(num);
        }

        return false;
    }
};

int main()
{
    Solution sol;

    vector<int> nums = {1, 2, 3, 1};

    bool ans = sol.containsDuplicate(nums);

    cout << (ans ? "true" : "false");

    return 0;
}

/*

===========================================================
            LEETCODE 217 : CONTAINS DUPLICATE
===========================================================

Problem Statement:

Given an integer array nums, return true if any value appears
at least twice in the array, and return false if every element
is distinct.


-----------------------------------------------------------
Example:

Input:
nums = [1,2,3,1]

Output:
true

Explanation:
The number 1 appears more than once.


===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:

Compare every element with every other element.
If any two elements are equal, a duplicate exists.


Pseudo Code:

for i from 0 to n-1:
    for j from i+1 to n-1:
        if nums[i] == nums[j]:
            return true

return false


Complete Brute Force Code:

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        int n = nums.size();

        for(int i = 0; i < n; i++) {

            for(int j = i + 1; j < n; j++) {

                if(nums[i] == nums[j]) {
                    return true;
                }

            }
        }

        return false;
    }
};


Time Complexity:
O(n^2)

Space Complexity:
O(1)


===========================================================
OPTIMAL APPROACH
===========================================================

Observation:

If we store every visited number, then before inserting a new
number we can check whether it already exists.

A hash set provides average O(1) lookup.


Intuition:

Traverse the array:

- If current number is already present in set:
      duplicate found -> return true

- Otherwise insert it into set.


Pseudo Code:

Create empty hash set

For every number in nums:

    If number exists in set:
        return true

    Insert number into set

Return false


Complete Optimal Code:

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        unordered_set<int> st;

        for(int num : nums) {

            if(st.find(num) != st.end()) {
                return true;
            }

            st.insert(num);
        }

        return false;
    }
};


Time Complexity:
O(n)

Space Complexity:
O(n)


===========================================================
DRY RUN
===========================================================

nums = [1,2,3,1]


Initial:
set = {}


num = 1

1 not present

Insert 1

set = {1}


num = 2

2 not present

Insert 2

set = {1,2}


num = 3

3 not present

Insert 3

set = {1,2,3}


num = 1

1 already exists

Duplicate found

Return true


===========================================================
INTERVIEW NOTES
===========================================================

Pattern:

Hashing / Frequency Checking


Key Observation:

To detect duplicates, maintain a record of elements already
seen while traversing the array.


Common Mistakes:

1. Using nested loops and getting O(n^2) unnecessarily.

2. Forgetting that unordered_set only stores unique values.

3. Returning false immediately after finding a new element
   instead of checking the complete array.


When to use this approach:

Use hashing when:

- You need fast existence checking.
- You need to detect duplicates.
- You need frequency/count information.
- Brute force comparison is too slow.


===========================================================

*/

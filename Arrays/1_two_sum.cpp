#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp; // value -> index

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];

            if (mp.find(complement) != mp.end()) {
                return {mp[complement], i};
            }

            mp[nums[i]] = i;
        }

        return {};
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> ans = sol.twoSum(nums, target);

    cout << "Indices: ";
    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}

/*

===========================================================
                LEETCODE 1 : TWO SUM
===========================================================

Problem Statement:
Given an array of integers nums and an integer target,
return indices of the two numbers such that they add up
to target.

You may assume that each input has exactly one solution,
and you may not use the same element twice.

-----------------------------------------------------------
Example:

Input:
nums = [2,7,11,15]
target = 9

Output:
[0,1]

Explanation:
nums[0] + nums[1] = 2 + 7 = 9

===========================================================
BRUTE FORCE APPROACH
===========================================================

Idea:
Check every possible pair of elements and see if their sum
is equal to target.

Pseudo Code:

for i from 0 to n-1:
    for j from i+1 to n-1:
        if nums[i] + nums[j] == target:
            return {i, j}


Complete Brute Force Code:

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        int n = nums.size();

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {

                if(nums[i] + nums[j] == target) {
                    return {i, j};
                }

            }
        }

        return {};
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
For every number nums[i], we only need to find another
number equal to:

target - nums[i]

A hash map can store previously visited numbers and their
indices, allowing O(1) average lookup.


Intuition:
While traversing the array:

Current number = nums[i]

Required number = target - nums[i]

If required number already exists in the map,
we found the answer.

Otherwise, store the current number and its index.


Pseudo Code:

Create hashmap mp

For every index i:

    complement = target - nums[i]

    If complement exists in mp:
        return {mp[complement], i}

    Else:
        store nums[i] with index i


Complete Optimal Code:

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int, int> mp;

        for(int i = 0; i < nums.size(); i++) {

            int complement = target - nums[i];

            if(mp.find(complement) != mp.end()) {
                return {mp[complement], i};
            }

            mp[nums[i]] = i;
        }

        return {};
    }
};


Time Complexity:
O(n)

Space Complexity:
O(n)


===========================================================
DRY RUN
===========================================================

nums = [2,7,11,15]
target = 9


i = 0
nums[i] = 2

complement = 9 - 2 = 7

7 not present in map

Store:
mp = {2 : 0}


i = 1
nums[i] = 7

complement = 9 - 7 = 2

2 exists in map at index 0

Answer:
{0,1}


===========================================================
INTERVIEW NOTES
===========================================================

Pattern:
Hashing / Two Sum Pattern


Key Observation:
Instead of searching for the second number,
store visited numbers and directly check for the required
complement.


Common Mistakes:

1. Checking the current element before inserting it
   can cause using the same element twice.

2. Forgetting to store index along with value.

3. Using unordered_map incorrectly with duplicate values.


When to use this approach:

Use this pattern when:

- You need to find pairs with a given condition.
- You need fast lookup of previous elements.
- Brute force gives O(n^2) and hashing can reduce it.

===========================================================

*/

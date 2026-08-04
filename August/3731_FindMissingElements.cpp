#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        unordered_set<int> st(nums.begin(), nums.end());

        vector<int> ans;
        for (int x = mn + 1; x < mx; x++) {
            if (!st.count(x))
                ans.push_back(x);
        }
        return ans;
    }
};

int main() {
    Solution obj;

    vector<int> nums = {1,4,2,5};

    vector<int> ans = obj.findMissingElements(nums);

    cout << "Missing Elements : ";
    for (int x : ans)
        cout << x << " ";
    cout << endl;

    return 0;
}

/*

==========================
Problem Statement
==========================

You are given an integer array nums consisting of unique integers.

Originally, nums contained every integer within a certain continuous range.
Some integers are now missing, but the smallest and largest numbers of that
original range are still present.

Return all missing integers in sorted order.

-------------------------------------------------
Example
-------------------------------------------------

Input:
nums = {1,4,2,5}

Output:
3

Explanation:
Range = [1...5]
Present = {1,2,4,5}
Missing = {3}

==================================================
Brute Force Approach
==================================================

Idea
----
For every number between minimum and maximum,
scan the entire array to check whether it exists.

Pseudo Code
-----------

find min
find max

for x = min+1 to max-1
    found = false

    for every element in nums
        if element == x
            found = true

    if found == false
        answer.push_back(x)

Complete Brute Force Code
-------------------------

vector<int> findMissingElements(vector<int>& nums) {

    int mn = *min_element(nums.begin(), nums.end());
    int mx = *max_element(nums.begin(), nums.end());

    vector<int> ans;

    for(int x = mn + 1; x < mx; x++) {

        bool found = false;

        for(int num : nums) {
            if(num == x) {
                found = true;
                break;
            }
        }

        if(!found)
            ans.push_back(x);
    }

    return ans;
}

Time Complexity
---------------
O((max-min) * n)

Space Complexity
----------------
O(1)

==================================================
Optimal Approach (Hash Set)
==================================================

Observation
-----------
Searching an element repeatedly in an array is expensive.

If all elements are stored in a hash set,
membership checking becomes O(1).

Intuition
---------
1. Find minimum and maximum.
2. Store all numbers inside an unordered_set.
3. Traverse from min+1 to max-1.
4. If current number is absent in set,
   it is a missing element.

Pseudo Code
-----------

find minimum
find maximum

insert every element into hash set

for x=min+1 to max-1
    if x not present
        answer.push_back(x)

return answer

Complete Optimal Code
---------------------

vector<int> findMissingElements(vector<int>& nums) {

    int mn = *min_element(nums.begin(), nums.end());
    int mx = *max_element(nums.begin(), nums.end());

    unordered_set<int> st(nums.begin(), nums.end());

    vector<int> ans;

    for(int x = mn + 1; x < mx; x++) {

        if(!st.count(x))
            ans.push_back(x);
    }

    return ans;
}

Time Complexity
---------------
O(n + (max-min))

Since values are limited (<=100), this is effectively O(n).

Space Complexity
----------------
O(n)

==================================================
Dry Run
==================================================

nums = {1,4,2,5}

Minimum = 1
Maximum = 5

Hash Set =
{1,2,4,5}

Check

2 -> present

3 -> absent
Answer = {3}

4 -> present

Return {3}

==================================================
Interview Notes
==================================================

Pattern
-------
Hash Set / Membership Checking

Key Observation
---------------
Whenever multiple existence queries are required,
convert the array into a hash set.

Common Mistakes
---------------
1. Forgetting that smallest and largest are never missing.
2. Iterating from min instead of min+1.
3. Iterating till <= max instead of < max.
4. Using vector search repeatedly.

When to use this approach
-------------------------
Whenever:
- Fast lookup is required.
- Array contains unique elements.
- Multiple membership queries are performed.

*/
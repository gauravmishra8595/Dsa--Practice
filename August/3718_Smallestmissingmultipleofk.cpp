#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        vector<bool> freq(101, false);

        for (int x : nums) {
            freq[x] = true;
        }

        int multiple = k;

        while (multiple <= 100) {
            if (!freq[multiple]) {
                return multiple;
            }
            multiple += k;
        }

        return ((100 / k) + 1) * k;
    }
};

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution sol;
    cout << sol.missingMultiple(nums, k) << '\n';

    return 0;
}

/*
============================================================
                DSA NOTEBOOK - MISSING MULTIPLE
============================================================

Problem Statement:
------------------
Given an array nums and an integer k, find the smallest
positive multiple of k that is not present in nums.


Example:
--------
Input:
5 3
1 3 6 9 12

Multiples of 3:
3, 6, 9, 12, 15, ...

3  -> present
6  -> present
9  -> present
12 -> present
15 -> missing

Output:
15


============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
Start from k and check every multiple of k.

For each multiple, search the entire array to determine
whether that multiple exists.

The first multiple that is not found is the answer.


Pseudo Code:
------------
multiple = k

while true:
    found = false

    for every x in nums:
        if x == multiple:
            found = true
            break

    if found == false:
        return multiple

    multiple += k


Complete Brute Force Code:
--------------------------

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        int multiple = k;

        while (true) {
            bool found = false;

            for (int x : nums) {
                if (x == multiple) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                return multiple;
            }

            multiple += k;
        }
    }
};


Time Complexity:
----------------
O(n * m)

where m = number of multiples checked.


Space Complexity:
-----------------
O(1)


============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
We only need to check multiples of k.

Instead of searching the complete array for every multiple,
store whether each number is present using a frequency array.

Then checking a multiple takes O(1).


Intuition:
----------
Mark every number present in nums.

Then check:

k, 2k, 3k, 4k, ...

The first multiple whose frequency is false is the answer.


Pseudo Code:
------------
Create freq array initialized with false.

For every x in nums:
    freq[x] = true

multiple = k

while multiple <= 100:
    if freq[multiple] == false:
        return multiple

    multiple += k

return first multiple greater than 100


Complete Optimal Code:
----------------------

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        vector<bool> freq(101, false);

        for (int x : nums) {
            freq[x] = true;
        }

        int multiple = k;

        while (multiple <= 100) {
            if (!freq[multiple]) {
                return multiple;
            }

            multiple += k;
        }

        return ((100 / k) + 1) * k;
    }
};


Time Complexity:
----------------
O(n + m)

where:
n = number of elements
m = number of multiples checked

With the bounded range, this is effectively O(n).


Space Complexity:
-----------------
O(1)

The frequency array has fixed size 101.


============================================================
DRY RUN
============================================================

nums = [1, 3, 6, 9, 12]
k = 3

Mark all numbers:

freq[1]  = true
freq[3]  = true
freq[6]  = true
freq[9]  = true
freq[12] = true

Now check multiples:

3  -> present
6  -> present
9  -> present
12 -> present
15 -> missing

Therefore:

Answer = 15


============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Frequency Array / Presence Tracking


Key Observation:
----------------
Only multiples of k matter.

We do not need to check every number.

Check:

k, 2k, 3k, 4k, ...


Common Mistakes:
----------------
1. Starting from 0 instead of k.

2. Checking every number instead of only multiples of k.

3. Forgetting to handle the answer beyond the frequency
   array's range.

4. Using an unnecessarily complicated data structure when
   the value range is small.


When to Use This Approach:
--------------------------
Use a frequency array when:

- The value range is small and bounded.
- We only need to know whether a value exists.
- Fast O(1) presence checking is required.
- The problem asks for a missing value.


============================================================
                    END OF NOTES
============================================================
*/
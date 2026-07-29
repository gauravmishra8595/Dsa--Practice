#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    string getPermutation(int n, int k)
    {
        vector<int> nums;
        int fact = 1;

        for (int i = 1; i < n; i++)
        {
            nums.push_back(i);
            fact *= i;
        }
        nums.push_back(n);

        k--;

        string ans = "";

        while (true)
        {
            ans += to_string(nums[k / fact]);
            nums.erase(nums.begin() + (k / fact));

            if (nums.empty())
                break;

            k %= fact;
            fact /= nums.size();
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    int n = 3;
    int k = 3;

    cout << sol.getPermutation(n, k);

    return 0;
}

/*

============================================================
Problem Statement
============================================================

LeetCode 60: Permutation Sequence

The set [1, 2, 3, ..., n] contains n! unique permutations.

Given n and k, return the kth permutation sequence of numbers
1 to n.

Example:
Input:
n = 3, k = 3

Permutations:
123
132
213
231
312
321

Output:
231


============================================================
Brute Force Approach
============================================================

Idea:
------

Generate all permutations of numbers from 1 to n.
Store them in sorted order.
Return the kth permutation.

Since n is small, generating all n! permutations works,
but it becomes impossible for larger n.


Pseudo Code:
------------

function solve(n, k):

    create array nums = [1,2,...,n]

    generate all permutations using recursion

    sort all permutations

    return kth permutation


Complete Brute Force Code:

------------------------------------------------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    void generate(vector<int>& nums,
                  vector<int>& curr,
                  vector<vector<int>>& ans,
                  vector<int>& used) {

        if(curr.size() == nums.size()) {
            ans.push_back(curr);
            return;
        }

        for(int i = 0; i < nums.size(); i++) {

            if(!used[i]) {

                used[i] = 1;
                curr.push_back(nums[i]);

                generate(nums, curr, ans, used);

                curr.pop_back();
                used[i] = 0;
            }
        }
    }


    string getPermutation(int n, int k) {

        vector<int> nums;
        for(int i = 1; i <= n; i++)
            nums.push_back(i);

        vector<vector<int>> ans;
        vector<int> curr;
        vector<int> used(n, 0);

        generate(nums, curr, ans, used);

        sort(ans.begin(), ans.end());

        string res = "";

        for(int x : ans[k-1])
            res += to_string(x);

        return res;
    }
};

------------------------------------------------------------


Time Complexity:
----------------

O(n! * n)

Generating all permutations and storing them.


Space Complexity:
-----------------

O(n! * n)

Storing all permutations.


============================================================
Optimal Approach
============================================================

Observation:
------------

All permutations are divided into blocks.

For n numbers:

Number of permutations starting with each number:

(n-1)!

Example for n = 4:

Each starting digit has:

3! = 6 permutations.


Intuition:
----------

Instead of generating every permutation, directly find the
position of each digit.

Use factorial numbering system.

For each position:

1. Find which block contains kth permutation.
2. Select that number.
3. Remove it from available numbers.
4. Continue for remaining positions.


Pseudo Code:
------------

function getPermutation(n, k):

    store numbers [1..n]

    calculate (n-1)!

    k = k - 1

    while numbers remain:

        index = k / factorial

        choose number at index

        remove chosen number

        k = k % factorial

        update factorial


Complete Optimal Code:

------------------------------------------------------------

class Solution {
public:

    string getPermutation(int n, int k) {

        vector<int> nums;

        int fact = 1;

        for(int i = 1; i < n; i++) {

            nums.push_back(i);
            fact *= i;
        }

        nums.push_back(n);

        k--;

        string ans = "";

        while(true) {

            int index = k / fact;

            ans += to_string(nums[index]);

            nums.erase(nums.begin() + index);


            if(nums.empty())
                break;


            k %= fact;

            fact /= nums.size();
        }

        return ans;
    }
};

------------------------------------------------------------


Time Complexity:
----------------

O(n^2)

Because removing elements from vector takes O(n).


Space Complexity:
-----------------

O(n)

For storing available numbers.


============================================================
Dry Run With Example
============================================================

Input:

n = 3
k = 3


Numbers:

[1,2,3]

Factorial:

(3-1)! = 2


Convert k to zero based:

k = 2


First position:

index = k / fact

index = 2 / 2

index = 1


Pick:

nums[1] = 2


Remaining:

[1,3]


Update:

k = 2 % 2 = 0

fact = 2 / 2 = 1


Second position:

index = 0 / 1

index = 0


Pick:

1


Remaining:

[3]


Answer:

231


============================================================
Interview Notes
============================================================

Pattern:
--------

Mathematical Permutation / Factorial Number System


Key Observation:
----------------

The kth permutation can be found without generating all
permutations by identifying permutation blocks using factorials.


Common Mistakes:
----------------

1. Forgetting k is 1-indexed.
   Convert k to zero based using k--.

2. Wrong factorial calculation.

3. Not removing selected numbers.

4. Integer overflow for large factorial values.


When to use this approach:
--------------------------

Use this technique when:

- Need kth lexicographical permutation.
- n is large enough that n! generation is impossible.
- Elements are unique and ordered.
============================================================
*/

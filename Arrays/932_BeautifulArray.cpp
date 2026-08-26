#include <bits/stdc++.h>
using namespace std;

// LeetCode 932 - Beautiful Array
class Solution
{
public:
    vector<int> beautifulArray(int n)
    {
        vector<int> ans = {1};

        while ((int)ans.size() < n)
        {
            vector<int> next;

            // Generate odd numbers: 2*x - 1
            for (int x : ans)
            {
                int val = 2 * x - 1;
                if (val <= n)
                    next.push_back(val);
            }

            // Generate even numbers: 2*x
            for (int x : ans)
            {
                int val = 2 * x;
                if (val <= n)
                    next.push_back(val);
            }

            ans = next;
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    int n;
    cin >> n;

    vector<int> ans = sol.beautifulArray(n);

    for (int x : ans)
        cout << x << " ";

    cout << '\n';

    return 0;
}

/*
============================================================
                LEETCODE 932 - BEAUTIFUL ARRAY
============================================================

Problem Statement:
------------------
Given an integer n, return any beautiful array of length n.

An array nums of length n is beautiful if:

For every i < k < j, there is no index k such that

    2 * nums[k] == nums[i] + nums[j]

In other words, for every pair of elements nums[i] and nums[j],
their average must not appear between them.

Example:
--------
Input:
    n = 4

Output:
    [2, 1, 4, 3]

Check:
    For every i < k < j,
    2 * nums[k] != nums[i] + nums[j].

Multiple valid answers are possible.


============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
-----
Generate permutations of [1 ... n].

For every permutation, check whether it satisfies the
beautiful-array condition.

The first valid permutation is the answer.

This works for small n but is extremely slow because there
are n! permutations.

Pseudo Code:
------------
generate all permutations of [1 ... n]

for every permutation:
    if isBeautiful(permutation):
        return permutation

isBeautiful(arr):
    for i = 0 to n-1:
        for k = i+1 to n-1:
            for j = k+1 to n-1:
                if 2 * arr[k] == arr[i] + arr[j]:
                    return false

    return true


Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool isBeautiful(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                for (int j = k + 1; j < n; j++) {
                    if (2 * arr[k] == arr[i] + arr[j])
                        return false;
                }
            }
        }

        return true;
    }

    vector<int> beautifulArray(int n) {
        vector<int> arr(n);

        iota(arr.begin(), arr.end(), 1);

        do {
            if (isBeautiful(arr))
                return arr;
        } while (next_permutation(arr.begin(), arr.end()));

        return {};
    }
};

Time Complexity:
----------------
O(n! * n^3)

Space Complexity:
-----------------
O(n)


============================================================
OPTIMAL APPROACH
============================================================

Observation:
------------
Suppose we have a beautiful array.

If we transform every element x into:

    2*x

then all elements become even.

Similarly, if we transform every element x into:

    2*x - 1

then all elements become odd.

These transformations preserve the beautiful-array property.

Why?

For two elements a and b:

    2 * (2*x) = 2*a + 2*b

would imply an arithmetic progression among the original
elements.

The same idea holds for the odd transformation.

Therefore, we can construct the answer by separating:

    Odd numbers
    Even numbers

and recursively constructing beautiful arrays for them.


Intuition:
----------
Start with:

    [1]

This is trivially beautiful.

From a beautiful array, create:

    Odd part:
        2*x - 1

    Even part:
        2*x

For n = 4:

Start:
    [1]

First expansion:
    Odd:
        1
    Even:
        2

    [1, 2]

Next expansion:
    Odd:
        1, 3
    Even:
        2, 4

    [1, 3, 2, 4]

This is a beautiful array.

The implementation repeatedly expands the current beautiful
array until its size becomes n.

Values greater than n are discarded.


Pseudo Code:
------------
ans = [1]

while size(ans) < n:

    next = empty array

    for x in ans:
        odd = 2*x - 1
        if odd <= n:
            add odd to next

    for x in ans:
        even = 2*x
        if even <= n:
            add even to next

    ans = next

return ans


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<int> beautifulArray(int n) {
        vector<int> ans = {1};

        while ((int)ans.size() < n) {
            vector<int> next;

            for (int x : ans) {
                int val = 2 * x - 1;
                if (val <= n)
                    next.push_back(val);
            }

            for (int x : ans) {
                int val = 2 * x;
                if (val <= n)
                    next.push_back(val);
            }

            ans = next;
        }

        return ans;
    }
};

Time Complexity:
----------------
O(n)

Each generated value is processed a constant number of times.

Space Complexity:
-----------------
O(n)

We maintain the current array and the next array.


============================================================
DRY RUN
============================================================

Example:
    n = 4

Initial:
    ans = [1]

Iteration 1:
    Odd values:
        2*1 - 1 = 1

    Even values:
        2*1 = 2

    ans = [1, 2]

Iteration 2:
    From 1:
        Odd  = 1
        Even = 2

    From 2:
        Odd  = 3
        Even = 4

    Values <= 4:
        ans = [1, 3, 2, 4]

Now size = 4.

Return:
    [1, 3, 2, 4]

Check:
    i = 0, k = 1, j = 2:
        2 * 3 = 6
        1 + 2 = 3
        Not equal.

    i = 0, k = 1, j = 3:
        2 * 3 = 6
        1 + 4 = 5
        Not equal.

    i = 0, k = 2, j = 3:
        2 * 2 = 4
        1 + 4 = 5
        Not equal.

    i = 1, k = 2, j = 3:
        2 * 2 = 4
        3 + 4 = 7
        Not equal.

Therefore, the array is beautiful.


============================================================
INTERVIEW NOTES
============================================================

Pattern:
--------
Divide and Conquer / Mathematical Construction

Key Observation:
----------------
Separate the array into odd and even numbers.

For a beautiful array A:

    Odd transformation:
        2*x - 1

    Even transformation:
        2*x

Both transformations preserve the beautiful property.

Since an odd number and an even number can never form an
integer average that belongs to both groups in the problematic
way, concatenating the odd group and even group is safe.

Common Mistakes:
----------------
1. Trying to generate permutations.
2. Checking every triple, which leads to O(n^3) validation.
3. Forgetting to discard values greater than n.
4. Mixing the order of odd and even groups without understanding
   why the transformation preserves the property.
5. Assuming there is only one valid beautiful array.

When to use this approach:
--------------------------
Use this type of construction when:

- The problem asks for ANY valid permutation/arrangement.
- The condition is based on arithmetic relationships.
- A transformation can preserve the required property.
- The elements can be divided into useful groups such as
  odd/even.
- Direct brute force over permutations is factorial.

The main trick in this problem is:

    Beautiful array
          |
          +----> transform to odd numbers
          |
          +----> transform to even numbers

This gives an O(n) constructive solution.

============================================================
*/

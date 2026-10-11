#include <bits/stdc++.h>
using namespace std;
int sumOfSquares(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (n % (i + 1) == 0) {
            ans += nums[i] * nums[i];
        }
    }

    return ans;
}

int main() {
    vector<int> nums = {1, 2, 3, 4};

    cout << sumOfSquares(nums) << endl;  // Output: 21

    return 0;
}
/*
============================================================
                    CP NOTEBOOK
          SUM OF SQUARES OF SPECIAL ELEMENTS
============================================================

1. PROBLEM STATEMENT
--------------------
Given an integer array nums of size n, calculate the sum of
squares of all elements whose 1-based indices divide n evenly.

An element nums[i] is special if:
    n % (i + 1) == 0

Return the sum of squares of all special elements.

2. EXAMPLE
----------
Input:
    nums = {1, 2, 3, 4}

Output:
    21

Explanation:
    n = 4

    Position 1: 4 % 1 == 0 -> 1 * 1 = 1
    Position 2: 4 % 2 == 0 -> 2 * 2 = 4
    Position 3: 4 % 3 != 0 -> Skip
    Position 4: 4 % 4 == 0 -> 4 * 4 = 16

    Total = 1 + 4 + 16 = 21

3. BRUTE FORCE APPROACH
-----------------------

Idea:
    Check every possible 1-based position from 1 to n.
    For each position, check whether it divides n evenly.
    If it does, add the square of that element to the answer.

    This is the straightforward approach. The optimal solution
    below also uses this method because it is already O(n).

Pseudo Code:
    n = size of nums
    ans = 0

    for i = 1 to n:
        if n % i == 0:
            ans += nums[i - 1] * nums[i - 1]

    return ans

Complete Brute Force Code (Revision Only):

    int sumOfSquaresBrute(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                ans += nums[i - 1] * nums[i - 1];
            }
        }

        return ans;
    }

Time Complexity:
    O(n) - Check all n positions.

Space Complexity:
    O(1) - Only a constant number of variables.

4. OPTIMAL APPROACH
-------------------

Observation:
    An element is special if its 1-based position is a divisor
    of the array length n.

    Since C++ arrays use 0-based indexing, position i + 1
    corresponds to nums[i].

    Therefore, the condition is:
        n % (i + 1) == 0

Intuition:
    Traverse the array once.
    If the current 1-based position divides n evenly, add
    the square of the current element to the answer.
    Otherwise, skip it.

Pseudo Code:
    n = size of nums
    ans = 0

    for i = 0 to n - 1:
        if n % (i + 1) == 0:
            ans += nums[i] * nums[i]

    return ans

Complete Optimal Code (Revision Only):

    int sumOfSquares(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (n % (i + 1) == 0) {
                ans += nums[i] * nums[i];
            }
        }

        return ans;
    }

Time Complexity:
    O(n) - Each element is checked exactly once.

Space Complexity:
    O(1) - No additional data structure is used.

Why Optimal?
    Every element may need to be checked, so O(n) time is
    optimal in the general case.

5. DRY RUN
----------

Input:
    nums = {1, 2, 3, 4}

Initial:
    n = 4
    ans = 0

Iteration 1:
    i = 0
    Position = i + 1 = 1
    4 % 1 == 0 -> True
    ans = 0 + (1 * 1) = 1

Iteration 2:
    i = 1
    Position = i + 1 = 2
    4 % 2 == 0 -> True
    ans = 1 + (2 * 2) = 5

Iteration 3:
    i = 2
    Position = i + 1 = 3
    4 % 3 == 0 -> False
    ans remains 5

Iteration 4:
    i = 3
    Position = i + 1 = 4
    4 % 4 == 0 -> True
    ans = 5 + (4 * 4) = 21

Final Answer:
    21

6. INTERVIEW NOTES
------------------

Pattern:
    Array Traversal + Divisibility (Modulo Operator)

Key Observation:
    An element is special when its 1-based index is a divisor
    of the array length.

    a % b == 0 means a is divisible by b without a remainder.

Common Mistakes:
    1. Using i instead of i + 1 for the 1-based position.
       Incorrect: n % i == 0
       Correct:   n % (i + 1) == 0

    2. Adding nums[i] instead of nums[i] * nums[i].

    3. Removing the condition and accidentally summing the
       squares of every element.

    4. Forgetting to initialize ans = 0.

    5. Using an integer type that may overflow if the problem's
       constraints allow very large values.

When to Use This Approach:
    - When array positions must satisfy a divisibility rule.
    - When checking factors or multiples using modulo.
    - When each element can be processed independently.
    - When a single traversal is sufficient.

============================================================
*/

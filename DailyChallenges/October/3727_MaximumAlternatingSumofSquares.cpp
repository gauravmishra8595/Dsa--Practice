#include <bits/stdc++.h>
    using namespace std;
class Solution
{
public:
    long long maxAlternatingSum(vector<int> &nums)
    {
        vector<long long> squares;

        for (int x : nums)
        {
            squares.push_back(1LL * x * x);
        }

        sort(squares.begin(), squares.end());

        int n = squares.size();
        long long ans = 0;

        for (int i = 0; i < n; i++)
        {
            if (i < n / 2)
            {
                ans -= squares[i];
            }
            else
            {
                ans += squares[i];
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    vector<int> nums1 = {1, 2, 3};
    cout << sol.maxAlternatingSum(nums1) << '\n'; // 12

    vector<int> nums2 = {1, -1, 2, -2, 3, -3};
    cout << sol.maxAlternatingSum(nums2) << '\n'; // 16

    return 0;
}

/*
============================================================
PROBLEM STATEMENT
============================================================

LeetCode 3727: Maximum Alternating Sum of Squares

Given an integer array nums, we may rearrange its elements
in any order.

The alternating score is:

    arr[0]^2 - arr[1]^2 + arr[2]^2 - arr[3]^2 + ...

Return the maximum possible alternating score.

============================================================
EXAMPLE
============================================================

Input:
    nums = [1, 2, 3]

Output:
    12

Explanation:
    Rearrange the array as [2, 1, 3].

    Score = 2^2 - 1^2 + 3^2
          = 4 - 1 + 9
          = 12

============================================================
BRUTE FORCE APPROACH
============================================================

Idea:
    Try every possible permutation of nums.
    Calculate the alternating sum of squares for each
    permutation and keep the maximum score.

    This approach is only practical for very small arrays.

Pseudo Code:
    maximum = -infinity

    Generate every permutation:
        score = 0

        For each index i:
            If i is even:
                score += nums[i] * nums[i]
            Else:
                score -= nums[i] * nums[i]

        maximum = max(maximum, score)

    Return maximum

Complete Brute Force Code (Revision Only):

    long long bruteForce(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        long long maximum = LLONG_MIN;

        do {
            long long score = 0;

            for (int i = 0; i < nums.size(); i++) {
                long long sq = 1LL * nums[i] * nums[i];

                if (i % 2 == 0)
                    score += sq;
                else
                    score -= sq;
            }

            maximum = max(maximum, score);

        } while (next_permutation(nums.begin(), nums.end()));

        return maximum;
    }

Time Complexity:
    O(n! * n)

    There can be n! permutations, and calculating each
    permutation's score takes O(n) time.

Space Complexity:
    O(n) auxiliary space for the permutation and variables,
    excluding the input array.

============================================================
OPTIMAL APPROACH
============================================================

Observation:
    The score depends on the squares of elements, not their
    original signs.

    Every squared value is non-negative.

    Elements at even indices contribute positively.
    Elements at odd indices contribute negatively.

Intuition:
    To maximize the score, assign the largest squared
    values to positive positions and the smallest squared
    values to negative positions.

    There are ceil(n / 2) positive positions and
    floor(n / 2) negative positions.

    Sort the squared values in ascending order.

    Subtract the smallest floor(n / 2) values and add
    all remaining values.

Pseudo Code:
    squares = empty array

    For each x in nums:
        squares.push(x * x)

    Sort squares in ascending order

    answer = 0

    For i from 0 to n - 1:
        If i < n / 2:
            answer -= squares[i]
        Else:
            answer += squares[i]

    Return answer

Complete Optimal Code (Revision Only):

    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> squares;

        for (int x : nums) {
            squares.push_back(1LL * x * x);
        }

        sort(squares.begin(), squares.end());

        int n = squares.size();
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            if (i < n / 2)
                ans -= squares[i];
            else
                ans += squares[i];
        }

        return ans;
    }

Time Complexity:
    O(n log n)

    Creating the squared array takes O(n).
    Sorting takes O(n log n).
    Computing the answer takes O(n).

Space Complexity:
    O(n) for storing the squared values.

============================================================
DRY RUN
============================================================

Input:
    nums = [1, 2, 3]

Step 1: Square every element.

    squares = [1, 4, 9]

Step 2: Sort in ascending order.

    squares = [1, 4, 9]

Step 3: Calculate n / 2.

    n = 3
    n / 2 = 1

Step 4: Process the squared values.

    i = 0:
        0 < 1
        ans = 0 - 1 = -1

    i = 1:
        1 >= 1
        ans = -1 + 4 = 3

    i = 2:
        2 >= 1
        ans = 3 + 9 = 12

Final Answer:
    12

============================================================
INTERVIEW NOTES
============================================================

Pattern:
    Greedy + Sorting + Array

Key Observation:
    Larger squared values should occupy positive positions,
    while smaller squared values should occupy negative
    positions.

Common Mistakes:
    1. Sorting nums by their original values instead of
       sorting the squared values.
    2. Forgetting that negative numbers become positive
       after squaring.
    3. Using int for the accumulated answer when long long
       is safer.
    4. Incorrectly splitting the array when n is odd.
    5. Using the wrong comparison at the n / 2 boundary.

When to Use This Approach:
    Use this greedy sorting strategy when elements can be
    rearranged freely and the objective assigns positive
    and negative coefficients to fixed positions.

    Place the largest values at positive positions and
    the smallest values at negative positions.

============================================================
*/

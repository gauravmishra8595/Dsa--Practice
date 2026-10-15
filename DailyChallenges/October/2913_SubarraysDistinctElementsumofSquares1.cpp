#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;
        for (int startIndex = 0; startIndex < n; ++startIndex) {
            int frequency[101] = {0};
            int distinctCount = 0;
            for (int endIndex = startIndex; endIndex < n; ++endIndex) {
                int currentElement = nums[endIndex];
                frequency[currentElement]++;
                if (frequency[currentElement] == 1) {
                    distinctCount++;
                }
                totalSum += distinctCount * distinctCount;
            }
        }
        return totalSum;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    Solution sol;
    cout << sol.sumCounts(nums) << '\n';

    return 0;
}

/*
============================================================
       LEETCODE 2913: SUBARRAYS DISTINCT ELEMENT SUM
============================================================

PROBLEM STATEMENT:
Given an integer array nums, calculate the sum of the
squares of the number of distinct elements in every
non-empty subarray.

Contribution of each subarray:
    distinct_count * distinct_count

Return the total sum.

EXAMPLE:
Input:
3
1 2 1

Output:
15

Explanation:
Subarray       Distinct Count    Square
[1]                  1              1
[1, 2]               2              4
[1, 2, 1]            2              4
[2]                  1              1
[2, 1]               2              4
[1]                  1              1

Total = 1 + 4 + 4 + 1 + 4 + 1 = 15

------------------------------------------------------------
BRUTE FORCE APPROACH
------------------------------------------------------------

IDEA:
Generate every subarray. For each subarray, scan all its
elements and count distinct values using a set. Add the
square of the distinct count to the answer.

PSEUDO CODE:
1. Initialize totalSum = 0.
2. For every starting index i:
       For every ending index j >= i:
           Create an empty set.
           Insert every element from nums[i...j].
           d = size of set.
           totalSum += d * d.
3. Return totalSum.

COMPLETE BRUTE FORCE CODE (REFERENCE ONLY):

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                unordered_set<int> st;

                for (int k = i; k <= j; ++k) {
                    st.insert(nums[k]);
                }

                int d = st.size();
                totalSum += d * d;
            }
        }

        return totalSum;
    }
};

TIME COMPLEXITY: O(n^3) average
SPACE COMPLEXITY: O(n)

------------------------------------------------------------
OPTIMAL APPROACH
------------------------------------------------------------

OBSERVATION:
When a new element is added to a subarray, its distinct
count increases only if that element has not appeared
earlier in the current subarray.

INTUITION:
Fix the starting index and extend the ending index.

Maintain:
- frequency[x]: occurrences of x in the current subarray.
- distinctCount: number of values occurring at least once.
- totalSum: sum of squared distinct counts.

Whenever frequency[x] becomes 1, increase distinctCount.
Then add distinctCount * distinctCount to totalSum.

Since the problem's constraints allow values from 1 to 100,
a fixed frequency array is sufficient and efficient.

PSEUDO CODE:
1. Initialize totalSum = 0.
2. For startIndex from 0 to n - 1:
       Initialize frequency[101] to zero.
       distinctCount = 0.

       For endIndex from startIndex to n - 1:
           x = nums[endIndex]
           frequency[x]++

           If frequency[x] == 1:
               distinctCount++

           totalSum += distinctCount * distinctCount

3. Return totalSum.

COMPLETE OPTIMAL CODE (REFERENCE ONLY):

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        int totalSum = 0;

        for (int startIndex = 0; startIndex < n; ++startIndex) {
            int frequency[101] = {0};
            int distinctCount = 0;

            for (int endIndex = startIndex; endIndex < n; ++endIndex) {
                int x = nums[endIndex];
                frequency[x]++;

                if (frequency[x] == 1) {
                    distinctCount++;
                }

                totalSum += distinctCount * distinctCount;
            }
        }

        return totalSum;
    }
};

TIME COMPLEXITY: O(n^2)
    There are n(n + 1)/2 subarrays, and each extension
    requires O(1) time.

SPACE COMPLEXITY: O(1) auxiliary space
    The frequency array has a fixed size of 101.

    If the value range is not fixed, use a hash map or
    coordinate compression as appropriate.

------------------------------------------------------------
DRY RUN WITH EXAMPLE
------------------------------------------------------------

nums = [1, 2, 1]

StartIndex = 0:
    EndIndex = 0:
        Subarray = [1]
        frequency[1] = 1
        distinctCount = 1
        totalSum = 1

    EndIndex = 1:
        Subarray = [1, 2]
        frequency[2] = 1
        distinctCount = 2
        totalSum = 1 + 4 = 5

    EndIndex = 2:
        Subarray = [1, 2, 1]
        frequency[1] = 2
        distinctCount remains 2
        totalSum = 5 + 4 = 9

StartIndex = 1:
    Reset frequency array and distinctCount.

    EndIndex = 1:
        Subarray = [2]
        distinctCount = 1
        totalSum = 9 + 1 = 10

    EndIndex = 2:
        Subarray = [2, 1]
        distinctCount = 2
        totalSum = 10 + 4 = 14

StartIndex = 2:
    Reset frequency array and distinctCount.

    EndIndex = 2:
        Subarray = [1]
        distinctCount = 1
        totalSum = 14 + 1 = 15

FINAL ANSWER = 15

------------------------------------------------------------
INTERVIEW NOTES
------------------------------------------------------------

PATTERN:
    Subarray enumeration + frequency counting.

KEY OBSERVATION:
    A value contributes to the distinct count only on its
    first occurrence within the current subarray.

COMMON MISTAKES:
    1. Increasing distinctCount for every occurrence.
    2. Forgetting to reset the frequency array for each
       starting index.
    3. Adding distinctCount instead of its square.
    4. Using frequency[101] when values may exceed 100.
    5. Forgetting single-element subarrays.
    6. Ignoring integer overflow for larger constraints.

WHEN TO USE THIS APPROACH:
    - Every contiguous subarray must be considered.
    - A property can be maintained incrementally.
    - Element frequencies determine the required property.
    - The constraints permit O(n^2) time.

VS CODE TESTING:
    Input:
        3
        1 2 1

    Output:
        15

Compile:
    g++ -std=c++17 main.cpp -o main

Run:
    ./main             (Linux/macOS)
    .\main.exe         (Windows)

NOTE:
    This solution uses the small value range specified by
    LeetCode 2913. The expected O(n^2) solution is optimal
    for the intended constraints.

============================================================
*/
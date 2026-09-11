#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {};
        for (int d : digits)
            cnt[d]++;

        int res = 0;
        for (int a = 1; a <= 9; a++) {
            if (cnt[a] == 0)
                continue;

            cnt[a]--;

            // Choose the tens digit
            for (int b = 0; b <= 9; b++) {
                if (cnt[b] == 0)
                    continue;

                cnt[b]--;

                // Choose the units digit
                // It must be even: 0, 2, 4, 6, 8
                for (int c = 0; c <= 8; c += 2) {
                    if (cnt[c] > 0)
                        res++;
                }

                // Restore tens digit
                cnt[b]++;
            }

            // Restore hundreds digit
            cnt[a]++;
        }

        return res;
    }
};

int main() {
    Solution sol;

    vector<int> digits = {1, 2, 3, 4};

    cout << sol.totalNumbers(digits) << '\n';

    return 0;
}

/*
================================================================================
              LEETCODE 3483 - UNIQUE 3-DIGIT EVEN NUMBERS
================================================================================

PROBLEM STATEMENT
-----------------
You are given an array `digits` containing digits.

Using these digits, form unique 3-digit even numbers.

Rules:
1. The number must have exactly 3 digits.
2. The first digit cannot be 0.
3. The last digit must be even.
4. A digit cannot be used more times than it appears in `digits`.
5. Count each unique number only once.

Return the number of unique 3-digit even numbers that can be formed.

EXAMPLE
-------
Input:
    digits = [1, 2, 3, 4]

Some valid numbers:
    124
    132
    134
    142
    214
    234
    ...

Output:
    6

================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Try every possible choice of three indices:

    i -> hundreds digit
    j -> tens digit
    k -> units digit

For every choice:
- All three indices must be different.
- Hundreds digit cannot be 0.
- Units digit must be even.
- Store the formed number in a set.

The set removes duplicate numbers when the input contains repeated digits.

PSEUDO CODE
-----------
function totalNumbers(digits):

    create empty set

    for i = 0 to n - 1:
        for j = 0 to n - 1:
            for k = 0 to n - 1:

                if i == j or j == k or i == k:
                    continue

                if digits[i] == 0:
                    continue

                if digits[k] is odd:
                    continue

                number = digits[i] * 100
                       + digits[j] * 10
                       + digits[k]

                insert number into set

    return size of set

COMPLETE BRUTE FORCE CODE
-------------------------
int totalNumbers(vector<int>& digits) {

    int n = digits.size();
    set<int> st;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {

                if (i == j || j == k || i == k)
                    continue;

                if (digits[i] == 0)
                    continue;

                if (digits[k] % 2 != 0)
                    continue;

                int num = digits[i] * 100
                        + digits[j] * 10
                        + digits[k];

                st.insert(num);
            }
        }
    }

    return st.size();
}

TIME COMPLEXITY
----------------
There are n choices for each of the three positions.

Time:
    O(n^3 log M)

where M is the number of unique numbers stored in the set.

SPACE COMPLEXITY
----------------
O(M)

because the set stores all unique numbers.

================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
For a 3-digit number ABC:

    A = hundreds digit
    B = tens digit
    C = units digit

We have:

    A cannot be 0
    C must be even

Therefore:

    A -> 1 to 9
    B -> 0 to 9
    C -> 0, 2, 4, 6, 8

The only remaining problem is making sure we do not use a digit more
times than it appears.

So we maintain a frequency array:

    cnt[10]

where:

    cnt[d] = number of times digit d is available.

INTUITION
---------
Suppose:

    digits = [1, 1, 2]

Initially:

    cnt[1] = 2
    cnt[2] = 1

Choose:

    a = 1

We temporarily use one 1:

    cnt[1] = 1

Now choose the tens digit.

If:

    b = 1

we temporarily use the second 1:

    cnt[1] = 0

Now the last digit can only be:

    0, 2, 4, 6, 8

Digit 2 is available, so:

    112

is counted.

After checking, we restore the digit counts.

This "take -> explore -> restore" technique is called
BACKTRACKING / FREQUENCY RESTORATION.

PSEUDO CODE
-----------
function totalNumbers(digits):

    create cnt[10]

    for every digit d:
        cnt[d]++

    result = 0

    for a = 1 to 9:

        if cnt[a] == 0:
            continue

        use digit a
        cnt[a]--

        for b = 0 to 9:

            if cnt[b] == 0:
                continue

            use digit b
            cnt[b]--

            for c = 0, 2, 4, 6, 8:

                if cnt[c] > 0:
                    result++

            restore digit b
            cnt[b]++

        restore digit a
        cnt[a]++

    return result

COMPLETE OPTIMAL CODE
---------------------
class Solution {
public:
    int totalNumbers(vector<int>& digits) {

        int cnt[10] = {};

        for (int d : digits)
            cnt[d]++;

        int res = 0;

        for (int a = 1; a <= 9; a++) {

            if (cnt[a] == 0)
                continue;

            cnt[a]--;

            for (int b = 0; b <= 9; b++) {

                if (cnt[b] == 0)
                    continue;

                cnt[b]--;

                for (int c = 0; c <= 8; c += 2) {

                    if (cnt[c] > 0)
                        res++;
                }

                cnt[b]++;
            }

            cnt[a]++;
        }

        return res;
    }
};

TIME COMPLEXITY
----------------
There are at most:

    9 choices for a
    10 choices for b
    5 choices for c

So:

    O(9 * 10 * 5)

    = O(1)

Since the digit range is fixed from 0 to 9, the solution is
effectively constant time.

SPACE COMPLEXITY
----------------
We use:

    cnt[10]

Therefore:

    O(10)
    = O(1)

================================================================================
DRY RUN
================================================================================

Input:

    digits = [1, 2, 3, 4]

Frequency:

    cnt[1] = 1
    cnt[2] = 1
    cnt[3] = 1
    cnt[4] = 1

STEP 1: Choose hundreds digit
------------------------------

a = 1

1 is available.

Use it:

    cnt[1]--

Now:

    cnt[1] = 0

STEP 2: Choose tens digit
-------------------------

Possible b values:

    0, 2, 3, 4

For example:

    b = 2

Use 2:

    cnt[2]--

Now remaining digits include:

    3, 4

STEP 3: Choose units digit
---------------------------

The units digit must be even:

    0, 2, 4, 6, 8

Check each:

    c = 0 -> unavailable
    c = 2 -> already used
    c = 4 -> available -> COUNT
    c = 6 -> unavailable
    c = 8 -> unavailable

So:

    124

is counted.

RESTORE
--------
After finishing with b = 2:

    cnt[2]++

Then try another tens digit.

After finishing all b values:

    cnt[1]++

Then choose another hundreds digit.

This explores all valid combinations without generating duplicates.

================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
Frequency Array + Enumeration + Backtracking/Restore

KEY OBSERVATION
---------------
For a 3-digit even number:

    First digit:
        1 to 9

    Middle digit:
        0 to 9

    Last digit:
        0, 2, 4, 6, 8

Using a frequency array allows us to handle repeated digits correctly.

COMMON MISTAKES
---------------
1. Allowing 0 as the first digit.

   024 is not a 3-digit number.

2. Forgetting that the last digit must be even.

   Valid:
       0, 2, 4, 6, 8

3. Not restoring cnt[a] and cnt[b].

   After temporarily using a digit, it must be restored so that
   other combinations can use it.

4. Using a digit more times than available.

   Example:

       digits = [1, 2, 3]

   111 cannot be formed.

5. Using a set unnecessarily.

   Since we choose digit VALUES rather than indices and each
   (a, b, c) combination represents exactly one number, duplicates
   are naturally avoided by the frequency array.

WHEN TO USE THIS APPROACH
-------------------------
Use this approach when:

- The values are from a small fixed range.
- Repeated values are possible.
- We need to construct numbers/sequences.
- We have restrictions on specific positions.
- We need to respect the available frequency of elements.

This pattern is especially useful for:

    "Form a number/string using given elements with constraints."

================================================================================
IMPORTANT CODE PATTERN
================================================================================

The most important technique here is:

    cnt[a]--;

    // explore choices

    cnt[a]++;

This means:

    TAKE -> EXPLORE -> RESTORE

It is a very common competitive programming/backtracking pattern.

================================================================================
FINAL TAKEAWAY
================================================================================

Instead of using indices and a set, we work directly with digit values.

For every:

    hundreds digit  -> 1 to 9
    tens digit      -> 0 to 9
    units digit     -> 0, 2, 4, 6, 8

we check whether the required digit is available.

The frequency array guarantees that:
- repeated digits are handled correctly,
- invalid digit usage is prevented,
- duplicate numbers are not counted.

Final complexity:

    Time  : O(1)
    Space : O(1)

================================================================================
*/

#include <bits/stdc++.h>
    using namespace std;

class Solution
{
public:
    vector<int> findEvenNumbers(vector<int> &digits)
    {
        vector<int> result;

        // Frequency map for digits 0-9
        vector<int> mp(10, 0);

        for (int digit : digits)
        {
            mp[digit]++;
        }

        // Hundreds digit: 1-9
        for (int i = 1; i <= 9; i++)
        {
            if (mp[i] == 0)
                continue;

            mp[i]--;

            // Tens digit: 0-9
            for (int j = 0; j <= 9; j++)
            {
                if (mp[j] == 0)
                    continue;

                mp[j]--;

                // Units digit: must be even
                // Possible values: 0, 2, 4, 6, 8
                for (int k = 0; k <= 8; k += 2)
                {
                    if (mp[k] == 0)
                        continue;

                    mp[k]--;

                    int num = i * 100 + j * 10 + k;
                    result.push_back(num);

                    // Restore units digit
                    mp[k]++;
                }

                // Restore tens digit
                mp[j]++;
            }

            // Restore hundreds digit
            mp[i]++;
        }

        return result;
    }
};

int main()
{
    Solution sol;

    vector<int> digits = {2, 1, 3, 0};

    vector<int> result = sol.findEvenNumbers(digits);

    for (int num : result)
    {
        cout << num << " ";
    }

    cout << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 2094 - FINDING 3-DIGIT EVEN NUMBERS
================================================================================

PROBLEM STATEMENT
-----------------
You are given an array of digits.

Form all possible UNIQUE 3-digit even numbers using the given digits.

Rules:
1. The number must have exactly 3 digits.
2. The first digit cannot be 0.
3. The last digit must be even.
4. A digit can be used only as many times as it appears in the array.
5. Return all valid numbers in ascending order.

EXAMPLE
-------
Input:
    digits = [2, 1, 3, 0]

Output:
    [102, 120, 130, 132, 210, 230, 302, 310, 312, 320]

================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Try every possible choice of three indices.

For every:
    i -> hundreds digit
    j -> tens digit
    k -> units digit

Check:
    1. i, j, k are different.
    2. digits[i] is not zero.
    3. digits[k] is even.

Construct the number and store it in a set.

The set removes duplicates caused by repeated digits.

PSEUDO CODE
-----------
function findEvenNumbers(digits):

    create empty set

    for i = 0 to n-1:
        for j = 0 to n-1:
            for k = 0 to n-1:

                if i == j or j == k or i == k:
                    continue

                if digits[i] == 0:
                    continue

                if digits[k] is odd:
                    continue

                num = digits[i] * 100
                    + digits[j] * 10
                    + digits[k]

                insert num into set

    convert set to vector
    sort vector

    return vector

COMPLETE BRUTE FORCE CODE
-------------------------
vector<int> findEvenNumbers(vector<int>& digits) {

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

    vector<int> result(st.begin(), st.end());

    return result;
}

TIME COMPLEXITY
----------------
Three nested loops:

    O(n^3)

Set insertion:

    O(log M)

Sorting:

    O(M log M)

Overall:

    O(n^3 + M log M)

where M is the number of unique valid numbers.

SPACE COMPLEXITY
----------------
The set stores unique numbers:

    O(M)

================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------
For a 3-digit even number:

    ABC

The positions have fixed restrictions:

    A -> 1 to 9
    B -> 0 to 9
    C -> 0, 2, 4, 6, 8

Since digits are only from 0 to 9, we can store their frequencies.

Create:

    mp[10]

where:

    mp[d] = number of times digit d is available.

INTUITION
---------
Instead of choosing indices, choose digit VALUES directly.

For example:

    digits = [1, 1, 2]

Frequency:

    mp[1] = 2
    mp[2] = 1

If we choose:

    i = 1

we decrease:

    mp[1]--

Then if we choose:

    j = 1

we decrease again:

    mp[1]--

Now no more 1 is available.

This correctly allows:

    112

but prevents:

    111

because only two 1s exist.

TAKE -> EXPLORE -> RESTORE
---------------------------
This is the most important pattern.

For example:

    mp[i]--;

    // explore

    mp[i]++;

Similarly:

    mp[j]--;

    // explore

    mp[j]++;

And:

    mp[k]--;

    // use digit

    mp[k]++;

This ensures that digits are never used more times than available.

PSEUDO CODE
-----------
function findEvenNumbers(digits):

    create mp[10]

    for every digit:
        mp[digit]++

    result = []

    for i = 1 to 9:

        if mp[i] == 0:
            continue

        mp[i]--

        for j = 0 to 9:

            if mp[j] == 0:
                continue

            mp[j]--

            for k = 0, 2, 4, 6, 8:

                if mp[k] == 0:
                    continue

                mp[k]--

                number = i*100 + j*10 + k

                add number to result

                mp[k]++

            mp[j]++

        mp[i]++

    return result

COMPLETE OPTIMAL CODE
---------------------
vector<int> findEvenNumbers(vector<int>& digits) {

    vector<int> result;
    vector<int> mp(10, 0);

    for (int digit : digits) {
        mp[digit]++;
    }

    for (int i = 1; i <= 9; i++) {

        if (mp[i] == 0)
            continue;

        mp[i]--;

        for (int j = 0; j <= 9; j++) {

            if (mp[j] == 0)
                continue;

            mp[j]--;

            for (int k = 0; k <= 8; k += 2) {

                if (mp[k] == 0)
                    continue;

                mp[k]--;

                int num = i * 100 + j * 10 + k;

                result.push_back(num);

                mp[k]++;
            }

            mp[j]++;
        }

        mp[i]++;
    }

    return result;
}

TIME COMPLEXITY
----------------
There are:

    9 choices for hundreds digit
    10 choices for tens digit
    5 choices for units digit

Therefore:

    9 × 10 × 5 = 450

So:

    Time = O(450)
         = O(1)

SPACE COMPLEXITY
----------------
Frequency array contains only 10 elements:

    mp[10]

The result contains at most 450 numbers.

Auxiliary space:

    O(10)
    = O(1)

Including the output:

    O(450)
    = O(1)

because the problem has a fixed digit range.

================================================================================
DRY RUN
================================================================================

Input:

    digits = [2, 1, 3, 0]

STEP 1: FREQUENCY ARRAY
-----------------------

Initial:

    mp[0] = 1
    mp[1] = 1
    mp[2] = 1
    mp[3] = 1

All other frequencies are 0.

STEP 2: HUNDREDS DIGIT
----------------------

i starts from 1 because 0 cannot be the first digit.

Choose:

    i = 1

Use one 1:

    mp[1]--

STEP 3: TENS DIGIT
------------------

Choose:

    j = 0

Use zero:

    mp[0]--

STEP 4: UNITS DIGIT
-------------------

Possible even digits:

    0, 2, 4, 6, 8

Check:

    k = 0 -> unavailable
    k = 2 -> available

So:

    num = 1*100 + 0*10 + 2
        = 102

Add:

    result = [102]

Restore 2:

    mp[2]++

Next possible even digit:

    k = 4 -> unavailable
    k = 6 -> unavailable
    k = 8 -> unavailable

Restore j:

    mp[0]++

Then try other tens digits.

For:

    i = 1
    j = 2
    k = 0

we get:

    120

For:

    i = 1
    j = 3
    k = 0

we get:

    130

And so on.

================================================================================
WHY NO SET IS REQUIRED
================================================================================

In the brute force solution, we need a set because different indices can
produce the same number.

Example:

    digits = [1, 1, 2]

Using index 0 and index 1 for digit 1 can generate the same number:

    112

In the frequency approach, we don't choose indices.

We choose digit values:

    i = 1
    j = 1
    k = 2

This combination is considered exactly once.

Therefore:

    NO SET IS REQUIRED.

================================================================================
WHY SORTING IS NOT REQUIRED
================================================================================

We do NOT sort the input digits.

The loops themselves generate numbers in increasing order:

    i = 1, 2, 3, ..., 9
    j = 0, 1, 2, ..., 9
    k = 0, 2, 4, 6, 8

Therefore the generated numbers are already sorted.

Example:

    102
    104
    106
    108
    120
    124
    ...

So:

    sort(result.begin(), result.end());

is NOT required.

================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------
Frequency Array + Nested Enumeration + Take/Restore

KEY OBSERVATION
---------------
For every 3-digit even number:

    Hundreds -> 1 to 9
    Tens     -> 0 to 9
    Units    -> 0, 2, 4, 6, 8

COMMON MISTAKES
---------------
1. Starting hundreds digit from 0.

   Wrong:

       for (int i = 0; i <= 9; i++)

   Correct:

       for (int i = 1; i <= 9; i++)

2. Allowing odd units digits.

   Wrong:

       for (int k = 0; k <= 9; k++)

   Correct:

       for (int k = 0; k <= 8; k += 2)

3. Forgetting to decrease frequency.

   Always do:

       mp[i]--;
       mp[j]--;
       mp[k]--;

4. Forgetting to restore frequency.

   Always restore:

       mp[k]++;
       mp[j]++;
       mp[i]++;

5. Using a set unnecessarily.

   Frequency-based digit selection already prevents duplicates.

6. Sorting unnecessarily.

   The loops generate the result in increasing order, so sorting is
   not required.

================================================================================
WHEN TO USE THIS APPROACH
================================================================================

Use this approach when:

- Values have a very small fixed range.
- We need to construct numbers or sequences.
- Repeated elements are possible.
- Each element has a limited frequency.
- There are restrictions on different positions.

Common pattern:

    Frequency Array
          ↓
    Choose position
          ↓
    Decrease frequency
          ↓
       Explore
          ↓
    Restore frequency

================================================================================
FINAL TAKEAWAY
================================================================================

For LeetCode 2094, the cleanest solution is:

    1. Count frequencies of digits.
    2. Choose hundreds digit from 1 to 9.
    3. Choose tens digit from 0 to 9.
    4. Choose units digit from 0,2,4,6,8.
    5. Decrease frequency when using a digit.
    6. Restore frequency after exploring.
    7. Add every valid number directly to result.

No:

    - Sorting input
    - Set
    - next_permutation
    - Backtracking function

is required.

Final complexity:

    Time  : O(1)
    Space : O(1)

================================================================================
*/

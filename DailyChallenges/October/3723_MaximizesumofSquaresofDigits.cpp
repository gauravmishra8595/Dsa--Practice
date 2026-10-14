#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9LL * num) {
            return "";
        }

        int nines = sum / 9;
        int remain = sum % 9;

        string result(nines, '9');

        if (remain > 0) {
            result.push_back(char(remain + '0'));
        }

        result.append(num - (int)result.length(), '0');

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    int num, sum;
    cout << "Enter num and sum: ";
    cin >> num >> sum;

    string result = sol.maxSumOfSquares(num, sum);

    if (result.empty()) {
        cout << "No valid number exists.\n";
    } else {
        cout << "Maximum number: " << result << '\n';

        long long digitSum = 0;
        long long squareSum = 0;

        for (char c : result) {
            int digit = c - '0';
            digitSum += digit;
            squareSum += 1LL * digit * digit;
        }

        cout << "Digit sum: " << digitSum << '\n';
        cout << "Sum of squared digits: " << squareSum << '\n';
    }

    return 0;
}

/*
============================================================
       LEETCODE 3723 - MAXIMIZE SUM OF SQUARES OF DIGITS
============================================================

PROBLEM STATEMENT:
------------------
Given two integers num and sum, construct a number represented
as a string with exactly num digits such that:

1. The sum of its digits equals sum.
2. The sum of the squares of its digits is maximized.
3. Among equally optimal answers, choose the largest number.
4. If no valid number exists, return an empty string.

The number is represented as a string because num can be large.

EXAMPLE:
--------
Input:
num = 4
sum = 20

Output:
9920

Explanation:
9 + 9 + 2 + 0 = 20

Sum of squared digits:
9^2 + 9^2 + 2^2 + 0^2
= 81 + 81 + 4 + 0
= 166

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA:
-----
Generate every possible num-digit number, calculate its digit
sum and sum of squared digits, and retain the valid number
with the maximum score.

If scores are equal, retain the numerically largest number.

This approach is suitable only for very small inputs.

PSEUDO CODE:
------------
best = empty string
bestScore = -1

FOR every num-digit number:
    calculate digitSum
    calculate squareSum

    IF digitSum == sum:
        IF squareSum > bestScore:
            update best and bestScore
        ELSE IF squareSum == bestScore AND number > best:
            update best

RETURN best

COMPLETE BRUTE FORCE CODE (COMMENTS ONLY):
------------------------------------------
This illustrative implementation is limited to small num.
It is intentionally not executable.

    string bruteForce(int num, int sum) {
        if (sum > 9 * num) return "";

        long long start = 1;
        for (int i = 1; i < num; i++) {
            start *= 10;
        }

        long long end = start * 10 - 1;

        string best = "";
        long long bestScore = -1;

        for (long long n = start; n <= end; n++) {
            string s = to_string(n);

            int digitSum = 0;
            long long squareSum = 0;

            for (char c : s) {
                int d = c - '0';
                digitSum += d;
                squareSum += 1LL * d * d;
            }

            if (digitSum == sum &&
                (squareSum > bestScore ||
                 (squareSum == bestScore && s > best))) {
                best = s;
                bestScore = squareSum;
            }
        }

        return best;
    }

TIME COMPLEXITY:
----------------
O(10^num * num)

There are exponentially many candidate numbers. Checking each
candidate takes O(num) time.

SPACE COMPLEXITY:
-----------------
O(num) for storing a candidate string.

============================================================
OPTIMAL APPROACH: GREEDY
============================================================

OBSERVATION:
------------
Every digit is between 0 and 9.

Therefore, the maximum digit sum possible with num digits is:

    maxSum = 9 * num

If sum > maxSum, no valid answer exists.

To maximize the sum of squared digits, concentrate the digit
sum into as many 9s as possible. Then place the remainder,
if any, and fill the remaining positions with zeros.

INTUITION:
----------
A larger digit contributes more to the sum of squares.

For example, for a total digit sum of 10:

    9^2 + 1^2 = 82
    5^2 + 5^2 = 50

Thus, concentrating the sum into the largest possible digits
maximizes the score.

To maximize the numerical value as well, put the largest
digits at the beginning.

KEY FORMULAS:
-------------
Number of nines = sum / 9
Remainder digit = sum % 9

Construct the answer as:

    [nines] + [remainder if nonzero] + [zeros]

PSEUDO CODE:
------------
IF sum > 9 * num:
    RETURN ""

nines = sum / 9
remain = sum % 9

result = string containing nines copies of '9'

IF remain > 0:
    append remain as a digit

append zeros until result has num digits

RETURN result

COMPLETE OPTIMAL CODE (COMMENTS ONLY):
--------------------------------------

    class Solution {
    public:
        string maxSumOfSquares(int num, int sum) {
            if (sum > 9LL * num) {
                return "";
            }

            int nines = sum / 9;
            int remain = sum % 9;

            string result(nines, '9');

            if (remain > 0) {
                result.push_back(char(remain + '0'));
            }

            result.append(num - (int)result.length(), '0');

            return result;
        }
    };

TIME COMPLEXITY:
----------------
O(num)

Creating and filling the output string takes O(num) time.

SPACE COMPLEXITY:
-----------------
O(num), including the output string.
Auxiliary space excluding the output is O(1).

============================================================
DRY RUN WITH EXAMPLE
============================================================

Input:
num = 4
sum = 20

Step 1: Check feasibility.

    9 * num = 9 * 4 = 36
    sum = 20

Since 20 <= 36, a valid answer exists.

Step 2: Calculate the number of nines.

    nines = sum / 9
          = 20 / 9
          = 2

Step 3: Calculate the remainder.

    remain = sum % 9
           = 20 % 9
           = 2

Step 4: Create the initial result.

    result = "99"

Step 5: Append the remainder digit.

    result = "992"

Step 6: Fill the remaining positions with zeros.

    Current length = 3
    Required length = 4
    Zeros to append = 4 - 3 = 1

    result = "9920"

Step 7: Verify.

    Number of digits = 4
    Digit sum = 9 + 9 + 2 + 0 = 20

    Sum of squares:
    81 + 81 + 4 + 0 = 166

Final output:

    9920

ADDITIONAL EDGE CASES:
----------------------

Case 1:
num = 3, sum = 27
Output = "999"

Case 2:
num = 3, sum = 10
Output = "9100"

Case 3:
num = 4, sum = 9
Output = "9000"

Case 4:
num = 2, sum = 19
Output = ""

Reason: 19 > 9 * 2 = 18.

============================================================
INTERVIEW NOTES
============================================================

PATTERN:
--------
Greedy algorithm + mathematical construction.

KEY OBSERVATION:
----------------
Maximize the digit squares by placing as much of the available
sum as possible into digits equal to 9.

COMMON MISTAKES:
----------------
1. Forgetting to check sum > 9 * num.
2. Returning an integer instead of a string.
3. Forgetting to fill all remaining positions with zeros.
4. Placing the remainder before the nines.
5. Using brute force for large constraints.
6. Using an incorrect string length when appending zeros.
7. Forgetting that sum / 9 uses integer division.

WHEN TO USE THIS APPROACH:
--------------------------
Use this greedy construction when:
1. A fixed sum must be distributed among bounded digits.
2. Larger digits are favored by the objective function.
3. The answer can be constructed directly.
4. A lexicographically or numerically largest arrangement
   is required among optimal arrangements.

FINAL COMPLEXITIES:
-------------------
Time:  O(num)
Space: O(num), including the output string.

============================================================
VS CODE TESTING
============================================================

1. Save this file as main.cpp.
2. Compile using:

   g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o main

3. Run:

   ./main

   On Windows:

   .\main.exe

4. Enter:

   4 20

Expected result:

   Maximum number: 9920
   Digit sum: 20
   Sum of squared digits: 166

NOTE:
The actual executable code contains only the optimal
Solution implementation and a main() function for testing.
Brute force and revision code are present only in comments.

============================================================
*/

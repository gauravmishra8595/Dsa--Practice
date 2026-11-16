#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string digitSum(string s, int k) {

        while (s.length() > k) {

            string temp = "";

            for (int i = 0; i < s.length(); i += k) {

                int sum = 0;

                for (int j = i; j < min(i + k, (int)s.length()); j++) {
                    sum += s[j] - '0';
                }

                temp += to_string(sum);
            }

            s = temp;
        }

        return s;
    }
};

int main() {
    string s;
    int k;

    cin >> s >> k;

    Solution obj;

    cout << obj.digitSum(s, k) << endl;

    return 0;
}

/*
=========================================================
       LEETCODE 2243 - CALCULATE DIGIT SUM OF A STRING
=========================================================

1. PROBLEM STATEMENT
--------------------

You are given a string s consisting of digits and
an integer k.

Perform the following operation repeatedly:

1. Divide s into consecutive groups of size k.
2. If the last group contains fewer than k characters,
   keep that smaller group.
3. Calculate the sum of digits in each group.
4. Replace each group with its digit sum as a string.
5. Repeat until the length of s becomes <= k.

Return the final string.


=========================================================
2. EXAMPLE
=========================================================

Input:
s = "11111222223"
k = 3

Output:
"135"

Explanation:

First operation:

"111" -> 3
"112" -> 4
"222" -> 6
"23"  -> 5

New string:

"3465"

Second operation:

"346" -> 13
"5"   -> 5

New string:

"135"

Since length = 3 and k = 3, stop.

Final Answer = "135"


=========================================================
3. BRUTE FORCE APPROACH
=========================================================

IDEA:
-----

Simulate the operations directly.

For every iteration:
1. Create an empty temporary string.
2. Divide the current string into groups of size k.
3. Calculate the sum of digits in each group.
4. Convert the sum into a string.
5. Append it to the temporary string.
6. Replace the original string with the temporary string.
7. Repeat until its length is <= k.

PSEUDO CODE:
------------

while length(s) > k:

    temp = ""

    for i = 0 to length(s)-1 step k:

        sum = 0

        for j = i to min(i+k, length(s))-1:

            sum += s[j] - '0'

        temp += to_string(sum)

    s = temp

return s


COMPLETE BRUTE FORCE CODE:
--------------------------

class Solution {
public:
    string digitSum(string s, int k) {

        while (s.length() > k) {

            string temp = "";

            for (int i = 0; i < s.length(); i += k) {

                int sum = 0;

                for (int j = i;
                     j < min(i + k, (int)s.length());
                     j++) {

                    sum += s[j] - '0';
                }

                temp += to_string(sum);
            }

            s = temp;
        }

        return s;
    }
};


TIME COMPLEXITY:
----------------

O(n log_k n)

Each operation processes every digit of the
current string.

The string length decreases approximately by
a factor of k in each operation.

SPACE COMPLEXITY:
-----------------

O(n) for the temporary string.


=========================================================
4. OPTIMAL APPROACH
=========================================================

OBSERVATION:
------------

We only need to simulate the operations.

There is no need for advanced data structures
or prefix sums.

The key observation is:

Every group is independent.

We can calculate its digit sum and immediately
append the result to a new string.

INTUITION:
----------

Use two strings:

1. s = Current string.
2. temp = String generated after one operation.

For every group of k digits:

- Calculate the sum.
- Convert the sum into a string.
- Append it to temp.

After processing all groups:

s = temp

Continue until s.length() <= k.

PSEUDO CODE:
------------

while s.length() > k:

    temp = ""

    for i = 0 to s.length()-1, increment by k:

        sum = 0

        for j = i to min(i+k, s.length())-1:
            sum += digit at position j

        append string(sum) to temp

    s = temp

return s


COMPLETE OPTIMAL CODE:
----------------------

class Solution {
public:
    string digitSum(string s, int k) {

        while (s.length() > k) {

            string temp = "";

            for (int i = 0; i < s.length(); i += k) {

                int sum = 0;

                for (int j = i;
                     j < min(i + k, (int)s.length());
                     j++) {

                    sum += s[j] - '0';
                }

                temp += to_string(sum);
            }

            s = temp;
        }

        return s;
    }
};


TIME COMPLEXITY:
----------------

O(n log_k n), for k > 1.

SPACE COMPLEXITY:
-----------------

O(n) for the temporary string.


=========================================================
5. DRY RUN
=========================================================

Input:

s = "11111222223"
k = 3

INITIAL STRING:

11111222223

---------------- FIRST OPERATION ----------------

Group 1: "111"

1 + 1 + 1 = 3

Group 2: "112"

1 + 1 + 2 = 4

Group 3: "222"

2 + 2 + 2 = 6

Group 4: "23"

2 + 3 = 5

New string:

s = "3465"

---------------- SECOND OPERATION ----------------

Group 1: "346"

3 + 4 + 6 = 13

Group 2: "5"

5 = 5

New string:

s = "135"

---------------- CHECK CONDITION ----------------

Length of s = 3

k = 3

Since length(s) <= k, stop.

FINAL ANSWER:

"135"


=========================================================
6. INTERVIEW NOTES
=========================================================

PATTERN:
--------

String + Simulation + Grouping.

KEY OBSERVATION:
----------------

Process the string in groups of k and replace
each group with its digit sum.

Repeat until the string length is <= k.

COMMON MISTAKES:
----------------

1. Forgetting the last group may contain fewer
   than k digits.

2. Forgetting to convert the sum into a string
   using to_string().

3. Updating s before all groups are processed.

4. Using j < i + k without checking the string length.

5. Forgetting the while condition.

6. Returning the intermediate string instead of
   the final string.

WHEN TO USE THIS APPROACH:
--------------------------

1. When a string needs to be processed in fixed-size groups.
2. When each group produces a new value.
3. When an operation must be repeated until a condition
   becomes false.
4. When direct simulation is sufficient.

=========================================================
              END OF LEETCODE 2243
=========================================================
*/

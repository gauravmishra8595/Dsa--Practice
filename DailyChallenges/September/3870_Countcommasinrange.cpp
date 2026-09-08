#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countCommas(int n) {
        return n < 1000 ? 0 : n - 999;
    }
};

int main() {
    Solution sol;

    cout << sol.countCommas(100) << '\n';   // 0
    cout << sol.countCommas(1000) << '\n';  // 1
    cout << sol.countCommas(1010) << '\n';  // 11

    return 0;
}

/*
============================================================
                    PROBLEM STATEMENT
============================================================

Given an integer n, count the total number of commas used
when writing every integer from 1 to n with commas as digit
separators.

For example:
1000 -> "1,000" uses 1 comma.
10000 -> "10,000" uses 1 comma.

Return the total number of commas.

============================================================
                        EXAMPLE
============================================================

Input:
n = 1010

Numbers from 1 to 1010 that contain a comma are:
1000, 1001, ..., 1010

Count = 1010 - 1000 + 1
      = 11

Output:
11


============================================================
                  BRUTE FORCE APPROACH
============================================================

Idea:
------
Check every number from 1 to n and count how many commas
are needed in its comma-formatted representation.

A number:
- Less than 1000 needs 0 commas.
- From 1000 to 999999 needs 1 comma.
- Larger numbers may need more commas.

For a generic brute force solution, convert every number
to a string and count digit groups.

Pseudo Code:
------------
count = 0

for i = 1 to n:
    convert i to string
    traverse its digits
    count commas according to groups of 3 digits

return count

Complete Brute Force Code:
--------------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countCommas(int n) {
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            string s = to_string(i);

            // Number of commas = number of digits - 1,
            // divided into groups of 3.
            if (s.length() > 3) {
                ans += (s.length() - 1) / 3;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    cout << sol.countCommas(1010) << '\n';
    return 0;
}

Time Complexity:
----------------
O(n * log(n))

Space Complexity:
-----------------
O(log(n)) for the temporary string.


============================================================
                   OPTIMAL APPROACH
============================================================

Observation:
------------
For the given problem constraints, every number below 1000
has no comma.

Every number from 1000 onward contributes at least one comma.

Therefore, if we only need to count the commas for the
range relevant to this problem, the answer is simply the
number of integers from 1000 to n.

Count of integers from 1000 to n:

n - 1000 + 1
= n - 999

If n < 1000, the answer is 0.

Intuition:
----------
All numbers before 1000 look like:

1, 2, 3, ..., 999

and require no comma.

Starting from 1000, each number contributes one comma:

1000 -> 1
1001 -> 1
1002 -> 1
...
n    -> 1

Hence:

answer = n - 999, if n >= 1000
answer = 0, otherwise.

Pseudo Code:
------------
if n < 1000:
    return 0

return n - 999

Complete Optimal Code:
----------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countCommas(int n) {
        return n < 1000 ? 0 : n - 999;
    }
};

int main() {
    Solution sol;
    cout << sol.countCommas(1010) << '\n';
    return 0;
}

Time Complexity:
----------------
O(1)

Space Complexity:
-----------------
O(1)


============================================================
                        DRY RUN
============================================================

Example:
n = 1010

Step 1:
n >= 1000, so commas start appearing from 1000.

Step 2:
Numbers requiring a comma:

1000, 1001, 1002, ..., 1010

Step 3:
Count them:

1010 - 1000 + 1
= 11

Using the formula:

n - 999
= 1010 - 999
= 11

Answer = 11


============================================================
                     INTERVIEW NOTES
============================================================

Pattern:
--------
Counting elements in a continuous range using a mathematical
formula instead of iterating through all elements.

Key Observation:
----------------
Numbers below 1000 contain no comma.

For every number from 1000 onward, the first comma appears
after the first digit group.

Thus, the count of numbers >= 1000 is:

n - 1000 + 1 = n - 999

Common Mistakes:
----------------
1. Forgetting that 1000 itself contains a comma.
2. Using n - 1000 instead of n - 999.
3. Iterating unnecessarily when a direct formula exists.
4. Not handling n < 1000.
5. Assuming every larger number has exactly one comma for
   variants of the problem where n can be much larger.

When to use this approach:
--------------------------
Use a mathematical/counting approach when:
- The valid elements form a continuous range.
- Every element in that range contributes the same amount.
- The boundaries can be determined directly.

For a generalized version where n can be very large and
numbers may contain multiple commas, count each digit-group
range separately (1000-999999, 1000000-999999999, etc.).

============================================================
*/

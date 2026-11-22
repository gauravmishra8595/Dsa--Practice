#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool checkString(string s)
    {
        int n = s.size();

        for (int i = 1; i < n; i++)
        {
            if (s[i] == 'a' && s[i - 1] == 'b')
            {
                return false;
            }
        }

        return true;
    }
};

// ================= MAIN FUNCTION =================

int main()
{
    Solution obj;

    string s;
    cin >> s;

    cout << (obj.checkString(s) ? "true" : "false") << endl;

    return 0;
}

/*
========================================================
                 LEETCODE 2124
       CHECK IF ALL A'S APPEAR BEFORE ALL B'S
========================================================

1. PROBLEM STATEMENT
--------------------------------------------------------

Given a string s consisting only of characters 'a' and 'b'.

Return true if all occurrences of 'a' appear before all
occurrences of 'b'.

Otherwise, return false.

A valid string can contain:
- Only 'a'
- Only 'b'
- All 'a' followed by all 'b'

--------------------------------------------------------
2. EXAMPLE
--------------------------------------------------------

Example 1:

Input:
s = "aaabbb"

Output:
true

Explanation:
All 'a' characters appear before all 'b' characters.

Example 2:

Input:
s = "abab"

Output:
false

Explanation:
An 'a' appears after a 'b'.

Example 3:

Input:
s = "bbb"

Output:
true

========================================================
              BRUTE FORCE APPROACH
========================================================

1. IDEA
--------------------------------------------------------

Check every pair of indices.

If we find a 'b' at an earlier position and an 'a'
at a later position, the string is invalid.

2. PSEUDO CODE
--------------------------------------------------------

for i = 0 to n-1:
    for j = i+1 to n-1:

        if s[i] == 'b' AND s[j] == 'a':
            return false

return true

3. COMPLETE BRUTE FORCE CODE
--------------------------------------------------------

bool checkString(string s) {
    int n = s.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (s[i] == 'b' && s[j] == 'a') {
                return false;
            }
        }
    }

    return true;
}

4. TIME COMPLEXITY
--------------------------------------------------------

O(n^2)

Two nested loops are used to check all pairs.

5. SPACE COMPLEXITY
--------------------------------------------------------

O(1)

No extra data structure is used.

========================================================
                OPTIMAL APPROACH
========================================================

1. OBSERVATION
--------------------------------------------------------

A valid string must have all 'a' characters before
all 'b' characters.

Therefore, the substring "ba" must never occur.

If "ba" exists anywhere, the string is invalid.

2. INTUITION
--------------------------------------------------------

Traverse the string from left to right.

Check every adjacent pair:

    s[i-1] and s[i]

If:
    s[i-1] == 'b'
    AND
    s[i] == 'a'

Return false.

If the complete traversal finishes without finding
"ba", return true.

Start the loop from i = 1 to avoid accessing s[-1].

3. PSEUDO CODE
--------------------------------------------------------

for i = 1 to n-1:

    if s[i-1] == 'b' AND s[i] == 'a':
        return false

return true

4. COMPLETE OPTIMAL CODE
--------------------------------------------------------

class Solution {
public:
    bool checkString(string s) {
        int n = s.size();

        for (int i = 1; i < n; i++) {
            if (s[i] == 'a' && s[i-1] == 'b') {
                return false;
            }
        }

        return true;
    }
};

5. TIME COMPLEXITY
--------------------------------------------------------

O(n)

Only one traversal of the string is required.

6. SPACE COMPLEXITY
--------------------------------------------------------

O(1)

Only a constant amount of extra space is used.

========================================================
                    DRY RUN
========================================================

Input:
s = "aaabbb"

Index:     0   1   2   3   4   5
String:    a   a   a   b   b   b

i = 1:
s[0] = 'a', s[1] = 'a'
No "ba" found.

i = 2:
s[1] = 'a', s[2] = 'a'
No "ba" found.

i = 3:
s[2] = 'a', s[3] = 'b'
No "ba" found.

i = 4:
s[3] = 'b', s[4] = 'b'
No "ba" found.

i = 5:
s[4] = 'b', s[5] = 'b'
No "ba" found.

Loop completed.

Output: true

----------------------------------------

Input:
s = "abab"

Index:     0   1   2   3
String:    a   b   a   b

i = 1:
s[0] = 'a', s[1] = 'b'
No "ba" found.

i = 2:
s[1] = 'b', s[2] = 'a'

"ba" FOUND!

Return false.

Output: false

========================================================
                  INTERVIEW NOTES
========================================================

1. PATTERN
--------------------------------------------------------

String Traversal + Adjacent Character Checking.

2. KEY OBSERVATION
--------------------------------------------------------

The string is valid if and only if the substring "ba"
does not occur.

3. COMMON MISTAKES
--------------------------------------------------------

- Starting the loop from i = 0 and accessing s[i-1].
- Checking "ab" instead of "ba".
- Forgetting to return true after the loop.
- Using nested loops unnecessarily.

4. WHEN TO USE THIS APPROACH
--------------------------------------------------------

Use this approach when:

- Characters must follow a specific order.
- You need to detect an invalid character transition.
- A single traversal can verify the condition.
- The problem involves checking adjacent characters.

========================================================
                  FINAL COMPLEXITY
========================================================

Brute Force:
Time  : O(n^2)
Space : O(1)

Optimal:
Time  : O(n)
Space : O(1)

========================================================
                  END OF NOTES
========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minChanges(string s) {
        int changes = 0;

        for (int i = 0; i < s.length(); i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }

        return changes;
    }
};

int main() {
    Solution sol;

    string s = "1001";

    cout << sol.minChanges(s) << endl;

    return 0;
}

/*
============================================================
                LEETCODE 2914
       Minimum Number of Changes to Make Binary
                  String Beautiful
============================================================

1. PROBLEM STATEMENT

Given a binary string s, we need to make it beautiful.

A binary string is beautiful if we can partition it into
substrings of length 2, where each substring contains
identical characters.

We can change any character:
    '0' -> '1'
    '1' -> '0'

Return the minimum number of changes required.

------------------------------------------------------------
2. EXAMPLE

Input:
    s = "1001"

Output:
    2

Explanation:

    Pairs: "10" | "01"

    "10" -> Change one character -> "00"
    "01" -> Change one character -> "11"

    Result: "0011"

    Minimum changes = 2

------------------------------------------------------------
3. BRUTE FORCE APPROACH

IDEA:

For every pair of characters:
    - If both characters are equal, no change is needed.
    - If both characters are different, one change is needed.

This is already the simplest direct approach.

PSEUDO CODE:

    changes = 0

    for i = 0 to n-1, increment by 2:
        if s[i] != s[i+1]:
            changes++

    return changes

COMPLETE BRUTE FORCE CODE:

    int minChanges(string s) {
        int changes = 0;
        int n = s.length();

        for (int i = 0; i < n; i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }

        return changes;
    }

TIME COMPLEXITY:
    O(N)

SPACE COMPLEXITY:
    O(1)

------------------------------------------------------------
4. OPTIMAL APPROACH

OBSERVATION:

The string must be divided into consecutive pairs:

    (s[0], s[1])
    (s[2], s[3])
    (s[4], s[5])
    ...

For every pair:
    - Equal characters -> 0 changes.
    - Different characters -> 1 change.

Since each pair is independent, we can calculate
the answer by simply counting unequal pairs.

INTUITION:

If a pair contains different characters, changing
either one of them makes the pair equal.

Therefore, exactly one change is sufficient and necessary.

We just count such pairs.

PSEUDO CODE:

    changes = 0

    for i = 0 to n-1, increment by 2:

        if s[i] != s[i+1]:
            changes++

    return changes

COMPLETE OPTIMAL CODE:

    class Solution {
    public:
        int minChanges(string s) {
            int changes = 0;

            for (int i = 0; i < s.length(); i += 2) {
                if (s[i] != s[i + 1]) {
                    changes++;
                }
            }

            return changes;
        }
    };

TIME COMPLEXITY:
    O(N)

    Every character is visited exactly once.

SPACE COMPLEXITY:
    O(1)

    Only one integer variable is used.

------------------------------------------------------------
5. DRY RUN

Input:
    s = "1001"

String indices:

    Index:  0  1  2  3
    String: 1  0  0  1

Initially:
    changes = 0

ITERATION 1:
    i = 0

    s[0] = '1'
    s[1] = '0'

    Characters are different.

    changes = 1

ITERATION 2:
    i = 2

    s[2] = '0'
    s[3] = '1'

    Characters are different.

    changes = 2

Loop ends.

Final Answer:
    2

------------------------------------------------------------
6. INTERVIEW NOTES

PATTERN:
    String + Greedy + Pairwise Comparison

KEY OBSERVATION:
    Every consecutive pair is independent.

    If characters differ, exactly one change is required.

    If characters are equal, zero changes are required.

COMMON MISTAKES:

    1. Incrementing i by 1 instead of 2.

    2. Comparing overlapping pairs.

    3. Forgetting that indexing starts from 0.

    4. Accessing s[i+1] without ensuring that
       the string length is even.

    5. Trying unnecessary dynamic programming.

WHEN TO USE THIS APPROACH:

    - When a string must be divided into fixed-size pairs.
    - When each pair can be processed independently.
    - When the minimum cost for each pair is directly known.
    - When a greedy counting approach gives the optimal answer.

------------------------------------------------------------
FINAL TAKEAWAY:

    Unequal pair -> 1 change
    Equal pair   -> 0 changes

    Answer = Count of unequal consecutive pairs.

    Time:  O(N)
    Space: O(1)

============================================================
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }
        if (n == 2) {
            return -1;
        }
        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }
        return 3;
    }
};
int main() {
    Solution sol;

    vector<string> tests = {
        "dog",
        "card",
        "gf",
        "abc",
        "bca",
        "cba",
        "acb"
    };

    for (const string& s : tests) {
        cout << "s = " << s
             << " -> " << sol.minOperations(s) << '\n';
    }

    return 0;
}

/*
============================================================
LEETCODE 3863: MINIMUM OPERATIONS TO SORT A STRING
============================================================

PROBLEM STATEMENT:
------------------
Given a string s consisting of lowercase English letters,
one operation allows us to choose any proper substring
(not the entire string) and sort it in non-decreasing order.

Return the minimum number of operations required to sort
the entire string. Return -1 if it is impossible.

EXAMPLE:
--------
Input:  s = "dog"
Output: 1
Explanation:
Sort substring "og" -> "go".
Result: "dgo", which is sorted.

Input:  s = "card"
Output: 2
Explanation:
"car" -> "acr": "acrd"
"rd"  -> "dr":  "acdr"

Input:  s = "gf"
Output: -1

============================================================
BRUTE FORCE APPROACH
============================================================

IDEA:
-----
Try every possible proper substring, sort it, and check
whether the resulting string becomes sorted.

For a general brute-force search, use BFS over string
states. Each edge represents one valid substring-sorting
operation. BFS guarantees the minimum number of operations.

PSEUDO CODE:
------------
function bruteForce(s):
    if s is sorted:
        return 0

    queue = [s]
    visited = {s}
    operations = 0

    while queue is not empty:
        process all states at current BFS level

        for each current string:
            for every substring [l, r]:
                skip if [l, r] is the entire string

                next = current
                sort next[l ... r]

                if next is sorted:
                    return operations + 1

                if next is not visited:
                    add next to visited and queue

        operations++

    return -1

COMPLETE BRUTE FORCE CODE (REVISION ONLY):
------------------------------------------
int bruteForce(string s) {
    if (is_sorted(s.begin(), s.end())) {
        return 0;
    }

    queue<string> q;
    unordered_set<string> visited;

    q.push(s);
    visited.insert(s);

    int operations = 0;
    int n = s.size();

    while (!q.empty()) {
        int levelSize = q.size();

        while (levelSize--) {
            string current = q.front();
            q.pop();

            for (int l = 0; l < n; l++) {
                for (int r = l; r < n; r++) {
                    if (l == 0 && r == n - 1) {
                        continue;
                    }

                    string next = current;

                    sort(next.begin() + l,
                         next.begin() + r + 1);

                    if (is_sorted(next.begin(), next.end())) {
                        return operations + 1;
                    }

                    if (visited.insert(next).second) {
                        q.push(next);
                    }
                }
            }
        }

        operations++;
    }

    return -1;
}

TIME COMPLEXITY:
----------------
Exponential in the worst case due to the number of distinct
string states. Each state examines O(n^2) substrings, and
each substring sort can take O(n log n).

SPACE COMPLEXITY:
-----------------
Exponential in the worst case for the BFS queue and visited
set. Each stored state requires O(n) space.

Note: This approach is only for understanding and is not
suitable for the given constraint n <= 10^5.

============================================================
OPTIMAL APPROACH: CASE ANALYSIS
============================================================

OBSERVATION:
------------
Let:
    mn = minimum character in s
    mx = maximum character in s

A sorted string must place its minimum character at the
beginning and its maximum character at the end.

The answer depends on whether the string is already sorted
and where its minimum and maximum characters occur.

INTUITION:
----------
Case 1: Already sorted
    No operation is required.
    Answer = 0

Case 2: Length is 2 and string is unsorted
    The only substring containing both characters is the
    entire string, which is forbidden.
    Answer = -1

Case 3: s[0] == mn OR s[n-1] == mx
    One boundary is already correct.
    Sort the remaining proper substring.
    Answer = 1

Case 4: mn or mx appears at an interior position
    One operation can position the required extreme at a
    boundary, and another can sort the remaining substring.
    Answer = 2

Case 5: None of the above
    Neither extreme is at its required boundary, and neither
    occurs in the interior. At least three operations are
    necessary and sufficient.
    Answer = 3

PSEUDO CODE:
------------
function minOperations(s):
    n = length(s)

    if s is sorted:
        return 0

    if n == 2:
        return -1

    mn = minimum character in s
    mx = maximum character in s

    if s[0] == mn or s[n-1] == mx:
        return 1

    for i from 1 to n-2:
        if s[i] == mn or s[i] == mx:
            return 2

    return 3

COMPLETE OPTIMAL CODE (REVISION ONLY):
--------------------------------------
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        if (is_sorted(s.begin(), s.end())) {
            return 0;
        }

        if (n == 2) {
            return -1;
        }

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }

        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }

        return 3;
    }
};

TIME COMPLEXITY:
----------------
O(n), where n is the length of the string.
Sorting check: O(n)
Finding minimum and maximum: O(n)
Interior scan: O(n)

SPACE COMPLEXITY:
-----------------
O(1) auxiliary space, excluding implementation details
of standard-library algorithms.

============================================================
DRY RUN WITH EXAMPLE
============================================================

Example: s = "card"

Step 1:
    Is "card" sorted?
    No.

Step 2:
    n = 4, so the length-2 impossible case does not apply.

Step 3:
    mn = 'a'
    mx = 'r'

Step 4:
    s[0] = 'c', which is not mn.
    s[3] = 'd', which is not mx.

Step 5:
    Check interior characters:
    s[1] = 'a' = mn

    An extreme character occurs in the interior.

Step 6:
    Return 2.

Actual operations:
    "card" -> sort "car" -> "acrd"
    "acrd" -> sort "rd"  -> "acdr"

Final answer: 2

============================================================
INTERVIEW NOTES
============================================================

PATTERN:
--------
Greedy case analysis on character extremes and their
positions in a string.

KEY OBSERVATION:
----------------
Only the positions of the minimum and maximum characters
matter after checking whether the string is already sorted.

COMMON MISTAKES:
----------------
1. Forgetting to check whether the string is already sorted.
2. Forgetting that sorting the entire string is forbidden.
3. Returning 1 for every unsorted string.
4. Missing the special case n == 2.
5. Scanning only for the minimum or only for the maximum
   in the interior.
6. Using a brute-force simulation for n = 10^5.
7. Confusing a substring (contiguous) with a subsequence.

WHEN TO USE THIS APPROACH:
--------------------------
Use case analysis when:
- The operation has a strong restriction, such as excluding
  the entire string.
- The answer depends on extreme values and their positions.
- The problem hints reveal a small fixed set of outcomes.
- A linear scan can replace expensive operation simulation.

============================================================
*/
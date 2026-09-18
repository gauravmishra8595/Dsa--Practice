#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        // Find first and last occurrence of every character.
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // Find the smallest valid interval for every character.
        for (int c = 0; c < 26; c++) {
            if (last[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];
            bool valid = true;

            for (int i = l; i <= r; i++) {
                int x = s[i] - 'a';

                // x occurs before l -> interval is invalid.
                if (first[x] < l) {
                    valid = false;
                    break;
                }

                // Include all occurrences of x.
                r = max(r, last[x]);
            }

            if (valid)
                intervals.push_back({l, r});
        }

        // Interval scheduling: choose earliest finishing intervals.
        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        vector<string> ans;
        int prevEnd = -1;

        for (auto &[l, r] : intervals) {
            if (l > prevEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                prevEnd = r;
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<string> tests = {
        "adefaddaccc",
        "abbaccd",
        "abab"
    };

    for (const string &s : tests) {
        vector<string> ans = sol.maxNumOfSubstrings(s);

        cout << "Input: " << s << '\n';
        cout << "Output: [";

        for (int i = 0; i < (int)ans.size(); i++) {
            if (i > 0)
                cout << ", ";

            cout << '"' << ans[i] << '"';
        }

        cout << "]\n\n";
    }

    return 0;
}


/*
===============================================================================
                    LEETCODE 1520 - MAXIMUM NUMBER OF
                         NON-OVERLAPPING SUBSTRINGS
===============================================================================

PROBLEM STATEMENT
-----------------
Given a string s of lowercase English letters, return the maximum number of
non-empty substrings such that:

1. Every character that appears in a chosen substring occurs only inside that
   substring.
2. The chosen substrings do not overlap.
3. If multiple answers contain the maximum number of substrings, the answer
   with the minimum total length is preferred.

Any valid answer satisfying these conditions is accepted.


EXAMPLE
-------
Input:
s = "adefaddaccc"

Output:
["e", "f", "ccc"]

Explanation:

"e"  -> e occurs only once.
"f"  -> f occurs only once.
"ccc" -> all occurrences of c are inside "ccc".

These three substrings are non-overlapping and give the maximum count.


===============================================================================
BRUTE FORCE APPROACH
===============================================================================

IDEA
----
Try every possible substring [l, r].

A substring is valid if every character inside it has all of its occurrences
inside [l, r].

After finding all valid substrings, choose a maximum number of non-overlapping
ones using backtracking/DP.

This approach is useful for understanding but is too slow for large input.

PSEUDO CODE
-----------
1. Find first and last occurrence of every character.
2. Generate every possible substring [l, r].
3. Check whether every character in [l, r] has:
       first[character] >= l
       last[character]  <= r
4. Store all valid intervals.
5. Try every combination of non-overlapping intervals.
6. Keep the combination having maximum number of intervals.
7. Return the corresponding substrings.

COMPLETE BRUTE FORCE CODE
-------------------------
/*
class BruteForceSolution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // Generate all possible intervals.
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                bool valid = true;

                for (int i = l; i <= r; i++) {
                    int c = s[i] - 'a';

                    if (first[c] < l || last[c] > r) {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                    intervals.push_back({l, r});
            }
        }

        vector<string> best;
        vector<string> current;

        function<void(int, int)> dfs =
            [&](int idx, int prevEnd) {

                if (current.size() > best.size()) {
                    best = current;
                }

                for (int i = idx; i < intervals.size(); i++) {
                    int l = intervals[i].first;
                    int r = intervals[i].second;

                    if (l > prevEnd) {
                        current.push_back(
                            s.substr(l, r - l + 1)
                        );

                        dfs(i + 1, r);

                        current.pop_back();
                    }
                }
            };

        dfs(0, -1);

        return best;
    }
};
*/

// TIME COMPLEXITY
// ---------------
// Generating all substrings:
// O(N^2)

// Checking each substring:
// O(N)

// Therefore:
// O(N^3)

// Backtracking can additionally be exponential in the number of valid
// intervals.

// SPACE COMPLEXITY
// ----------------
// O(N^2) for storing all candidate intervals.

// Recursion can also require additional space.


// ===============================================================================
// OPTIMAL APPROACH
// ===============================================================================

// OBSERVATION
// -----------
// There are only 26 lowercase English letters.

// For every character, calculate:

//     first[c] = first occurrence of c
//     last[c]  = last occurrence of c

// Suppose we start a substring at first[c].

// Initially:

//     l = first[c]
//     r = last[c]

// Now scan from l to r.

// If we encounter character x:

//     r = max(r, last[x])

// because the substring must contain every occurrence of x.

// However, if:

//     first[x] < l

// then x appears before our proposed substring, so this interval can never
// be valid.


// INTUITION
// ---------
// For every character, construct the SMALLEST valid interval starting from its
// first occurrence.

// Example:

//     s = "adefaddaccc"

// For 'a':

//     [0, 7]

// because a occurs from 0 to 7.

// For 'd':

//     initially [1, 6]

// but this interval contains 'a', whose first occurrence is 0.

// Therefore 'd' cannot form a valid independent substring.

// For 'e':

//     [2, 2]

// For 'f':

//     [3, 3]

// For 'c':

//     [8, 10]

// So the valid intervals are:

//     [0,7]
//     [2,2]
//     [3,3]
//     [8,10]

// Now the problem becomes an interval scheduling problem:

//     Select the maximum number of non-overlapping intervals.

// The classic greedy solution is to always choose the interval that ends
// earliest.


// PSEUDO CODE
// -----------
// 1. Find first and last occurrence of every character.
// 2. For every character c:
//        l = first[c]
//        r = last[c]

//        Scan i from l to r:
//            x = s[i]

//            If first[x] < l:
//                interval is invalid.

//            r = max(r, last[x])

//        If valid:
//            store [l, r]

// 3. Sort intervals by ending position.
// 4. Greedily select an interval if:
//        l > previousEnd

// 5. Add the substring to the answer.
// 6. Return answer.


// COMPLETE OPTIMAL CODE
// ---------------------
/*
class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';

            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        for (int c = 0; c < 26; c++) {
            if (last[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];
            bool valid = true;

            for (int i = l; i <= r; i++) {
                int x = s[i] - 'a';

                if (first[x] < l) {
                    valid = false;
                    break;
                }

                r = max(r, last[x]);
            }

            if (valid)
                intervals.push_back({l, r});
        }

        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a,
                const pair<int, int>& b) {
                 return a.second < b.second;
             });

        vector<string> ans;
        int prevEnd = -1;

        for (auto &[l, r] : intervals) {
            if (l > prevEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                prevEnd = r;
            }
        }

        return ans;
    }
};
*/

// TIME COMPLEXITY
// ---------------
// Finding first/last occurrences:
// O(N)

// There are only 26 characters, and each character's interval is scanned.

// At most:
// O(26 * N)

// Sorting at most 26 intervals:
// O(26 log 26)

// Since 26 is constant:

// Overall:
// O(N)

// SPACE COMPLEXITY
// ----------------
// First/last arrays:
// O(26)

// At most 26 intervals:
// O(26)

// Ignoring output:
// O(1)

// Including output:
// O(N)


// ===============================================================================
// DRY RUN WITH EXAMPLE
// ===============================================================================

// s = "adefaddaccc"

// Index:
//      0 1 2 3 4 5 6 7 8 9 10
//      a d e f a d d a c c  c


// STEP 1: FIRST AND LAST OCCURRENCES
// -----------------------------------

// Character    First    Last
// a              0        7
// d              1        6
// e              2        2
// f              3        3
// c              8       10


// STEP 2: BUILD VALID INTERVALS
// -----------------------------

// For 'a':

//     l = 0
//     r = 7

// Characters inside [0,7]:

//     a d e f a d d a

// Every character starts at or after 0.

// Therefore:

//     [0,7] -> "adefadda"

// is valid.


// For 'd':

//     l = 1
//     r = 6

// Inside this interval we encounter:

//     a

// But:

//     first[a] = 0

// and:

//     0 < 1

// Therefore 'a' occurs outside the interval.

// So:

//     [1,6]

// is invalid.


// For 'e':

//     l = 2
//     r = 2

// Only e exists inside.

// Therefore:

//     [2,2] -> "e"

// is valid.


// For 'f':

//     l = 3
//     r = 3

// Therefore:

//     [3,3] -> "f"

// is valid.


// For 'c':

//     l = 8
//     r = 10

// All c's are inside the interval.

// Therefore:

//     [8,10] -> "ccc"

// is valid.


// VALID INTERVALS
// ----------------

//     [0,7]   -> "adefadda"
//     [2,2]   -> "e"
//     [3,3]   -> "f"
//     [8,10]  -> "ccc"


// STEP 3: SORT BY END POSITION
// ----------------------------

//     [2,2]   -> "e"
//     [3,3]   -> "f"
//     [0,7]   -> "adefadda"
//     [8,10]  -> "ccc"


// STEP 4: GREEDY SELECTION
// ------------------------

// Initially:

//     prevEnd = -1

// Take [2,2]:

//     "e"

//     prevEnd = 2


// Take [3,3]:

//     "f"

//     prevEnd = 3


// Check [0,7]:

//     0 <= 3

// Overlap exists, so skip it.


// Take [8,10]:

//     8 > 3

// So take:

//     "ccc"

// Final answer:

//     ["e", "f", "ccc"]


// ===============================================================================
// INTERVIEW NOTES
// ===============================================================================

// PATTERN
// -------
// Greedy + Interval Scheduling

// The string problem is converted into a collection of valid intervals.

// Then we use the classic:

//     Earliest Finishing Interval First

// greedy strategy.


// KEY OBSERVATION
// ---------------
// For every character c, start from:

//     first[c]

// and initially end at:

//     last[c]

// While scanning the interval, expand the right boundary whenever another
// character requires a larger last occurrence.

// If any character has:

//     first[x] < left

// the interval is invalid.


// COMMON MISTAKES
// ---------------

// 1. WRONG LAST OCCURRENCE

//    Incorrect:
//        end[c] = 1;

//    Correct:
//        end[c] = i;


// 2. WRONG VALIDITY CONDITION

//    If:

//        first[x] < left

//    then the interval is INVALID.


// 3. FORGETTING TO EXPAND THE INTERVAL

//    We must do:

//        r = max(r, last[x]);

//    because every occurrence of x must be included.


// 4. ITERATING BEYOND 26 CHARACTERS

//    Since the alphabet contains 26 lowercase letters:

//        for (int c = 0; c < 26; c++)

//    not:

//        for (int c = 0; c < n; c++)


// 5. USING STARTING POSITION FOR GREEDY SORTING

//    The interval scheduling greedy strategy depends on the ending position.

//    Sort by:

//        interval.second


// 6. FORGETTING NON-OVERLAPPING CONDITION

//    Select interval [l,r] only when:

//        l > previousEnd


// 7. NOT UNDERSTANDING WHY SMALLEST INTERVALS MATTER

//    We want the maximum NUMBER of substrings.

//    Smaller valid intervals leave more space for additional substrings.


// WHEN TO USE THIS APPROACH
// -------------------------
// Use this approach when:

// - The alphabet is small/fixed.
// - Every character has global first/last occurrence constraints.
// - A valid substring can be represented as an interval.
// - You need the maximum number of non-overlapping valid intervals.
// - The problem resembles interval scheduling after preprocessing.

// GENERAL PATTERN:

//     Find first/last occurrence
//               |
//               v
//     Construct smallest valid intervals
//               |
//               v
//     Sort by ending position
//               |
//               v
//     Greedy interval selection
//               |
//               v
//            Answer

// ===============================================================================
// */

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        vector<long long> dp(s.size() + 1, 0);
        vector<long long> last(26, 0);

        for (int i = 1; i <= (int)s.size(); i++) {
            int c = s[i - 1] - 'a';
            dp[i] = (2LL * dp[i - 1] + 1 - last[c] + MOD) % MOD;
            last[c] = (dp[i - 1] + 1) % MOD;
        }

        return dp[s.size()];
    }
};

int main() {
    Solution sol;

    vector<string> tests = {
        "abc",
        "aba",
        "aaa"
    };

    for (const string& s : tests) {
        cout << s << " -> " << sol.distinctSubseqII(s) << '\n';
    }

    return 0;
}

/*
================================================================================
                    LEETCODE 940 - DISTINCT SUBSEQUENCES II
================================================================================

Problem Statement:
------------------
Given a string s, return the number of distinct non-empty subsequences of s.
Since the answer can be very large, return it modulo 1e9 + 7.

A subsequence is obtained by deleting zero or more characters without
changing the relative order of the remaining characters.

Example:
--------
Input:
    s = "aba"

All distinct non-empty subsequences are:
    "a", "b", "aa", "ab", "ba", "aba"

Answer:
    6

For:
    s = "abc"

All non-empty subsequences are distinct:
    "a", "b", "c", "ab", "ac", "bc", "abc"

Answer:
    7


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Generate every subsequence using recursion/bitmasking.

There are 2^n subsequences. However, many of them can be identical when
characters repeat.

Use a set to store all generated subsequences. Finally, return the size
of the set.

Pseudo Code:
-----------
function generate(index, current):
    if index == n:
        if current is not empty:
            insert current into set
        return

    generate(index + 1, current)

    current += s[index]
    generate(index + 1, current)
    remove last character

main:
    generate(0, "")
    return size(set)


Complete Brute Force Code:
---------------------------
/*
class Solution {
public:
    set<string> st;

    void generate(int index, string &s, string &cur) {
        if (index == s.size()) {
            if (!cur.empty())
                st.insert(cur);
            return;
        }

        // Do not take current character
        generate(index + 1, s, cur);

        // Take current character
        cur.push_back(s[index]);
        generate(index + 1, s, cur);
        cur.pop_back();
    }

    int distinctSubseqII(string s) {
        st.clear();

        string cur;
        generate(0, s, cur);

        return st.size();
    }
};
*/

// Time Complexity:
// ----------------
// There are O(2^n) subsequences, and inserting strings into a set can take
// up to O(n log(2^n)) in the worst case.

// Overall:
//     O(n * 2^n)

// Space Complexity:
// -----------------
// The set can contain O(2^n) subsequences, each of length up to n.

// Overall:
//     O(n * 2^n)

// This approach is only useful for understanding the problem and cannot handle
// large inputs.


// ================================================================================
// OPTIMAL APPROACH
// ================================================================================

// Observation:
// ------------
// If we simply double the number of subsequences whenever we see a new
// character, duplicates are created when the same character occurs again.

// Suppose the current number of distinct non-empty subsequences is dp[i-1].

// For the new character s[i-1]:

//     Existing subsequences remain:
//         dp[i-1]

//     Append the new character to every existing subsequence:
//         dp[i-1]

//     The character alone creates one more subsequence:
//         1

// So initially:

//     dp[i] = 2 * dp[i-1] + 1

// But if this character appeared earlier, some subsequences are duplicated.

// We need to subtract exactly the set of subsequences that were created
// during the previous occurrence of this character.

// Intuition:
// ----------
// For every character c, maintain:

//     last[c] = number of distinct subsequences that existed
//               before the previous occurrence of c, plus the single
//               character c itself.

// When c appears again:

//     dp[i] = 2 * dp[i-1] + 1 - last[c]

// After processing c, update:

//     last[c] = dp[i-1] + 1

// This removes duplicates without explicitly storing the subsequences.

// Pseudo Code:
// -----------
// MOD = 1e9 + 7

// dp[0] = 0
// last[26] = {0}

// for i from 1 to n:
//     c = s[i-1]

//     dp[i] = 2 * dp[i-1] + 1 - last[c]
//     dp[i] %= MOD

//     last[c] = dp[i-1] + 1

// return dp[n]


// Complete Optimal Code:
// ----------------------
/*
class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;

        vector<long long> dp(s.size() + 1, 0);
        vector<long long> last(26, 0);

        for (int i = 1; i <= (int)s.size(); i++) {
            int c = s[i - 1] - 'a';

            dp[i] =
                (2LL * dp[i - 1] + 1 - last[c] + MOD) % MOD;

            last[c] = (dp[i - 1] + 1) % MOD;
        }

        return dp[s.size()];
    }
};
*/


// Time Complexity:
// ----------------
// We process every character exactly once.

//     O(n)

// Space Complexity:
// -----------------
// dp array:
//     O(n)

// last array:
//     O(26) = O(1)

// Therefore:
//     O(n)

// The implementation can also be reduced to O(1) DP space, but O(n) is
// perfectly acceptable and makes the recurrence easier to understand.


// ================================================================================
// DRY RUN WITH EXAMPLE: "aba"
// ================================================================================

// Initially:

//     dp[0] = 0
//     last[a] = 0
//     last[b] = 0
//     last[c] = 0
//     ...

// --------------------------------------------------
// i = 1, character = 'a'

// Before processing:
//     dp[0] = 0
//     last[a] = 0

// Formula:

//     dp[1] = 2 * 0 + 1 - 0
//           = 1

// Subsequence:
//     "a"

// Update:

//     last[a] = dp[0] + 1
//             = 1

// --------------------------------------------------
// i = 2, character = 'b'

// Before processing:
//     dp[1] = 1
//     last[b] = 0

// Formula:

//     dp[2] = 2 * 1 + 1 - 0
//           = 3

// Subsequences:

//     "a"
//     "b"
//     "ab"

// Update:

//     last[b] = dp[1] + 1
//             = 2

// --------------------------------------------------
// i = 3, character = 'a'

// Before processing:
//     dp[2] = 3
//     last[a] = 1

// If we did not remove duplicates:

//     2 * 3 + 1 = 7

// But the second 'a' recreates one group of subsequences that already
// existed from the previous 'a'.

// Therefore:

//     dp[3] = 2 * 3 + 1 - 1
//           = 6

// Final distinct subsequences:

//     "a"
//     "b"
//     "aa"
//     "ab"
//     "ba"
//     "aba"

// Answer:
//     6


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Dynamic Programming + Duplicate Removal

// This is a classic "count distinct subsequences" DP problem.

// Key Observation:
// ----------------
// For every new character:

//     new_count = 2 * old_count + 1

// Then subtract the number of subsequences that were already generated
// when the same character appeared previously.

// The last-occurrence information allows duplicate removal in O(1) time
// per character.

// Common Mistakes:
// ----------------
// 1. Forgetting the +1.

//    The +1 represents the subsequence containing only the current character.

// 2. Forgetting duplicate removal.

//    Simply doing:

//        dp = 2 * dp + 1

//    counts duplicate subsequences when characters repeat.

// 3. Incorrectly storing last[c].

//    After processing character c:

//        last[c] = dp[i-1] + 1

// 4. Forgetting modulo.

//    The number of subsequences grows exponentially.

// 5. Negative modulo.

//    Use:

//        (value + MOD) % MOD

//    because subtraction can make the intermediate value negative.

// 6. Confusing subsequences with substrings.

//    Characters do not need to be contiguous.

// When to Use This Approach:
// --------------------------
// Use this approach when:

// - You need the number of DISTINCT subsequences.
// - The string length is too large for O(2^n).
// - Duplicate subsequences are caused by repeated characters.
// - Characters come from a small alphabet such as lowercase English letters.

// Core Formula to Remember:
// --------------------------
//     dp[i] = 2 * dp[i-1] + 1 - last[s[i-1]]

// and

//     last[s[i-1]] = dp[i-1] + 1

// Complexity:
// -----------
//     Time  = O(n)
//     Space = O(n) with the notebook implementation

// ================================================================================
// */

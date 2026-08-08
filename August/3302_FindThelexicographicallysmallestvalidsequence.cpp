#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> ans(m);
        vector<int> last(m, -1);

        // last[j] = latest index in word1 where word1[index] == word2[j]
        int i = n - 1;
        int j = m - 1;

        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        bool canSkip = true;
        j = 0;

        // Greedily choose the earliest possible index.
        for (i = 0; i < n; i++) {
            if (j == m)
                break;

            if (word1[i] == word2[j]) {
                ans[j++] = i;
            }
            else if (canSkip && (j == m - 1 || i < last[j + 1])) {
                // Use the one allowed mismatch here.
                canSkip = false;
                ans[j++] = i;
            }
        }

        return j == m ? ans : vector<int>();
    }
};

int main() {
    Solution sol;

    string word1 = "vbcca";
    string word2 = "abc";

    vector<int> ans = sol.validSequence(word1, word2);

    cout << "[";
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
        if (i + 1 < (int)ans.size())
            cout << ",";
    }
    cout << "]\n";

    return 0;
}


/*
================================================================================
LeetCode 3302 - Find the Lexicographically Smallest Valid Sequence
================================================================================

Problem Statement
-----------------
You are given two strings word1 and word2.

A string x is called "almost equal" to y if we can change at most one
character of x to make it identical to y.

We need to choose indices from word1 such that:

1. The indices are strictly increasing.
2. The characters at those indices form a string almost equal to word2.
3. The resulting index array is lexicographically smallest.

Return the lexicographically smallest valid index sequence.
If no valid sequence exists, return an empty array.

Constraints:
    1 <= word2.length < word1.length <= 3 * 10^5

Source: LeetCode 3302.


Example
-------
Input:
    word1 = "vbcca"
    word2 = "abc"

Output:
    [0,1,2]

Explanation:
    word1[0] = 'v' -> can be changed to 'a'
    word1[1] = 'b'
    word1[2] = 'c'

So the selected string "vbc" is almost equal to "abc".

The important point is that we minimize the INDEX ARRAY,
not the resulting string.


================================================================================
Brute Force Approach
================================================================================

Idea
----
Try every possible subsequence of word1 having length m = word2.length().

For every selected subsequence:

    selected[i] = word1[index[i]]

Count how many positions differ from word2.

If the number of mismatches is <= 1, the sequence is valid.

Among all valid sequences, keep the lexicographically smallest one.

This works for small inputs but is far too slow for n <= 3 * 10^5.


Pseudo Code
-----------
    function bruteForce(word1, word2):

        n = word1.length
        m = word2.length

        best = empty

        function dfs(pos, start, current):

            if pos == m:
                mismatches = 0

                for i = 0 to m-1:
                    if word1[current[i]] != word2[i]:
                        mismatches++

                if mismatches <= 1:
                    if best is empty OR current < best:
                        best = current

                return

            for i = start to n - (m - pos):
                current.push_back(i)
                dfs(pos + 1, i + 1, current)
                current.pop_back()

        dfs(0, 0, [])

        return best


Complete Brute Force Code
-------------------------
(The following code is intentionally inside comments and is NOT executable.)

class BruteForceSolution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> best;
        vector<int> current;

        function<void(int, int)> dfs = [&](int pos, int start) {
            if (pos == m) {
                int mismatches = 0;

                for (int i = 0; i < m; i++) {
                    if (word1[current[i]] != word2[i]) {
                        mismatches++;
                    }
                }

                if (mismatches <= 1) {
                    if (best.empty() || current < best) {
                        best = current;
                    }
                }

                return;
            }

            // Need (m - pos) elements including current position.
            for (int i = start; i <= n - (m - pos); i++) {
                current.push_back(i);
                dfs(pos + 1, i + 1);
                current.pop_back();
            }
        };

        dfs(0, 0);
        return best;
    }
};


Time Complexity
----------------
There are:

    C(n, m)

possible subsequences.

Checking one subsequence takes O(m).

Therefore:

    O(C(n, m) * m)

which is exponential in practice.

Space Complexity
-----------------
Recursion depth + current sequence:

    O(m)


================================================================================
Optimal Approach
================================================================================

Observation
-----------
We are allowed at most ONE mismatch.

Therefore, while constructing the answer from left to right:

    - If word1[i] == word2[j],
      choosing i is always safe.

    - If word1[i] != word2[j],
      we may use this index as our ONE mismatch,
      but only if the remaining part of word2 can still be matched.

The difficult part is deciding whether taking a mismatch now
will leave enough positions to finish the sequence.

To answer that efficiently, we preprocess the suffix of word1.


Intuition
---------
First scan from RIGHT to LEFT.

For every position j in word2:

    last[j] = the latest index in word1
              that can match word2[j]

while preserving the order for the remaining suffix.

Example:

    word1 = "bacdc"
    word2 = "abc"

For the suffixes of word2, we know where they can still be matched.

Suppose we are currently trying to match word2[j] using word1[i],
but the characters differ.

We can spend our one mismatch here only if:

    i < last[j + 1]

This means that after taking i, there is still a valid position
after i from which word2[j + 1] can be matched.

If j is the final character of word2, there is no suffix left,
so any index can be used as the one mismatch.


Why is the greedy choice optimal?
---------------------------------
We process word1 from left to right.

The first index chosen for the answer has the highest priority
in lexicographical ordering.

Therefore, whenever an index can safely be used, we should choose
the earliest possible index.

For an exact match:

    word1[i] == word2[j]

we always choose i immediately.

For a mismatch:

    word1[i] != word2[j]

we choose i only when using the mismatch here still allows
the remaining characters to be matched.

This gives the earliest possible index at every position,
which makes the complete answer lexicographically smallest.


Pseudo Code
-----------
    function validSequence(word1, word2):

        n = word1.length
        m = word2.length

        ans = array of size m
        last = array of size m filled with -1

        // Build suffix feasibility information.
        i = n - 1
        j = m - 1

        while i >= 0 and j >= 0:

            if word1[i] == word2[j]:
                last[j] = i
                j--

            i--

        canSkip = true
        j = 0

        // Greedy construction.
        for i = 0 to n-1:

            if j == m:
                break

            if word1[i] == word2[j]:

                ans[j] = i
                j++

            else if canSkip AND
                    (j == m-1 OR i < last[j+1]):

                // Spend the one mismatch.
                ans[j] = i
                canSkip = false
                j++

        if j == m:
            return ans

        return empty array


Complete Optimal Code
---------------------
(The following is intentionally inside comments and is NOT executable.)

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> ans(m);
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        bool canSkip = true;
        j = 0;

        for (i = 0; i < n; i++) {
            if (j == m)
                break;

            if (word1[i] == word2[j]) {
                ans[j++] = i;
            }
            else if (canSkip &&
                     (j == m - 1 || i < last[j + 1])) {

                canSkip = false;
                ans[j++] = i;
            }
        }

        return j == m ? ans : vector<int>();
    }
};


Time Complexity
----------------
Right-to-left preprocessing:

    O(n)

Left-to-right greedy construction:

    O(n)

Total:

    O(n + m)

Since m <= n:

    O(n)


Space Complexity
----------------
The last[] array and answer array both require O(m).

Therefore:

    O(m)

Auxiliary space apart from the returned answer:

    O(m)


================================================================================
Dry Run with Example
================================================================================

Input:

    word1 = "vbcca"
    word2 = "abc"


Step 1: Build last[]

Scan word1 from right to left.

word2 = a b c
        0 1 2

For 'c':
    latest matching index = 3

For 'b':
    latest matching index = 2

For 'a':
    no exact match exists.

So conceptually:

    last = [-1, 2, 3]


Step 2: Greedy scan from left to right

Initially:

    j = 0
    word2[j] = 'a'
    canSkip = true


i = 0:

    word1[0] = 'v'
    word2[0] = 'a'

Characters differ.

Can we use our one mismatch?

Yes, because j is not the last position and:

    i < last[1]
    0 < 2

So choose index 0.

    ans = [0]
    j = 1
    canSkip = false


i = 1:

    word1[1] = 'b'
    word2[1] = 'b'

Exact match.

    ans = [0,1]
    j = 2


i = 2:

    word1[2] = 'c'
    word2[2] = 'c'

Exact match.

    ans = [0,1,2]
    j = 3


j == word2.length()

Done.

Final answer:

    [0,1,2]


================================================================================
Interview Notes
================================================================================

Pattern
-------
Greedy + Two Pointers + Suffix Preprocessing


Key Observation
---------------
When choosing an index from left to right, the earliest index is
always preferred because the answer itself must be lexicographically
smallest.

The only tricky decision is when the current character is different.

Since only one mismatch is allowed, we need to know whether the
remaining suffix can still be matched.

The right-to-left scan provides exactly this information.


Common Mistakes
---------------
1. Minimizing the resulting string instead of the index array.

   The problem asks for lexicographically smallest INDICES.

2. Always taking the first mismatch.

   This can make the remaining suffix impossible.

3. Using the mismatch without checking the suffix.

   Before spending the mismatch, make sure the remaining characters
   can still be selected in increasing order.

4. Using a DP table of size O(n * m).

   With n up to 3 * 10^5, this is far too large.

5. Forgetting that the mismatch can be used at the last character.

   If j == m - 1, there is no remaining suffix to check, so the
   current index can safely be used as the mismatch.

6. Confusing "at most one mismatch" with "exactly one mismatch".

   Zero mismatches is also valid.


When to Use This Approach
-------------------------
Use this pattern when:

    - You need the lexicographically smallest subsequence/index array.
    - You are allowed a very small number of mismatches.
    - You need to greedily choose the earliest possible index.
    - A suffix/prefix feasibility check can tell whether a greedy
      choice is safe.
    - n is very large, making O(n * m) DP impossible.

General Pattern:

    1. Precompute suffix feasibility from the right.
    2. Greedily construct the answer from the left.
    3. Take the earliest possible choice.
    4. Spend the limited mismatch only when the suffix remains feasible.


Final Complexity:

    Time  = O(n + m)
    Space = O(m)

================================================================================
*/
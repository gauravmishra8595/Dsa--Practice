#include <bits/stdc++.h>
using namespace std;

/* Optimal solution implementation */
class Solution
{
public:
    string lexPalindromicPermutation(string s, string target)
    {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        // A palindrome can have at most one odd frequency.
        char mid = 0;
        for (int i = 0; i < 26; i++)
        {
            if (cnt[i] % 2)
            {
                if (mid != 0)
                    return "";
                mid = char('a' + i);
                cnt[i]--;
            }
        }

        /*
            cnt now contains pairs only.
            cnt[c] = number of copies available in the left half * 2.
        */

        int half = n / 2;

        // Try to make target's first half exactly.
        // Subtract 2 because every chosen character consumes one
        // character from both sides of the palindrome.
        for (int i = 0; i < half; i++)
            cnt[target[i] - 'a'] -= 2;

        auto valid = [&]()
        {
            for (int x : cnt)
                if (x < 0)
                    return false;
            return true;
        };

        // If target's first half can be formed, check the palindrome
        // whose first half is exactly target's first half.
        if (valid())
        {
            string left = target.substr(0, half);
            string right = left;
            reverse(right.begin(), right.end());

            string candidate = left;
            if (n & 1)
                candidate += mid;
            candidate += right;

            if (candidate > target)
                return candidate;
        }
        for (int i = half - 1; i >= 0; i--)
        {
            int cur = target[i] - 'a';

            cnt[cur] += 2;
            if (!valid())
                continue;
            for (int j = cur + 1; j < 26; j++)
            {
                if (cnt[j] < 2)
                    continue;

                cnt[j] -= 2;

                string left = target.substr(0, i);
                left += char('a' + j);

                for (int c = 0; c < 26; c++)
                    left += string(cnt[c] / 2, char('a' + c));

                string right = left;
                reverse(right.begin(), right.end());

                string answer = left;
                if (n & 1)
                    answer += mid;
                answer += right;

                return answer;
            }
        }

        return "";
    }
};

int main()
{
    Solution sol;

    cout << sol.lexPalindromicPermutation("baba", "abba") << '\n';
    cout << sol.lexPalindromicPermutation("baba", "bbaa") << '\n';
    cout << sol.lexPalindromicPermutation("abc", "abb") << '\n';
    cout << sol.lexPalindromicPermutation("aac", "abb") << '\n';

    return 0;
}

/*
================================================================================
PROBLEM: 3734. Lexicographically Smallest Palindromic Permutation Greater Than Target
================================================================================

Problem Statement:
------------------
You are given two strings s and target of the same length n.

Return the lexicographically smallest string that:
1. Is a permutation of s.
2. Is a palindrome.
3. Is strictly greater than target.

If no such string exists, return "".

Constraints:
    1 <= n <= 300
    s and target contain lowercase English letters.


Example:
--------
Input:
    s = "baba"
    target = "abba"

Possible palindromic permutations:
    "abba"
    "baab"

"baab" is the smallest palindrome strictly greater than "abba".

Output:
    "baab"


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Generate all permutations of s.

For every permutation:
    1. Check whether it is a palindrome.
    2. Check whether it is greater than target.
    3. Keep the lexicographically smallest valid answer.

This is only useful as a conceptual baseline because n can be as large as 300.

Pseudo Code:
-----------
function bruteForce(s, target):
    ans = ""

    generate every permutation p of s:
        if p is palindrome AND p > target:
            if ans is empty OR p < ans:
                ans = p

    return ans


Complete Brute Force Code (for revision only):
-----------------------------------------------

class BruteForceSolution {
public:
    string ans;
    string target;

    bool isPalindrome(const string& s) {
        int l = 0, r = s.size() - 1;

        while (l < r) {
            if (s[l] != s[r])
                return false;

            l++;
            r--;
        }

        return true;
    }

    void generate(string& s, int idx) {
        if (idx == (int)s.size()) {
            if (isPalindrome(s) && s > target) {
                if (ans.empty() || s < ans)
                    ans = s;
            }
            return;
        }

        for (int i = idx; i < (int)s.size(); i++) {
            swap(s[idx], s[i]);
            generate(s, idx + 1);
            swap(s[idx], s[i]);
        }
    }

    string solve(string s, string t) {
        target = t;
        ans = "";

        generate(s, 0);

        return ans;
    }
};

Time Complexity:
----------------
O(n! * n)

There can be n! permutations and checking a palindrome/comparison
takes O(n).

Space Complexity:
-----------------
O(n)

Recursion depth is O(n), ignoring the generated permutations.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
A palindrome is completely determined by its first half and its middle
character.

For example:

    "baab"

First half:
    "ba"

Second half is forced:
    reverse("ba") = "ab"

For odd length:

    "abcba"

First half:
    "ab"

Middle:
    "c"

Second half:
    "ba"

Therefore, instead of permuting all n characters, we only need to
construct the first half.

A palindrome is possible iff at most one character has odd frequency.

For every character:
    halfCount[c] = frequency[c] / 2

If there is one odd frequency, that character becomes the middle.


Intuition:
---------
We need the smallest palindrome greater than target.

Think of the first half of our answer.

There are two possibilities:

1. The first half is exactly target's first half.

   Then there is only one palindrome possible with that first half.
   We construct it and check whether it is > target.

2. The first half must become larger than target's first half.

   To make the answer as small as possible:
   - Keep the prefix equal to target for as long as possible.
   - Change the RIGHTMOST possible position.
   - At that position choose the SMALLEST character greater than target[i].
   - Fill all remaining positions with the smallest available characters.

Why rightmost?

Example:

    target half = "abca"

Changing index 0 gives something like:
    "bb..."

Changing index 2 gives:
    "abda..."

The second answer is lexicographically smaller because it preserves
a longer prefix of target.

Why smallest larger character?

At the first differing position, choosing the smallest possible
character greater than target produces the smallest valid answer.


Pseudo Code:
-----------
count frequencies of s

if more than one odd frequency:
    return ""

store odd character as middle
remove the middle character from its count

for every character in target's first half:
    consume two copies from count

if all counts are non-negative:
    construct palindrome using target's first half
    if palindrome > target:
        return palindrome

for i from half-1 down to 0:

    restore the pair used by target[i]

    if target[0..i-1] cannot be formed:
        continue

    for c from target[i]+1 to 'z':
        if c has at least two copies:
            consume two copies of c

            left = target[0..i-1]
            left += c

            fill remaining left-half positions
            in increasing character order

            right = reverse(left)

            answer = left + middle + right

            return answer

return ""


Complete Optimal Code (LeetCode version, for revision only):
---------------------------------------------------------------

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                if (mid != 0)
                    return "";

                mid = char('a' + i);
                cnt[i]--;
            }
        }

        int half = n / 2;

        for (int i = 0; i < half; i++)
            cnt[target[i] - 'a'] -= 2;

        auto valid = [&]() {
            for (int x : cnt) {
                if (x < 0)
                    return false;
            }

            return true;
        };

        First try to keep the complete first half equal to target.
        if (valid()) {
            string left = target.substr(0, half);

            string right = left;
            reverse(right.begin(), right.end());

            string candidate = left;

            if (n & 1)
                candidate += mid;

            candidate += right;

            if (candidate > target)
                return candidate;
        }

        // Find the rightmost position where we can increase target.
        for (int i = half - 1; i >= 0; i--) {
            int cur = target[i] - 'a';

            // Restore the pair of target[i].
            cnt[cur] += 2;

            if (!valid())
                continue;

            // Pick the smallest character greater than target[i].
            for (int j = cur + 1; j < 26; j++) {
                if (cnt[j] < 2)
                    continue;

                cnt[j] -= 2;

                string left = target.substr(0, i);
                left += char('a' + j);

                // Smallest possible remaining suffix.
                for (int c = 0; c < 26; c++)
                    left += string(cnt[c] / 2, char('a' + c));

                string right = left;
                reverse(right.begin(), right.end());

                string answer = left;

                if (n & 1)
                    answer += mid;

                answer += right;

                return answer;
            }
        }

        return "";
    }
};


Time Complexity:
----------------
O(26 * n)

There are O(n) positions in the first half.

At each position we scan at most 26 characters.

Building the final answer takes O(n).

Since the alphabet size is fixed at 26:

    O(26n) = O(n)

Space Complexity:
-----------------
O(26 + n)

The frequency array has only 26 elements.

The constructed answer uses O(n) space.

Ignoring the returned string, auxiliary space is O(26) = O(1).


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:
    s = "baba"
    target = "abba"

Step 1: Frequency
-----------------
a -> 2
b -> 2

No odd frequency.

Therefore:

    middle = ""

First-half counts:

    a -> 1
    b -> 1


Step 2: Try target's first half
--------------------------------
target first half:

    "ab"

Consume:
    a
    b

Everything is available.

Construct palindrome:

    left  = "ab"
    right = "ba"

Candidate:

    "abba"

But:

    "abba" > "abba"

is false.

So we need to make the first half larger.


Step 3: Move from right to left
--------------------------------
i = 1

target[i] = 'b'

Restore b.

Available first-half characters:

    a -> 1
    b -> 1

Need a character > 'b'.

None exists.

Continue.


i = 0

target[i] = 'a'

Restore a.

Now both a and b are available.

Need the smallest character > 'a'.

That character is:

    'b'


Choose 'b'.

Remaining character:

    'a'


Construct left half:

    "ba"


Mirror:

    "ab"


Final palindrome:

    "baab"


Compare:

    "baab" > "abba"

true.


Answer:
    "baab"


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Greedy + Frequency Counting + Palindrome Construction


Key Observation:
----------------
A palindromic permutation is completely determined by its first half
and, for odd n, its middle character.

Therefore we should never generate complete permutations.

To obtain the smallest answer greater than target:

    1. Keep the longest possible prefix equal to target.
    2. Change the rightmost possible position.
    3. Use the smallest character greater than target[i].
    4. Fill the remaining positions in sorted order.


Common Mistakes:
----------------
1. Generating all permutations.

   Factorial complexity is impossible for n <= 300.

2. Forgetting the palindrome condition.

   Every character used in the first half must have another copy
   in the second half.

3. Mishandling odd frequencies.

   At most one character may have an odd frequency.

4. Changing the leftmost possible position.

   This produces a valid answer but not necessarily the smallest one.

5. Choosing an arbitrary larger character.

   We must choose the smallest available character greater than target[i].

6. Forgetting the equality case.

   The answer must be STRICTLY greater than target.

7. Filling the remaining half in descending order.

   After the first greater position is fixed, the remaining suffix
   must be as small as possible, so fill it in ascending order.

8. Checking only whether the first half is greater.

   For the special case where the first half is exactly target's
   first half, the middle and mirrored half determine whether the
   complete palindrome is strictly greater.


When to Use This Approach:
--------------------------
Use this pattern when:

- You need the lexicographically smallest string greater than a target.
- The answer has strong structural constraints.
- The string can be represented by a smaller independent portion.
- Character frequencies are important.
- You can make the first difference greedily.
- The alphabet is small, such as lowercase English letters.

General Template:

    Build frequency information
            |
            v
    Identify structural constraints
            |
            v
    Construct the smallest possible prefix
            |
            v
    Find the rightmost position to increase
            |
            v
    Choose smallest possible larger character
            |
            v
    Minimize the remaining suffix
            |
            v
    Build the final structured object


================================================================================
*/

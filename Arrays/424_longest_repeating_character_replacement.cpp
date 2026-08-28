#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int characterReplacement(string s, int k)
    {
        vector<int> freq(26, 0);

        int left = 0;
        int maxFreq = 0;
        int ans = 0;

        for (int right = 0; right < s.size(); right++)
        {
            freq[s[right] - 'A']++;

            maxFreq = max(maxFreq, freq[s[right] - 'A']);

            while ((right - left + 1) - maxFreq > k)
            {
                freq[s[left] - 'A']--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    string s;
    int k;

    cout << "Enter uppercase string: ";
    cin >> s;

    cout << "Enter k: ";
    cin >> k;

    cout << "Answer: " << sol.characterReplacement(s, k) << '\n';

    return 0;
}

/*
================================================================================
LEETCODE 424 - LONGEST REPEATING CHARACTER REPLACEMENT
================================================================================

Problem Statement:
------------------
You are given a string s consisting of uppercase English letters and
an integer k.

You can choose at most k characters in the string and replace them
with any other uppercase English character.

Return the length of the longest substring containing the same letter
after performing at most k replacements.


Example:
--------
Input:
    s = "AABABBA"
    k = 1

Output:
    4

Explanation:
-------------
Take substring:

    "AABA"

Replace the 'B' with 'A':

    "AAAA"

Length = 4.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Consider every possible substring.

For each substring:
    1. Count the frequency of every character.
    2. Find the character with maximum frequency.
    3. All other characters need to be replaced.
    4. If replacements <= k, the substring is valid.

Number of replacements required:

    substring length - maximum frequency


Pseudo Code:
-----------
ans = 0

for left = 0 to n-1:

    create frequency array

    for right = left to n-1:

        increase frequency of s[right]

        maxFreq = maximum frequency

        replacements =
            (right - left + 1) - maxFreq

        if replacements <= k:
            ans = max(ans, window length)

return ans


Complete Brute Force Code (inside comments only):
---------------------------------------------------

class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int ans = 0;

        for (int left = 0; left < n; left++) {

            vector<int> freq(26, 0);
            int maxFreq = 0;

            for (int right = left; right < n; right++) {

                freq[s[right] - 'A']++;

                maxFreq = max(
                    maxFreq,
                    freq[s[right] - 'A']
                );

                int len = right - left + 1;

                int replacements = len - maxFreq;

                if (replacements <= k)
                    ans = max(ans, len);
            }
        }

        return ans;
    }
};


Time Complexity:
----------------
O(26 * n^2)

For every substring we may scan 26 characters to find max frequency.

Since 26 is constant:

    O(n^2)


Space Complexity:
-----------------
O(26)

Therefore:

    O(1)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
For any window:

    [left ... right]

suppose the most frequent character occurs maxFreq times.

To make the entire window contain the same character, we need to
replace every other character.

Therefore:

    replacements =
        windowLength - maxFreq


The window is valid when:

    windowLength - maxFreq <= k


or:

    (right - left + 1) - maxFreq <= k


Intuition:
---------
Use a sliding window.

Expand the right pointer and maintain character frequencies.

Also maintain:

    maxFreq = maximum frequency of a single character in the window


If:

    windowLength - maxFreq <= k

the window is valid.

Otherwise, we have too many characters that would need replacement,
so move left forward until the window becomes valid again.


Important Optimization:
-----------------------
We do NOT decrease maxFreq when moving left.

Why?

Suppose maxFreq was 5.

After removing some characters, the actual maximum frequency might
become 4.

Keeping maxFreq = 5 can make the window look slightly more valid
than it really is.

However, this does NOT cause an incorrect answer.

We only use maxFreq to determine whether we need to shrink.

The algorithm still returns the correct maximum length.

This is a standard sliding-window optimization for this problem.


Pseudo Code:
-----------
freq[26] = 0

left = 0
maxFreq = 0
ans = 0

for right = 0 to n-1:

    freq[s[right]]++

    maxFreq =
        max(maxFreq, freq[s[right]])

    while windowLength - maxFreq > k:

        freq[s[left]]--
        left++

    ans =
        max(ans, windowLength)

return ans


Complete Optimal Code (inside comments only):
-----------------------------------------------

class Solution {
public:
    int characterReplacement(string s, int k) {

        vector<int> freq(26, 0);

        int left = 0;
        int maxFreq = 0;
        int ans = 0;

        for (int right = 0; right < s.size(); right++) {

            freq[s[right] - 'A']++;

            maxFreq = max(
                maxFreq,
                freq[s[right] - 'A']
            );

            while ((right - left + 1) - maxFreq > k) {

                freq[s[left] - 'A']--;

                left++;
            }

            ans = max(
                ans,
                right - left + 1
            );
        }

        return ans;
    }
};


Time Complexity:
----------------
O(n)

Each character is:
    - inserted once
    - removed at most once

Therefore:

    O(n)


Space Complexity:
-----------------
O(26)

Since there are only 26 uppercase English letters:

    O(1)


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:

    s = "AABABBA"
    k = 1


Start:

    left = 0
    maxFreq = 0
    ans = 0


right = 0
---------
Character = A

Window:

    "A"

Frequency:

    A = 1

maxFreq = 1

Window length:

    1

Replacements:

    1 - 1 = 0

0 <= 1

Valid.

ans = 1


right = 1
---------
Character = A

Window:

    "AA"

A = 2

maxFreq = 2

Window length = 2

Replacements:

    2 - 2 = 0

Valid.

ans = 2


right = 2
---------
Character = B

Window:

    "AAB"

A = 2
B = 1

maxFreq = 2

Window length = 3

Replacements:

    3 - 2 = 1

1 <= k

Valid.

ans = 3


right = 3
---------
Character = A

Window:

    "AABA"

A = 3
B = 1

maxFreq = 3

Window length = 4

Replacements:

    4 - 3 = 1

Valid.

ans = 4


right = 4
---------
Character = B

Window:

    "AABAB"

A = 3
B = 2

maxFreq = 3

Window length = 5

Replacements:

    5 - 3 = 2

2 > k

Invalid.

Shrink from left.

Remove first A.

Window:

    "ABAB"

A = 2
B = 2

left = 1

Still using maxFreq = 3.

Check:

    4 - 3 = 1

Now considered valid.

ans remains 4.


right = 5
---------
Character = B

Window:

    "ABABB"

A = 2
B = 3

maxFreq = 3

Window length = 5

Replacements:

    5 - 3 = 2

Invalid.

Remove s[left] = A.

Window:

    "BABB"

left = 2

Actual frequencies:

    A = 1
    B = 3

maxFreq = 3

Window length = 4

Replacements:

    4 - 3 = 1

Valid.

ans = 4


right = 6
---------
Character = A

Window:

    "BABBA"

B = 3
A = 2

maxFreq = 3

Window length = 5

Replacements:

    5 - 3 = 2

Invalid.

Remove B.

Window:

    "ABBA"

B = 2
A = 2

left = 3

Using maxFreq = 3:

    4 - 3 = 1

Window accepted.

ans = 4


Final Answer:

    4


================================================================================
WHY DOES length - maxFreq GIVE THE NUMBER OF REPLACEMENTS?
================================================================================

Consider:

    "AABAB"

Frequency:

    A = 3
    B = 2

The best character to keep is A.

Keep:

    A A A

Characters that must change:

    B B

Therefore:

    replacements = 5 - 3
                 = 2


In general:

    replacements =
        total characters - most frequent character count


If:

    replacements <= k

the window can be converted into a string containing one repeated
character using at most k replacements.


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Sliding Window + Frequency Array


Key Observation:
----------------
For a window to become all the same character:

    replacements = windowLength - maxFrequency

The window is valid when:

    windowLength - maxFrequency <= k


Common Mistakes:
----------------

1. Using:

       maxFrequency - windowLength

   instead of:

       windowLength - maxFrequency


2. Forgetting that maxFreq means the frequency of the MOST COMMON
   character in the current window.

3. Recalculating maxFreq from scratch every time.

   Maintain:

       maxFreq = max(maxFreq, currentFrequency)


4. Resetting maxFreq while shrinking.

   It is okay to keep the historical maximum.

5. Using a set.

   A set cannot tell us how many times each character occurs.


6. Shrinking with:

       if

   instead of:

       while

   The window may require multiple removals before becoming valid.


7. Confusing this problem with "longest substring with at most k
   distinct characters".

   Here we care about:

       characters that need replacement

   not the number of distinct characters.


When to Use This Approach:
--------------------------
Use this pattern when:

- You need the longest substring.
- You can modify at most k characters.
- The goal is to make all characters in a window equal.
- A frequency count determines how many modifications are needed.
- The condition can be expressed as:

      window size - maximum frequency <= k


General Pattern:
----------------

    expand right
          |
          v
    update frequency
          |
          v
    update max frequency
          |
          v
    is window invalid?
       /          \
     yes           no
      |             |
   shrink left      |
      |             |
      +------<------+
                    |
                    v
              update answer


Quick Revision:
---------------

Problem:
    Longest substring after at most k replacements.

Pattern:
    Sliding Window

Data Structure:
    Frequency Array [26]

Formula:

    replacements =
        windowLength - maxFreq

Valid:

    replacements <= k

Invalid:

    replacements > k

Action:
    Move left pointer.

Complexity:

    Time  = O(n)
    Space = O(1)


================================================================================
*/

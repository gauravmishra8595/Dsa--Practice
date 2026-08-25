#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maximumLengthSubstring(string s)
    {
        vector<int> freq(26, 0);
        int left = 0, ans = 0;

        for (int right = 0; right < s.size(); right++)
        {
            freq[s[right] - 'a']++;

            while (freq[s[right] - 'a'] > 2)
            {
                freq[s[left] - 'a']--;
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
    cin >> s;

    cout << sol.maximumLengthSubstring(s) << '\n';

    return 0;
}

/*
============================================================
                 LEETCODE 3090
       Maximum Length Substring With Two Occurrences
============================================================

Problem Statement:
------------------
Given a string s, find the maximum length of a substring such
that each character appears at most twice in the substring.

Return the maximum possible length.

Example:
--------
Input:
s = "bcbbbcba"

Output:
4

Explanation:
The substring "bcbb" has:
b -> 2 occurrences
c -> 1 occurrence

Therefore, its length is 4, and no valid substring is longer.

------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Generate every possible substring and maintain the frequency
of every character. If every character appears at most twice,
update the answer.

Pseudo Code:
------------
for left = 0 to n-1:
    create frequency array
    for right = left to n-1:
        increase frequency[s[right]]
        if frequency[s[right]] > 2:
            break
        update answer

Complete Brute Force Code:
---------------------------

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        int ans = 0;

        for (int left = 0; left < n; left++) {
            vector<int> freq(26, 0);

            for (int right = left; right < n; right++) {
                freq[s[right] - 'a']++;

                if (freq[s[right] - 'a'] > 2)
                    break;

                ans = max(ans, right - left + 1);
            }
        }

        return ans;
    }
};

Time Complexity:
----------------
O(n^2)

Space Complexity:
-----------------
O(26) = O(1)


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
We need the longest substring where no character occurs more
than 2 times.

If a character occurs 3 times inside our current substring,
that substring becomes invalid.

We can maintain a valid window using two pointers.

Intuition:
----------
Use the Sliding Window / Two Pointer technique.

Maintain:
    left  -> start of current window
    right -> end of current window

For every new character:
    1. Add it to the frequency array.
    2. If its frequency becomes greater than 2, move left
       forward until the window becomes valid again.
    3. Update the maximum window length.

The important point is that left never moves backward,
so both pointers together traverse the string only once.

Pseudo Code:
------------
create freq[26] initialized to 0
left = 0
ans = 0

for right = 0 to n-1:
    freq[s[right]]++

    while freq[s[right]] > 2:
        freq[s[left]]--
        left++

    ans = max(ans, right - left + 1)

return ans

Complete Optimal Code:
----------------------

class Solution {
public:
    int maximumLengthSubstring(string s) {
        vector<int> freq(26, 0);
        int left = 0, ans = 0;

        for (int right = 0; right < s.size(); right++) {
            freq[s[right] - 'a']++;

            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};

Time Complexity:
----------------
O(n)

Each character is added to the window once and removed
from the window at most once.

Space Complexity:
-----------------
O(26) = O(1)


------------------------------------------------------------
Dry Run with Example
------------------------------------------------------------

s = "bcbbbcba"

Start:
left = 0
ans = 0

right = 0 -> 'b'
freq: b = 1
window = "b"
ans = 1

right = 1 -> 'c'
freq: b = 1, c = 1
window = "bc"
ans = 2

right = 2 -> 'b'
freq: b = 2, c = 1
window = "bcb"
ans = 3

right = 3 -> 'b'
freq: b = 3
Invalid window.

Move left:
remove s[0] = 'b'
freq: b = 2

window = "cbb"
ans = 3

right = 4 -> 'b'
freq: b = 3
Invalid.

Move left:
remove s[1] = 'c'
freq: c = 0
b = 3

Still invalid.

Move left:
remove s[2] = 'b'
freq: b = 2

window = "bb"
ans = 3

right = 5 -> 'c'
window = "bbc"
ans = 3

right = 6 -> 'b'
window = "bbcb"
b = 3 -> invalid

Move left until b <= 2.

Valid window becomes "bcb"
ans = 3

right = 7 -> 'a'
window = "bcba"
All characters occur at most twice.

Length = 4

Final Answer:
4


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
Sliding Window / Two Pointers

Key Observation:
----------------
The substring is valid if every character appears at most
twice.

When adding s[right] makes its frequency 3, the current
window is invalid. Move left until the frequency becomes 2.

Common Mistakes:
----------------
1. Checking only adjacent characters.
2. Using s[i + 1] when i == n - 1.
3. Forgetting to decrease the frequency while moving left.
4. Using O(n^2) unnecessarily.
5. Returning a vector when the function requires an int.
6. Forgetting that the condition applies to EVERY character,
   not just consecutive equal characters.

When to Use This Approach:
--------------------------
Use Sliding Window when:
- We need a longest/shortest substring.
- The substring must satisfy a frequency/count condition.
- Adding an element can make the window invalid.
- We can restore validity by moving the left pointer.

General Template:
-----------------
for (right = 0; right < n; right++) {
    add s[right];

    while (window is invalid) {
        remove s[left];
        left++;
    }

    update answer;
}

============================================================
*/
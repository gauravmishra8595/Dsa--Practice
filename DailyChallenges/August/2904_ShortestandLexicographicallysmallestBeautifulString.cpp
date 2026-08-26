#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0, ones = 0;
        string ans = "";

        for (int right = 0; right < n; right++) {
            if (s[right] == '1') {
                ones++;
            }

            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }

            if (ones == k) {
                while (left < right && s[left] == '0') {
                    left++;
                }

                string curr = s.substr(left, right - left + 1);

                if (ans.empty() ||
                    curr.size() < ans.size() ||
                    (curr.size() == ans.size() && curr < ans)) {
                    ans = curr;
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    string s = "100011001";
    int k = 3;

    cout << sol.shortestBeautifulSubstring(s, k) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 2904 - SHORTEST BEAUTIFUL SUBSTRING
================================================================================

Problem Statement:
------------------
Given a binary string s and an integer k, find the shortest substring of s
that contains exactly k occurrences of '1'.

If multiple substrings have the same minimum length, return the
lexicographically smallest one.

If no such substring exists, return "".


Example:
--------
Input:
s = "100011001"
k = 3

Output:
"111"


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Try every possible substring.

For every substring:
1. Count the number of '1's.
2. If it contains exactly k ones, consider it as a candidate.
3. Keep the shortest candidate.
4. If lengths are equal, keep the lexicographically smaller candidate.


Pseudo Code:
-----------
for len = k to n:
    result = ""

    for start = 0 to n - len:
        temp = s.substr(start, len)

        count ones in temp

        if ones == k:
            if result is empty OR temp < result:
                result = temp

    if result is not empty:
        return result

return ""


Complete Brute Force Code:
--------------------------

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();

        for (int len = k; len <= n; len++) {
            string result = "";

            for (int start = 0; start <= n - len; start++) {
                string temp = s.substr(start, len);

                int ones = 0;

                for (char ch : temp) {
                    if (ch == '1') {
                        ones++;
                    }
                }

                if (ones == k) {
                    if (result.empty() || temp < result) {
                        result = temp;
                    }
                }
            }

            if (!result.empty()) {
                return result;
            }
        }

        return "";
    }
};


Time Complexity:
----------------
O(n^3)

Space Complexity:
-----------------
O(n)


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
We need a substring containing exactly k ones.

Instead of counting ones again for every substring, maintain the count
using a sliding window.

When the window has more than k ones, move the left pointer forward.

When the window has exactly k ones, remove unnecessary leading zeros.
This gives the shortest valid substring for the current right endpoint.


Intuition:
----------
Maintain a window [left ... right].

Example:

    0 0 1 1 0 0 1
    ^             ^
  left           right

If the window contains exactly k ones, leading zeros do not contribute
to the number of ones.

Therefore, remove them:

    0 0 1 1 0 0 1
      -> 1 1 0 0 1


Then compare the resulting substring with the current answer.

Comparison rules:
1. Smaller length is better.
2. If lengths are equal, lexicographically smaller is better.


Pseudo Code:
-----------
left = 0
ones = 0
answer = ""

for right = 0 to n - 1:

    if s[right] == '1':
        ones++

    while ones > k:
        if s[left] == '1':
            ones--
        left++

    if ones == k:

        while left < right AND s[left] == '0':
            left++

        current = s.substr(left, right - left + 1)

        if current is better than answer:
            answer = current

return answer


Complete Optimal LeetCode Code:
--------------------------------

class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0, ones = 0;
        string ans = "";

        for (int right = 0; right < n; right++) {
            if (s[right] == '1') {
                ones++;
            }

            while (ones > k) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }

            if (ones == k) {
                while (left < right && s[left] == '0') {
                    left++;
                }

                string curr = s.substr(left, right - left + 1);

                if (ans.empty() ||
                    curr.size() < ans.size() ||
                    (curr.size() == ans.size() && curr < ans)) {
                    ans = curr;
                }
            }
        }

        return ans;
    }
};


Time Complexity:
----------------
The sliding-window traversal is O(n).

However, this implementation creates and compares strings using substr(),
so the strict complexity of the implementation can be O(n^2).

Sliding-window logic: O(n)
Overall implementation: O(n^2)


Space Complexity:
-----------------
O(n)


================================================================================
DRY RUN
================================================================================

Example:
--------
s = "100011001"
k = 3


Start:
left = 0
ones = 0
ans = ""


right = 0
s[right] = '1'

ones = 1


right = 1
s[right] = '0'

ones = 1


right = 2
s[right] = '0'

ones = 1


right = 3
s[right] = '0'

ones = 1


right = 4
s[right] = '1'

ones = 2


right = 5
s[right] = '1'

ones = 3

Now ones == k.

Window:
"100011"

Remove leading zeros:

"111"

Candidate = "111"

ans = "111"


Continue moving right.

Whenever ones becomes greater than 3,
move left until ones becomes 3 again.

For every window containing exactly 3 ones:
1. Remove leading zeros.
2. Compare its length with ans.
3. If lengths are equal, compare lexicographically.

Finally:

ans = "111"


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Sliding Window / Two Pointers


Key Observation:
----------------
Only the number of '1's matters.

When there are exactly k ones, leading zeros can be removed because they
do not help satisfy the condition.

This gives the shortest valid substring for that right endpoint.


Common Mistakes:
----------------
1. Checking for at least k ones instead of exactly k ones.

2. Forgetting to remove leading zeros.

3. Forgetting the lexicographical tie-breaker.

4. Not moving left when ones > k.

5. Forgetting the case where no valid substring exists.

6. Confusing s.size() with s.length().

   Both are correct for C++ string:

       s.size()
       s.length()


When to Use This Approach:
--------------------------
Use sliding window when:
- The problem asks about a contiguous substring/subarray.
- A condition depends on counts/frequencies/sum.
- The window can be adjusted by moving left and right pointers.

Common examples:
- Longest substring with at most K distinct characters.
- Minimum window substring.
- Subarray with a given sum.
- Binary substring with exactly K ones.
- Longest substring with at most K zeros.


================================================================================
*/

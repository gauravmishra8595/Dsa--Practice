#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    vector<string> result;

    bool isValid(string &s, int start, int len)
    {
        if (len <= 0 || len > 3 || start + len > s.size())
            return false;

        // Leading zero is not allowed for multi-digit numbers
        if (len > 1 && s[start] == '0')
            return false;

        int num = stoi(s.substr(start, len));

        return num >= 0 && num <= 255;
    }

    void solve(string &s, int start, int parts, string &temp)
    {
        if (parts == 4)
        {
            if (start == s.size())
            {
                result.push_back(temp);
            }
            return;
        }

        // We need at least one character for every remaining part
        int remainingParts = 4 - parts;

        for (int len = 1; len <= 3; len++)
        {
            if (start + len > s.size())
                break;

            // After taking len characters, enough characters must remain
            // for the remaining parts.
            int remainingChars = s.size() - (start + len);

            if (remainingChars < remainingParts - 1 ||
                remainingChars > 3 * (remainingParts - 1))
                continue;

            if (!isValid(s, start, len))
                continue;

            string part = s.substr(start, len);

            int oldSize = temp.size();

            if (!temp.empty())
                temp += ".";

            temp += part;

            solve(s, start + len, parts + 1, temp);

            temp.resize(oldSize);
        }
    }

    vector<string> restoreIpAddresses(string s)
    {
        result.clear();

        if (s.size() < 4 || s.size() > 12)
            return result;

        string temp;
        solve(s, 0, 0, temp);

        return result;
    }
};

int main()
{
    string s = "25525511135";

    Solution sol;

    vector<string> ans = sol.restoreIpAddresses(s);

    for (string &ip : ans)
    {
        cout << ip << '\n';
    }

    return 0;
}

/*
================================================================================
                 LEETCODE 93 - RESTORE IP ADDRESSES
================================================================================

Problem Statement:
------------------
A valid IP address consists of exactly four integers separated by dots.

Each integer must:

    - Be between 0 and 255.
    - Not contain leading zeros.

Given a string containing only digits, return all possible valid IP addresses
that can be formed by inserting exactly three dots.

Example:
--------
Input:
    s = "25525511135"

Output:
    ["255.255.11.135", "255.255.111.35"]

Another Example:

Input:
    s = "101023"

Output:
    ["1.0.10.23", "1.0.102.3", "10.1.0.23",
     "10.10.2.3", "101.0.2.3"]


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
An IP address needs exactly 3 dots.

So we can try every possible position for:

    Dot 1
    Dot 2
    Dot 3

There are O(n^3) possible ways to place the three dots.

For every possibility:

    1. Split the string into four parts.
    2. Check whether all four parts are valid.
    3. If valid, add the IP address to the answer.


Pseudo Code:
------------
1. Try position of first dot.
2. Try position of second dot.
3. Try position of third dot.
4. Extract the four parts.
5. Check each part:
       - Length <= 3
       - Value <= 255
       - No leading zero
6. If all are valid, store the IP.


Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<string> result;

    bool valid(string part) {
        if (part.empty() || part.size() > 3)
            return false;

        if (part.size() > 1 && part[0] == '0')
            return false;

        int num = stoi(part);

        return num >= 0 && num <= 255;
    }

    vector<string> restoreIpAddresses(string s) {
        result.clear();

        int n = s.size();

        for (int i = 1; i <= 3; i++) {
            for (int j = i + 1; j <= i + 3; j++) {
                for (int k = j + 1; k <= j + 3; k++) {

                    if (k >= n)
                        continue;

                    string a = s.substr(0, i);
                    string b = s.substr(i, j - i);
                    string c = s.substr(j, k - j);
                    string d = s.substr(k);

                    if (valid(a) &&
                        valid(b) &&
                        valid(c) &&
                        valid(d)) {

                        result.push_back(
                            a + "." + b + "." + c + "." + d
                        );
                    }
                }
            }
        }

        return result;
    }
};


Time Complexity:
----------------
O(n^3 * n)

There are O(n^3) ways to place 3 dots.

Checking/building an IP can take O(n).

Since n <= 12 for this problem, this is effectively constant time.


Space Complexity:
-----------------
O(n)

Ignoring the output space.

The temporary strings require O(n) space.


================================================================================
OPTIMAL APPROACH - BACKTRACKING
================================================================================

Observation:
------------
An IP address always contains exactly 4 parts.

Each part can contain at most 3 digits because:

    100 <= valid 3-digit number <= 255

So for every part, we only need to try:

    Length 1
    Length 2
    Length 3


Intuition:
----------
At every position, choose the next IP part.

For example:

    "25525511135"

At the beginning we can choose:

    "2"
    "25"
    "255"

For each choice, recursively construct the next part.

Before accepting a part, check:

    1. Length <= 3
    2. No leading zero
    3. Value <= 255


When 4 parts have been created:

    If all characters are used:
        Store the IP address.

    Otherwise:
        This path is invalid.


Pseudo Code:
------------
solve(start, parts, temp):

    If parts == 4:
        If start == n:
            store temp
        return

    For length = 1 to 3:

        If not enough characters:
            break

        If current part is invalid:
            continue

        Add current part to temp

        solve(next position, parts + 1, temp)

        Remove current part from temp


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<string> result;

    bool isValid(string& s, int start, int len) {
        if (len <= 0 || len > 3 || start + len > s.size())
            return false;

        if (len > 1 && s[start] == '0')
            return false;

        int num = stoi(s.substr(start, len));

        return num >= 0 && num <= 255;
    }

    void solve(string& s, int start, int parts, string& temp) {
        if (parts == 4) {
            if (start == s.size()) {
                result.push_back(temp);
            }
            return;
        }

        int remainingParts = 4 - parts;

        for (int len = 1; len <= 3; len++) {
            if (start + len > s.size())
                break;

            int remainingChars = s.size() - (start + len);

            if (remainingChars < remainingParts - 1 ||
                remainingChars > 3 * (remainingParts - 1))
                continue;

            if (!isValid(s, start, len))
                continue;

            string part = s.substr(start, len);

            int oldSize = temp.size();

            if (!temp.empty())
                temp += ".";

            temp += part;

            solve(s, start + len, parts + 1, temp);

            temp.resize(oldSize);
        }
    }

    vector<string> restoreIpAddresses(string s) {
        result.clear();

        if (s.size() < 4 || s.size() > 12)
            return result;

        string temp;

        solve(s, 0, 0, temp);

        return result;
    }
};


Time Complexity:
----------------
O(3^4)

At most 3 choices are made for each of the 4 IP parts.

Since the number of parts is fixed at 4:

    3^4 = 81

So for this problem, the number of states is effectively constant.

Considering the cost of creating/storing strings:

    O(3^4 * n)


Space Complexity:
-----------------
O(n)

Recursion depth is at most 4.

The temporary IP string requires O(n) space.

Ignoring output space.


================================================================================
DRY RUN
================================================================================

Example:

    s = "25525511135"


Start:

    start = 0
    parts = 0
    temp = ""


Choose first part:

    "2"
    "25"
    "255"


Take:

    "255"

Now:

    temp = "255"
    start = 3
    parts = 1


Next choices:

    "2"
    "25"
    "255"


Take:

    "255"

Now:

    temp = "255.255"
    start = 6
    parts = 2


Remaining:

    "11135"


Possible choices:

    "1"
    "11"
    "111"


Take:

    "11"

Now:

    temp = "255.255.11"
    start = 8
    parts = 3


Remaining:

    "135"

Take:

    "135"

Now:

    temp = "255.255.11.135"
    start = 11
    parts = 4


Since:

    start == s.size()

Store:

    "255.255.11.135"


Backtrack.

Try:

    "111"

Then remaining:

    "35"

Possible fourth part:

    "35"

So:

    "255.255.111.35"

Store it.


Final Result:

    255.255.11.135
    255.255.111.35


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Backtracking + String Partitioning


Key Observation:
----------------
An IP address has exactly 4 parts.

Each part can have at most 3 digits.

Therefore, at every recursive step:

    Try length 1
    Try length 2
    Try length 3

Then validate the selected part.


Common Mistakes:
----------------
1. Allowing leading zeros.

   Invalid:

       "01"
       "001"

   Valid:

       "0"
       "10"
       "100"


2. Allowing numbers greater than 255.

   Invalid:

       "256"
       "999"


3. Forgetting that exactly 4 parts are required.

4. When parts == 4, forgetting to check:

       start == s.size()

   Otherwise, we may accept an IP before consuming the entire string.

5. Forgetting to backtrack the temporary string.

6. Trying to create parts longer than 3 characters.

7. Forgetting to clear result in restoreIpAddresses() if the Solution
   object is reused.


When to Use This Approach:
--------------------------
Use this pattern when:

    - You need to split a string into a fixed number of parts.
    - Each part has its own validity condition.
    - You need all valid partitions.
    - You can make a small number of choices at every position.

Common examples:

    - Restore IP Addresses
    - Palindrome Partitioning
    - Combination Sum
    - Generate Parentheses
    - Word Break variations


Important Backtracking Pattern:
-------------------------------

void solve(start, parts, temp) {

    if (base condition) {
        // Store answer
        return;
    }

    for (each possible choice) {

        if (choice is invalid)
            continue;

        // Choose
        add choice;

        // Explore
        solve(next);

        // Undo
        remove choice;
    }
}


Why This Is Better Than Brute Force:
------------------------------------
Instead of blindly trying all positions of 3 dots, we build only valid
IP parts.

Invalid choices are rejected immediately:

    - More than 3 digits
    - Leading zero
    - Value > 255

This is the standard backtracking/pruning pattern.


Complexity:
-----------

Time  = O(3^4 * n)   ≈ O(n) for this fixed problem
Space = O(n)         auxiliary space

The output space is not included.

================================================================================
*/

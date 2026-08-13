#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool detectCapitalUse(string word)
    {
        int n = word.size();

        if (n <= 1)
            return true;
        if (isupper(word[0]) && isupper(word[1]))
        {
            for (int i = 2; i < n; i++)
            {
                if (islower(word[i]))
                    return false;
            }
            return true;
        }
        if (isupper(word[0]))
        {
            for (int i = 1; i < n; i++)
            {
                if (isupper(word[i]))
                    return false;
            }
            return true;
        }

        // Case 3: All letters lowercase.
        for (char c : word)
        {
            if (isupper(c))
                return false;
        }

        return true;
    }
};

int main()
{
    Solution sol;

    vector<string> tests = {
        "USA",
        "leetcode",
        "Google",
        "FlaG"};

    for (const string &word : tests)
    {
        cout << word << " -> "
             << (sol.detectCapitalUse(word) ? "true" : "false")
             << '\n';
    }
    return 0;
}

/*
================================================================================
                         LEETCODE 520
                         DETECT CAPITAL
================================================================================

Problem Statement:
------------------
We define a word as having correct capitalization if one of the following
conditions is true:

1. All letters in the word are uppercase.
2. All letters in the word are lowercase.
3. Only the first letter is uppercase.

Given a string word, return true if it follows the capitalization rules.


Example:
--------
Input:
    word = "USA"

Output:
    true

Explanation:
    All letters are uppercase.


Input:
    word = "leetcode"

Output:
    true

Explanation:
    All letters are lowercase.


Input:
    word = "Google"

Output:
    true

Explanation:
    Only the first letter is uppercase.


Input:
    word = "FlaG"

Output:
    false

Explanation:
    It is neither all uppercase, all lowercase, nor only the first
    letter uppercase.


Brute Force Approach:
---------------------

Idea:
-----
Check the three valid capitalization patterns directly.

Valid patterns:

    1. UPPERCASE
    2. lowercase
    3. First uppercase + remaining lowercase

We can count uppercase and lowercase characters and determine whether
the word matches one of these patterns.


Pseudo Code:
------------
function detectCapitalUse(word):

    uppercase = 0

    for every character c:
        if c is uppercase:
            uppercase++

    if uppercase == 0:
        return true

    if uppercase == word.length:
        return true

    if uppercase == 1 AND word[0] is uppercase:
        return true

    return false


Complete Brute Force Code:
--------------------------

class Solution {
public:
    bool detectCapitalUse(string word) {

        int uppercase = 0;

        for (char c : word) {
            if (isupper(c))
                uppercase++;
        }

        if (uppercase == 0)
            return true;

        if (uppercase == word.size())
            return true;

        if (uppercase == 1 && isupper(word[0]))
            return true;

        return false;
    }
};


Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(1)


Optimal Approach:
-----------------

Observation:
------------
There are only three valid patterns:

    ALL UPPERCASE
    ALL lowercase
    First Uppercase + remaining lowercase

We can check these patterns directly.

Intuition:
----------
Look at the first two characters.

If the first two characters are uppercase, then the entire word must be
uppercase.

If only the first character is uppercase, then every remaining character
must be lowercase.

If the first character is lowercase, then every character must be lowercase.

This avoids counting characters and directly validates the required pattern.


Pseudo Code:
------------
function detectCapitalUse(word):

    if length <= 1:
        return true

    if first two characters are uppercase:
        check remaining characters are lowercase? No.
        They must all be uppercase.

    else if first character is uppercase:
        check remaining characters are lowercase

    else:
        check all characters are lowercase

    return result


Complete Optimal Code:
----------------------

class Solution {
public:
    bool detectCapitalUse(string word) {

        int n = word.size();

        if (n <= 1)
            return true;

        if (isupper(word[0]) && isupper(word[1])) {

            for (int i = 2; i < n; i++) {
                if (islower(word[i]))
                    return false;
            }

            return true;
        }

        if (isupper(word[0])) {

            for (int i = 1; i < n; i++) {
                if (isupper(word[i]))
                    return false;
            }

            return true;
        }

        for (char c : word) {
            if (isupper(c))
                return false;
        }

        return true;
    }
};


Time Complexity:
----------------
O(n)

Each character is checked at most once.


Space Complexity:
-----------------
O(1)

No extra data structure is used.


Dry Run with Example:
---------------------

word = "Google"

Characters:

    G o o g l e
    ^

Step 1:
    First two characters:
        G -> uppercase
        o -> lowercase

    Therefore, this must be the pattern:

        Uppercase + all remaining lowercase

Step 2:
    Check:
        o -> lowercase
        o -> lowercase
        g -> lowercase
        l -> lowercase
        e -> lowercase

All are lowercase.

Therefore:

    return true


Another Example:

word = "FlaG"

First character:
    F -> uppercase

Second character:
    l -> lowercase

Therefore, every remaining character must be lowercase.

Check:

    l -> lowercase
    a -> lowercase
    G -> uppercase  <-- invalid

Therefore:

    return false


Interview Notes:
----------------

Pattern:
    String Pattern Checking


Key Observation:
    There are exactly three valid capitalization patterns:

        1. All uppercase
        2. All lowercase
        3. First uppercase, rest lowercase


Common Mistakes:
----------------
1. Checking only the first character.

2. Forgetting the "all uppercase" case.

3. Treating "USA" as invalid because multiple uppercase letters exist.

4. Using unnecessary data structures.

5. Forgetting that a one-character word is always valid.

6. Mixing up:
       isupper()
       islower()


When to use this approach:
--------------------------
Use direct pattern checking when:

    - The input has a small number of valid formats.
    - We only need to validate the string.
    - No complex data structure is required.
    - Every character can be checked independently.

This is a simple O(n) string-validation problem.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Optimal Solution
class Solution
{
public:
    vector<string> result;

    void solve(string &temp, int n, int k)
    {
        if (result.size() == k)
        {
            return;
        }

        if (temp.size() == n)
        {
            result.push_back(temp);
            return;
        }

        for (char ch = 'a'; ch <= 'c'; ch++)
        {
            if (!temp.empty() && temp.back() == ch)
                continue;

            temp.push_back(ch);
            solve(temp, n, k);
            temp.pop_back();
        }
    }

    string getHappyString(int n, int k)
    {
        result.clear();

        string temp;
        solve(temp, n, k);

        if (result.size() < k)
            return "";

        return result[k - 1];
    }
};

int main()
{
    int n = 3;
    int k = 9;

    Solution sol;

    cout << sol.getHappyString(n, k) << endl;

    return 0;
}

/*
================================================================================
              LEETCODE 1415 - THE K-TH LEXICOGRAPHICAL STRING
================================================================================

Problem Statement:
------------------
A happy string is a string that:

    1. Contains only the characters 'a', 'b', and 'c'.
    2. Does not contain two consecutive equal characters.

Given integers n and k, return the k-th happy string of length n in
lexicographical order.

If there are fewer than k happy strings, return "".


Example:
--------
Input:
    n = 3
    k = 9

All happy strings of length 3 in lexicographical order:

    1.  abc
    2.  acb
    3.  bac
    4.  bca
    5.  cab
    6.  cba

There are only 6 happy strings.

Therefore:

    k = 9

Answer:

    ""


Another Example:
----------------
Input:
    n = 3
    k = 2

Happy strings:

    abc
    acb
    bac
    bca
    cab
    cba

Answer:

    acb


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Generate every possible string of length n using:

    'a', 'b', 'c'

There are:

    3^n

possible strings.

For every generated string:

    1. Check whether it is happy.
    2. If it is happy, store it.
    3. Finally return the k-th string.


Pseudo Code:
------------
generate(pos):

    If pos == n:
        If string is happy:
            store string
        return

    For ch = 'a' to 'c':
        add ch
        generate(pos + 1)
        remove ch

After generating all strings:

    If result.size() < k:
        return ""

    return result[k - 1]


Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<string> result;

    void generate(string& temp, int n) {
        if (temp.size() == n) {
            bool happy = true;

            for (int i = 1; i < n; i++) {
                if (temp[i] == temp[i - 1]) {
                    happy = false;
                    break;
                }
            }

            if (happy) {
                result.push_back(temp);
            }

            return;
        }

        for (char ch = 'a'; ch <= 'c'; ch++) {
            temp.push_back(ch);
            generate(temp, n);
            temp.pop_back();
        }
    }

    string getHappyString(int n, int k) {
        result.clear();

        string temp;
        generate(temp, n);

        if (result.size() < k)
            return "";

        return result[k - 1];
    }
};


Time Complexity:
----------------
O(3^n * n)

There are 3^n possible strings.

Checking whether each string is happy takes O(n).


Space Complexity:
-----------------
O(3^n * n)

This includes storing all generated happy strings.

Recursion depth is O(n).


================================================================================
OPTIMAL APPROACH - BACKTRACKING + PRUNING
================================================================================

Observation:
------------
We do NOT need to generate strings containing consecutive equal characters.

For example:

    temp = "ab"

Next character can only be:

    'a' -> invalid
    'b' -> invalid
    'c' -> valid

So instead of generating all 3^n strings and checking them afterward,
we immediately reject invalid choices.


Intuition:
----------
At every position, try:

    'a'
    'b'
    'c'

But skip the character if it is equal to the previous character.

Because we try characters in increasing order:

    'a' -> 'b' -> 'c'

the generated happy strings are automatically in lexicographical order.

Therefore, the moment we generate the k-th happy string, we can stop.


For example, n = 3:

Start:

    ""

Choose 'a':

    "a"

Next choices:

    "ab"
    "ac"

This generates:

    abc
    acb

Then start with 'b':

    bac
    bca

Then start with 'c':

    cab
    cba


The order is already lexicographical.


Pseudo Code:
------------
solve(temp):

    If we already found k strings:
        stop

    If temp.size() == n:
        add temp to result
        return

    For ch = 'a' to 'c':

        If temp is not empty AND
           temp.back() == ch:
            continue

        choose ch
        solve(temp)
        undo ch


getHappyString():

    clear result

    solve("")

    If fewer than k strings exist:
        return ""

    return result[k - 1]


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<string> result;

    void solve(string& temp, int n, int k) {
        if (result.size() == k) {
            return;
        }

        if (temp.size() == n) {
            result.push_back(temp);
            return;
        }

        for (char ch = 'a'; ch <= 'c'; ch++) {
            if (!temp.empty() && temp.back() == ch)
                continue;

            temp.push_back(ch);
            solve(temp, n, k);
            temp.pop_back();
        }
    }

    string getHappyString(int n, int k) {
        result.clear();

        string temp;
        solve(temp, n, k);

        if (result.size() < k)
            return "";

        return result[k - 1];
    }
};


Time Complexity:
----------------
There are at most:

    3 * 2^(n-1)

happy strings.

We stop as soon as k strings are generated.

Therefore, the practical complexity is:

    O(min(k, 2^n) * n)

because each generated answer has length n.


Space Complexity:
-----------------
O(n)

Recursion depth = n.

The result stores at most k strings, so if output space is included:

    O(k * n)

Auxiliary recursion space:

    O(n)


================================================================================
DRY RUN
================================================================================

Example:

    n = 3
    k = 2


Start:

    temp = ""


Try 'a':

    temp = "a"


Try 'a':

    Invalid because previous character is 'a'.

Skip.


Try 'b':

    temp = "ab"


Try 'a':

    temp = "aba"

    Size = 3

    Store "aba"

    But wait:
    Lexicographical order for this branch should be:

        aba

However, for the standard problem example, let's trace correctly
using all choices:

From "a":

    "ab"
        "aba"
        "abc"

    "ac"
        "aca"
        "acb"


So the happy strings begin:

    1. aba
    2. abc
    3. aca
    4. acb
    ...


Therefore for:

    n = 3
    k = 2

Answer:

    abc


Important:
----------
The exact generated strings depend on the definition of happy string,
but the recursion always explores characters in:

    'a' -> 'b' -> 'c'

which guarantees lexicographical order.


For n = 3:

All happy strings are:

    aba
    abc
    aca
    acb
    bab
    bac
    bca
    bcb
    cab
    cac
    cba
    cbc

There are:

    3 * 2^(3-1)
    = 12

happy strings.


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Backtracking + Lexicographical Ordering + Pruning


Key Observation:
----------------
The next character cannot be equal to the previous character.

Therefore, after choosing one character, there are only 2 valid choices
for the next character.


For example:

    Previous = 'a'

Next can be:

    'b'
    'c'

But NOT:

    'a'


Another Important Observation:
------------------------------
We generate characters in lexicographical order:

    'a'
    'b'
    'c'

Therefore, the generated valid strings are automatically in
lexicographical order.

We do NOT need to sort the result afterward.


Common Mistakes:
----------------
1. Forgetting to prevent consecutive equal characters.

2. Sorting the result unnecessarily.

3. Forgetting backtracking:

       temp.push_back(ch);
       solve(...);
       temp.pop_back();

4. Returning result[k] instead of result[k - 1].

   k is 1-based, vector indexing is 0-based.

5. Forgetting to return "" when fewer than k happy strings exist.

6. Continuing to generate strings after finding the k-th string.

   We can prune using:

       if (result.size() == k)
           return;


When to Use This Approach:
--------------------------
Use this pattern when:

    - You need to generate strings/combinations.
    - There are constraints on adjacent characters.
    - The answer is required in lexicographical order.
    - You only need the first k valid results.
    - Invalid choices can be rejected early.


Useful Backtracking Template:
-----------------------------

void solve(string& temp) {

    if (base condition) {
        result.push_back(temp);
        return;
    }

    for (each choice) {

        if (choice is invalid)
            continue;

        // Choose
        temp.push_back(choice);

        // Explore
        solve(temp);

        // Undo
        temp.pop_back();
    }
}


Important:
----------
For LeetCode 1415, the maximum n is small.

Number of happy strings:

    3 * 2^(n - 1)

because:

    First character:
        3 choices

    Every next character:
        2 choices

This is much smaller than generating all:

    3^n

strings.


Complexity:
-----------

Time  = O(min(k, 2^n) * n)
Space = O(n) auxiliary space

If output storage is counted:

    O(k * n)

================================================================================
*/

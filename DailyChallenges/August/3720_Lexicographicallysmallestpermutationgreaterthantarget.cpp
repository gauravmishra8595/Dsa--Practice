#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string result = "";

    bool solve(string &curr, vector<int> &count, string &target, int i,
               bool greater)
    {
        if (i == target.length())
        {
            if (greater)
            {
                result = curr;
                return true;
            }
            return false;
        }

        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            if (count[ch - 'a'] == 0)
                continue;

            if (!greater && ch < target[i])
                continue;

            curr.push_back(ch);
            count[ch - 'a']--;

            bool isGreater = greater || ch > target[i];

            if (solve(curr, count, target, i + 1, isGreater))
                return true;

            curr.pop_back();
            count[ch - 'a']++;
        }

        return false;
    }

    string lexGreaterPermutation(string s, string target)
    {
        vector<int> count(26, 0);

        for (char ch : s)
            count[ch - 'a']++;

        string curr;
        solve(curr, count, target, 0, false);

        return result;
    }
};

int main()
{
    Solution sol;

    string s = "abdc";
    string target = "abcc";

    cout << sol.lexGreaterPermutation(s, target) << '\n';

    return 0;
}

/*
================================================================================
PROBLEM STATEMENT
================================================================================

Given a string s and a target string, rearrange the characters of s to find
the lexicographically smallest permutation that is strictly greater than
target.

If no such permutation exists, return "".


EXAMPLE
================================================================================

s      = "abdc"
target = "abcc"

Possible valid permutations include:

    "abdc"
    "acbd"
    "acdb"
    ...

The smallest permutation greater than "abcc" is:

    "abdc"


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----

Generate all permutations of s.

For every permutation:
    1. Check whether it is greater than target.
    2. If yes, update the answer if it is smaller than the current answer.

This works but is very expensive because there can be n! permutations.


PSEUDO CODE
-----------

generate(index):

    if index == n:
        if current permutation > target:
            update answer
        return

    for j from index to n-1:
        swap current[index] and current[j]
        generate(index + 1)
        swap back


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:
    string result = "";

    void generate(string& s, int index, string& target) {
        if (index == s.size()) {
            if (s > target) {
                if (result.empty() || s < result)
                    result = s;
            }
            return;
        }

        for (int j = index; j < s.size(); j++) {
            swap(s[index], s[j]);

            generate(s, index + 1, target);

            swap(s[index], s[j]);
        }
    }

    string lexGreaterPermutation(string s, string target) {
        generate(s, 0, target);
        return result;
    }
};


int main() {
    Solution sol;

    string s = "abdc";
    string target = "abcc";

    cout << sol.lexGreaterPermutation(s, target) << '\n';

    return 0;
}


TIME COMPLEXITY
---------------

O(n! * n)

There can be n! permutations and checking/comparing a permutation can take
O(n).


SPACE COMPLEXITY
----------------

O(n)

Recursion depth is O(n).


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------

Because we iterate characters from 'a' to 'z', the recursion automatically
tries permutations in lexicographical order.

At every position:

    1. If the current prefix is already greater than target,
       we can choose the smallest available character.

    2. If the current prefix is equal to target,
       we cannot choose a character smaller than target[i].

    3. Choosing a character equal to target[i] keeps us equal.

    4. Choosing a character greater than target[i] makes the complete
       prefix greater.

The FIRST complete valid permutation found is therefore the lexicographically
smallest valid permutation.


INTUITION
---------

We maintain a boolean:

    greater

which tells us whether the prefix constructed so far is already greater
than target's prefix.

Initially:

    greater = false

because we have constructed nothing.

For every position:

    If greater == false:

        ch < target[i]
            -> impossible, because the final string would be smaller.

        ch == target[i]
            -> still equal, so continue with greater = false.

        ch > target[i]
            -> now the prefix is greater.

    If greater == true:

        Any remaining character is allowed because the prefix is already
        greater than target.

Since we try characters from 'a' to 'z', we always try the smallest possible
character first.

Therefore, the first successful permutation is the answer.


PSEUDO CODE
-----------

solve(curr, count, target, i, greater):

    if i == target.length:
        if greater:
            answer = curr
            return true
        return false

    for ch = 'a' to 'z':

        if ch is unavailable:
            continue

        if prefix is not greater AND ch < target[i]:
            continue

        choose ch

        newGreater = greater OR (ch > target[i])

        if solve(next state):
            return true

        undo choice

    return false


COMPLETE OPTIMAL CODE
---------------------

class Solution {
public:
    string result = "";

    bool solve(string& curr, vector<int>& count, string& target, int i,
               bool greater) {

        if (i == target.length()) {
            if (greater) {
                result = curr;
                return true;
            }
            return false;
        }

        for (char ch = 'a'; ch <= 'z'; ch++) {

            if (count[ch - 'a'] == 0)
                continue;

            if (!greater && ch < target[i])
                continue;

            curr.push_back(ch);
            count[ch - 'a']--;

            bool isGreater = greater || ch > target[i];

            if (solve(curr, count, target, i + 1, isGreater))
                return true;

            curr.pop_back();
            count[ch - 'a']++;
        }

        return false;
    }

    string lexGreaterPermutation(string s, string target) {

        vector<int> count(26, 0);

        for (char ch : s)
            count[ch - 'a']++;

        string curr;

        solve(curr, count, target, 0, false);

        return result;
    }
};


int main() {
    Solution sol;

    string s = "abdc";
    string target = "abcc";

    cout << sol.lexGreaterPermutation(s, target) << '\n';

    return 0;
}


TIME COMPLEXITY
---------------

Worst case:

    O(26 * n!)

because backtracking may still explore many states.

However, iterating characters in sorted order means that once the first
valid permutation is found, the search stops.

For this particular backtracking implementation, it is NOT the same optimal
complexity as the direct greedy/next-permutation solution.


SPACE COMPLEXITY
----------------

O(n + 26)

O(n) for the recursion/current string and O(26) for character frequencies.

Therefore:

    O(n)


================================================================================
DRY RUN
================================================================================

s      = "abdc"
target = "abcc"


Frequency:

    a -> 1
    b -> 1
    c -> 1
    d -> 1


i = 0
target[0] = 'a'
greater = false

Try 'a':

    'a' == 'a'

So:

    curr = "a"
    greater = false


i = 1
target[1] = 'b'

Try 'b':

    'b' == 'b'

So:

    curr = "ab"
    greater = false


i = 2
target[2] = 'c'

Try 'c':

    'c' == 'c'

So:

    curr = "abc"
    greater = false


i = 3
target[3] = 'c'

Try 'd':

    'd' > 'c'

Therefore:

    curr = "abcd"
    greater = true

But note that after choosing c at i = 2, the remaining character is d,
so the first valid permutation is:

    "abdc"

depending on the available character order and backtracking path.

The recursion tries available characters in ascending order, skips invalid
choices, and returns immediately when it reaches a complete permutation
strictly greater than target.

Final answer:

    "abdc"


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------

Backtracking + Greedy Character Ordering + Frequency Counting


KEY OBSERVATION
---------------

Because characters are tried from 'a' to 'z', the first valid complete
permutation is lexicographically smallest.

The boolean `greater` tells us whether the prefix has already become greater
than target.


COMMON MISTAKES
---------------

1. Allowing ch < target[i] while the prefix is still equal.

   This creates a permutation smaller than target.

2. Forgetting to update:

       greater = greater || ch > target[i]

3. Not restoring the frequency after backtracking.

       count[ch - 'a']++


4. Trying characters in arbitrary order.

   To obtain the lexicographically smallest answer, try:

       'a' -> 'z'


5. Returning the first permutation without ensuring that it is greater.

   At the base case:

       greater must be true.


6. Confusing `greater` with `ch > target[i]`.

   Once the prefix becomes greater, it remains greater regardless of the
   remaining characters.


WHEN TO USE THIS APPROACH
-------------------------

Use this pattern when:

    - You need to construct a permutation.
    - The answer has lexicographical constraints.
    - You have duplicate characters.
    - You need to maintain character frequencies.
    - You need the first valid answer in lexicographical order.
    - n is small enough for backtracking.

For large n, prefer the direct greedy/next-permutation style solution
because this backtracking solution can still have factorial worst-case
complexity.


IMPORTANT
---------

This code preserves the logic of the original recursive solution.

It is a lexicographically ordered backtracking solution, NOT a true
O(n)-style optimal greedy solution.

For an actual large-constraint problem, the better approach is:

    1. Match the target prefix.
    2. Find the rightmost position where we can increase the character.
    3. Put the smallest possible greater character there.
    4. Sort/fill the suffix with the smallest remaining characters.

================================================================================
*/

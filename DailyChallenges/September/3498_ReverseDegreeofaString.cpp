#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int reverseDegree(string s) {
        int result = 0;

        for (int i = 0; i < s.size(); i++) {
            int reverseValue = 26 - (s[i] - 'a');
            result += reverseValue * (i + 1);
        }

        return result;
    }
};

int main() {
    Solution sol;

    string s;
    cin >> s;

    cout << sol.reverseDegree(s) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 3498 - REVERSE DEGREE
================================================================================

Problem Statement:
------------------
Given a string s consisting of lowercase English letters, calculate its
reverse degree.

For each character:
    - Its reverse alphabetical value is:
          a -> 26
          b -> 25
          c -> 24
          ...
          z -> 1

The reverse degree is the sum of:

    reverseValue(character) * position

where position is 1-indexed.

Return the reverse degree of the string.


Example:
--------
Input:
    abc

Calculation:
    a -> 26, position = 1  => 26 * 1 = 26
    b -> 25, position = 2  => 25 * 2 = 50
    c -> 24, position = 3  => 24 * 3 = 72

Answer:
    26 + 50 + 72 = 148

Output:
    148


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
For every character, first find its normal alphabetical position:

    a = 1
    b = 2
    ...
    z = 26

Then calculate its reverse value:

    reverseValue = 27 - normalValue

Finally multiply it by its 1-based position and add it to the answer.

This is already linear and is effectively the direct approach to the problem.


Pseudo Code:
------------
function reverseDegree(s):
    result = 0

    for i from 0 to n-1:
        normalValue = s[i] - 'a' + 1
        reverseValue = 27 - normalValue
        result += reverseValue * (i + 1)

    return result


Complete Brute Force Code:
--------------------------

// class Solution {
// public:
//     int reverseDegree(string s) {
//         int result = 0;
//
//         for (int i = 0; i < s.size(); i++) {
//             int normalValue = s[i] - 'a' + 1;
//             int reverseValue = 27 - normalValue;
//
//             result += reverseValue * (i + 1);
//         }
//
//         return result;
//     }
// };


Time Complexity:
----------------
O(n)

Each character is processed once.


Space Complexity:
-----------------
O(1)

Only a few integer variables are used.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
For a lowercase character:

    s[i] - 'a'

gives a zero-based value:

    a -> 0
    b -> 1
    ...
    z -> 25

Therefore, its reverse alphabetical value can be directly calculated as:

    26 - (s[i] - 'a')

So:

    a -> 26
    b -> 25
    ...
    z -> 1


Intuition:
----------
There is no need to create a reverse alphabet string or use a lookup table.

For every character:
    reverseValue = 26 - (s[i] - 'a')

Since the problem uses 1-based positions, multiply by:

    i + 1

and add the result to the answer.


Pseudo Code:
------------
function reverseDegree(s):
    result = 0

    for i from 0 to n-1:
        reverseValue = 26 - (s[i] - 'a')
        result += reverseValue * (i + 1)

    return result


Complete Optimal Code:
----------------------

// class Solution {
// public:
//     int reverseDegree(string s) {
//         int result = 0;
//
//         for (int i = 0; i < s.size(); i++) {
//             int reverseValue = 26 - (s[i] - 'a');
//             result += reverseValue * (i + 1);
//         }
//
//         return result;
//     }
// };


Time Complexity:
----------------
O(n)

Each character is visited exactly once.


Space Complexity:
-----------------
O(1)

No extra data structure is required.


================================================================================
DRY RUN
================================================================================

Example:
    s = "abc"

Initial:
    result = 0

i = 0:
    s[0] = 'a'
    s[0] - 'a' = 0
    reverseValue = 26 - 0 = 26
    position = 0 + 1 = 1
    result += 26 * 1
    result = 26

i = 1:
    s[1] = 'b'
    s[1] - 'a' = 1
    reverseValue = 26 - 1 = 25
    position = 1 + 1 = 2
    result += 25 * 2
    result = 76

i = 2:
    s[2] = 'c'
    s[2] - 'a' = 2
    reverseValue = 26 - 2 = 24
    position = 2 + 1 = 3
    result += 24 * 3
    result = 148

Final Answer:
    148


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
String traversal + character-to-number mapping.


Key Observation:
----------------
For lowercase English letters:

    s[i] - 'a'

gives a value from 0 to 25.

Therefore:

    26 - (s[i] - 'a')

directly gives the reverse alphabetical value from 26 to 1.


Common Mistakes:
----------------
1. Using i instead of i + 1.
   The position is 1-indexed.

2. Using:
       25 - (s[i] - 'a')
   This would make 'a' equal to 25 instead of 26.

3. Forgetting that:
       s[i] - 'a'
   is zero-based.

4. Using unnecessary extra data structures such as a reverse alphabet
   string or map.


When to Use This Approach:
--------------------------
Use this direct character arithmetic whenever a problem maps lowercase
English letters to alphabetical or reverse-alphabetical positions.

General pattern:

    normal value  = character - 'a' + 1
    reverse value = 27 - normal value

or directly:

    reverse value = 26 - (character - 'a')

================================================================================
*/


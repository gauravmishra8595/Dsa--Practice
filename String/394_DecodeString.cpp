#include <bits/stdc++.h>
using namespace std;

// ==================== OPTIMAL SOLUTION ====================

class Solution
{
public:
    string decodeString(string s)
    {
        stack<int> numStack;
        stack<string> strStack;

        string curr = "";
        int num = 0;

        for (char ch : s)
        {

            if (isdigit(ch))
            {
                num = num * 10 + (ch - '0');
            }
            else if (ch == '[')
            {
                numStack.push(num);
                strStack.push(curr);

                num = 0;
                curr = "";
            }
            else if (ch == ']')
            {
                int repeat = numStack.top();
                numStack.pop();

                string prev = strStack.top();
                strStack.pop();

                string temp = "";

                while (repeat--)
                {
                    temp += curr;
                }

                curr = prev + temp;
            }
            else
            {
                curr += ch;
            }
        }

        return curr;
    }
};

int main()
{
    Solution sol;

    string s = "3[a2[c]]";

    cout << sol.decodeString(s) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 394
                        DECODE STRING
================================================================================

PROBLEM STATEMENT
-----------------
Given an encoded string, decode it according to the following rule:

    k[encoded_string]

means:

    encoded_string repeated k times.

The input may contain nested encodings.

For example:

    3[a2[c]]

First decode:

    2[c] = cc

Then:

    a + cc = acc

Finally:

    3[acc] = accaccacc


IMPORTANT:
----------
Numbers can contain multiple digits.

For example:

    100[a]

means:

    a repeated 100 times.


================================================================================
EXAMPLE
================================================================================

Input:

    s = "3[a2[c]]"


Decode:

    2[c] = "cc"

    a + "cc" = "acc"

    3["acc"] = "accaccacc"


Output:

    "accaccacc"


Another example:

    s = "3[a]2[bc]"

Output:

    "aaabcbc"


Another example:

    s = "2[abc]3[cd]ef"

Output:

    "abcabccdcdcdef"


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
A simple recursive approach is to process the string from left to right.

Whenever we encounter:

    number[...]


we recursively decode everything inside the brackets.

Then repeat the decoded substring number times.

This is conceptually simple, but repeated string construction can
cause extra work.


PSEUDO CODE
-----------

    decode():

        result = ""

        while current character is not ']':

            if character is a letter:

                add it to result

            else:

                read number k

                skip '['

                inner = decode()

                skip ']'

                repeat inner k times

                add to result

        return result


COMPLETE BRUTE FORCE CODE
-------------------------

// class Solution {
// public:
//
//     string decodeString(string s) {
//
//         int index = 0;
//
//         return decode(s, index);
//     }
//
// private:
//
//     string decode(string& s, int& index) {
//
//         string result = "";
//
//         while (index < s.size() && s[index] != ']') {
//
//             if (isalpha(s[index])) {
//
//                 result += s[index];
//                 index++;
//
//             } else {
//
//                 int num = 0;
//
//                 while (index < s.size() &&
//                        isdigit(s[index])) {
//
//                     num = num * 10 +
//                           (s[index] - '0');
//
//                     index++;
//                 }
//
//                 index++; // skip '['
//
//                 string inner = decode(s, index);
//
//                 index++; // skip ']'
//
//                 while (num--) {
//                     result += inner;
//                 }
//             }
//         }
//
//         return result;
//     }
// };


TIME COMPLEXITY
----------------
Let:

    L = length of decoded output

In the worst case, constructing the output itself takes:

    O(L)

However, depending on the nesting and repeated intermediate
string construction, extra copying can occur.

For interview/CP purposes:

    O(L + n)

where n is the encoded string length.


SPACE COMPLEXITY
----------------

Recursive call stack:

    O(n)

plus decoded strings:

    O(L)

Therefore:

    O(n + L)


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------

The brackets create a nested structure.

For example:

    3[a2[c]]

When we see:

    3[

we cannot finish the current string until we know what is inside
the brackets.

So we need to temporarily save:

    1. The current number
    2. The string constructed before '['


This naturally leads to using STACKS.


INTUITION
---------

We maintain two stacks:

    numStack
    strStack


numStack:
---------
Stores repetition counts.

Example:

    3[ ... ]

push:

    3


strStack:
---------
Stores the string that existed before the current '['.


Example:

    "abc3[xy]"

When '[' appears:

    save "abc"


Then decode the content.

When ']' appears:

    retrieve the saved string
    repeat the current decoded part
    combine them


================================================================================
STEP-BY-STEP EXAMPLE
================================================================================

Input:

    3[a2[c]]


Initially:

    curr = ""
    num = 0


Read '3':

    num = 3


Read '[':

    numStack = [3]
    strStack = [""]

    curr = ""


Read 'a':

    curr = "a"


Read '2':

    num = 2


Read '[':

    numStack = [3, 2]
    strStack = ["", "a"]

    curr = ""


Read 'c':

    curr = "c"


Read ']'

Top number:

    2

Current string:

    "c"

Repeat:

    "cc"


Previous string:

    "a"

Combine:

    "a" + "cc"

    = "acc"


Now:

    numStack = [3]
    strStack = [""]

    curr = "acc"


Read final ']'

Top number:

    3

Repeat:

    "accaccacc"


Previous string:

    ""


Final:

    "accaccacc"


================================================================================
PSEUDO CODE
================================================================================

    numStack = empty stack
    strStack = empty stack

    curr = ""
    num = 0


    for every character ch:

        if ch is digit:

            num = num * 10 + digit


        else if ch == '[':

            push num into numStack
            push curr into strStack

            num = 0
            curr = ""


        else if ch == ']':

            repeat = top of numStack
            pop numStack

            previous = top of strStack
            pop strStack

            temp = curr repeated repeat times

            curr = previous + temp


        else:

            curr += ch


    return curr


================================================================================
COMPLETE OPTIMAL CODE
================================================================================

// class Solution {
// public:
//
//     string decodeString(string s) {
//
//         stack<int> numStack;
//         stack<string> strStack;
//
//         string curr = "";
//         int num = 0;
//
//         for (char ch : s) {
//
//             if (isdigit(ch)) {
//
//                 num = num * 10 +
//                       (ch - '0');
//
//             }
//             else if (ch == '[') {
//
//                 numStack.push(num);
//                 strStack.push(curr);
//
//                 num = 0;
//                 curr = "";
//             }
//             else if (ch == ']') {
//
//                 int repeat = numStack.top();
//                 numStack.pop();
//
//                 string previous = strStack.top();
//                 strStack.pop();
//
//                 string temp = "";
//
//                 while (repeat--) {
//                     temp += curr;
//                 }
//
//                 curr = previous + temp;
//             }
//             else {
//
//                 curr += ch;
//             }
//         }
//
//         return curr;
//     }
// };


TIME COMPLEXITY
----------------
Let:

    n = encoded string length
    L = length of final decoded string


We must produce the decoded output, so at least:

    O(L)

work is necessary.

Overall:

    O(n + L)

for the decoding process, ignoring implementation-specific
string-copy costs.


SPACE COMPLEXITY
----------------

Two stacks store intermediate information.

Maximum nesting depth:

    O(n)

The decoded result requires:

    O(L)

Therefore:

    O(n + L)


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:

    s = "3[a2[c]]"


----------------------------------------
CHARACTER: '3'
----------------------------------------

    num = 3


----------------------------------------
CHARACTER: '['
----------------------------------------

Push:

    numStack:
        [3]

    strStack:
        [""]

Reset:

    num = 0
    curr = ""


----------------------------------------
CHARACTER: 'a'
----------------------------------------

    curr = "a"


----------------------------------------
CHARACTER: '2'
----------------------------------------

    num = 2


----------------------------------------
CHARACTER: '['
----------------------------------------

Push:

    numStack:
        [3, 2]

    strStack:
        ["", "a"]

Reset:

    num = 0
    curr = ""


----------------------------------------
CHARACTER: 'c'
----------------------------------------

    curr = "c"


----------------------------------------
CHARACTER: ']'
----------------------------------------

repeat = 2

Current:

    "c"

Repeat:

    "cc"

Previous:

    "a"

Combine:

    "a" + "cc"

    curr = "acc"


Stacks:

    numStack:
        [3]

    strStack:
        [""]


----------------------------------------
CHARACTER: ']'
----------------------------------------

repeat = 3

Current:

    "acc"

Repeat:

    "accaccacc"

Previous:

    ""

Final:

    curr = "accaccacc"


ANSWER:

    "accaccacc"


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------

Stack + String Parsing


KEY OBSERVATION
---------------

Whenever we see:

    '['

we need to remember:

    current number
    current string


Whenever we see:

    ']'

we complete the current nested expression.


Therefore:

    '[' -> PUSH

    ']' -> POP


This is the main pattern.


================================================================================
WHY TWO STACKS?
================================================================================

Suppose:

    "abc3[xy]"


Before '[':

    curr = "abc"
    num = 3


We need to remember "abc" while processing "xy".

So:

    strStack.push("abc")
    numStack.push(3)


After ']'

    current = "xy"

Repeat:

    "xyxyxy"

Previous:

    "abc"

Final:

    "abcxyxyxy"


================================================================================
COMMON MISTAKES
================================================================================

1. FORGETTING MULTI-DIGIT NUMBERS

Wrong:

    num = ch - '0'


For:

    100[a]

this only processes one digit.

Correct:

    num = num * 10 + (ch - '0')


2. NOT RESETTING num AFTER '['

After:

    numStack.push(num)

do:

    num = 0


3. NOT RESETTING curr AFTER '['

After saving the previous string:

    strStack.push(curr)

do:

    curr = ""


4. FORGETTING TO RESTORE THE PREVIOUS STRING

At ']':

    previous = strStack.top()

Then:

    curr = previous + repeated


5. CONFUSING '[' AND ']'

Opening bracket:

    Save state.


Closing bracket:

    Restore state and combine.


6. USING ONLY ONE STACK

One stack can be used with pairs/objects, but two stacks make
the solution much cleaner and easier to understand.


7. INTEGER OVERFLOW

For normal LeetCode constraints, int is sufficient for the
encoded repetition number.

If constraints are significantly larger, consider using a
larger integer type.


================================================================================
WHEN TO USE THIS APPROACH
================================================================================

Use a stack when the problem contains:

    - Nested brackets
    - Nested expressions
    - Parentheses
    - Undo operations
    - Nested decoding
    - Expressions that must be processed from inside out


Typical clue:

    "Nested structure"


Think:

    STACK


================================================================================
STACK PATTERN
================================================================================

Opening:

    PUSH STATE


Processing:

    WORK ON CURRENT LEVEL


Closing:

    POP STATE
    COMBINE


General structure:

        '['
         |
         v
      PUSH
         |
         v
     process inner
         |
         v
        ']'
         |
         v
       POP
         |
         v
      COMBINE


================================================================================
IMPORTANT TEMPLATE
================================================================================

When parsing numbers:

    int num = 0;

    num = num * 10 + (ch - '0');


When '[' appears:

    numStack.push(num);
    strStack.push(curr);

    num = 0;
    curr = "";


When ']' appears:

    int repeat = numStack.top();
    numStack.pop();

    string previous = strStack.top();
    strStack.pop();

    string temp = "";

    while (repeat--) {
        temp += curr;
    }

    curr = previous + temp;


FINAL COMPLEXITY
================================================================================

Optimal:

    Time  : O(n + L)
    Space : O(n + L)

where:

    n = encoded string length
    L = decoded string length


================================================================================
CORE IDEA TO REMEMBER
================================================================================

             3[a2[c]]
                 |
                 v
             SEE NUMBER
                 |
                 v
              SEE '['
                 |
                 v
          SAVE CURRENT STATE
                 |
                 v
          DECODE INNER PART
                 |
                 v
              SEE ']'
                 |
                 v
           RESTORE STATE
                 |
                 v
             REPEAT
                 |
                 v
             COMBINE
                 |
                 v
              ANSWER


================================================================================
*/
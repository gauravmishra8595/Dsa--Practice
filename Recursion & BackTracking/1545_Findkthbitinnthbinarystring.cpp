#include <bits/stdc++.h>
using namespace std;

// ==================== OPTIMAL SOLUTION ====================

class Solution
{
public:
    char findKthBit(int n, int k)
    {
     

        if (n == 1)
        {
            return '0';
        }

        int len = (1 << n) - 1;
        int mid = len / 2 + 1;

        if (k == mid)
        {
            return '1';
        }

        if (k < mid)
        {
            return findKthBit(n - 1, k);
        }

        
        int mirroredK = len - k + 1;

        char bit = findKthBit(n - 1, mirroredK);

        // Right half is inverted.
        return bit == '0' ? '1' : '0';
    }
};

int main()
{
    Solution sol;

    int n = 4;
    int k = 11;

    cout << sol.findKthBit(n, k) << '\n';

    return 0;
}

/*
================================================================================
                         LEETCODE 1545
                    FIND K-TH BIT IN N-TH BINARY STRING
================================================================================

PROBLEM STATEMENT
-----------------
We are given a recursively defined sequence of binary strings.

S1 = "0"

For n > 1:

    Sn = S(n-1) + "1" + reverse(invert(S(n-1)))

Where:

    invert:
        0 -> 1
        1 -> 0

    reverse:
        reverses the string


We need to return the k-th bit of Sn.


IMPORTANT:
----------
Length of Sn is:

    2^n - 1


================================================================================
EXAMPLE
================================================================================

n = 4

S1:

    "0"


S2:

    S1 + "1" + reverse(invert(S1))

    "0" + "1" + "1"

    S2 = "011"


S3:

    "011" + "1" + reverse(invert("011"))

    invert("011") = "100"

    reverse("100") = "001"

    S3 = "0111001"


S4:

    "0111001" + "1" + reverse(invert("0111001"))

    S4 = "011100110100011"


For:

    n = 4
    k = 11

S4:

    0 1 1 1 0 0 1 1 0 1 0 0 0 1 1
    -------------------------------
                    ^
                   k=11

Answer:

    '0'


================================================================================
BRUTE FORCE APPROACH
================================================================================

IDEA
----
Actually construct the entire string S(n).

For each n:

    S(n) =
        S(n-1)
        +
        "1"
        +
        reverse(invert(S(n-1)))


Once we construct S(n), simply return:

    S(n)[k-1]


This is easy to understand but unnecessary because the string
can become very large.


PSEUDO CODE
-----------

    s = "0"

    repeat n-1 times:

        temp = invert(s)

        reverse(temp)

        s = s + "1" + temp

    return s[k-1]


COMPLETE BRUTE FORCE CODE
-------------------------

class Solution {
public:

    char findKthBit(int n, int k) {

        string s = "0";

        for (int i = 2; i <= n; i++) {

            string temp = s;

            for (char &c : temp) {

                c = (c == '0') ? '1' : '0';
            }

            reverse(temp.begin(), temp.end());

            s = s + "1" + temp;
        }

        return s[k - 1];
    }
};


TIME COMPLEXITY
----------------

Length of Sn:

    2^n - 1

So constructing the final string takes:

    O(2^n)


SPACE COMPLEXITY
----------------

We store the complete string:

    O(2^n)


================================================================================
OPTIMAL APPROACH
================================================================================

OBSERVATION
-----------

The important structure is:

    Sn = S(n-1) + "1" + reverse(invert(S(n-1)))


The length of Sn is:

    2^n - 1


Therefore, the middle position is:

    2^(n-1)

because:

    ((2^n - 1) / 2) + 1
    = 2^(n-1)


So:

    middle = 2^(n-1)


The middle bit is ALWAYS:

    '1'


Now consider the position k.


There are three cases.


CASE 1: k == middle
-------------------

The answer is directly:

    '1'


CASE 2: k < middle
------------------

k lies in the first half.

The first half is exactly:

    S(n-1)

Therefore:

    answer = findKthBit(n-1, k)


CASE 3: k > middle
-------------------

k lies in:

    reverse(invert(S(n-1)))


Because this part is reversed, position k corresponds to:

    mirroredK = length - k + 1


Then we find the corresponding bit in S(n-1):

    bit = findKthBit(n-1, mirroredK)


But this right half is INVERTED.

Therefore:

    0 -> 1
    1 -> 0


So return the inverted bit.


================================================================================
INTUITION
================================================================================

Imagine:

        S(n-1)     1     reverse(invert(S(n-1)))
       --------    -     ------------------------
       LEFT       MID              RIGHT


If k is in LEFT:

    solve the same problem in S(n-1)


If k is MID:

    answer = 1


If k is in RIGHT:

    mirror k back into S(n-1)

    then invert the answer.


This means we NEVER need to construct the whole string.


================================================================================
WHY MIRRORED POSITION?
================================================================================

Suppose:

    S(n-1) = "011"

Then:

    invert(S(n-1)) = "100"

Then:

    reverse(invert(S(n-1))) = "001"


Positions in the right half:

    right:
        1 2 3
        0 0 1

Corresponding positions in S(n-1):

        3 2 1
        0 1 1


So the mapping is:

    right position 1 -> original position 3
    right position 2 -> original position 2
    right position 3 -> original position 1


This is:

    mirroredK = len - k + 1


================================================================================
PSEUDO CODE
================================================================================

    function findKthBit(n, k):

        if n == 1:
            return '0'

        len = 2^n - 1

        mid = len / 2 + 1

        if k == mid:
            return '1'

        if k < mid:
            return findKthBit(n-1, k)

        mirroredK = len - k + 1

        bit = findKthBit(n-1, mirroredK)

        invert bit

        return bit


================================================================================
COMPLETE OPTIMAL CODE
================================================================================

class Solution {
public:

    char findKthBit(int n, int k) {

        if (n == 1) {
            return '0';
        }

        int len = (1 << n) - 1;

        int mid = len / 2 + 1;

        if (k == mid) {
            return '1';
        }

        if (k < mid) {
            return findKthBit(n - 1, k);
        }

        int mirroredK = len - k + 1;

        char bit = findKthBit(n - 1, mirroredK);

        return bit == '0' ? '1' : '0';
    }
};


TIME COMPLEXITY
----------------

At every recursive call, n decreases by 1.

Therefore:

    O(n)


SPACE COMPLEXITY
----------------

Recursion depth:

    O(n)


No complete string is constructed.


================================================================================
DRY RUN WITH EXAMPLE
================================================================================

Input:

    n = 4
    k = 11


STEP 1
------

S4 length:

    2^4 - 1
    = 15

Middle:

    15 / 2 + 1
    = 8


k = 11

Since:

    11 > 8

k is in the right half.


Mirror k:

    15 - 11 + 1
    = 5


Now solve:

    findKthBit(3, 5)


STEP 2
------

S3 length:

    2^3 - 1
    = 7

Middle:

    7 / 2 + 1
    = 4


k = 5

Since:

    5 > 4

Right half again.

Mirror:

    7 - 5 + 1
    = 3


Now solve:

    findKthBit(2, 3)


STEP 3
------

S2 length:

    2^2 - 1
    = 3

Middle:

    3 / 2 + 1
    = 2


k = 3

Right half.

Mirror:

    3 - 3 + 1
    = 1


Now solve:

    findKthBit(1, 1)


STEP 4
------

S1:

    "0"

Therefore:

    findKthBit(1, 1) = '0'


STEP 5
------

We came from the right half of S2.

Right half is inverted.

    '0' -> '1'

Therefore:

    findKthBit(2, 3) = '1'


STEP 6
------

We came from the right half of S3.

Invert:

    '1' -> '0'

Therefore:

    findKthBit(3, 5) = '0'


STEP 7
------

We came from the right half of S4.

Invert:

    '0' -> '1'


Therefore:

    findKthBit(4, 11) = '1'


IMPORTANT:
----------
The actual S4 is:

    S4 = "011100110100011"

Index:

    1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    0  1  1  1  0  0  1  1  0  1  0  0  0  1  1

At k = 11:

    answer = '0'


So let's carefully follow the recursion:

For S4, k = 11.

    len = 15
    mid = 8
    mirroredK = 15 - 11 + 1 = 5

Call:

    findKthBit(3, 5)


For S3:

    S3 = "0111001"
    len = 7
    mid = 4

k = 5

    mirroredK = 7 - 5 + 1 = 3

Call:

    findKthBit(2, 3)


For S2:

    S2 = "011"
    len = 3
    mid = 2

k = 3

    mirroredK = 3 - 3 + 1 = 1

Call:

    findKthBit(1, 1)

S1:

    "0"

Return:

    '0'


Back to S2:
Invert:

    0 -> 1

So:

    findKthBit(2, 3) = '1'


Back to S3:
Invert:

    1 -> 0

So:

    findKthBit(3, 5) = '0'


Back to S4:
Invert:

    0 -> 1


This indicates the stated S4 construction above needs correction.

Let's construct carefully:

S1:
    0

S2:
    S1 + 1 + reverse(invert(S1))
    0 + 1 + 1
    = 011

S3:
    S2 = 011
    invert = 100
    reverse = 001

    S3 = 011 + 1 + 001
       = 0111001

S4:
    S3 = 0111001
    invert = 1000110
    reverse = 0110001

    S4 = 0111001 + 1 + 0110001

       = 011100110110001

Index 11 is:

    0

Therefore, why did recursion return 1?

Let's inspect the mapping carefully.

S4:

    LEFT  = S3       = 0111001
    MID   = 1
    RIGHT = 0110001

For k = 11:

    Right-half position:

    k - mid = 11 - 8
            = 3

Right half:

    0 1 1 0 0 0 1
    1 2 3 4 5 6 7

Position 3 = 1.

The corresponding position in S3 after reversing is:

    7 - 3 + 1 = 5

S3[5] = 0

Invert:

    0 -> 1

Again gives 1.

Therefore the correct S4 index 11 is actually:

    1


FINAL ANSWER FOR:

    n = 4
    k = 11

    '1'


================================================================================
INTERVIEW NOTES
================================================================================

PATTERN
-------

Recursion + Divide and Conquer + Symmetry


KEY OBSERVATION
---------------

The string has the structure:

    S(n-1) + "1" + reverse(invert(S(n-1)))


Therefore:

    LEFT:
        same as S(n-1)

    MIDDLE:
        always 1

    RIGHT:
        mirrored + inverted version of S(n-1)


This allows us to find one character without constructing
the complete string.


COMMON MISTAKES
---------------

1. Constructing the entire string.

   This is unnecessary.


2. Forgetting the middle position.

       middle = 2^(n-1)

   The middle bit is always:

       '1'


3. Forgetting to mirror k in the right half.

       mirroredK = len - k + 1


4. Forgetting to invert the result from the right half.

       0 -> 1
       1 -> 0


5. Off-by-one errors.

   The problem uses 1-based k.

   C++ strings use 0-based indexing.

   The recursive formula above keeps k as 1-based.


6. Using floating-point pow().

   Prefer:

       (1 << n)

   when n is small enough.


7. Thinking we need to generate S(n).

   We only need ONE character.


================================================================================
WHEN TO USE THIS APPROACH
================================================================================

Use this recursive pattern when:

    - A string is defined recursively.
    - The next string contains the previous string.
    - There is a middle element.
    - The other half is reversed/inverted.
    - The question asks for only one position.


Typical thought process:

    Can I locate k without constructing the string?


If the answer is yes:

    Use recursion / divide and conquer.


================================================================================
IMPORTANT FORMULA
================================================================================

Length:

    len = 2^n - 1


Middle:

    mid = 2^(n-1)


If:

    k == mid

Answer:

    '1'


If:

    k < mid

Go to:

    findKthBit(n-1, k)


If:

    k > mid

Mirror:

    mirroredK = len - k + 1

Then:

    answer = invert(findKthBit(n-1, mirroredK))


================================================================================
FINAL COMPLEXITY
================================================================================

Brute Force:

    Time  : O(2^n)
    Space : O(2^n)


Optimal:

    Time  : O(n)
    Space : O(n)


================================================================================
CORE IDEA TO REMEMBER
================================================================================

                 S(n)
                  |
        -----------------------
        |          |          |
    S(n-1)        1       reverse +
                           invert
        |                     |
        |                     |
      LEFT                   RIGHT
        |                     |
        |                     |
    k < mid               k > mid
        |                     |
        v                     v
   solve n-1            mirror k
                              |
                              v
                         solve n-1
                              |
                              v
                            invert




================================================================================
*/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size())
            return false;

        int m1[256], m2[256];

        memset(m1, -1, sizeof(m1));
        memset(m2, -1, sizeof(m2));

        for (int i = 0; i < s.size(); i++) {
            unsigned char a = s[i];
            unsigned char b = t[i];

            if (m1[a] == -1 && m2[b] == -1) {
                m1[a] = b;
                m2[b] = a;
            }
            else if (m1[a] != b || m2[b] != a) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    string s, t;
    cin >> s >> t;

    Solution sol;

    cout << (sol.isIsomorphic(s, t) ? "YES" : "NO") << '\n';

    return 0;
}

/*
============================================================
                LEETCODE 205: ISOMORPHIC STRINGS
============================================================

1. PROBLEM STATEMENT
------------------------------------------------------------
Given two strings s and t, determine whether they are
isomorphic.

Two strings are isomorphic if characters in s can be
replaced to get t, following these rules:

1. Each character must always map to the same character.
2. Two different characters cannot map to the same character.

Return YES if isomorphic, otherwise NO.

------------------------------------------------------------
2. EXAMPLE
------------------------------------------------------------

Example 1:
Input:
s = "egg"
t = "add"

Output:
YES

Mapping:
e -> a
g -> d

Example 2:
Input:
s = "foo"
t = "bar"

Output:
NO

Reason:
o -> a
o -> r

Same character maps to different characters.

Example 3:
Input:
s = "ab"
t = "aa"

Output:
NO

Reason:
a -> a
b -> a

Two different characters map to the same character.


============================================================
3. BRUTE FORCE APPROACH
============================================================

IDEA:
------------------------------------------------------------
Compare every character with all previously visited
characters.

Check two conditions:

1. If s[i] == s[j], then t[i] must equal t[j].
2. If t[i] == t[j], then s[i] must equal s[j].

If either condition fails, strings are not isomorphic.

PSEUDO CODE:
------------------------------------------------------------

1. If lengths are different, return false.
2. Iterate through every index i.
3. Compare s[i], t[i] with all previous positions j.
4. If s[i] == s[j] but t[i] != t[j], return false.
5. If t[i] == t[j] but s[i] != s[j], return false.
6. If no violation occurs, return true.

COMPLETE BRUTE FORCE CODE:
------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

bool isIsomorphic(string s, string t) {

    if (s.size() != t.size())
        return false;

    for (int i = 0; i < s.size(); i++) {

        for (int j = 0; j < i; j++) {

            if (s[i] == s[j] && t[i] != t[j])
                return false;

            if (t[i] == t[j] && s[i] != s[j])
                return false;
        }
    }

    return true;
}

int main() {

    string s, t;
    cin >> s >> t;

    cout << (isIsomorphic(s, t) ? "YES" : "NO");

    return 0;
}

TIME COMPLEXITY:
------------------------------------------------------------
O(n^2)

Two nested loops compare each character with all
previous characters.

SPACE COMPLEXITY:
------------------------------------------------------------
O(1)

Only a constant amount of extra space is used.


============================================================
4. OPTIMAL APPROACH
============================================================

OBSERVATION:
------------------------------------------------------------
We need to maintain a one-to-one mapping between
characters of both strings.

There are two conditions:

1. s -> t:
   One character in s cannot map to multiple characters
   in t.

2. t -> s:
   Two different characters in s cannot map to the
   same character in t.

INTUITION:
------------------------------------------------------------
Use two arrays of size 256.

m1[256]:
Stores mapping from s to t.

m2[256]:
Stores reverse mapping from t to s.

Initially, initialize both arrays with -1.

For every pair of characters:

a = s[i]
b = t[i]

CASE 1:
Both characters are unmapped.

    m1[a] = b;
    m2[b] = a;

Establish mapping in both directions.

CASE 2:
A mapping already exists.

Check:

    m1[a] != b || m2[b] != a

If either condition is true, mapping is invalid.

Otherwise, continue.

PSEUDO CODE:
------------------------------------------------------------

1. If lengths are different, return false.

2. Create two arrays m1[256], m2[256].

3. Initialize both arrays with -1.

4. Traverse both strings.

5. For each index:
   a = s[i]
   b = t[i]

6. If m1[a] == -1 AND m2[b] == -1:
       m1[a] = b
       m2[b] = a

7. Otherwise, if:
       m1[a] != b OR m2[b] != a

       Return false.

8. Return true.

COMPLETE OPTIMAL CODE:
------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

bool isIsomorphic(string s, string t) {

    if (s.size() != t.size())
        return false;

    int m1[256], m2[256];

    memset(m1, -1, sizeof(m1));
    memset(m2, -1, sizeof(m2));

    for (int i = 0; i < s.size(); i++) {

        unsigned char a = s[i];
        unsigned char b = t[i];

        if (m1[a] == -1 && m2[b] == -1) {

            m1[a] = b;
            m2[b] = a;
        }
        else if (m1[a] != b || m2[b] != a) {

            return false;
        }
    }

    return true;
}

int main() {

    string s, t;
    cin >> s >> t;

    cout << (isIsomorphic(s, t) ? "YES" : "NO");

    return 0;
}

TIME COMPLEXITY:
------------------------------------------------------------
O(n)

We traverse both strings exactly once.

Each mapping lookup and update takes O(1).

SPACE COMPLEXITY:
------------------------------------------------------------
O(1)

Two fixed-size arrays of 256 elements are used.

============================================================
5. DRY RUN WITH EXAMPLE
============================================================

Input:

s = "egg"
t = "add"

Initially:

m1[] = -1
m2[] = -1

ITERATION 1:
------------------------------------------------------------
i = 0

a = 'e'
b = 'a'

Both are unmapped.

m1['e'] = 'a'
m2['a'] = 'e'

Valid mapping established.

ITERATION 2:
------------------------------------------------------------
i = 1

a = 'g'
b = 'd'

Both are unmapped.

m1['g'] = 'd'
m2['d'] = 'g'

Valid mapping established.

ITERATION 3:
------------------------------------------------------------
i = 2

a = 'g'
b = 'd'

Check:

m1['g'] == 'd'  TRUE
m2['d'] == 'g'  TRUE

Existing mapping is consistent.

Final Result:

YES

============================================================
6. INTERVIEW NOTES
============================================================

PATTERN:
------------------------------------------------------------
Hashing / Character Mapping / Two-way Mapping

KEY OBSERVATION:
------------------------------------------------------------
Isomorphic strings require a bijective mapping.

Both directions must be checked:

s -> t
t -> s

COMMON MISTAKES:
------------------------------------------------------------

1. Using only one mapping array.

2. Checking consistent mapping but forgetting one-to-one
   mapping.

3. Forgetting to check whether string lengths are equal.

4. Accessing character indices without considering
   unsigned char when using a 256-element array.

5. Initializing mapping arrays incorrectly.

WHEN TO USE THIS APPROACH:
------------------------------------------------------------

Use two-way mapping when:

1. Two sequences require a one-to-one correspondence.
2. Every source element must map consistently.
3. No two distinct source elements can map to the
   same target element.

Similar applications:
- Isomorphic Strings
- Word Pattern
- Bijective Character Mapping
- Pattern Matching Problems

============================================================
                    FINAL COMPLEXITY
============================================================

Brute Force:
Time  : O(n^2)
Space : O(1)

Optimal:
Time  : O(n)
Space : O(1)

============================================================
*/

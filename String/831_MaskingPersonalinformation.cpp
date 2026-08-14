#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string maskPII(string s)
    {
        if (s.find('@') != string::npos)
        {
            transform(s.begin(), s.end(), s.begin(), ::tolower);

            int at = s.find('@');

            string name = s.substr(0, at);
            string domain = s.substr(at);

            return name[0] + string(5, '*') + name.back() + domain;
        }
        string digits;

        for (char c : s)
        {
            if (isdigit(c))
            {
                digits += c;
            }
        }

        int n = digits.size();
        string local = "***-***-" + digits.substr(n - 4);

        if (n == 10)
        {
            return local;
        }

        string country = string(n - 10, '*');

        return "+" + country + "-" + local;
    }
};

int main()
{
    Solution sol;

    string s;
    getline(cin, s);

    cout << sol.maskPII(s) << endl;

    return 0;
}

/*
============================================================
                    LEETCODE 831
              Masking Personal Information
============================================================

Problem Statement:
------------------
You are given a string s representing either an email address
or a phone number.

Mask the personal information according to these rules:

1. Email:
   - Convert the entire email to lowercase.
   - Keep the first and last character of the name.
   - Replace all characters between them with exactly 5 '*'.
   - Keep the '@' and domain unchanged except for lowercase.

   Example:
   "LeetCode@LeetCode.com"
   becomes
   "l*****e@leetcode.com"

2. Phone Number:
   - Remove all non-digit characters.
   - Keep the last 10 digits as the local phone number.
   - Format the local number as:
     "***-***-XXXX"
   - If there is a country code:
     Add '+' followed by the required number of '*',
     followed by '-'.

Example:
--------
Input:
LeetCode@LeetCode.com

Output:
l*****e@leetcode.com

Another Example:
Input:
+1(234)567-890

Output:
+*-***-***-7890


------------------------------------------------------------
Brute Force Approach
------------------------------------------------------------

Idea:
-----
Check whether the input contains '@'.

If it is an email:
    Convert everything to lowercase and construct the masked
    email.

If it is a phone number:
    Extract all digits and construct the masked phone number.

There is no need to actually generate every possible masking.
The direct construction is already optimal.

Pseudo Code:
------------
if s contains '@':
    convert s to lowercase
    find '@'
    get name and domain
    return first character + "*****" + last character + domain

else:
    extract all digits
    count digits

    local number = "***-***-" + last 4 digits

    if total digits == 10:
        return local number

    country code length = total digits - 10
    return "+" + '*' * country code length + "-" + local number

Complete Brute Force Code:
---------------------------

class Solution {
public:
    string maskPII(string s) {
        if (s.find('@') != string::npos) {
            transform(s.begin(), s.end(), s.begin(), ::tolower);

            int at = s.find('@');

            string name = s.substr(0, at);
            string domain = s.substr(at);

            return name[0] + string(5, '*') + name.back() + domain;
        }

        string digits;

        for (char c : s) {
            if (isdigit(c)) {
                digits += c;
            }
        }

        int n = digits.size();
        string result = "***-***-" + digits.substr(n - 4);

        if (n == 10)
            return result;

        return "+" + string(n - 10, '*') + "-" + result;
    }
};

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n)


------------------------------------------------------------
Optimal Approach
------------------------------------------------------------

Observation:
------------
The input can only be one of two types:

1. Email
2. Phone number

We can distinguish them by checking whether '@' exists.

For email, only the first and last characters of the name
are required.

For phone number, only:
    - number of digits
    - last 4 digits
are important.

Intuition:
----------
Instead of performing unnecessary operations, directly build
the required masked string.

Email:
    first + "*****" + last + domain

Phone:
    "***-***-" + last four digits

If the phone number has more than 10 digits, the extra digits
represent the country code.

Pseudo Code:
------------
if '@' exists:
    lowercase string
    locate '@'
    extract name
    extract domain

    return:
        first character
        + "*****"
        + last character
        + domain

else:
    collect only digits

    n = number of digits

    result = "***-***-" + last 4 digits

    if n == 10:
        return result

    return "+" + '*' repeated (n - 10) + "-" + result

Complete Optimal Code:
----------------------

class Solution {
public:
    string maskPII(string s) {
        if (s.find('@') != string::npos) {
            transform(s.begin(), s.end(), s.begin(), ::tolower);

            int at = s.find('@');

            string name = s.substr(0, at);
            string domain = s.substr(at);

            return name[0] + string(5, '*') + name.back() + domain;
        }

        string digits;

        for (char c : s) {
            if (isdigit(c)) {
                digits += c;
            }
        }

        int n = digits.size();

        string local = "***-***-" + digits.substr(n - 4);

        if (n == 10)
            return local;

        string country = string(n - 10, '*');

        return "+" + country + "-" + local;
    }
};

Time Complexity:
----------------
O(n)

Space Complexity:
-----------------
O(n)


------------------------------------------------------------
Dry Run With Example
------------------------------------------------------------

Example 1:
----------
s = "LeetCode@LeetCode.com"

Step 1:
Check '@'.

'@' exists, so it is an email.

Step 2:
Convert to lowercase:

"leetcode@leetcode.com"

Step 3:
Separate name and domain:

name   = "leetcode"
domain = "@leetcode.com"

Step 4:
Keep:
    first character = 'l'
    last character  = 'e'

Replace middle characters with 5 stars:

"l*****e"

Step 5:
Add domain:

"l*****e@leetcode.com"

Answer:
l*****e@leetcode.com


Example 2:
----------
s = "+1(234)567-890"

Step 1:
No '@', so it is a phone number.

Step 2:
Extract digits:

"1234567890"

Step 3:
Number of digits = 10

Step 4:
Take last 4 digits:

"7890"

Step 5:
Format:

"***-***-7890"

Answer:
***-***-7890


Example 3:
----------
s = "+86-(10)12345678"

Digits:

861012345678

Total digits = 12

Last 10 digits:

1012345678

Country code length:

12 - 10 = 2

Country code becomes:

"**"

Final:

+**-***-***-5678


------------------------------------------------------------
Interview Notes
------------------------------------------------------------

Pattern:
--------
String Parsing / String Manipulation

Key Observation:
----------------
The presence of '@' tells us whether the input is an email
or a phone number.

Email:
    Keep first + last character of the name.

Phone:
    Keep only the last four digits and mask everything else.

Common Mistakes:
----------------
1. Forgetting to convert email to lowercase.
2. Masking the entire email name instead of keeping the first
   and last characters.
3. Forgetting to remove '-', '(', ')', '+', and spaces from
   phone numbers before counting digits.
4. Using the original string length for phone numbers instead
   of the number of digits.
5. Forgetting the country-code stars for phone numbers with
   more than 10 digits.
6. Incorrectly formatting the last 10 digits.

When to Use This Approach:
--------------------------
Use direct string parsing when:
- The input has a small number of clearly defined formats.
- The required output can be constructed directly.
- We only need a single pass through the string.
- There is no need for complex data structures.

General Template:
-----------------
1. Identify the type of input.
2. Extract the required information.
3. Ignore unnecessary characters.
4. Construct the answer directly.

============================================================
*/
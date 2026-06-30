#include <iostream>
#include <string>
#include <climits>

using namespace std;

class Solution
{
public:
    int myAtoi(string s)
    {

        int i = 0;
        int n = s.size();
        int sign = 1;
        long long ans = 0;

        // Step 1: Skip leading whitespaces
        while (i < n && s[i] == ' ')
        {
            i++;
        }

        // Step 2: Check for sign
        if (i < n && (s[i] == '+' || s[i] == '-'))
        {

            if (s[i] == '-')
                sign = -1;

            i++;
        }

        // Step 3: Convert digits into number
        while (i < n && isdigit(s[i]))
        {

            int digit = s[i] - '0';

            // Check for overflow
            if (ans > (INT_MAX - digit) / 10)
            {

                if (sign == 1)
                    return INT_MAX;
                else
                    return INT_MIN;
            }

            ans = ans * 10 + digit;
            i++;
        }

        return sign * ans;
    }
};

int main()
{

    string s;

    cout << "Enter a string: ";
    getline(cin, s);

    Solution obj;

    int ans = obj.myAtoi(s);

    cout << "Converted Integer = " << ans << endl;

    return 0;
}

/*
==========================
Brute Force Approach
==========================

Idea:

1. Ignore all leading spaces.
2. Check if the number is positive or negative.
3. Store all valid digits separately.
4. Convert the stored digits into an integer.
5. Stop whenever a non-digit character is found.
6. Handle overflow manually.

Pseudo Code

Skip spaces

Check sign

Store digits

Convert digits into number

Apply sign

Return answer

Time Complexity:
O(N)

N = Length of string

Space Complexity:
O(N)

Reason:
Extra space is used to store digits.

--------------------------------------------------

Brute Force Code

int myAtoi(string s)
{
    int i = 0;
    int sign = 1;

    while(i < s.size() && s[i] == ' ')
        i++;

    if(i < s.size() && (s[i] == '+' || s[i] == '-'))
    {
        if(s[i] == '-')
            sign = -1;
        i++;
    }

    string digits = "";

    while(i < s.size() && isdigit(s[i]))
    {
        digits += s[i];
        i++;
    }

    long long num = 0;

    for(char ch : digits)
    {
        int digit = ch - '0';

        if(num > (INT_MAX - digit) / 10)
        {
            if(sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }

        num = num * 10 + digit;
    }

    return sign * num;
}

==================================================
Optimal Approach (Implemented Above)
==================================================

Idea:

1. Skip all leading spaces.
2. Check whether the number is positive or negative.
3. Read digits one by one.
4. Before adding a digit, check if the next operation
   will overflow the 32-bit integer range.
5. If overflow occurs:
      Return INT_MAX for positive numbers.
      Return INT_MIN for negative numbers.
6. Otherwise, continue building the number.
7. Return sign × answer.

Example 1:

Input:
"42"

Output:
42

------------------------------------

Example 2:

Input:
"   -42"

Skip spaces

Sign = Negative

Answer = -42

------------------------------------

Example 3:

Input:
"4193 with words"

Read only digits

Stop at first alphabet

Output = 4193

------------------------------------

Example 4:

Input:
"words and 987"

First non-space character is alphabet

Output = 0

------------------------------------

Example 5:

Input:
"-91283472332"

Value exceeds INT_MIN

Output = INT_MIN

Time Complexity:
O(N)

N = Length of string

Space Complexity:
O(1)

Why is this Optimal?

• Traverses the string only once.
• Uses constant extra memory.
• Handles whitespace, sign, invalid characters,
  and overflow during traversal.

LeetCode Problem:
8. String to Integer (atoi)
*/
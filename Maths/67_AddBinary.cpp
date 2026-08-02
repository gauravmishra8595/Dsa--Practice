#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string addBinary(string a, string b)
    {
        string ans = "";
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry)
        {
            int sum = carry;

            if (i >= 0)
                sum += a[i--] - '0';
            if (j >= 0)
                sum += b[j--] - '0';

            ans.push_back((sum % 2) + '0');
            carry = sum / 2;
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main()
{
    Solution obj;

    string a = "11";
    string b = "1";

    cout << obj.addBinary(a, b) << endl;

    return 0;
}

/*

===========================
Problem Statement
===========================

Given two binary strings a and b, return their sum as a binary string.

Leetcode 67 - Add Binary

===========================
Example
===========================

Input:
a = "11"
b = "1"

Output:
"100"

Explanation:
  11
+  1
----
100

==========================================================
Brute Force Approach
==========================================================

Idea:
Convert both binary strings into decimal numbers, add them,
then convert the sum back to binary.

This approach only works when the numbers fit into integer
or long long range. It fails for very large binary strings.

Pseudo Code:

decimalA = BinaryToDecimal(a)
decimalB = BinaryToDecimal(b)

sum = decimalA + decimalB

return DecimalToBinary(sum)

----------------------------------------------------------
Complete Brute Force Code
----------------------------------------------------------

class Solution {
public:

    long long toDecimal(string s){
        long long num = 0;
        for(char c : s)
            num = num * 2 + (c - '0');
        return num;
    }

    string toBinary(long long n){
        if(n == 0) return "0";

        string ans = "";
        while(n){
            ans.push_back((n % 2) + '0');
            n /= 2;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string addBinary(string a, string b) {
        long long x = toDecimal(a);
        long long y = toDecimal(b);
        return toBinary(x + y);
    }
};

Time Complexity:
O(N)

Space Complexity:
O(1)

(Note: Not valid for large inputs.)

==========================================================
Optimal Approach
==========================================================

Observation:

Binary addition is identical to decimal addition.

At each position:
sum = bitA + bitB + carry

Current Bit = sum % 2
Carry = sum / 2

Traverse both strings from right to left.

Intuition:

Instead of converting into decimal (which may overflow),
perform binary addition directly digit by digit.

Pseudo Code:

i = n-1
j = m-1
carry = 0

while(i>=0 || j>=0 || carry)

    sum = carry

    if(i>=0)
        sum += a[i]

    if(j>=0)
        sum += b[j]

    answer += (sum % 2)

    carry = sum / 2

reverse(answer)

return answer

----------------------------------------------------------
Complete Optimal Code
----------------------------------------------------------

class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;

        while(i >= 0 || j >= 0 || carry){
            int sum = carry;

            if(i >= 0) sum += a[i--] - '0';
            if(j >= 0) sum += b[j--] - '0';

            ans.push_back((sum % 2) + '0');
            carry = sum / 2;
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

Time Complexity:
O(max(N, M))

Space Complexity:
O(max(N, M))

==========================================================
Dry Run
==========================================================

Input:

a = "1010"
b = "1011"

Step 1:
0 + 1 + carry(0) = 1
Ans = 1

Step 2:
1 + 1 = 2
Bit = 0
Carry = 1

Ans = 01

Step 3:
0 + 0 + 1 = 1

Ans = 101

Step 4:
1 + 1 = 2
Bit = 0
Carry = 1

Ans = 0101

Remaining carry = 1

Ans = 10101

==========================================================
Interview Notes
==========================================================

Pattern:
- String Processing
- Simulation
- Bit Manipulation

Key Observation:
- Binary addition can be performed directly without converting
  to decimal.
- Maintain a carry exactly like elementary addition.

Common Mistakes:
- Forgetting the remaining carry.
- Not reversing the answer.
- Incorrect character-to-integer conversion.
- Using integer conversion leading to overflow.

When to use this approach:
- Adding very large binary numbers.
- Problems involving binary arithmetic represented as strings.
- Whenever overflow is possible with integer conversion.

*/

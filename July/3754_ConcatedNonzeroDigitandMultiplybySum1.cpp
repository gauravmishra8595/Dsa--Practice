#include <iostream>
using namespace std;

class Solution
{
public:
    long long sumAndMultiply(int n)
    {
        int place = 1;
        int number = 0;
        int sum = 0;

        while (n > 0)
        {
            int digit = n % 10;

            if (digit != 0)
            {
                number += digit * place;
                place *= 10;
                sum += digit;
            }

            n /= 10;
        }

        return 1LL * number * sum;
    }
};

int main()
{
    Solution obj;

    int n;
    cout << "Enter number: ";
    cin >> n;

    cout << "Answer = " << obj.sumAndMultiply(n) << endl;

    return 0;
}

/*
======================== BRUTE FORCE APPROACH ========================

Idea:
1. Convert the integer into a string.
2. Traverse every character.
3. Ignore '0'.
4. Concatenate all non-zero digits into another string.
5. Calculate the sum of non-zero digits.
6. Convert the new string back to an integer.
7. Return (concatenated number * sum).

Example:
Input: 1020304

String = "1020304"

New String = "1234"
Sum = 1 + 2 + 3 + 4 = 10

Answer = 1234 * 10 = 12340

Code:

string s = to_string(n);
string temp = "";
int sum = 0;

for(char c : s){
    if(c != '0'){
        temp += c;
        sum += c - '0';
    }
}

int number = stoi(temp);
return 1LL * number * sum;

Time Complexity : O(d)
Space Complexity: O(d)

(where d = number of digits)


======================== OPTIMAL APPROACH ========================

Idea:
Instead of converting the number into a string,
extract digits using modulo (%) and division (/).

Steps:
1. Take the last digit using n % 10.
2. If it is non-zero:
      - Add it to the sum.
      - Place it in the reconstructed number using the
        current place value (1,10,100,...).
3. Remove the last digit using n /= 10.
4. Continue until the number becomes 0.
5. Return reconstructed_number * sum.

Example:

Input: 1020304

Digits extracted:
4 -> keep
0 -> ignore
3 -> keep
0 -> ignore
2 -> keep
0 -> ignore
1 -> keep

Reconstructed number = 1234
Sum = 10

Answer = 12340

Why does place work?

Since digits are extracted from right to left,
we rebuild the number using place values:
place = 1
place = 10
place = 100
place = 1000
...

This preserves the original order of non-zero digits
without using any extra string.

Time Complexity : O(d)
Space Complexity: O(1)

(where d = number of digits)
*/
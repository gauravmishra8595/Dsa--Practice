#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProduct(int n)
    {
        int mx1 = 0, mx2 = 0;

        while (n > 0)
        {
            int d = n % 10;
            n /= 10;

            if (d >= mx1)
            {
                mx2 = mx1;
                mx1 = d;
            }
            else if (d > mx2)
            {
                mx2 = d;
            }
        }

        return mx1 * mx2;
    }
};

int main()
{
    Solution obj;

    int n;
    cin >> n;

    cout << obj.maxProduct(n);

    return 0;
}

/*

=========================================================
LeetCode 3536. Maximum Product of Two Digits
=========================================================

Problem Statement:
------------------
You are given a positive integer n.

Return the maximum product of any two digits present in n.

Note:
- If a digit appears multiple times, it may be used multiple times.
- We only need the maximum possible product.

---------------------------------------------------------
Example
---------------------------------------------------------

Input:
124

Output:
8

Explanation:
Digits = {1,2,4}
Possible products:
1*2 = 2
1*4 = 4
2*4 = 8

Maximum = 8


=========================================================
Brute Force Approach
=========================================================

Idea:
-----
1. Extract all digits into an array.
2. Check every possible pair.
3. Keep the maximum product.

Pseudo Code:
------------

store digits in vector

ans = 0

for i = 0 to size-1
    for j = i+1 to size-1
        ans = max(ans, digits[i] * digits[j])

return ans

---------------------------------------------------------
Complete Brute Force Code
---------------------------------------------------------

class Solution {
public:
    int maxProduct(int n) {
        vector<int> digits;

        while(n){
            digits.push_back(n%10);
            n/=10;
        }

        int ans = 0;

        for(int i=0;i<digits.size();i++){
            for(int j=i+1;j<digits.size();j++){
                ans=max(ans,digits[i]*digits[j]);
            }
        }

        return ans;
    }
};

Time Complexity:
O(d²)

where d = number of digits (<=10)

Space Complexity:
O(d)


=========================================================
Optimal Approach
=========================================================

Observation:
------------
The maximum product always comes from the two largest digits.

Instead of storing every digit, simply keep track of:
- largest digit
- second largest digit

Intuition:
----------
While traversing the digits:

If current digit is larger than largest:
    secondLargest = largest
    largest = current

Else if current digit is larger than secondLargest:
    secondLargest = current

Finally,
answer = largest × secondLargest

Pseudo Code:
------------

largest = 0
secondLargest = 0

while(n>0)

    digit = n%10

    if digit >= largest
        secondLargest = largest
        largest = digit

    else if digit > secondLargest
        secondLargest = digit

    n/=10

return largest*secondLargest

---------------------------------------------------------
Complete Optimal Code
---------------------------------------------------------

class Solution {
public:
    int maxProduct(int n) {
        int mx1 = 0, mx2 = 0;

        while (n > 0) {
            int d = n % 10;
            n /= 10;

            if (d >= mx1) {
                mx2 = mx1;
                mx1 = d;
            } else if (d > mx2) {
                mx2 = d;
            }
        }

        return mx1 * mx2;
    }
};

Time Complexity:
O(d)

d = number of digits

Since d <= 10, this is effectively O(1).

Space Complexity:
O(1)


=========================================================
Dry Run
=========================================================

Input:
n = 124

Initially

mx1 = 0
mx2 = 0

Digit = 4

mx1 = 4
mx2 = 0

Digit = 2

mx1 = 4
mx2 = 2

Digit = 1

No change

Answer

4 × 2 = 8


=========================================================
Interview Notes
=========================================================

Pattern:
--------
Single traversal
Tracking largest and second largest values

Key Observation:
----------------
Maximum product is always formed using the two largest digits.

Common Mistakes:
----------------
1. Forgetting to update second largest when largest changes.
2. Using '>' instead of '>=' for duplicate maximum digits.
   Example:
   22 should return 4.
3. Storing all digits unnecessarily.

When to use this approach:
--------------------------
Whenever the problem asks for:
- Largest and second largest element
- Top K (small K)
- One-pass optimization
- Constant extra space solution

=========================================================

*/
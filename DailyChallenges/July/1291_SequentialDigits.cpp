#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;
        string s = "123456789";

        int lowLen = to_string(low).size();
        int highLen = to_string(high).size();

        for (int len = lowLen; len <= highLen; len++) {
            for (int i = 0; i + len <= 9; i++) {
                int num = stoi(s.substr(i, len));
                if (num >= low && num <= high)
                    ans.push_back(num);
            }
        }

        return ans;
    }
};

int main() {
    Solution obj;

    int low = 10, high = 40;
    vector<int> ans = obj.sequentialDigits(low, high);

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*

===========================
Leetcode 1291. Sequential Digits
===========================

Problem Statement:
------------------
An integer has sequential digits if and only if each digit in the number is exactly one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

--------------------------------------------------

Example:
--------
Input:
low = 100
high = 300

Output:
123 234

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea:
-----
Check every number from low to high.
For each number, verify whether every adjacent digit differs by exactly +1.

Pseudo Code:
------------
for num = low to high
    if isSequential(num)
        answer.push_back(num)

return answer

Complete Brute Force Code:
--------------------------

class Solution {
public:

    bool isSequential(int num){
        string s = to_string(num);

        for(int i=1;i<s.size();i++){
            if(s[i] != s[i-1] + 1)
                return false;
        }

        return true;
    }

    vector<int> sequentialDigits(int low, int high) {

        vector<int> ans;

        for(int num=low; num<=high; num++){
            if(isSequential(num))
                ans.push_back(num);
        }

        return ans;
    }
};

Time Complexity:
----------------
O((high-low+1) * D)

D = Number of digits.

Space Complexity:
-----------------
O(1)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation:
------------
There are very few sequential digit numbers.

They are simply substrings of:

123456789

Examples:
12
23
34
...
123
234
...
1234
2345
...
123456789

Generate every possible substring once and keep those within range.

Intuition:
----------
Instead of checking every number, directly construct all valid sequential numbers.

Maximum possible sequential numbers:

Length 2 -> 8 numbers
Length 3 -> 7 numbers
...
Length 9 -> 1 number

Total = 36 numbers only.

Pseudo Code:
------------
s = "123456789"

for length = digits(low) to digits(high)
    for every valid starting index
        num = substring(length)
        if low <= num <= high
            add into answer

return answer

Complete Optimal Code:
----------------------

class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {

        vector<int> ans;

        string s = "123456789";

        int lowLen = to_string(low).size();
        int highLen = to_string(high).size();

        for(int len = lowLen; len <= highLen; len++){

            for(int i=0; i+len<=9; i++){

                int num = stoi(s.substr(i,len));

                if(num>=low && num<=high)
                    ans.push_back(num);
            }
        }

        return ans;
    }
};

Time Complexity:
----------------
O(36)

or simply O(1)

Space Complexity:
-----------------
O(1)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input:
low = 100
high = 300

s = "123456789"

Length = 3

i = 0
substring = "123"
num = 123
Valid

i = 1
substring = "234"
num = 234
Valid

i = 2
substring = "345"
Greater than high

Remaining are also larger.

Answer:
123 234

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern:
--------
Construct / Enumeration

Key Observation:
----------------
Every sequential number is just a substring of
"123456789".

Only 36 possible candidates exist.

Common Mistakes:
----------------
1. Iterating from low to high.
2. Forgetting to limit substring end.
3. Incorrect digit length range.
4. Using string comparison instead of integer comparison.

When to use this approach:
--------------------------
- Very small candidate space.
- Numbers can be generated directly.
- Enumeration is significantly cheaper than validation.

*/
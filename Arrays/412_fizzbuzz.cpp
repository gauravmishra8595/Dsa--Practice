#include <bits/stdc++.h>
using namespace std;

// LeetCode 412: Fizz Buzz

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans;

        for (int i = 1; i <= n; i++) {
            if (i % 15 == 0) {
                ans.push_back("FizzBuzz");
            }
            else if (i % 3 == 0) {
                ans.push_back("Fizz");
            }
            else if (i % 5 == 0) {
                ans.push_back("Buzz");
            }
            else {
                ans.push_back(to_string(i));
            }
        }

        return ans;
    }
};

int main() {
    int n;
    cin >> n;

    Solution obj;
    vector<string> ans = obj.fizzBuzz(n);

    for (string s : ans) {
        cout << s << " ";
    }

    cout << endl;
    return 0;
}

/*
=========================================================
                LEETCODE 412 - FIZZ BUZZ
=========================================================

1. PROBLEM STATEMENT
--------------------
Given an integer n, return a vector of strings from 1 to n.

Rules:
- If number is divisible by 3, store "Fizz".
- If number is divisible by 5, store "Buzz".
- If divisible by both 3 and 5, store "FizzBuzz".
- Otherwise, store the number as a string.

2. EXAMPLE
----------
Input:
n = 15

Output:
["1","2","Fizz","4","Buzz","Fizz",
 "7","8","Fizz","Buzz","11","Fizz",
 "13","14","FizzBuzz"]


=========================================================
3. BRUTE FORCE APPROACH
=========================================================

IDEA:
-----
Check divisibility by 3 and 5 separately.
If both conditions are true, append "FizzBuzz".
Otherwise, append the appropriate string.

PSEUDO CODE:
------------
1. Create an empty answer vector.
2. Iterate i from 1 to n.
3. If i is divisible by both 3 and 5:
      Add "FizzBuzz".
4. Else if divisible by 3:
      Add "Fizz".
5. Else if divisible by 5:
      Add "Buzz".
6. Otherwise:
      Convert i to string and add it.
7. Return the answer.

COMPLETE BRUTE FORCE CODE:
--------------------------
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans;

        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 == 0) {
                ans.push_back("FizzBuzz");
            }
            else if (i % 3 == 0) {
                ans.push_back("Fizz");
            }
            else if (i % 5 == 0) {
                ans.push_back("Buzz");
            }
            else {
                ans.push_back(to_string(i));
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
----------------
O(n)

SPACE COMPLEXITY:
-----------------
O(n) for storing the answer.


=========================================================
4. OPTIMAL APPROACH
=========================================================

OBSERVATION:
------------
A number divisible by both 3 and 5 is also divisible by
their LCM, which is 15.

Therefore:
i % 15 == 0 means "FizzBuzz".

INTUITION:
----------
Traverse numbers from 1 to n exactly once.

For each number:
- Check divisibility by 15 first.
- Then check divisibility by 3.
- Then check divisibility by 5.
- Otherwise convert the number into a string.

Using i % 15 makes the combined condition simpler.

PSEUDO CODE:
------------
1. Initialize an empty vector ans.
2. Loop i from 1 to n.
3. If i % 15 == 0:
      Push "FizzBuzz".
4. Else if i % 3 == 0:
      Push "Fizz".
5. Else if i % 5 == 0:
      Push "Buzz".
6. Else:
      Push to_string(i).
7. Return ans.

COMPLETE OPTIMAL CODE:
----------------------
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans;

        for (int i = 1; i <= n; i++) {
            if (i % 15 == 0) {
                ans.push_back("FizzBuzz");
            }
            else if (i % 3 == 0) {
                ans.push_back("Fizz");
            }
            else if (i % 5 == 0) {
                ans.push_back("Buzz");
            }
            else {
                ans.push_back(to_string(i));
            }
        }

        return ans;
    }
};

TIME COMPLEXITY:
----------------
O(n)

Each number is processed exactly once.

SPACE COMPLEXITY:
-----------------
O(n) auxiliary output space for the answer vector.

=========================================================
5. DRY RUN
=========================================================

Input: n = 15

i       Condition          Output
-------------------------------------
1       None               "1"
2       None               "2"
3       Divisible by 3     "Fizz"
4       None               "4"
5       Divisible by 5     "Buzz"
6       Divisible by 3     "Fizz"
7       None               "7"
8       None               "8"
9       Divisible by 3     "Fizz"
10      Divisible by 5     "Buzz"
11      None               "11"
12      Divisible by 3     "Fizz"
13      None               "13"
14      None               "14"
15      Divisible by 15    "FizzBuzz"

Final Answer:
["1","2","Fizz","4","Buzz","Fizz","7","8",
 "Fizz","Buzz","11","Fizz","13","14","FizzBuzz"]


=========================================================
6. INTERVIEW NOTES
=========================================================

PATTERN:
--------
Array / Vector Traversal + Conditional Logic.

KEY OBSERVATION:
----------------
LCM(3, 5) = 15.

A number divisible by both 3 and 5 is divisible by 15.

COMMON MISTAKES:
----------------
1. Checking divisibility by 3 before checking both conditions.
2. Forgetting to convert integers into strings using to_string().
3. Starting the loop from 0 instead of 1.
4. Returning an integer vector instead of vector<string>.
5. Forgetting to store the result in the answer vector.

WHEN TO USE THIS APPROACH:
--------------------------
1. When multiple divisibility conditions are given.
2. When a problem requires processing a sequence.
3. When different conditions produce different outputs.
4. When a single traversal is sufficient.

=========================================================
                 END OF LEETCODE 412
=========================================================
*/

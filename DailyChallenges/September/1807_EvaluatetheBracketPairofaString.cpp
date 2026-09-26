#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string evaluate(string s, vector<vector<string>> &knowledge)
    {
        unordered_map<string, string> mp;

        for (auto &entry : knowledge)
        {
            mp[entry[0]] = entry[1];
        }

        string result;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                int j = s.find(')', i + 1);
                string key = s.substr(i + 1, j - i - 1);

                auto it = mp.find(key);
                result += (it != mp.end()) ? it->second : "?";

                i = j;
            }
            else
            {
                result += s[i];
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;

    string s = "(name)is(age)yearsold";
    vector<vector<string>> knowledge = {
        {"name", "bob"},
        {"age", "two"}};

    cout << sol.evaluate(s, knowledge) << '\n';

    return 0;
}

/*
================================================================================
                    EVALUATE THE BRACKET PAIRS OF A STRING
================================================================================

Problem Statement:
------------------
Given a string s containing lowercase English letters, spaces, and bracket
pairs of the form "(key)", and a knowledge list containing key-value pairs,
replace every "(key)" with its corresponding value.

If a key is not present in knowledge, replace it with '?'.

Example:
--------
Input:
s = "(name)is(age)yearsold"
knowledge = [["name","bob"], ["age","two"]]

Output:
"bobistwoyearsold"


================================================================================
Brute Force Approach
================================================================================

Idea:
-----
For every bracket pair, extract the key and search the entire knowledge
vector linearly to find its value.

If the key is found, append its value; otherwise append '?'.

Pseudo Code:
------------
1. Set result = empty string.
2. Traverse s from left to right.
3. If current character is '(':
      Find the next ')'.
      Extract the key between '(' and ')'.
      Linearly search knowledge for the key.
      If found, append its value.
      Otherwise append '?'.
      Move index to ')'.
4. Otherwise append the current character.
5. Return result.

Complete Brute Force Code:
--------------------------

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        string result;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                int j = s.find(')', i + 1);
                string key = s.substr(i + 1, j - i - 1);

                string value = "?";

                for (auto &entry : knowledge) {
                    if (entry[0] == key) {
                        value = entry[1];
                        break;
                    }
                }

                result += value;
                i = j;
            }
            else {
                result += s[i];
            }
        }

        return result;
    }
};

Time Complexity:
----------------
O(N * K)

N = length of string
K = number of key-value pairs.

Space Complexity:
-----------------
O(N)


================================================================================
Optimal Approach
================================================================================

Observation:
------------
Searching the knowledge vector for every key takes O(K) time.

We can store all key-value pairs in an unordered_map so that each lookup
takes O(1) average time.

Intuition:
----------
Convert:

knowledge = [["name","bob"], ["age","two"]]

into:

mp["name"] = "bob"
mp["age"]  = "two"

Then while traversing the string, extract every key and directly look it up
in the hash map.

Pseudo Code:
------------
1. Create unordered_map mp.
2. Store every key-value pair in mp.
3. Traverse s from left to right.
4. If '(' is found:
      Find ')'.
      Extract the key.
      Search key in mp.
      If found, append its value.
      Otherwise append '?'.
      Move index to ')'.
5. Otherwise append the current character.
6. Return result.

Complete Optimal Code:
----------------------

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        for (auto &entry : knowledge) {
            mp[entry[0]] = entry[1];
        }

        string result;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                int j = s.find(')', i + 1);
                string key = s.substr(i + 1, j - i - 1);

                auto it = mp.find(key);
                result += (it != mp.end()) ? it->second : "?";

                i = j;
            } else {
                result += s[i];
            }
        }

        return result;
    }
};

Time Complexity:
----------------
Average: O(N + K)

N = length of string
K = number of knowledge pairs.

Space Complexity:
-----------------
O(N + K)


================================================================================
Dry Run with Example
================================================================================

s = "(name)is(age)yearsold"

knowledge:
[
    ["name", "bob"],
    ["age", "two"]
]

Hash Map:
---------
name -> bob
age  -> two


i = 0
-----
Current character = '('

Find closing ')'.

key = "name"

mp["name"] = "bob"

result = "bob"


Next:
-----
Characters 'i' and 's' are normal characters.

result = "bobis"


Next:
-----
Find "(age)".

key = "age"

mp["age"] = "two"

result = "bobistwo"


Remaining:
----------
"yearsold"

Final result:
-------------
"bobistwoyearsold"


================================================================================
Interview Notes
================================================================================

Pattern:
--------
String Parsing + Hash Map

Key Observation:
----------------
Preprocess the key-value pairs into a hash map so every key can be searched
in O(1) average time.

Common Mistakes:
----------------
1. Forgetting to move i to the closing ')'.
2. Incorrect substring length.
3. Searching the knowledge vector for every key.
4. Forgetting '?' for unknown keys.
5. Accidentally including '(' or ')' in the key.
6. Using mp[key] just to check existence.

When to use this approach:
--------------------------
Use this approach when a string contains tokens that need to be replaced
using key-value mappings and fast repeated lookup is required.

General Pattern:
----------------

    Knowledge
        |
        v
    Hash Map
        |
        v
    Traverse String
        |
        v
    Extract Key
        |
        v
    Hash Map Lookup
       /       \
    Found     Missing
      |           |
    value         ?
       \         /
        Append Result


================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> mp;

        for (string s : strs)
        {
            string key = s;
            sort(key.begin(), key.end());
            mp[key].push_back(s);
        }

        vector<vector<string>> ans;
        for (auto &it : mp)
            ans.push_back(it.second);

        return ans;
    }
};

int main()
{
    Solution obj;

    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    vector<vector<string>> ans = obj.groupAnagrams(strs);

    for (auto &group : ans)
    {
        cout << "[ ";
        for (auto &word : group)
            cout << word << " ";
        cout << "]\n";
    }

    return 0;
}

/*

=========================================
LeetCode 49
Group Anagrams
=========================================

Problem Statement
-----------------
Given an array of strings strs, group the anagrams together.
You can return the answer in any order.

Two strings are anagrams if they contain the same characters with the same
frequency, only arranged differently.

--------------------------------------------------

Example
-------

Input:
strs = ["eat","tea","tan","ate","nat","bat"]

Output:
[
 ["bat"],
 ["tan","nat"],
 ["eat","tea","ate"]
]

--------------------------------------------------
Brute Force Approach
--------------------------------------------------

Idea
----
Compare every string with every other unused string.
For each comparison:
1. Sort both strings.
2. If sorted strings are equal, they belong to the same group.

Pseudo Code
-----------
visited[]

for i = 0 to n-1

    if visited[i]
        continue

    newGroup

    for j = i to n-1

        if !visited[j]

            if sort(strs[i]) == sort(strs[j])

                add strs[j]
                visited[j] = true

Complete Brute Force Code
-------------------------

class Solution {
public:

    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        int n = strs.size();

        vector<bool> vis(n,false);
        vector<vector<string>> ans;

        for(int i=0;i<n;i++){

            if(vis[i]) continue;

            vector<string> group;

            string temp1 = strs[i];
            sort(temp1.begin(),temp1.end());

            for(int j=i;j<n;j++){

                if(vis[j]) continue;

                string temp2 = strs[j];
                sort(temp2.begin(),temp2.end());

                if(temp1==temp2){
                    group.push_back(strs[j]);
                    vis[j]=true;
                }
            }

            ans.push_back(group);
        }

        return ans;
    }
};

Time Complexity
---------------
O(n² * k log k)

n = number of strings
k = average length of string

Space Complexity
----------------
O(n)

--------------------------------------------------
Optimal Approach
--------------------------------------------------

Observation
-----------
Two strings are anagrams if their sorted versions are identical.

Use the sorted string as a unique key in a hash map.

Intuition
---------
For every string:
1. Create a copy.
2. Sort it.
3. Store the original string in the hashmap using the sorted string as key.

Finally, all values of the hashmap become the answer.

Pseudo Code
-----------
unordered_map

for every string

    key = sorted(string)

    map[key].push_back(string)

answer = all map values

Complete Optimal Code
---------------------

class Solution {
public:

    vector<vector<string>> groupAnagrams(vector<string>& strs){

        unordered_map<string,vector<string>> mp;

        for(string s : strs){

            string key = s;
            sort(key.begin(),key.end());

            mp[key].push_back(s);
        }

        vector<vector<string>> ans;

        for(auto &it : mp)
            ans.push_back(it.second);

        return ans;
    }
};

Time Complexity
---------------
Sorting each string:
O(k log k)

For all strings:
O(n * k log k)

Space Complexity
----------------
O(n * k)

(HashMap stores all strings.)

--------------------------------------------------
Dry Run
--------------------------------------------------

Input

["eat","tea","tan","ate","nat","bat"]

Iteration

eat

Sorted = aet

Map

aet -> eat

----------------

tea

Sorted = aet

Map

aet -> eat tea

----------------

tan

Sorted = ant

Map

ant -> tan

----------------

ate

Sorted = aet

Map

aet -> eat tea ate

----------------

nat

Sorted = ant

Map

ant -> tan nat

----------------

bat

Sorted = abt

Map

abt -> bat

Final Answer

[
[eat tea ate]
[tan nat]
[bat]
]

--------------------------------------------------
Interview Notes
--------------------------------------------------

Pattern
-------
HashMap + Sorting

Key Observation
---------------
All anagrams produce the same sorted string.

Common Mistakes
---------------
1. Sorting the original string instead of a copy.
2. Forgetting unordered_map groups automatically.
3. Assuming output order matters (it doesn't).

When to use this approach
-------------------------
Whenever strings need to be grouped by identical character composition.
Sorting provides a canonical representation, making HashMap grouping simple.

Alternative
-----------
Instead of sorting, use a frequency count of 26 letters as the hashmap key.
That achieves O(n * k), but requires a custom hash for vectors or encoded keys.

*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumPushes(string word)
    {
        vector<int> freq(26, 0);

        for (char ch : word)
            freq[ch - 'a']++;

        sort(freq.begin(), freq.end(), greater<int>());

        int ans = 0;

        for (int i = 0; i < 26; i++)
        {
            if (freq[i] == 0)
                break;
            ans += freq[i] * (i / 8 + 1);
        }

        return ans;
    }
};

int main()
{
    Solution obj;

    string word = "abcde";
    cout << obj.minimumPushes(word) << endl;

    return 0;
}

/*

===========================
LeetCode 3014 - Minimum Number of Pushes to Type Word I
===========================

-----------------------------------
Problem Statement
-----------------------------------
You are given a string word consisting of lowercase English letters.

You can remap the letters onto the telephone keypad.

Each key can contain at most 8 different letters.

Typing a letter requires:
- 1 push if it is the first letter assigned to a key.
- 2 pushes if it is the second letter assigned to that key.
- 3 pushes if it is the third.
- ...

Find the minimum number of pushes required to type the given word.

-----------------------------------
Example
-----------------------------------

Input:
word = "abcde"

Output:
5

Explanation:
Each character appears once.
Since there are only 5 unique letters, all can be placed in the first position.
Total pushes = 5.

-----------------------------------
Brute Force Approach
-----------------------------------

Idea:
Try every possible assignment of letters to keys and calculate the total number of pushes.

Since there are enormous possible mappings, this approach is infeasible.

-----------------------------------
Pseudo Code
-----------------------------------

Generate all keypad assignments
For each assignment
    Calculate total pushes
Return minimum

-----------------------------------
Complete Brute Force Code
-----------------------------------

class Solution {
public:
    int minimumPushes(string word) {
        Generate every possible mapping
        Compute pushes
        Return minimum

        Not feasible due to huge search space.
    }
};

-----------------------------------
Time Complexity
-----------------------------------

Exponential

-----------------------------------
Space Complexity
-----------------------------------

Exponential

=========================================================
Optimal Approach
=========================================================

-----------------------------------
Observation
-----------------------------------

Only the frequency of each character matters.

Most frequent letters should require the fewest pushes.

Each push level can contain at most 8 letters.

-----------------------------------
Intuition
-----------------------------------

1. Count frequency of every letter.

2. Sort frequencies in descending order.

3. Assign:

First 8 letters -> 1 push

Next 8 letters -> 2 pushes

Next 8 letters -> 3 pushes

Remaining -> 4 pushes

Multiply:
frequency × push_count

-----------------------------------
Pseudo Code
-----------------------------------

Count frequencies

Sort descending

ans = 0

for i = 0 to 25

    if frequency == 0
        break

    push = i / 8 + 1

    ans += frequency * push

return ans

-----------------------------------
Complete Optimal Code
-----------------------------------

class Solution {
public:
    int minimumPushes(string word) {

        vector<int> freq(26,0);

        for(char ch : word)
            freq[ch-'a']++;

        sort(freq.begin(), freq.end(), greater<int>());

        int ans = 0;

        for(int i=0;i<26;i++){

            if(freq[i]==0)
                break;

            ans += freq[i] * (i/8 + 1);
        }

        return ans;
    }
};

-----------------------------------
Time Complexity
-----------------------------------

Counting Frequency : O(N)

Sorting 26 elements : O(26 log 26)

Traversal : O(26)

Overall:

O(N)

-----------------------------------
Space Complexity
-----------------------------------

O(26)

≈ O(1)

=========================================================
Dry Run
=========================================================

word = "aabbccc"

Frequency:

c -> 3

a -> 2

b -> 2

Sorted:

3 2 2

Index 0

Push = 1

Answer = 3

Index 1

Push = 1

Answer = 5

Index 2

Push = 1

Answer = 7

Final Answer = 7

=========================================================
Interview Notes
=========================================================

Pattern:
Greedy + Frequency Counting + Sorting

Key Observation:
Higher frequency characters should receive lower push counts.

Common Mistakes:
1. Sorting in ascending order.
2. Forgetting to ignore zero frequencies.
3. Using incorrect push formula.
4. Forgetting that each push level can hold only 8 letters.

When to use this approach:
Whenever:
- Only frequencies matter.
- Costs increase with position.
- Most frequent items should receive smallest cost.
- Greedy assignment after sorting gives the optimal answer.

*/
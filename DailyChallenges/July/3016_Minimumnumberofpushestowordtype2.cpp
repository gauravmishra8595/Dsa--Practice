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

======================== Problem Statement ========================

3016. Minimum Number of Pushes to Type Word II

You are given a string word consisting of lowercase English letters.

A telephone keypad has 8 keys (2-9). You may assign every distinct
character to exactly one key in any order.

Typing a character requires:
- 1 push if it is the first character assigned to a key.
- 2 pushes if it is the second.
- 3 pushes if it is the third.
- ...

Return the minimum number of pushes required to type the entire word.

============================== Example ==============================

Input:
word = "abcde"

Output:
5

Explanation:
Assign every character to first position of different keys.
Each character needs only one push.

====================================================================
                     BRUTE FORCE APPROACH
====================================================================

Idea:
Try every possible assignment of characters among 8 keys and compute
the total pushes. Return the minimum.

This is impossible in practice because the number of assignments grows
exponentially.

-------------------------- Pseudo Code --------------------------

Collect distinct characters

Generate every possible assignment to 8 keys

For every assignment:
    Compute push count
    Update minimum

Return answer

---------------- Complete Brute Force Code ----------------

class Solution {
public:
    int minimumPushes(string word) {
        // Generate all possible assignments of characters
        // Evaluate each assignment
        // Return minimum pushes

        // Not feasible due to exponential complexity.
    }
};

---------------- Time Complexity ----------------

Exponential

---------------- Space Complexity ----------------

Exponential (recursive states)

====================================================================
                     OPTIMAL APPROACH
====================================================================

Observation

Only the frequency of every character matters.

Characters appearing more frequently should require fewer pushes.

Each push level can contain at most 8 characters because there are
only 8 keys.

Therefore,

Top 8 frequent letters -> cost = 1

Next 8 letters -> cost = 2

Next 8 letters -> cost = 3

Remaining letters -> cost = 4

--------------------------- Intuition ---------------------------

Sort character frequencies in descending order.

Assign smallest push counts to largest frequencies greedily.

This greedy assignment is always optimal.

------------------------- Pseudo Code -------------------------

freq[26]

Count frequency

Sort descending

answer = 0

For i = 0 to 25

    if frequency == 0
        break

    answer += frequency * (i/8 + 1)

Return answer

---------------- Complete Optimal Code ----------------

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

            ans += freq[i]*(i/8 + 1);
        }

        return ans;
    }
};

---------------- Time Complexity ----------------

O(N + 26 log 26)

Since alphabet size is fixed,

=> O(N)

---------------- Space Complexity ----------------

O(26)

=> O(1)

====================================================================
                        DRY RUN
====================================================================

word = "aabbccc"

Frequency

c -> 3
a -> 2
b -> 2

Sorted frequencies

3 2 2

i = 0
cost = 1

ans = 3

i = 1
cost = 1

ans = 5

i = 2
cost = 1

ans = 7

Answer = 7

====================================================================
                      INTERVIEW NOTES
====================================================================

Pattern

Greedy + Sorting Frequencies

Key Observation

Always assign the most frequent characters to the lowest push count.

Common Mistakes

1. Sorting ascending instead of descending.

2. Forgetting there are only 8 keys.

3. Using (i%8) instead of (i/8).

4. Counting pushes using character order instead of frequency.

When to use this approach

Whenever:
- Cost depends on ordering.
- Higher frequency should receive lower cost.
- Greedy assignment after sorting is optimal.

====================================================================

*/
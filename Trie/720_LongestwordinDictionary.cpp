#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct TrieNode {
        TrieNode* child[26];
        bool isEnd;

        TrieNode() {
            isEnd = false;
            memset(child, 0, sizeof(child));
        }
    };

    TrieNode* root = new TrieNode();

    void insert(const string& word) {
        TrieNode* curr = root;

        for (char c : word) {
            int idx = c - 'a';

            if (!curr->child[idx])
                curr->child[idx] = new TrieNode();

            curr = curr->child[idx];
        }

        curr->isEnd = true;
    }

    void dfs(TrieNode* node, string& current, string& answer) {
        for (int i = 0; i < 26; i++) {
            if (!node->child[i])
                continue;

            TrieNode* next = node->child[i];

            // Every prefix must itself be a valid word
            if (!next->isEnd)
                continue;

            current.push_back('a' + i);

            if (current.length() > answer.length())
                answer = current;

            dfs(next, current, answer);

            current.pop_back();
        }
    }

public:
    string longestWord(vector<string>& words) {
        for (const string& word : words)
            insert(word);

        string answer = "";
        string current = "";

        dfs(root, current, answer);

        return answer;
    }
};

int main() {
    Solution sol;

    vector<string> words = {
        "w", "wo", "wor", "worl", "world",
        "banana", "ban", "bana", "banan"
    };

    cout << sol.longestWord(words) << '\n';

    return 0;
}

/*
================================================================================
                    LEETCODE 720 - LONGEST WORD IN DICTIONARY
================================================================================

Problem Statement:
------------------
Given an array of strings words representing an English Dictionary, return the
longest word in words that can be built one character at a time by other words
in words.

If there are multiple possible answers with the same length, return the
lexicographically smallest one.

A word can be built one character at a time if every prefix of the word is also
present in the dictionary.

Example:
--------
Input:
words = ["w","wo","wor","worl","world","banana","ban","bana","banan"]

Output:
"world"

Explanation:
"w"      exists
"wo"     exists
"wor"    exists
"worl"   exists
"world"  exists

Therefore "world" can be built one character at a time.

Another example:
Input:
["a","banana","app","appl","ap","apply","apple"]

Output:
"apple"

Both "apple" and "apply" have the same length, but "apple" is lexicographically
smaller.


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
For every word, check whether all of its prefixes exist in the dictionary.

Example:
word = "world"

Check:
"w"     -> exists
"wo"    -> exists
"wor"   -> exists
"worl"  -> exists
"world" -> exists

If all prefixes exist, the word is a valid candidate.

Use an unordered_set for O(1) average prefix lookup.

If two valid words have the same length, choose the lexicographically smaller
one.

Pseudo Code:
-----------
put all words into a set

answer = ""

for every word:
    valid = true

    for i = 1 to word.length:
        prefix = word[0...i]

        if prefix is not in set:
            valid = false
            break

    if valid:
        if word is longer than answer:
            answer = word
        else if same length and word is lexicographically smaller:
            answer = word

return answer


Complete Brute Force Code:
--------------------------
(The following code is for revision only and is NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> st(words.begin(), words.end());

        string answer = "";

        for (const string& word : words) {
            bool valid = true;
            string prefix = "";

            for (char c : word) {
                prefix += c;

                if (!st.count(prefix)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                if (word.length() > answer.length() ||
                    (word.length() == answer.length() && word < answer)) {
                    answer = word;
                }
            }
        }

        return answer;
    }
};
*/


// Time Complexity:
// ----------------
// Let:
// N = number of words
// L = maximum word length

// For every word, we check up to L prefixes.

// Creating/checking prefixes can take O(L), so:

// O(N * L^2)

// Space Complexity:
// -----------------
// O(N * L)

// for storing all words and temporary prefixes.


// ================================================================================
// OPTIMAL APPROACH - TRIE
// ================================================================================

// Observation:
// ------------
// A word is valid only when every prefix is also a word.

// A Trie naturally represents all prefixes of words.

// For example:

// words = ["w", "wo", "wor", "worl", "world"]

// Trie:

// root
//  |
//  w *
//  |
//  o *
//  |
//  r *
//  |
//  l *
//  |
//  d *

// * = complete word

// While traversing the Trie, we are allowed to continue only through nodes that
// represent complete words.

// Therefore, if we reach "world", we know:

// "w" -> valid
// "wo" -> valid
// "wor" -> valid
// "worl" -> valid
// "world" -> valid


// Intuition:
// ----------
// 1. Insert every word into a Trie.
// 2. Mark the end of every word using isEnd = true.
// 3. Start DFS from the root.
// 4. We can move to a child only if that child represents a complete word.
// 5. Keep track of the current word.
// 6. Update the answer whenever we find a longer valid word.
// 7. Since children are visited from 'a' to 'z', lexicographically smaller words
//    are naturally considered first.

// The important condition is:

// if (!next->isEnd)
//     continue;

// This guarantees that every prefix of the selected word exists in the
// dictionary.


// Pseudo Code:
// -----------
// create Trie root

// for every word:
//     insert word into Trie

// answer = ""

// DFS(root):
//     for characters from 'a' to 'z':
//         if child does not exist:
//             continue

//         if child is not the end of a word:
//             continue

//         add character to current word

//         update answer

//         DFS(child)

//         remove character from current word

// return answer


// Complete Optimal Code:
// ----------------------
// (The following code is for revision only and is NOT executable.)

/*
#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct TrieNode {
        TrieNode* child[26];
        bool isEnd;

        TrieNode() {
            isEnd = false;
            memset(child, 0, sizeof(child));
        }
    };

    TrieNode* root = new TrieNode();

    void insert(const string& word) {
        TrieNode* curr = root;

        for (char c : word) {
            int idx = c - 'a';

            if (!curr->child[idx])
                curr->child[idx] = new TrieNode();

            curr = curr->child[idx];
        }

        curr->isEnd = true;
    }

    void dfs(TrieNode* node, string& current, string& answer) {
        for (int i = 0; i < 26; i++) {
            if (!node->child[i])
                continue;

            TrieNode* next = node->child[i];

            if (!next->isEnd)
                continue;

            current.push_back('a' + i);

            if (current.length() > answer.length())
                answer = current;

            dfs(next, current, answer);

            current.pop_back();
        }
    }

public:
    string longestWord(vector<string>& words) {
        for (const string& word : words)
            insert(word);

        string answer = "";
        string current = "";

        dfs(root, current, answer);

        return answer;
    }
};
*/


// Time Complexity:
// ----------------
// Let:
// S = total number of characters in all words.

// Building Trie:
// O(S)

// DFS:
// Each valid Trie node is visited once.
// Checking 26 children at each node gives:

// O(26 * S) = O(S)

// Overall:

// O(S)

// Space Complexity:
// -----------------
// Trie stores every character:

// O(S)

// DFS recursion:
// O(L)

// where L is the maximum word length.

// Overall:

// O(S)


// ================================================================================
// DRY RUN
// ================================================================================

// Input:
// ["w","wo","wor","worl","world","banana","ban","bana","banan"]

// Step 1: Insert all words into Trie.

// Relevant Trie paths:

// w
// |
// o
// |
// r
// |
// l
// |
// d

// and

// b
// |
// a
// |
// n
// |
// a
// |
// n
// |
// a


// Step 2: DFS starts at root.

// Children:
// 'b'
// 'w'

// We process characters from 'a' to 'z'.

// Take 'b':
// "b" is NOT a complete word.

// Therefore we cannot continue through 'b'.

// Take 'w':
// "w" IS a complete word.

// current = "w"
// answer = "w"

// Continue:

// "wo" -> complete
// answer = "wo"

// "wor" -> complete
// answer = "wor"

// "worl" -> complete
// answer = "worl"

// "world" -> complete
// answer = "world"

// Now no more children.

// Return from DFS.

// Final answer:

// "world"


// ================================================================================
// INTERVIEW NOTES
// ================================================================================

// Pattern:
// --------
// Trie + DFS

// This problem is a classic Trie problem where we need to verify that every
// prefix of a word exists.

// Key Observation:
// ----------------
// A word can be built character-by-character only if every prefix is a complete
// word.

// In a Trie, this can be checked by:

// next->isEnd

// If a Trie node is not the end of a word, we cannot continue from that node.


// Common Mistakes:
// ----------------
// 1. Forgetting to mark the end of every word using isEnd.

// 2. Traversing through a node even when it is not a complete word.

// 3. Forgetting the lexicographical tie-breaking rule.

// 4. Comparing only word lengths and ignoring lexicographical order.

// 5. Using a Trie but not understanding why incomplete prefixes must stop DFS.

// 6. Forgetting to backtrack:

//    current.push_back(...)
//    dfs(...)
//    current.pop_back(...)


// When to Use This Approach:
// --------------------------
// Use Trie when:

// - You need prefix-based searching.
// - You need to check whether prefixes exist.
// - You need autocomplete-like functionality.
// - You need to find words sharing common prefixes.
// - You need dictionary/prefix operations.
// - Problems involve "word can be formed one character at a time".

// For LeetCode 720 specifically:

// Trie + DFS is a clean optimal solution.

// Key line to remember:

// if (!next->isEnd)
//     continue;

// This ensures that every prefix is a valid dictionary word.


// ================================================================================
// FINAL COMPLEXITY
// ================================================================================

// Brute Force:
// Time  : O(N * L^2)
// Space : O(N * L)

// Optimal Trie:
// Time  : O(S)
// Space : O(S)

// where S = total number of characters in all words.


// ================================================================================
// */

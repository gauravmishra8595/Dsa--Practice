#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct TrieNode
    {
        bool endOfWord;
        string word;
        TrieNode *children[26];

        TrieNode()
        {
            endOfWord = false;
            word = "";
            for (int i = 0; i < 26; i++)
                children[i] = NULL;
        }
    };

    vector<string> ans;
    int m, n;
    vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void insert(TrieNode *root, string &word)
    {
        TrieNode *curr = root;

        for (char ch : word)
        {
            if (curr->children[ch - 'a'] == NULL)
                curr->children[ch - 'a'] = new TrieNode();

            curr = curr->children[ch - 'a'];
        }

        curr->endOfWord = true;
        curr->word = word;
    }

    void dfs(vector<vector<char>> &board, int i, int j, TrieNode *root)
    {

        if (i < 0 || i >= m || j < 0 || j >= n)
            return;

        if (board[i][j] == '$')
            return;

        if (root->children[board[i][j] - 'a'] == NULL)
            return;

        root = root->children[board[i][j] - 'a'];

        if (root->endOfWord)
        {
            ans.push_back(root->word);
            root->endOfWord = false; // avoid duplicates
        }

        char temp = board[i][j];
        board[i][j] = '$';

        for (auto &d : dir)
            dfs(board, i + d[0], j + d[1], root);

        board[i][j] = temp;
    }

    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {

        m = board.size();
        n = board[0].size();

        TrieNode *root = new TrieNode();

        for (string &word : words)
            insert(root, word);

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (root->children[board[i][j] - 'a'] != NULL)
                    dfs(board, i, j, root);
            }
        }

        return ans;
    }
};

int main()
{

    Solution obj;

    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}};

    vector<string> words = {"oath", "pea", "eat", "rain"};

    vector<string> ans = obj.findWords(board, words);

    for (string &x : ans)
        cout << x << " ";

    return 0;
}

/*

==========================================================
Problem Statement
==========================================================

LeetCode 212. Word Search II

Given an m x n board of characters and a list of words,
return all words present in the board.

Rules:
- Characters must be adjacent (up, down, left, right).
- Same cell cannot be used twice in one word.

----------------------------------------------------------

Example

Input

board =
o a a n
e t a e
i h k r
i f l v

words = ["oath","pea","eat","rain"]

Output

["oath","eat"]

==========================================================
Approach 1 : Brute Force
==========================================================

Idea
-----

For every word

Run LeetCode 79 (Word Search) independently.

If found

Store the answer.

Pseudo Code
-----------

for every word

    run DFS

    if found

        add to answer

Complete Brute Force Code
-------------------------

// vector<string> ans;
//
// for(string word:words){
//
//     if(exist(board,word))      // Leetcode 79 solution
//         ans.push_back(word);
// }
//
// return ans;

Time Complexity
---------------

Suppose

K = number of words

L = average word length

Board = M x N

Time

O(K * M * N * 4 * 3^(L-1))

Very slow for large dictionary.

Space Complexity
----------------

O(L)

==========================================================
Approach 2 : Trie + DFS + Backtracking (Optimal)
==========================================================

Observation
-----------

Many words share prefixes.

Example

eat

ear

earn

Searching separately repeats

e -> a

multiple times.

Trie stores common prefixes once.

Intuition
---------

1. Insert every word into Trie.

2. Start DFS from every board cell.

3. Move inside Trie simultaneously.

4. If current Trie node has no child

Stop immediately.

5. If endOfWord

Add answer.

6. Mark board visited.

7. Explore four directions.

8. Restore character.

Pseudo Code
-----------

Insert all words into Trie

for every cell

    DFS(i,j,root)

DFS

if invalid
    return

if child absent
    return

move Trie node

if endOfWord

    add answer

mark visited

DFS 4 directions

restore

Complete Optimal Code
---------------------

class Solution {
public:

    struct TrieNode{

        bool endOfWord;
        string word;
        TrieNode* children[26];

        TrieNode(){

            endOfWord=false;
            word="";

            for(int i=0;i<26;i++)
                children[i]=NULL;
        }
    };

    vector<string> ans;

    int m,n;

    vector<vector<int>> dir{{1,0},{-1,0},{0,1},{0,-1}};

    void insert(TrieNode* root,string &word){

        TrieNode* curr=root;

        for(char ch:word){

            if(curr->children[ch-'a']==NULL)
                curr->children[ch-'a']=new TrieNode();

            curr=curr->children[ch-'a'];
        }

        curr->endOfWord=true;
        curr->word=word;
    }

    void dfs(vector<vector<char>>& board,int i,int j,TrieNode* root){

        if(i<0 || i>=m || j<0 || j>=n)
            return;

        if(board[i][j]=='$')
            return;

        if(root->children[board[i][j]-'a']==NULL)
            return;

        root=root->children[board[i][j]-'a'];

        if(root->endOfWord){

            ans.push_back(root->word);

            root->endOfWord=false;
        }

        char temp=board[i][j];

        board[i][j]='$';

        for(auto &d:dir)

            dfs(board,i+d[0],j+d[1],root);

        board[i][j]=temp;
    }

    vector<string> findWords(vector<vector<char>>& board,
                             vector<string>& words){

        m=board.size();

        n=board[0].size();

        TrieNode* root=new TrieNode();

        for(string &word:words)

            insert(root,word);

        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                if(root->children[board[i][j]-'a'])
                    dfs(board,i,j,root);

        return ans;
    }
};

Time Complexity
---------------

Building Trie

O(total characters in all words)

Searching

O(M * N * 4 * 3^(L-1))

where

L = maximum word length

Much faster than brute force because Trie prunes
invalid prefixes immediately.

Space Complexity
----------------

Trie

O(total characters in all words)

Recursion Stack

O(L)

==========================================================
Dry Run
==========================================================

Board

o a a n

e t a e

i h k r

i f l v

Trie contains

oath

pea

eat

rain

Start from

'o'

Trie has child 'o'

↓

oa

↓

oat

↓

oath

Found

Store "oath"

Continue searching

Next

'e'

↓

ea

↓

eat

Found

Answer

["oath","eat"]

==========================================================
Interview Notes
==========================================================

Pattern
-------

Trie + DFS + Backtracking

Key Observation
---------------

Trie eliminates unnecessary DFS searches by pruning
paths whose prefixes do not exist.

Common Mistakes
---------------

1. Forgetting to restore board after DFS.

2. Using visited matrix instead of modifying board
(increases memory).

3. Forgetting to mark endOfWord=false leading to duplicates.

4. Not storing complete word in Trie.

5. Building Trie incorrectly.

When to use this approach
-------------------------

Use Trie + DFS whenever

• Multiple string searches on a grid

• Dictionary lookup

• Prefix pruning

Classic Problems

- LeetCode 212 Word Search II
- Boggle Game
- Dictionary Search
- Autocomplete
- Prefix Matching

==========================================================
Summary
==========================================================

Approach 1

Brute Force

Run Word Search (LC 79) for every word.

Time

O(K * M * N * 4 * 3^(L-1))

----------------------------------------------------------

Approach 2 (Optimal)

Trie + DFS + Backtracking

Time

O(total Trie characters + M*N*4*3^(L-1))

Preferred Interview Solution

==========================================================

*/
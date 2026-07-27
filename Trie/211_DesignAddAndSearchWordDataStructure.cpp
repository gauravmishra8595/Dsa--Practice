#include <bits/stdc++.h>
using namespace std;

class WordDictionary
{
    struct TrieNode
    {
        TrieNode *child[26];
        bool isEnd;

        TrieNode()
        {
            isEnd = false;
            for (int i = 0; i < 26; i++)
                child[i] = nullptr;
        }
    };

    TrieNode *root;

    bool dfs(string &word, int idx, TrieNode *node)
    {
        if (node == nullptr)
            return false;

        if (idx == word.size())
            return node->isEnd;

        if (word[idx] == '.')
        {
            for (int i = 0; i < 26; i++)
            {
                if (dfs(word, idx + 1, node->child[i]))
                    return true;
            }
            return false;
        }

        return dfs(word, idx + 1, node->child[word[idx] - 'a']);
    }

public:
    WordDictionary()
    {
        root = new TrieNode();
    }

    void addWord(string word)
    {
        TrieNode *cur = root;

        for (char ch : word)
        {
            int idx = ch - 'a';
            if (cur->child[idx] == nullptr)
                cur->child[idx] = new TrieNode();
            cur = cur->child[idx];
        }

        cur->isEnd = true;
    }

    bool search(string word)
    {
        return dfs(word, 0, root);
    }
};

int main()
{

    WordDictionary obj;

    obj.addWord("bad");
    obj.addWord("dad");
    obj.addWord("mad");

    cout << boolalpha;

    cout << obj.search("pad") << endl; // false
    cout << obj.search("bad") << endl; // true
    cout << obj.search(".ad") << endl; // true
    cout << obj.search("b..") << endl; // true

    return 0;
}

/*

=========================================================
LeetCode 211. Design Add and Search Words Data Structure
=========================================================

---------------------------------------------------------
Problem Statement
---------------------------------------------------------
Design a data structure that supports adding new words and
finding if a string matches any previously added string.

Implement:

1. WordDictionary()
2. addWord(word)
3. search(word)

search() may contain '.' wildcard.

'.' matches any one lowercase English letter.

---------------------------------------------------------
Example
---------------------------------------------------------

Input:

addWord("bad")
addWord("dad")
addWord("mad")

search("pad")
search("bad")
search(".ad")
search("b..")

Output:

false
true
true
true

---------------------------------------------------------
Approach 1 : Brute Force (Store all words)
---------------------------------------------------------

Idea
-----
Store every inserted word inside a vector.

For searching:

If lengths differ -> skip.

Otherwise compare character by character.

'.' matches every character.

Pseudo Code
------------

vector<string> words

addWord(word):
    words.push_back(word)

search(word):
    for every storedWord
        if lengths differ
            continue

        match=true

        for every character
            if query[i]=='.'
                continue

            if query[i]!=storedWord[i]
                match=false
                break

        if match
            return true

    return false

Complete Brute Force Code
-------------------------

class WordDictionary {
    vector<string> words;

public:

    void addWord(string word){
        words.push_back(word);
    }

    bool search(string word){

        for(string s:words){

            if(s.size()!=word.size())
                continue;

            bool ok=true;

            for(int i=0;i<s.size();i++){

                if(word[i]=='.')
                    continue;

                if(word[i]!=s[i]){
                    ok=false;
                    break;
                }
            }

            if(ok)
                return true;
        }

        return false;
    }
};

Time Complexity
----------------

addWord : O(1)

search :
O(N * L)

N = number of words
L = average length

Space Complexity
-----------------

O(total words)

---------------------------------------------------------
Approach 2 : Trie + DFS (Optimal)
---------------------------------------------------------

Observation
------------

Many words share common prefixes.

Trie stores prefixes efficiently.

When '.' occurs, we only need to explore all possible
children from current node.

Intuition
----------

Trie allows:

Insertion in O(L)

Normal search in O(L)

Wildcard handled using DFS.

Whenever '.' appears

Try all 26 children.

If any returns true

Answer is true.

Pseudo Code
------------

Node

children[26]

isEnd

addWord(word)

node=root

for character

create node if absent

move

mark end

DFS(word,index,node)

if node==NULL

false

if index==word length

return isEnd

if current=='.'

for all 26 children

if dfs(child)

return true

return false

else

go to required child

search(word)

return dfs(root)

Complete Optimal Code
----------------------

class WordDictionary {

    struct TrieNode{

        TrieNode* child[26];
        bool isEnd;

        TrieNode(){

            isEnd=false;

            for(int i=0;i<26;i++)
                child[i]=NULL;
        }
    };

    TrieNode* root;

    bool dfs(string &word,int idx,TrieNode* node){

        if(node==NULL)
            return false;

        if(idx==word.size())
            return node->isEnd;

        if(word[idx]=='.'){

            for(int i=0;i<26;i++){

                if(dfs(word,idx+1,node->child[i]))
                    return true;
            }

            return false;
        }

        return dfs(word,
                   idx+1,
                   node->child[word[idx]-'a']);
    }

public:

    WordDictionary(){
        root=new TrieNode();
    }

    void addWord(string word){

        TrieNode* cur=root;

        for(char ch:word){

            int id=ch-'a';

            if(cur->child[id]==NULL)
                cur->child[id]=new TrieNode();

            cur=cur->child[id];
        }

        cur->isEnd=true;
    }

    bool search(string word){

        return dfs(word,0,root);
    }
};

Time Complexity
----------------

addWord :

O(L)

search :

Best Case :

O(L)

Worst Case :

O(26^k * L)

k = number of '.' wildcards

In practice, much faster because DFS only explores existing
Trie branches.

Space Complexity
-----------------

Trie Storage

O(total characters inserted)

Recursive Stack

O(L)

---------------------------------------------------------
Dry Run
---------------------------------------------------------

Insert

bad

dad

mad

Trie

(root)

  |
  b
   |
   a
    |
    d*

  d
   |
   a
    |
    d*

  m
   |
   a
    |
    d*

Search ".ad"

index=0

'.'

Try

b

DFS

a

DFS

d

End

Found

Return true

Search "b.."

b

.

Try a

.

Try d

End reached

true

---------------------------------------------------------
Interview Notes
---------------------------------------------------------

Pattern
--------

Trie + DFS / Backtracking

Key Observation
----------------

Trie compresses common prefixes.

'.' means branching to every existing child.

Common Mistakes
----------------

1. Forget NULL check.

2. Returning false immediately after checking first child.

3. Forgetting isEnd check.

4. Using BFS instead of recursive DFS.

5. Not handling "." correctly.

When to use this approach
--------------------------

Whenever:

✔ Dictionary operations

✔ Prefix searching

✔ Wildcard matching

✔ Autocomplete

✔ Word Search problems

✔ Prefix based queries

---------------------------------------------------------
Approach Comparison
---------------------------------------------------------

1. Vector + Linear Scan

Insertion:
O(1)

Search:
O(N*L)

Space:
O(total words)

Suitable for very small input.

--------------------------------

2. Trie + DFS (Optimal)

Insertion:
O(L)

Search:
O(L) normal

Worst:
O(26^k * L)

Space:
O(total characters)

Best choice for repeated queries.

*/
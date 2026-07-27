#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------
// Optimal Solution (Trie / Prefix Tree)
// Time Complexity:
// insert  -> O(L)
// search  -> O(L)
// startsWith -> O(L)
// Space Complexity: O(Total Characters)
// ---------------------------------------------------------

class TrieNode
{
public:
    TrieNode *child[26];
    bool isEnd;

    TrieNode()
    {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            child[i] = NULL;
    }
};

class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(string word)
    {
        TrieNode *node = root;

        for (char ch : word)
        {
            int idx = ch - 'a';

            if (node->child[idx] == NULL)
                node->child[idx] = new TrieNode();

            node = node->child[idx];
        }

        node->isEnd = true;
    }

    bool search(string word)
    {
        TrieNode *node = root;

        for (char ch : word)
        {
            int idx = ch - 'a';

            if (node->child[idx] == NULL)
                return false;

            node = node->child[idx];
        }

        return node->isEnd;
    }

    bool startsWith(string prefix)
    {
        TrieNode *node = root;

        for (char ch : prefix)
        {
            int idx = ch - 'a';

            if (node->child[idx] == NULL)
                return false;

            node = node->child[idx];
        }

        return true;
    }
};

int main()
{

    Trie trie;

    trie.insert("apple");

    cout << trie.search("apple") << endl;   // 1
    cout << trie.search("app") << endl;     // 0
    cout << trie.startsWith("app") << endl; // 1

    trie.insert("app");

    cout << trie.search("app") << endl; // 1

    return 0;
}

/*

============================================================
                LEETCODE 208
          Implement Trie (Prefix Tree)
============================================================

------------------------------------------------------------
Problem Statement
------------------------------------------------------------

Implement a Trie (Prefix Tree).

Functions:

1. Trie()

2. insert(word)

3. search(word)

4. startsWith(prefix)

------------------------------------------------------------
Example
------------------------------------------------------------

Input

Trie
insert("apple")
search("apple")
search("app")
startsWith("app")
insert("app")
search("app")

Output

null
null
true
false
true
null
true

------------------------------------------------------------
Approach 1 : Brute Force (Vector of Strings)
------------------------------------------------------------

Idea
-----

Store every inserted word inside a vector.

For search:
    Compare every string.

For startsWith:
    Check prefix with every string.

Pseudo Code
------------

vector<string> words

insert(word)
    push_back(word)

search(word)
    for every string
        if string == word
            return true
    return false

startsWith(prefix)

    for every string

        if string starts with prefix

            return true

    return false

Complete Brute Force Code
-------------------------

class Trie {

    vector<string> words;

public:

    Trie() {}

    void insert(string word){
        words.push_back(word);
    }

    bool search(string word){

        for(string s : words)
            if(s==word)
                return true;

        return false;
    }

    bool startsWith(string prefix){

        for(string s : words){

            if(s.substr(0,prefix.size())==prefix)
                return true;

        }

        return false;
    }
};

Time Complexity
---------------

insert       O(1)

search       O(N*L)

startsWith   O(N*L)

N = Number of words

L = Average length

Space Complexity
----------------

O(N*L)

============================================================
Approach 2 : Optimal (Trie / Prefix Tree)
============================================================

Observation
-----------

Many words share common prefixes.

Example

apple

app

application

apt

The prefix "app" should not be stored multiple times.

Trie stores shared prefixes efficiently.

------------------------------------------------------------
Intuition
------------------------------------------------------------

Each node stores

26 pointers
isEnd flag

Insert

Go character by character.

Create node if absent.

Move ahead.

Mark last node as end.

Search

Traverse characters.

If any node missing

return false

After traversal

return isEnd

startsWith

Same traversal

No need to check isEnd.

------------------------------------------------------------
Pseudo Code
------------------------------------------------------------

insert(word)

node = root

for character

    if child absent

        create child

    move child

mark end

--------------------------------

search(word)

node=root

for character

    if child absent

        return false

    move child

return node->isEnd

--------------------------------

startsWith(prefix)

node=root

for character

    if child absent

        return false

    move child

return true

------------------------------------------------------------
Complete Optimal Code
------------------------------------------------------------

class TrieNode{

public:

    TrieNode* child[26];

    bool isEnd;

    TrieNode(){

        isEnd=false;

        for(int i=0;i<26;i++)
            child[i]=NULL;
    }
};

class Trie {

    TrieNode* root;

public:

    Trie(){

        root=new TrieNode();
    }

    void insert(string word){

        TrieNode* node=root;

        for(char ch:word){

            int idx=ch-'a';

            if(node->child[idx]==NULL)
                node->child[idx]=new TrieNode();

            node=node->child[idx];
        }

        node->isEnd=true;
    }

    bool search(string word){

        TrieNode* node=root;

        for(char ch:word){

            int idx=ch-'a';

            if(node->child[idx]==NULL)
                return false;

            node=node->child[idx];
        }

        return node->isEnd;
    }

    bool startsWith(string prefix){

        TrieNode* node=root;

        for(char ch:prefix){

            int idx=ch-'a';

            if(node->child[idx]==NULL)
                return false;

            node=node->child[idx];
        }

        return true;
    }
};

------------------------------------------------------------
Time Complexity
------------------------------------------------------------

Insert

O(L)

Search

O(L)

StartsWith

O(L)

L = Length of string

------------------------------------------------------------
Space Complexity
------------------------------------------------------------

O(Total Characters Inserted)

============================================================
Dry Run
============================================================

Insert

apple

Root

|

a

|

p

|

p

|

l

|

e(end)

--------------------------------

search("apple")

root

↓

a

↓

p

↓

p

↓

l

↓

e(end)

Return true

--------------------------------

search("app")

Reach second 'p'

isEnd == false

Return false

--------------------------------

insert("app")

Mark second 'p' as end

Now

search("app")

Return true

============================================================
Interview Notes
============================================================

Pattern
-------

✔ Trie
✔ Prefix Search
✔ String Processing
✔ Design Data Structure

------------------------------------------------------------

Key Observation
---------------

Instead of storing complete words separately,

Store characters as nodes.

Common prefixes share memory.

------------------------------------------------------------

Common Mistakes
---------------

1. Forgetting to initialize child pointers.

2. Forgetting to mark isEnd=true.

3. Returning true after traversal in search()
   without checking isEnd.

4. Confusing search() with startsWith().

------------------------------------------------------------

When to use Trie
----------------

Whenever problems involve

✔ Prefix Matching

✔ Dictionary

✔ Auto Complete

✔ Search Suggestions

✔ Spell Checker

✔ Word Search

✔ Longest Prefix

✔ XOR Trie (Binary Trie)

============================================================*/

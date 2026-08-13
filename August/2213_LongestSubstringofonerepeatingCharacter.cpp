#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    struct Node
    {
        char lc, rc;
        int pref, suff, best, len;

        Node(char c = '#', int l = 0)
            : lc(c), rc(c), pref(l), suff(l), best(l), len(l) {}
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b)
    {
        if (a.len == 0)
            return b;
        if (b.len == 0)
            return a;

        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pref = a.pref;
        if (a.pref == a.len && a.rc == b.lc)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.rc == b.lc)
            res.suff = b.len + a.suff;

        res.best = max(a.best, b.best);
        if (a.rc == b.lc)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int node, int l, int r)
    {
        if (l == r)
        {
            tree[node] = Node(s[l], 1);
            return;
        }

        int mid = (l + r) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, char c)
    {
        if (l == r)
        {
            tree[node] = Node(c, 1);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * node, l, mid, idx, c);
        else
            update(2 * node + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    SegmentTree(const string &str)
    {
        s = str;
        tree.resize(4 * s.size() + 5);
        build(1, 0, s.size() - 1);
    }

    void update(int idx, char c)
    {
        update(1, 0, s.size() - 1, idx, c);
    }

    int getBest()
    {
        return tree[1].best;
    }
};

class Solution
{
public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int> &queryIndices)
    {
        SegmentTree st(s);
        vector<int> ans;

        for (int i = 0; i < (int)queryIndices.size(); i++)
        {
            st.update(queryIndices[i], queryCharacters[i]);
            ans.push_back(st.getBest());
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    string s = "babacc";
    string queryCharacters = "bcb";
    vector<int> queryIndices = {1, 3, 3};

    vector<int> ans =
        sol.longestRepeating(s, queryCharacters, queryIndices);

    for (int x : ans)
        cout << x << ' ';

    cout << '\n';

    return 0;
}

/*
================================================================================
                        LEETCODE 2213
              Longest Substring of One Repeating Character
================================================================================

Problem Statement:
------------------
You are given a string s consisting of lowercase English letters.

You are also given:
    queryCharacters[i]
    queryIndices[i]

For every query i:
    - Change s[queryIndices[i]] to queryCharacters[i].
    - Return the length of the longest substring containing only one
      repeating character.

Return the answer after every query.

Example:
--------
Input:
    s = "babacc"
    queryCharacters = "bcb"
    queryIndices = [1, 3, 3]

Output:
    [3, 3, 3]

Explanation:
    Initial string: babacc

    Query 1:
        index 1 -> 'b'
        String = bbbacc
        Longest repeating substring = "bbb"
        Answer = 3

    Query 2:
        index 3 -> 'c'
        String = bbbccc
        Longest repeating substring = "bbb" or "ccc"
        Answer = 3

    Query 3:
        index 3 -> 'b'
        String = bbbbcc
        Longest repeating substring = "bbbb"
        Answer = 4

    Note:
    The official LeetCode example may use a different query sequence;
    the notebook implementation follows the given problem definition.


Brute Force Approach:
---------------------

Idea:
-----
For every query:
    1. Modify the character.
    2. Traverse the entire string.
    3. Find the longest consecutive sequence of equal characters.

Since the whole string can be scanned after every update, this is simple
but inefficient for large constraints.


Pseudo Code:
------------
function longestRepeating(s, queryCharacters, queryIndices):

    answer = []

    for every query i:
        s[queryIndices[i]] = queryCharacters[i]

        current = 1
        best = 1

        for j = 1 to n - 1:
            if s[j] == s[j - 1]:
                current++
            else:
                current = 1

            best = max(best, current)

        answer.push_back(best)

    return answer


Complete Brute Force Code:
--------------------------

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {

        vector<int> ans;
        int n = s.size();

        for (int i = 0; i < queryIndices.size(); i++) {

            s[queryIndices[i]] = queryCharacters[i];

            int current = 1;
            int best = 1;

            for (int j = 1; j < n; j++) {

                if (s[j] == s[j - 1])
                    current++;
                else
                    current = 1;

                best = max(best, current);
            }

            ans.push_back(best);
        }

        return ans;
    }
};


Time Complexity:
----------------
For each query:
    O(n)

For q queries:
    O(n * q)

Space Complexity:
-----------------
O(1) extra space, excluding the answer array.


Optimal Approach:
-----------------

Observation:
------------
A query changes only ONE character.

Therefore, recomputing the longest repeating substring over the entire
string after every update is unnecessary.

We need a data structure that supports:

    1. Point Update
    2. Query maximum consecutive equal-character segment

A Segment Tree is ideal for this.


Intuition:
----------
For every segment of the string, store:

    lc   = first character of the segment
    rc   = last character of the segment
    pref = longest repeating prefix
    suff = longest repeating suffix
    best = longest repeating substring inside the segment
    len  = length of the segment

Suppose we merge two segments:

    Left | Right

The answer can come from:

    1. Completely inside Left
    2. Completely inside Right
    3. Crossing the boundary

A crossing substring is possible only when:

    Left.rc == Right.lc

Then:

    crossing length = Left.suff + Right.pref

For the prefix:
    If the entire Left segment is the same character and its last
    character equals Right's first character, Left.pref can be extended
    using Right.pref.

Similarly for the suffix.


Pseudo Code:
------------
build(node, l, r):

    if l == r:
        create leaf node
        return

    build(left child)
    build(right child)

    tree[node] = merge(left child, right child)


merge(A, B):

    result.len = A.len + B.len
    result.lc = A.lc
    result.rc = B.rc

    result.pref = A.pref

    if A.pref == A.len AND A.rc == B.lc:
        result.pref = A.len + B.pref

    result.suff = B.suff

    if B.suff == B.len AND A.rc == B.lc:
        result.suff = B.len + A.suff

    result.best = max(A.best, B.best)

    if A.rc == B.lc:
        result.best = max(result.best, A.suff + B.pref)

    return result


update(node, l, r, index, character):

    if l == r:
        replace leaf with new character
        return

    if index is in left half:
        update(left child)
    else:
        update(right child)

    tree[node] = merge(left child, right child)


For every query:

    update(index, character)
    answer = tree[1].best


Complete Optimal Code:
----------------------

class SegmentTree {
    struct Node {
        char lc, rc;
        int pref, suff, best, len;

        Node(char c = '#', int l = 0)
            : lc(c), rc(c), pref(l), suff(l), best(l), len(l) {}
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pref = a.pref;
        if (a.pref == a.len && a.rc == b.lc)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.rc == b.lc)
            res.suff = b.len + a.suff;

        res.best = max(a.best, b.best);

        if (a.rc == b.lc)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = Node(s[l], 1);
            return;
        }

        int mid = (l + r) / 2;

        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            tree[node] = Node(c, 1);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * node, l, mid, idx, c);
        else
            update(2 * node + 1, mid + 1, r, idx, c);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    SegmentTree(const string& str) {
        s = str;
        tree.resize(4 * s.size() + 5);
        build(1, 0, s.size() - 1);
    }

    void update(int idx, char c) {
        update(1, 0, s.size() - 1, idx, c);
    }

    int getBest() {
        return tree[1].best;
    }
};


class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {

        SegmentTree st(s);
        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {

            st.update(queryIndices[i], queryCharacters[i]);
            ans.push_back(st.getBest());
        }

        return ans;
    }
};


Time Complexity:
----------------
Building Segment Tree:
    O(n)

Each point update:
    O(log n)

For q queries:
    O(q log n)

Total:
    O(n + q log n)

Space Complexity:
-----------------
Segment Tree:
    O(n)

Answer array:
    O(q)

Total:
    O(n + q)


Dry Run with Example:
---------------------

s = "babacc"

Represent the string as:

    b a b a c c
    0 1 2 3 4 5

Initial longest repeating substring:

    "bb" does not exist
    "aa" does not exist
    "cc" exists

So:
    best = 2


Suppose query:
    index = 1
    character = 'b'

String becomes:

    b b b a c c
    -------
      "bbb"

Segment Tree updates only the path containing index 1.

The nodes on that path are recalculated.

Root now stores:

    best = 3

Next query:
    index = 3
    character = 'c'

String becomes:

    b b b c c c
    -----------
       "bbbccc"

The root combines the left and right segments.

The maximum is:

    max("bbb", "ccc") = 3

Therefore:
    best = 3


Interview Notes:
----------------

Pattern:
    Segment Tree + Point Update + Range Aggregation


Key Observation:
    Store enough information at every segment so that two adjacent
    segments can be merged in O(1).

    The important four values are:

        prefix
        suffix
        best
        boundary characters

    The boundary characters tell us whether the suffix of the left
    segment can connect with the prefix of the right segment.


Common Mistakes:
----------------
1. Recomputing the complete string after every update.
   This leads to O(nq).

2. Storing only the maximum answer in a segment.
   That is insufficient because two segments can form a larger answer
   across their boundary.

3. Forgetting prefix/suffix merging.

4. Forgetting to check:
       left.rightCharacter == right.leftCharacter

5. Confusing substring with subsequence.
   We need a CONTIGUOUS substring.

6. Updating only the leaf without recalculating its ancestors.

7. Forgetting that the query asks for the answer AFTER each update.


When to use this approach:
--------------------------
Use this Segment Tree pattern when:

    - There are many point updates.
    - We need an answer after every update.
    - The answer depends on adjacent elements.
    - A segment can be summarized using a small fixed amount of data.
    - Two summaries can be merged in O(1).

This pattern is especially useful for problems involving:

    - Longest consecutive equal elements
    - Longest prefix/suffix properties
    - Maximum subarray-like problems
    - Range queries with point updates
    - String queries where adjacency matters

================================================================================
*/

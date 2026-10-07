#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<string> removeInvalidParentheses(string s)
    {
        int leftRemove = 0, rightRemove = 0;

        // Find the minimum number of '(' and ')' to remove.
        for (char c : s)
        {
            if (c == '(')
            {
                leftRemove++;
            }
            else if (c == ')')
            {
                if (leftRemove > 0)
                    leftRemove--;
                else
                    rightRemove++;
            }
        }

        unordered_set<string> ans;
        function<void(int, int, int, string &)> dfs =
            [&](int index, int leftRem, int rightRem, string &path)
        {
            if (index == (int)s.size())
            {
                if (leftRem == 0 && rightRem == 0)
                {
                    ans.insert(path);
                }
                return;
            }

            char c = s[index];

            // Remove current parenthesis.
            if (c == '(' && leftRem > 0)
            {
                dfs(index + 1, leftRem - 1, rightRem, path);
            }

            if (c == ')' && rightRem > 0)
            {
                dfs(index + 1, leftRem, rightRem - 1, path);
            }

            // Keep current character.
            if (c == '(')
            {
                path.push_back(c);
                dfs(index + 1, leftRem, rightRem, path);
                path.pop_back();
            }
            else if (c == ')')
            {
                // Only keep ')' if it can be matched.
                int open = 0;
                for (char x : path)
                {
                    if (x == '(')
                        open++;
                    else if (x == ')')
                        open--;
                }

                if (open > 0)
                {
                    path.push_back(c);
                    dfs(index + 1, leftRem, rightRem, path);
                    path.pop_back();
                }
            }
            else
            {
                path.push_back(c);
                dfs(index + 1, leftRem, rightRem, path);
                path.pop_back();
            }
        };

        string path;
        dfs(0, leftRemove, rightRemove, path);

        return vector<string>(ans.begin(), ans.end());
    }
};

int main()
{
    Solution sol;

    string s = "()())()";
    vector<string> ans = sol.removeInvalidParentheses(s);

    for (const string &x : ans)
        cout << x << '\n';

    return 0;
}

/*
================================================================================
                        LEETCODE 301 - REMOVE INVALID PARENTHESES
================================================================================

Problem Statement:
------------------
Given a string s containing parentheses and letters, remove the minimum number
of invalid parentheses so that the resulting string is valid.

Return all possible results. The answer can be returned in any order.

A valid parentheses string:
1. Has balanced '(' and ')'.
2. At every prefix, the number of ')' must not exceed the number of '('.

Example:
--------
Input:
    s = "()())()"

Output:
    ["(())()", "()()()"]

Both strings are valid and require removing exactly one ')'.

Another example:
    s = "(a)())()"

Possible output:
    ["(a())()", "(a)()()"]


================================================================================
BRUTE FORCE APPROACH
================================================================================

Idea:
-----
Try removing every possible subset of parentheses.

For every generated string:
1. Check whether it is valid.
2. Track the minimum number of removals.
3. Store all valid strings having that minimum.

This works because we explore every possibility, but it is extremely expensive.

Pseudo Code:
------------
function solve(s):
    ans = empty set
    minRemove = infinity

    generate all subsets of characters:
        if resulting string is valid:
            removals = n - length(result)

            if removals < minRemove:
                clear ans
                minRemove = removals

            if removals == minRemove:
                add result to ans

    return ans


Complete Brute Force Code:
---------------------------

class Solution {
public:
    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(')
                balance++;
            else if (c == ')') {
                balance--;
                if (balance < 0)
                    return false;
            }
        }

        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> all;

        int n = s.size();

        // Generate all subsequences.
        for (int mask = 0; mask < (1 << n); mask++) {
            string cur;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i))
                    cur += s[i];
            }

            if (isValid(cur))
                all.insert(cur);
        }

        int maxLen = 0;
        for (auto &x : all)
            maxLen = max(maxLen, (int)x.size());

        vector<string> ans;

        for (auto &x : all) {
            if ((int)x.size() == maxLen)
                ans.push_back(x);
        }

        return ans;
    }
};

Time Complexity:
----------------
O(2^n * n)

There are 2^n subsequences and checking each one can take O(n).

Space Complexity:
-----------------
O(2^n * n)

We may store up to O(2^n) generated strings.


================================================================================
OPTIMAL APPROACH
================================================================================

Observation:
------------
We do NOT need to try arbitrary numbers of removals.

First calculate exactly how many '(' and ')' must be removed.

Example:
    "())"

Process:
    '(' -> balance = 1
    ')' -> balance = 0
    ')' -> unmatched ')'

Therefore:
    leftRemove = 0
    rightRemove = 1

Any valid answer must remove exactly one ')'.

Intuition:
----------
Use DFS/backtracking.

At every character:
1. Remove it if it is an invalid parenthesis that we still need to remove.
2. Keep it and continue.
3. For ')', keep it only when there is an unmatched '(' available.

Characters other than parentheses are always kept.

The number of removals is fixed beforehand, so every generated answer uses
the minimum possible number of deletions.

An unordered_set removes duplicate answers automatically.

Pseudo Code:
------------
1. Count:
       leftRemove = extra '('
       rightRemove = extra ')'

2. DFS(index, leftRemove, rightRemove, path)

3. If index == n:
       if leftRemove == 0 and rightRemove == 0:
           add path to answer

4. If current character is '(':
       Option 1: remove it if leftRemove > 0
       Option 2: keep it

5. If current character is ')':
       Option 1: remove it if rightRemove > 0
       Option 2: keep it only if path currently has an unmatched '('

6. If current character is a letter:
       Always keep it.

7. Return all unique answers.


Complete Optimal Code:
----------------------

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int leftRemove = 0, rightRemove = 0;

        for (char c : s) {
            if (c == '(') {
                leftRemove++;
            } else if (c == ')') {
                if (leftRemove > 0)
                    leftRemove--;
                else
                    rightRemove++;
            }
        }

        unordered_set<string> ans;

        function<void(int, int, int, int, string&)> dfs =
            [&](int index, int leftRem, int rightRem,
                int balance, string& path) {

            if (index == (int)s.size()) {
                if (leftRem == 0 && rightRem == 0 && balance == 0)
                    ans.insert(path);
                return;
            }

            char c = s[index];

            // Remove current '('.
            if (c == '(' && leftRem > 0) {
                dfs(index + 1, leftRem - 1, rightRem,
                    balance, path);
            }

            // Remove current ')'.
            if (c == ')' && rightRem > 0) {
                dfs(index + 1, leftRem, rightRem - 1,
                    balance, path);
            }

            // Keep current character.
            if (c == '(') {
                path.push_back(c);

                dfs(index + 1, leftRem, rightRem,
                    balance + 1, path);

                path.pop_back();
            }
            else if (c == ')') {
                if (balance > 0) {
                    path.push_back(c);

                    dfs(index + 1, leftRem, rightRem,
                        balance - 1, path);

                    path.pop_back();
                }
            }
            else {
                path.push_back(c);

                dfs(index + 1, leftRem, rightRem,
                    balance, path);

                path.pop_back();
            }
        };

        string path;
        dfs(0, leftRemove, rightRemove, 0, path);

        return vector<string>(ans.begin(), ans.end());
    }
};

Time Complexity:
----------------
Worst case: O(2^n * n)

The DFS can still explore exponentially many possibilities, while constructing
or storing strings can take O(n).

In practice, calculating the exact number of removals and pruning invalid ')'
makes this much faster than brute force.

Space Complexity:
-----------------
O(2^n * n)

The answer set can contain exponentially many strings, each of length O(n).

Recursion stack:
    O(n)


================================================================================
DRY RUN
================================================================================

Input:
    s = "()())()"

Step 1: Calculate removals.

Characters:
    ( -> leftRemove = 1
    ) -> leftRemove = 0
    ( -> leftRemove = 1
    ) -> leftRemove = 0
    ) -> rightRemove = 1
    ( -> leftRemove = 1
    ) -> leftRemove = 0

Therefore:
    leftRemove  = 0
    rightRemove = 1

So exactly one ')' must be removed.

DFS explores choices.

One valid path:
    ()())()
       ^
       Remove this ')'

Result:
    ()()()

Another valid path:
    ()())()
      ^
      Remove this ')'

Result:
    (())()

Both:
    "()()()"
    "(())()"

are valid and use exactly one removal.

Therefore the answer is:
    ["()()()", "(())()"]

Order does not matter.


================================================================================
INTERVIEW NOTES
================================================================================

Pattern:
--------
Backtracking + Pruning + Exact Removal Count.

Key Observation:
----------------
First determine the minimum number of '(' and ')' that must be removed.

Then DFS only considers those required removals.

For ')', it can be kept only when there is an unmatched '(' available.

This guarantees that no generated result contains an invalid prefix.

Common Mistakes:
----------------
1. Generating every possible string without calculating the required removals.

2. Keeping ')' when balance == 0.
   This creates an invalid prefix.

3. Forgetting that duplicate results are possible.
   Use unordered_set or duplicate-skipping logic.

4. Removing more parentheses than necessary.

5. Checking validity only at the end without pruning invalid prefixes.

6. Forgetting to verify:
       leftRemove == 0
       rightRemove == 0
       balance == 0
   at the end of DFS.

7. Accidentally removing letters.
   Only parentheses are candidates for removal.

When to Use This Approach:
--------------------------
Use this approach when:
- The problem asks for ALL valid strings.
- We need the minimum number of deletions.
- We have a small enough input for backtracking.
- Invalid partial states can be pruned early.
- Duplicate generated states need to be handled.

Core Template:
--------------
1. Find the exact number of invalid elements to remove.
2. Backtrack over keep/remove choices.
3. Prune impossible states early.
4. Store unique valid answers.

For LeetCode 301, the main idea is:

    "Calculate minimum removals first,
     then backtrack only over those removals."

================================================================================
*/

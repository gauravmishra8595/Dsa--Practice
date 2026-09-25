#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<string> multiply(vector<string> &a, vector<string> &b)
    {
        if (a.empty())
            return b;
        if (b.empty())
            return a;

        vector<string> ans;

        for (auto &i : a)
        {
            for (auto &j : b)
            {
                ans.push_back(i + j);
            }
        }

        return ans;
    }

    vector<string> braceExpansionII(string expression)
    {

        vector<string> res, curr;

        stack<vector<string>> st;

        for (char x : expression)
        {

            // Normal lowercase character
            if (x >= 'a' && x <= 'z')
            {

                if (!curr.empty())
                {

                    for (auto &i : curr)
                    {
                        i += x;
                    }
                }
                else
                {

                    curr.push_back(string(1, x));
                }
            }

            // Opening brace
            else if (x == '{')
            {

                // Save the previous expression state
                st.push(res);
                st.push(curr);

                res.clear();
                curr.clear();
            }

            // Closing brace
            else if (x == '}')
            {

                // Get curr from before '{'
                vector<string> preCurr = st.top();
                st.pop();

                // Get res from before '{'
                vector<string> preRes = st.top();
                st.pop();

                // Move current possibilities into res
                for (auto &i : curr)
                {
                    res.push_back(i);
                }

                // Concatenate previous expression with
                // the current brace expression
                curr = multiply(preCurr, res);

                // Restore previous union result
                res = preRes;
            }

            // Comma means union
            else if (x == ',')
            {

                // Add current possibilities to res
                for (auto &i : curr)
                {
                    res.push_back(i);
                }

                // Start a new alternative
                curr.clear();
            }
        }

        // Add remaining possibilities
        for (auto &i : curr)
        {
            res.push_back(i);
        }

        // Sort for lexicographical order
        sort(res.begin(), res.end());

        // Remove duplicates
        res.erase(unique(res.begin(), res.end()), res.end());

        return res;
    }
};

int main()
{

    Solution sol;

    string expression;

    cout << "Enter expression: ";
    cin >> expression;

    vector<string> ans = sol.braceExpansionII(expression);

    cout << "Output: [";

    for (int i = 0; i < ans.size(); i++)
    {
        cout << "\"" << ans[i] << "\"";

        if (i + 1 < ans.size())
        {
            cout << ", ";
        }
    }

    cout << "]\n";

    return 0;
}

/*
======================================================================
                    LEETCODE 1096
                 BRACE EXPANSION II
======================================================================

PROBLEM STATEMENT
-----------------

Given a string expression containing:

    - lowercase English letters
    - '{'
    - '}'
    - ','

Generate all possible strings represented by the expression.

Rules:

    1. Comma represents UNION.

       {a,b}

       -> a, b


    2. Adjacent expressions represent CONCATENATION.

       {a,b}{c,d}

       -> ac, ad, bc, bd


    3. Nested braces are allowed.


Example:
--------

Input:

    {a,b}{c,{d,e}}

Output:

    ["ac","ad","ae","bc","bd","be"]


======================================================================
BRUTE FORCE APPROACH
======================================================================

Idea:
-----

Replace every brace expression with all possible choices.

For example:

    {a,b}c

can become:

    ac
    bc

For nested expressions, recursively expand them.

This approach repeatedly creates new expressions and can perform
a lot of unnecessary work.


Pseudo Code:
------------

function solve(expression):

    find an opening brace

    if there is no brace:
        return expression

    find matching closing brace

    extract everything inside braces

    split by comma

    for every choice:

        replace braces with choice

        recursively solve

    remove duplicates

    return answer


Complete Brute Force Code:
---------------------------

class Solution {
public:

    vector<string> brute(string s) {

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '{') {

                int j = i;
                int balance = 0;

                while (j < s.size()) {

                    if (s[j] == '{')
                        balance++;

                    else if (s[j] == '}')
                        balance--;

                    if (balance == 0)
                        break;

                    j++;
                }

                string inside =
                    s.substr(i + 1, j - i - 1);

                vector<string> options;
                string curr;

                for (char c : inside) {

                    if (c == ',') {
                        options.push_back(curr);
                        curr.clear();
                    }
                    else {
                        curr += c;
                    }
                }

                options.push_back(curr);

                set<string> ans;

                for (string option : options) {

                    string next =
                        s.substr(0, i) +
                        option +
                        s.substr(j + 1);

                    vector<string> temp =
                        brute(next);

                    for (string x : temp) {
                        ans.insert(x);
                    }
                }

                return vector<string>(
                    ans.begin(),
                    ans.end()
                );
            }
        }

        return {s};
    }

    vector<string> braceExpansionII(string expression) {
        return brute(expression);
    }
};


Time Complexity:
----------------

Can become exponential because every alternative may generate
multiple complete expressions.

If K final strings are generated and each has length L:

    Approximately O(K * L)

plus the cost of constructing intermediate expressions.


Space Complexity:
-----------------

    O(K * L)

for storing generated strings.


======================================================================
OPTIMAL APPROACH
======================================================================

Observation:
------------

There are two main operations.

1. UNION

       {a,b}

       -> {"a", "b"}


2. CONCATENATION

       {a,b}{c,d}

       -> {"ac", "ad", "bc", "bd"}


Therefore:

    ','       -> UNION
    adjacency -> CONCATENATION
    '{'       -> start nested expression
    '}'       -> finish nested expression


Intuition:
----------

We maintain:

    curr
        Current strings being concatenated.

    res
        Current UNION result.


Example:

    {a,b}

After reading 'a':

    curr = {"a"}

After ',':

    res = {"a"}
    curr = {}


After reading 'b':

    curr = {"b"}


At '}':

    res becomes:

    {"a", "b"}


For concatenation:

    {a,b}{c,d}

First part:

    {"a", "b"}

Second part:

    {"c", "d"}


Use Cartesian product:

    a + c = ac
    a + d = ad
    b + c = bc
    b + d = bd


The given solution uses a stack to save the state before
entering a new '{'.


Stack stores:

    previous res
    previous curr


When '}' is found, those states are restored.


Pseudo Code:
------------

curr = empty
res = empty
stack = empty


For every character x:


If x is a lowercase letter:

    If curr is empty:
        curr = {x}

    Else:
        append x to every string in curr


If x == '{':

    push res
    push curr

    clear res
    clear curr


If x == ',':

    move curr into res

    clear curr


If x == '}':

    retrieve previous curr
    retrieve previous res

    move current curr into res

    concatenate:

        previous curr × current res

    restore previous res


At the end:

    move curr into res

    sort res

    remove duplicates


Complete Optimal Code:
----------------------

class Solution {
public:

    vector<string> multiply(vector<string>& a,
                             vector<string>& b) {

        if (a.empty()) return b;
        if (b.empty()) return a;

        vector<string> ans;

        for (auto &i : a) {
            for (auto &j : b) {
                ans.push_back(i + j);
            }
        }

        return ans;
    }

    vector<string> braceExpansionII(string expression) {

        vector<string> res, curr;

        stack<vector<string>> st;

        for (char x : expression) {

            if (x >= 'a' && x <= 'z') {

                if (!curr.empty()) {

                    for (auto &i : curr) {
                        i += x;
                    }

                } else {

                    curr.push_back(string(1, x));
                }
            }

            else if (x == '{') {

                st.push(res);
                st.push(curr);

                res.clear();
                curr.clear();
            }

            else if (x == '}') {

                vector<string> preCurr = st.top();
                st.pop();

                vector<string> preRes = st.top();
                st.pop();

                for (auto &i : curr) {
                    res.push_back(i);
                }

                curr = multiply(preCurr, res);

                res = preRes;
            }

            else if (x == ',') {

                for (auto &i : curr) {
                    res.push_back(i);
                }

                curr.clear();
            }
        }

        for (auto &i : curr) {
            res.push_back(i);
        }

        sort(res.begin(), res.end());

        res.erase(
            unique(res.begin(), res.end()),
            res.end()
        );

        return res;
    }
};


Time Complexity:
----------------

Let:

    K = number of generated strings
    L = maximum string length

The Cartesian products generate the required combinations.

Approximately:

    O(K * L)

for generating the output, with additional sorting:

    O(K log K)

Therefore a practical bound is:

    O(K * L + K log K)


Space Complexity:
-----------------

    O(K * L)

for storing generated strings.

The stack additionally requires space proportional to the
nesting depth.


======================================================================
DRY RUN
======================================================================

Expression:

    {a,b}{c,{d,e}}


STEP 1:
-------

Read:

    {

Save:

    res = {}
    curr = {}

Clear both.


Read:

    a

Since curr is empty:

    curr = {"a"}


Read:

    ,

Move curr to res:

    res = {"a"}

Clear curr:

    curr = {}


Read:

    b

Since curr is empty:

    curr = {"b"}


Read:

    }

Move curr into res:

    res = {"a", "b"}


Restore previous state.

The first brace expression gives:

    {"a", "b"}


STEP 2:
-------

Read:

    {c,{d,e}}


Read:

    c

    curr = {"c"}


Read:

    ,

Move curr to res:

    res = {"c"}

curr:

    {}


STEP 3:
-------

Read:

    {d,e}


Read:

    d

    curr = {"d"}


Read:

    ,

    res = {"d"}
    curr = {}


Read:

    e

    curr = {"e"}


Read:

    }

Inside expression becomes:

    {"d", "e"}


Now combine with previous curr.

The second expression becomes:

    {"c", "d", "e"}


STEP 4:
-------

Now we have:

    {"a", "b"}

multiplied by:

    {"c", "d", "e"}


Cartesian product:

    a + c = ac
    a + d = ad
    a + e = ae

    b + c = bc
    b + d = bd
    b + e = be


Result:

    ac
    ad
    ae
    bc
    bd
    be


Sort:

    ["ac","ad","ae","bc","bd","be"]


======================================================================
INTERVIEW NOTES
======================================================================

Pattern:
--------

    Stack + Parsing + Cartesian Product
    String Generation
    Union + Concatenation


Key Observation:
----------------

The entire problem can be viewed as:

    ','       -> UNION
    adjacency -> CONCATENATION
    '{ }'     -> NESTED EXPRESSION


The most important operation is:

    multiply(a, b)

which performs:

    every string from a
    +
    every string from b


For example:

    a = {"x", "y"}
    b = {"1", "2"}

Then:

    multiply(a,b)

gives:

    {"x1", "x2", "y1", "y2"}


Common Mistakes:
----------------

1. Forgetting to save BOTH curr and res when '{' appears.

2. Restoring stack values in the wrong order.

3. Forgetting to clear curr after ','.

4. Forgetting to add curr into res before processing '}'.

5. Forgetting Cartesian product during concatenation.

6. Forgetting to sort the final answer.

7. Forgetting to remove duplicates.

8. Using:

       unique(res.begin(), res.end())

   without erase.

   WRONG:

       return vector<string>(
           res.begin(),
           unique(res.begin(), res.end())
       );

   Better:

       res.erase(
           unique(res.begin(), res.end()),
           res.end()
       );


9. Confusing UNION and CONCATENATION.

       {a,b} -> a OR b

       {a,b}{c,d}
            -> ac, ad, bc, bd


10. Using a set everywhere when a vector is sufficient and
    sorting/deduplicating only at the end.


When to use this approach:
--------------------------

Use this stack-based approach when:

    - the expression has nested braces
    - alternatives are separated by commas
    - adjacent expressions must be concatenated
    - you need all generated combinations
    - recursion can be replaced by explicit stack state


Competitive Programming Trick:
-------------------------------

Remember:

    COMMA
       =
    UNION


    ADJACENT
       =
    MULTIPLICATION / CARTESIAN PRODUCT


    BRACES
       =
    SAVE STATE + START NEW EXPRESSION


This mental model makes LeetCode 1096 much easier to implement.


======================================================================
*/

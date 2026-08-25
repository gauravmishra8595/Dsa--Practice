#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();

        int ones = 0;
        for (char c : s) ones += (c == '1');

        vector<int> zs, ze, len;

        for (int i = 0; i < n;) {
            if (s[i] == '0') {
                int j = i;
                while (j < n && s[j] == '0') j++;
                zs.push_back(i);
                ze.push_back(j - 1);
                len.push_back(j - i);
                i = j;
            } else {
                i++;
            }
        }

        int m = zs.size();

        if (m < 2)
            return vector<int>(queries.size(), ones);

        vector<int> val(m - 1);
        for (int i = 0; i < m - 1; i++)
            val[i] = len[i] + len[i + 1];

        int sz = val.size();

        vector<int> lg(sz + 1);
        for (int i = 2; i <= sz; i++)
            lg[i] = lg[i / 2] + 1;

        vector<vector<int>> st(lg[sz] + 1, vector<int>(sz));
        st[0] = val;

        for (int k = 1; k <= lg[sz]; k++) {
            int d = 1 << (k - 1);
            for (int i = 0; i + (1 << k) <= sz; i++)
                st[k][i] = max(st[k - 1][i], st[k - 1][i + d]);
        }

        auto rmq = [&](int l, int r) {
            int k = lg[r - l + 1];
            return max(st[k][l], st[k][r - (1 << k) + 1]);
        };

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int ja = lower_bound(ze.begin(), ze.end(), l) - ze.begin();
            int jb = upper_bound(zs.begin(), zs.end(), r) - zs.begin() - 2;

            int best = 0;

            if (ja <= jb) {

                auto calc = [&](int j) {
                    return val[j]
                         - max(0, l - zs[j])
                         - max(0, ze[j + 1] - r);
                };

                best = max(calc(ja), calc(jb));

                if (jb - ja >= 2)
                    best = max(best, rmq(ja + 1, jb - 1));
            }

            ans.push_back(ones + best);
        }

        return ans;
    }
};

int main() {
    Solution obj;

    string s = "0100";
    vector<vector<int>> queries = {{0,3},{0,2},{1,3},{2,3}};

    vector<int> ans = obj.maxActiveSectionsAfterTrade(s, queries);

    for (int x : ans)
        cout << x << " ";
    cout << "\n";

    return 0;
}

/*

======================== PROBLEM STATEMENT ========================

Given a binary string s and multiple queries [l, r].

For every query:

Construct

    t = '1' + s[l...r] + '1'

Perform at most one trade.

Trade consists of:

1. Convert one contiguous block of 1's surrounded by 0's into 0's.
2. Then convert one contiguous block of 0's surrounded by 1's into 1's.

Return the maximum number of active (1) sections after the optimal trade.

Queries are independent.

==================================================================

Example

Input:

s = "0100"

queries

[0,3]
[0,2]
[1,3]
[2,3]

Output

4 3 1 1

==================================================================
====================== BRUTE FORCE APPROACH =======================

Idea

For every query

Extract substring.

Add virtual 1's.

Enumerate every removable 1-block.

Remove it.

Enumerate every valid 0-block.

Flip it.

Count total ones.

Take maximum.

--------------------------------------------------

Pseudo Code

for every query

    build substring

    answer = countOnes

    for every valid 1-block

        erase

        for every valid 0-block

            fill

            answer=max(answer,ones)

--------------------------------------------------

Complete Brute Force Code

class Solution {
public:

    vector<int> solve(string s, vector<vector<int>>& queries){

        vector<int> ans;

        for(auto &q:queries){

            string cur=s.substr(q[0],q[1]-q[0]+1);

            // simulate every possible trade

            // O(length^2)

        }

        return ans;
    }

};

--------------------------------------------------

Time Complexity

O(Q * N^2)

Worst case even O(Q * N^3)

--------------------------------------------------

Space Complexity

O(N)

==================================================================
====================== OPTIMAL APPROACH ===========================

Observation

Suppose we have

000111000

Removing the middle 111 produces

000000000

The three zero blocks merge.

If

Left zero length = L

Middle one length = M

Right zero length = R

Gain

+(L+M+R)

Loss

-M

Net increase

L+R

Notice M cancels.

Only adjacent zero lengths matter.

--------------------------------------------------

Observation

Every removable one block corresponds to one valley between two zero blocks.

Profit

leftZeroLength + rightZeroLength

Near query boundaries,

profit gets clipped because only part of zero block belongs to query.

--------------------------------------------------

Data Structures

1. Prefix count of total ones.

2. Zero block decomposition

start[]

end[]

length[]

3. Sparse Table

Range Maximum Query over

value[i]=length[i]+length[i+1]

--------------------------------------------------

Pseudo Code

Build zero blocks

Build value array

Build sparse table

For every query

Find first usable valley

Find last usable valley

Answer

max(

left clipped,

right clipped,

RMQ middle

)

Final

ones + bestGain

--------------------------------------------------

Complete Optimal Code

(class Solution)

Same as executable code above.

--------------------------------------------------

Time Complexity

Preprocessing

O(N log N)

Each Query

O(log N)

Overall

O((N+Q)logN)

--------------------------------------------------

Space Complexity

O(N log N)

==================================================================
======================== DRY RUN ==================================

s

0100

Zero blocks

[0]

[2,3]

Lengths

1

2

Value

1+2=3

Total ones

1

Query

[0,3]

Gain

3

Answer

1+3=4

==================================================================
====================== INTERVIEW NOTES ============================

Pattern

Intervals + Sparse Table + Binary Search

--------------------------------------------------

Key Observation

Removing a surrounded 1 block merges adjacent zero blocks.

The removed one's length cancels.

Only adjacent zero lengths matter.

Profit

LeftZero + RightZero

--------------------------------------------------

Common Mistakes

1. Forgetting virtual 1's.

2. Counting removed one's length.

3. Ignoring clipped zero blocks near query boundaries.

4. RMQ indices off by one.

5. Using O(length) per query.

--------------------------------------------------

When to use this approach

Whenever

• Queries are static

• Range maximum is required

• Values are immutable

Sparse Table is an ideal choice.

==================================================================

*/

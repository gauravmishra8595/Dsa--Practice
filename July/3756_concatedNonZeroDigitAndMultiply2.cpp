#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>> &queries)
    {
        int n = s.size();

        // Store only non-zero digits
        vector<int> digit;
        vector<int> id(n, -1);

        for (int i = 0; i < n; i++)
        {
            if (s[i] != '0')
            {
                id[i] = digit.size();
                digit.push_back(s[i] - '0');
            }
        }

        int m = digit.size();

        // powers of 10 modulo MOD
        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        // Prefix number and prefix digit sum
        vector<long long> prefNum(m + 1, 0);
        vector<int> prefSum(m + 1, 0);

        for (int i = 0; i < m; i++)
        {
            prefNum[i + 1] = (prefNum[i] * 10 + digit[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + digit[i];
        }

        // Previous non-zero position
        vector<int> prevNZ(n, -1);
        int last = -1;
        for (int i = 0; i < n; i++)
        {
            if (s[i] != '0')
                last = i;
            prevNZ[i] = last;
        }

        // Next non-zero position
        vector<int> nextNZ(n, -1);
        last = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] != '0')
                last = i;
            nextNZ[i] = last;
        }

        vector<int> ans;

        for (auto &q : queries)
        {
            int l = q[0];
            int r = q[1];

            int L = nextNZ[l];

            // No non-zero digit in this range
            if (L == -1 || L > r)
            {
                ans.push_back(0);
                continue;
            }

            int R = prevNZ[r];

            int a = id[L];
            int b = id[R];

            int len = b - a + 1;

            long long number =
                (prefNum[b + 1] -
                 (prefNum[a] * pow10[len]) % MOD +
                 MOD) %
                MOD;

            long long sum = prefSum[b + 1] - prefSum[a];

            ans.push_back((number * sum) % MOD);
        }

        return ans;
    }
};

int main()
{

    string s = "10203004";

    vector<vector<int>> queries = {
        {0, 7},
        {1, 3},
        {4, 6}};

    Solution obj;

    vector<int> ans = obj.sumAndMultiply(s, queries);

    cout << "Answer : ";

    for (int x : ans)
        cout << x << " ";

    return 0;
}

/*
========================= BRUTE FORCE =========================

Idea:
For every query:

1. Traverse substring s[l...r].
2. Ignore all zeros.
3. Form the number digit by digit.
4. Calculate digit sum.
5. Return number * sum.

Pseudo Code:

for every query
{
    number = 0
    sum = 0

    for(i=l;i<=r;i++)
    {
        if(s[i]!='0')
        {
            number = number*10 + digit
            sum += digit
        }
    }

    answer = (number * sum)%MOD
}

Time Complexity:
O(Q * N)

Worst Case:
N = 100000
Q = 100000

=> 10^10 operations (TLE)


========================= OPTIMAL APPROACH =========================

Observation:
The non-zero digits never change.

Example:
s = "10203004"

Compressed digits = [1,2,3,4]

Instead of processing every query separately,
preprocess useful information once.

Preprocessing:

1. Store only non-zero digits.

2. Prefix Sum
prefSum[i]
= sum of first i non-zero digits.

Used to calculate digit sum in O(1).

3. Prefix Number
prefNum[i]
= number formed by first i non-zero digits.

Example

Digits = 1 2 3 4

prefNum

0
1
12
123
1234

4. pow10[]
Stores powers of 10 modulo MOD.

5. nextNZ[]
next non-zero index for every position.

6. prevNZ[]
previous non-zero index for every position.

For every query:

Step 1:
Find first non-zero digit using nextNZ.

Step 2:
Find last non-zero digit using prevNZ.

Step 3:
If no non-zero digit exists
answer = 0.

Step 4:
Using prefix arrays,

Digit Sum =
prefSum[right]-prefSum[left]

Number =
(prefNum[right+1]
 - prefNum[left]*10^(length))

Everything is obtained in O(1).

Overall Complexity

Preprocessing : O(N)

Each Query : O(1)

Total :

O(N + Q)

Space Complexity :

O(N)

This is the optimal solution accepted on LeetCode.
*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string smallestNumber(string num, long long t)
    {
        long long temp = t;

        // Check whether t contains any prime factor > 7
        for (int i = 2; i <= 9; i++)
        {
            while (temp % i == 0)
                temp /= i;
        }
        if (temp > 1)
            return "-1";

        int n = num.size();
        vector<long long> rem(n + 1);
        rem[0] = t;

        int pos = n - 1;

        // rem[i] = remaining divisor after processing first i digits
        for (int i = 0; i < n; i++)
        {
            if (num[i] == '0')
            {
                pos = i;
                break;
            }
            rem[i + 1] = rem[i] / gcd(rem[i], 1LL * (num[i] - '0'));
        }

        // Already satisfies
        if (rem[n] == 1)
            return num;

        // Try increasing digits from right to left
        for (int i = pos; i >= 0; i--)
        {

            while (++num[i] <= '9')
            {

                long long cur = rem[i] / gcd(rem[i], 1LL * (num[i] - '0'));

                int d = 9;

                // Fill suffix greedily with largest digits
                for (int j = n - 1; j > i; j--)
                {
                    while (cur % d != 0)
                        d--;
                    cur /= d;
                    num[j] = char('0' + d);
                }

                if (cur == 1)
                    return num;
            }
        }

        // Need one extra digit
        string ans;

        for (int d = 9; d >= 2; d--)
        {
            while (t % d == 0)
            {
                ans.push_back(char('0' + d));
                t /= d;
            }
        }

        ans += string(max(0, n + 1 - (int)ans.size()), '1');

        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main()
{
    Solution obj;

    string num;
    long long t;

    cin >> num >> t;

    cout << obj.smallestNumber(num, t) << endl;

    return 0;
}

/*

==========================================================
                Problem Statement
==========================================================

Given a positive integer as a string num and an integer t,
return the smallest zero-free number greater than or equal
to num such that the product of its digits is divisible by t.

If no such number exists, return "-1".

----------------------------------------------------------
Example
----------------------------------------------------------

Input:
num = "1234"
t = 256

Output:
1488

Explanation:
1*4*8*8 = 256, divisible by 256.

==========================================================
                Brute Force Approach
==========================================================

Idea
-----

Start from num and keep increasing by 1.
For every number:
1. Ignore if it contains digit 0.
2. Compute product of digits.
3. Check if divisible by t.
4. Return first valid number.

----------------------------------------------------------
Pseudo Code
----------------------------------------------------------

current = num

while(true)

    if(no zero in current)

        product = product of digits

        if(product % t == 0)
            return current

    current++

----------------------------------------------------------
Complete Brute Force Code
----------------------------------------------------------

class Solution {
public:
    string smallestNumber(string num, long long t) {

        long long cur = stoll(num);

        while (true) {

            string s = to_string(cur);

            bool ok = true;
            long long prod = 1;

            for(char c : s){
                if(c=='0'){
                    ok=false;
                    break;
                }
                prod*=c-'0';
            }

            if(ok && prod%t==0)
                return s;

            cur++;
        }
    }
};

----------------------------------------------------------
Time Complexity
----------------------------------------------------------

Very large / practically infinite.

----------------------------------------------------------
Space Complexity
----------------------------------------------------------

O(1)

==========================================================
                Optimal Approach
==========================================================

Observation
-----------

Only prime factors 2,3,5,7 can be produced by decimal digits.

If t contains any other prime factor,
answer is immediately impossible.

Instead of checking every larger number,
modify the current number greedily.

----------------------------------------------------------
Intuition
----------------------------------------------------------

1. Maintain rem[i]
   = remaining divisor after processing first i digits.

2. Traverse digits from right to left.

3. Increase current digit.

4. Greedily fill remaining suffix using largest digits
   (9 to 2) so that remaining divisor becomes 1.

5. First successful construction is the smallest answer.

6. If impossible for same length,
   construct smallest valid number of length n+1.

----------------------------------------------------------
Pseudo Code
----------------------------------------------------------

factor check

if impossible
    return -1

build rem[]

if rem[n]==1
    return num

for every position from right

    increase digit

    compute remaining divisor

    greedily fill suffix

    if divisor becomes 1
        return answer

construct answer with one extra digit

----------------------------------------------------------
Complete Optimal Code
----------------------------------------------------------

class Solution {
public:
    string smallestNumber(string num, long long t) {

        long long temp=t;

        for(int i=2;i<=9;i++)
            while(temp%i==0)
                temp/=i;

        if(temp>1)
            return "-1";

        int n=num.size();

        vector<long long> rem(n+1);

        rem[0]=t;

        int pos=n-1;

        for(int i=0;i<n;i++){

            if(num[i]=='0'){
                pos=i;
                break;
            }

            rem[i+1]=rem[i]/gcd(rem[i],1LL*(num[i]-'0'));
        }

        if(rem[n]==1)
            return num;

        for(int i=pos;i>=0;i--){

            while(++num[i]<='9'){

                long long cur=rem[i]/gcd(rem[i],1LL*(num[i]-'0'));

                int d=9;

                for(int j=n-1;j>i;j--){

                    while(cur%d)
                        d--;

                    cur/=d;

                    num[j]='0'+d;
                }

                if(cur==1)
                    return num;
            }
        }

        string ans;

        for(int d=9;d>=2;d--)

            while(t%d==0){

                ans.push_back('0'+d);

                t/=d;
            }

        ans+=string(max(0,n+1-(int)ans.size()),'1');

        reverse(ans.begin(),ans.end());

        return ans;
    }
};

----------------------------------------------------------
Time Complexity
----------------------------------------------------------

O(9 * N)

----------------------------------------------------------
Space Complexity
----------------------------------------------------------

O(N)

==========================================================
                Dry Run
==========================================================

num = 1234
t = 256

Remaining divisor after prefix

1 -> 256
12 ->128
123 ->128
1234 ->32

Not satisfied.

Increase digits from right.

1235
1236
...
1488

Product

1*4*8*8 = 256

Answer = 1488

==========================================================
                Interview Notes
==========================================================

Pattern
-------

Greedy + Number Theory + Prefix Processing

----------------------------------------------------------
Key Observation
----------------------------------------------------------

Digits can only contribute prime factors
2,3,5,7.

----------------------------------------------------------
Common Mistakes
----------------------------------------------------------

1. Forgetting numbers must be zero-free.

2. Not checking impossible prime factors.

3. Using brute-force increment.

4. Overflow while computing product.

----------------------------------------------------------
When to use this approach
----------------------------------------------------------

Whenever

- digit product matters
- only factors of decimal digits matter
- answer requires smallest lexicographical construction
- constraints are too large for brute force

==========================================================

*/
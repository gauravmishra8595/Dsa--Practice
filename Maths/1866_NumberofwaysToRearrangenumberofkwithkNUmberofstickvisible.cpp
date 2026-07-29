#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    long long dp[1001][1001];
    const long long MOD = 1e9 + 7;

    long long solve(int n, int k)
    {

        if (n == 0 && k == 0)
            return 1;

        if (n == 0 || k == 0)
            return 0;

        if (dp[n][k] != -1)
            return dp[n][k];

        // Place largest stick:
        // 1. Visible -> remaining n-1 sticks with k-1 visible
        // 2. Hidden -> remaining n-1 sticks with k visible

        long long visible = solve(n - 1, k - 1);

        long long hidden = solve(n - 1, k) * (n - 1);

        return dp[n][k] = (visible + hidden) % MOD;
    }

    int rearrangeSticks(int n, int k)
    {

        memset(dp, -1, sizeof(dp));

        return solve(n, k);
    }
};

int main()
{

    Solution sol;

    int n = 3;
    int k = 2;

    cout << sol.rearrangeSticks(n, k);

    return 0;
}

/*

============================================================
Problem Statement
============================================================

LeetCode 1866:
Number of Ways to Rearrange Sticks With K Sticks Visible


You have n sticks with different heights.

Arrange them in a line.

A stick is visible if there is no taller stick before it.

Return the number of arrangements where exactly k sticks are
visible from the left.


Example:

Input:

n = 3
k = 2


Possible arrangements:

[1,3,2] -> visible: 1,3
[2,3,1] -> visible: 2,3
[2,1,3] -> visible: 2,3

Answer:

3


============================================================
Brute Force Approach
============================================================

Idea:
------

Generate all permutations of sticks.

For every permutation:

1. Count visible sticks.
2. If count == k, increase answer.


Pseudo Code:
------------

generate all permutations

count visible sticks in every permutation

if visible == k:
    answer++


Complete Brute Force Code:

------------------------------------------------------------

// Not feasible for large n

class Solution {

public:

    int ans = 0;


    void check(vector<int>& arr, int k) {

        int mx = 0;
        int count = 0;


        for(int x : arr) {

            if(x > mx) {

                mx = x;
                count++;
            }
        }


        if(count == k)
            ans++;
    }


    void permute(vector<int>& arr, int idx, int k) {

        if(idx == arr.size()) {

            check(arr,k);
            return;
        }


        for(int i = idx; i < arr.size(); i++) {

            swap(arr[i],arr[idx]);

            permute(arr,idx+1,k);

            swap(arr[i],arr[idx]);
        }
    }


    int rearrangeSticks(int n,int k) {

        vector<int> arr(n);

        iota(arr.begin(),arr.end(),1);


        permute(arr,0,k);

        return ans;
    }
};


------------------------------------------------------------


Time Complexity:

O(n! * n)


Space Complexity:

O(n)


============================================================
Optimal Approach
============================================================

Observation:
------------

Consider the tallest stick.

The tallest stick is always visible.

For n sticks:

Case 1:
Tallest stick is placed at the end.

Then it is visible and remaining n-1 sticks need k-1 visible.

Ways:

dp[n-1][k-1]


Case 2:
Tallest stick is not the first visible stick.

It is hidden by smaller sticks.

The tallest stick can be inserted in any of the n-1 positions.

Remaining sticks need k visible.

Ways:

(n-1) * dp[n-1][k]


Recurrence:

dp[n][k] =
dp[n-1][k-1] +
(n-1) * dp[n-1][k]


Intuition:
----------

Use the position of the tallest stick to break the problem
into smaller subproblems.


Pseudo Code:
------------

solve(n,k):

    if n==0 and k==0:
        return 1

    if n==0 or k==0:
        return 0


    visible =
        solve(n-1,k-1)


    hidden =
        (n-1)*solve(n-1,k)


    return visible + hidden


============================================================
Complete Optimal Code
============================================================

class Solution {

public:

long long dp[1001][1001];


int rearrangeSticks(int n,int k){

    memset(dp,-1,sizeof(dp));

    return solve(n,k);
}

};


============================================================

Time Complexity:

O(n*k)


Space Complexity:

O(n*k)


============================================================
Dry Run
============================================================

n = 3
k = 2


dp(3,2)


Visible case:

dp(2,1)


Hidden case:

2 * dp(2,2)


Calculate:

dp(2,1)

= dp(1,0) + 1*dp(1,1)

= 0 + 1

= 1


dp(2,2)

= dp(1,1)

= 1


Therefore:

dp(3,2)

= 1 + 2*1

= 3


Answer = 3


============================================================
Interview Notes
============================================================

Pattern:

Dynamic Programming + Combinatorics


Key Observation:

Focus on the tallest stick.

Its position decides whether it contributes a visible stick
or remains hidden.


Common Mistakes:

1. Forgetting multiplication by (n-1).

2. Wrong base cases.

3. Not using modulo.

4. Confusing visible sticks with total sticks.


When to use this approach:

Use when:

- Counting arrangements.
- One element (largest/smallest) creates natural cases.
- Recursive relation depends on previous states.

============================================================

*/

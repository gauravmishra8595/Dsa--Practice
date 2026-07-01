#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



class Solution
{
public:
    int minInsertions(string s)
    {

        string rev = s;
        reverse(rev.begin(), rev.end());

        int n = s.size();

        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        // Standard LCS DP
        for (int i = 1; i <= n; i++)
        {

            for (int j = 1; j <= n; j++)
            {

                if (s[i - 1] == rev[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }

            prev = curr;
        }

        int lps = prev[n];

        return n - lps;
    }
};

int main()
{

    Solution obj;

    string s;

    cout << "Enter string : ";
    cin >> s;

    cout << "Minimum Insertions = " << obj.minInsertions(s);

    return 0;
}



// ==========================================================
// LeetCode 1312 - Minimum Insertion Steps to Make a String Palindrome
// ==========================================================

// There are two popular DP approaches:

// 1. Memoization (Top-Down DP)
//    Time  : O(n^2)
//    Space : O(n^2)

// 2. LCS + Space Optimization (Optimal)
//    Time  : O(n^2)
//    Space : O(n)

// The code below implements the OPTIMAL solution.

// ----------------------------------------------------------
// Why does LCS work?

// Suppose

// s = "mbadm"

// Reverse it

// rev = "mdabm"

// The Longest Common Subsequence between
// s and rev is actually the Longest Palindromic
// Subsequence (LPS).

// Characters already inside the LPS never need insertion.

// Therefore,

// Minimum Insertions = n - LPS

// ----------------------------------------------------------

// ==========================================================
// Approach 1 : Memoization (Top-Down DP)
// ==========================================================

// State

// solve(i, j)

// returns minimum insertions required
// to make substring s[i...j] palindrome.

// ----------------------------------------------------------

// Base Case

// If i >= j

// Substring is already palindrome.

// Return 0.

// ----------------------------------------------------------

// Transition

// Case 1

// If s[i] == s[j]

// No insertion required.

// Move both pointers.

// solve(i+1, j-1)

// ----------------------------------------------------------

// Case 2

// Characters are different.

// We have two choices.

// Choice 1

// Insert character matching s[i]

// 1 + solve(i+1, j)

// Choice 2

// Insert character matching s[j]

// 1 + solve(i, j-1)

// Take minimum.

// dp[i][j] =
// 1 + min(
//     solve(i+1,j),
//     solve(i,j-1)
// )

// ----------------------------------------------------------

// Complexity

// Time  : O(n²)

// Space : O(n²)

// ==========================================================
// Approach 2 : Optimal (LCS)
// ==========================================================

// Observation

// Instead of directly counting insertions,
// find the Longest Palindromic Subsequence.

// LPS can be found by

// LCS(s, reverse(s))

// Reason

// A palindrome reads the same forward and backward.

// Therefore,

// Longest Common Subsequence between
// the string and its reverse
// is the Longest Palindromic Subsequence.

// Finally,

// Minimum Insertions

// = Length of String

// - Length of LPS

// ----------------------------------------------------------

// LCS DP

// if(s[i-1] == rev[j-1])

//     curr[j] = 1 + prev[j-1]

// else

//     curr[j] = max(prev[j], curr[j-1])

// ----------------------------------------------------------

// Why Space Optimization?

// Each row only depends on

// Previous row

// Current row

// So instead of an n x n table,
// store only two rows.

// prev -> previous row

// curr -> current row

// ----------------------------------------------------------

// Complexity

// Time  : O(n²)

// Space : O(n)

//----------------------------
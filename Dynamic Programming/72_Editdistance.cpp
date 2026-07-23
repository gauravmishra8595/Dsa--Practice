#include <bits/stdc++.h>
using namespace std;

// ===================== Optimal Solution (Bottom-Up DP) =====================

class Solution
{
public:
    int minDistance(string word1, string word2)
    {

        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Base Cases
        for (int i = 0; i <= m; i++)
        {
            dp[i][0] = i;
        }

        for (int j = 0; j <= n; j++)
        {
            dp[0][j] = j;
        }

        // DP Transition
        for (int i = 1; i <= m; i++)
        {

            for (int j = 1; j <= n; j++)
            {

                if (word1[i - 1] == word2[j - 1])
                {

                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {

                    dp[i][j] = 1 + min({
                                       dp[i - 1][j],    // Delete
                                       dp[i][j - 1],    // Insert
                                       dp[i - 1][j - 1] // Replace
                                   });
                }
            }
        }

        return dp[m][n];
    }
};

int main()
{

    Solution obj;

    string word1 = "horse";
    string word2 = "ros";

    cout << "Minimum Operations = "
         << obj.minDistance(word1, word2);

    return 0;
}

/*

===============================================================================
              LEETCODE 72 - EDIT DISTANCE
===============================================================================


Problem Statement
-----------------

Given two strings word1 and word2, return the minimum number of operations
required to convert word1 into word2.

Allowed operations:

1. Insert a character
2. Delete a character
3. Replace a character


Example
-------

Input:

word1 = "horse"
word2 = "ros"


Output:

3


Explanation:

horse -> rorse (replace h with r)
rorse -> rose  (delete r)
rose  -> ros   (delete e)


===============================================================================
AVAILABLE APPROACHES
===============================================================================


1. Brute Force Recursion

Time Complexity:
O(3^(m+n))

Space Complexity:
O(m+n)


2. Recursion + Memoization (Top Down DP)

Time Complexity:
O(m*n)

Space Complexity:
O(m*n)


3. Bottom-Up Dynamic Programming  <-- BEST CLASSIC APPROACH

Time Complexity:
O(m*n)

Space Complexity:
O(m*n)


4. Space Optimized DP

Time Complexity:
O(m*n)

Space Complexity:
O(n)


===============================================================================
BRUTE FORCE APPROACH
===============================================================================


Idea
----

Try all three possible operations:

1. Insert
2. Delete
3. Replace

Choose the minimum.


Pseudo Code
-----------

solve(i,j)

if i reaches end of word1:

    return remaining characters of word2


if j reaches end of word2:

    return remaining characters of word1


if characters are same:

    solve(i+1,j+1)


else:

    1 + min(

        insert,
        delete,
        replace

    )


Complete Brute Force Code (Revision Only)
------------------------------------------


class Solution {

public:

int solve(int i,int j,string &a,string &b){

    if(i==a.size())
        return b.size()-j;


    if(j==b.size())
        return a.size()-i;


    if(a[i]==b[j])
        return solve(i+1,j+1,a,b);


    return 1 + min({

        solve(i,j+1,a,b),     // Insert

        solve(i+1,j,a,b),     // Delete

        solve(i+1,j+1,a,b)    // Replace

    });
}


int minDistance(string a,string b){

    return solve(0,0,a,b);

}

};


Time Complexity
---------------

O(3^(m+n))


Space Complexity
----------------

O(m+n)


===============================================================================
TOP DOWN DP (MEMOIZATION)
===============================================================================


Idea
----

Store answers of already calculated states.

dp[i][j] means:

Minimum operations to convert:

word1[i...end]

to

word2[j...end]


Pseudo Code
-----------


if dp[i][j] already calculated

    return dp[i][j]


if characters match

    dp[i][j] = solve(i+1,j+1)


else

    dp[i][j] = 1 + min(

        insert,

        delete,

        replace

    )


Time Complexity
---------------

O(m*n)


Space Complexity
----------------

O(m*n)


===============================================================================
OPTIMAL APPROACH (BOTTOM-UP DP)
===============================================================================


Observation
-----------

Create a table:

dp[i][j]


Meaning:

Minimum operations to convert first i characters of word1
into first j characters of word2.


Base Cases:

If word1 is empty:

Need j insertions.


If word2 is empty:

Need i deletions.



Intuition
---------

For every pair of characters:


Case 1:
Characters are equal.

No operation required.

dp[i][j] = dp[i-1][j-1]



Case 2:
Characters are different.

Try all operations:

1. Delete:

dp[i-1][j]


2. Insert:

dp[i][j-1]


3. Replace:

dp[i-1][j-1]


Take minimum and add 1.


Pseudo Code
-----------


Create dp table (m+1)*(n+1)


Initialize:

dp[i][0] = i

dp[0][j] = j


for i = 1 to m

    for j = 1 to n


        if word1[i-1]==word2[j-1]

            dp[i][j]=dp[i-1][j-1]


        else

            dp[i][j]=1+min(

                delete,

                insert,

                replace

            )


return dp[m][n]



Complete Optimal Code (Revision Only)
--------------------------------------


class Solution {

public:

int minDistance(string word1,string word2){

    int m=word1.size();
    int n=word2.size();


    vector<vector<int>> dp(
        m+1,
        vector<int>(n+1,0)
    );


    for(int i=0;i<=m;i++)
        dp[i][0]=i;


    for(int j=0;j<=n;j++)
        dp[0][j]=j;



    for(int i=1;i<=m;i++){

        for(int j=1;j<=n;j++){


            if(word1[i-1]==word2[j-1]){

                dp[i][j]=dp[i-1][j-1];

            }

            else{

                dp[i][j]=1+min({

                    dp[i-1][j],

                    dp[i][j-1],

                    dp[i-1][j-1]

                });

            }

        }

    }


    return dp[m][n];

}

};


Time Complexity
---------------

O(m*n)


Space Complexity
----------------

O(m*n)


===============================================================================
DRY RUN
===============================================================================


word1 = "horse"

word2 = "ros"



DP final value:


      "" r o s

""    0 1 2 3

h     1 1 2 3

o     2 2 1 2

r     3 2 2 2

s     4 3 3 2

e     5 4 4 3



Answer:

dp[5][3] = 3


===============================================================================
INTERVIEW NOTES
===============================================================================


Pattern
-------

Dynamic Programming on Strings


Key Observation
---------------

Whenever two characters mismatch:

Three choices are possible:

1. Delete
2. Insert
3. Replace


Take the minimum.


Common Mistakes
---------------

1. Wrong base cases.

2. Forgetting +1 for operation.

3. Mixing insert/delete indexes.

4. Using max instead of min.

5. Confusing Edit Distance with LCS.


When to use this approach
-------------------------

Use Edit Distance DP when questions involve:

✔ Convert one string into another

✔ Minimum operations

✔ Insert/Delete/Replace

✔ String similarity


===============================================================================

*/
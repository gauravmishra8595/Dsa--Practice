#include <bits/stdc++.h>
using namespace std;

// Optimal Solution Implementation
class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {

        vector<vector<int>> ans;

        for (int i = 0; i < numRows; i++)
        {

            vector<int> row(i + 1, 1);

            for (int j = 1; j < i; j++)
            {
                row[j] = ans[i - 1][j - 1] + ans[i - 1][j];
            }

            ans.push_back(row);
        }

        return ans;
    }
};

int main()
{

    Solution sol;

    int numRows = 5;

    vector<vector<int>> ans = sol.generate(numRows);

    for (auto row : ans)
    {
        for (auto x : row)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}

/*

============================================================
Problem Statement
============================================================

LeetCode 118: Pascal's Triangle

Given an integer numRows, return the first numRows of Pascal's
triangle.

In Pascal's Triangle:

- The first and last element of every row is 1.
- Every middle element is the sum of the two numbers directly
  above it.


Example:

Input:
numRows = 5

Output:

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]


============================================================
Brute Force Approach
============================================================

Idea:
------

Generate every element using the mathematical formula:

nCr = n! / (r! * (n-r)!)

For every row, calculate each value independently.


Pseudo Code:
------------

function generate(numRows):

    ans = empty list

    for row from 0 to numRows-1:

        currentRow = empty list

        for col from 0 to row:

            value = rowCcol

            add value to currentRow


        add currentRow to ans


    return ans


Complete Brute Force Code:

------------------------------------------------------------

#include<bits/stdc++.h>
using namespace std;

class Solution {

public:

    long long factorial(int n) {

        long long ans = 1;

        for(int i = 1; i <= n; i++)
            ans *= i;

        return ans;
    }


    vector<vector<int>> generate(int numRows) {

        vector<vector<int>> ans;


        for(int i = 0; i < numRows; i++) {

            vector<int> row;


            for(int j = 0; j <= i; j++) {

                long long value =
                factorial(i) /
                (factorial(j) * factorial(i-j));


                row.push_back(value);
            }


            ans.push_back(row);
        }


        return ans;
    }
};


------------------------------------------------------------


Time Complexity:
----------------

O(n^3)

Because factorial is calculated repeatedly for every element.


Space Complexity:
-----------------

O(n^2)

For storing the triangle.


============================================================
Optimal Approach
============================================================

Observation:
------------

Each element in Pascal's Triangle depends only on the previous
row.

For every row:

- First element = 1
- Last element = 1
- Middle elements:

current[j] = previous[j-1] + previous[j]


Intuition:
----------

Build the triangle row by row.

Instead of calculating combinations, reuse already calculated
values from the previous row.


Pseudo Code:
------------

function generate(numRows):

    ans = empty list


    for i from 0 to numRows-1:

        create row of size i+1 filled with 1


        for j from 1 to i-1:

            row[j] =
            previousRow[j-1] + previousRow[j]


        add row to ans


    return ans


Complete Optimal Code:

------------------------------------------------------------

class Solution {

public:

    vector<vector<int>> generate(int numRows) {


        vector<vector<int>> ans;


        for(int i = 0; i < numRows; i++) {


            vector<int> row(i+1, 1);


            for(int j = 1; j < i; j++) {

                row[j] =
                ans[i-1][j-1] +
                ans[i-1][j];
            }


            ans.push_back(row);
        }


        return ans;
    }
};


------------------------------------------------------------


Time Complexity:
----------------

O(n^2)

Because every element of the triangle is calculated once.


Space Complexity:
-----------------

O(n^2)

For storing the complete Pascal Triangle.


============================================================
Dry Run With Example
============================================================

Input:

numRows = 5


Iteration 1:

i = 0

row = [1]

ans:

[
 [1]
]


Iteration 2:

i = 1

row = [1,1]

ans:

[
 [1],
 [1,1]
]


Iteration 3:

i = 2

row = [1,1,1]

Middle element:

row[1] =
ans[1][0] + ans[1][1]

= 1 + 1

= 2


row = [1,2,1]


Iteration 4:

i = 3

row = [1,1,1,1]


Middle:

row[1] = 1 + 2 = 3

row[2] = 2 + 1 = 3


row = [1,3,3,1]


Iteration 5:

i = 4

Middle values:

row[1] = 1 + 3 = 4

row[2] = 3 + 3 = 6

row[3] = 3 + 1 = 4


Final Answer:

[
 [1],
 [1,1],
 [1,2,1],
 [1,3,3,1],
 [1,4,6,4,1]
]


============================================================
Interview Notes
============================================================

Pattern:
--------

Dynamic Programming / Previous Row Dependency


Key Observation:
----------------

Every value depends on the two values directly above it.


Common Mistakes:
----------------

1. Forgetting that every row starts and ends with 1.

2. Accessing previous row when i = 0.

3. Using factorial unnecessarily causing overflow.

4. Wrong row indexing.


When to use this approach:
--------------------------

Use this approach when:

- Generating Pascal's Triangle.
- Current values depend on previous computed values.
- Avoiding repeated mathematical calculations.

============================================================

*/

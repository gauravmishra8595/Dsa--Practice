#include <bits/stdc++.h>
using namespace std;

// =========================================================
// Optimal Solution
// =========================================================

class Solution
{
public:
    vector<int> arrayRankTransform(vector<int> &arr)
    {
        vector<int> temp = arr;

        sort(temp.begin(), temp.end());

        unordered_map<int, int> mp;

        int rank = 1;

        for (int x : temp)
        {
            if (mp.find(x) == mp.end())
            {
                mp[x] = rank;
                rank++;
            }
        }

        for (int i = 0; i < arr.size(); i++)
        {
            arr[i] = mp[arr[i]];
        }

        return arr;
    }
};

// =========================================================
// Main Function For VS Code Testing
// =========================================================

int main()
{
    vector<int> arr = {40, 10, 20, 30, 20};

    Solution obj;

    vector<int> ans = obj.arrayRankTransform(arr);

    for (int x : ans)
        cout << x << " ";

    cout << endl;

    return 0;
}

/*
=========================================================
LeetCode 1331 - Rank Transform of an Array
=========================================================


Problem Statement
-----------------

Given an array arr, replace every element with its rank.

Rules:

1. Smallest element gets rank 1.
2. Larger elements get larger ranks.
3. Equal elements get the same rank.
4. Rank should be minimum possible.



Example:

Input:

[40,10,20,30,20]


Sorted:

[10,20,20,30,40]


Rank Mapping:

10 -> 1
20 -> 2
30 -> 3
40 -> 4


Output:

[4,1,2,3,2]



=========================================================
BRUTE FORCE APPROACH
=========================================================


Idea
----

For every element:

Find how many UNIQUE values are smaller than it.

Rank = number of smaller unique values + 1.



Pseudo Code
-----------


for every element i

    rank = 1

    for every element j

        if arr[j] < arr[i]

            check if arr[j] was counted before

            if not counted

                rank++


    answer[i] = rank



Brute Force Code
----------------


vector<int> bruteForce(vector<int> arr)
{
    int n = arr.size();

    vector<int> ans(n);


    for(int i = 0; i < n; i++)
    {
        int rank = 1;


        for(int j = 0; j < n; j++)
        {
            if(arr[j] < arr[i])
            {
                bool alreadyCounted = false;


                for(int k = 0; k < j; k++)
                {
                    if(arr[k] == arr[j])
                    {
                        alreadyCounted = true;
                        break;
                    }
                }


                if(!alreadyCounted)
                    rank++;
            }
        }


        ans[i] = rank;
    }


    return ans;
}



Time Complexity:

O(n^3)


Space Complexity:

O(n)



=========================================================
OPTIMAL APPROACH
=========================================================


Observation
-----------

We need ranks but original order must remain unchanged.

Therefore:

Do not sort the original array.

Create a copy.

Sort the copy.

Create a mapping:

value -> rank


Then replace every value in original array using this map.



Pseudo Code
-----------


temp = arr


sort(temp)


rank = 1


for every element x in temp

    if x is not present in map

        map[x] = rank

        rank++



for every index i

    arr[i] = map[arr[i]]



return arr



Optimal Code
------------


vector<int> arrayRankTransform(vector<int>& arr)
{
    vector<int> temp = arr;


    sort(temp.begin(), temp.end());


    unordered_map<int,int> mp;


    int rank = 1;


    for(int x : temp)
    {
        if(mp.find(x) == mp.end())
        {
            mp[x] = rank;
            rank++;
        }
    }


    for(int i = 0; i < arr.size(); i++)
    {
        arr[i] = mp[arr[i]];
    }


    return arr;
}



Time Complexity:

Copy Array      O(n)

Sorting         O(n log n)

Creating Map    O(n)

Replacing       O(n)


Overall:

O(n log n)



Space Complexity:

O(n)



=========================================================
INTERVIEW NOTES
=========================================================


Pattern:

Sorting + HashMap


Key Observation:

The original order matters.

So:

Never sort the original array.

Sort a copy and create:

value -> rank


Common Mistakes:

1. Sorting original array.

2. Assigning different ranks to duplicate values.

3. Starting rank from 0 instead of 1.



Dry Run:

Input:

40 10 20 30 20


Copy:

40 10 20 30 20


After Sorting:

10 20 20 30 40


Map:

10 -> 1

20 -> 2

30 -> 3

40 -> 4


Replace:

40 -> 4

10 -> 1

20 -> 2

30 -> 3

20 -> 2


Answer:

4 1 2 3 2



Final Complexity:


Brute Force:

Time  : O(n^3)

Space : O(n)



Optimal:

Time  : O(n log n)

Space : O(n)


=========================================================
*/